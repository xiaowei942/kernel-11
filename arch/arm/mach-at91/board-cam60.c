/*
 * KwikByte CAM60
 *
 * based on board-sam9260ek.c
 *   Copyright (C) 2005 SAN People
 *   Copyright (C) 2006 Atmel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/types.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>

#include <asm/hardware.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/irq.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <asm/arch/board.h>
#include <asm/arch/gpio.h>

#include "generic.h"


/*
 * Serial port configuration.
 *    0 .. 5 = USART0 .. USART5
 *    6      = DBGU
 */
static struct at91_uart_config __initdata cam60_uart_config = {
	.console_tty	= 0,				/* ttyS0 */
	.nr_tty		= 1,
	.tty_map	= { 6, -1, -1, -1, -1, -1, -1 }	/* ttyS0, ..., ttyS6 */
};

static void __init cam60_map_io(void)
{
	/* Initialize processor: 10 MHz crystal */
	at91sam9260_initialize(10000000);

	/* Setup the serial ports and console */
	at91_init_serial(&cam60_uart_config);
}

static void __init cam60_init_irq(void)
{
	at91sam9260_init_interrupts(NULL);
}


/*
 * USB Host
 */
static struct at91_usbh_data __initdata cam60_usbh_data = {
	.ports		= 1,
};


/*
 * SPI devices.
 */
#if defined(CONFIG_MTD_DATAFLASH)
static struct mtd_partition __initdata cam60_spi_partitions[] = {
	{
		.name	= "BOOT1",
		.offset	= 0,
		.size	= 4 * 1056,
	},
	{
		.name	= "BOOT2",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= 256 * 1056,
	},
	{
		.name	= "kernel",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= 2222 * 1056,
	},
	{
		.name	= "file system",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= MTDPART_SIZ_FULL,
	},
};

static struct flash_platform_data __initdata cam60_spi_flash_platform_data = {
	.name		= "spi_flash",
	.parts		= cam60_spi_partitions,
	.nr_parts	= ARRAY_SIZE(cam60_spi_partitions)
};
#endif

static struct spi_board_info cam60_spi_devices[] = {
#if defined(CONFIG_MTD_DATAFLASH)
	{	/* DataFlash chip */
		.modalias	= "mtd_dataflash",
		.chip_select	= 0,
		.max_speed_hz	= 15 * 1000 * 1000,
		.bus_num	= 0,
		.platform_data	= &cam60_spi_flash_platform_data
	},
#endif
};


/*
 * MACB Ethernet device
 */
static struct __initdata at91_eth_data cam60_macb_data = {
	.phy_irq_pin	= AT91_PIN_PB5,
	.is_rmii	= 0,
};


/*
 * NAND Flash
 */
static struct mtd_partition __initdata cam60_nand_partition[] = {
	{
		.name	= "nand_fs",
		.offset	= 0,
		.size	= MTDPART_SIZ_FULL,
	},
};

static struct mtd_partition * __init nand_partitions(int size, int *num_partitions)
{
	*num_partitions = ARRAY_SIZE(cam60_nand_partition);
	return cam60_nand_partition;
}

static struct at91_nand_data __initdata cam60_nand_data = {
	.ale		= 21,
	.cle		= 22,
	// .det_pin	= ... not there
	.rdy_pin	= AT91_PIN_PA9,
	.enable_pin	= AT91_PIN_PA7,
	.partition_info	= nand_partitions,
};


static void __init cam60_board_init(void)
{
	/* Serial */
	at91_add_device_serial();
	/* SPI */
	at91_add_device_spi(cam60_spi_devices, ARRAY_SIZE(cam60_spi_devices));
	/* Ethernet */
	at91_add_device_eth(&cam60_macb_data);
	/* USB Host */
	/* enable USB power supply circuit */
	at91_set_gpio_output(AT91_PIN_PB18, 1);
	at91_add_device_usbh(&cam60_usbh_data);
	/* NAND */
	at91_add_device_nand(&cam60_nand_data);
}

MACHINE_START(CAM60, "KwikByte CAM60")
	/* Maintainer: KwikByte */
	.phys_io	= AT91_BASE_SYS,
	.io_pg_offst	= (AT91_VA_BASE_SYS >> 18) & 0xfffc,
	.boot_params	= AT91_SDRAM_BASE + 0x100,
	.timer		= &at91sam926x_timer,
	.map_io		= cam60_map_io,
	.init_irq	= cam60_init_irq,
	.init_machine	= cam60_board_init,
MACHINE_END
