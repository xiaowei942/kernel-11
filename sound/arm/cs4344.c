/*
 *
 * Atmel
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 */

#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/spi/spi.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/clk.h>
#include <linux/platform_device.h>

#include <sound/initval.h>
#include <sound/control.h>
#include <sound/driver.h>
#include <sound/core.h>
#include <sound/pcm.h>

#include <asm/io.h>
#include <asm/io.h>
#include <asm/processor.h>
#include <linux/atmel_pdc.h>
#include <asm/arch/board.h>

#include "at73c213.h"

//linux_yu
#if	0	 
	#define DBGYU(fmt, arg...)	printk(fmt, ##arg);
#else
	#define DBGYU(fmt, arg...)
#endif

/*-----------------------------------------------------------------------------
 *  AT73C213 SPI
 *-----------------------------------------------------------------------------*/
static struct spi_device *at73c213_spi_device;
static unsigned char at73c213_regs[0x11];
static unsigned char at73c213_spi_wbuffer[2];
static unsigned char at73c213_spi_rbuffer[2];

/*-----------------------------------------------------------------------------
 *  AT73C213 SPI write regs
 *-----------------------------------------------------------------------------*/
static int at73c213_write_reg(u8 reg, u8 val)
{
    struct spi_message msg;
    struct spi_transfer msg_xfer =
    {
        .len        = 2,
        .cs_change  = 0,
    };

	DBGYU("%s\n", __FUNCTION__);
//	msleep(1500);	//linux_yu
    spi_message_init(&msg);

    at73c213_spi_wbuffer[0] = reg;
    at73c213_spi_wbuffer[1] = val;

    msg_xfer.tx_buf = at73c213_spi_wbuffer;
    msg_xfer.rx_buf = at73c213_spi_rbuffer;
    spi_message_add_tail(&msg_xfer, &msg);

    at73c213_regs[reg] = val;

    return spi_sync(at73c213_spi_device, &msg);
}

/*-----------------------------------------------------------------------------
 *  AT73C213 SPI read regs
 *-----------------------------------------------------------------------------*/
static unsigned char at73c213_read_reg(unsigned char reg)
{
	
	DBGYU("%s\n", __FUNCTION__);
    return at73c213_regs[reg];
}

/*-----------------------------------------------------------------------------
 *  AT73C213 - Init
 *-----------------------------------------------------------------------------*/
static void at73c213_hw_init(void)
{
/*
	From AT73C213 datasheet
	Path DAC to headset output
	1. Write @0x10 => 0x03 (deassert the reset)
	2. Write @0x0C => 0xFF (precharge + master on)
	3. Write @0x00 => 0x30 (ONLNOL and ONLONOR set to 1)
	4. Delay 500 ms
	5. Write @0x0C => 0x01 (precharge off + master on)
	6. Delay 1ms
	7. Write @0x00 => 0x3C (ONLNOL, ONLNOR, ONDACR and ONDACL set to 1)
*/
	/* Make sure everything is off */
	at73c213_write_reg(DAC_CTRL, 0x00);
	DBGYU("%s\n", __FUNCTION__);

	msleep(500);

	/* de-reset the device */
    	at73c213_write_reg(DAC_RST, 0x03);

	/* Turn on precharge */
	at73c213_write_reg(DAC_PRECH, 0xFF);
	at73c213_write_reg(DAC_CTRL, 0x30);

    	/* Wait 500 ms*/
    	msleep(500);

	at73c213_write_reg(DAC_PRECH, 0x01);

	msleep(1);

	at73c213_write_reg(DAC_RLOG, 0x1f);
	at73c213_write_reg(DAC_LLOG, 0x1f);
//	msleep(1500);	//linux_yu
	at73c213_write_reg(DAC_CTRL, 0x3C);
//	msleep(1500);	//linux_yu
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_probe
 *----------------------------------------------------------------------------*/
static int __devinit at73c213_probe(struct spi_device *spi)
{
	int retval = 0;

	DBGYU("%s\n", __FUNCTION__);
	if(!spi)
		return -ENXIO;

	at73c213_spi_device = spi;

	return retval;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_remove
 *----------------------------------------------------------------------------*/
static int __devexit at73c213_remove(struct spi_device *spi)
{
	DBGYU("%s\n", __FUNCTION__);
	return 0;
}

#ifdef CONFIG_PM
/*-----------------------------------------------------------------------------
* snd_at73c213_suspend
*----------------------------------------------------------------------------*/
static int at73c213_suspend(struct spi_device *spi)
{
	DBGYU("%s\n", __FUNCTION__);
	return 0;
}

/*-----------------------------------------------------------------------------
* snd_at73c213_resume
*----------------------------------------------------------------------------*/
static int at73c213_resume(struct spi_device *spi)
{
	DBGYU("%s\n", __FUNCTION__);
	return 0;
}
#endif /* CONFIG_PM */

/*-----------------------------------------------------------------------------
 * AT73C213 Driver
 *----------------------------------------------------------------------------*/
static struct spi_driver at73c213_driver =
{
	.driver =
	{
		.name       = "at73c213",
		.bus        = &spi_bus_type,
		.owner      = THIS_MODULE,
	}
	,
		.probe      = at73c213_probe,
		.remove     = __devexit_p(at73c213_remove),
		/* TODO:  investigate suspend and resume... */
	#ifdef CONFIG_PM
		.resume     = at73c213_resume,
		.suspend    = at73c213_suspend,
	#endif
};

/********************************************************************************
*   Mixer
********************************************************************************/

/*-----------------------------------------------------------------------------
 *  Info functions
 *----------------------------------------------------------------------------*/
static int at73c213_info_pcm_volume(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info * uinfo)
{
	DBGYU("%s\n", __FUNCTION__);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.integer.min = 0x0;
	uinfo->value.integer.max = 0x1f;
	return 0;
}

/*-----------------------------------------------------------------------------
 *  Get functions
 *----------------------------------------------------------------------------*/
static int at73c213_get_pcm_volume(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value * ucontrol)
{
	DBGYU("%s\n", __FUNCTION__);
	ucontrol->value.integer.value[0] = (0x1f - at73c213_read_reg(DAC_LLOG)); /*left */
	ucontrol->value.integer.value[1] = (0x1f - at73c213_read_reg(DAC_RLOG)); /*right*/
	return 0;
}

/*-----------------------------------------------------------------------------
 *  Put functions
 *----------------------------------------------------------------------------*/
static int at73c213_put_pcm_volume(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value * ucontrol)
{
	DBGYU("%s\n", __FUNCTION__);
	at73c213_write_reg(DAC_LLOG,(0x1f - ucontrol->value.integer.value[0]));
	at73c213_write_reg(DAC_RLOG,(0x1f - ucontrol->value.integer.value[1]));
	return 0;
}

/*-----------------------------------------------------------------------------
 *  Controls
 *----------------------------------------------------------------------------*/
static struct snd_kcontrol_new snd_at73c213_controls[] =
{
	{
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name  = "PCM Playback Volume",
		.info  = at73c213_info_pcm_volume,
		.get   = at73c213_get_pcm_volume,
		.put   = at73c213_put_pcm_volume
	},
};

/*-----------------------------------------------------------------------------
 *  Controls
 *----------------------------------------------------------------------------*/
static int __devinit snd_chip_at73c213_mixer_new(struct snd_card *card)
{
	int idx, err;

	DBGYU("%s\n", __FUNCTION__);
	snd_assert(card != NULL, return -EINVAL);

	if(at73c213_spi_device == NULL) {
		printk(KERN_WARNING "No at73c231_spi_device found\n");
		return -EFAULT;
	}

	/*  Set Mixer IOCTL */
	for (idx = 0; idx < ARRAY_SIZE(snd_at73c213_controls); idx++) {
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_at73c213_controls[idx], NULL))) < 0)
			return err;
	}

	/* Init DAC Hardware */
	at73c213_hw_init();

	return 0;
}

/********************************************************************************
*   DSP
********************************************************************************/

/*-----------------------------------------------------------------------------
 * snd_at73c213_playback_hw
 *----------------------------------------------------------------------------*/
static struct snd_pcm_hardware snd_at73c213_playback_hw =
{
	.info    = (	SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER  ),
	.formats = SNDRV_PCM_FMTBIT_S16_LE,
        .rates =  SNDRV_PCM_RATE_CONTINUOUS,
        .rate_min =         48000,
        .rate_max =         48000,
    	.channels_min   = 2,
    	.channels_max   = 2,
    	.buffer_bytes_max = 64 * 1024 - 1,
    	.period_bytes_min = 1024,
    	.period_bytes_max = 64 * 1024 - 1,
    	.periods_min    = 4,
    	.periods_max    = 1024,
};

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_open - open callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	DBGYU("%s\n", __FUNCTION__);
	runtime->hw = snd_at73c213_playback_hw;
	chip->substream = substream;

	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_close - close callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	chip->substream = NULL;
	DBGYU("%s\n", __FUNCTION__);
	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_hw_params - hw_params callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_hw_params(struct snd_pcm_substream *substream,
                                      struct snd_pcm_hw_params *hw_params)
{
	DBGYU("%s\n", __FUNCTION__);
	return snd_pcm_lib_malloc_pages(substream,
                                    params_buffer_bytes(hw_params));
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_hw_free - hw_free callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_hw_free(struct snd_pcm_substream *substream)
{
	DBGYU("%s\n", __FUNCTION__);
    return snd_pcm_lib_free_pages(substream);
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_prepare - prepare callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	struct platform_device *pdev = chip->pdev;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int block_size;

	DBGYU("%s\n", __FUNCTION__);
	block_size = frames_to_bytes(runtime, runtime->period_size);

	chip->period = 0;

	/* Make sure that our data are actually readable by the SSC */
	dma_sync_single_for_device(&pdev->dev, runtime->dma_addr,
			block_size, DMA_TO_DEVICE);
	dma_sync_single_for_device(&pdev->dev, runtime->dma_addr + block_size,
			block_size, DMA_TO_DEVICE);

	writel(runtime->dma_addr, chip->ssc_regs + PDC_TPR);
	writel(runtime->period_size * 2, chip->ssc_regs + PDC_TCR);
	writel(runtime->dma_addr + block_size, chip->ssc_regs + PDC_TNPR);
	writel(runtime->period_size * 2, chip->ssc_regs + PDC_TNCR);

	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_trigger - trigger callback
 *----------------------------------------------------------------------------*/
static int snd_at73c213_pcm_trigger(struct snd_pcm_substream *substream,
                                    int cmd)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	int retval = 0;
	unsigned long flags = 0;

	DBGYU("%s\n", __FUNCTION__);
	spin_lock_irqsave(&chip->lock, flags);

	switch (cmd)
	{
		case SNDRV_PCM_TRIGGER_START:
			writel(SSC_INT_ENDTX, chip->ssc_regs + SSC_IER);
			writel(PDC_PTCR_TXTEN, chip->ssc_regs + PDC_PTCR);
			break;
		case SNDRV_PCM_TRIGGER_STOP:
			writel(PDC_PTCR_TXTDIS, chip->ssc_regs + PDC_PTCR);
			writel(SSC_INT_ENDTX, chip->ssc_regs + SSC_IDR);
			break;
		default:
			printk(KERN_WARNING "at73c213: spurious command %x\n", cmd);
			retval = -EINVAL;
			break;
	}

	spin_unlock_irqrestore(&chip->lock, flags);

	return retval;
}

/*-----------------------------------------------------------------------------
 * snd_pcm_uframes - pointer callback
 *----------------------------------------------------------------------------*/
static snd_pcm_uframes_t snd_at73c213_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t pos;
	unsigned long bytes;

	DBGYU("%s\n", __FUNCTION__);
	bytes = readl(chip->ssc_regs + PDC_TPR) - runtime->dma_addr;

	pos = bytes_to_frames(runtime, bytes);
	if (pos >= runtime->buffer_size)
		pos -= runtime->buffer_size;

	return pos;
}

/*-----------------------------------------------------------------------------
 * operators
 *----------------------------------------------------------------------------*/
static struct snd_pcm_ops at73c213_playback_ops =
{
	.open       = snd_at73c213_pcm_open,
	.close      = snd_at73c213_pcm_close,
	.ioctl      = snd_pcm_lib_ioctl,
	.hw_params  = snd_at73c213_pcm_hw_params,
	.hw_free    = snd_at73c213_pcm_hw_free,
	.prepare    = snd_at73c213_pcm_prepare,
	.trigger    = snd_at73c213_pcm_trigger,
	.pointer    = snd_at73c213_pcm_pointer,
};

/*-----------------------------------------------------------------------------
 * snd_at73c213_pcm_free free a pcm device
 *----------------------------------------------------------------------------*/
static void snd_at73c213_pcm_free(struct snd_pcm *pcm)
{
	struct snd_at73c213 *chip = snd_pcm_chip(pcm);

	DBGYU("%s\n", __FUNCTION__);
	if (chip->pcm != 0 )
	{
		snd_pcm_lib_preallocate_free_for_all(chip->pcm);
		chip->pcm = NULL;
	}
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_new_pcm create a new pcm device
 *----------------------------------------------------------------------------*/
static int __devinit snd_at73c213_new_pcm(struct snd_card * card)
{
	struct snd_pcm *pcm;
	struct snd_at73c213 * chip = card->private_data;
	int err;

	DBGYU("%s\n", __FUNCTION__);
	msleep(1500);	//linux_yu
	err = snd_pcm_new(chip->card, "AT73C213", 0, 1, 0, &pcm);
	if (err)
		return err;

	pcm->private_data = chip;
	pcm->private_free = snd_at73c213_pcm_free;
	pcm->info_flags = SNDRV_PCM_INFO_BLOCK_TRANSFER;
	pcm->private_data = chip;
	strcpy( pcm->name, "AT73C213" );
	chip->pcm = pcm;

	/* set operators */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &at73c213_playback_ops);

	/* pre-allocation of buffers */
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV, NULL, 64 * 1024, 64 * 1024);

	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_interrupt
 *---------------------------------------------------------------------------*/
static irqreturn_t snd_at73c213_interrupt(int irq, void *dev_id)
{
	struct snd_at73c213 *chip = dev_id;
	struct platform_device *pdev = chip->pdev;
	struct snd_pcm_runtime *runtime = chip->substream->runtime;
	u32 status;
	int offset, next_period, block_size;

	DBGYU("%s\n", __FUNCTION__);
	spin_lock(&chip->lock);

	block_size = frames_to_bytes(runtime, runtime->period_size);

	status = readl(chip->ssc_regs + SSC_IMR);

	if (status & SSC_INT_ENDTX)
	{
		chip->period++;
		if (chip->period == runtime->periods)
			chip->period = 0;
		next_period = chip->period + 1;
		if (next_period == runtime->periods)
			next_period = 0;

		offset = block_size * next_period;

		/* Make sure that our data are actually readable by the SSC */
		dma_sync_single_for_device(&pdev->dev, runtime->dma_addr + offset,
				block_size, DMA_TO_DEVICE);
		writel(runtime->dma_addr + offset, chip->ssc_regs + PDC_TNPR);
		writel(runtime->period_size * 2, chip->ssc_regs + PDC_TNCR);

		if (next_period == 0)
		{
			(void)readl(chip->ssc_regs + PDC_TPR);
			(void)readl(chip->ssc_regs + PDC_TCR);
		}
	}
	else
	{
		printk(KERN_WARNING
				"Spurious SSC interrupt, status = 0x%08lx\n",
				(unsigned long)status);
		writel(status, chip->ssc_regs + SSC_IDR);
	}

	(void)readl(chip->ssc_regs + SSC_IMR);
	spin_unlock(&chip->lock);

	if (status & SSC_INT_ENDTX)
		snd_pcm_period_elapsed(chip->substream);

	return IRQ_HANDLED;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_chip_init
 *----------------------------------------------------------------------------*/
static int snd_at73c213_chip_init(struct snd_at73c213 *chip)
{
	DBGYU("%s\n", __FUNCTION__);
	
//	msleep(1500);	//linux_yu
	/* Reset the SSC */
	writel(SSC_CR_SWRST, chip->ssc_regs + SSC_CR);

	/* Enable SSC and setup for I2S */
	writel(chip->ssc_div, chip->ssc_regs + SSC_CMR);

	/* CKO, START, STTDLY, PERIOD */
	writel((1<<2)|(4<<8)|(1<<16)|(15<<24), chip->ssc_regs + SSC_TCMR);

	/* DATLEN, MSBF, DATNB, FSLEN, FSOS */
	writel((15<<0)|(1<<7)|(1<<8)|(15<<16)|(1<<20), chip->ssc_regs + SSC_TFMR);

	/* Enable SSC RX */
	writel(SSC_CR_TXEN, chip->ssc_regs + SSC_CR);
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_probe
 *----------------------------------------------------------------------------*/
static int __devinit snd_at73c213_probe(struct platform_device *pdev)
{
	struct atmel_at73c213_data *pdata = pdev->dev.platform_data;
	struct snd_at73c213 *chip;
	struct snd_card          *card;
	int irq, ret;
	struct resource *res;

	DBGYU("%s\n", __FUNCTION__);
	/* register the soundcard */
	card = snd_card_new(SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1, THIS_MODULE, sizeof(struct snd_at73c213));
	if (card == NULL){
		return -ENOMEM;
	}

	chip = card->private_data;
	chip->ssc_div = pdata->ssc_div;
	chip->at73_mck = pdata->at73_mck;
	spin_lock_init(&chip->lock);
	chip->card = card;
	strcpy( card->driver, "AT73C213" );
	strcpy( card->shortname, "AT73C213" );
	strcpy( card->longname, "AT73C213" );

	if (!pdev)
		return -ENXIO;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENXIO;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	chip->irq = irq;

	/* Request mem region */
	if (!request_mem_region(res->start, res->end - res->start + 1, pdev->name))
		return -EBUSY;

	/* Remap SSC register */
	chip->ssc_regs = ioremap(res->start, res->end - res->start + 1);
	if (!chip->ssc_regs)
		return -ENOMEM;

	snd_chip_at73c213_mixer_new(card);

	snd_at73c213_new_pcm(card);

	ret = request_irq(chip->irq, snd_at73c213_interrupt, 0, "AT73C213", chip);
	if (ret)
		return ret;
	snd_at73c213_chip_init(chip);

	ret = snd_card_register(card);
	if(ret)
		return ret;

	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_remove
 *----------------------------------------------------------------------------*/
static int __devexit snd_at73c213_remove(struct platform_device *pdev)
{
	DBGYU("%s\n", __FUNCTION__);
	return 0;
}

/*-----------------------------------------------------------------------------
 * snd_at73c213_driver
 *----------------------------------------------------------------------------*/
static struct platform_driver snd_at73c213_driver =
{
	.probe      = snd_at73c213_probe,
	.remove     = __devexit_p(snd_at73c213_remove),
	.driver     =
	{
		.name       = "atmel_ssc_at73c213",
	}
	,
};

static int __init snd_at73c213_init(void)
{
	int ret;

	DBGYU("%s\n", __FUNCTION__);
	ret = spi_register_driver(&at73c213_driver);
	if(ret)
		return ret;

	ret = platform_driver_register(&snd_at73c213_driver);
	if(ret)
	{
		spi_unregister_driver(&at73c213_driver);
		return ret;
	}

	return 0;
}

static void __exit snd_at73c213_exit(void)
{
	DBGYU("%s\n", __FUNCTION__);
	platform_driver_unregister(&snd_at73c213_driver);
	spi_unregister_driver(&at73c213_driver);
}

/********************************************************************************
*   Module
********************************************************************************/
MODULE_AUTHOR("Atmel");
MODULE_DESCRIPTION("at73c213 snd driver");
MODULE_LICENSE("GPL");

module_init(snd_at73c213_init);
module_exit(snd_at73c213_exit);
