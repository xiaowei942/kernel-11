/*
 *  pmm.h 
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (in pmm.c) and the process calling ioctl (pmm_test.c)
 */

#ifndef PMM_H
#define PMM_H

#include <linux/ioctl.h>

/* 
 * The major device number. We can't rely on dynamic 
 * registration any more, because ioctls need to know 
 * it. 
 */
#define MAJOR_NUM 100

/* 
 * Set the message of the device driver 
 */
#define IOCTL_SET_CPUIDLE		_IO(MAJOR_NUM, 0)
#define IOCTL_SET_LCDLIGHTDOWN		_IO(MAJOR_NUM, 1)
#define IOCTL_SET_STANDBY		_IO(MAJOR_NUM, 2)
#define IOCTL_SET_MEM			_IO(MAJOR_NUM, 3)
#define IOCTL_SET_LCDSHUTDOWN		_IO(MAJOR_NUM, 4)
#define IOCTL_SET_LCDWAKEUP		_IO(MAJOR_NUM, 5)
#define IOCTL_SET_LCD_STANDBY		_IO(MAJOR_NUM, 6)
#define IOCTL_EXIT_LCD_STANDBY		_IO(MAJOR_NUM, 7)

#define IOCTL_SET_LCD_TYPE		_IO(MAJOR_NUM, 8)

//#define IOCTL_SYS_SHUTDOWN		_IO(MAJOR_NUM, 8)
//#define IOCTL_SYS_HALT			_IO(MAJOR_NUM, 9)
//#define IOCTL_SYS_REBOOT		_IO(MAJOR_NUM, 10)

#define IOCTL_INFRARED_OPEN		_IO(MAJOR_NUM, 11)
#define IOCTL_INFRARED_CLOSE		_IO(MAJOR_NUM, 12)

#define IOCTL_INFRAD_RX_DIS		_IO(MAJOR_NUM, 13)
#define IOCTL_INFRAD_RX_EN		_IO(MAJOR_NUM, 14)

#define IOCTL_UART_OPEN			_IO(MAJOR_NUM, 15)
#define IOCTL_UART_CLOSE		_IO(MAJOR_NUM, 16)

#define IOCTL_UDP_OPEN			_IO(MAJOR_NUM, 17)
#define IOCTL_UDP_CLOSE			_IO(MAJOR_NUM, 18)

#define IOCTL_UHP_OPEN			_IO(MAJOR_NUM, 19)
#define IOCTL_UHP_CLOSE			_IO(MAJOR_NUM, 20)

#define IS_ALARM_SHUTDOWN		_IO(MAJOR_NUM, 21)

#define IOCTL_KEYB_BEEP			_IO(MAJOR_NUM, 22)

#define IOCTL_1HZ_ENABLE		_IO(MAJOR_NUM, 23)
#define IOCTL_1HZ_DISABLE		_IO(MAJOR_NUM, 24)

#define IOCTL_GET_FIQ			_IO(MAJOR_NUM, 25)

#define IOCTL_GET_SHTDWN		_IO(MAJOR_NUM, 32)
#define IOCTL_SHTDWN_CHARGE		_IO(MAJOR_NUM, 33)


#define FB_SLEEP	0x4
#define FB_STANDBY	0x2

/* 
 * The name of the device file 
 */
#define DEVICE_FILE_NAME "pmm"

#if 0
/************************************
 * The Macro of FrameBuffer
 ***********************************/
#define SLEEP_ENTERY	0x2
#define STANDBY_ENTERY	0x4
#define SLEEP_WAKEUP	0x10002
#define STANDBY_WAKEUP	0x10004
#endif

#endif
