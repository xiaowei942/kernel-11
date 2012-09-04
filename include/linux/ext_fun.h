#ifndef T11_EXPORT_FILE
#define T11_EXPORT_FILE


/***********************************************
 * T11 define signals	range:0x30-0x3b
 **********************************************/
#define ZZSIGSEC	0x3b
#define ZZSIGALM	0x3a
#define ZZPWRKEY	0x39
#define	ZZCHARGE	0x38
#define ZZLOWPWR	0x37
#define ZZSHTDWN	0x36

/***********************************************
 * FrameBuffer export functiom
 **********************************************/
extern void fb_entry_sleep (unsigned short int cmd);
extern void fb_exit_sleep (unsigned short int cmd);

extern void kernel_halt (void);
extern void kernel_power_off (void);
extern void kernel_restart (char *cmd);

extern void at91_set_cpu_stop (int val);
extern int at91_suspend_stop_cpu(void);

extern void set_alarm_shutdown (void);

extern unsigned char get_charge_state(void);

#endif
