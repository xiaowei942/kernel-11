//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : main.c
//* Object              : main application written in C
//* Creation            : GGi
//*----------------------------------------------------------------------------


#include "adc_spi.h"
#include <linux/delay.h>
#include <asm-generic/errno-base.h>

#define PIOB_PB26_BASE		0xFFFFF600
#define PB26_SODR	 	0xFFFFF630
#define PB26_OER	 	0xFFFFF610
#define PB26 			(0x1<<26)
#define PIO_PDR			(0x04 >> 2)
#define PIO_ASR			(0x70 >> 2)
static int kbuf = 0;
static int return_value = 400;
static volatile unsigned int *paddr;
static volatile unsigned int addr;
//#define ADC
int spi_config(void);
void spi_read_enable(void);
void spi_read_disable(void);
int values(int k);

/***************************************************************************
 *函数：int values(int k)
 *功能： 将读到 的值转换成 电压值，返回值value电压是实际电压的100倍
 *													
 ***************************************************************************/
int values(int  k)
{
	int value;
	

	//value =	( (k * 330 * 2/ 16/255);
	value = k>>4;  //后四位 无效
	value += 3;		//为减小误差 故＋3
#ifdef ADC
	printk(KERN_ALERT"Mzm: The value is %d \n",value);
#endif	
	value = value*330*2;	//读取电压是实际电压的 100倍
	//value = value>>4;  //后四位 无效
	value = value>>8;	//除以256 应该除以255  3.3V ：255  ＝ 实际电压：读到的值
	
	
	return value;
}

/***************************************************************************
 *函数：spi_config()
 *功能： 配置SPI 将要用到的各个IO，配置spi为主机模式，设置spi
 *		的芯片选择寄存器：设置时钟，传输位数，波特率，发送延时
 *													
 ***************************************************************************/
int spi_config()
{
	int tmp;
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi_config.... \n");
#endif
	//使能spi pioa piob的时钟  
	paddr = ioremap(AT91A_PMC_PCER, 4);
	*paddr |= ((0x1<<2)|(0x1<<3)|(0x1<<12));
	iounmap(paddr);

	//PA0 PA1 PA2 PA27 的配置 ：PA27 片选信号NPCS1
	paddr = ioremap(0xfffff400, 0xA8);

#if 1
	//*paddr |=AT91C_PA27_SPI0_NPCS1;
	//*(paddr+(0x10>>2)) |= AT91C_PA27_SPI0_NPCS1;//(1 << 27);
	//*(paddr+(0x60>>2)) |= ~(0xfffffffe);
	//*(paddr+(0x64>>2)) |= (0xfffffffe);
		
	tmp = 0 ;
	for(tmp=0;tmp<200000;tmp++);


	// PA27是 外设B功能口：PIO——BSR
	*(paddr+(0x74>>2)) = AT91C_PA27_SPI0_NPCS1;

	//PA0 PA1 PA2 是外设A功能口：PIO——ASR
	*(paddr+(0x70>>2)) = ((AT91C_PA0_SPI0_MISO )|(AT91C_PA2_SPI0_SPCK  )|(AT91C_PA1_SPI0_MOSI));
	
	//禁用IO PIO——PDR
	*(paddr+1) = ((AT91C_PA0_SPI0_MISO )|(AT91C_PA2_SPI0_SPCK  )|(AT91C_PA1_SPI0_MOSI)| AT91C_PA27_SPI0_NPCS1);
#endif
	iounmap(paddr);

	//SPI 复位		
	paddr = ioremap(AT91A_SPI0_CR,4);
	*paddr |=  AT91_SPI_RESTART;
	iounmap(paddr);


	//配置SPI为主机模式 //1101 npcs1
	paddr = ioremap(AT91A_SPI0_MR,4);
	*paddr = AT91_SPI_NPCS_MASTER;
	iounmap(paddr);
	
	//设置芯片选择寄存器 设置传输位数:波特率 传输延时 AT91C_SPI_CPOL   100kbps //cpol =1 ncpha =0;
	paddr = ioremap(AT91A_SPI0_CSR1,4);
	*paddr = (0x3 | (AT91C_SPI_DLYBS & (ADC_DLYS)) | (AT91C_SPI_DLYBCT & DATAFLASH_TCHS) | (0x30 << 8)| (0x7 << 4));
	iounmap(paddr);
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi_config is OK \n");
#endif
	return 0;
}

/***************************************************************************
 *函数：spi_read_enable()
 *功能： 通过设置PB26 为1 使能AD，使能后，要先发送一串数据
 *		才能正常通信，发送数据任意，下面发送的是：0x000D5555
 *													
 ***************************************************************************/
void spi_read_enable(void)
{
	spi_config();
	//SPI 使能
	paddr = ioremap(AT91A_SPI0_CR,4);	
	*paddr |=  AT91_SPI_ENABLE;
	iounmap(paddr);

	//PB26 置 1 AD使能
	paddr = ioremap(PIOB_PB26_BASE,0xa8);
	*paddr = PB26;
	*(paddr +(0x10>>2)) = PB26;
	*(paddr +(0x30>>2)) = PB26;
	iounmap(paddr);

	mdelay(1);
	//发送一串数据使AD正常工作
	paddr = ioremap(AT91A_SPI0_TDR,4);	
	*paddr |=  0x000D5555;
	//mdelay(2);
	iounmap(paddr);
}

/***************************************************************************
 *函数：spi_read_disable()
 *功能： 通过设置PB26 为0 禁用AD
 *		
 *													
 ***************************************************************************/
void spi_read_disable(void)
{
#if 1
	paddr = ioremap(AT91A_SPI0_SR,4);
	*paddr |=0x02; //disable spi
	iounmap(paddr);
#endif
	paddr = ioremap(PIOB_PB26_BASE,0xa8);

	*paddr = PB26;
	*(paddr +(0x10>>2)) = PB26;
	*(paddr +(0x34>>2)) = PB26; 	//PB26 置 0 禁用AD

	iounmap(paddr);


}

/***************************************************************************
 *函数：spi_readdata()
 *功能： 使能AD后，读取spi的状态位，直到有数据接受到，把数据存放在
 *		全局变量Kbuf中，然后禁用AD，判断数据接受的格式是否正确。
 *													
 ***************************************************************************/
int	spi_readdata(void)
{
	spi_read_enable();					//使能SPI AD

	paddr = ioremap(AT91A_SPI0_SR,4);		//读取接受RDY
	while(!((*paddr) & 0x1));

	iounmap(paddr);

	paddr = ioremap(AT91A_SPI0_RDR,4);		//读取数据 寄存器中数据后16位有效
	kbuf = (int)(*(paddr) & 0xffff);
 	iounmap(paddr);

	//禁用AD
	//spi_read_disable();
	//判断数据是否正确 从AD得到的数据是15位的，其数据格式：最高三位是0，最低4位也是0
	//	中间的8位数据是有效的数据，
	//这里判断一下是否读取有错误
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
/***************************************************************************
 *函数：spi_open();
 *功能： 对应用户程序中的open（），调用spi_config()配置SPI。
 *															
 ***************************************************************************/
int spi_open(struct inode *inode,struct file *file)
{
#ifdef ADC
	printk(KERN_ALERT"Mzm: Open the spi just now\n");
#endif
	//spi_config();

#ifdef ADC
	printk(KERN_ALERT"Mzm: Open the spi over....\n");

#endif
	return 0;
}
/***************************************************************************
 *函数：spi_read();
 *功能： 对应用户程序中的read（），调用spi_readdata()使能AD，读取数据
 *		若读取5次出错则返回0，读取失败退出，成功返回 1
 *													
 ***************************************************************************/
static ssize_t  spi_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos)
{
	unsigned int count1 = 0;	
#ifdef ADC
	printk(KERN_ALERT"Mzm: Spi read .....\n");	
#endif


	while((count1++ < 5) && (spi_readdata())); 	//读取5次；

	if(count1 > 5)				//读取5次失败,返回电压值为0 ,程序返回1；
	{
		printk(KERN_ALERT"Mzm: TIME OUT \n");
	
		kbuf = 0;
		
		put_user(return_value,(int*)buf);
		return -ENODATA;
	}
	
	return_value = values(kbuf);

	// 将数据返回用户空间
	put_user(return_value,(int*)buf);
	
	kbuf = 0;

#ifdef ADC
	printk(KERN_ALERT"Mzm: Copy_to_user is over\n");
#endif
	return 0;
}	
/***************************************************************************
 *函数：spi_write();
 *功能： 对应用户程序中的write（），没有实现
 *		
 *													
 ***************************************************************************/
static ssize_t  spi_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos)
{	
	return 0;
}

/***************************************************************************
 *函数：spi_ioctl();
 *功能： 对应用户程序中的 ioctl（），没有实现
 *		
 *													
 ***************************************************************************/
int spi_ioctl(struct inode *inode, struct file *file,unsigned int cmd, unsigned long arg)
{	
	return 0;
}

/***************************************************************************
 *函数：spi_release();
 *功能： 对应用户程序中的 close（），禁用spi，禁用AD
 *		
 *													
 ***************************************************************************/
int spi_release(struct inode *inode, struct file *file)
{	
#if 0
	paddr = ioremap(AT91A_SPI0_SR,4);
	*paddr |=0x02; //disable spi
	iounmap(paddr);
#endif
	spi_read_disable();
#ifdef ADC
	printk(KERN_ALERT"Mzm: adc_spi_Release........\n");
#endif
	return 0;
}

/***************************************************************************
 *		AD驱动文件指针结构体
 *													
 ***************************************************************************/
struct file_operations spi_fops={

	open:spi_open,
	read:spi_read,
	write:spi_write,
	ioctl:spi_ioctl,
	release:spi_release,
	
}; 

/***************************************************************************
 *函数：spi_driver_init（）；
 *功能：注册AD驱动为字符设备驱动，主设备号：240
 *															
 ***************************************************************************/
int __init spi_driver_init(void)
{
	int rc;

	printk(KERN_ALERT"Mzm: Start to spi reg chrder....\n");
				
	if ((rc = register_chrdev(SPI_MAJOR, DEVICENAME , &spi_fops)) < 0){
		printk(KERN_ALERT"Mzm: Spi_driver: can't get major %d\n", SPI_MAJOR);
		return 1;
	}

	//printk("the module adc is insert\n");
	printk(KERN_ALERT"Mzm: The Major is %d\n",SPI_MAJOR);

	return 0;
}

/***************************************************************************
 *函数：spi_driver_exit（）；
 *功能：注销AD驱动模块
 *															
 ***************************************************************************/
void __exit spi_driver_exit(void)
{
	unregister_chrdev(SPI_MAJOR, DEVICENAME);
	printk(KERN_ALERT"Mzm: Exit the Spi Module\n");
			
}

module_init(spi_driver_init);
module_exit(spi_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karsten Jeppesen <karsten@jeppesens.com>");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");
