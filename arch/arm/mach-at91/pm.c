/*
 * arch/arm/mach-at91/pm.c
 * AT91 Power Management
 *
 * Copyright (C) 2005 David Brownell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/suspend.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/atomic.h>
#include <asm/mach/time.h>
#include <asm/mach/irq.h>
#include <asm/mach-types.h>

//#include <asm/arch/at91_pmc.h>
#include <asm/arch/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/at91_pmc.h>
#include <linux/delay.h>

#include "generic.h"


#ifdef CONFIG_ARCH_AT91RM9200
#include <asm/arch/at91rm9200_mc.h>


static inline void sdram_selfrefresh_enable(void)
{
	at91_sys_write(AT91_SDRAMC_SRR, 1);
	/* effective on the next instruction */
}

static inline void sdram_selfrefresh_disable(void)
{
	/* automatically disabled by CPU or DMA access */
}

#elif defined(CONFIG_ARCH_AT91CAP9)
#include <asm/arch/at91cap9_ddrsdr.h>

static u32 saved_lpr;

static inline void sdram_selfrefresh_enable(void)
{
	u32 lpr;

	saved_lpr = at91_sys_read(AT91_DDRSDRC_LPR);

	lpr = saved_lpr & ~AT91_DDRSDRC_LPCB;
	at91_sys_write(AT91_DDRSDRC_LPR, lpr | AT91_DDRSDRC_LPCB_SELF_REFRESH);
}

#define sdram_selfrefresh_disable()	at91_sys_write(AT91_DDRSDRC_LPR, saved_lpr)

#else
#include <asm/arch/at91sam926x_sdramc.h>
#include <asm/arch/at91_shdwc.h>

#ifdef CONFIG_ARCH_AT91SAM9263
/*
 * FIXME the EB1 SDRAM controller might be in use too ... until system
 * headers change so we can use offsets from a controller base address,
 * act as if there's only one controller.
 */
#define	AT91_SDRAMC	AT91_SDRAMC0
#warning Assuming EB1 SDRAM controller is *NOT* used
#endif

static inline void sdram_selfrefresh_enable(void)
{
	/* set sdram selfrefresh & close PCK */
	at91_sys_write(AT91_SDRAMC_LPR, AT91_SDRAMC_LPCB_SELF_REFRESH);
	at91_sys_write (AT91_PMC_SCDR, 0x1);
}

static inline void sdram_selfrefresh_disable(void)
{
	at91_sys_write(AT91_SDRAMC_LPR, AT91_SDRAMC_LPCB_DISABLE);
}

#endif


#if defined(AT91_SHDWC)

#include <asm/arch/at91_rstc.h>
#include <asm/arch/at91_shdwc.h>

/*
 * Show the reason for the previous system reset.
 */
static void __init show_reset_status(void)
{
#if 0
	static char reset[] __initdata = "reset";

	static char general[] __initdata = "general";
	static char wakeup[] __initdata = "wakeup";
	static char watchdog[] __initdata = "watchdog";
	static char software[] __initdata = "software";
	static char user[] __initdata = "user";
	static char unknown[] __initdata = "unknown";

	static char signal[] __initdata = "signal";
	static char rtc[] __initdata = "rtc";
	static char rtt[] __initdata = "rtt";
	static char restore[] __initdata = "power-restored";

	char *reason, *r2 = reset;
	u32 reset_type, wake_type;

	reset_type = at91_sys_read(AT91_RSTC_SR) & AT91_RSTC_RSTTYP;
	wake_type = at91_sys_read(AT91_SHDW_SR);

	switch (reset_type) {
	case AT91_RSTC_RSTTYP_GENERAL:
		reason = general;
		break;
	case AT91_RSTC_RSTTYP_WAKEUP:
		/* board-specific code enabled the wakeup sources */
		reason = wakeup;

		/* "wakeup signal" */
		if (wake_type & AT91_SHDW_WAKEUP0)
			r2 = signal;
		else {
			r2 = reason;
			if (wake_type & AT91_SHDW_RTTWK)	/* rtt wakeup */
				reason = rtt;
			else if (wake_type & AT91_SHDW_RTCWK)	/* rtc wakeup */
				reason = rtc;
			else if (wake_type == 0)	/* power-restored wakeup */
				reason = restore;
			else				/* unknown wakeup */
				reason = unknown;
		}
		break;
	case AT91_RSTC_RSTTYP_WATCHDOG:
		reason = watchdog;
		break;
	case AT91_RSTC_RSTTYP_SOFTWARE:
		reason = software;
		break;
	case AT91_RSTC_RSTTYP_USER:
		reason = user;
		break;
	default:
		reason = unknown;
		break;
	}
	pr_info("AT91: Starting after %s %s\n", reason, r2);
#endif
}
#else
static void __init show_reset_status(void) {}
#endif

#ifdef CONFIG_AT91_SLOW_CLOCK
extern void at91_slow_clock(void);
extern u32 at91_slow_clock_sz;
#endif

static int at91_pm_valid_state(suspend_state_t state)
{
	//printk (KERN_ALERT "petworm: at91_pm_valid_state.\n");

	switch (state) {
	case PM_SUSPEND_ON:
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		return 1;
	default:
		return 0;
	}
}


static suspend_state_t target_state;
int cpu_need_stop = 0;

void at91_set_cpu_stop (int val)
{
	cpu_need_stop = val;
}
EXPORT_SYMBOL(at91_set_cpu_stop);
/*
 * Called after processes are frozen, but before we shutdown devices.
 */
static int at91_pm_set_target(suspend_state_t state)
{
	//printk (KERN_ALERT "petworm: at91_pm_set_target.\n");
	target_state = state;

	return 0;
}

/*
 * Verify that all the clocks are correct before entering
 * slow-clock mode.
 */
#warning "This should probably be moved to clocks.c"
static int at91_pm_verify_clocks(void)
{
	unsigned long scsr;
	int i;

	scsr = at91_sys_read(AT91_PMC_SCSR);

	/* USB must not be using PLLB */
	if (cpu_is_at91rm9200()) {
		if ((scsr & (AT91RM9200_PMC_UHP | AT91RM9200_PMC_UDP)) != 0) {
			pr_debug("AT91: PM - Suspend-to-RAM with USB still active\n");
			return 0;
		}
	} else if (cpu_is_at91sam9260() || cpu_is_at91sam9261() || cpu_is_at91sam9263()) {
		if ((scsr & (AT91SAM926x_PMC_UHP | AT91SAM926x_PMC_UDP)) != 0) {
			pr_debug("AT91: PM - Suspend-to-RAM with USB still active\n");
			return 0;
		}
	} else if (cpu_is_at91cap9()) {
		if ((scsr & AT91CAP9_PMC_UHP) != 0) {
			pr_debug("AT91: PM - Suspend-to-RAM with USB still active\n");
			return 0;
		}
	}

#ifdef CONFIG_AT91_PROGRAMMABLE_CLOCKS
	/* PCK0..PCK3 must be disabled, or configured to use clk32k */
	for (i = 0; i < 4; i++) {
		u32 css;

		if ((scsr & (AT91_PMC_PCK0 << i)) == 0)
			continue;

		css = at91_sys_read(AT91_PMC_PCKR(i)) & AT91_PMC_CSS;
		if (css != AT91_PMC_CSS_SLOW) {
			pr_debug("AT91: PM - Suspend-to-RAM with PCK%d src %d\n", i, css);
			return 0;
		}
	}
#endif

	return 1;
}

/*
 * This is called from clk_must_disable(), to see how deeply to suspend.
 * For example, some controllers (like OHCI) need one of the PLL clocks
 * in order to act as a wakeup source, and those are not available when
 * going into slow clock mode.
 */
int at91_suspend_entering_slow_clock(void)
{
	return (target_state == PM_SUSPEND_MEM);
}
EXPORT_SYMBOL(at91_suspend_entering_slow_clock);

int at91_suspend_stop_cpu(void)
{
	return cpu_need_stop;
}
EXPORT_SYMBOL(at91_suspend_stop_cpu);

static void (*slow_clock)(void);


static int at91_pm_enter(suspend_state_t state)
{
	at91_gpio_suspend();
	at91_irq_suspend();

	pr_debug("AT91: PM - wake mask %08x, pm state %d\n",
			/* remember all the always-wake irqs */
			(at91_sys_read(AT91_PMC_PCSR)
					| (1 << AT91_ID_FIQ)
					| (1 << AT91_ID_SYS)
					| (at91_extern_irq))
				& at91_sys_read(AT91_AIC_IMR),
			state);

	switch (state) {
		/*
		 * Suspend-to-RAM is like STANDBY plus slow clock mode, so
		 * drivers must suspend more deeply:  only the master clock
		 * controller may be using the main oscillator.
		 */
		case PM_SUSPEND_MEM:
			//at91_sys_write (AT91_AIC_IDCR, 0x1 << 31);
			//at91_set_gpio_input (AT91_PIN_PB29, 1);
			printk (KERN_ALERT "petworm: idle irq is %x.\n", at91_sys_read (AT91_AIC_IMR));
			/*
			 * Ensure that clocks are in a valid state.
			 */
			if (!at91_pm_verify_clocks())
			{
				//at91_set_B_periph (AT91_PIN_PB29, 1);
				//at91_sys_write (AT91_AIC_IECR, 0x1 << 31);
				goto error;
			}

			//printk (KERN_ALERT "petworm: after verify clock.\n");
			/*
			 * Enter slow clock mode by switching over to clk32k and
			 * turning off the main oscillator; reverse on wakeup.
			 */
			if (slow_clock) {
				slow_clock();
				//at91_set_B_periph (AT91_PIN_PB29, 1);
				//at91_sys_write (AT91_AIC_IECR, 0x1 << 31);
				break;
			} else {
				/* DEVELOPMENT ONLY */
				pr_info("AT91: PM - no slow clock mode yet ...\n");
				/* FALLTHROUGH leaving master clock alone */
			}

		/*
		 * STANDBY mode has *all* drivers suspended; ignores irqs not
		 * marked as 'wakeup' event sources; and reduces DRAM power.
		 * But otherwise it's identical to PM_SUSPEND_ON:  cpu idle, and
		 * nothing fancy done with main or cpu clocks.
		 */
		case PM_SUSPEND_STANDBY:
			/*
			 * NOTE: the Wait-for-Interrupt instruction needs to be
			 * in icache so no SDRAM accesses are needed until the
			 * wakeup IRQ occurs and self-refresh is terminated.
			 */
			asm("b 1f; .align 5; 1:");
			/* drain write buffer */
			asm("mcr p15, 0, r0, c7, c10, 4");
			sdram_selfrefresh_enable();
			/* fall though to next state */

		case PM_SUSPEND_ON:
			/* wait for interrupt */
			asm("mcr p15, 0, r0, c7, c0, 4");

			sdram_selfrefresh_disable();
			break;

		default:
			pr_debug("AT91: PM - bogus suspend state %d\n", state);
			goto error;
	}

	pr_debug("AT91: PM - wakeup %08x\n",
			at91_sys_read(AT91_AIC_IPR) & at91_sys_read(AT91_AIC_IMR));
	//petworm add
//	printk (KERN_ALERT "AT91: PM - wakeup %08x\n",
//			at91_sys_read(AT91_AIC_IPR) & at91_sys_read(AT91_AIC_IMR));

error:
	target_state = PM_SUSPEND_ON;
	at91_irq_resume();
	at91_gpio_resume();
	return 0;
}


static struct platform_suspend_ops at91_pm_ops ={
	.valid		= at91_pm_valid_state,
	.set_target	= at91_pm_set_target,
	.enter		= at91_pm_enter,
};


static int __init at91_pm_init(void)
{
	printk("AT91: Power Management\n");

#ifdef CONFIG_AT91_SLOW_CLOCK
	/* REVISIT allocations of SRAM should be dynamically managed.
	 * FIQ handlers and other components will want SRAM/TCM too...
	 */
	slow_clock = (void *) (AT91_IO_VIRT_BASE - at91_slow_clock_sz);
	memcpy(slow_clock, at91_slow_clock, at91_slow_clock_sz);
#endif

#ifdef CONFIG_ARCH_AT91RM9200
	/* AT91RM9200 SDRAM low-power mode cannot be used with self-refresh. */
	at91_sys_write(AT91_SDRAMC_LPR, 0);
#endif

	suspend_set_ops(&at91_pm_ops);

	show_reset_status();

	// Santiage add 20090407: SDRAM self-flush open
	//at91_sys_write(AT91_SDRAMC_LPR, AT91_SDRAMC_LPCB_SELF_REFRESH);

	return 0;
}
arch_initcall(at91_pm_init);

