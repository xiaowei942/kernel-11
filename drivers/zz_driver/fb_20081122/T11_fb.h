#ifndef T11_FB
#define T11_FB

#include <linux/ioctl.h>

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

#define SUCCESS 0
#define DEVICE_NAME "T11_FrameBuffer"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */
#define FB_MAJOR	244

#define IOCTL_FLUSH		_IO(FB_MAJOR, 0)
#define AUTO_FLUSH_ON		_IO(FB_MAJOR, 1)
#define AUTO_FLUSH_OFF		_IO(FB_MAJOR, 2)

#define FLUSH_TIME	8

#undef FB_DEBUG

#define HORIZONTAL 240 
#define VERTICAL 320
#define OLD_FB

#define SLEEP_ENTERY	0x4
#define SLEEP_WAKEUP	0x10004
#define STANDBY_ENTERY	0x2
#define STANDBY_WAKEUP	0x10002

#endif
