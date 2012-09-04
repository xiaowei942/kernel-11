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
//* File Name           : main.c
//* Object              : main application written in C
//* Creation            : NLe   27/11/2002
//*
//*----------------------------------------------------------------------------
#include "infrared.h"
#include <linux/clk.h>


#include <asm/arch/at91_aic.h>
#include <asm/hardware.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch-at91/at91sam9261.h>
unsigned int * p;
char retch = 'A';
int infrared_num = 0;

void UART1_init(void);
unsigned int US1_Baudrate (const unsigned int, const unsigned int );
void Infrared_UART1_puts(const char *,size_t count);
void Infrared_UART1_putc(char );

static struct semaphore infrared_sem;

/********************************************************
 * 函数：红外字符串发送函数
 * 功能：用户空间的字符串通过红外口输出
 * 参数：const char *buffer ：将要发送的字符串
 * 	size_t 	count 	  :  要发送的字符传长度
 *******************************************************/
void Infrared_UART1_puts(const char *buffer,size_t count) // \arg pointer to a string ending by \0
{	
	while(count-- > 0)
 	{
		Infrared_UART1_putc(*buffer++);
#ifdef DEBUG
		printk("the puts...%c\n",*buffer);
#endif
	}
}


/********************************************************
 * 函数：红外字符发送函数
 * 功能：把一个字符通过红外口发送出去
 * 参数：const char car ：将要发送的字符
 *******************************************************/
void Infrared_UART1_putc(char car) // \arg pointer to a string ending by \0
{		
		p = ioremap(US1_BASE_CR,0x124);
		while (!((*(p + US1_CSR)) & AT91C_US_TXRDY))
#ifdef DEBUG
			printk("wait....\n");
#endif	
			*(p + US1_THR) =  (car & 0x1FF);
		iounmap(p);
}



/********************************************************
 * 函数：通过红外接收字符函数
 * 功能：通过红外接受一个字符，并把字符存放在全局变量：retch中（retch为char 型占8位，并非9位，然而PHR中有效位为9位）
 * 		适用键盘的0－9 足以。。
 * 参数：void 该函数主要被中断处理函数调用
 * 返回值：无返回之；
 *******************************************************/
void Infrared_UART1_getc(void)
{
	int car = 0xffffffff ;
#ifdef DEBUG
	printk("##this is in getc ##\n");
#endif
	car = (*(p+US1_RHR)&0x1ff);
#ifdef DEBUG
	printk("###########the char is 0x%x#####\n",car);
#endif
	retch = (char)(car &0xff);

	//return car;
	
}
/********************************************************
 * 函数：UART1初始化函数
 * 功能：初始化红外将要用到的外设功能口和IO口，使能UART1的时钟，数据波特率为1200，晴空跟Uart相关的PD寄存器
 * 	设置UART1 为 普通模式 1位停止位 空校验 8位 始终为主始终 99.3Mhz
 * 参数：
 * 返回值：
 *******************************************************/
void UART1_init(void)
{
	int tmp;
#ifdef DEBUG
	printk("##this is in uart1_init\n");
#endif
	//配置 PB11	不使能红外
	p =ioremap(PIOB_BASE,0xA8);
	*(p + PIO_PER) = 0x940;
	*(p + PIO_OER) = 0x940;
	*(p + PIO_SODR) = 0x940;
	iounmap(p);

	// 设置将要用到的外设口 SCK RTS1 CTS1 RXD1 TXD1
	p =ioremap(PIOA_BASE,0xA8); //SCK RTS1 CTS1
	*(p + PIO_BSR) = (AT91C_PIO_PA11|AT91C_PIO_PA12|AT91C_PIO_PA13);
	*(p + PIO_PDR) = (AT91C_PIO_PA11|AT91C_PIO_PA12|AT91C_PIO_PA13);
	iounmap(p);
	
	p =ioremap(PIOC_BASE,0xA8);// RXD1 TXD1
	*(p + PIO_ASR) = (AT91C_PIO_PC12|AT91C_PIO_PC13);
	*(p + PIO_PDR) = (AT91C_PIO_PC12|AT91C_PIO_PC13);
	iounmap(p);


	for(tmp = 0;tmp<10000;tmp++);
	//给UART1 提供时钟
	p =ioremap(PMC_PCER,4); 
	*p = (0x1 << ID_US1);
	iounmap(p);

	//设置UART 的寄存器
	p = ioremap(US1_BASE_CR,0x124);
	*(p + US1_IDR) = (unsigned int ) -1;
	*p = 	AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS ;
	//设置红外的波特率
	*(p + US1_BRGR) = US1_Baudrate(AT91C_MASTER_CLOCK,AT91C_BAUDRATE_1200);
	//设置传送延时 0
	*(p + US1_TTGR) = TIME_GUARD;
	
	//set PDC for UART1 设置跟UART 相关的PDC 
	//DIS TX RX
	*(p + US1_PTCR) = AT91C_PDC_RXTDIS;
	*(p + US1_PTCR) = AT91C_PDC_TXTDIS;
	
	//bzero TX and TNX 
	*(p + US1_TNPR) = 0;
	*(p + US1_TNCR) = 0;
	*(p + US1_TPR) = 0;
	*(p + US1_TCR) = 0;
	
	//bzero RX and RNX
	*(p + US1_RNPR) = 0;
	*(p + US1_RNCR) = 0;
	*(p + US1_RPR) = 0;
	*(p + US1_RCR) = 0;
	
	//EN TX and RX 使能发送 接受
	*(p + US1_PTCR) = AT91C_PDC_RXTEN;
	*(p + US1_PTCR) = AT91C_PDC_TXTEN;
	
	//set US1_MR 设置UART1 为 普通模式 1位停止位 空校验 8位 始终为主始终 99.3Mhz 
	*(p + US1_MR) = (AT91C_US_USMODE_NORMAL |AT91C_US_NBSTOP_1_BIT | AT91C_US_PAR_NONE | AT91C_US_CHRL_8_BITS |AT91C_US_CLKS_CLOCK);
	
	*p |= AT91C_US_TXEN;
	*p |= AT91C_US_RXEN;
	iounmap(p);

}
/********************************************************
 * 函数：设置红外波特率的函数
 * 功能：被 UART1——init初始化函数调用设置波特率，为设置更准确的波特率，遵循四舍五入的原则。		
 * 参数：const unsigned int main_clock： 主时钟频率：99.3
 *	 const unsigned int baud_rate :  红外波特率 1200
 * 返回值：返回 处理后的波特率的值
 *******************************************************/
unsigned int US1_Baudrate (const unsigned int main_clock, const unsigned int baud_rate)  // \arg UART baudrate
{
	unsigned int baud_value = ((main_clock*10)/(baud_rate * 16));
	if ((baud_value % 10) >= 5)
		baud_value = (baud_value / 10) + 1;
	else
		baud_value /= 10;
	return baud_value;
}

/********************************************************
 * 函数：设备打开函数
 * 功能：初始化红外用到的一系列的寄存器，初始化信号量，调用了UART1——init函数，设置PB11 IO口，使能红外通信。		
 * 参数：	
 * 返回值：
 *******************************************************/
static int infrared_open(struct inode *inode, struct file *filp)
{
	infrared_num++;
	
	UART1_init();
	//PB11 ==0 红外通信开始
	p =ioremap(PIOB_BASE,0xA8); //PB11 zero
	
	*(p + PIO_CODR) = 0x800;
	iounmap(p);
	//初始化信号量
	sema_init(&infrared_sem,0);
	
	printk("##infrared communicate open sucess! \n");

	p = ioremap (US1_BASE_CR, 0xA8);
	printk ("CR is %x.\n", *(p+1));
	printk ("CR is %x.\n", *(p+4));
	printk ("CR is %x.\n", *(p+5));
	printk ("CR is %x.\n", *(p+6));
	printk ("CR is %x.\n", *(p+8));
	printk ("CR is %x.\n", *(p+9));
	printk ("CR is %x.\n", *(p+10));
	printk ("CR is %x.\n", *(p+11));
	iounmap (p);
	return 0;

}
/********************************************************
 * 函数：设备关闭函数
 * 功能：关闭红外通信，PB11 置1		
 * 参数：	
 * 返回值：
 *******************************************************/

static int infrared_release(struct inode *inode, struct file *filp)
{	
		infrared_num--;
		if(infrared_num!=0)
		{
				printk("##there is not eq compile open and release\n");
				return 0;
		}
		p =ioremap(PIOB_BASE,0xA8); //PB11 1
		*(p + PIO_SODR) = 0x800;
		printk("##the Infrared Disable\n");
		iounmap(p);
		return 0;
}
/********************************************************
 * 函数：红外写函数
 * 功能：通过比较用户空间传来的buf长度，选择字符发送或者字符串发送，调用字符发送函数Infrared_UART1_putc
 * 		和字符串发送函数 Infrared_UART1_puts
 * 参数：const char __user *buf 用户空间传进内核的数据
 * 	 size_t count,	: 数据大小。
 * 返回值：
 *******************************************************/
static ssize_t infrared_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos)
{	
	char ch;
	
	if(count == 1)
	{	
		get_user(ch,buf);

		Infrared_UART1_putc(ch);
#ifdef	DEBUG
		printk("##the count is 1\n");
#endif
	}
	else{
#ifdef DEBUG	
		printk("##the count is %d\n",count);
#endif
		Infrared_UART1_puts(buf,count);
	}
	
			
	printk("##this is infrared_write test\n");
	return count;
}
/********************************************************
 * 函数：红外读函数
 * 功能：使能RXRDY 中断，中断产生中断处理函数，等待信号量infrared_sem （该信号由中断处理函数释放）
 *	用户空间调用的read函数，是个等待函数，中断处理程序完成，释放信号两，此时全局变量retch为读到的字符
 * 	调用copy_to_user，把字符传到用户空间。
 * 参数：const char __user *buf   用户空间的数据用来接受内核空间数据
 * 	 size_t count,	: 数据大小。
 * 返回值：
 *******************************************************/
static ssize_t infrared_read(struct file *file,  char __user *buf, size_t count, loff_t *f_pos)
{

	printk("##this is in infrared_read\n");

#if 1	
	p = ioremap(US1_BASE_CR,0x124);
	*(p + (0x8>>2)) = 0x1;

#endif
	//retch = Infrared_UART1_getc();
	down_interruptible(&infrared_sem);
	iounmap(p);
	if(copy_to_user(buf,&retch,1))
	{
		printk("errror copy -to user\n");
	}
#ifdef DEBUG
	printk("\n#####int read the char is%x\n",retch); 
#endif
	return count;
}
/********************************************************
 * 函数：红外控制函数
 * 功能：暂无
 * 参数：
 * 返回值：
 *******************************************************/
static int infrared_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("this is infrared ioctl \n");
	return 0;
}
/********************************************************
 * 函数：中断处理程序
 * 功能：响应中断，读出字符，释放信号两
 * 参数：
 * 返回值：
 *******************************************************/
static irqreturn_t infrared_interrupt(int irq,void *dev_id)
{
#if 1
	//关中断
	*(p + (US1_IDR)) = 0xffffffff;
	printk("##this is in infrared_interrupt\n");

	//读出字符
	Infrared_UART1_getc();
	//释放信号量
	up(&infrared_sem);
#endif	
			
	return IRQ_HANDLED;	
}
/*****************************************************************
 *
 * 红外驱动操作结构体
 *
 ****************************************************************/
struct file_operations infrared_fops = {
	 read:infrared_read,
	 write:infrared_write,
	 open:infrared_open,
	 release:infrared_release,
	 ioctl:infrared_ioctl,
};


int __init infrared_driver_init(void)
{
	int rc;
	// 注册字符设备 
	if ((rc = register_chrdev(infrared_MAJOR, DEVICENAME , &infrared_fops)) < 0){
		printk("infrared driver: can't get major %d\n", infrared_MAJOR);
		return 1;
	}
	//注册中断
	rc = request_irq(7,infrared_interrupt,0,"infrared",NULL);
	if(rc)
	{
		printk(" infrared irq not registered. Error:%d\n",rc);
	}

	
	printk(" the infrared driver is insert \n");
	return 0;
}

/*----------------------------------------------------------------------*/
void __exit infrared_driver_exit(void)
{
	//释放中断
	free_irq(7,NULL);
	//释放设备
	unregister_chrdev(infrared_MAJOR, DEVICENAME);
	
	printk("infrared driver exit\n");
}

module_init(infrared_driver_init);
module_exit(infrared_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karsten Jeppesen <karsten@jeppesens.com>");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");
