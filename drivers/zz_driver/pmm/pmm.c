/*
 *  pmm.c - Create a module which to control SUSPEND
 */

#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for get_user and put_user */
#include <linux/sched.h>
#include <linux/suspend.h>	/*for pm_suspend*/
#include <asm/io.h>		/*for ioremap & iounmap*/
#include <asm/arch/at91_pmc.h>
#include <asm/arch/gpio.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/irq.h>
#include <linux/interrupt.h>	/* We want an interrupt */
#include "pmm.h"
#include <linux/ext_fun.h>

#include <asm/arch/at91_shdwc.h>

#define SUCCESS 0
#define	FAILED	1
#define DEVICE_NAME "pmm_dev"

#define	DEBUG	1

/* 
 * Is the device open right now? Used to prevent
 * concurent access into the same device 
 */
static int Device_Open = 0;

/*
 * the mark of alarm shutdown, if alarm_shutdown = 1 shutdown the system;
 * else just wakeup the system.
 */
char alarm_shutdown = 0;

void set_alarm_shutdown (void)
{
	alarm_shutdown = 1;
}
EXPORT_SYMBOL (set_alarm_shutdown);

/* 
 * This is called whenever a process attempts to open the device file 
 */
static int device_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk("device_open(%p)\n", file);
#endif

	/* 
	 * We don't want to talk to two processes at the same time 
	 */
	if (Device_Open > 2)
		return -EBUSY;

	Device_Open++;

	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk("device_release(%p,%p)\n", inode, file);
#endif

	/* 
	 * We're now ready for our next caller 
	 */
	Device_Open--;

	module_put(THIS_MODULE);
	return SUCCESS;
}


static ssize_t device_read(struct file *file,	char __user * buffer,	size_t length, loff_t * offset)
{
#ifdef DEBUG
	printk("device_read\n");
#endif
	
	return 0;
}


static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
#ifdef DEBUG
	printk("device_write\n");
#endif

	return 0;
}

/* 
 * This function is called whenever a process tries to do an ioctl on our
 * device file. We get two extra parameters (additional to the inode and file
 * structures, which all device functions get): the number of the ioctl called
 * and the parameter given to the ioctl function.
 *
 * If the ioctl is write or read/write (meaning output is returned to the
 * calling process), the ioctl call returns the output of this function.
 *
 */

extern void at91_rtc_setincien(void);
extern void at91_rtc_clrincien(void);
extern void soft_shutdown_on (void);
extern void soft_shutdown_off (void);
extern u32 _SetILI9325 (u8 tmp);
int device_ioctl(struct inode *inode,	/* see include/linux/fs.h */
		 struct file *file,	/* ditto */
		 unsigned int ioctl_num,	/* number and param for ioctl */
		 unsigned long ioctl_param)
{
	int i, tmp;
	u8 retval;
	//volatile unsigned int* port_addr;
	//unsigned int *reg;

	switch (ioctl_num) 
	{
	case IOCTL_SET_CPUIDLE:
		//printk("the commond is IOCTL_SET_CPUIDLE\n");
		at91_sys_write (AT91_PMC_SCDR, 0x1);
		asm("mcr p15, 0, r0, c7, c0, 4");
		break;

	case IOCTL_SET_LCDLIGHTDOWN:
		//printk("the commond is IOCTL_SET_LCDLIGHTDOWN\n");
		break;

	case IOCTL_SET_STANDBY:
		//printk("the commond is IOCTL_SET_STANDBY\n");
		pm_suspend(PM_SUSPEND_STANDBY);
		break;

	case IOCTL_SET_MEM:
		//printk("the commond is IOCTL_SET_MEM\n");
		soft_shutdown_on ();
		pm_suspend(PM_SUSPEND_MEM);
		break;

	case IOCTL_SET_LCDSHUTDOWN:
		//printk("the commond is IOCTL_SET_LCDSHUTDOWN\n");
		fb_entry_sleep (FB_SLEEP);
		at91_set_cpu_stop(1);
		break;
	case IOCTL_SET_LCDWAKEUP:
		//printk ("the command is IOCTL_SET_LCDWAKEUP\n");
		fb_exit_sleep (FB_SLEEP);
		at91_set_cpu_stop(0);
		break;
	case IOCTL_SET_LCD_STANDBY:
		//fb_entry_sleep (FB_STANDBY);
		at91_set_cpu_stop(1);
		break;
	case IOCTL_EXIT_LCD_STANDBY:
		//fb_exit_sleep (FB_STANDBY);
		at91_set_cpu_stop(0);
		break;

	case IOCTL_SET_LCD_TYPE:
		if (copy_from_user ((void *) &retval, (void *)ioctl_param, 1))
		{
			printk (KERN_ALERT"copy data error.\n");
			return -1;
		}
		printk (KERN_ALERT "#####################################\n");
		printk (KERN_ALERT "petworm: retval is %x.\n");
		printk (KERN_ALERT "#####################################\n");
		_SetILI9325 (retval);
		
		break;
#if 0
	case IOCTL_SYS_SHUTDOWN:
		lock_kernel();
		//printk (KERN_ALERT "petworm: power off now.\n");
		kernel_power_off();
		unlock_kernel();
		break;
	case IOCTL_SYS_HALT:
		lock_kernel();
		kernel_halt();
		unlock_kernel();
		break;
	case IOCTL_SYS_REBOOT:
		kernel_restart(NULL);
		break;
#endif
	case IOCTL_INFRARED_OPEN:
		at91_set_gpio_output (AT91_PIN_PB11,0);
		break;
	case IOCTL_INFRARED_CLOSE:
		at91_set_gpio_output (AT91_PIN_PB11,1);
		break;
	case IOCTL_INFRAD_RX_DIS:
		at91_set_gpio_output (AT91_PIN_PC13, 1);
		break;
	case IOCTL_INFRAD_RX_EN:
		at91_set_A_periph (AT91_PIN_PC13, 1);
		break;
	case IOCTL_UART_OPEN:
		at91_set_gpio_output (AT91_PIN_PB18, 0);
		at91_set_gpio_output (AT91_PIN_PB7, 0);
		at91_set_gpio_output (AT91_PIN_PB25, 0);
		break;
	case IOCTL_UART_CLOSE:
		/* close PB7 first, colse PB18 second */
		at91_set_gpio_output (AT91_PIN_PB7, 1);
		at91_set_gpio_output (AT91_PIN_PB18, 1);
		break;
	case IOCTL_UDP_OPEN:
		at91_set_gpio_output (AT91_PIN_PB18, 0);
		at91_set_gpio_output (AT91_PIN_PB7, 1);
		at91_set_gpio_output (AT91_PIN_PB25, 0);
		break;
	case IOCTL_UDP_CLOSE:
		at91_set_gpio_output (AT91_PIN_PB18, 1);
		break;
	case IOCTL_UHP_OPEN:
		at91_set_gpio_output (AT91_PIN_PB18, 0);
		at91_set_gpio_output (AT91_PIN_PB7, 1);
		at91_set_gpio_output (AT91_PIN_PB25, 1);
		break;
	case IOCTL_UHP_CLOSE:
		at91_set_gpio_output (AT91_PIN_PB25, 0);
		at91_set_gpio_output (AT91_PIN_PB18, 1);
		break;

	case IS_ALARM_SHUTDOWN:
		//printk (KERN_ALERT "petworm: pmm ioctl: IS_ALARM_SHUTDOWN. %x\n", alarm_shutdown);
		soft_shutdown_off ();
		if (copy_to_user((void *) ioctl_param, (void *) &alarm_shutdown, 1))
			printk (KERN_ALERT "copy error\n");
		alarm_shutdown = 0;
		break;
	case IOCTL_KEYB_BEEP:
		//printk (KERN_ALERT "petowrm: beep time is %d.\n", ioctl_param);
		at91_set_gpio_value (AT91_PIN_PB9, 0);
		mdelay (ioctl_param);
		at91_set_gpio_value (AT91_PIN_PB9, 1);
		break;
	case IOCTL_1HZ_ENABLE:
		at91_rtc_setincien();
		break;
	case IOCTL_1HZ_DISABLE:
		at91_rtc_clrincien();
		break;

	case IOCTL_GET_FIQ:
#ifdef EMERGENCY_SHUTDOWN
		for (i = 0, tmp =0; i < 3; i++)
		{
			mdelay (20);
			if (at91_get_gpio_value(AT91_PIN_PC11))
				tmp ++;
		}

		if (tmp < 3)
			retval = 1;
		else
			retval = 0;

		if (copy_to_user ((void *)ioctl_param, (void *)&retval, 1))
			printk (KERN_ALERT, "emergency shutdown copy data error.\n");
#else
		retval = 0;
		if (copy_to_user ((void *)ioctl_param, (void *)&retval, 1))
			printk (KERN_ALERT, "emergency shutdown copy data error.\n");
#endif
		break;

case IOCTL_GET_SHTDWN:
#if 1
		retval = at91_sys_read(AT91_SHDW_SR) & 0x1;
#else
		tmp = at91_sys_read(AT91_SHDW_SR);

		printk (KERN_ALERT "SHDW SR is %x.\n", (u32) tmp);
		printk (KERN_ALERT "SHDW MR is %x.\n", at91_sys_read(AT91_SHDW_MR));
#endif
		if (copy_to_user ((void *) ioctl_param, (void *) &retval, 1))
			printk (KERN_ALERT "copy error.\n");
		break;

	case IOCTL_SHTDWN_CHARGE:
		at91_sys_write (AT91_SHDW_CR, AT91_SHDW_SHDW | AT91_SHDW_KEY);
		break;
	default:
		break;
	}

	return SUCCESS;
}

struct file_operations Fops = {
	.read = device_read,
	.write = device_write,
	.ioctl = device_ioctl,
	.open = device_open,
	.release = device_release,	/* a.k.a. close */
};

static struct proc_dir_entry *proc_file;
static int zzgpios_read (char *page, char **start, off_t off, int count,
			  int *eof, void *data_unused)
{
	int iskey, check_num = 0;
	int i;

	at91_set_gpio_input (AT91_PIN_PB15, 0);

	for (i = 0; i < 3; i++)
	{
		mdelay (10);
		iskey = at91_get_gpio_value (AT91_PIN_PB15);
		if (!iskey)
		{
			check_num ++;
		}
	}

	if (check_num >= 2)
		iskey = 1;
	else
		iskey = 0;

	return sprintf (page, "%d", iskey);

}


#ifdef EMERGENCY_SHUTDOWN
void emergency_shutdown_func (void)
{
	int have_guicmd = 0;
	struct task_struct *p, *pchild1, *pchild2;
	struct task_struct *psig1, *psig2, *psig3;
	struct list_head *list1, *list2;

	/* beep */
	//Keyb_beep (240);

	read_lock(&tasklist_lock);
	p=&init_task;

	for_each_process(p)
	{// 一级子进程

		if(!memcmp (p->comm, "guicmd", 6) && 
#if 0
				(!memcmp (p->parent->comm, "rcS", 3) ||
				 !memcmp (p->parent->comm, "sh", 2)))
#else
				(memcmp (p->parent->comm, "guicmd", 6)))
#endif
		{
			have_guicmd |= 0x1;
			psig1 = p;

			list_for_each(list1, &p->children)
			{// 二级子进程
				pchild1 = list_entry(list1, struct task_struct, sibling);

				if (!memcmp (pchild1->comm, "sh", 2) && !list_empty(&pchild1->children))
				{
					list_for_each(list2, &pchild1->children)
					{
						pchild2 = list_entry(list2, struct task_struct, sibling);

						have_guicmd |= 0x2;
						psig2 = pchild2;

					}
				}
			}
		}
		else if (!memcmp (p->comm, "t11comm", 7))
		{
			have_guicmd |= 0x4;
#if 0
			psig3 = p;
#else
			if (!memcmp (p->parent->comm, "t11comm", 7))
				psig3 = p->parent;
			else
				psig3 = p;

#endif
		}
	}


	if (have_guicmd & 0x4)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig3->pid);
		send_sig(ZZSHTDWN, psig3, 1);
	}
	else if (have_guicmd & 0x2)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig2->pid);
		send_sig(ZZSHTDWN, psig2, 1);
	}
	else if (have_guicmd & 0x1)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig1->pid);
		if (psig1->blocked.sig[1]& (0x1 << 18))
			printk (KERN_ALERT "sig have been blocked.\n");

		send_sig(ZZSHTDWN, psig1, 1); 
	}


	read_unlock(&tasklist_lock);

}

DECLARE_TASKLET (emergency_shutdown, emergency_shutdown_func, NULL);
static irqreturn_t T11_shutdown_irq (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	int tmp, i;
/*
	printk ("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printk ("T11_shutdown_irq enter.\n");
	printk ("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
*/
	//disable_irq (AT91_ID_FIQ);
	disable_irq (AT91_PIN_PC11);

	at91_set_gpio_input (AT91_PIN_PC11, 0);
	
retry:
	for (i = 0, tmp =0; i < 3; i++)
	{
		mdelay (20);
		if (!at91_get_gpio_value(AT91_PIN_PC11))
			tmp ++;
	}

	if (tmp == 3)
		tasklet_schedule (&emergency_shutdown);
	else if (tmp == 0)
	{
		at91_set_B_periph(AT91_PIN_PC11, 1);
		//enable_irq (AT91_ID_FIQ);
		enable_irq (AT91_PIN_PC11);
	}
	else
		goto retry;

	return IRQ_HANDLED;
}
#endif

int __init init_pmm_module(void)
{
	int ret_val;

	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

	if (ret_val < 0) 
	{
		printk("%s failed with %d\n","Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	proc_file = create_proc_entry("zzgpios", 0, NULL);
	if (proc_file)
		proc_file->read_proc = zzgpios_read;
#ifdef EMERGENCY_SHUTDOWN
	/* emergency shutdown irq */
	//at91_set_B_periph(AT91_PIN_PC11, 1);
	at91_set_gpio_input (AT91_PIN_PC11, 0);
	if (request_irq(AT91_PIN_PC11, T11_shutdown_irq, /*IRQF_SHARED | */IRQ_TYPE_EDGE_FALLING, "emergency_shutdown", NULL/*&Device_Open*/))
		printk (KERN_ALERT"power key irq error\n");
#endif
/*
	printk("%s The major device number is %d.\n",
	       "Registeration is a success", MAJOR_NUM);
	printk("If you want to talk to the device driver,\n");
	printk("you'll have to create a device file. \n");
	printk("We suggest you use:\n");
	printk("mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
	printk("The device file name is important, because\n");
	printk("the ioctl program assumes that's the\n");
	printk("file you'll use.\n");
*/
	return 0;
}

void __exit cleanup_pmm_module()
{
//	int ret;

	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
//	ret = unregister_chrdev(MAJOR_NUM, DEVICE_NAME);

//	if (ret < 0)
//		printk("Error in module_unregister_chrdev: %d\n", ret);
}

module_init(init_pmm_module);
module_exit(cleanup_pmm_module);

void __init t11_gpio_init (void)
{
	int *pio_addr;

	pio_addr = ioremap (0xfffff800, 4);
	*(pio_addr + (0x64 >> 2)) = 0xffffffff;
	iounmap (pio_addr);

	pio_addr = ioremap (0xfffff600, 4);
	*(pio_addr + (0x64 >> 2)) = 0xffffffff;
	iounmap (pio_addr);

	pio_addr = ioremap (0xfffff400, 4);
	*(pio_addr + (0x64 >> 2)) = 0xffffffff;
	iounmap (pio_addr);

	at91_set_gpio_output (AT91_PIN_PA15, 1);
	at91_set_gpio_output (AT91_PIN_PA16, 1);
	at91_set_gpio_output (AT91_PIN_PA21, 1);
	at91_set_gpio_output (AT91_PIN_PA22, 1);
	at91_set_gpio_output (AT91_PIN_PA25, 1);
	at91_set_gpio_output (AT91_PIN_PA26, 1);
	at91_set_gpio_output (AT91_PIN_PA29, 1);
	at91_set_gpio_output (AT91_PIN_PA30, 1);
	at91_set_gpio_output (AT91_PIN_PA31, 1);

	at91_set_gpio_output (AT91_PIN_PB3, 1);
	at91_set_gpio_output (AT91_PIN_PB13, 1);
	at91_set_gpio_output (AT91_PIN_PB14, 1);
	at91_set_gpio_output (AT91_PIN_PB19, 1);
	at91_set_gpio_output (AT91_PIN_PB21, 1);
	at91_set_gpio_output (AT91_PIN_PB22, 1);
	at91_set_gpio_output (AT91_PIN_PB26, 1);
	at91_set_gpio_output (AT91_PIN_PB28, 0);

	at91_set_gpio_output (AT91_PIN_PC3, 1);
	at91_set_gpio_output (AT91_PIN_PC4, 1);
	at91_set_gpio_output (AT91_PIN_PC6, 1);
	at91_set_gpio_output (AT91_PIN_PC7, 1);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karsten Jeppesen <karsten@jeppesens.com>");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");

