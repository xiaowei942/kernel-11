#include <linux/kernel.h>	    /* We're doing kernel work */
#include <linux/module.h>	    /* Specifically, a module */
#include <linux/sched.h>
#include <linux/init.h>		/* Needed for the macros */
#include <linux/interrupt.h>	/* We want an interrupt */
#include <linux/cdev.h>
#include <asm/io.h>
#include <linux/delay.h>      /*Needed for udelay(),mdelay()*/
#include <linux/irq.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/unistd.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/arch/gpio.h>
#include <linux/platform_device.h>

#include <linux/sched.h>
#include <asm/arch/board.h>
#include <linux/ioctl.h>
#include <asm/arch/at91_pmc.h>

#include <linux/ext_fun.h>

#define LOW_POWER_WARNING	1

#define T11_CHARGE_IRQ_ID	AT91_PIN_PA24
#define T11_LOW_POWER_WARNING	AT91_PIN_PA14

#define CHARGE_MAJOR		101
#define CHARGE_MINOR		0

#define CHARGE_INIT		_IO(CHARGE_MAJOR, 0)
#define CHARGE_OPNE_IRQ		_IO(CHARGE_MAJOR, 1)
#define CHARGE_CLOSE_IRQ	_IO(CHARGE_MAJOR, 2)
#define CHARGE_STATE_GET	_IO(CHARGE_MAJOR, 3)
#define BATTERY_STATE_GET	_IO(CHARGE_MAJOR, 4)
#define LOWPWR_INIT		_IO(CHARGE_MAJOR, 5)
#define LOW_POWER_GET		_IO(CHARGE_MAJOR, 6)


static struct cdev	*charge_cdev;
static dev_t 		charge_dev;

/* 当前充电状态 1 - 充 0 - 断 */
static u8		charge_state = 0;

static u8		is_irq_register = 0;


static irqreturn_t T11_charge_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs);
static irqreturn_t T11_low_power_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs);


unsigned char get_charge_state(void)
{
	return charge_state;
}
EXPORT_SYMBOL (get_charge_state);



u8 get_pio_state(u32 pin, u32 val)
{
	int temp;
	int i;

retest_pio_stat:
	temp = 0; i = 3;

	do{
		if (at91_get_gpio_value(pin) == val)
			temp += 1;
		mdelay(20);
	}while(--i);

	if (temp == 3)
		return 1;
	else if (temp == 0)
		return 0;
	else
		goto retest_pio_stat;
}

static void send_signal (u32 data)
{
	int have_guicmd = 0;
	struct task_struct *p, *pchild1, *pchild2;
	struct task_struct *psig1, *psig2, *psig3;
	struct list_head *list1, *list2;
	//printk (KERN_ALERT "rtt tasklet.\n");
	printk (KERN_ALERT "charge_tasklet_func: data is %x.\n", data);


	read_lock(&tasklist_lock);
	p=&init_task;

	for_each_process(p)
	{// 一级子进程
		//printk ("%d: %s parent is %d; status is: %x; flags is %x.\n", p->pid, p->comm, p->parent->pid, p->state, p->flags);
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

	//printk (KERN_ALERT "petworm: have_guicmd is %x.\n", have_guicmd);
	if (have_guicmd & 0x4)
		send_sig(data, psig3, 1);
	else if (have_guicmd & 0x2)
		send_sig(data, psig2, 1);
	else if (have_guicmd & 0x1)
		send_sig(data, psig1, 1);

	read_unlock(&tasklist_lock);
}

void charge_tasklet_func (void)
{
	send_signal (ZZCHARGE);
}

void low_power_tasklet_func (void)
{
	send_signal (ZZLOWPWR);
}

/********************************************************
 *
 *
 *
 *******************************************************/
static int charge_open(struct inode *pinode, struct file *pfile)
{
	return 0;
}


/********************************************************
 * 
 *******************************************************/
static ssize_t charge_read(struct file *p_file, char __user *buf, 
			ssize_t count, loff_t *p_pos)
{
#if 0
	unsigned int count1 = 0;	
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi read .....\n");	
#endif


	while((count1++ < 5) && (spi_readdata()));

	if(count1 > 5)			
	{
		printk(KERN_ALERT"Mzm: TIME OUT \n");
	
		kbuf = 0;
		
		put_user(return_value,(int*)buf);
		return 1;
	}
	
	return_value = values(kbuf);

	put_user(return_value,(int*)buf);
	
	kbuf = 0;

#ifdef ADC
	printk(KERN_ALERT"Mzm: Copy_to_user is over\n");
#endif
#endif
	return 0;
}


/*******************************************************
 * 函数：
 * 功能：
 * 参数：
 ********************************************************/
static int charge_ioctl(struct inode *p_inode, struct file *p_file, 
			unsigned int cmd, unsigned long arg)
{
	u8 ret;
	u32 *pioa;

	switch (cmd)
	{
		case CHARGE_INIT:
			charge_state = get_pio_state (AT91_PIN_PA24, 1);

			if (copy_to_user ((void *)arg, (void *) &charge_state, 1))
				printk (KERN_ALERT "charge state get error\n");

			if (!(is_irq_register & 0xf))
			{
				// change wire irq
				if (request_irq(T11_CHARGE_IRQ_ID, T11_charge_interrputs, IRQ_TYPE_EDGE_BOTH | IRQF_DISABLED, "charge_wire", NULL))
					printk (KERN_ALERT"power key irq error\n");

				is_irq_register |= 1;
			}

			enable_irq_wake(T11_CHARGE_IRQ_ID);
			break;
		case LOWPWR_INIT:
			ret = get_pio_state (AT91_PIN_PA14, 0);

			if (copy_to_user ((void *)arg, (void *) &ret, 1))
				printk (KERN_ALERT "charge state get error\n");

			if (!(is_irq_register & 0xf0))
			{
				// low power warning irq
				if (request_irq(T11_LOW_POWER_WARNING, T11_low_power_interrputs, IRQ_TYPE_EDGE_BOTH, "low_power", NULL))
					printk (KERN_ALERT"low power warning irq error\n");

				is_irq_register |= 0x10;
			}
			break;

		case CHARGE_OPNE_IRQ:
			//at91_set_gpio_irq (AT91_PIN_PA24, 1);
			enable_irq (T11_CHARGE_IRQ_ID);
			break;
		case CHARGE_CLOSE_IRQ:
			disable_irq (T11_CHARGE_IRQ_ID);
			//at91_set_gpio_input (AT91_PIN_PA24, 1);
			break;
		case CHARGE_STATE_GET:
			charge_state = get_pio_state (AT91_PIN_PA24, 1);

			if (copy_to_user ((void *)arg, (void *) &charge_state, 1))
				printk (KERN_ALERT "charge state get error\n");
			break;
		case BATTERY_STATE_GET:
			if (charge_state)
			{
				/* 0 - 充, 1 - 满 */
				ret = get_pio_state (AT91_PIN_PB10, 1);
			}
			else
				ret = -1;
			if (copy_to_user ((void *)arg, (void *) &ret, 1))
				printk (KERN_ALERT "battery state get error\n");
			break;

		case LOW_POWER_GET:
			ret = get_pio_state (AT91_PIN_PA14, 0);
#if 0
			if (!charge_state)
			{
				if (get_pio_state (AT91_PIN_PA14, 1))
					enable_irq(T11_LOW_POWER_WARNING);
				else
					charge_state = 1;
			}
			//charge_state = 1; // Santiage test low power status
#endif
			if (copy_to_user ((void *)arg, (void *) &ret, 1))
				printk (KERN_ALERT "charge state get error\n");
			break;

		default:
			return -EINVAL;
	}
	return 0;
}

static int charge_release(struct inode *p_inode, struct file *p_file)
{
	//spi_read_disable();
	return 0;
}


/*****************************************************************
 *
 * 充电模块操作结构体
 *
 ****************************************************************/
static struct file_operations charge_fops =
{
	.owner = THIS_MODULE,
	.read = charge_read,
	.ioctl = charge_ioctl,
	.open = charge_open,
	.release = charge_release,
};



/******************************************************************
 *  shutdwon charge interrupt function
 ******************************************************************/
DECLARE_TASKLET (charge_tasklet, charge_tasklet_func, NULL);
static irqreturn_t T11_charge_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	printk (KERN_ALERT "battery charge interrupt\n");

	disable_irq (T11_CHARGE_IRQ_ID);
	//at91_set_gpio_input (AT91_PIN_PA24, 1);

	charge_state = get_pio_state (AT91_PIN_PA24, 1);

	enable_irq (T11_CHARGE_IRQ_ID);

	tasklet_schedule (&charge_tasklet);

	return IRQ_HANDLED;	
}

#ifdef LOW_POWER_WARNING
/******************************************************************
 *  low power warning interrupt function
 ******************************************************************/
DECLARE_TASKLET (low_power_tasklet, low_power_tasklet_func, NULL);
static int low_power_status = 0;
static irqreturn_t T11_low_power_interrputs (int irq, void *dev_id, 
					struct pt_regs *regs)
{
	int ret;
	printk (KERN_ALERT "low power warning.\n");

	disable_irq (T11_LOW_POWER_WARNING);
	//at91_set_gpio_input (AT91_PIN_PA24, 1);

#if 0
	if (!get_pio_state (AT91_PIN_PA14, 0))
	{
		enable_irq (T11_LOW_POWER_WARNING);
	}
	else
	{
		tasklet_schedule (&low_power_tasklet);
	}
#else
	ret = get_pio_state (AT91_PIN_PA14, 0);
	if (ret != low_power_status)
	{
		low_power_status = ret;
		tasklet_schedule (&low_power_tasklet);
	}
	enable_irq (T11_LOW_POWER_WARNING);
#endif

	return IRQ_HANDLED;
}
#endif

static int __init T11_charge_init(void)
{
	int ret, err;
	unsigned int charge_major = CHARGE_MAJOR, charge_minor = CHARGE_MINOR;


	printk (KERN_ALERT "init charge mode.\n");

	if (charge_major) {
	 	charge_dev = MKDEV(charge_major, charge_minor);
	 	ret = register_chrdev_region(charge_dev, 1, "charge");
	} else {
		ret = alloc_chrdev_region(&charge_dev, charge_minor, 1, "charge");
		charge_major = MAJOR(charge_dev);
	}
	if (ret < 0) {
	 	printk(KERN_WARNING "scull: can't get charge major %d\n", ret);
	 	return ret;
	}

	/* 为cdev结构体分配内存空间 */
	charge_cdev = cdev_alloc();

	// 为电池设备进行kcdev注册
	cdev_init(charge_cdev, &charge_fops);
	charge_cdev->owner = THIS_MODULE;
	charge_cdev->ops = &charge_fops;
	err = cdev_add(charge_cdev, charge_dev, 1);
	if (err)
	{
		printk(KERN_NOTICE "Error %d charge mode drivce.\n", err);
		goto fail_init;
	}

	/* set the PA24 as irq port */
	at91_set_gpio_input (AT91_PIN_PA24, 0);
	at91_set_deglitch (AT91_PIN_PA24, 1);

#ifdef LOW_POWER_WARNING
	/* set the PA14 as irq port */
	at91_set_gpio_input (AT91_PIN_PA14, 0);
	at91_set_deglitch (AT91_PIN_PA14, 1);
#endif

	return 0;

fail_init:
	printk (KERN_ALERT "charge mode failed to init.\n");
	return -1;
}

static int __exit T11_charge_exit(void)
{
	printk (KERN_ALERT "exit charge mode.\n");

	/* 释放中断号 */
	disable_irq(T11_CHARGE_IRQ_ID);
	free_irq(T11_CHARGE_IRQ_ID, NULL);

	/* 释放低电压报警中断 */
	disable_irq(T11_LOW_POWER_WARNING);
	free_irq(T11_LOW_POWER_WARNING, NULL);

	/* 释放文件指针 */
	cdev_del(charge_cdev);	/*释放kcdev*/
	/*释放设备号*/
	unregister_chrdev_region (charge_dev, 1);

	return 0;
}

MODULE_AUTHOR("Petworm");
MODULE_LICENSE("Dual BSD/GPL");

module_init(T11_charge_init);
module_exit(T11_charge_exit);



#if 0
/* 读电池电压 */

int values(int  k)
{
	int value;
	

	//value = ( (k * 330 * 2/ 16/255);
	value = k>>4;
	value += 3;
#ifdef ADC
	printk(KERN_ALERT"Mzm: The value is %d \n",value);
#endif	
	value = value*330*2;
	//value = value>>4; 
	value = value>>8;
	
	
	return value;
}


int spi_config()
{
	int tmp;
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi_config.... \n");
#endif
#if 0
	paddr = ioremap(AT91A_PMC_PCER, 4);
	*paddr |= ((0x1<<2)|(0x1<<3)|(0x1<<12));
	iounmap(paddr);

#else
	at91_sys_write (AT91_PMC_PCER, (0x1<<2)|(0x1<<3)|(0x1<<12));
#endif

	paddr = ioremap(0xfffff400, 0xA8);
#if 1
		
	tmp = 0 ;
	for(tmp=0;tmp<200000;tmp++);


	*(paddr+(0x74>>2)) = AT91C_PA27_SPI0_NPCS1;

	*(paddr+(0x70>>2)) = ((AT91C_PA0_SPI0_MISO )|(AT91C_PA2_SPI0_SPCK  )|(AT91C_PA1_SPI0_MOSI));
	
	*(paddr+1) = ((AT91C_PA0_SPI0_MISO )|(AT91C_PA2_SPI0_SPCK  )|(AT91C_PA1_SPI0_MOSI)| AT91C_PA27_SPI0_NPCS1);
#endif
	iounmap(paddr);

#if 0
	paddr = ioremap(AT91A_SPI0_CR,4);	
	*paddr |=  AT91_SPI_RESTART;
	iounmap(paddr);
#else
	at91_sys_write (AT91A_SPI0_CR, AT91_SPI_RESTART);
#endif
	
#if 0
	paddr = ioremap(AT91A_SPI0_MR,4);
	*paddr = AT91_SPI_NPCS_MASTER;	
	iounmap(paddr);
#else
	at91_sys_write (AT91A_SPI0_MR, AT91_SPI_NPCS_MASTER);
#endif
	
#if 0
	paddr = ioremap(AT91A_SPI0_CSR1,4);
	*paddr = (0x3 | (AT91C_SPI_DLYBS & (ADC_DLYS)) | (AT91C_SPI_DLYBCT & DATAFLASH_TCHS) | (0x30 << 8)| (0x7 << 4));
	iounmap(paddr);
#else
	at91_sys_write (AT91A_SPI0_CSR1, 0x3 | AT91_SPI_DLYBS | (AT91_SPI_DLYBCT & (0x1 << 24)) | (0x30 << 8)| (0x7 << 4));
#endif
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi_config is OK \n");
#endif
	return 0;
}

void spi_read_enable(void)
{
	spi_config();
#if 0
	paddr = ioremap(AT91A_SPI0_CR,4);	
	*paddr |=  AT91_SPI_ENABLE;
	iounmap(paddr);
#else
	at91_sys_write (AT91A_SPI0_CR, AT91_SPI_ENABLE);
#endif

	paddr = ioremap(PIOB_PB26_BASE,0xa8);
	*paddr = PB26;
	*(paddr +(0x10>>2)) = PB26;
	*(paddr +(0x30>>2)) = PB26;
	iounmap(paddr);

	mdelay(1);

#if 0
	paddr = ioremap(AT91A_SPI0_TDR,4);	
	*paddr |=  0x000D5555;
	//mdelay(2);
	iounmap(paddr);
#else
	at91_sys_write (AT91A_SPI0_TDR, 0x000D5555);
#endif
}

void spi_read_disable(void)
{
#if 1
	paddr = ioremap(AT91A_SPI0_SR,4);
	*paddr |=0x02; 
	iounmap(paddr);
#endif
	paddr = ioremap(PIOB_PB26_BASE,0xa8);

	*paddr = PB26;
	*(paddr +(0x10>>2)) = PB26;
	*(paddr +(0x34>>2)) = PB26;

	iounmap(paddr);


}


int	spi_readdata(void)
{
	spi_read_enable();

	paddr = ioremap(AT91A_SPI0_SR,4);
	while(!((*paddr) & 0x1));

	iounmap(paddr);

	paddr = ioremap(AT91A_SPI0_RDR,4);
	kbuf = (int)(*(paddr) & 0xffff);
 	iounmap(paddr);
	
	if((kbuf & 0xf00f) || (kbuf == 0xff0))
	{
#ifdef ADC
		printk(KERN_ALERT"Mzm: Read data error \n");
#endif
		return 1;
	}
#ifdef	ADC
	printk(KERN_ALERT"Mzm: The number is 0x%x \n",kbuf);	
#endif
	return 0;
}
#endif

