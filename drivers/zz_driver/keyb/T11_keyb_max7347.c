/***************************************************************
 * keyboard driver
 ***************************************************************/

#include <linux/kernel.h>	    /* We're doing kernel work */
#include <linux/module.h>	    /* Specifically, a module */
#include <linux/sched.h>
#include <linux/init.h>		/* Needed for the macros */
#include <linux/fs.h>
#include <linux/interrupt.h>	/* We want an interrupt */
#include <linux/cdev.h>
#include <asm/io.h>
#include <linux/delay.h>      /*Needed for udelay(),mdelay()*/
#include <linux/keyboard.h>
#include <linux/irq.h>
#include <linux/time.h>
#include <linux/unistd.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/arch/gpio.h>
#include <asm/arch/at91_pmc.h>
#include <linux/platform_device.h>

#include <asm-generic/errno-base.h>

#include <linux/pm.h>
#include <asm/arch/board.h>
#include <linux/clk.h>

#include <linux/ext_fun.h>
/*
#include <asm/arch/at91sam926x_sdramc.h>
#include <asm/arch/at91_shdwc.h>
*/
/*
#include <asm/arch-at91/at91_twi.h>
#include <asm/hardware.h>
*/

#include "T11_keyb_max7347.h"


/* 键盘设备结构体 */
static struct keyb_dev
{
	struct cdev	*kb_cdev;		/* cdev结构指针 */
	u16		kbuf[MAX_BUF_NUM];	/* 键盘按键缓冲区 */
	u16		bufb, bufs;		/* 键盘队列指针 */
	u8		irkey;
	u8		is_beep;		/* 按键声音 */
	u8		is_backlight;		/* 键盘背光, 1 - 关, 0 - 开 */
	u8		is_sleep;
};

dev_t dev;		/* 设备信息 */

static struct keyb_dev *pkeyb_dev;

#ifdef HAVE_8025_DEV
/* 8025时钟设备结构体 */

static struct s_8025_dev
{
	struct cdev		*timer_8025_cdev;
	struct rx_8025_time	time;
	u32			time_sign;
};

static struct s_8025_dev *p8025_dev;
#endif

/* TWI r/w lock */
static atomic_t twi_rw_lock = ATOMIC_INIT(1);


/* 蜂鸣器tasklet */
DECLARE_TASKLET (keyb_beep_tasklet, keyb_beep_tasklet_func, NULL);
/* 关机键tasklet */
DECLARE_TASKLET (keyb_pwrkey_tasklet, keyb_pwrkey_tasklet_func, NULL);

static u8  retval = 0;		/* 关机键返回值 */	

static u16 beep_bak = 0;

static struct clk *twi_clk;

static struct timeval otm, ntm;

static struct timer_list pwrkey_timer;

static void pwrkey_timer_handler (void)
{
	printk (KERN_ALERT "petworm: enable power key irq.\n");
	//at91_set_B_periph (POWER_PIO, 1);
#if 0
	enable_irq (POWER_IRQ_ID);
#else
	PWR_IRQ_ENABLE();
#endif
}

u16 get_key_val_no_irq (void)
{
	char datac,tstint;
	int num;
	U16 keysca;
	
	do
        {
             	do
             	{
			/* 从键盘节片读取键值 */
       			if (Key_Read(&datac, 0x0))
				printk (KERN_ALERT "Keyb chip read failed.\n");
#ifdef KEYB_DEBUG
			printk (KERN_ALERT "keyirq: the key is %x\n", keysca);
#endif
			if (datac == 0x0)
				return 0;

                	num = (int) (datac & 0x3f);
                	keysca = raw2scancode(num);
#ifdef __NEW_KB
			if (keysca == 0x0f)
			{
				//mdelay (15000);
				pkeyb_dev->is_backlight = !at91_get_gpio_value(KEY_BL);
				at91_set_gpio_value (KEY_BL, pkeyb_dev->is_backlight);
				//at91_set_gpio_value (KEY_BL, !at91_get_gpio_value (KEY_BL));
			}
			else
			{
				if (!at91_get_gpio_value (KEY_SHT))
					keysca |= (0x0f << 8);
				
				//if (kbufin (keysca))
				//	printk (KERN_ALERT "petworm: kbufin full.\n");
			}
#else
			/* 将读取的键值放入缓冲区 */
			if (kbufin (keysca))
				printk (KERN_ALERT "petworm: kbufin full.\n");
#endif



#ifdef __NET_KB
                }while (((datac & 0x40) != 0x0) || (datac != 0x0));
#else
                }while (((datac & 0x40) != 0x0));
#endif

                Key_Read(&tstint, 0x3);
	}while ((tstint & 0x80) != 0);

	return keysca;
}

/********************************************************
 *
 *
 *
 *******************************************************/
void keyb_pwrkey_tasklet_func(void)
{
	int have_guicmd = 0;
	struct task_struct *p, *pchild1, *pchild2;
	struct task_struct *psig1, *psig2, *psig3;
	struct list_head *list1, *list2;

	printk (KERN_ALERT "pwrkey tasklet.\n");

	/* beep */
	Keyb_beep (retval * 120);

	read_lock(&tasklist_lock);
	p=&init_task;

	for_each_process(p)
	{// 一级子进程
		printk ("%d: %s status is: %x; flags is %x.\n", p->pid, p->comm, p->state, p->flags);
		if(!memcmp (p->comm, "guicmd", 6) && 
				(!memcmp (p->parent->comm, "rcS", 3) ||
				 !memcmp (p->parent->comm, "sh", 2)))
		{
			have_guicmd |= 0x1;
			psig1 = p;
			//printk (KERN_ALERT "p->comm is %s.\n", p->comm);
			list_for_each(list1, &p->children)
			{// 二级子进程
				pchild1 = list_entry(list1, struct task_struct, sibling);
				//printk (KERN_ALERT "petworm: pchild1 is %s - %d\n", pchild1-> comm, list_empty(&pchild1->children));
				if (!memcmp (pchild1->comm, "sh", 2) && !list_empty(&pchild1->children))
				{
					list_for_each(list2, &pchild1->children)
					{
						pchild2 = list_entry(list2, struct task_struct, sibling);
						//printk (KERN_ALERT "petworm: pchild2 is %d-%s\n", pchild2->pid, pchild2-> comm);
						have_guicmd |= 0x2;
						psig2 = pchild2;
						
					}
				}
				//printk (KERN_ALERT "guicmd has a child %d:%d:%s.\n", p->pid, pchild1->pid,  pchild1->comm);
			}
			
		}
		else if (!memcmp (p->comm, "t11comm", 7))
		{
			have_guicmd |= 0x4;
			psig3 = p;
		}
	}

	printk (KERN_ALERT "petworm: have_guicmd is %x.\n", have_guicmd);
	if (have_guicmd & 0x4)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig3->pid);
		send_sig(ZZPWRKEY, psig3, 1);
	}
	else if (have_guicmd & 0x2)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig2->pid);
		send_sig(ZZPWRKEY, psig2, 1);
	}
	else if (have_guicmd & 0x1)
	{
		printk (KERN_ALERT "petworm: sign send to %x.\n", psig1->pid);
		if (psig1->blocked.sig[1]& (0x1 << 18))
			printk (KERN_ALERT "sig have been blocked.\n");
/*
		printk (KERN_ALERT "%x-%x-%x-%x-%x-%x.\n", psig1->blocked.sig[1],
				psig1->blocked.sig[0], psig1->real_blocked.sig[1],
				psig1->real_blocked.sig[0],
				psig1->saved_sigmask.sig[1],
				psig1->saved_sigmask.sig[0]);
*/
		send_sig(ZZPWRKEY, psig1, 1); 
	}
	else if (!have_guicmd && retval)
		retval = 0;

	read_unlock(&tasklist_lock);
}

/********************************************************
 *
 *
 *
 *******************************************************/
void keyb_beep_tasklet_func (void)
{
	/* keyb beep */
#ifdef KEYB_DEBUG
	printk (KERN_ALERT "petworm: keyb beep.\n");
#endif

	if (!pkeyb_dev->is_sleep)
	{
		Keyb_beep(60);
	}
} 

/********************************************************
 *
 *
 *
 *******************************************************/
static int keyb_open(struct inode *pinode, struct file *pfile)
{
	pkeyb_dev->bufs = pkeyb_dev->bufb = 0;
	//AT91_TWI_Init(100000);
	return 0;
}

/********************************************************
 * 函数：键盘缓冲区读函数
 * 功能：将键盘驱动中的按键缓冲区复制到用户空间
 * 参数：struct file *p_file:键盘文件指针
 * 	 char __user *buf:   读键缓冲区
 * 	 ssize_t     count:  读取键值的数目
 *******************************************************/
static ssize_t keyb_read(struct file *p_file, char __user *buf, 
			ssize_t count, loff_t *p_pos)
{
	int keynum = 0,i;
	U16 retch;

	if (pkeyb_dev->bufs == pkeyb_dev->bufb)
		return 0;
	for (i = 0; i < (int) count / 2; i++)
	{
		retch = readkey();

		keynum += 2;

		if (pkeyb_dev->bufs == pkeyb_dev->bufb)
			goto out;
	}
out:
	if (copy_to_user(buf, (void *) &retch, keynum))
		printk (KERN_ALERT "copy error\n");
	return (ssize_t) keynum;
}

/********************************************************
 * 函数：键盘缓冲区写函数
 * 功能：将用户空间的键值复制到键盘驱动的按键缓冲区中
 * 	 仅用于T11中文输入法
 * 参数：struct file *p_file:键盘文件指针
 * 	 char __user *buf:   要写入缓冲区的字符串
 * 	 ssize_t     count:  要写入的数目
 *******************************************************/
static ssize_t keyb_write(struct file *pfile, char __user *buf,
	       		size_t count, loff_t *p_pos)
{
	unsigned char keyq[2];
	U16 temp = 0;

#ifdef KEYB_DEBUG
	printk(KERN_ALERT"write function.\n");
#endif
	printk (KERN_ALERT "buf addr is %x.\n", buf);
	if (count != 2)
		printk (KERN_ALERT"keyb write only support two char.%d\n", count);

	if (copy_from_user((void *) keyq, buf, count))
	{
		printk (KERN_ALERT"data copy fail.\n");
		return 0;
	}
	/* 将键值写入kbuf */

	temp = keyq[1] << 8;
	temp |= keyq[0];

#ifdef KEYB_DEBUG
	printk (KERN_ALERT"the data is at kernel now.%x\n", temp);
#endif

	if (kbufin(temp))
		printk (KERN_ALERT "petworm: kbufin full.\n");

	return 2;
}

/********************************************************
 * 函数：键盘驱动控制函数
 * 功能：控制键盘驱动的行为，预留函数
 * 	 功能1：决定读取按键的键值是以什么形式转换及读取的
 * 	 	键值会放入到什么地方
 * 参数：
 ********************************************************/
static int keyb_ioctl(struct inode *p_inode, struct file *p_file, 
			unsigned int cmd, unsigned long arg)
{
	u8 isclr;
	u8 ret = 0;
	u16 check_key;

	//printk (KERN_ALERT "the cmd is %x, the arg is %x.\n",cmd, arg);

	switch (cmd)
	{
		case KEYB_SET_BUF_CLR:
			printk (KERN_ALERT "clear the key buf.\n");
			pkeyb_dev->bufs = pkeyb_dev->bufb = 0;
			break;
		case KEYB_IS_BUF_CLR:
			if (pkeyb_dev->bufs == pkeyb_dev->bufb)
				isclr = 1;
			else
				isclr = 0;
			if (copy_to_user ((void *)arg, (void *) &isclr, 1))
				printk (KERN_ALERT "copy error\n");
			break;
		case KEYB_BEEP_OFF:
			pkeyb_dev->is_beep = 0;
			break;
		case KEYB_BEEP_ON:
			pkeyb_dev->is_beep = 1;
			break;
		case KEYB_BEEP_GET:
			if (copy_to_user ((void *)arg, (void *) &pkeyb_dev->is_beep, 1))
				printk (KERN_ALERT "copy error\n");
			break;
		case PWRKEY_DISABLE_A_SEC:
			printk (KERN_ALERT "petworm: soft shutdown reset.\n");
			do_gettimeofday (&otm);
			break;

		case PWRKEY_DISABLE:
#if 0
			disable_irq (POWER_IRQ_ID);
#else
			if (!timer_pending(&pwrkey_timer))	// Santiage add 20081224 test
				PWR_IRQ_DISABLE();
#endif
			//pkeyb_dev->is_beep = 0;
			break;
		case PWRKEY_ENABLE:
			//pkeyb_dev->is_beep = 1;
#if 0
			enable_irq (POWER_IRQ_ID);
#else
			if (!timer_pending(&pwrkey_timer))	// Santiage add 20081224 test
				PWR_IRQ_ENABLE();
#endif
			break;

		case KEYB_PWRKEY_GET:
			if (retval)
			{
				if (copy_to_user ((void *)arg, (void *) &retval, 1))
					printk (KERN_ALERT "copy error\n");
				retval = 0;
			}
			break;

		case KEYB_IRQ_DISABLE:
/*
			check_key = 0x0400;
			Key_Write (&check_key, 2);
*/
			disable_irq (KEY_IRQ_ID);
			if (!(beep_bak & 0xff00))
			{
				beep_bak = pkeyb_dev->is_beep;
				beep_bak |= 0xff00;
			}
			at91_set_gpio_output (AT91_PIN_PB29, 0);
			pkeyb_dev->is_beep = 0;
			break;
		case KEYB_IRQ_ENABLE:
			if (beep_bak & 0xff00)
			{
				pkeyb_dev->is_beep = (u8) (beep_bak & 0xff);
				beep_bak = 0;
			}
			at91_set_B_periph (AT91_PIN_PB29, 1);
			enable_irq (KEY_IRQ_ID);
/*
			check_key = 0x0480;
			Key_Write (&check_key,2);
*/
			break;

		case KEYB_BL_SAVE:
			at91_set_gpio_value (KEY_BL, 1);
			break;
		case KEYB_BL_RESTORE:
			at91_set_gpio_value (KEY_BL, pkeyb_dev->is_backlight);
			break;
		case PWRKEY_DISABLE_TEMP:
			local_bh_disable ();
#if 0
			disable_irq(POWER_IRQ_ID);
#else
			PWR_IRQ_DISABLE();
#endif
			pwrkey_timer.expires = jiffies + 200;
			if (!timer_pending(&pwrkey_timer))
				add_timer(&pwrkey_timer);
			local_bh_enable ();
			break;

		case PWRKEY_INIT:
			if (request_irq(POWER_IRQ_ID, T11_shutdown_interrputs, IRQ_TYPE_LEVEL_HIGH, "power_key", NULL))
				printk (KERN_ALERT"power key irq error\n");
			break;

		case PWRKEY_TIMER_OFF:
			del_timer(&pwrkey_timer);
			break;

		case KEYB_CHECK_VAL:
			check_key = get_key_val_no_irq ();
			if (copy_to_user ((void *)arg, (void *) &check_key, 2))
					printk (KERN_ALERT "copy error\n");
			break;

		case SCAN_KEY_VAL:
#ifndef SCAN_KEY
			ret = return_pioa20_val();
#endif
			if (copy_to_user ((void *)arg, (void *) &ret, 1))
				printk (KERN_ALERT "scan keyval copy error\n");
			break;


		default:
			return -EINVAL;
	}
	return 0;
}

static int keyb_release(struct inode *p_inode, struct file *p_file)
{
	return 0;
}

/*****************************************************************
 *
 * 键盘驱动操作结构体
 *
 ****************************************************************/
static const struct file_operations keyb_fops =
{
	.owner = THIS_MODULE,
	.read = keyb_read,
	.write = keyb_write,
	.ioctl = keyb_ioctl,
	.open = keyb_open,
	.release = keyb_release,
};


/*****************************************************************
 * 函数：键盘驱动中断服务程序
 * 功能：响应键盘中断、从键盘芯片中读取按键扫描码并将其放入
 * 	 到键盘缓冲区中
 * 参数：参数为系统要求，本身不用到参数
 ****************************************************************/
static irqreturn_t max7347_ServeIrq (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	char datac,tstint;
	int num;
	unsigned int irq_state;
	U16 keysca;

	if (!atomic_dec_and_test (&twi_rw_lock))
	{
		printk (KERN_ALERT "TWI has been locked.\n");
		atomic_inc (&twi_rw_lock);
		disable_irq (KEY_IRQ_ID);
		return IRQ_HANDLED;
	}

	local_irq_save(irq_state);
	//local_irq_disable();
	
	//at91_set_gpio_output (AT91_PIN_PB29, 1);

        do
        {
             	do
             	{
			/* 从键盘节片读取键值 */
       			if (Key_Read(&datac, 0x0))
			{
				printk (KERN_ALERT "Keyb chip read failed.\n");
				return IRQ_HANDLED;
			}
#ifdef KEYB_DEBUG
			printk (KERN_ALERT "keyirq: the key is %x\n", keysca);
#endif

                	num = (int) (datac & 0x3f);
                	keysca = raw2scancode(num);
#ifdef __NEW_KB
#if 1
			if (keysca == 0x0f)
			{
				//mdelay (15000);
				pkeyb_dev->is_backlight = !at91_get_gpio_value(KEY_BL);
				at91_set_gpio_value (KEY_BL, pkeyb_dev->is_backlight);
				//at91_set_gpio_value (KEY_BL, !at91_get_gpio_value (KEY_BL));
			}
			else
#endif
			{
				if (!at91_get_gpio_value (KEY_SHT))
					keysca |= (0x0f << 8);
				if (kbufin (keysca))
					printk (KERN_ALERT "petworm: kbufin full.\n");
			}
#else
			/* 将读取的键值放入缓冲区 */
			if (kbufin (keysca))
				printk (KERN_ALERT "petworm: kbufin full.\n");
#endif
			//printk (KERN_ALERT "petworm: keybufin is %x.\n", keysca);

#if 0
#ifdef CONFIG_VT
             		handle_scancode(keysca, 1);
			handle_scancode(keysca, 0);
#endif
			tasklet_schedule(&keyboard_tasklet);
#endif

#ifdef __NET_KB
                }while (((datac & 0x40) != 0x0) || (datac != 0x0));
#else
                }while (((datac & 0x40) != 0x0));
#endif

                Key_Read(&tstint, 0x3);
	}while ((tstint & 0x80) != 0);

	//at91_set_B_periph (AT91_PIN_PB29, 1);

	//local_irq_enable();
	local_irq_restore(irq_state);

	if (pkeyb_dev->is_beep)
		tasklet_schedule (&keyb_beep_tasklet);

	atomic_inc (&twi_rw_lock);

	return IRQ_HANDLED;
}

/******************************************************************
 *  shutdwon keyb interrupt program
 ******************************************************************/
static irqreturn_t T11_shutdown_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	int iskey;
	int time_of_powerkey = 0;
	int time_spin;

	printk (KERN_ALERT "power key press.\n");
#if 0
	if (retval)
		goto quit;
#endif
#if 0
	disable_irq (POWER_IRQ_ID);
#else
	PWR_IRQ_DISABLE();
#endif
	at91_set_gpio_input (POWER_PIO, 0);
	mdelay (20);
	iskey = at91_get_gpio_value (POWER_PIO);
	if (iskey)
	{
		while (1)
		{
			mdelay (100);

			iskey = at91_get_gpio_value (POWER_PIO);
			if (!iskey || time_of_powerkey > 20)
			{
				break;
			}
			else if (iskey)
			{
				time_of_powerkey ++;
			}
		}
	}
	else
	{
		retval = 0x0;
		printk (KERN_ALERT "power key: noisy signal.\n");
		at91_set_B_periph (POWER_PIO, 1);
#if 0
		enable_irq (POWER_IRQ_ID);
#else
		PWR_IRQ_ENABLE();
#endif
		goto quit_pwrkey_irq;
	}

	if ((time_of_powerkey > 20) && !get_charge_state())
	{
		printk (KERN_ALERT "petworm: keyb: real shutdown.\n");
		/* real shutdown */
		retval = 0x2;
		at91_sys_write (AT91_AIC_ICCR, POWER_IRQ);
		at91_set_B_periph (POWER_PIO, 1);
		//is_irq_disable = 0; // forbid enable power key irq again
		//del_timer(&pwrkey_timer);
	}
	else
	{
		printk (KERN_ALERT "petworm: keyb: soft shutdown.\n");
		/* soft shutdown */
		retval = 0x1;
		at91_set_B_periph (POWER_PIO, 1);
		//enable_irq (POWER_IRQ_ID);
#if 1
		do_gettimeofday (&ntm);
		time_spin = (int)(ntm.tv_sec - otm.tv_sec);
		if ((time_spin <= 2 && time_spin >= 0))	/* soft shutdown protect */
		{
			printk (KERN_ALERT "forbid the soft shutdown.%d\n", 
					ntm.tv_sec - otm.tv_sec);
			retval = 0x0;
		}
#endif
		pwrkey_timer.expires = jiffies + 200;
		add_timer(&pwrkey_timer);
	}

	if (retval)
		tasklet_schedule (&keyb_pwrkey_tasklet);

/*
	if (!(retval & 0x2))
	{
		pwrkey_timer.expires = jiffies + 200;
		add_timer(&pwrkey_timer);
	}
*/
quit_pwrkey_irq:
	return IRQ_HANDLED;
}

/******************************************************************
 *  shutdwon keyb interrupt program
 ******************************************************************/
#ifdef	SCAN_KEY
static irqreturn_t T11_scan_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	int iskey;

	printk (KERN_ALERT "scan key press.\n");

	disable_irq (SCAN_KEY_ID);
	at91_set_gpio_input (SCAN_KEY_ID, 0);

	iskey = at91_get_gpio_value (SCAN_KEY_ID);
	if (iskey)
	{
		goto quit_scan_irq;
	}
	mdelay (20);
	iskey = at91_get_gpio_value (SCAN_KEY_ID);
	if (!iskey)
	{
		printk (KERN_ALERT "scan key: kbufin.\n");
		kbufin (0xf);
		if (pkeyb_dev->is_beep)
			tasklet_schedule (&keyb_beep_tasklet);
	}

quit_scan_irq:
	enable_irq (SCAN_KEY_ID);
	return IRQ_HANDLED;
}

#else

u8 return_pioa20_val (void)
{
	int iskey;

	iskey = at91_get_gpio_value (SCAN_KEY_ID);
	if (iskey)
	{
		goto quit_scan_irq;
	}

	mdelay (20);
	iskey = at91_get_gpio_value (SCAN_KEY_ID);
	if (!iskey)
	{
		printk (KERN_ALERT "scan key: kbufin.\n");
		//kbufin (0xf);
		if (pkeyb_dev->is_beep)
			tasklet_schedule (&keyb_beep_tasklet);
	}
	else
		goto quit_scan_irq;

	return 1;

quit_scan_irq:
	return 0;
}
#endif

#ifdef HAVE_8025_DEV
// the lock of 8025 r/w
static atomic_t rx8025_rw_lock = ATOMIC_INIT(1);
static ssize_t timer_8025_read (struct file *p_file, char __user *buf,
			ssize_t count, loff_t *p_pos)
{
	u32 ret = 0;
	char ch[3];

#ifdef RX8025_OPT_LOCK
rx8025_read_wait:
	if (!atomic_dec_and_test (&rx8025_rw_lock))
	{
		printk (KERN_ALERT "petworm: timer_8025_read: rx8025 locker.\n");
		atomic_inc (&rx8025_rw_lock);
		mdelay (2);
		goto rx8025_read_wait;
	}
#endif
	while (!atomic_dec_and_test (&twi_rw_lock))
	{
		printk (KERN_ALERT "petworm: timer_8025_read: twi locker.\n");
		atomic_inc (&twi_rw_lock);
		mdelay (2);
	}

	disable_irq (KEY_IRQ_ID);
	if (get_8025_time())
	{
		printk (KERN_ALERT "8025: read time error.\n");
		ret = -ETIME;
		goto quit;
	}

	/* check time */
	if (check_time (&p8025_dev->time))
	{
		ret = -ETIME;
		goto quit;
	}

	if (copy_to_user (buf, (void *) &p8025_dev->time, 28))
	{
		printk (KERN_ALERT "8025: copy to user failed.\n");
		ret = -ENODATA;
		goto quit;
	}

quit:
	atomic_inc (&twi_rw_lock);
	enable_irq (KEY_IRQ_ID);
#ifdef RX8025_OPT_LOCK
	atomic_inc (&rx8025_rw_lock);
#endif

	return ret;
}

static ssize_t timer_8025_write (struct file *pfile, char __user *buf,
			ssize_t count, loff_t *p_pos)
{
	u32 ret = 0;
	struct rx_8025_time time_buf; 
#ifdef RX8025_OPT_LOCK
rx8025_read_wait:
	if (!atomic_dec_and_test (&rx8025_rw_lock))
	{
		printk (KERN_ALERT "petworm: timer_8025_write: rx8025 locker.\n");
		atomic_inc (&rx8025_rw_lock);
		mdelay (2);
		goto rx8025_read_wait;
	}
#endif
	if (copy_from_user((void *)&time_buf, buf, 28))
	{
		printk (KERN_ALERT "8025 write: data copy failed.\n");
		ret = -1;
		goto quit;
	}

	ret = check_time(&time_buf);
	if (ret)
	{
		printk (KERN_ALERT "time data error: %x.\n", ret);
		ret = -1;
		goto quit;
	}

	ret = change_time(&time_buf);
	if (ret)
		goto quit;


	while (!atomic_dec_and_test (&twi_rw_lock))
	{
		printk (KERN_ALERT "petworm: timer_8025_write: twi locker.\n");
		atomic_inc (&twi_rw_lock);
		mdelay (2);
	}

	disable_irq (KEY_IRQ_ID);
	update_8025 (&time_buf);
	atomic_inc (&twi_rw_lock);
	enable_irq (KEY_IRQ_ID);

quit:
#ifdef RX8025_OPT_LOCK
	atomic_inc (&rx8025_rw_lock);
#endif
	return ret;
}

static int timer_8025_ioctl (struct inode *p_inode, struct file *p_file,
			unsigned int cmd, unsigned arg)
{
	return 0;
}

static int timer_8025_open (struct inode *pinode, struct file *pfile)
{
	char ch[2];
	//printk ("we can operation this file.\n");

	ch[0] = 0xe0;
	ch[1] = 0x20;

	while (!atomic_dec_and_test (&twi_rw_lock))
	{
		atomic_inc (&twi_rw_lock);
		mdelay (2);
	}

	disable_irq (KEY_IRQ_ID);
	/* set time form as 24 mode */
	T11_TWI_WriteMulti (ch, 2, AT91_RX8025_I2C_ADDRESS);
	atomic_inc (&twi_rw_lock);
	enable_irq (KEY_IRQ_ID);

	return 0;
}

static int timer_8025_release (struct inode *p_inode, struct file *p_file)
{
	return 0;
}
#endif

/*****************************************************************
 *
 * 8025时钟驱动操作结构体
 *
 ****************************************************************/
#ifdef HAVE_8025_DEV
static const struct file_operations f8025_fops =
{
	.owner = THIS_MODULE,
	.read = timer_8025_read,
	.write = timer_8025_write,
	.ioctl = timer_8025_ioctl,
	.open = timer_8025_open,
	.release = timer_8025_release,
};
#endif



/*****************************************************************
 *
 * 键盘驱动中断初始化程序
 *
 ****************************************************************/
void AT91_IRQ_Init(void)
{
#ifdef KEYB_DEBUG
	printk (KERN_ALERT "Init irq.\n");
#endif
	// petworm off need not along 
	// Enable the keyboard interrupt used the PIOC2
	//at91_set_B_periph (AT91_PIN_PC2, 1);
	// Set the interrup IRQ0
	//at91_aic_write (AT91_AIC_IDCR, IRQ0);

	if (request_irq(KEY_IRQ_ID, max7347_ServeIrq, IRQ_TYPE_LEVEL_LOW, "keyb_max7347", NULL))
		printk (KERN_ALERT"keyb irq error\n");
#ifdef	SCAN_KEY
	// scan key init
	if (request_irq(SCAN_KEY_ID, T11_scan_interrputs, IRQ_TYPE_EDGE_BOTH, "scan_key", NULL))
		printk (KERN_ALERT"scan key irq error\n");
#endif

	//setup_timer (&powerkey_timer, powerkey_timer_handler, 0);
	//at91_aic_write (AT91_AIC_IECR, IRQ0);
}

void AT91_TWI_Open (int time)
{
	/* Init the twi pin */
	at91_set_A_periph (AT91_PIN_PA7, 1);
	at91_set_A_periph (AT91_PIN_PA8, 1);

	AT91_PMC_EnableTWIClock ();

	AT91_TWI_Reset();
	AT91_TWI_Configure ();

	AT91_TWI_SetClock (time);
}

int AT91_TWI_Init (int time)
{
	char ch[3];
#ifdef KEYB_DEBUG
	printk (KERN_ALERT "init TWI.\n");
#endif	
	AT91_TWI_Open (time);

#if 0
	local_irq_disable();
	ch[0] = 0x4;
	ch[1] = 0x80;
	do{
		Key_Write(ch, 2);
		Key_Read(&ch[2], ch[0]);
#ifdef KEYB_DEBUG
		printk(KERN_ALERT"key reg 4 is %x\n", ch[2]);
#endif
	}while (ch[1] != ch[2]);

	ch[0] = 0x1;
	ch[1] = 0x1f;
	do{
		Key_Write(ch, 2);
		Key_Read(&ch[2], ch[0]);
#ifdef KEYB_DEBUG
		printk(KERN_ALERT"key reg 1 is %x\n", ch[2]);
#endif
	}while (ch[1] != ch[2]);


	ch[0] = 0x2;
	ch[1] = 0x00;
	do{
		Key_Write(ch, 2);
		Key_Read(&ch[2], ch[0]);
#ifdef KEYB_DEBUG
		printk(KERN_ALERT"key reg 2 is %x\n", ch[2]);
#endif
	}while (ch[1] != ch[2]);


	ch[0] = 0x3;
	ch[1] = 0x01;
	do{
		Key_Write(ch, 2);
		Key_Read(&ch[2], ch[0]);
#ifdef KEYB_DEBUG
		printk(KERN_ALERT"key reg 3 is %x\n", ch[2]);
#endif
	}while (ch[1] != (ch[2] & 0x1f));

	local_irq_enable();
#else

	ch[0] = 0x4;
	ch[1] = 0x80; 
	if (Key_Write(ch, 2))
		printk (KERN_ALERT "Keyb chip write failed.\n");

	ch[0] = 0x1;
	ch[1] = 0x1f;
	if (Key_Write(ch, 2))
		printk (KERN_ALERT "Keyb chip write failed.\n");

	ch[0] = 0x2;
	ch[1] = 0x00;
	if (Key_Write(ch, 2))
		printk (KERN_ALERT "Keyb chip write failed.\n");

	ch[0] = 0x3;
	ch[1] = 0x01;
	if (Key_Write(ch, 2))
		printk (KERN_ALERT "Keyb chip write failed.\n");
#endif

#ifdef KEYB_DEBUG
       ch[0] = 0x1;
       Key_Read(&ch[1], ch[0]);
       printk(KERN_ALERT"key reg 1 is %x\n", ch[1]);       
     
       ch[0] = 0x2;
       Key_Read(&ch[1], ch[0]);
       printk(KERN_ALERT"key reg 2 is %x\n", ch[1]);

       ch[0] = 0x3;
       Key_Read(&ch[1], ch[0]);
       printk(KERN_ALERT"key reg 3 is %x\n", ch[1]);

       ch[0] = 0x4;
       Key_Read(&ch[1], ch[0]);
       printk(KERN_ALERT"key reg 4 is %x\n", ch[1]); 
#endif
       return 0;
}

int cdev_Init()
{
	int result, err;
	unsigned int kb_major = KEYB_CFG_MAJOR, kb_minor = KEYB_CFG_MINOR;
#ifdef KEYB_DEBUG
	printk (KERN_ALERT "Init cdev.\n");
#endif
	if (kb_major) {
	 	dev = MKDEV(kb_major, kb_minor);
	 	result = register_chrdev_region(dev, 2, "kb0");
	} else {
		result = alloc_chrdev_region(&dev, kb_minor, 1, "kb0");
		kb_major = MAJOR(dev);
	}
	if (result < 0) {
	 	printk(KERN_WARNING "scull: can't get keyb major %d\n", result);
	 	return result;
	}
#if 1
	printk (KERN_ALERT"kb_major is %d\n", kb_major);
	printk (KERN_ALERT"kb_minor is %d\n", kb_minor);
#endif
	// 为键盘设备结构体分配空间
	pkeyb_dev = kmalloc(sizeof(struct keyb_dev), GFP_KERNEL);
	//pkeyb_dev = __get_free_page(GFP_KERNEL);
	if (!pkeyb_dev)
	{
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset (pkeyb_dev, 0, sizeof(struct keyb_dev));

	/* 为cdev结构体分配内存空间 */
	pkeyb_dev->kb_cdev = cdev_alloc();
	
	// 为键盘设备进行kcdev注册
	cdev_init(pkeyb_dev->kb_cdev, &keyb_fops);
	pkeyb_dev->kb_cdev->owner = THIS_MODULE;
	pkeyb_dev->kb_cdev->ops = &keyb_fops;
	err = cdev_add(pkeyb_dev->kb_cdev, dev, 1);
	if (err)
	{
		printk(KERN_NOTICE "Error %d keyboard drivce.\n", err);
		goto fail_cdev_add;
	}
#ifdef  HAVE_8025_DEV
	p8025_dev = kmalloc(sizeof (struct keyb_dev), GFP_KERNEL);
	if (!p8025_dev)
	{
		printk ("timer malloc failed.\n");
	}

	// 8025设备cdev注册
	p8025_dev->timer_8025_cdev = cdev_alloc();
	cdev_init (p8025_dev->timer_8025_cdev, &f8025_fops);
	p8025_dev->timer_8025_cdev->owner = THIS_MODULE;
	p8025_dev->timer_8025_cdev->ops = &f8025_fops;
	err = cdev_add(p8025_dev->timer_8025_cdev, dev, 2);
	if (err)
	{
		printk (KERN_ALERT "Error %d 8025 drivces.\n", err);
	}
#endif
	return 0;

	// 失败处理
fail_cdev_add:
	printk(KERN_NOTICE "the cdev add failed.\n");
	kfree (pkeyb_dev);
fail_malloc:
	printk(KERN_NOTICE "the malloc failed.\n");
	unregister_chrdev_region (dev, 1);
	return result;
}

static struct platform_driver at91_keyb_driver = {
	.probe		= at91_keyb_probe,
	.remove		= __devexit_p(at91_keyb_remove),
	.suspend	= at91_keyb_suspend,
	.resume		= at91_keyb_resume,
	.driver		= {
		.name	= "at91_i2c",
		.owner	= THIS_MODULE,
	},
};

static int __init MAX7347_keyb_init(void)
{
#ifdef KEYB_DEBUG
	unsigned int temp;
#endif
	printk (KERN_ALERT"init MAX7347 keyboard chip.\n");

	/* init keyb power management */
	platform_driver_register(&at91_keyb_driver);

	twi_base = ioremap (AT91SAM9261_BASE_TWI, 0x4);

#ifdef __NEW_KB
	/* keyb back-light init */
	at91_set_gpio_output (KEY_BL, 1);
	/* buzzer init */
	at91_set_gpio_output (KEY_BP, 1);
	/* shift key init */
	at91_set_gpio_input (KEY_SHT, 1);
#endif

#ifdef KEYB_DEBUG
	printk (KERN_ALERT "twi_base is %x.\n", AT91SAM9261_BASE_TWI);

	printk (KERN_ALERT "twi_base is %x.\n", twi_base);
#endif

	if (cdev_Init())
		goto fail_init;

	AT91_TWI_Init(100000);

	/* 初始化电源键恢复定时器 */
	init_timer (&pwrkey_timer);
	pwrkey_timer.function = pwrkey_timer_handler;

	AT91_IRQ_Init();


	/* clean the key buffer */
	pkeyb_dev->bufs = pkeyb_dev->bufb = 0;

	/* 默认键盘发声 */
	pkeyb_dev->is_beep = 0;

	/* 初始化键盘背光状态 */
	pkeyb_dev->is_backlight = at91_get_gpio_value(KEY_BL);

#ifdef KEYB_DEBUG
	printk (KERN_ALERT"keyb init finished.\n");
#endif
	return 0;

fail_init:
	printk(KERN_ALERT"fail_init\n");
	return -ENOMEM;
}

static int __exit MAX7347_keyb_exit(void)
{
	printk(KERN_ALERT "exit keyb_max7347.\n");
	/* 释放中断号 */
	disable_irq(KEY_IRQ_ID);
	free_irq (KEY_IRQ_ID, NULL);
#if 0
	disable_irq(POWER_IRQ_ID);
#else
	PWR_IRQ_DISABLE();
#endif
	free_irq (POWER_IRQ_ID, NULL);

	/* 释放文件指针 */
	cdev_del(pkeyb_dev->kb_cdev);	/*释放kcdev*/
	kfree(pkeyb_dev);	/*释放设备结构体*/
	unregister_chrdev_region (dev, 1);	 /*释放设备号*/

	iounmap (twi_base);

	/* cancel the iomap */	
	//iounmap (aic_base);
	return 0;
}

MODULE_AUTHOR("Petworm");
MODULE_LICENSE("Dual BSD/GPL");

module_init(MAX7347_keyb_init);
module_exit(MAX7347_keyb_exit);

/****************************************************************
 * 函数：TWI单字节写函数
 * 功能：向键盘芯片中写入一个字节，该函数和T11_TWI_ReadSingle
 * 	 函数配合使用（即读取的寄存器前需先用本函数写入要读取的
 * 	 寄存器的编号）
 * 参数：int iaddr 要写入的字符变量,该处为键盘节片的寄存器编号
 ****************************************************************/
int T11_TWI_ReadSingle (char *data)
{
	unsigned int status,error=0, end=0;
	unsigned int limit = 0;

	/* Enable Master Mode */
	at91_twi_write (AT91_TWI_CR, AT91_TWI_MSEN);

	/* Set the TWI Master Mode Register */
	at91_twi_write (AT91_TWI_MMR, AT91_MAX7347_I2C_ADDRESS | AT91_TWI_MREAD);
/*
	printk ("MMR is %x.\n", at91_twi_read(AT91_TWI_MMR));
	printk ("SR is %x.\n", at91_twi_read(AT91_TWI_SR));
	printk ("IDAR is %x.\n", at91_twi_read(AT91_TWI_IADR));
	printk ("CWGR is %x.\n", at91_twi_read(AT91_TWI_CWGR));
*/

	at91_twi_write (AT91_TWI_CR, AT91_TWI_START | AT91_TWI_STOP);


	while (!end)
	{
		status = at91_twi_read (AT91_TWI_SR);
		if ((status & AT91_TWI_NACK) == AT91_TWI_NACK)
		{
			error++;
       			end=1;
		}
		/*  Wait for the receive ready is set */
		if ((status & AT91_TWI_RXRDY) == AT91_TWI_RXRDY)
			end=1;
 
      		if (++limit > 10000)
    			return 2;
	}

	*(data) = at91_twi_read (AT91_TWI_RHR);

	/* Wait for the Transmit complete is set */
	status = at91_twi_read (AT91_TWI_SR);
	limit = 0;
	while (!(status & AT91_TWI_TXCOMP))
	{
		status = at91_twi_read (AT91_TWI_SR);
		if (++limit > 10000)
    			return 2;
	}    
	return error;
}

/****************************************************************
 * 函数：TWI单字节读函数
 * 功能：从键盘芯片中读取一个字节，该函数需要T11_TWI_ReadMulti
 * 	 函数配合使用（即读取的寄存器需要先用T11_TWI_ReadMulti
 * 	 函数写入）
 * 参数：char *data 要写入的字符变量的指针
 ****************************************************************/
int T11_TWI_ReadMulti (char *data, u32 chip)
{
#if 0
	u32 status=0, end = 0;
	int i;
	u32 error = 0, ready = 0;
	u32 limit = 0;


	printk(KERN_ALERT "In: ReadSingle\n");

	mdelay(2);
	/* 使能主机模式  */
	at91_twi_write(AT91_TWI_CR, AT91_TWI_MSEN);

	/* 设置模式寄存器 = 从级地址   |   读写位 */
	at91_twi_write(AT91_TWI_MMR, chip | AT91_TWI_MREAD);

	/* 开始接收 */
	at91_twi_write(AT91_TWI_CR, AT91_TWI_START);

	for(i = 0; i < 7; i++)
	{

		while (!end)
		{
			status = at91_twi_read (AT91_TWI_SR);
			if ((status & AT91_TWI_NACK) == AT91_TWI_NACK)
			{
				error++;
				end=1;
			}
			/*  Wait for the receive ready is set */
			if ((status & AT91_TWI_RXRDY) == AT91_TWI_RXRDY)
				end=1;

			if (++limit > 10000)
				return 2;
		}		


		/* 接收数据 */
			data[i] = at91_twi_read(AT91_TWI_RHR);

	}
	/* 接收完毕 置停止位 */
		at91_twi_write(AT91_TWI_CR, AT91_TWI_STOP);

	/*  等待发送结束  */
	status = at91_twi_read(AT91_TWI_SR);
	while (!(status & AT91_TWI_TXCOMP))
	{
		status = at91_twi_read(AT91_TWI_SR);
		if (++ready > 10000)
		{
			return 2;
		}
	}   

	mdelay(4);

	return error;
#else



	u32 status=0;
	int i;
	u32 error = 0, limit;

	//AT9_TWI_init();

	mdelay(2);
	/* 使能主机模式  */
	at91_twi_write(AT91_TWI_CR, AT91_TWI_MSEN);

#if 0
	/* 发送寄存器地址 */
	at91_twi_write(AT91_TWI_MMR, chip & ~AT91_TWI_MREAD);
	at91_twi_write(AT91_TWI_THR, 0xf0);
	status = at91_twi_read (AT91_TWI_SR);
	while (!(status & AT91_TWI_TXCOMP))
	{
		udelay (10);
		status = at91_twi_read (AT91_TWI_SR);
		if (++limit > 10000)
			return 2;
	}
	limit = 0;
#endif
	/* 设置模式寄存器 = 从级地址   |   读写位 */
	at91_twi_write(AT91_TWI_MMR, chip | AT91_TWI_MREAD);

	/* 开始接收 */
	at91_twi_write(AT91_TWI_CR, AT91_TWI_START);

	for(i=0;i<8;i++)
	{
		/* 等待应答 */
		limit = 0;
		status = at91_twi_read(AT91_TWI_SR);
		while ((status & AT91_TWI_NACK) == AT91_TWI_NACK)
		{
			if (++limit > 10000)
			{
				return 2;
			}
			status = at91_twi_read(AT91_TWI_SR);
		}    

		/*  等待接收ready 位 被置  */
		limit = 0;
		status = at91_twi_read(AT91_TWI_SR);
		while ((status & AT91_TWI_RXRDY) != AT91_TWI_RXRDY)
		{
			if (++limit > 10000)
			{
				return 2;
			}
			status = at91_twi_read(AT91_TWI_SR);
		}


		/* 接收数据 */
		data[i] = at91_twi_read(AT91_TWI_RHR);
	}

	/* 接收完毕 置停止位 */
	at91_twi_write(AT91_TWI_CR, AT91_TWI_STOP);

	/*  等待发送结束  */
	limit = 0; 
	status = at91_twi_read(AT91_TWI_SR);
	while (!(status & AT91_TWI_TXCOMP))
	{
		status = at91_twi_read(AT91_TWI_SR);
		if (++limit > 10000)
		{
			return 2;
		}
	}   

	mdelay(4);

	return error;
#endif
}

/****************************************************************
 * 函数：TWI单字节读函数
 * 功能：从键盘芯片中读取一个字节，该函数需要T11_TWI_WriteSingle
 * 	 函数配合使用（即读取的寄存器需要先用T11_TWI_WriteSingle
 * 	 函数写入）
 * 参数：char *data 要写入的字符变量的指针
 ****************************************************************/
int T11_TWI_WriteSingle (int iaddr)
{
	unsigned int end = 0, status, error=0;
	unsigned int limit = 0;
	/* Enable Master Mode */
	at91_twi_write (AT91_TWI_CR, AT91_TWI_MSEN);
	/* Set the TWI Master Mode Register */
	at91_twi_write (AT91_TWI_MMR, AT91_MAX7347_I2C_ADDRESS & ~AT91_TWI_MREAD);
/*
	printk ("MMR is %x.\n", at91_twi_read(AT91_TWI_MMR));
	printk ("SR is %x.\n", at91_twi_read(AT91_TWI_SR));
	printk ("IDAR is %x.\n", at91_twi_read(AT91_TWI_IADR));
	printk ("CWGR is %x.\n", at91_twi_read(AT91_TWI_CWGR));
*/
	/* Write the data to send into THR. Start conditionn DADDR and R/W bit are sent automatically */
	at91_twi_write (AT91_TWI_THR, iaddr);

	while (!end)
	{
		udelay(10);
		status = at91_twi_read (AT91_TWI_SR);
		if ((status & AT91_TWI_NACK) == AT91_TWI_NACK)
		{
			error++;
			end=1;
		}
		/*  Wait for the Transmit ready is set */
		if ((status & AT91_TWI_TXRDY) == AT91_TWI_TXRDY)
			end=1;

		if (++limit > 10000)
    			return 2;
	}

	/* Wait for the Transmit complete is set */
	status = at91_twi_read (AT91_TWI_SR);
	limit = 0;
	while (!(status & AT91_TWI_TXCOMP))
	{
		udelay(10);
		status = at91_twi_read (AT91_TWI_SR);
		if (++limit > 10000)
    			return 2;
	}

	return error;
}

/****************************************************************
 * 函数：TWI多字节写函数
 * 功能：向键盘芯片中写入多个字节，
 * 参数：char *data	要写入的址淞恐刚�
 * 	 int num	要写入的字节数
 ****************************************************************/
int T11_TWI_WriteMulti(char *data, int num, u32 chip)
{
	unsigned int end = 0, status, error=0, Count;
	unsigned int limit = 0;

	
	/* Enable Master Mode */
	at91_twi_write (AT91_TWI_CR, AT91_TWI_MSEN);

	/* Wait until TXRDY is high to transmit */
	do{
   		status = at91_twi_read (AT91_TWI_SR);
   		if (++limit > 10000)
   			return 2;
	}while (!(status & AT91_TWI_TXRDY));

	/* Set the TWI Master Mode Register */
	at91_twi_write (AT91_TWI_MMR, /*AT91_MAX7347_I2C_ADDRESS*/chip & ~AT91_TWI_MREAD);

	/* Send the data */
	for ( Count=0; Count < num ;Count++ )
	{/* Write the data to send into THR. Start conditionn DADDR and R/W bit are sent automatically */
		at91_twi_write (AT91_TWI_THR, *data++);
		limit = 0;
		while (!end)
		{
			udelay(10);
			status = at91_twi_read (AT91_TWI_SR);
			if ((status & AT91_TWI_NACK) == AT91_TWI_NACK)
			{
				error++;
				end=1;
			}

			/*  Wait for the Transmit ready is set */
			if ((status & AT91_TWI_TXRDY) == AT91_TWI_TXRDY)
				end=1;
 
			if (++limit > 10000)
			{
         	  		//pTwi->TWI_CR = AT91C_TWI_STOP;
			    	return 2;
			}
		}
	}

    /* Wait for the Transmit complete is set */
	status = at91_twi_read (AT91_TWI_SR);
	limit = 0;
	while (!(status & AT91_TWI_TXCOMP))
	{
		udelay(10);
		status = at91_twi_read (AT91_TWI_SR);
		if (++limit > 10000)
			return 2;
	}
	return error;
}

int Key_Read(char *data, int iaddr)
{
#if 1
	if (T11_TWI_WriteSingle(iaddr/*, AT91_MAX7347_I2C_ADDRESS*/))
		return -1;
	if (T11_TWI_ReadSingle(data))
		return -1;
#else
	while (T11_TWI_WriteSingle(iaddr/*, AT91_MAX7347_I2C_ADDRESS*/))
	{
		//AT91_TWI_Init (100000);
		mdelay(2);
	}
	while (T11_TWI_ReadSingle(data))
	{
		//AT91_TWI_Init (100000);
		mdelay(2);
	}
#endif
	return 0;
}

int Key_Write(char *data, int num)
{
#if 0
	while (T11_TWI_WriteMulti(data, num, AT91_MAX7347_I2C_ADDRESS))
		mdelay(2);
#else
	int retval;
	retval = T11_TWI_WriteMulti(data, num, AT91_MAX7347_I2C_ADDRESS);
#endif

	return retval;
}

/**************************************************************
 *
 * inline 函数
 *
 **************************************************************/

inline unsigned char raw2scancode (int num)
{
	pkeyb_dev->irkey = 0;
	switch (pkeyb_dev->irkey)
	{
		case 0:
			return num;
		case 1:
			return key_scan_map[num];
		case 2:
			return key_cook_map[num];
		default:
			return -1;
	}
}

inline int kbufin (U16 key)
{
	int temp;
#ifdef 	KEYB_DEBUG
	printk (KERN_ALERT"petowrm: keyb: kbufin is %x.\n", key);
#endif
	printk (KERN_ALERT"petowrm: keyb: kbufin is %x.\n", key);

	/* test the buf if full. */
	temp = pkeyb_dev->bufs +1;
	if (temp >= MAX_BUF_NUM)
	      temp -= MAX_BUF_NUM;	

	if(temp == pkeyb_dev->bufb)
		return 1;

	/* write the key to buf */
	pkeyb_dev->kbuf[pkeyb_dev->bufs] = key;
	if ((++pkeyb_dev->bufs) >= MAX_BUF_NUM)
	       pkeyb_dev->bufs -= MAX_BUF_NUM;
#ifdef KEYB_DEBUG
	printk (KERN_ALERT"petworm: kbuf top is %d\n", pkeyb_dev->bufs);
#endif
	return 0;
}

inline U16 readkey(void)
{
	U16 retch;

	if (pkeyb_dev->bufs == pkeyb_dev->bufb)
		return -1;
	retch = pkeyb_dev->kbuf[pkeyb_dev->bufb];
	if((++pkeyb_dev->bufb) >= MAX_BUF_NUM)
		pkeyb_dev->bufb = 0;
	return retch;
}

// Enable the TWI clock in PMC
inline void AT91_PMC_EnableTWIClock(void)
{
	at91_sys_write (AT91_PMC_PCER, 0x1 << 11);
}

inline void AT91_PMC_DisableTWIClock(void)
{
	at91_sys_write (AT91_PMC_PCDR, 0x1 << 11);
}

// Reset the TWI
inline void AT91_TWI_Reset(void)
{
	at91_twi_write (AT91_TWI_CR, AT91_TWI_SWRST);
}

// Configure the TWI
inline void AT91_TWI_Configure(void)
{
	at91_twi_write (AT91_TWI_IDR, 0xffffffff);

	at91_twi_write (AT91_TWI_CR, AT91_TWI_SWRST);

	at91_twi_write (AT91_TWI_CR, AT91_TWI_MSEN);
}

inline void AT91_TWI_SetClock (int t)
{
	int cdiv, ckdiv;

	/* get the system clk */
	struct clk *twi_clk;
	twi_clk = clk_get(NULL, "twi_clk");

	/* Calcuate clock dividers */
	cdiv = (clk_get_rate(twi_clk) / (2 * t)) - 3;
	cdiv = cdiv + 1;	/* round up */
	ckdiv = 0;
	while (cdiv > 255) 
	{
		ckdiv++;
		cdiv = cdiv >> 1;
	}

	if (ckdiv > 7) {
		printk(KERN_ERR "AT91 I2C: Invalid TWI clockrate!\n");
		ckdiv = 7;
	}
	at91_twi_write(AT91_TWI_CWGR, (ckdiv << 16) | (cdiv << 8) | cdiv);
}

void inline Keyb_beep (int time)
{
	at91_set_gpio_value (KEY_BP, 0);
	mdelay (time);
	at91_set_gpio_value (KEY_BP, 1);
}
//EXPORE_SYMBOL(Keyb_beep);

/* 键盘电源管理模块 */
static int __devinit at91_keyb_probe(struct platform_device *pdev)
{
	printk (KERN_ALERT "keyb probe resource is %x.\n", pdev->resource->start);
	return 0;
}

static int __devexit at91_keyb_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_PM
static int keyb_wakeup;
static int at91_keyb_suspend(struct platform_device *pdev, pm_message_t mesg)
{
	u8 ch[3] = {0};
	//printk ("petworm: keyb suspend.\n");
	
	/* set the keyb irq */
	if (!at91_suspend_entering_slow_clock ())
	{// standby
		enable_irq_wake(KEY_IRQ_ID);
		keyb_wakeup = 1;
	}
	else
	{// mem
		retval = 0;
		keyb_wakeup = 2;
		pkeyb_dev->is_sleep = 1;
		at91_set_gpio_value (KEY_BL, 1);

		ch[0] = 0x4;
		ch[1] = 0x00;
		Key_Write (ch, 2);
	}
	enable_irq_wake(POWER_IRQ_ID);

	return 0;
}

static int at91_keyb_resume(struct platform_device *pdev)
{
	char ch[3] = {0};
	//printk ("petworm: keyb resume.\n");
	/* set the keyb irq */
	if (keyb_wakeup == 1)
	{// standby
		disable_irq_wake(KEY_IRQ_ID);
	}
	else if (keyb_wakeup == 2)
	{// mem
		pkeyb_dev->is_sleep = 0;

		ch[0] = 0x4;
		ch[1] = 0x80;
		Key_Write (ch, 2);
	}
	disable_irq_wake(POWER_IRQ_ID);

	return 0;
}
#else
#define at91_keyb_suspend	NULL
#define at91_keyb_resume	NULL
#endif


#ifdef HAVE_8025_DEV
/*******************************************************************************
 *函数：读出时间日期星期的函数
 *参数：TIME ＊times ：用来存放时间日期星期的结构体
 *功能：调用8025芯片读寄存器的直存放在regs中：把对应的
 *		时间 日子 星期存放在结构体中对应的位置上，每次都读取两次，
 *		比较值是否相同，相同：返回，不相同：继续读，直到相同为止
 *返回直：h返回给被掉函数，判断读取成功与否。
********************************************************************************/
static int  get_8025_time(void)
{
	char rx8025_regs[16] = {0};
	int i, j;
	u32 read_err = 0;

	

	/* 读取时间数据 */
	for (i = 0; i < 10; i ++)
	{

		//T11_TWI_WriteSingle (0xf0, AT91_RX8025_I2C_ADDRESS);
		if (T11_TWI_ReadMulti (rx8025_regs, AT91_RX8025_I2C_ADDRESS))
		{
			read_err ++;
			mdelay (10);
			continue;
		}
		else
			read_err = 0;

		while (at91_twi_read (AT91_TWI_SR) & AT91_TWI_RXRDY)
			at91_twi_read (AT91_TWI_RHR);

		//printk (KERN_ALERT "8025 time read over.\n");

		/* judgement the data */
		for (j = 1; j < 8; j++)
		{
			if (IsBCDNum (rx8025_regs[j]))
				read_err ++;
		}

		//printk ("read_err is %x.\n", read_err);
		if (read_err)
			continue;

		read_err = 0;
		//printk (KERN_ALERT "8025 judgement over.\n");
		break;
	}

	while (at91_twi_read (AT91_TWI_SR) & AT91_TWI_RXRDY)
		at91_twi_read (AT91_TWI_RHR);

	if (read_err)
		return 1;


	//printk (KERN_ALERT "petworm: copy time data.\n");
	/* 对应位置存放 时间 */
	p8025_dev->time.hour = bcd_to_dec(rx8025_regs[3]);
	p8025_dev->time.min = bcd_to_dec(rx8025_regs[2]);
	p8025_dev->time.sec = bcd_to_dec(rx8025_regs[1]);

	/* 对应位置存放 日期 */
	p8025_dev->time.year = bcd_to_dec(rx8025_regs[7]);
	p8025_dev->time.year += RX8025_START_YEAR;
	p8025_dev->time.month = bcd_to_dec(rx8025_regs[6]);
	p8025_dev->time.day = bcd_to_dec(rx8025_regs[5]);

	/* 对应位置存放 星期 */
	p8025_dev->time.week = bcd_to_dec(rx8025_regs[4]);

/*
	printk("The time is %2x:%2x:%2x\n",p8025_dev->time.hour,p8025_dev->time.min,p8025_dev->time.sec);
	printk("The date is %2x-%2x-%2x\n",p8025_dev->time.year,p8025_dev->time.month,p8025_dev->time.day);
	printk("The week is %2x\n",p8025_dev->time.week);
*/
	return 0;
}

#define LEAPS_THRU_END_OF(y) ((y)/4 - (y)/100 + (y)/400)
#define LEAP_YEAR(year) ((!(year % 4) && (year % 100)) || !(year % 400))
static days_of_mouth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static s32 GetWeek(s32 year, s32 month, s32 day)
{
    long  i;
    i=1461*(long)(month<=2?year-1:year)/4+153*(long)(month<=2?month+13:month+1)/5+day;
    return (s32)((i-621049)%7);
}

static int check_time(struct rx_8025_time *time_buf)
{
	int ret = 0;
	unsigned int days = 0;
	int weekstar = 1;
	int i;

	if (time_buf->sec > 59)
		ret |= 0x1;
	if (time_buf->min > 59)
		ret |= 0x2;
	if (time_buf->hour > 24)
		ret |= 0x4;
/*
	if (time_buf->week > 6)
		ret |= 0x8;
*/
	if (time_buf->day > 31)
		ret |= 0x10;
	if (time_buf->month > 11)
		ret |= 0x20;
	if (time_buf->year < 1990 || time_buf->year > 2089)
		ret |= 0x40;

	/* calculate the week day */
#if 0
	for (i = 1990; i <= time_buf->year; i++)
	{
		days += 365 + LEAP_YEAR(i);
	}
	for (i = 0; i < time_buf->month - 1; i++)
	{
		if (time_buf->month == 1)
			days += days_of_mouth [i] + LEAP_YEAR(time_buf->year);
		else
			days += days_of_mouth [i];
	}
	days += time_buf->day;

	time_buf->week = (days % 7) + weekstar;
#else
	if (!ret)
		time_buf->week = GetWeek(time_buf->year, time_buf->month, time_buf->day);
#endif
	
/*
	printk (KERN_ALERT "petworm: otm:%4d-%2d-%2d %2d:%2d:%2d %d\n", time_buf->year,
			time_buf->month, time_buf->day, time_buf->hour,
			time_buf->min, time_buf->sec, time_buf->week);
*/
	return ret;
}

static int change_time(struct rx_8025_time *time_buf)
{

	time_buf->sec = dec_to_bcd(time_buf->sec);
	time_buf->min = dec_to_bcd(time_buf->min);
	time_buf->hour = dec_to_bcd(time_buf->hour);
	time_buf->day = dec_to_bcd(time_buf->day);
	time_buf->month = dec_to_bcd(time_buf->month);
	time_buf->year = dec_to_bcd(time_buf->year -= RX8025_START_YEAR);

	return 0;
}

static int update_8025(struct rx_8025_time *time_buf)
{
	u8 ch[2];
	u32 tmp[7];
	int i;

	tmp[0] = time_buf->sec;
	tmp[1] = time_buf->min;
	tmp[2] = time_buf->hour;
	tmp[3] = time_buf->week;
	tmp[4] = time_buf->day;
	tmp[5] = time_buf->month;
	tmp[6] = time_buf->year;

	for (i = 0; i < 7; i++)
	{
		ch[0] = i << 4;
		ch[1] = (u8) tmp[i];
		T11_TWI_WriteMulti (ch, 2, AT91_RX8025_I2C_ADDRESS);
	}

	return 0;
}

static u8 dec_to_bcd(u8 data)
{
	u8 temp;
	
	temp = data/10;
	temp = temp <<4;
	temp += data%10;

	return temp;
	
}

static u8 bcd_to_dec(u8 data)
{
	u8 temp;
	
	temp = data / 16;
	temp *= 10;
	temp += data % 16;
	
	return temp;
}

static u8 num_to_bcd (u32 data)
{
	u8 bcd = 0;
	u8 tmp;

	tmp = data % 10;
	bcd |= tmp;
	tmp = (int) (data / 10);
	bcd |= tmp << 4;

	//printk (KERN_ALERT "8025: num_to_bcd return %x.\n", bcd);
	return bcd;
}

static inline int IsBCDNum(u8 data)
{
	int ret = 0;

	if ((data & 0x0F) > 0x09)
		ret ++;

	if ((data & 0xF0) > 0x90)
		ret ++;

	//printk (KERN_ALERT "petworm: IsBCDNum %x - %x\n", data, ret);
	return ret;
}

#else
static int get_8025_time (void){}
static int check_time(struct rx_8025_time *time_buf){}
static int change_time(struct rx_8025_time *time_buf){}
static u8 num_to_bcd (u32 data){}
static int update_8025(struct rx_8025_time *time_buf){}
#endif
