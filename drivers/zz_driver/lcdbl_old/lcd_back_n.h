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
//* Object              :
//*
//* 1.0 27/03/03 HIi    : Creation
//* 1.01 03/05/04 HIi   : AT9C_VERSION incremented to 1.01
//* 1.02 15/06/04 HIi   : AT9C_VERSION incremented to 1.02 ==> 
//*						  Add crc32 to verify dataflash download
//* 1.03 25/05/05 GGi   : AT9C_VERSION incremented to 1.03 ==> 9261 version
//*----------------------------------------------------------------------------

#ifndef lcdback_back_h
#define lcdback_back_h


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>	/* for put_user */
#include <asm/io.h>


#define AT91C_VERSION   "VER 1.0"
#define DEVICENAME "lcdback_back"
#define lcdback_MAJOR  241

#define AT91C_FRAME_BUFFER	0x20000000
#define AT91C_ATMEL_LOGO		0x20020000
#define AT91C_ATMEL_WAVE	0x20030000
#define AT91C_MATRIX_EBICSA 	0xffffee30
#define AT91C_SMC_SETUP5  	0xffffec50
#define AT91C_SMC_PULSE5		0xffffec54
#define	AT91C_SMC_CYCLE5	0xffffec58
#define	AT91C_SMC_CTRL5		0xffffec5c
#define  AT91C_PIOB_PER		0xfffff600	

volatile unsigned int *paddr;
unsigned int lcdback_count=0;
void lcdback_lcd(unsigned int );
int lcdback_init(void);


#endif
