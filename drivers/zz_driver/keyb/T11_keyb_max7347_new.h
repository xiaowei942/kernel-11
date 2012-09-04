

#ifndef max7347_h
#define max7347_h

//#include <stdio.h>
#include <linux/clk.h>

#include <asm/arch/at91_twi.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/arch/at91_pmc.h>

typedef unsigned short int U16;

#define AT91_PIOA_BASE		AT91_PIOA + AT91_BASE_SYS
#define AT91_PIOC_BASE		AT91_PIOC + AT91_BASE_SYS
#define AT91_PIOB_BASE          AT91_PIOB + AT91_BASE_SYS
#define AT91_AIC_BASE		AT91_AIC + AT91_BASE_SYS
#define AT91_PMC_BASE		AT91_PMC + AT91_BASE_SYS

static void __iomem *twi_base;
static void __iomem *aic_base;
static void __iomem *pmc_base;


#define at91_pmc_read(reg)		__raw_readl(pmc_base + (reg))
#define at91_pmc_write(reg, val)	__raw_writel((val), pmc_base + (reg))

#define at91_aic_read(reg)		__raw_readl(aic_base + (reg))
#define at91_aic_write(reg, val)	__raw_writel((val), aic_base + (reg))

#define at91_twi_read(reg)		__raw_readl(twi_base + (reg))
#define at91_twi_write(reg, val)	__raw_writel((val), twi_base + (reg))

#define AT91_MAX7347_I2C_ADDRESS  (0x38<<16) /* Internal addr: 0x38 */

#define IRQ0		(0x1 << AT91SAM9261_ID_IRQ0)

/*****************************************************************
 *
 ****************************************************************/
#define MAX_BUF_NUM	16

/* MAX7347 register offset */
#define MAX7347_KEYFIFO_REG		0x00
#define MAX7347_DEBOUNCE_REG      	0x01
#define MAX7347_AUTOREPEAT_REG		0x02
#define MAX7347_INTERRUPT_REG		0x03
#define MAX7347_CONFIGURATION_REG	0x04
#define MAX7347_PORT_REG		0x05
#define MAX7347_KEYSOUND_REG		0x06
#define MAX7347_ALERTSOUND_REG		0x07

#define AT91_PA7_TWD		(unsigned int) (0x1 << 7)
#define AT91_PA8_TWCK		(unsigned int) (0x1 << 8)

#define TWI_NULL		0xff
#define TWI_READ		0x1
#define TWI_WRITE		0x0
//#define AT91_TWI_SWRST		((unsigned int) 0x1 << 7)	

/************************************************************************
 *
 * ioctl
 *
 ***********************************************************************/
#define KEYB_CMD_CLRBUF		0x005
#define KEYB_CMD_HAVEKEY	0x006

/************************************************************************
 *
 *
 *
 ************************************************************************/
#define PVK_DELETECHAR     0x08
#define PVK_RETURN         0x0D
#define PVK_ESCAPE         0x1B
#define PVK_PAGEUP         0x21
#define PVK_PAGEDOWN       0x22
#define PVK_END            0x23
#define PVK_HOME           0x24
#define PVK_INSERT         0x2D
#define PVK_DELETE         0x2E
#define PVK_LEFT           0x25
#define PVK_UP             0x26
#define PVK_RIGHT          0x27
#define PVK_DOWN           0x28

#if 1
const unsigned char key_scan_map[] = {0x0b,	0x02,	0x03,	//0x00='0',  0x01='1', 0x02='4'
				      0x08,	'f',	0x7b, 	//0x03='7',  0x04=fun, 0x05=right
			     	      0x7f,	'f',	0x34,	//0x06=esc, 0x07=shift, 0x08='.'
			    	      0x03,	0x06,	0x09,	//0x09='2', 0x0a='5', 0x0b='8'
			     	      'f',	0x1f,	0x7e,	//0x0c=tab, 0x0d=down, 0x0e=up
				      'f',	0x0e,	0x04,	//0x0f=banklight, 0x10=del, 0x11='3'
			     	      0x07,	0x0a,	'f',	//0x12='6', 0x13='9', 0x14=help
			     	      0x79,	0x7d,	'f'};	//0x15=left, 0x16=enter, 0x17=power


const unsigned char key_cook_map[] = {'0',		'1',		'4',		//0x00='0',  0x01='1', 0x02='4'
			     	      '7',		'f',		PVK_LEFT, 	//0x03='7',  0x04=fun, 0x05=left
			     	      PVK_ESCAPE,	'f',		'.',		//0x06=esc, 0x07=shift, 0x08='.'
			     	      '2',		'5',		'8',		//0x09='2', 0x0a='5', 0x0b='8'
			     	      'f',		PVK_DOWN,	PVK_UP,		//0x0c=tab, 0x0d=down, 0x0e=up
			     	      'f',		PVK_DELETE,	'3',		//0x0f=banklight, 0x10=del, 0x11='3'
			     	      '6',		'9',		'f',		//0x12='6', 0x13='9', 0x14=help
			     	      PVK_RIGHT,	PVK_RETURN,	'f'};		//0x15=right, 0x16=enter, 0x17=power

const unsigned short int  key_zzcooked_map[24][5] = {
					{0x00,0x0B30,0x1655,0x2F56,0x1157},	//"K00","0","U","v","W"
					{0x01,0x0231,0x3920,0x324D,0x314E},	//"K01","1"," ","M","N"
					{0x02,0x0534,0x0C2D,0x2247,0x2348},	//"K02","4","-","G","H"
					{0x03,0x0837,0x0D2B,0x1E41,0x3042},	//"K03","7","+","A","B"
	
					{0x04,0x8200,0x8214,0x0000,0x0000},	//"K04","功能","shift+功能"
					{0x05,0x4B00,0x4700,0x0000,0x0000},	//"K05","<","shift+<"
					{0x06,0x011B,0x2E03,0x0000,0x0000},	//"K06","退出","shift+退出"
					{0x07,0x0000,0x0000,0x0000,0x0000},	//"K07","换档"

					{0x08,0x342E,0x2D58,0x1559,0x2C5A},	//"K08",".","X","Y","Z"
					{0x09,0x0332,0x184F,0x1950,0x1051},	//"K09","2","O","P","Q"
					{0x0A,0x0635,0x352F,0x1749,0x244A},	//"K10","5","/","I","J"
					{0x0B,0x0938,0x092A,0x2E43,0x2044},	//"K11","8","*","C","D"
	
					{0x0C,0x9600,0x9AF1,0x0000,0x0000},	//"K12"切换"
					{0x0D,0x5000,0x5100,0x0000,0x0000},	//"K13","V","shift+V"
					{0x0E,0x4800,0x4900,0x0000,0x0000},	//"K14","^","shift+^"
					{0x0F,0x9700,0x0000,0x0000,0x0000},	//"K15","背光"
					{0x10,0x0E08,0x2E04,0x0000,0x0000},	//"K16","删除","shift+删除"
		
					{0x11,0x0433,0x1352,0x1F53,0x1454},	//"K17","3","R","S","T"
					{0x12,0x0736,0x0B29,0x254B,0x264C},	//"K18","6",")","K","L"
					{0x13,0x0A39,0x0A28,0x1245,0x2146},	//"K19","9","(","E","F"

					{0x14,0x3B00,0x5400,0x0000,0x0000},	//"K20","帮助","shift+帮助"
					{0x15,0x4D00,0x4f00,0x0000,0x0000},	//"K21",">","shift+>"
					{0x16,0x1C0D,0x0E00,0x0000,0x0000},	//"K22","确定","shift+确定"
					{0x17,0x0000,0x0000,0x0000,0x0000}};	//"K23","关机"
#endif

/* inline function */

inline unsigned char raw2scancode (int num);
inline int kbufin (U16 key);
inline U16 readkey(void);


int Key_Read (char data);
#endif

