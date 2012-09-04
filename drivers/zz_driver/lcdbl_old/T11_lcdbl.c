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
/*
 * AT91SAM9261 LCD Controller
 *
 * (C) Copyright 2001-2002
 * Wolfgang Denk, DENX Software Engineering -- wd@denx.de
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/************************************************************************/
/* ** HEADER FILES														*/
/************************************************************************/
#include "T11_lcdbl.h"
#define PB12 (0x1<<12)

/*----------------------------------------------------------------------*/
void lcdback_lcd(unsigned int count)
{
	unsigned int loop;
		paddr = ioremap(0xfffff630,8);
		for(loop=0;loop<count;loop++)
		{
			*(paddr+1)|=PB12;
			*paddr|=PB12;
		}

		iounmap(paddr);
}	
/*----------------------------------------------------------------------*/
static int lcdback_open(struct inode *inode, struct file *filp)
{
	paddr = ioremap(0xfffff630,4);
	*paddr |=	PB12;
	iounmap(paddr);
	//printk("lcd back ground open sucess! \n");
	return 0;
	//*AT91C_PIOC_SODR|=0x00000080;
}

/*----------------------------------------------------------------------*/
static ssize_t lcdback_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos)
{	
	printk("this is lcdwrite test\n");
	return 0;
}

/*----------------------------------------------------------------------*/
static ssize_t lcdback_read(struct file *file,  char __user *buf, size_t count, loff_t *f_pos)
{
	printk("this is lcd read test \n");
	return 0;
}

/*----------------------------------------------------------------------*/
static int lcdback_irelease(struct inode *inode, struct file *filp)
{	
	paddr = ioremap(0xfffff634,4);
	*paddr |= PB12;
	iounmap(paddr);
	printk("lcd release goodbye \n");
	return 0;
	//	*AT91C_PIOC_CODR|=0x00000080;
}

/*----------------------------------------------------------------------*/
static int lcdback_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)

{
	//int i=0;
	if(cmd>15)
	{
#ifdef LCDBL_DBG
		printk("+++++++++++++++++++++++++++++\n");
		printk("please input the right step 0~15\n");
		printk("+++++++++++++++++++++++++++++\n");
#endif
		return 1;
	}
#ifdef LCDBL_DBG	
	printk("****************************\n");
	printk("star ioctl the lcd back\n");
#endif
	
	if(lcdback_count > 0){
		lcdback_lcd(16-lcdback_count);			
	}

	lcdback_lcd(cmd);
	//while(i++ < 20000);
	lcdback_count = cmd;
#ifdef LCDBL_DBG
	printk("lcdback_back ioctl is run,\n");
	printk("the step is : %d \n",15-lcdback_count);
	printk("the cmd  is : %d \n",cmd);	
	printk("****************************\n");
#endif
	return 0;
}
/*----------------------------------------------------------------------*/
struct file_operations lcdback_fops = {
	 read:lcdback_read,
	 write:lcdback_write,
	 open:lcdback_open,
	 release:lcdback_irelease,
	 ioctl:lcdback_ioctl,
};
/*----------------------------------------------------------------------*/
/*			lcd _init					      */
/*----------------------------------------------------------------------*/
int lcdback_init()
{
	paddr = ioremap(AT91C_MATRIX_EBICSA,1);
	*paddr &=0xffffff0f;
	iounmap(paddr);
	paddr = ioremap(AT91C_SMC_SETUP5,16);
 	*paddr=0x01020102; //AT91C_SMC_SETUP5
 	*(paddr+1)=0x08060806;//cs time//AT91C_SMC_PULSE5
	*(paddr+2)=0x000a000a;//a2 time// AT91C_SMC_CYCLE5
	*(paddr+3)=0x10001003; //AT91C_SMC_CTRL5
	iounmap(paddr);
	
	paddr = ioremap(AT91C_PIOB_PER,0xA8);	
 	*paddr |=PB12;
	*(paddr+1)|=0x00000020;
	*(paddr + (0x10>>2))|=PB12;
	*(paddr + (0x34>>2))|=PB12;
	iounmap(paddr);
	//printk("the lcdback_init is OK \n");
	return 0;

}
/*----------------------------------------------------------------------*/
int __init lcdback_driver_init(void)
{
	int rc;
	lcdback_init();
	
	if ((rc = register_chrdev(lcdback_MAJOR, DEVICENAME , &lcdback_fops)) < 0){
		printk("lcd driver: can't get major %d\n", lcdback_MAJOR);
		return 1;
	}
	printk("the lcd back light driver is insert \n");
	return 0;
}

/*----------------------------------------------------------------------*/
void __exit lcdback_driver_exit(void)
{
	unregister_chrdev(lcdback_MAJOR, DEVICENAME);
	printk("lcd driver exit\n");
}

module_init(lcdback_driver_init);
module_exit(lcdback_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karsten Jeppesen <karsten@jeppesens.com>");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");
