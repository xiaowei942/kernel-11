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

#include <asm/arch/at91_twi.h>
#include <linux/pm.h>
#include <linux/platform_device.h>


#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/string.h>
#include <linux/rtc.h>		/* get the user-level API */
#include <linux/bcd.h>
#include <linux/list.h>
/*
#include <asm/arch/at91sam926x_sdramc.h>
#include <asm/arch/at91_shdwc.h>
*/
/*
#include <asm/arch-at91/at91_twi.h>
#include <asm/hardware.h>
*/

#include "T11_keyb_max7347.h"

#define KEYB_DEBUG

#define KEYB_CFG_MAJOR 243
#define KEYB_CFG_MINOR 0

static int keyb_major;

struct keyb_dev
{
	struct cdev	*kb_cdev;	/* cdev结构指针 */
	U16		kbuf[MAX_BUF_NUM];	/* 键盘按键缓冲区 */
	int		bufb, bufs; /* 键盘队列指针 */
	int		irkey;
};

static dev_t dev;		/* 设备信息 */

static struct keyb_dev *pkeyb_dev;
static struct i2c_client *new_client;

static unsigned short ignore[] = { I2C_CLIENT_END };
static unsigned short normal_addr[] = { 0x38, I2C_CLIENT_END };

static struct i2c_client_address_data addr_data = {
	.normal_i2c = normal_addr,
	.probe = ignore,
	.ignore = ignore,
};

static LIST_HEAD(max7347_clients);

static int max7347_command(struct i2c_client *client, unsigned int cmd, void *arg);
static int max7347_detach_client(struct i2c_client *client);
static int max7347_attach_adapter(struct i2c_adapter *adapter);
static void max7347_init_client(struct i2c_client *client);


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
	//printk (KERN_ALERT"petowrm: keyb: kbufin is %x.\n", key);
#endif
	temp = pkeyb_dev->bufs +1;
	if (temp >= MAX_BUF_NUM)
	      temp -= MAX_BUF_NUM;	

	if(temp == pkeyb_dev->bufb)
		return 1;

	pkeyb_dev->kbuf[pkeyb_dev->bufs] = key;
	if ((++pkeyb_dev->bufs) >= MAX_BUF_NUM)
	       pkeyb_dev->bufs -= MAX_BUF_NUM;
#ifdef KEYB_DEBUG
	//printk (KERN_ALERT"petworm: kbuf top is %d\n", pkeyb_dev->bufs);
#endif
	return 0;
}

/***************************************************************************
 *
 * i2c read/write function
 *
 ***************************************************************************/
static inline int max7347_read(u8 reg)
{
#if 0
	return i2c_smbus_read_byte_data(new_client, reg);
#else
	struct i2c_msg msg[2];
	char ret;

	msg[0].addr = new_client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &reg;

	msg[1].addr = new_client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 1;
	msg[1].buf = &ret;

	i2c_transfer (new_client->adapter, msg, 2);
	return ret;
#endif
}

static inline int max7347_write(u8 reg, u8 data)
{
#if 0
	return i2c_smbus_write_byte_data(new_client, reg, data);
#else
	struct i2c_msg msg[1];
	char ret;

	msg[1].addr = new_client->addr;
	msg[1].flags = 0;
	msg[1].len = 1;
	msg[1].buf = &ret;

	i2c_transfer (new_client->adapter, msg, 1);

	return ret;
#endif
}

inline int Key_Read(char *data, int iaddr)
{
	s32 ret;
	ret = max7347_read(iaddr);
	if (ret < 0)
		return -EIO;
	else
	{
		*data = (char) ret;
		return 0;
	}
}


/********************************************************
 *
 *
 *
 *******************************************************/
static int keyb_open(struct inode *pinode, struct file *pfile)
{
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
	char keyret[2];

	if (pkeyb_dev->bufs == pkeyb_dev->bufb)
		return 0;
	for (i = 0; i < (int) count / 2; i++)
	{
		//retch = readkey();
#if 0		
		keyret[i] = (char) ((retch & 0xff00) >> 8);
		keyret[++i] = (char) (retch & 0xff);
#endif
		keynum += 2;

		if (pkeyb_dev->bufs == pkeyb_dev->bufb)
			goto out;
	}
out:
#ifdef KEYB_DEBUG
	printk (KERN_ALERT"petworm: keyb: keyret is %x-%x.\n", keyret[0], keyret[1]);
#endif
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

	kbufin(temp);

	return 2;
}

/********************************************************
 * 函数：键盘驱动控制函数
 * 功能：控制键盘驱动的行为，预留函数
 * 	 功能1：决定读取按键的键值是以什么形式转换及读取的
 * 	 	键值会放入到什么地方
 * 参数：
 ********************************************************/
static int keyb_ioctl(struct inode *p_inode, struct file p_file, 
			unsigned int cmd, unsigned long arg)
{
#if 1
	printk (KERN_ALERT "the cmd is %x, the arg is %x.\n",cmd, arg);
#else
	switch (cmd)
	{
		printk (KERN_ALERT"the cmd is %x.", cmd);
		case KEYB_CMD_CLRBUF:
			pkeyb_dev->bufs = pkeyb_dev->bufb = 0;
			break;
		case KEYB_CMD_HAVEKEY:
			if (pkeyb_dev->bufs == pkeyb_dev->bufb)
				arg = 0;
			else
				arg = pkeyb_dev->kbuf[pkeyb_dev->bufb];
			break;
		default:
			return -EINVAL;
	}
#endif
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

	//disable_irq (IRQ0);	// 屏蔽中断IRQ0
	//disable_irq (1);
	local_irq_save(irq_state);
	//local_irq_disable();

        do
        {
             	do
             	{
			/* 从键盘节片读取键值 */
       			Key_Read(&datac, 0x0);
			
                	num = (int) (datac & 0x3f);
                	keysca = raw2scancode(num);
#ifdef KEYB_DEBUG
			printk (KERN_ALERT "keyirq: the key is %x\n", datac);
#endif
			/* 将读取的键值放入缓冲区 */
			kbufin (keysca);
#if 0
#ifdef CONFIG_VT
             		handle_scancode(keysca, 1);
			handle_scancode(keysca, 0);
#endif
			tasklet_schedule(&keyboard_tasklet);
#endif
  	            
                }while ((datac & 0x40) != 0x0);

                Key_Read(&tstint, 0x3);
	}while ((tstint & 0x80) != 0);

	//local_irq_enable();
	local_irq_restore(irq_state);
	//enable_irq(1);
	//enable_irq(IRQ0);	// 使苤卸螴RQ0

	return IRQ_HANDLED;
}


/************************************************************
 *
 *
 ***********************************************************/
static struct i2c_driver max7347_driver = {
	.driver = {
		.name	= "max7347",
	},
	.attach_adapter	= max7347_attach_adapter,
	.detach_client	= max7347_detach_client,
};

struct max7347_data {
	struct i2c_client client;
	struct list_head list;
};


static int max7347_detect(struct i2c_adapter *adapter, int address, int kind)
{
	struct max7347_data *data;
	int err = 0;

	printk (KERN_ALERT "petworm: max7347 detect start.\n");
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_I2C))
		goto exit;

	if (!(data = kzalloc(sizeof(struct max7347_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit;
	}
	INIT_LIST_HEAD(&data->list);

	/* The common I2C client data is placed right before the
	 * max7347-specific data. 
	 */
	new_client = &data->client;
	i2c_set_clientdata(new_client, data);
	new_client->addr = address;
	new_client->adapter = adapter;
	new_client->driver = &max7347_driver;
	new_client->flags = 0;
	memcpy (new_client->name, max7347_driver.driver.name, I2C_NAME_SIZE);

	printk (KERN_ALERT "kind is %d.\n", kind);
	printk (KERN_ALERT "i2c client name is %s.\n", new_client->name);
	printk (KERN_ALERT "i2c clinet addr is %x.\n", address);

	/* Tell the I2C layer a new client has arrived */
	if ((err = i2c_attach_client(new_client)))
		goto exit_free;

	/* Initialize the MAX7347 chip */
	max7347_init_client(new_client);

	/* Add client to local list */
	list_add(&data->list, &max7347_clients);

	return 0;

exit_free:
	printk (KERN_ALERT "attach client error.\n");
	kfree(data);
exit:
	printk (KERN_ALERT "kzalloc failed.\n");
	return err;
}

static int max7347_attach_adapter(struct i2c_adapter *adapter)
{
	return i2c_probe(adapter, &addr_data, max7347_detect);
}

static int max7347_detach_client(struct i2c_client *client)
{
	int err;
	struct max7347_data *data = i2c_get_clientdata(client);

	if ((err = i2c_detach_client(client)))
		return err;

	list_del(&data->list);
	kfree(data);
	return 0;
}

static void max7347_init_client(struct i2c_client *client)
{
	/* Initial the max7347 */
	printk (KERN_ALERT "set the max7347 for keyb device.\n");
	
	printk (KERN_ALERT "0x0 is %x.\n", max7347_read(0x0));
	printk (KERN_ALERT "0x1 is %x.\n", max7347_read(0x1));
	printk (KERN_ALERT "0x2 is %x.\n", max7347_read(0x2));
	printk (KERN_ALERT "0x3 is %x.\n", max7347_read(0x3));

	while (max7347_write(0x1, 0x1f) == -1);
	while (max7347_write(0x2, 0x00) == -1);
	while (max7347_write(0x3, 0x01) == -1);
	while (max7347_write(0x4, 0x80) == -1);
	
	printk (KERN_ALERT "test the max7347 for keyb device.\n");
	printk (KERN_ALERT "0x0 is %x.\n", max7347_read(0x0));
	printk (KERN_ALERT "0x1 is %x.\n", max7347_read(0x1));
	printk (KERN_ALERT "0x2 is %x.\n", max7347_read(0x2));
	printk (KERN_ALERT "0x3 is %x.\n", max7347_read(0x3));

}

static int __init t11_keyb_init (void)
{
	int result, err;
	unsigned int kb_major = KEYB_CFG_MAJOR, kb_minor = KEYB_CFG_MINOR;
#ifdef KEYB_DEBUG
	printk (KERN_ALERT "Init cdev.\n");
#endif
	if (kb_major) {
	 	dev = MKDEV(kb_major, kb_minor);
	 	result = register_chrdev_region(dev, 1, "kb0");
	} else {
		result = alloc_chrdev_region(&dev, kb_minor, 1, "kb0");
		kb_major = MAJOR(dev);
	}
	if (result < 0) {
	 	printk(KERN_WARNING "scull: can't get keyb major %d\n", result);
	 	return result;
	}

	result = i2c_add_driver(&max7347_driver);
	if (result)
		goto fail_i2c_reg;

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

	if (request_irq(AT91SAM9261_ID_IRQ0, max7347_ServeIrq, IRQ_TYPE_LEVEL_LOW, "keyb_max7347", NULL))
		printk (KERN_ALERT"irq error\n");

	return 0;

	// 失败处理
fail_i2c_reg:
	printk (KERN_NOTICE "the i2c driver register failed.\n");
fail_cdev_add:
	printk(KERN_NOTICE "the cdev add failed.\n");
	kfree (pkeyb_dev);
fail_malloc:
	printk(KERN_NOTICE "the malloc failed.\n");
	unregister_chrdev_region (dev, 1);
	return result;
}

static void __exit t11_keyb_exit (void)
{
	printk(KERN_ALERT "exit keyb_max7347.\n");

	i2c_del_driver (&max7347_driver);
	/* 释放文件指针 */
	cdev_del(pkeyb_dev->kb_cdev);	/*释放kcdev*/
	kfree(pkeyb_dev);	/*释放设备结构体*/
	unregister_chrdev_region (dev, 1);	 /*释放设备号*/


	return 0;	
}

module_init(t11_keyb_init);
module_exit(t11_keyb_exit);
MODULE_AUTHOR("Petworm");
MODULE_LICENSE("Dual BSD/GPL");
module_param(keyb_major, int, S_IRUGO);
