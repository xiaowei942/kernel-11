#ifndef T11_FB
#define T11_FB

#include <linux/ioctl.h>
#include <asm/atomic.h>

/*********************************************************************
 *
 *
 *
 ********************************************************************/

typedef struct fdc
{
	unsigned short int x1;
	unsigned short int y1;
	unsigned short int x2;
	unsigned short int y2;
}FDC;
#define FDCLEN	 8

//#define T11_AUTO_FLUSH_TIMETASK
#define T11_AUTO_FLUSH_KTHREAD

#ifdef T11_AUTO_FLUSH_KTHREAD
typedef struct movie_fb_addr
{
	atomic_t	sign[2];
	u16		*fb_buf[2];

	u8		write_sign;
	u8		read_sign;
}MFA;
#endif

static u32 sIsILI9325 = 0;
#if 0
u32 _SetILI9325(u16 tmp)
{
	printk (KERN_ALERT"petworm: _SetILI9325: LCD chip id is %x.\n", tmp);
	if (tmp == 0x9320)
		sIsILI9325 = 0;
	else
		sIsILI9325 = 1;
}
#else
u32 _SetILI9325(u8 tmp)
{
	printk (KERN_ALERT "petworm: _SetILI9325 is %x.\n", tmp);
	sIsILI9325 = tmp;
}
#endif

u32 _GetILI9325()
{
	printk (KERN_ALERT"petworm: _GetILI9325: sIsILI9325 is %x.\n", sIsILI9325);
	return sIsILI9325;
}

/*
 * Functions
 */

void Lcd_Init(void);
void Rectangle(int, int, int, int, u16);
void Mop(int, int, int, int, u16);
void Flash_Frame(void);
void FlushRect(unsigned short int x1,unsigned short int x2,unsigned short int y1,unsigned short int y2);

void fb_exit_sleep (unsigned short int cmd);
void fb_entry_sleep (unsigned short int cmd);

int  init_fb_module(void);
void cleanup_fb_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_mmap(struct file *filp, struct vm_area_struct *vma);
static int device_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

inline void flush_DCache (unsigned short int x1, unsigned short int x2, unsigned short int y1, unsigned short int y2);
inline void flush_DCache_all (void);

inline void MainLCD_Command(u16 tft_command);
inline void MainLCD_Data(u16 tft_data);
inline void MainLCD_Read(u16 *tmp);


#define SUCCESS 0
#define DEVICE_NAME "T11_FrameBuffer"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */
#define FB_MAJOR	244

#define IOCTL_FLUSH		_IO(FB_MAJOR, 0)
#define AUTO_FLUSH_ON		_IO(FB_MAJOR, 1)
#define AUTO_FLUSH_OFF		_IO(FB_MAJOR, 2)
#define AUTO_FLUSH_NUM		_IO(FB_MAJOR, 3)
#define SHIFT_DISPLAY_MODE	_IO(FB_MAJOR, 4)
#define ROTATE_FRAMEBUFFER	_IO(FB_MAJOR, 5)
#define ROTATE_SCREEN		_IO(FB_MAJOR, 6)

#define T11_FLUSH_8		(0xf428)
#define T11_FlUSH_5		(0xf425)
#define T11_FLUSH_4		(0xf424)

#define T11_FLUSH_NORMAL	(0xf430)
#define T11_FLUSH_MOIVE		(0xf431)

#define FLUSH_TIME	8

#undef FB_DEBUG

#define HORIZONTAL 240 
#define VERTICAL 320

#define OLD_FB
#define _OTHER_LCD

#define SLEEP_ENTERY	0x4
#define SLEEP_WAKEUP	0x10004
#define STANDBY_ENTERY	0x2
#define STANDBY_WAKEUP	0x10002

#endif
