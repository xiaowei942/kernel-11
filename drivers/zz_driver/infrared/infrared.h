 //  ----------------------------------------------------------------------------
 //          ATMEL Microcontroller Software Support  -  ROUSSET  -
 //  ----------------------------------------------------------------------------
 //  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 //  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 //  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 //  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 //  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 //  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 //  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 //  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 //  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 //  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 //  ----------------------------------------------------------------------------
//*----------------------------------------------------------------------------
//* File Name           : main.h
//* Object              : main application written in C
//* Creation            : NLe   27/11/2002
//*
//*----------------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>	/* for put_user */
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/clk.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/tty_flip.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/atmel_pdc.h>

#include <asm/io.h>

#include <asm/mach/serial_at91.h>
#include <asm/arch/board.h>

#define infrared_MAJOR  246
#define DEVICENAME			"infrared"

// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_RSTRX        ((unsigned int) 0x1 <<  2) // (DBGU) Reset Receiver
#define AT91C_US_RSTTX        ((unsigned int) 0x1 <<  3) // (DBGU) Reset Transmitter
#define AT91C_US_RXEN         ((unsigned int) 0x1 <<  4) // (DBGU) Receiver Enable
#define AT91C_US_RXDIS        ((unsigned int) 0x1 <<  5) // (DBGU) Receiver Disable
#define AT91C_US_TXEN         ((unsigned int) 0x1 <<  6) // (DBGU) Transmitter Enable
#define AT91C_US_TXDIS        ((unsigned int) 0x1 <<  7) // (DBGU) Transmitter Disable
#define AT91C_US_RSTSTA       ((unsigned int) 0x1 <<  8) // (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
// -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_USMODE       ((unsigned int) 0xF <<  0) // (USART) Usart mode
#define 	AT91C_US_USMODE_NORMAL               ((unsigned int) 0x0) // (USART) Normal
#define 	AT91C_US_USMODE_RS485                ((unsigned int) 0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                ((unsigned int) 0x2) // (USART) Hardware Handshaking
#define 	AT91C_US_USMODE_MODEM                ((unsigned int) 0x3) // (USART) Modem
#define 	AT91C_US_USMODE_ISO7816_0            ((unsigned int) 0x4) // (USART) ISO7816 protocol: T = 0
#define 	AT91C_US_USMODE_ISO7816_1            ((unsigned int) 0x6) // (USART) ISO7816 protocol: T = 1
#define 	AT91C_US_USMODE_IRDA                 ((unsigned int) 0x8) // (USART) IrDA
#define 	AT91C_US_USMODE_SWHSH                ((unsigned int) 0xC) // (USART) Software Handshaking
#define AT91C_US_CLKS         ((unsigned int) 0x3 <<  4) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CLKS_CLOCK                ((unsigned int) 0x0 <<  4) // (USART) Clock
#define 	AT91C_US_CLKS_FDIV1                ((unsigned int) 0x1 <<  4) // (USART) fdiv1
#define 	AT91C_US_CLKS_SLOW                 ((unsigned int) 0x2 <<  4) // (USART) slow_clock (ARM)
#define 	AT91C_US_CLKS_EXT                  ((unsigned int) 0x3 <<  4) // (USART) External (SCK)
#define AT91C_US_CHRL         ((unsigned int) 0x3 <<  6) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CHRL_5_BITS               ((unsigned int) 0x0 <<  6) // (USART) Character Length: 5 bits
#define 	AT91C_US_CHRL_6_BITS               ((unsigned int) 0x1 <<  6) // (USART) Character Length: 6 bits
#define 	AT91C_US_CHRL_7_BITS               ((unsigned int) 0x2 <<  6) // (USART) Character Length: 7 bits
#define 	AT91C_US_CHRL_8_BITS               ((unsigned int) 0x3 <<  6) // (USART) Character Length: 8 bits
#define AT91C_US_SYNC         ((unsigned int) 0x1 <<  8) // (USART) Synchronous Mode Select
#define AT91C_US_NBSTOP       ((unsigned int) 0x3 << 12) // (USART) Number of Stop bits
#define 	AT91C_US_NBSTOP_1_BIT                ((unsigned int) 0x0 << 12) // (USART) 1 stop bit
#define 	AT91C_US_NBSTOP_15_BIT               ((unsigned int) 0x1 << 12) // (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits

#define AT91C_US_PAR_NONE         ((unsigned int) 0x4 << 9) // (USART) Bit Order

#define UART_GET_CHAR(port)	__raw_readl(port + 0x18)
//#define UART_GET_CHAR(port)	__raw_readl((port)->membase + US1_RHR)



#define 	AT91C_US_NBSTOP_2_BIT                ((unsigned int) 0x2 << 12) // (USART) 2 stop bits
#define AT91C_US_MSBF         ((unsigned int) 0x1 << 16) // (USART) Bit Order
#define AT91C_US_MODE9        ((unsigned int) 0x1 << 17) // (USART) 9-bit Character length
#define AT91C_US_CKLO         ((unsigned int) 0x1 << 18) // (USART) Clock Output Select
#define AT91C_US_OVER         ((unsigned int) 0x1 << 19) // (USART) Over Sampling Mode
#define AT91C_US_INACK        ((unsigned int) 0x1 << 20) // (USART) Inhibit Non Acknowledge
#define AT91C_US_DSNACK       ((unsigned int) 0x1 << 21) // (USART) Disable Successive NACK
#define AT91C_US_MAX_ITER     ((unsigned int) 0x1 << 24) // (USART) Number of Repetitions
#define AT91C_US_FILTER       ((unsigned int) 0x1 << 28) // (USART) Receive Line Filter
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXRDY        ((unsigned int) 0x1 <<  0) // (DBGU) RXRDY Interrupt
#define AT91C_US_TXRDY        ((unsigned int) 0x1 <<  1) // (DBGU) TXRDY Interrupt
#define AT91C_US_ENDRX        ((unsigned int) 0x1 <<  3) // (DBGU) End of Receive Transfer Interrupt
#define AT91C_US_ENDTX        ((unsigned int) 0x1 <<  4) // (DBGU) End of Transmit Interrupt
#define AT91C_US_OVRE         ((unsigned int) 0x1 <<  5) // (DBGU) Overrun Interrupt
#define AT91C_US_FRAME        ((unsigned int) 0x1 <<  6) // (DBGU) Framing Error Interrupt
#define AT91C_US_PARE         ((unsigned int) 0x1 <<  7) // (DBGU) Parity Error Interrupt
#define AT91C_US_TXEMPTY      ((unsigned int) 0x1 <<  9) // (DBGU) TXEMPTY Interrupt
#define AT91C_US_TXBUFE       ((unsigned int) 0x1 << 11) // (DBGU) TXBUFE Interrupt
#define AT91C_US_RXBUFF       ((unsigned int) 0x1 << 12) // (DBGU) RXBUFF Interrupt
#define AT91C_US_COMM_TX      ((unsigned int) 0x1 << 30) // (DBGU) COMM_TX Interrupt
#define AT91C_US_COMM_RX      ((unsigned int) 0x1 << 31) // (DBGU) COMM_RX Interrupt
#define PIOA_BASE 				(0xFFFFF400)
#define PIOB_BASE 				(0xFFFFF600)
#define PIOC_BASE 				(0xFFFFF800)
#define PMC_PCER 				(0xFFFFFC10)
#define  US1_BASE_CR  	(0xFFFB4000)

#define  US1_CSR				( 0x14 >> 2)
#define  US1_RHR 				( 0x18 >> 2)
#define  US1_THR 				( 0x1C >> 2)
#define  US1_BRGR 			( 0x20 >> 2)
#define  US1_RTOR 			( 0x24 >> 2)
#define  US1_TTGR 			( 0x28 >> 2)
#define  US1_IDR 				( 0x0C >> 2)
#define  US1_MR 				( 0x4 >> 2)

#define  US1_RNPR 				( 0x110 >> 2)
#define  US1_TCR 				( 0x10C >> 2)
#define  US1_TPR 				( 0x108 >> 2)
#define  US1_RCR 				( 0x104 >> 2)
#define  US1_RPR 				( 0x100 >> 2)

#define  US1_PTCR 				( 0x120 >> 2)
#define  US1_TNCR 				( 0x11C >> 2)
#define  US1_TNPR 				( 0x118 >> 2)
#define  US1_RNCR 				( 0x114 >> 2)
#define  US1_PTSR 				( 0x124 >> 2)

//#define  US1_THR 				( 0x1C >> 2)

#define AT91C_PDC_RXTEN       ((unsigned int) 0x1 <<  0) // (PDC) Receiver Transfer Enable
#define AT91C_PDC_RXTDIS      ((unsigned int) 0x1 <<  1) // (PDC) Receiver Transfer Disable
#define AT91C_PDC_TXTEN       ((unsigned int) 0x1 <<  8) // (PDC) Transmitter Transfer Enable
#define AT91C_PDC_TXTDIS      ((unsigned int) 0x1 <<  9)

#define PIO_PER					(0x00 >> 2)
#define PIO_OER					(0x10 >> 2)
#define PIO_SODR					(0x30 >> 2)
#define PIO_CODR					(0x34 >> 2)
#define PIO_PDR					(0x04 >> 2)
#define PIO_ASR					(0x70 >> 2)
#define PIO_BSR					(0x74 >> 2)

#define AT91C_PIO_PA11       ((unsigned int) 1 << 11) // Pin Controlled by PA11
#define AT91C_PIO_PA12       ((unsigned int) 1 << 12) // Pin Controlled by PA12
#define AT91C_PIO_PA13       ((unsigned int) 1 << 13) // Pin Controlled by PA13

#define AT91C_PIO_PC12       ((unsigned int) 1 << 12) // Pin Controlled by PC12
#define AT91C_PIO_PC13       ((unsigned int) 1 << 13) // Pin Controlled by PC13

#define ID_US1    ((unsigned int)  7) // USART 1
// Global declarations
#define AT91C_MASTER_CLOCK 				99300000
//#define AT91C_MASTER_CLOCK 			67700000
#define AT91C_SLOW_CLOCK		32768
#define AT91C_BAUDRATE_1200	1200
#define TIME_GUARD  				0
#define AT91C_BAUD_RATE			115200

#define AT91C_KEYBOARD_SENSIBILITY			100000	// Time to consider a key is pushed
#define AT91C_KEYBOARD_WAIT_FOR_REFRESH		300000	// Time to wait before a new key test

// IRQ level declaration
#define AT91C_IRQ_LEVEL_ST_DBGU		3	// < SPI and > Audio
#define AT91C_IRQ_LEVEL_TWI			4
#define AT91C_IRQ_LEVEL_I2S			5	

// Constant declarations used by I2S mode
#define AT91C_I2S_NB_SLOT_BY_FRAME	2
#define AT91C_I2S_NB_BITS_BY_SLOT	16


#endif // MAIN_H
