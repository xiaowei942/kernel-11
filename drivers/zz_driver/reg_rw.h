/*
 *
 * before use the head file, add the "#include <zz/reg_rw.h>" in your code. 
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


#ifndef at91_reg_rw
#define at91_reg_rw

#include <asm/hardware.h>
#include <asm/io.h>



#define AT91Z_UDP_BASE		0xfffa4000
#define AT91Z_MCI_BASE		0xfffa8000
#define AT91Z_TWI_BASE		0xfffac000
#define AT91Z_USART0_BASE	0xfffb0000
#define AT91Z_USART1_BASE	0xfffb4000
#define AT91Z_USART2_BASE	0xfffb8000
#define AT91Z_SSC0_BASE		0xfffbc000
#define AT91Z_SSC1_BASE		0xfffc0000
#define AT91Z_SSC2_BASE		0xfffc4000
#define AT91Z_SPI0_BASE		0xfffc8000
#define AT91Z_SPI1_BASE		0xfffcc000

#define AT91Z_SDRAMC_BASE	0xffffea00
#define AT91Z_SMC_BASE		0xffffec00
#define AT91Z_MATRIX_BASE	0xffffee00
#define AT91Z_AIC_BASE		0xfffff000
#define AT91Z_DBGU_BASE		0xfffff200
#define AT91Z_PIOA_BASE		0xfffff400
#define AT91Z_PIOB_BASE		0xfffff600
#define AT91Z_PIOC_BASE		0xfffff800
#define AT91Z_PMC_BASE		0xfffffc00

#define AT91Z_RSTC_BASE		0xfffffd00
#define AT91Z_SHDWC_BASE	0xfffffd10
#define AT91Z_RTT_BASE		0xfffffd20
#define AT91Z_PIT_BASE		0xfffffd30
#define AT91Z_WDT_BASE		0xfffffd40
#define AT91Z_GPBR_BASE		0xfffffd50


/********************************************
 *
 * PIO register number and name
 *
 *******************************************/

#define PIO_PER		0x00
#define PIO_PDR		0x04
#define PIO_PSR		0x08

#define PIO_OER		0x10
#define PIO_ODR		0x14
#define PIO_OSR		0x18

#define PIO_IFER	0x20
#define PIO_IFDR	0x24
#define PIO_IFSR	0x28

#define PIO_SODR	0x30
#define PIO_CODR	0x34
#define PIO_ODSR	0x38
#define PIO_PDSR	0x3C
#define PIO_IER		0x40
#define PIO_IDR		0x44
#define PIO_IMR		0x48
#define PIO_ISR		0x4C
#define PIO_MDER	0x50
#define PIO_MDDR	0x54
#define PIO_MDSR	0x58

#define PIO_PUDR	0x60
#define PIO_PUER	0x64
#define PIO_PUSR	0x68
#define PIO_ASR		0x70
#define PIO_BSR		0x74
#define PIO_ABSR	0x78

#define PIO_OWER	0xA0
#define PIO_OWDR	0xA4
#define PIO_OWSR	0xA8


#define at91_reg_read(reg)		__raw_readl(reg)
#define at91_reg_write(reg, val)	__raw_writel((val), reg)



/**********************************************************
 *
 * PIO read/write base operation
 *
 *********************************************************/

#define at91_pioa_read(reg)		__raw_readl(pioa_base + (reg))
#define at91_pioa_write(reg, val)	__raw_writel((val), pioa_base + (reg))

#define at91_piob_read(reg)             __raw_readl(piob_base + (reg))
#define at91_piob_write(reg, val)       __raw_writel((val), piob_base + (reg))

#define at91_pioc_read(reg)		__raw_readl(pioc_base + (reg))
#define at91_pioc_write(reg, val)	__raw_writel((val), pioc_base + (reg))

/**********************************************************
 *
 * PIO read/write operation function
 *
 *********************************************************/

/* config the pio A or B peripheral */
inline void
at91_pio_cfg_periph (unsigned int pio, 
		     unsigned int enable_A,
		     unsigned int enable_B)
{
	at91_reg_write (pio + PIO_ASR, enable_A);
	at91_reg_write (pio + PIO_BSR, enable_B);
	at91_reg_write (pio + PIO_PDR, enable_A | enable_B);
}

/* config the pio bit in output status */
inline void
at91_pio_config_output (unsigned int pio, unsigned int bitEnable)
{
	at91_reg_write (pio + PIO_PER, bitEnable);
	at91_reg_write (pio + PIO_OER, bitEnable);
}

inline void
at91_pio_set_output (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_SODR, flag);
}

inline void
at91_pio_clear_output (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_CODR, flag);
}

/*
inline void
at91_pio_force_output (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_ODSR, flag);
}

inline void
at91_pio_output_enable (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_OER, flag);
}

inline void
at91_pio_output_disable (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_PDR, flag);
}

inline unsigned int
at91_pio_get_output_status (unsigned int pio, unsigned int flag)
{
	return at91_reg_read (pio + PIO_OSR);
}

inline unsigned int
at91_pio_enable (unsigned int pio, unsigned int flag)
{
	return (at91_pio_get_output_status (pio) & flag);
}

inline unsigned int
at91_pio_get_outputdata_status (unsigned int pio)
{
	return at91_reg_read (pio + PIO_ODSR);
}




inline void
at91_pio_config_input (unsigned int pio, unsigned int bitEnable)
{
	at91_reg_write (pio + PIO_ODR, bitEnable);
	at91_reg_write (pio + PIO_PER, bitEnable);
}

inline void
at91_pio_cfg_opendrain (unsigned int pio, unsigned int multiDrvEnable)
{
	at91_reg_write (pio + PIO_MDDR, ~multiDrvEnable);
	at91_reg_write (pio + PIO_MDER, multiDrvEnable);
}

inline void
at91_pio_cfg_pullup (unsigned int pio, unsigned int pullup_enable)
{
	at91_reg_write (pio + PIO_PUDR, ~pullup_enable);
	at91_reg_write (pio + PIO_PUER, pullup_enable);
}

inline void
at91_pio_cfg_directDrive (unsigned int pio, unsigned int directDrive)
{
	at91_reg_write (pio + PIO_OWDR, ~directDrive);
	at91_reg_write (pio + PIO_OWER, directDrive);
}

inline void
at91_pio_cfg_inputFilter (unsigned int pio, unsigned int inputFilter)
{
	at91_reg_write (pio + PIO_IFDR, ~directDrive);
	at91_reg_write (pio + PIO_IFER, directDrive);
}

inline unsigned int
at91_pio_cfg_getInput (unsigned int pio)
{
	return at91_reg_read (pio + PIO_PDSR);
}

inline unsigned int
at91_pio_Is_inputSet( unsigned int pio, unsigned int flag)
{
	return (at91_pio_cfg_getInput(pio) & flag);
}


inline void
at91_pio_enable (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_PER, flag);
}

inline void
at91_pio_disable (unsigned int pio, unsigned int flag)
{
	at91_reg_write (pio + PIO_PDR, flag);
}

inline unsigned int
at91_pio_get_status (unsigned int pio)
{
	at91_reg_read (pio + PIO_PSR);
}

*/
#endif
