/*
 * OHCI HCD (Host Controller Driver) for USB.
 *
 *  Copyright (C) 2004 SAN People (Pty) Ltd.
 *  Copyright (C) 2005 Thibaut VARENE <varenet@parisc-linux.org>
 *
 * AT91 Bus Glue
 *
 * Based on fragments of 2.4 driver by Rick Bronson.
 * Based on ohci-omap.c
 *
 * This file is licenced under the GPL.
 */

#include <linux/clk.h>
#include <linux/platform_device.h>

#include <asm/mach-types.h>
#include <asm/hardware.h>
#include <asm/arch/board.h>
#include <asm/arch/cpu.h>

#ifndef CONFIG_ARCH_AT91
#error "CONFIG_ARCH_AT91 must be defined."
#endif

/* interface and function clocks; sometimes also an AHB clock */
static struct clk *iclk, *fclk, *hclk;
static int clocked;

extern int usb_disabled(void);

/*-------------------------------------------------------------------------*/

static void at91_start_clock(void)
{
	if (cpu_is_at91sam9261())
		clk_enable(hclk);
	clk_enable(iclk);
	clk_enable(fclk);
	clocked = 1;
}

static void at91_stop_clock(void)
{
	clk_disable(fclk);
	clk_disable(iclk);
	if (cpu_is_at91sam9261())
		clk_disable(hclk);
	clocked = 0;
}

static void at91_start_hc(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct ohci_regs __iomem *regs = hcd->regs;

	dev_dbg(&pdev->dev, "start\n");

	/*
	 * Start the USB clocks.
	 */
	at91_start_clock();

	/*
	 * The USB host controller must remain in reset.
	 */
	writel(0, &regs->control);
}

static void at91_stop_hc(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct ohci_regs __iomem *regs = hcd->regs;

	dev_dbg(&pdev->dev, "stop\n");

	/*
	 * Put the USB host controller into reset.
	 */
	writel(0, &regs->control);

	/*
	 * Stop the USB clocks.
	 */
	at91_stop_clock();
}


/*-------------------------------------------------------------------------*/

static int usb_hcd_at91_remove (struct usb_hcd *, struct platform_device *);

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */


/**
 * usb_hcd_at91_probe - initialize AT91-based HCDs
 * Context: !in_interrupt()
 *
 * Allocates basic resources for this USB host controller, and
 * then invokes the start() method for the HCD associated with it
 * through the hotplug entry's driver_data.
 */
static int usb_hcd_at91_probe(const struct hc_driver *driver,
			struct platform_device *pdev)
{
	int retval;
	struct usb_hcd *hcd = NULL;

	if (pdev->num_resources != 2) {
		pr_debug("hcd probe: invalid num_resources");
		return -ENODEV;
	}

	if ((pdev->resource[0].flags != IORESOURCE_MEM)
			|| (pdev->resource[1].flags != IORESOURCE_IRQ)) {
		pr_debug("hcd probe: invalid resource type\n");
		return -ENODEV;
	}

	hcd = usb_create_hcd(driver, &pdev->dev, "at91");
	if (!hcd)
		return -ENOMEM;
	hcd->rsrc_start = pdev->resource[0].start;
	hcd->rsrc_len = pdev->resource[0].end - pdev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		pr_debug("request_mem_region failed\n");
		retval = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		pr_debug("ioremap failed\n");
		retval = -EIO;
		goto err2;
	}

	iclk = clk_get(&pdev->dev, "ohci_clk");
	fclk = clk_get(&pdev->dev, "uhpck");
	if (cpu_is_at91sam9261())
		hclk = clk_get(&pdev->dev, "hck0");

	at91_start_hc(pdev);
	ohci_hcd_init(hcd_to_ohci(hcd));

	retval = usb_add_hcd(hcd, pdev->resource[1].start, IRQF_DISABLED);
	if (retval == 0)
		return retval;

	/* Error handling */
	at91_stop_hc(pdev);

	if (cpu_is_at91sam9261())
		clk_put(hclk);
	clk_put(fclk);
	clk_put(iclk);

	iounmap(hcd->regs);

 err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);

 err1:
	usb_put_hcd(hcd);
	return retval;
}


/* may be called with controller, bus, and devices active */

/**
 * usb_hcd_at91_remove - shutdown processing for AT91-based HCDs
 * @dev: USB Host Controller being removed
 * Context: !in_interrupt()
 *
 * Reverses the effect of usb_hcd_at91_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thread
 * context, "rmmod" or something similar.
 *
 */
static int usb_hcd_at91_remove(struct usb_hcd *hcd,
				struct platform_device *pdev)
{
	usb_remove_hcd(hcd);
	at91_stop_hc(pdev);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);

	if (cpu_is_at91sam9261())
		clk_put(hclk);
	clk_put(fclk);
	clk_put(iclk);
	fclk = iclk = hclk = NULL;

	dev_set_drvdata(&pdev->dev, NULL);
	return 0;
}

/*-------------------------------------------------------------------------*/

static int __devinit
ohci_at91_start (struct usb_hcd *hcd)
{
	struct at91_usbh_data	*board = hcd->self.controller->platform_data;
	struct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	int			ret;

	if ((ret = ohci_init(ohci)) < 0)
		return ret;

	ohci->num_ports = board->ports;

	if ((ret = ohci_run(ohci)) < 0) {
		err("can't start %s", hcd->self.bus_name);
		ohci_stop(hcd);
		return ret;
	}
	return 0;
}

/*-------------------------------------------------------------------------*/

static const struct hc_driver ohci_at91_hc_driver = {
	.description =		hcd_name,
	.product_desc =		"AT91 OHCI",
	.hcd_priv_size =	sizeof(struct ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/*
	 * basic lifecycle operations
	 */
	.start =		ohci_at91_start,
	.stop =			ohci_stop,
	.shutdown =		ohci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoint_disable =	ohci_endpoint_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
	.hub_irq_enable =	ohci_rhsc_enable,
#ifdef CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#endif
	.start_port_reset =	ohci_start_port_reset,
};

/*-------------------------------------------------------------------------*/

static int ohci_hcd_at91_drv_probe(struct platform_device *pdev)
{
	device_init_wakeup(&pdev->dev, 1);
	return usb_hcd_at91_probe(&ohci_at91_hc_driver, pdev);
}

static int ohci_hcd_at91_drv_remove(struct platform_device *pdev)
{
	device_init_wakeup(&pdev->dev, 0);
	return usb_hcd_at91_remove(platform_get_drvdata(pdev), pdev);
}

#ifdef CONFIG_PM

static int
ohci_hcd_at91_drv_suspend(struct platform_device *pdev, pm_message_t mesg)
{
	struct usb_hcd	*hcd = platform_get_drvdata(pdev);
	struct ohci_hcd	*ohci = hcd_to_ohci(hcd);

	if (device_may_wakeup(&pdev->dev))
	{
		enable_irq_wake(hcd->irq);		// petworm off
	}

	/*
	 * The integrated transceivers seem unable to notice disconnect,
	 * reconnect, or wakeup without the 48 MHz clock active.  so for
	 * correctness, always discard connection state (using reset).
	 *
	 * REVISIT: some boards will be able to turn VBUS off...
	 */
	if (clk_must_disable(fclk)) {
		//ohci_usb_reset (ohci);
		at91_stop_clock();
	}

	return 0;
}

static int ohci_hcd_at91_drv_resume(struct platform_device *pdev)
{
	struct usb_hcd	*hcd = platform_get_drvdata(pdev);

	if (device_may_wakeup(&pdev->dev))
	{
		disable_irq_wake(hcd->irq);		// petworm off
	}

	if (!clocked)
		at91_start_clock();

	return 0;
}
#else
#define ohci_hcd_at91_drv_suspend NULL
#define ohci_hcd_at91_drv_resume  NULL
#endif

MODULE_ALIAS("at91_ohci");

static struct platform_driver ohci_hcd_at91_driver = {
	.probe		= ohci_hcd_at91_drv_probe,
	.remove		= ohci_hcd_at91_drv_remove,
	.shutdown	= usb_hcd_platform_shutdown,
	.suspend	= ohci_hcd_at91_drv_suspend,
	.resume		= ohci_hcd_at91_drv_resume,
	.driver		= {
		.name	= "at91_ohci",
		.owner	= THIS_MODULE,
	},
};

