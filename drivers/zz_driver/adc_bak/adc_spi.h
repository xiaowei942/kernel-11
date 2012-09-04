//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : main.h
//* Object              : 
//*
//* 1.0 27/03/03 HIi    : Creation
//*----------------------------------------------------------------------------

#ifndef adc_h
#define adc_h

#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>	/* for put_user */
#include <asm/io.h>



#define DELAY 100000
#define AT91_SPI_NPCS_MASTER (0xD0001)
#define AT91_SPI_RESTART (0x1 <<7)
#define AT91_SPI_ENABLE (0x1)
#define ADC_DLYS (0xFF<<16)
#define ADC_3US (0xC0<<16)
#define AT91_CKGR_PLLBR (*(volatile unsigned int *)(0xFFFFFC2C)) 
#define AT91_PMC_MCKR (*(volatile unsigned int *)(0xFFFFFC30))

#define MCR	(*(unsigned *) 0xFFFFFC30)
#define MCF	(*(unsigned *) 0xFFFFFC24)
#define MO	(*(unsigned *) 0xFFFFFC20)

#define PMC_IER	(*(unsigned *) 0xFFFFFC60)
#define PMC_SR	(*(unsigned *) 0xFFFFFC68)

#define PPCK	(*(unsigned *) 0xFFFFFC18)
#define SPI_RCR	(*(unsigned *) 0xFFFC8104)

#define AT91C_BASE_PMC 			(0xFFFFFC00)
#define AT91A_PMC_PCER 			(0xFFFFFC10)
#define AT91C_PA27_SPI0_NPCS1		((unsigned int) 1 << 27)
#define	AT91C_PA0_SPI0_MISO		((unsigned int) 1 <<  0) 
#define	AT91C_PA2_SPI0_SPCK		((unsigned int) 1 <<  2)
#define	AT91C_PA1_SPI0_MOSI		((unsigned int) 1 <<  1)

#define AT91C_SPI_SCBR        		((unsigned int) 0xFF <<  8) // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS      		 ((unsigned int) 0xFF << 16) // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT      		((unsigned int) 0xFF << 24)

#define AT91_PIOA_ASR			(*(unsigned *) 0xFFFFF470)
#define AT91_PIOB_ASR			(*(unsigned *) 0xFFFFF670)

#define AT91_PIOA_PER			(*(unsigned *) 0xFFFFF400)
#define AT91_PIOA_PDR			(*(unsigned *) 0xFFFFF404)
#define AT91_PIOB_PER			(*(unsigned *) 0xFFFFF600)
#define AT91_PIOB_PDR			(*(unsigned *) 0xFFFFF604)

//#define AT91_SPI0_BASE			(volatile unsigned int *) 0xFFFC8000
#define AT91A_SPI0_CR 			(0xFFFC8000) 
#define AT91A_SPI0_MR 			(0xFFFC8004)	
#define AT91A_SPI0_CSR1 			(0xFFFC8034)
#define AT91A_SPI0_TDR			(0xFFFC800c)
#define AT91A_SPI0_SR 			(0xFFFC8010)
#define AT91A_SPI0_RDR			(0xFFFC8008)



#define AT91_SPI0_CR 			(*(volatile unsigned int *)(0xFFFC8000)) 
#define AT91_SPI0_MR 			(*(volatile unsigned int *)(0xFFFC8004))	

#define AT91_SPI0_RDR			 (*(volatile unsigned int *)(0xFFFC8008))
#define AT91_SPI0_TDR			 (*(volatile unsigned int *)(0xFFFC800c))
#define AT91_SPI0_SR 			 (*(volatile unsigned int *)(0xFFFC8010))
#define AT91_SPI0_IER			 (*(volatile unsigned int *)(0xFFFC8014))
#define AT91_SPI0_IDR			 (*(volatile unsigned int *)(0xFFFC8018))
#define AT91_SPI0_IMR			 (*(volatile unsigned int *)(0xFFFC801c))

#define AT91_SPI0_CSR0			 (*(volatile unsigned int *)(0xFFFC8030))
#define AT91_SPI0_CSR1 			(*(volatile unsigned int *)(0xFFFC8034))
#define AT91_SPI0_CSR2 			(*(volatile unsigned int *)(0xFFFC8038))
#define AT91_SPI0_CSR3 			(*(volatile unsigned int *)(0xFFFC803c))
//extern void AT91F_IntSDRAM(void);
#define DATAFLASH_TCSS			(0xc << 16)	// 250ns min (tCSS) <=> 12/48000000 = 250ns
#define DATAFLASH_TCHS			(0x1 << 24)	// 250ns min (tCSH) <=> (64*1+SCBR)/(2*48000000)
#define AT91_PMC_PLLAR			 (*(volatile unsigned int *)(0xFFFFFC28))

//AT91C_PMC_PLLAR 0xFFFFFC28

#define SPI_MAJOR 240

#define DEVICENAME "spi"
#define AT91_SPI0_ENABLE 0x1<<0;


extern void AT91F_LowLevelInit(void);

extern void AT91F_DBGU_Printk(char *buffer);



	//* Offset for ARM vector 6

#define AT91C_VERSION	"VER 1.0"
// Global variables and functions definition
extern unsigned int GetTickCount(void);
#endif
