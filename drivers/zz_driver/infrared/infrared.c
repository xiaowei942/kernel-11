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
 * �����������ַ������ͺ���
 * ���ܣ��û��ռ���ַ���ͨ����������
 * ������const char *buffer ����Ҫ���͵��ַ���
 * 	size_t 	count 	  :  Ҫ���͵��ַ�������
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
 * �����������ַ����ͺ���
 * ���ܣ���һ���ַ�ͨ������ڷ��ͳ�ȥ
 * ������const char car ����Ҫ���͵��ַ�
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
 * ������ͨ����������ַ�����
 * ���ܣ�ͨ���������һ���ַ��������ַ������ȫ�ֱ�����retch�У�retchΪchar ��ռ8λ������9λ��Ȼ��PHR����ЧλΪ9λ��
 * 		���ü��̵�0��9 ���ԡ���
 * ������void �ú�����Ҫ���жϴ���������
 * ����ֵ���޷���֮��
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
 * ������UART1��ʼ������
 * ���ܣ���ʼ�����⽫Ҫ�õ������蹦�ܿں�IO�ڣ�ʹ��UART1��ʱ�ӣ����ݲ�����Ϊ1200����ո�Uart��ص�PD�Ĵ���
 * 	����UART1 Ϊ ��ͨģʽ 1λֹͣλ ��У�� 8λ ʼ��Ϊ��ʼ�� 99.3Mhz
 * ������
 * ����ֵ��
 *******************************************************/
void UART1_init(void)
{
	int tmp;
#ifdef DEBUG
	printk("##this is in uart1_init\n");
#endif
	//���� PB11	��ʹ�ܺ���
	p =ioremap(PIOB_BASE,0xA8);
	*(p + PIO_PER) = 0x940;
	*(p + PIO_OER) = 0x940;
	*(p + PIO_SODR) = 0x940;
	iounmap(p);

	// ���ý�Ҫ�õ�������� SCK RTS1 CTS1 RXD1 TXD1
	p =ioremap(PIOA_BASE,0xA8); //SCK RTS1 CTS1
	*(p + PIO_BSR) = (AT91C_PIO_PA11|AT91C_PIO_PA12|AT91C_PIO_PA13);
	*(p + PIO_PDR) = (AT91C_PIO_PA11|AT91C_PIO_PA12|AT91C_PIO_PA13);
	iounmap(p);
	
	p =ioremap(PIOC_BASE,0xA8);// RXD1 TXD1
	*(p + PIO_ASR) = (AT91C_PIO_PC12|AT91C_PIO_PC13);
	*(p + PIO_PDR) = (AT91C_PIO_PC12|AT91C_PIO_PC13);
	iounmap(p);


	for(tmp = 0;tmp<10000;tmp++);
	//��UART1 �ṩʱ��
	p =ioremap(PMC_PCER,4); 
	*p = (0x1 << ID_US1);
	iounmap(p);

	//����UART �ļĴ���
	p = ioremap(US1_BASE_CR,0x124);
	*(p + US1_IDR) = (unsigned int ) -1;
	*p = 	AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS ;
	//���ú���Ĳ�����
	*(p + US1_BRGR) = US1_Baudrate(AT91C_MASTER_CLOCK,AT91C_BAUDRATE_1200);
	//���ô�����ʱ 0
	*(p + US1_TTGR) = TIME_GUARD;
	
	//set PDC for UART1 ���ø�UART ��ص�PDC 
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
	
	//EN TX and RX ʹ�ܷ��� ����
	*(p + US1_PTCR) = AT91C_PDC_RXTEN;
	*(p + US1_PTCR) = AT91C_PDC_TXTEN;
	
	//set US1_MR ����UART1 Ϊ ��ͨģʽ 1λֹͣλ ��У�� 8λ ʼ��Ϊ��ʼ�� 99.3Mhz 
	*(p + US1_MR) = (AT91C_US_USMODE_NORMAL |AT91C_US_NBSTOP_1_BIT | AT91C_US_PAR_NONE | AT91C_US_CHRL_8_BITS |AT91C_US_CLKS_CLOCK);
	
	*p |= AT91C_US_TXEN;
	*p |= AT91C_US_RXEN;
	iounmap(p);

}
/********************************************************
 * ���������ú��Ⲩ���ʵĺ���
 * ���ܣ��� UART1����init��ʼ�������������ò����ʣ�Ϊ���ø�׼ȷ�Ĳ����ʣ���ѭ���������ԭ��		
 * ������const unsigned int main_clock�� ��ʱ��Ƶ�ʣ�99.3
 *	 const unsigned int baud_rate :  ���Ⲩ���� 1200
 * ����ֵ������ �����Ĳ����ʵ�ֵ
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
 * �������豸�򿪺���
 * ���ܣ���ʼ�������õ���һϵ�еļĴ�������ʼ���ź�����������UART1����init����������PB11 IO�ڣ�ʹ�ܺ���ͨ�š�		
 * ������	
 * ����ֵ��
 *******************************************************/
static int infrared_open(struct inode *inode, struct file *filp)
{
	infrared_num++;
	
	UART1_init();
	//PB11 ==0 ����ͨ�ſ�ʼ
	p =ioremap(PIOB_BASE,0xA8); //PB11 zero
	
	*(p + PIO_CODR) = 0x800;
	iounmap(p);
	//��ʼ���ź���
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
 * �������豸�رպ���
 * ���ܣ��رպ���ͨ�ţ�PB11 ��1		
 * ������	
 * ����ֵ��
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
 * ����������д����
 * ���ܣ�ͨ���Ƚ��û��ռ䴫����buf���ȣ�ѡ���ַ����ͻ����ַ������ͣ������ַ����ͺ���Infrared_UART1_putc
 * 		���ַ������ͺ��� Infrared_UART1_puts
 * ������const char __user *buf �û��ռ䴫���ں˵�����
 * 	 size_t count,	: ���ݴ�С��
 * ����ֵ��
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
 * ���������������
 * ���ܣ�ʹ��RXRDY �жϣ��жϲ����жϴ��������ȴ��ź���infrared_sem �����ź����жϴ������ͷţ�
 *	�û��ռ���õ�read�������Ǹ��ȴ��������жϴ��������ɣ��ͷ��ź�������ʱȫ�ֱ���retchΪ�������ַ�
 * 	����copy_to_user�����ַ������û��ռ䡣
 * ������const char __user *buf   �û��ռ���������������ں˿ռ�����
 * 	 size_t count,	: ���ݴ�С��
 * ����ֵ��
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
 * ������������ƺ���
 * ���ܣ�����
 * ������
 * ����ֵ��
 *******************************************************/
static int infrared_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("this is infrared ioctl \n");
	return 0;
}
/********************************************************
 * �������жϴ������
 * ���ܣ���Ӧ�жϣ������ַ����ͷ��ź���
 * ������
 * ����ֵ��
 *******************************************************/
static irqreturn_t infrared_interrupt(int irq,void *dev_id)
{
#if 1
	//���ж�
	*(p + (US1_IDR)) = 0xffffffff;
	printk("##this is in infrared_interrupt\n");

	//�����ַ�
	Infrared_UART1_getc();
	//�ͷ��ź���
	up(&infrared_sem);
#endif	
			
	return IRQ_HANDLED;	
}
/*****************************************************************
 *
 * �������������ṹ��
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
	// ע���ַ��豸 
	if ((rc = register_chrdev(infrared_MAJOR, DEVICENAME , &infrared_fops)) < 0){
		printk("infrared driver: can't get major %d\n", infrared_MAJOR);
		return 1;
	}
	//ע���ж�
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
	//�ͷ��ж�
	free_irq(7,NULL);
	//�ͷ��豸
	unregister_chrdev(infrared_MAJOR, DEVICENAME);
	
	printk("infrared driver exit\n");
}

module_init(infrared_driver_init);
module_exit(infrared_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karsten Jeppesen <karsten@jeppesens.com>");
MODULE_DESCRIPTION("Driver for the Total Impact briQ front panel");
