/*********************************************************************
 *  linux/init/progress.c
 *
 *  Copyright (C) 2008  ZhuBin
 *
 *  Added the progress bar of T11 system welcome image.
 *  the progress bar star piont is (52, 242), end piont is (178, 252),
 *  and there is 14 block in progress bar.
 ********************************************************************/
#include <linux/mm.h>
#include <asm/uaccess.h>	/* for put_user */
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/at91sam9261_matrix.h>

#include <asm/delay.h>


#define STARTX		53
#define STARTY		242
#define ENDX		190
#define ENDY		252

#define LENX		137
#define LENY		10

#define BLOCKX		8
#define BLOCKY		10
#define BLK_CLR		0x0013

//void T11_lcd_early_init (void);
//void T11_lcd_progress (int num);
volatile unsigned short *cmd_port;
volatile unsigned short *dat_port;


inline void
T11_LCD_Command(u16 tft_cmd)
{
	*cmd_port = tft_cmd;
}

inline void
T11_LCD_Data(u16 tft_dat)
{
	*dat_port = tft_dat;
}

inline void
T11_LCD_Read (u16 *tmp)
{
	*tmp = *dat_port;
}

#ifdef CONFIG_T11_LCD_WEL
static int progress_blk = 0;

void T11_lcd_progress (int num)
{
	int sx, sy, ex, ey;
	int i;

	if (num == 100)
	{
		if (progress_blk > 11)
			return;

		progress_blk += 1;
		sx = STARTX + progress_blk * (BLOCKX + 1);
		sy = STARTY;
		ex = sx + BLOCKX - 1;
		ey = sy + BLOCKY - 1;
	}
	else
	{
		progress_blk = num;
		sx = STARTX + num * (BLOCKX + 1);
		sy = STARTY;
		ex = sx + BLOCKX - 1;
		ey = sy + BLOCKY - 1;
	}

	printk (KERN_ALERT "screen enter:%d.\n", progress_blk);
	/* set the LCD controller in slow mode */

	// 行 * 列 即为将要写的像素点数	
	/*50 寄存器,液晶ram上的水平的起始坐标*/
	T11_LCD_Command(0x0050); T11_LCD_Data(sx); 
   	/*51 寄存器，液晶ram上的水平方向的结束坐标*/
	T11_LCD_Command(0x0051); T11_LCD_Data(ex);
 	/*52 寄存器，液晶ram上的竖直方向的起始坐标**/ 
	T11_LCD_Command(0x0052); T11_LCD_Data(sy);
	/*53 寄存器，液晶ram上的竖直方向的结束坐标**/
	T11_LCD_Command(0x0053); T11_LCD_Data(ey);

	/*20寄存器，将要写液晶的水平起始坐标*/
	T11_LCD_Command(0x0020); T11_LCD_Data(sx);
	/*21寄存器，将要写液晶的竖直起始坐标*/
	T11_LCD_Command(0x0021); T11_LCD_Data(sy);

	T11_LCD_Command(0x0003); T11_LCD_Data(0x1030);
	/*22寄存器，向液晶写数据显示*/
	T11_LCD_Command(0x0022);

	for (i = 0; i < BLOCKX * BLOCKY; i++)
		T11_LCD_Data(BLK_CLR);

	T11_LCD_Command(0x0003); T11_LCD_Data(0x1230);
	/* backup the LCD controller mode */

}
//extern u32 _SetILI9325(u16 tmp);
void T11_lcd_early_init (void)
{
	printk (KERN_ALERT "screen init.\n");
	unsigned short tmp;

	cmd_port = ioremap (0x60000000, 2);
	dat_port = ioremap (0x60000004, 2);

	printk (KERN_ALERT "petworm: cmd_port is %x.\n", cmd_port);
	printk (KERN_ALERT "petworm: dat_port is %x.\n", dat_port);
	/* because we initial the LCD controller in u-boot */
	/* we needn't initial most steps again in here */

//	T11_LCD_Command(0x0000); T11_LCD_Read (&tmp);
//	printk (KERN_ALERT "petworm: xxx LCD chip id is %x.\n", tmp);
//#if 0
//	if (tmp == 0x9320)
//		sIsILI9325 = 0;
//	else
//		sIsILI9325 = 1;
//#else
//	_SetILI9325 (tmp);
//#endif
}

void T11_lcd_progress_over (void)
{
	iounmap (cmd_port);
	iounmap (dat_port);
}

EXPORT_SYMBOL(T11_lcd_early_init);
EXPORT_SYMBOL(T11_lcd_progress);
EXPORT_SYMBOL(T11_lcd_progress_over);

/*
	T11_lcd_early_init ();		// petworm
	T11_lcd_progress (1);
	T11_lcd_progress (2);
	T11_lcd_progress (3);
	T11_lcd_progress (4);
*/

#endif /* CONFIG_T11_LCD_WEL */

#ifdef CONFIG_T11_LCD_ROLL
void rolling_bar_init(void)
{
	printk (KERN_ALERT "screen init.\n");

	cmd_port = ioremap (0x60000000, 2);
	dat_port = ioremap (0x60000004, 2);

	printk (KERN_ALERT "petworm: cmd_port is %x.\n", cmd_port);
	printk (KERN_ALERT "petworm: dat_port is %x.\n", dat_port);
	/* because we initial the LCD controller in u-boot */
	/* we needn't initial most steps again in here */
}

void time_roll (int pos)
{
	int sx, sy, ex, ey;
	int i, j, k;
	int blknu;

	unsigned short rb[1370];

	if ((pos >= 4) && (pos <= 14))
	{
		blknu = 5;
	}
	else
	{
		switch (pos)
		{
			case 0:
			case 18:
				blknu = 1;
				break;
			case 1:
			case 17:
				blknu = 2;
				break;
			case 2:
			case 16:
				blknu = 3;
				break;
			case 3:
			case 15:
				blknu = 4;
				break;
		}
	}

	sx = STARTX + ((pos - 5) > 0 ? (pos - 5) : 0) * (BLOCKX + 1);
	sy = STARTY;
	ex = sx + (BLOCKX * blknu);
	ey = sy + (BLOCKY * blknu);

	memset (rb, 0xff, 2740);

	for (k = 0; k < blknu; k++)
	{
		for (i = 0; i < BLOCKX; i++)
		for (j = 0; j < BLOCKY; j++)
		{
			rb[sx + i + (k * (BLOCKX + 1)) + j * LENX] = BLK_CLR;
		}
	}

	printk (KERN_ALERT "screen enter.\n");
	/* set the LCD controller in slow mode */

	// 行 * 列 即为将要写的像素点数	
	/*50 寄存器,液晶ram上的水平的起始坐标*/
	T11_LCD_Command(0x0050); T11_LCD_Data(STARTX); 
   	/*51 寄存器，液晶ram上的水平方向的结束坐标*/
	T11_LCD_Command(0x0051); T11_LCD_Data(ENDX);
 	/*52 寄存器，液晶ram上的竖直方向的起始坐标**/ 
	T11_LCD_Command(0x0052); T11_LCD_Data(STARTY);
	/*53 寄存器，液晶ram上的竖直方向的结束坐标**/
	T11_LCD_Command(0x0053); T11_LCD_Data(ENDY);

	/*20寄存器，将要写液晶的水平起始坐标*/
	T11_LCD_Command(0x0020); T11_LCD_Data(STARTX);
	/*21寄存器，将要写液晶的竖直起始坐标*/
	T11_LCD_Command(0x0021); T11_LCD_Data(STARTY);

	T11_LCD_Command(0x0003); T11_LCD_Data(0x1030);
	/*22寄存器，向液晶写数据显示*/
	T11_LCD_Command(0x0022);

	for (i = 0; i < LENX * LENY; i++)
		T11_LCD_Data(BLK_CLR);

	T11_LCD_Command(0x0003); T11_LCD_Data(0x1230);
	/* backup the LCD controller mode */
}

EXPORT_SYMBOL(rolling_bar_init);
EXPORT_SYMBOL(time_roll);

#endif /* CONFIG_T11_LCD_ROLL */
