#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>	/* for put_user */
#include <asm/io.h>
//#include <asm/delay.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/at91sam9261_matrix.h>
#include <asm/page.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include "t11_fb_hx8347.h"


/* Global variables are declared as static, so are global within the file. */
static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open?  				 * Used to prevent multiple access to device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.ioctl = device_ioctl,
	.release = device_release,
    	.mmap = device_mmap
};

#ifdef OLD_FB
unsigned short int *graphicMem[38];
#else
volatile u16 *graphicMem;
//dma_addr_t memaddr;
#endif

volatile u16 *command_port;
volatile u16 *data_port;

static int auto_flush_sign = 0;		/* fb auto flush sing */
					/* 0 - 关， 1 - 开 */
#ifdef T11_AUTO_FLUSH_TIMETASK
static struct timer_list flush_timer;

static void auto_flush_timer (void)
{
	//printk (KERN_ALERT "petworm: flush all screen.\n");
	Flash_Frame();
	flush_timer.expires = jiffies + FLUSH_TIME;
	add_timer(&flush_timer);
}
#endif

#ifdef T11_AUTO_FLUSH_KTHREAD
static struct task_struct *p_fb_thread = 0;
static wait_queue_head_t fb_event;
static wait_queue_head_t fb_write;
static int thread_wait_time = 10;	// normal: 80ms
					// movie:  40ms/50ms(20f/s 25f/s)
static spinlock_t fb_lock;
static int fb_mode = 0;
static MFA fb_addr = {0};

static void movie_flush (void);

static int framebuffer_thread (void *data)
{
	while (!kthread_should_stop () && auto_flush_sign)
	{
		//printk ("------------------->fb thread<-----------------------\n");

		wait_event_interruptible_timeout (fb_event, NULL/*kthread_should_stop() || !auto_flush_sign*/, thread_wait_time);


		//printk (" wait condition is %x.\n", kthread_should_stop() || !auto_flush_sign);
		if (!auto_flush_sign)
			continue;

		spin_lock_irq (&fb_lock);
		if (fb_mode)
			movie_flush ();
		else
			Flash_Frame ();
		spin_unlock_irq (&fb_lock);
	}
	return 0;
}
#endif

int init_fb_module(void){
	Major = register_chrdev(FB_MAJOR, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk("FrameBuffer: Registering the character device failed with %d\n", Major);
		return Major;
	}
	printk("<1>FrameBuffer major number %d.\n", FB_MAJOR);

	Lcd_Init();

#ifdef T11_AUTO_FLUSH_TIMETASK
	/* init auto flush timer */
	init_timer (&flush_timer);
	flush_timer.function = auto_flush_timer;
	flush_timer.expires = jiffies + FLUSH_TIME;
#endif

#ifdef T11_AUTO_FLUSH_KTHREAD
	init_waitqueue_head (&fb_event);
	init_waitqueue_head (&fb_write);
	spin_lock_init (&fb_lock);
	thread_wait_time = FLUSH_TIME;
#endif

#if 0	/* petowrm off */
	Rectangle(0, 0, HORIZONTAL, VERTICAL, 0XFFFF);
	Mop(0, 0, HORIZONTAL / 2, VERTICAL / 2, 0);
#endif
	return 0;
}

void cleanup_fb_module(void){
//	int ret;
	unregister_chrdev(Major, DEVICE_NAME);
//	if (ret < 0)
//		printk("Error in unregister_chrdev: %d\n", ret);
}

module_init(init_fb_module);
module_exit(cleanup_fb_module);

#ifdef OLD_FB
struct page *ili9320_vma_nopage(struct vm_area_struct *vma, unsigned long address, int *type)
{
	unsigned int offset;
	struct page *page = NOPAGE_SIGBUS;
	void *pageptr = NULL;

	offset = (address - vma->vm_start) + (vma->vm_pgoff << PAGE_SHIFT);
	//printk(KERN_ALERT"offset count: %x\n", offset);


	offset >>= PAGE_SHIFT;
	pageptr = graphicMem[offset];
	//printk(KERN_ALERT"offset page: %x\n", offset);


	page = virt_to_page(pageptr);
	get_page(page);

	if(type)
		*type = VM_FAULT_MINOR;

out:
	//printk(KERN_ALERT"get out\n");
	return page;
}

void ili9320_vma_open(struct vm_area_struct *vma)
{
	//printk(KERN_ALERT"fb_vma_open\n");

	return;
}

void ili9320_vma_close(struct vm_area_struct *vma)
{
	//printk(KERN_ALERT"fb_vma_close\n");

	return;
}

static struct vm_operations_struct ili9320_vm_ops = {
	.open = ili9320_vma_open,
	.close = ili9320_vma_close,
	.nopage = ili9320_vma_nopage
};
#endif

static int device_mmap(struct file *filp, struct vm_area_struct *vma)
{
#ifndef OLD_FB
	printk (KERN_ALERT "petworm: fb: 1.vm_page_prot is %x.\n", vma->vm_page_prot);
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = (virt_to_phys(graphicMem) >> PAGE_SHIFT);
	vma->vm_flags |= VM_RESERVED;
	printk (KERN_ALERT "petworm: fb: 2.vm_page_prot is %x.\n", vma->vm_page_prot);
	printk (KERN_ALERT "petworm: vm_start is %x, vm_end is %x.\n", vma->vm_start, vma->vm_end);
	printk (KERN_ALERT "petworm: vm_pgoff is %x.\n", vma->vm_pgoff);
	if(remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, vma->vm_end - vma->vm_start, vma->vm_page_prot))
		return -EAGAIN;

	printk("<1>mmap has been run over!\n");
#else
	vma->vm_ops = &ili9320_vm_ops;
	vma->vm_flags |= VM_RESERVED;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	//vma->vm_private_data = filp->private_data;
#endif
	return 0;
}

/* * Methods */

/*  * Called when a process tries to open the device file, like * "cat /dev/mycharfile" */
static int device_open(struct inode *inode, struct file *file){

	static int counter = 0;

	if (Device_Open > 4)
		return -EBUSY;
	Device_Open++;
	/*
	   if (*graphicMem == 0 && *(graphicMem + 340) == 0 && *(graphicMem + 560))
	   printk (KERN_ALERT "petworm: graphic clean.\n");
	   */

#if 0
	unsigned int *p;
	/* 打开背光 */
	p = ioremap(0xfffff600,0x40);
	*p |= 0x1000;
	*(p+(0x10>>2)) |= 0x1000;
	*(p+(0x30>>2)) |= 0x1000;
	iounmap(p);
#endif
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

/*  * Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file){
	Device_Open--;
	/* We're now ready for our next caller */
	/*
	 * Decrement the usage count, or else once you opened the file, you'll 
	 * never get get rid of the module.
	 */
	module_put(THIS_MODULE);
	return 0;
}

/*  * Called when a process, which already opened the dev file, attempts to * read from it. */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
		char *buffer,	/* buffer to fill with data */
		size_t length,	/* length of the buffer     */
		loff_t * offset){
	/*
	 * Number of bytes actually written to the buffer
	 */
	int bytes_read = 0;
	/*
	 * If we're at the end of the message,
	 * return 0 signifying end of file
	 */
	if (*msg_Ptr == 0)
		return 0;
	/*
	 * Actually put the data into the buffer
	 */
	while (length && *msg_Ptr) {
		/*
		 * The buffer is in the user data segment, not the kernel
		 * segment so "*" assignment won't work.  We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment.
		 */
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read++;
	}
	/*
	 * Most read functions return the number of bytes put into the buffer
	 */
	return bytes_read;
}
/*
 * Called when a process writes to dev file: echo "hi" > /dev/hello
 */
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
#if 0
	printk (KERN_ALERT "petworm: fb write.\n");
 	Flash_Frame();
	return -EINVAL;
#else

	if (!fb_mode)
		return -1;

retry:
	printk ("fb: fb write: %x\t%x\t%x.\n", fb_mode, fb_addr.write_sign, fb_addr.sign[fb_addr.write_sign]);

	if (atomic_read(&fb_addr.sign[fb_addr.write_sign]) == 0/*fb_addr.sign[fb_addr.write_sign] == 0*/)
	{
		if (copy_from_user ((void *) fb_addr.fb_buf[fb_addr.write_sign], (void *) buff, 153600))
			return -EIO;

		//fb_addr.sign[fb_addr.write_sign] = 1;
		atomic_set (&fb_addr.sign[fb_addr.write_sign], 1);
		fb_addr.write_sign = !fb_addr.write_sign;
	}
	else
	{
#if 0
		wait_event_interruptible_timeout (fb_write, NULL/*kthread_should_stop() || !auto_flush_sign*/, thread_wait_time * 2 - thread_wait_time / 2);
		//wait_event_interruptible (fb_write, !atomic_read (&fb_addr.sign[fb_addr.write_sign]));

		goto retry;
#else
		return -EBUSY;
#endif
	}

	return 0;
#endif
}

/**********************************************************************************************
*	函数：	驱动控制函数
*	功能：	用来被对应用户程序的ioctl（）函数，主要通过处理用户测试程序传过来的参数，
*		主要调用print（）函数进行lcd要显示的位置，大小，颜色等设置，实现液晶的显示。
*	参数：	 unsigned int cmd；用户传过来的各种参数，用于被ioctl分析。
*	返回之:	自带
************************************************************************************************/
static int device_ioctl(struct inode *inode, struct file *filp, 
				unsigned int cmd, unsigned long arg)
{
	FDC  fbdc;
	u16   flush_num = 0;
	u8    tmp;

#if 0
	printk (KERN_ALERT "fbdev: cmd is %x, arg is %x.\n", cmd, arg);
#endif
	//printk ("petworm: auto_flush_sign is %x.\n", auto_flush_sign);
	switch(cmd)
	{
		case IOCTL_FLUSH:
			if (auto_flush_sign)
				break;
			if(copy_from_user((void *) &fbdc, (void *)arg, FDCLEN))
			{
				printk("Copy_from_user: Error\n");
				return -EIO;
			}

			//printk (KERN_ALERT "fdc is (%d,%d),(%d,%d)\n", fbdc.x1, fbdc.y1, fbdc.x2, fbdc.y2);

			/* 调用 显示函数 */
			FlushRect(fbdc.x1,fbdc.x2,fbdc.y1,fbdc.y2);
			break;

		case AUTO_FLUSH_ON:
			if (auto_flush_sign)
				break;
			auto_flush_sign = 1;
#ifdef T11_AUTO_FLUSH_TIMETASK
			add_timer(&flush_timer);
#endif
#ifdef T11_AUTO_FLUSH_KTHREAD
			p_fb_thread = kthread_create (framebuffer_thread, NULL,"fb0", NULL);
			if (IS_ERR(p_fb_thread))
			{
				printk (KERN_ALERT "framebuffer flush thread creat failed.\n");
				auto_flush_sign = 0;
				p_fb_thread = NULL;
			}
			else
				wake_up_process (p_fb_thread);
#endif
			break;
		case AUTO_FLUSH_OFF:
			if (!auto_flush_sign)
				break;
			auto_flush_sign = 0;
#ifdef T11_AUTO_FLUSH_TIMETASK
			del_timer(&flush_timer);
#endif
#ifdef T11_AUTO_FLUSH_KTHREAD
			mdelay (20);
			kthread_stop (p_fb_thread);
			p_fb_thread = NULL;
#endif
			break;

		case AUTO_FLUSH_NUM:
			printk (">>>>>>>>>>>>>>>>>>>>lcd flush num<<<<<<<<<<<<<<<<<\n");
			if (!auto_flush_sign)
				break;

			if (copy_from_user ((void *) &flush_num, (void *) arg, 2))
			{
				return -EIO;
			}

			printk ("fb display freqency is %x.\n", flush_num);

			if ((flush_num != T11_FLUSH_8) && (flush_num != T11_FlUSH_5) && (flush_num != T11_FLUSH_4))
			{
				printk ("fb: argment error.\n");
				return -EINVAL;
			}
			else
			{
				printk (KERN_ALERT "kernel: lcd flush num is %d.\n", flush_num & 0xf);
				thread_wait_time = flush_num & 0xf;
			}

			mdelay (thread_wait_time * 10);
			break;

		case SHIFT_DISPLAY_MODE:

			if (!auto_flush_sign)
				break;

			if (copy_from_user ((void *) &flush_num, (void *) arg, 2))
			{
				return -EIO;
			}

			printk ("fb display mode is %x.\n", flush_num);

			if ((flush_num != T11_FLUSH_NORMAL) && (flush_num != T11_FLUSH_MOIVE))
			{
				printk ("fb: argment error.\n");
				return -EINVAL;
			}
			else
				flush_num = flush_num & 0xf;

			printk (KERN_ALERT "kernel: lcd display mode is %d.\n", flush_num);

			if ((flush_num == 0) && (fb_mode == 1))
			{// exit movie play mode
				fb_mode = 0;
				free_page (fb_addr.fb_buf[0]);
				free_page (fb_addr.fb_buf[1]);
			}

			if ((flush_num == 1) && (fb_mode == 0))
			{
				//fb_addr.sign[0] = ATOMIC_INIT(0);
				atomic_set (&fb_addr.sign[0],0);
retry_1:
				fb_addr.fb_buf[0] = (u16 *) __get_free_pages(GFP_KERNEL, 6);
				if (fb_addr.fb_buf[0] == NULL)
				{
					printk ("fb: fb_buf[0] malloc failed.\n");
					goto retry_1;
				}

				//fb_addr.sign[1] = ATOMIC_INIT(0);
				atomic_set (&fb_addr.sign[1],0);
retry_2:
				fb_addr.fb_buf[1] = (u16 *) __get_free_pages(GFP_KERNEL, 6);
				if (fb_addr.fb_buf[1] == NULL)
				{
					printk ("fb: fb_buf[1] malloc failed.\n");
					goto retry_2;
				}

				fb_addr.write_sign = 0;
				fb_addr.read_sign = 0;

				fb_mode = 1;
			}

			break;

		case ROTATE_FRAMEBUFFER:
			if (copy_from_user ((void *) &tmp, (void *) arg, 1))
			{
				return -EIO;
			}

			if (tmp & 0xfe)
				return -EINVAL;
#ifdef HX8347D_LCD
			if (tmp)
				flush_num = 0xa0;
			else
				flush_num = 0x00;

			MainLCD_Command (0x0016), MainLCD_Data (flush_num);
#else
			flush_num = 0x1210;	// 0x3 read error
			if (tmp)
				flush_num = 0x1228;
			else
				flush_num = 0x1210;

			MainLCD_Command(0x0003);MainLCD_Data(flush_num);
#endif
			break;
#if 0
		case ROTATE_SCREEN:
			if (copy_from_user ((void *) &tmp, (void *) arg, 1))
			{
				return -EIO;
			}

			if (tmp & 0xfc)
				return -EINVAL;

			MainLCD_Command (0x0003);
			flush_num = MainLCD_Read();

			flush_num &= ~(0x30);
			flush_num |= tmp << 4;
			MainLCD_Command(0x0003);MainLCD_Data(flush_num);
			break;
#endif
		default:
			return -ENOIOCTLCMD;

	}
	return 0;
}

void Delayms(unsigned int time)
{
	udelay (time * 1000);
}

inline void
MainLCD_Command(u16 tft_command)
{
	*command_port = tft_command;
	//Delayus(10);
}

inline void
MainLCD_Data(u16 tft_data)
{
	*data_port = tft_data;
	//Delayus(10);
}

inline unsigned short
MainLCD_Read(u8 *ret)
{
	return (*ret = *data_port);
}

void Lcd_Init(void)
{
	unsigned int *p;
	int i;
	struct page *page;

	/* ioremap for lcd user interface */
	command_port = ioremap(0x60000000, 2);
	data_port = ioremap(0x60000004, 2);

#ifdef OLD_FB 
	for(i = 0; i < 38; i++)
	{
		graphicMem[i] = (unsigned short int *)__get_free_page(GFP_KERNEL);
		page = virt_to_page (graphicMem[i]);
		SetPageReserved (page);
	}
#else
        //ioremap (0x4100000, 2);	????????????????????/petworm 

	/* allocate buffer memory */
	graphicMem = (unsigned short int *)__get_free_pages(GFP_HIGHUSER, 6);
	printk (KERN_ALERT "petworm: graphicMem is %x.\n", graphicMem);
#if 0
	memset ((void *)graphicMem, 0, PAGE_SIZE << 6);
#else
	for (i = 0; i < 240 * 320; i ++)
		*(graphicMem + i) = 0x0;
	flush_DCache_all ();
#endif


	for(page = virt_to_page(graphicMem); page < virt_to_page(graphicMem + 40 * PAGE_SIZE); page++)
	{
		SetPageReserved(page);
	}

#endif


#ifndef _OTHER_LCD
	/* Bus Matrix Initialization */
	at91_sys_write (AT91_MATRIX_EBICSA, 0xffffff0f);

	/* SMC Initialization */
	p = ioremap(0xffffec50, 16);
	*(p++) = 0x01020102;
	*(p++) = 0x08060806;
	*(p++) = 0x000a000a;
	*(p++) = 0x10001003;
	iounmap(p);

	/* PIO Initialization */
	at91_set_gpio_output(AT91_PIN_PC7, 1);
	at91_set_gpio_value(AT91_PIN_PC7, 0);
	Delayms(100);
	at91_set_gpio_value(AT91_PIN_PC7, 1);
#else
	/* Bus Matrix Initialization */
	at91_sys_write (AT91_MATRIX_EBICSA, 0xffffff0f);

	/* SMC Initialization */
	p = ioremap(0xffffec50, 16);
	*(p++) = 0x0;
	*(p++) = 0x03030303;
	*(p++) = 0x00040004;
	*(p++) = 0x10001003;
	iounmap(p);

	/* PIO Initialization */
	at91_set_gpio_output(AT91_PIN_PC7, 1);
	at91_set_gpio_value(AT91_PIN_PC7, 0);
	Delayms(100);
	at91_set_gpio_value(AT91_PIN_PC7, 1);
#endif

	at91_set_A_periph (AT91_PIN_PC5, 1);

#ifdef HX8347D_LCD
	/* LCD Initialization */
	MainLCD_Command(0x0002);MainLCD_Data(0x0000);
	MainLCD_Command(0x0003);MainLCD_Data(0x0000); //Column Start
	MainLCD_Command(0x0004);MainLCD_Data(0x0000);
	MainLCD_Command(0x0005);MainLCD_Data(0x00EF); //Column End
	MainLCD_Command(0x0006);MainLCD_Data(0x0000);
	MainLCD_Command(0x0007);MainLCD_Data(0x0000); //Row Start
	MainLCD_Command(0x0008);MainLCD_Data(0x0001);
	MainLCD_Command(0x0009);MainLCD_Data(0x003F); //Row End
#else
	/* LCD Initialization */
	MainLCD_Command(0x0020); MainLCD_Data(0x0000);// GRAM horizontal Address          
	MainLCD_Command(0x0021); MainLCD_Data(0x0000);// GRAM Vertical Address            
	MainLCD_Command(0x0030); MainLCD_Data(0x0000);// - Adjust the Gamma Curve -
	MainLCD_Command(0x003D); MainLCD_Data(0x1000);// - Adjust the Gamma Curve -//
	MainLCD_Command(0x0050); MainLCD_Data(0x0000);// Horizontal GRAM Start Address
	MainLCD_Command(0x0051); MainLCD_Data(0x00EF);// Horizontal GRAM End Address
	MainLCD_Command(0x0052); MainLCD_Data(0x0000);// Vertical GRAM Start Address
	MainLCD_Command(0x0053); MainLCD_Data(0x013F);// Vertical GRAM End Address
#endif

}

void Point(int h, int v, u16 color)
{
	int page;
	int offset;

	if((h < 0) || (h > HORIZONTAL))
	{
		return;
	}
	else if((v < 0) || (v > VERTICAL))
	{
		return;
	}
	page = ((v * HORIZONTAL + h) * 2) >> PAGE_SHIFT;
	offset = ((v * HORIZONTAL + h) * 2) - (page << PAGE_SHIFT);
#ifdef OLD_FB
	graphicMem[page][offset >> 1] = color;
#else
	graphicMem[v * HORIZONTAL + h] = color;
#endif
}
static void movie_flush (void)
{
	int i;

	printk ("fb: fb move flush: %x\t%x\t%x.\n", fb_mode, fb_addr.read_sign, fb_addr.sign[fb_addr.read_sign]);

	if (atomic_read(&fb_addr.sign[fb_addr.read_sign]) == 1/*fb_addr.sign[fb_addr.read_sign] == 1*/)
	{
		MainLCD_Command(0x0022);
		for(i = 0; i < HORIZONTAL * VERTICAL; i++)
		{
			*data_port = *(fb_addr.fb_buf[fb_addr.read_sign] + i);
		}
		//fb_addr.sign[fb_addr.read_sign] = 0;
		atomic_set (&fb_addr.sign[fb_addr.read_sign], 0);
		fb_addr.read_sign = !fb_addr.read_sign;
	}
/*
	else
	{
		MainLCD_Command(0x0022);
		for(i = 0; i < HORIZONTAL * VERTICAL; i++)
		{
			*data_port = 0x0;
		}
	}
*/
	//printk ("fb: movie flush exit.\n");
}

void Flash_Frame(void)
{
	static int i;
	int page;
	int offset;

	//printk ("petworm: Flash_Frame enter.\n");
#ifdef HX8347D_LCD
	/* LCD Initialization */
	MainLCD_Command(0x0002);MainLCD_Data(0x0000);
	MainLCD_Command(0x0003);MainLCD_Data(0x0000); //Column Start
	MainLCD_Command(0x0004);MainLCD_Data(0x0000);
	MainLCD_Command(0x0005);MainLCD_Data(0x00EF); //Column End
	MainLCD_Command(0x0006);MainLCD_Data(0x0000);
	MainLCD_Command(0x0007);MainLCD_Data(0x0000); //Row Start
	MainLCD_Command(0x0008);MainLCD_Data(0x0001);
	MainLCD_Command(0x0009);MainLCD_Data(0x003F); //Row End
#else
	/*50 寄存器,液晶ram上的水平的起始坐标*/
	MainLCD_Command(0x0050); MainLCD_Data(0); // Horizontal GRAM Start Address
   	/*51 寄存器，液晶ram上的水平方向的结束坐标*/
	MainLCD_Command(0x0051); MainLCD_Data(239);// Horizontal GRAM End Address
 	/*52 寄存器，液晶ram上的竖直方向的起始坐标**/ 
	MainLCD_Command(0x0052); MainLCD_Data(0);// Vertical GRAM Start Address
	/*53 寄存器，液晶ram上的竖直方向的结束坐标**/
	MainLCD_Command(0x0053); MainLCD_Data(319);
	/*20寄存器，将要写液晶的水平起始坐标*/
	MainLCD_Command(0x0020); MainLCD_Data(0);
	/*21寄存器，将要写液晶的竖直起始坐标*/
	MainLCD_Command(0x0021); MainLCD_Data(0);
#endif
	MainLCD_Command(0x0022);

	flush_DCache_all ();

	for(i = 0; i < HORIZONTAL * VERTICAL; i++)
	{
#ifdef OLD_FB 
		page = (i * 2) >> PAGE_SHIFT;
		offset =  (i * 2) - (page << PAGE_SHIFT);

		MainLCD_Data(graphicMem[page][offset >> 1]);
#else
		//MainLCD_Data(graphicMem[i]);
		*data_port = *(graphicMem + i);
#endif
	}
}

void Mop(int h1, int v1, int h2, int v2, u16 color)
{
	int i, j;
	for(i = v1; i < v2; i++)
	{
		for(j = h1; j < h2; j++)
		{
			Point(j, i, color++);
		}
		color -= (h2 - h1 - 2);
	}

	Flash_Frame();
	return;
}

void Rectangle(int h1, int v1, int h2, int v2, u16 color)
{
	int i, j;
	for(i = v1; i < v2; i++)
	{
		for(j = h1; j < h2; j++)
		{
			Point(j, i, color);
		}
	}
	Flash_Frame();

	return;
}


inline u16 GetMemColor(unsigned short int i, unsigned short int j)
{
	int offset, page;


#ifndef OLD_FB
	if((i < 0) || (i > HORIZONTAL))
	{
		return;
	}
	else if((j < 0) || (j > VERTICAL))
	{
		return;
	}
	return graphicMem[j * HORIZONTAL + i];
#else
#if 0
	offset = i * 2 + j * 2 * 240;
	page = 0;
	while (offset > 4096)
	{
		offset -= 4096;
		page +=1;
	}
#else
	page = ((j * HORIZONTAL + i) * 2) >> PAGE_SHIFT;
	offset = ((j * HORIZONTAL + i) * 2) - (page << PAGE_SHIFT);
#endif
	return graphicMem[page][offset >> 1];
#endif
}

void FlushRect(unsigned short int x1,unsigned short int x2,unsigned short int y1,unsigned short int y2)
{
	unsigned int i,j;
	unsigned int flag = 0;
	//unsigned int irq_state;
#ifdef HX8347D_LCD
	MainLCD_Command(0x0002);MainLCD_Data(0x0000);
	MainLCD_Command(0x0003);MainLCD_Data(x1); //Column Start
	MainLCD_Command(0x0004);MainLCD_Data(0x0000);
	MainLCD_Command(0x0005);MainLCD_Data(x2); //Column End
	MainLCD_Command(0x0006);MainLCD_Data(y1 >= 0xff);
	MainLCD_Command(0x0007);MainLCD_Data(y1 & 0xff); //Row Start
	MainLCD_Command(0x0008);MainLCD_Data(y1 >= 0xff);
	MainLCD_Command(0x0009);MainLCD_Data(y1 & 0xff); //Row End
	MainLCD_Command(0x0022);
#else
	//printk (KERN_ALERT "Flush Rect run.\n");
	/*判断 将要写入的行。列是不是4的整数倍，*/
	/* 修改说明：因为在快速模式下是一次填充4个像素点，所以要判断要填充的矩形的长为4的倍数 */
	if((x1 % 4) || ((x2-x1+1) % 4)) 
	{
#ifdef FB_DEBUG
		printk (KERN_ALERT "enter slow.\n");
#endif
		/*写03 寄存器，为0x1030 ，第九位为0表示禁用快速写模式*/
		flag = 1;
		MainLCD_Command(0x0003); MainLCD_Data(0x1010);
	}
#ifdef FB_DEBUG
	MainLCD_Command (0x0003);
	printk (KERN_ALERT "0x03 register is %x.\n", MainLCD_Read());
#endif

	// 行 * 列 即为将要写的像素点数
	/*50 寄存器,液晶ram上的水平的起始坐标*/
	MainLCD_Command(0x0050); MainLCD_Data(x1); // Horizontal GRAM Start Address
   	/*51 寄存器，液晶ram上的水平方向的结束坐标*/
	MainLCD_Command(0x0051); MainLCD_Data(x2);// Horizontal GRAM End Address
 	/*52 寄存器，液晶ram上的竖直方向的起始坐标**/
	MainLCD_Command(0x0052); MainLCD_Data(y1);// Vertical GRAM Start Address
	/*53 寄存器，液晶ram上的竖直方向的结束坐标**/
	MainLCD_Command(0x0053); MainLCD_Data(y2);
	/*20寄存器，将要写液晶的水平起始坐标*/
	MainLCD_Command(0x0020); MainLCD_Data(x1);
	/*21寄存器，将要写液晶的竖直起始坐标*/
	MainLCD_Command(0x0021); MainLCD_Data(y1);
	/*22寄存器，向液晶写数据显示*/
	MainLCD_Command(0x0022);
#endif
	//local_irq_save(irq_state);
#if 0
#endif
	/* flush the D-cache */
	flush_DCache_all ();
#if 0
#endif
	for (j = y1; j <= y2; j ++)
	{
		for (i = x1; i <= x2; i ++)
		{
			MainLCD_Data(GetMemColor(i,j));
		}
	}

	/* 判断是否被改了模式，如果改了则返回初始化的状态 */
	if(flag)
	{
		flag = 0;
		MainLCD_Command(0x0003); MainLCD_Data(0x1210);
	}
}

inline void 
flush_DCache (unsigned short int x1, unsigned short int x2, 
				unsigned short int y1, unsigned short int y2)
{
	int i,j,k;

	j = ((y1 * HORIZONTAL + x1) * 2) >> PAGE_SHIFT;
	if ((k = (((y2 * HORIZONTAL + x2) * 2) >> PAGE_SHIFT)) < 37)
		k++;

	//printk (KERN_ALERT "start page number is %d.\nend page number is %d.\n", j ,k);

	for (i = j; i <= k; i++)
		flush_dcache_page (virt_to_page(graphicMem[i]));

}

inline void 
flush_DCache_all (void)
{
	int i;
	for (i = 0; i < 38; i++)
		flush_dcache_page (virt_to_page(graphicMem[i]));
}

#ifdef HX8347D_LCD
/********************************************************************************
*	函数：	fb_exit_sleep
*	功能：	进入sleep或者sandby模式；退出这两种模式的流程不同，
*		standby模式 不需要重新初始化，退出sleep模式 需要冲洗初始化
*	参数：	void
*	
*	返回值：void
**********************************************************************************/
void fb_exit_sleep(unsigned short int cmd)
{
	u8 tmp;

	// 1. Release form standby
	MainLCD_Command(0x0019); MainLCD_Data(0x1);	// OSC_EN=1
	MainLCD_Command(0x001f); MainLCD_Data(0x0088);
	Delayms (10);
	MainLCD_Command(0x001f); MainLCD_Data(0x0080);
	Delayms (10);
	MainLCD_Command(0x001f); MainLCD_Data(0x0090);
	Delayms (10);
	MainLCD_Command(0x001f); MainLCD_Data(0x00d0);
	Delayms (10);

	// 2. Power supply setting
	//MainLCD_Command(0x001B);MainLCD_Data(0x001B); //VRH=4.65V
	//MainLCD_Command(0x001A);MainLCD_Data(0x0001); //BT (VGH~15V,VGL~-10V,DDVDH~5V)
	//MainLCD_Command(0x0024);MainLCD_Data(0x002F); //VMH(VCOM High voltage ~3.2V)
	//MainLCD_Command(0x0025);MainLCD_Data(0x0057); //VML(VCOM Low voltage -1.2V)
	//MainLCD_Command(0x0023);MainLCD_Data(0x008C); //for Flicker adjust //can reload from OTP
	//MainLCD_Command(0x0018);MainLCD_Data(0x0036); //I/P_RADJ,N/P_RADJ, Normal mode 60Hz

	// 3. Display on flow
	MainLCD_Command(0x0028); MainLCD_Data(0x0038);
	Delayms (50); // Wait 2 frames or more
	MainLCD_Command(0x0028); MainLCD_Data(0x003c);
	Delayms (5);

	Flash_Frame ();

}
EXPORT_SYMBOL (fb_exit_sleep);

/****************************************************************************
*	函数：fb_entry_sleep
*	功能：进入sleep模式
*	参数：cmd  0x0002 表示 进入standby平模式,数据不丢失
*		   0x0004 进入sleep模式，数据丢失
*	返回值：void
******************************************************************************/
void fb_entry_sleep (unsigned short int cmd)
{
	u8 tmp;
		
	// 1. Display off flow
	MainLCD_Command(0x0028); MainLCD_Data(0x0038);
	Delayms (50); // Wait 2 frames or more
	MainLCD_Command(0x001f); MainLCD_Data(0x0089);
	Delayms (50); // Wait 2 frames or more
	MainLCD_Command(0x0028); MainLCD_Data(0x0004);
	Delayms (50);
	MainLCD_Command(0x0019); MainLCD_Data(0x0000);
	Delayms (10);

	// 2. Sleep Mode Set up Flow -> Standby
	//MainLCD_Command(0x001f); MainLCD_Read(&tmp);
	//tmp |= 0x1;
	//MainLCD_Command(0x001f); MainLCD_Data(tmp);	// STB=1
	//MainLCD_Command(0x0019); MainLCD_Data(0x0);	// OSC_EN=0

}
EXPORT_SYMBOL (fb_entry_sleep);
#else

/******************************************************
 ******* 此一下为 马志明 8.5日 添加******************
 ******************************************************/

/******************************************************************************
*	函数：init_function_setp1
*	功能：从standy模式退出时的寄存器初始化第一阶断
*	参数：void
*	
*	返回值：void
******************************************************************************/
void	init_function_setp1(void)
{
	MainLCD_Command(0x00e5); MainLCD_Data(0x8000);
	MainLCD_Command(0x0000); MainLCD_Data(0x0001);// Start internal OSC.
	MainLCD_Command(0x002b); MainLCD_Data(0x0010);// set SS and SM bit
	MainLCD_Command(0x0001); MainLCD_Data(0x0100);// set SS and SM bit
	MainLCD_Command(0x0002); MainLCD_Data(0x0700);// set 1 line inversion
	MainLCD_Command(0x0003); MainLCD_Data(0x1210);// set GRAM write direction and BGR=1.(0x1230)
	MainLCD_Command(0x0004); MainLCD_Data(0x0000);// Resize register 
	MainLCD_Command(0x0008); MainLCD_Data(0x0202);// set the back porch and front porch
	MainLCD_Command(0x0009); MainLCD_Data(0x0000);// set non-display area refresh cycle ISC[3:0]
	MainLCD_Command(0x000A); MainLCD_Data(0x0000);// FMARK function
	MainLCD_Command(0x000C); MainLCD_Data(0x0000);// RGB interface setting
	MainLCD_Command(0x000D); MainLCD_Data(0x0000);// Frame marker Position
	MainLCD_Command(0x000F); MainLCD_Data(0x0000);// RGB interface polarity
 
	MainLCD_Command(0x0050); MainLCD_Data(0x0000);// Horizontal GRAM Start Address
	MainLCD_Command(0x0051); MainLCD_Data(0x00EF);// Horizontal GRAM End Address
	MainLCD_Command(0x0052); MainLCD_Data(0x0000);// Vertical GRAM Start Address
	MainLCD_Command(0x0053); MainLCD_Data(0x013F);// Vertical GRAM Start Address
	MainLCD_Command(0x0060); MainLCD_Data(0x2700);// Gate Scan Line
	MainLCD_Command(0x0061); MainLCD_Data(0x0001);// NDL,VLE, REV
	MainLCD_Command(0x006A); MainLCD_Data(0x0000);// set scrolling line
	MainLCD_Command(0x0080); MainLCD_Data(0x0000);//- Partial Display Control -//
	MainLCD_Command(0x0081); MainLCD_Data(0x0000);
	MainLCD_Command(0x0082); MainLCD_Data(0x0000);
	MainLCD_Command(0x0083); MainLCD_Data(0x0000);
	MainLCD_Command(0x0084); MainLCD_Data(0x0000);
	MainLCD_Command(0x0085); MainLCD_Data(0x0000);
	MainLCD_Command(0x0090); MainLCD_Data(0x0010);//- Panel Control -//
	MainLCD_Command(0x0092); MainLCD_Data(0x0000);
	MainLCD_Command(0x0093); MainLCD_Data(0x0003);
	MainLCD_Command(0x0095); MainLCD_Data(0x0110);
	MainLCD_Command(0x0097); MainLCD_Data(0x0000);
	MainLCD_Command(0x0098); MainLCD_Data(0x0000);//- Panel Control -//
}

/******************************************************************************
*	函数：init_function_setp2
*	功能：从standy模式退出时的寄存器初始化第二阶段，初始化寄存器 0x30--0x3D
*	参数：void
*	
*	返回值：void
******************************************************************************/
void	init_function_setp2(void)
{
	MainLCD_Command(0x0030); MainLCD_Data(0x0000);// - Adjust the Gamma Curve -//
	MainLCD_Command(0x0031); MainLCD_Data(0x0507);
	MainLCD_Command(0x0032); MainLCD_Data(0x0104);
	MainLCD_Command(0x0035); MainLCD_Data(0x0105);
	MainLCD_Command(0x0036); MainLCD_Data(0x0404);
	MainLCD_Command(0x0037); MainLCD_Data(0x0603);
	MainLCD_Command(0x0038); MainLCD_Data(0x0004);
	MainLCD_Command(0x0039); MainLCD_Data(0x0007);
	MainLCD_Command(0x003C); MainLCD_Data(0x0501);
	MainLCD_Command(0x003D); MainLCD_Data(0x0404);// - Adjust the Gamma Curve -//
}

/****************************************************************************
*	函数：display_on_funtion
*	功能：进入普通显示模式
*	参数：void
*
*	返回值：void
*****************************************************************************/
void	display_on_funtion(void)
{
	/*07 寄存器,显示控制寄存器 进入普通显示模式*/
	MainLCD_Command(0x0007); MainLCD_Data(0x0173);// Horizontal GRAM Start Address

}
/****************************************************************************
*	函数：fb_entry_sleep
*	功能：进入sleep模式
*	参数：cmd  0x0002 表示 进入standby平模式,数据不丢失
*		   0x0004 进入sleep模式，数据丢失
*	返回值：void
******************************************************************************/
void fb_entry_sleep (unsigned short int cmd)
{
	/*07 寄存器,关闭显示 */
	MainLCD_Command(0x0007); MainLCD_Data(0x0000);  
    
    	/*10 寄存器，*/
	MainLCD_Command(0x0010); MainLCD_Data(0x0000);     
	MainLCD_Command(0x0011); MainLCD_Data(0x0000);    
	MainLCD_Command(0x0012); MainLCD_Data(0x0000);
    	MainLCD_Command(0x0013); MainLCD_Data(0x0000);

    	/*延时一段时间 */
    	Delayms(0xc8);
    	/*10寄存器，SLP= 1 进入sleep 模式 DB*/
	MainLCD_Command(0x0010); MainLCD_Data(cmd);
}
EXPORT_SYMBOL (fb_entry_sleep);

void power_set_function()
{

 	/*10 ，11，12，13 寄存器，关于电源的控制寄存器清空 */
    	MainLCD_Command(0x0010); MainLCD_Data(0x0000);
    	MainLCD_Command(0x0011); MainLCD_Data(0x0000);
    	MainLCD_Command(0x0012); MainLCD_Data(0x0000);
   	MainLCD_Command(0x0013); MainLCD_Data(0x0000);

 	/*延时一段时间 */
    	Delayms(0xc8);

    	MainLCD_Command(0x0010); MainLCD_Data(0x17b0);	/*10 寄存器，*/
    	MainLCD_Command(0x0011); MainLCD_Data(0x0137);	/*11 寄存器，设置升压电路1 、2 */
    	Delayms(0x32);
    	MainLCD_Command(0x0012); MainLCD_Data(0x139);	/*12 寄存器，**/
    	Delayms(0x32);
    	MainLCD_Command(0x0013); MainLCD_Data(0x1700);	/*13寄存器，设置 */


 	/*10寄存器，SLP= 1 进入sleep 模式*/
	MainLCD_Command(0x0029); MainLCD_Data(0x000c);

	Delayms(0x32);
	/*20寄存器，将要写液晶的水平起始坐标*/
	MainLCD_Command(0x0020); MainLCD_Data(0x0000);

	/*21寄存器，将要写液晶的竖直起始坐标*/
	MainLCD_Command(0x0021); MainLCD_Data(0x0000);
}

/********************************************************************************
*	函数：	fb_exit_sleep
*	功能：	进入sleep或者sandby模式；退出这两种模式的流程不同，
*		standby模式 不需要重新初始化，退出sleep模式 需要冲洗初始化
*	参数：	void
*	
*	返回值：void
**********************************************************************************/
void fb_exit_sleep(unsigned short int cmd)
{
	int i;

	/* 退出standby模式 */
 	if(cmd == 0x0002)
 	{
		/* 电源设置 */
 		power_set_function();
		/* 使能显示 */
  		display_on_funtion();
	}

	/* 退出sleep模式 */
	if(cmd == 0x0004)
	{
		/* 使 nCS信号，由低到高 6次 */
		for(i=0;i<6;i++)
		{
			MainLCD_Command(0x0022); 
			Delayms(0xa);
			MainLCD_Data(0x0000);
			Delayms(0xa);
   		}

		/* 9320 芯片部分寄存器初始化 */	
		init_function_setp1();
		/* 电源设置 */
		power_set_function();
		/* 9320 芯片部分寄存器初始化 */	
		init_function_setp2();
		/* 使能显示 */
		display_on_funtion();
		//drv_lcd_init();
		/* flush all FrameBuffer after exit sleep */
		Flash_Frame ();
	}
}
EXPORT_SYMBOL (fb_exit_sleep);
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("petworm");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");
