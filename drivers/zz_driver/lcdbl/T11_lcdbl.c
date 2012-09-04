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
/* ** HEADER FILES					        	*/
/************************************************************************/
#include "T11_lcdbl.h"
#include <linux/delay.h>
#include <asm/arch/gpio.h>
#include <asm/arch/at91_pio.h>
#include <asm/atomic.h>
#include <linux/interrupt.h>

static int flag = 1;
static int open_nu = 0;
/*----------------------------------------------------------------------*/
void lcdback_lcd(unsigned int count)
{
	unsigned int loop;

	for(loop=0;loop<count;loop++)
	{
		at91_set_gpio_value(AT91_PIN_PB12, 0);
		udelay (10);
		at91_set_gpio_value(AT91_PIN_PB12, 1);
		udelay (10);
	}

}


static struct tasklet_struct lcd_bl_tasklet;
void lcd_bl_tasklet_func(unsigned long command)
{
	int count;

	//printk ("petworm: lcd_bl_task: command is %d.\n", command);

	switch (command)
	{
		case 88: // close lcd back-light
			at91_set_gpio_value(AT91_PIN_PB12, 0);	
			flag = 0;
			break;
		case 100: // open lcd back-light & adjust the back-light level to 7
			at91_set_gpio_value(AT91_PIN_PB12, 1);
			udelay(40);
			lcdback_lcd (7);
			lcdback_count = 7;
			flag = 1;
			break;
		default: // adjust the back-light level
#if 1
			if (command >= lcdback_count)
				count = command - lcdback_count;
			else
				count = 16 + command -lcdback_count;

			if (count)
				lcdback_lcd (count);

			lcdback_count = command;
			break;
#else
			if (command >=0 && command <=15)
			{
				at91_set_gpio_value(AT91_PIN_PB12, 0);
				mdelay (4);
				at91_set_gpio_value(AT91_PIN_PB12, 1);
				lcdback_lcd (command);
			}
			break;
#endif
	}

}

/*----------------------------------------------------------------------*/
static int lcdback_open(struct inode *inode, struct file *filp)
{
	if (open_nu++ == 0)
	{

		lcdback_count = 7;
	}
	//printk("lcd back ground open sucess! \n");
	
	// initial lcd back-light tasklet
	tasklet_init (&lcd_bl_tasklet, lcd_bl_tasklet_func, NULL);
	return 0;
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
	if (--open_nu == 0)
	{
		at91_set_gpio_value(AT91_PIN_PB12, 0);
	}
	//printk("lcd release goodbye \n");

	// release the lcd back-light tasklet
	tasklet_kill (&lcd_bl_tasklet);
	return 0;
}


/*----------------------------------------------------------------------*/
static atomic_t rt9364_lock = ATOMIC_INIT(1);
static int lcdback_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{// Santiage edit 20090323:

	int ret = 0;
rt9364_opt_wait:
	if (!atomic_dec_and_test (&rt9364_lock))
	{
		atomic_inc (&rt9364_lock);
		printk (KERN_ALERT "petworm: rt9364: locked.\n");
		mdelay (10);
		goto rt9364_opt_wait;
	}

	if ((cmd < 0 || cmd > 17) && !(cmd == 88 || cmd == 100))
		goto quit;

	lcd_bl_tasklet.data = cmd;
	tasklet_schedule (&lcd_bl_tasklet);

quit:
	atomic_inc (&rt9364_lock);
	return ret;
}

/*----------------------------------------------------------------------*/
static const struct file_operations lcdback_fops = {
	.owner = THIS_MODULE,
	.read = lcdback_read,
	.write = lcdback_write,
	.open = lcdback_open,
	.release = lcdback_irelease,
	.ioctl = lcdback_ioctl,
};

/*--------------------------------------------------------------------*/
/*			lcd _init				      */
/*--------------------------------------------------------------------*/
int lcdback_init()
{
	at91_set_gpio_output(AT91_PIN_PB12, 1);
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
