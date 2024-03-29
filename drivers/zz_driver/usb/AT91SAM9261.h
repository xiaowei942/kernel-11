#ifndef AT91SAM9261H
#define AT91SAM9261H

typedef volatile unsigned int AT91_REG;// Hardware register definition

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR System Peripherals
// *****************************************************************************
typedef struct _AT91S_SYS {
	AT91_REG	 SDRAMC_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SDRAMC_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SDRAMC_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SDRAMC_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SDRAMC_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SDRAMC_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SDRAMC_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SDRAMC_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_MDR; 	// SDRAM Memory Device Register
	AT91_REG	 Reserved0[118]; 	// 
	AT91_REG	 SMC_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SMC_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SMC_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SMC_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SMC_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SMC_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SMC_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SMC_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SMC_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SMC_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SMC_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SMC_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SMC_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SMC_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SMC_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SMC_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SMC_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SMC_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SMC_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SMC_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SMC_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SMC_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SMC_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SMC_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SMC_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SMC_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SMC_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SMC_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SMC_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SMC_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SMC_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SMC_CTRL7; 	//  Control Register for CS 7
	AT91_REG	 Reserved1[96]; 	// 
	AT91_REG	 MATRIX_MCFG; 	//  Master Configuration Register
	AT91_REG	 MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 MATRIX_TCMR; 	//  Slave 0 Special Function Register
	AT91_REG	 Reserved3[2]; 	// 
	AT91_REG	 MATRIX_EBICSA; 	//  Slave 3 Special Function Register
	AT91_REG	 MATRIX_USBPCR; 	//  Slave 4 Special Function Register
	AT91_REG	 Reserved4[3]; 	// 
	AT91_REG	 MATRIX_VERSION; 	//  Version Register
	AT91_REG	 Reserved5[110]; 	// 
	AT91_REG	 AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved6[2]; 	// 
	AT91_REG	 AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved7[1]; 	// 
	AT91_REG	 AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 AIC_FFSR; 	// Fast Forcing Status Register
	AT91_REG	 Reserved8[45]; 	// 
	AT91_REG	 DBGU_CR; 	// Control Register
	AT91_REG	 DBGU_MR; 	// Mode Register
	AT91_REG	 DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 DBGU_CSR; 	// Channel Status Register
	AT91_REG	 DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved9[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved10[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 DBGU_PTSR; 	// PDC Transfer Status Register
	AT91_REG	 Reserved11[54]; 	// 
	AT91_REG	 PIOA_PER; 	// PIO Enable Register
	AT91_REG	 PIOA_PDR; 	// PIO Disable Register
	AT91_REG	 PIOA_PSR; 	// PIO Status Register
	AT91_REG	 Reserved12[1]; 	// 
	AT91_REG	 PIOA_OER; 	// Output Enable Register
	AT91_REG	 PIOA_ODR; 	// Output Disable Registerr
	AT91_REG	 PIOA_OSR; 	// Output Status Register
	AT91_REG	 Reserved13[1]; 	// 
	AT91_REG	 PIOA_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIOA_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIOA_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 PIOA_SODR; 	// Set Output Data Register
	AT91_REG	 PIOA_CODR; 	// Clear Output Data Register
	AT91_REG	 PIOA_ODSR; 	// Output Data Status Register
	AT91_REG	 PIOA_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIOA_IER; 	// Interrupt Enable Register
	AT91_REG	 PIOA_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIOA_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIOA_ISR; 	// Interrupt Status Register
	AT91_REG	 PIOA_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIOA_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIOA_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved15[1]; 	// 
	AT91_REG	 PIOA_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIOA_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIOA_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 PIOA_ASR; 	// Select A Register
	AT91_REG	 PIOA_BSR; 	// Select B Register
	AT91_REG	 PIOA_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved17[9]; 	// 
	AT91_REG	 PIOA_OWER; 	// Output Write Enable Register
	AT91_REG	 PIOA_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIOA_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved18[85]; 	// 
	AT91_REG	 PIOB_PER; 	// PIO Enable Register
	AT91_REG	 PIOB_PDR; 	// PIO Disable Register
	AT91_REG	 PIOB_PSR; 	// PIO Status Register
	AT91_REG	 Reserved19[1]; 	// 
	AT91_REG	 PIOB_OER; 	// Output Enable Register
	AT91_REG	 PIOB_ODR; 	// Output Disable Registerr
	AT91_REG	 PIOB_OSR; 	// Output Status Register
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 PIOB_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIOB_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIOB_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved21[1]; 	// 
	AT91_REG	 PIOB_SODR; 	// Set Output Data Register
	AT91_REG	 PIOB_CODR; 	// Clear Output Data Register
	AT91_REG	 PIOB_ODSR; 	// Output Data Status Register
	AT91_REG	 PIOB_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIOB_IER; 	// Interrupt Enable Register
	AT91_REG	 PIOB_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIOB_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIOB_ISR; 	// Interrupt Status Register
	AT91_REG	 PIOB_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIOB_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIOB_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved22[1]; 	// 
	AT91_REG	 PIOB_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIOB_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIOB_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved23[1]; 	// 
	AT91_REG	 PIOB_ASR; 	// Select A Register
	AT91_REG	 PIOB_BSR; 	// Select B Register
	AT91_REG	 PIOB_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved24[9]; 	// 
	AT91_REG	 PIOB_OWER; 	// Output Write Enable Register
	AT91_REG	 PIOB_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIOB_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved25[85]; 	// 
	AT91_REG	 PIOC_PER; 	// PIO Enable Register
	AT91_REG	 PIOC_PDR; 	// PIO Disable Register
	AT91_REG	 PIOC_PSR; 	// PIO Status Register
	AT91_REG	 Reserved26[1]; 	// 
	AT91_REG	 PIOC_OER; 	// Output Enable Register
	AT91_REG	 PIOC_ODR; 	// Output Disable Registerr
	AT91_REG	 PIOC_OSR; 	// Output Status Register
	AT91_REG	 Reserved27[1]; 	// 
	AT91_REG	 PIOC_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIOC_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIOC_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved28[1]; 	// 
	AT91_REG	 PIOC_SODR; 	// Set Output Data Register
	AT91_REG	 PIOC_CODR; 	// Clear Output Data Register
	AT91_REG	 PIOC_ODSR; 	// Output Data Status Register
	AT91_REG	 PIOC_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIOC_IER; 	// Interrupt Enable Register
	AT91_REG	 PIOC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIOC_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIOC_ISR; 	// Interrupt Status Register
	AT91_REG	 PIOC_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIOC_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIOC_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved29[1]; 	// 
	AT91_REG	 PIOC_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIOC_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIOC_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved30[1]; 	// 
	AT91_REG	 PIOC_ASR; 	// Select A Register
	AT91_REG	 PIOC_BSR; 	// Select B Register
	AT91_REG	 PIOC_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved31[9]; 	// 
	AT91_REG	 PIOC_OWER; 	// Output Write Enable Register
	AT91_REG	 PIOC_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIOC_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved32[213]; 	// 
	AT91_REG	 PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved33[1]; 	// 
	AT91_REG	 PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved34[1]; 	// 
	AT91_REG	 PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 PMC_PLLAR; 	// PLL A Register
	AT91_REG	 PMC_PLLBR; 	// PLL B Register
	AT91_REG	 PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved35[3]; 	// 
	AT91_REG	 PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved36[36]; 	// 
	AT91_REG	 RSTC_RCR; 	// Reset Control Register
	AT91_REG	 RSTC_RSR; 	// Reset Status Register
	AT91_REG	 RSTC_RMR; 	// Reset Mode Register
	AT91_REG	 Reserved37[1]; 	// 
	AT91_REG	 SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SHDWC_SHSR; 	// Shut Down Status Register
	AT91_REG	 Reserved38[1]; 	// 
	AT91_REG	 RTTC_RTMR; 	// Real-time Mode Register
	AT91_REG	 RTTC_RTAR; 	// Real-time Alarm Register
	AT91_REG	 RTTC_RTVR; 	// Real-time Value Register
	AT91_REG	 RTTC_RTSR; 	// Real-time Status Register
	AT91_REG	 PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 PITC_PIIR; 	// Period Interval Image Register
	AT91_REG	 WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 WDTC_WDSR; 	// Watchdog Status Register
	AT91_REG	 Reserved39[1]; 	// 
	AT91_REG	 SYS_GPBR0; 	// General Purpose Register 0
	AT91_REG	 SYS_GPBR1; 	// General Purpose Register 1
	AT91_REG	 SYS_GPBR2; 	// General Purpose Register 2
	AT91_REG	 SYS_GPBR3; 	// General Purpose Register 3
} AT91S_SYS, *AT91PS_SYS;

// -------- GPBR : (SYS Offset: 0x1350) GPBR General Purpose Register -------- 
// -------- GPBR : (SYS Offset: 0x1354) GPBR General Purpose Register -------- 
// -------- GPBR : (SYS Offset: 0x1358) GPBR General Purpose Register -------- 
// -------- GPBR : (SYS Offset: 0x135c) GPBR General Purpose Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR SDRAM Controller Interface
// *****************************************************************************
typedef struct _AT91S_SDRAMC {
	AT91_REG	 SDRAMC_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SDRAMC_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SDRAMC_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SDRAMC_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SDRAMC_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SDRAMC_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SDRAMC_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SDRAMC_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_MDR; 	// SDRAM Memory Device Register
} AT91S_SDRAMC, *AT91PS_SDRAMC;

// -------- SDRAMC_MR : (SDRAMC Offset: 0x0) SDRAM Controller Mode Register -------- 
#define AT91C_SDRAMC_MODE     ((unsigned int) 0xF <<  0) // (SDRAMC) Mode
#define 	AT91C_SDRAMC_MODE_NORMAL_CMD           ((unsigned int) 0x0) // (SDRAMC) Normal Mode
#define 	AT91C_SDRAMC_MODE_NOP_CMD              ((unsigned int) 0x1) // (SDRAMC) Issue a NOP Command at every access
#define 	AT91C_SDRAMC_MODE_PRCGALL_CMD          ((unsigned int) 0x2) // (SDRAMC) Issue a All Banks Precharge Command at every access
#define 	AT91C_SDRAMC_MODE_LMR_CMD              ((unsigned int) 0x3) // (SDRAMC) Issue a Load Mode Register at every access
#define 	AT91C_SDRAMC_MODE_RFSH_CMD             ((unsigned int) 0x4) // (SDRAMC) Issue a Refresh
#define 	AT91C_SDRAMC_MODE_EXT_LMR_CMD          ((unsigned int) 0x5) // (SDRAMC) Issue an Extended Load Mode Register
#define 	AT91C_SDRAMC_MODE_DEEP_CMD             ((unsigned int) 0x6) // (SDRAMC) Enter Deep Power Mode
// -------- SDRAMC_TR : (SDRAMC Offset: 0x4) SDRAMC Refresh Timer Register -------- 
#define AT91C_SDRAMC_COUNT    ((unsigned int) 0xFFF <<  0) // (SDRAMC) Refresh Counter
// -------- SDRAMC_CR : (SDRAMC Offset: 0x8) SDRAM Configuration Register -------- 
#define AT91C_SDRAMC_NC       ((unsigned int) 0x3 <<  0) // (SDRAMC) Number of Column Bits
#define 	AT91C_SDRAMC_NC_8                    ((unsigned int) 0x0) // (SDRAMC) 8 Bits
#define 	AT91C_SDRAMC_NC_9                    ((unsigned int) 0x1) // (SDRAMC) 9 Bits
#define 	AT91C_SDRAMC_NC_10                   ((unsigned int) 0x2) // (SDRAMC) 10 Bits
#define 	AT91C_SDRAMC_NC_11                   ((unsigned int) 0x3) // (SDRAMC) 11 Bits
#define AT91C_SDRAMC_NR       ((unsigned int) 0x3 <<  2) // (SDRAMC) Number of Row Bits
#define 	AT91C_SDRAMC_NR_11                   ((unsigned int) 0x0 <<  2) // (SDRAMC) 11 Bits
#define 	AT91C_SDRAMC_NR_12                   ((unsigned int) 0x1 <<  2) // (SDRAMC) 12 Bits
#define 	AT91C_SDRAMC_NR_13                   ((unsigned int) 0x2 <<  2) // (SDRAMC) 13 Bits
#define AT91C_SDRAMC_NB       ((unsigned int) 0x1 <<  4) // (SDRAMC) Number of Banks
#define 	AT91C_SDRAMC_NB_2_BANKS              ((unsigned int) 0x0 <<  4) // (SDRAMC) 2 banks
#define 	AT91C_SDRAMC_NB_4_BANKS              ((unsigned int) 0x1 <<  4) // (SDRAMC) 4 banks
#define AT91C_SDRAMC_CAS      ((unsigned int) 0x3 <<  5) // (SDRAMC) CAS Latency
#define 	AT91C_SDRAMC_CAS_2                    ((unsigned int) 0x2 <<  5) // (SDRAMC) 2 cycles
#define 	AT91C_SDRAMC_CAS_3                    ((unsigned int) 0x3 <<  5) // (SDRAMC) 3 cycles
#define AT91C_SDRAMC_DBW      ((unsigned int) 0x1 <<  7) // (SDRAMC) Data Bus Width
#define 	AT91C_SDRAMC_DBW_32_BITS              ((unsigned int) 0x0 <<  7) // (SDRAMC) 32 Bits datas bus
#define 	AT91C_SDRAMC_DBW_16_BITS              ((unsigned int) 0x1 <<  7) // (SDRAMC) 16 Bits datas bus
#define AT91C_SDRAMC_TWR      ((unsigned int) 0xF <<  8) // (SDRAMC) Number of Write Recovery Time Cycles
#define 	AT91C_SDRAMC_TWR_0                    ((unsigned int) 0x0 <<  8) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TWR_1                    ((unsigned int) 0x1 <<  8) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TWR_2                    ((unsigned int) 0x2 <<  8) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TWR_3                    ((unsigned int) 0x3 <<  8) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TWR_4                    ((unsigned int) 0x4 <<  8) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TWR_5                    ((unsigned int) 0x5 <<  8) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TWR_6                    ((unsigned int) 0x6 <<  8) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TWR_7                    ((unsigned int) 0x7 <<  8) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TWR_8                    ((unsigned int) 0x8 <<  8) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TWR_9                    ((unsigned int) 0x9 <<  8) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TWR_10                   ((unsigned int) 0xA <<  8) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TWR_11                   ((unsigned int) 0xB <<  8) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TWR_12                   ((unsigned int) 0xC <<  8) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TWR_13                   ((unsigned int) 0xD <<  8) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TWR_14                   ((unsigned int) 0xE <<  8) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TWR_15                   ((unsigned int) 0xF <<  8) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRC      ((unsigned int) 0xF << 12) // (SDRAMC) Number of RAS Cycle Time Cycles
#define 	AT91C_SDRAMC_TRC_0                    ((unsigned int) 0x0 << 12) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRC_1                    ((unsigned int) 0x1 << 12) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRC_2                    ((unsigned int) 0x2 << 12) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRC_3                    ((unsigned int) 0x3 << 12) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRC_4                    ((unsigned int) 0x4 << 12) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRC_5                    ((unsigned int) 0x5 << 12) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRC_6                    ((unsigned int) 0x6 << 12) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRC_7                    ((unsigned int) 0x7 << 12) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRC_8                    ((unsigned int) 0x8 << 12) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRC_9                    ((unsigned int) 0x9 << 12) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRC_10                   ((unsigned int) 0xA << 12) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRC_11                   ((unsigned int) 0xB << 12) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRC_12                   ((unsigned int) 0xC << 12) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRC_13                   ((unsigned int) 0xD << 12) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRC_14                   ((unsigned int) 0xE << 12) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRC_15                   ((unsigned int) 0xF << 12) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRP      ((unsigned int) 0xF << 16) // (SDRAMC) Number of RAS Precharge Time Cycles
#define 	AT91C_SDRAMC_TRP_0                    ((unsigned int) 0x0 << 16) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRP_1                    ((unsigned int) 0x1 << 16) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRP_2                    ((unsigned int) 0x2 << 16) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRP_3                    ((unsigned int) 0x3 << 16) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRP_4                    ((unsigned int) 0x4 << 16) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRP_5                    ((unsigned int) 0x5 << 16) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRP_6                    ((unsigned int) 0x6 << 16) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRP_7                    ((unsigned int) 0x7 << 16) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRP_8                    ((unsigned int) 0x8 << 16) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRP_9                    ((unsigned int) 0x9 << 16) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRP_10                   ((unsigned int) 0xA << 16) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRP_11                   ((unsigned int) 0xB << 16) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRP_12                   ((unsigned int) 0xC << 16) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRP_13                   ((unsigned int) 0xD << 16) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRP_14                   ((unsigned int) 0xE << 16) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRP_15                   ((unsigned int) 0xF << 16) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRCD     ((unsigned int) 0xF << 20) // (SDRAMC) Number of RAS to CAS Delay Cycles
#define 	AT91C_SDRAMC_TRCD_0                    ((unsigned int) 0x0 << 20) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRCD_1                    ((unsigned int) 0x1 << 20) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRCD_2                    ((unsigned int) 0x2 << 20) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRCD_3                    ((unsigned int) 0x3 << 20) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRCD_4                    ((unsigned int) 0x4 << 20) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRCD_5                    ((unsigned int) 0x5 << 20) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRCD_6                    ((unsigned int) 0x6 << 20) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRCD_7                    ((unsigned int) 0x7 << 20) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRCD_8                    ((unsigned int) 0x8 << 20) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRCD_9                    ((unsigned int) 0x9 << 20) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRCD_10                   ((unsigned int) 0xA << 20) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRCD_11                   ((unsigned int) 0xB << 20) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRCD_12                   ((unsigned int) 0xC << 20) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRCD_13                   ((unsigned int) 0xD << 20) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRCD_14                   ((unsigned int) 0xE << 20) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRCD_15                   ((unsigned int) 0xF << 20) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRAS     ((unsigned int) 0xF << 24) // (SDRAMC) Number of RAS Active Time Cycles
#define 	AT91C_SDRAMC_TRAS_0                    ((unsigned int) 0x0 << 24) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRAS_1                    ((unsigned int) 0x1 << 24) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRAS_2                    ((unsigned int) 0x2 << 24) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRAS_3                    ((unsigned int) 0x3 << 24) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRAS_4                    ((unsigned int) 0x4 << 24) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRAS_5                    ((unsigned int) 0x5 << 24) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRAS_6                    ((unsigned int) 0x6 << 24) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRAS_7                    ((unsigned int) 0x7 << 24) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRAS_8                    ((unsigned int) 0x8 << 24) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRAS_9                    ((unsigned int) 0x9 << 24) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRAS_10                   ((unsigned int) 0xA << 24) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRAS_11                   ((unsigned int) 0xB << 24) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRAS_12                   ((unsigned int) 0xC << 24) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRAS_13                   ((unsigned int) 0xD << 24) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRAS_14                   ((unsigned int) 0xE << 24) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRAS_15                   ((unsigned int) 0xF << 24) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TXSR     ((unsigned int) 0xF << 28) // (SDRAMC) Number of Command Recovery Time Cycles
#define 	AT91C_SDRAMC_TXSR_0                    ((unsigned int) 0x0 << 28) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TXSR_1                    ((unsigned int) 0x1 << 28) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TXSR_2                    ((unsigned int) 0x2 << 28) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TXSR_3                    ((unsigned int) 0x3 << 28) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TXSR_4                    ((unsigned int) 0x4 << 28) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TXSR_5                    ((unsigned int) 0x5 << 28) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TXSR_6                    ((unsigned int) 0x6 << 28) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TXSR_7                    ((unsigned int) 0x7 << 28) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TXSR_8                    ((unsigned int) 0x8 << 28) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TXSR_9                    ((unsigned int) 0x9 << 28) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TXSR_10                   ((unsigned int) 0xA << 28) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TXSR_11                   ((unsigned int) 0xB << 28) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TXSR_12                   ((unsigned int) 0xC << 28) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TXSR_13                   ((unsigned int) 0xD << 28) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TXSR_14                   ((unsigned int) 0xE << 28) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TXSR_15                   ((unsigned int) 0xF << 28) // (SDRAMC) Value : 15
// -------- SDRAMC_HSR : (SDRAMC Offset: 0xc) SDRAM Controller High Speed Register -------- 
#define AT91C_SDRAMC_DA       ((unsigned int) 0x1 <<  0) // (SDRAMC) Decode Cycle Enable Bit
#define 	AT91C_SDRAMC_DA_DISABLE              ((unsigned int) 0x0) // (SDRAMC) Disable Decode Cycle
#define 	AT91C_SDRAMC_DA_ENABLE               ((unsigned int) 0x1) // (SDRAMC) Enable Decode Cycle
// -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) SDRAM Controller Low-power Register -------- 
#define AT91C_SDRAMC_LPCB     ((unsigned int) 0x3 <<  0) // (SDRAMC) Low-power Configurations
#define 	AT91C_SDRAMC_LPCB_DISABLE              ((unsigned int) 0x0) // (SDRAMC) Disable Low Power Features
#define 	AT91C_SDRAMC_LPCB_SELF_REFRESH         ((unsigned int) 0x1) // (SDRAMC) Enable SELF_REFRESH
#define 	AT91C_SDRAMC_LPCB_POWER_DOWN           ((unsigned int) 0x2) // (SDRAMC) Enable POWER_DOWN
#define 	AT91C_SDRAMC_LPCB_DEEP_POWER_DOWN      ((unsigned int) 0x3) // (SDRAMC) Enable DEEP_POWER_DOWN
#define AT91C_SDRAMC_PASR     ((unsigned int) 0x7 <<  4) // (SDRAMC) Partial Array Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_TCSR     ((unsigned int) 0x3 <<  8) // (SDRAMC) Temperature Compensated Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_DS       ((unsigned int) 0x3 << 10) // (SDRAMC) Drive Strenght (only for Low Power SDRAM)
#define AT91C_SDRAMC_TIMEOUT  ((unsigned int) 0x3 << 12) // (SDRAMC) Time to define when Low Power Mode is enabled
#define 	AT91C_SDRAMC_TIMEOUT_0_CLK_CYCLES         ((unsigned int) 0x0 << 12) // (SDRAMC) Activate SDRAM Low Power Mode Immediately
#define 	AT91C_SDRAMC_TIMEOUT_64_CLK_CYCLES        ((unsigned int) 0x1 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
#define 	AT91C_SDRAMC_TIMEOUT_128_CLK_CYCLES       ((unsigned int) 0x2 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
// -------- SDRAMC_IER : (SDRAMC Offset: 0x14) SDRAM Controller Interrupt Enable Register -------- 
#define AT91C_SDRAMC_RES      ((unsigned int) 0x1 <<  0) // (SDRAMC) Refresh Error Status
// -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) SDRAM Controller Interrupt Disable Register -------- 
// -------- SDRAMC_IMR : (SDRAMC Offset: 0x1c) SDRAM Controller Interrupt Mask Register -------- 
// -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) SDRAM Controller Interrupt Status Register -------- 
// -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) SDRAM Controller Memory Device Register -------- 
#define AT91C_SDRAMC_MD       ((unsigned int) 0x3 <<  0) // (SDRAMC) Memory Device Type
#define 	AT91C_SDRAMC_MD_SDRAM                ((unsigned int) 0x0) // (SDRAMC) SDRAM Mode
#define 	AT91C_SDRAMC_MD_LOW_POWER_SDRAM      ((unsigned int) 0x1) // (SDRAMC) SDRAM Low Power Mode

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
// *****************************************************************************
typedef struct _AT91S_SMC {
	AT91_REG	 SMC_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SMC_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SMC_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SMC_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SMC_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SMC_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SMC_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SMC_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SMC_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SMC_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SMC_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SMC_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SMC_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SMC_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SMC_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SMC_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SMC_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SMC_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SMC_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SMC_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SMC_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SMC_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SMC_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SMC_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SMC_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SMC_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SMC_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SMC_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SMC_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SMC_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SMC_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SMC_CTRL7; 	//  Control Register for CS 7
} AT91S_SMC, *AT91PS_SMC;

// -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
#define AT91C_SMC_NWESETUP    ((unsigned int) 0x3F <<  0) // (SMC) NWE Setup Length
#define AT91C_SMC_NCSSETUPWR  ((unsigned int) 0x3F <<  8) // (SMC) NCS Setup Length in WRite Access
#define AT91C_SMC_NRDSETUP    ((unsigned int) 0x3F << 16) // (SMC) NRD Setup Length
#define AT91C_SMC_NCSSETUPRD  ((unsigned int) 0x3F << 24) // (SMC) NCS Setup Length in ReaD Access
// -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
#define AT91C_SMC_NWEPULSE    ((unsigned int) 0x7F <<  0) // (SMC) NWE Pulse Length
#define AT91C_SMC_NCSPULSEWR  ((unsigned int) 0x7F <<  8) // (SMC) NCS Pulse Length in WRite Access
#define AT91C_SMC_NRDPULSE    ((unsigned int) 0x7F << 16) // (SMC) NRD Pulse Length
#define AT91C_SMC_NCSPULSERD  ((unsigned int) 0x7F << 24) // (SMC) NCS Pulse Length in ReaD Access
// -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
#define AT91C_SMC_NWECYCLE    ((unsigned int) 0x1FF <<  0) // (SMC) Total Write Cycle Length
#define AT91C_SMC_NRDCYCLE    ((unsigned int) 0x1FF << 16) // (SMC) Total Read Cycle Length
// -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
#define AT91C_SMC_READMODE    ((unsigned int) 0x1 <<  0) // (SMC) Read Mode
#define AT91C_SMC_WRITEMODE   ((unsigned int) 0x1 <<  1) // (SMC) Write Mode
#define AT91C_SMC_NWAITM      ((unsigned int) 0x3 <<  5) // (SMC) NWAIT Mode
#define 	AT91C_SMC_NWAITM_NWAIT_DISABLE        ((unsigned int) 0x0 <<  5) // (SMC) External NWAIT disabled.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  ((unsigned int) 0x2 <<  5) // (SMC) External NWAIT enabled in frozen mode.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   ((unsigned int) 0x3 <<  5) // (SMC) External NWAIT enabled in ready mode.
#define AT91C_SMC_BAT         ((unsigned int) 0x1 <<  8) // (SMC) Byte Access Type
#define 	AT91C_SMC_BAT_BYTE_SELECT          ((unsigned int) 0x0 <<  8) // (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3.
#define 	AT91C_SMC_BAT_BYTE_WRITE           ((unsigned int) 0x1 <<  8) // (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd.
#define AT91C_SMC_DBW         ((unsigned int) 0x3 << 12) // (SMC) Data Bus Width
#define 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     ((unsigned int) 0x0 << 12) // (SMC) 8 bits.
#define 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   ((unsigned int) 0x1 << 12) // (SMC) 16 bits.
#define 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS ((unsigned int) 0x2 << 12) // (SMC) 32 bits.
#define AT91C_SMC_TDF         ((unsigned int) 0xF << 16) // (SMC) Data Float Time.
#define AT91C_SMC_TDFEN       ((unsigned int) 0x1 << 20) // (SMC) TDF Enabled.
#define AT91C_SMC_PMEN        ((unsigned int) 0x1 << 24) // (SMC) Page Mode Enabled.
#define AT91C_SMC_PS          ((unsigned int) 0x3 << 28) // (SMC) Page Size
#define 	AT91C_SMC_PS_SIZE_FOUR_BYTES      ((unsigned int) 0x0 << 28) // (SMC) 4 bytes.
#define 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     ((unsigned int) 0x1 << 28) // (SMC) 8 bytes.
#define 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   ((unsigned int) 0x2 << 28) // (SMC) 16 bytes.
#define 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES ((unsigned int) 0x3 << 28) // (SMC) 32 bytes.
// -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
// *****************************************************************************
typedef struct _AT91S_MATRIX {
	AT91_REG	 MATRIX_MCFG; 	//  Master Configuration Register
	AT91_REG	 MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 Reserved0[3]; 	// 
	AT91_REG	 MATRIX_TCMR; 	//  Slave 0 Special Function Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 MATRIX_EBICSA; 	//  Slave 3 Special Function Register
	AT91_REG	 MATRIX_USBPCR; 	//  Slave 4 Special Function Register
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 MATRIX_VERSION; 	//  Version Register
} AT91S_MATRIX, *AT91PS_MATRIX;

// -------- MATRIX_MCFG : (MATRIX Offset: 0x0) Master Configuration Register -------- 
#define AT91C_MATRIX_RCA926I  ((unsigned int) 0x1 <<  0) // (MATRIX) Remap Command for ARM926EJ-S Instruction Master
#define AT91C_MATRIX_RCA926D  ((unsigned int) 0x1 <<  1) // (MATRIX) Remap Command for ARM926EJ-S Data Master
// -------- MATRIX_SCFG0 : (MATRIX Offset: 0x4) Slave Configuration Register 0 -------- 
#define AT91C_MATRIX_SLOT_CYCLE ((unsigned int) 0xFF <<  0) // (MATRIX) Maximum Number of Allowed Cycles for a Burst
#define AT91C_MATRIX_DEFMSTR_TYPE ((unsigned int) 0x3 << 16) // (MATRIX) Default Master Type
#define 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           ((unsigned int) 0x0 << 16) // (MATRIX) No Default Master. At the end of current slave access, if no other master request is pending, the slave is deconnected from all masters. This results in having a one cycle latency for the first transfer of a burst.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         ((unsigned int) 0x1 << 16) // (MATRIX) Last Default Master. At the end of current slave access, if no other master request is pending, the slave stay connected with the last master having accessed it. This results in not having the one cycle latency when the last master re-trying access on the slave.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        ((unsigned int) 0x2 << 16) // (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
#define AT91C_MATRIX_FIXED_DEFMSTR0 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_HPDC3                ((unsigned int) 0x2 << 18) // (MATRIX) HPDC3 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_UHP                  ((unsigned int) 0x4 << 18) // (MATRIX) UHP Master is Default Master
// -------- MATRIX_SCFG1 : (MATRIX Offset: 0x8) Slave Configuration Register 1 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR1 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_HPDC3                ((unsigned int) 0x2 << 18) // (MATRIX) HPDC3 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_UHP                  ((unsigned int) 0x4 << 18) // (MATRIX) UHP Master is Default Master
// -------- MATRIX_SCFG2 : (MATRIX Offset: 0xc) Slave Configuration Register 2 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR2 ((unsigned int) 0x1 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
// -------- MATRIX_SCFG3 : (MATRIX Offset: 0x10) Slave Configuration Register 3 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR3 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_HPDC3                ((unsigned int) 0x2 << 18) // (MATRIX) HPDC3 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_UHP                  ((unsigned int) 0x4 << 18) // (MATRIX) UHP Master is Default Master
// -------- MATRIX_SCFG4 : (MATRIX Offset: 0x14) Slave Configuration Register 4 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR4 ((unsigned int) 0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_HPDC3                ((unsigned int) 0x2 << 18) // (MATRIX) HPDC3 Master is Default Master
// -------- MATRIX_TCMR : (MATRIX Offset: 0x24) TCM (Slave 0) Special Function Register -------- 
#define AT91C_MATRIX_ITCM_SIZE ((unsigned int) 0xF <<  0) // (MATRIX) Size of ITCM enabled memory block
#define 	AT91C_MATRIX_ITCM_SIZE_0KB                  ((unsigned int) 0x0) // (MATRIX) 0 KB (No ITCM Memory)
#define 	AT91C_MATRIX_ITCM_SIZE_16KB                 ((unsigned int) 0x5) // (MATRIX) 16 KB
#define 	AT91C_MATRIX_ITCM_SIZE_32KB                 ((unsigned int) 0x6) // (MATRIX) 32 KB
#define 	AT91C_MATRIX_ITCM_SIZE_64KB                 ((unsigned int) 0x7) // (MATRIX) 64 KB
#define AT91C_MATRIX_DTCM_SIZE ((unsigned int) 0xF <<  4) // (MATRIX) Size of DTCM enabled memory block
#define 	AT91C_MATRIX_DTCM_SIZE_0KB                  ((unsigned int) 0x0 <<  4) // (MATRIX) 0 KB (No DTCM Memory)
#define 	AT91C_MATRIX_DTCM_SIZE_16KB                 ((unsigned int) 0x5 <<  4) // (MATRIX) 16 KB
#define 	AT91C_MATRIX_DTCM_SIZE_32KB                 ((unsigned int) 0x6 <<  4) // (MATRIX) 32 KB
#define 	AT91C_MATRIX_DTCM_SIZE_64KB                 ((unsigned int) 0x7 <<  4) // (MATRIX) 64 KB
// -------- MATRIX_EBICSA : (MATRIX Offset: 0x30) EBI (Slave 3) Special Function Register -------- 
#define AT91C_MATRIX_CS1A     ((unsigned int) 0x1 <<  1) // (MATRIX) Chip Select 1 Assignment
#define 	AT91C_MATRIX_CS1A_SMC                  ((unsigned int) 0x0 <<  1) // (MATRIX) Chip Select 1 is assigned to the Static Memory Controller.
#define 	AT91C_MATRIX_CS1A_SDRAMC               ((unsigned int) 0x1 <<  1) // (MATRIX) Chip Select 1 is assigned to the SDRAM Controller.
#define AT91C_MATRIX_CS3A     ((unsigned int) 0x1 <<  3) // (MATRIX) Chip Select 3 Assignment
#define 	AT91C_MATRIX_CS3A_SMC                  ((unsigned int) 0x0 <<  3) // (MATRIX) Chip Select 3 is only assigned to the Static Memory Controller and NCS3 behaves as defined by the SMC.
#define 	AT91C_MATRIX_CS3A_SM                   ((unsigned int) 0x1 <<  3) // (MATRIX) Chip Select 3 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.
#define AT91C_MATRIX_CS4A     ((unsigned int) 0x1 <<  4) // (MATRIX) Chip Select 4 Assignment
#define 	AT91C_MATRIX_CS4A_SMC                  ((unsigned int) 0x0 <<  4) // (MATRIX) Chip Select 4 is only assigned to the Static Memory Controller and NCS4 behaves as defined by the SMC.
#define 	AT91C_MATRIX_CS4A_CF                   ((unsigned int) 0x1 <<  4) // (MATRIX) Chip Select 4 is assigned to the Static Memory Controller and the CompactFlash Logic (first slot) is activated.
#define AT91C_MATRIX_CS5A     ((unsigned int) 0x1 <<  5) // (MATRIX) Chip Select 5 Assignment
#define 	AT91C_MATRIX_CS5A_SMC                  ((unsigned int) 0x0 <<  5) // (MATRIX) Chip Select 5 is only assigned to the Static Memory Controller and NCS5 behaves as defined by the SMC
#define 	AT91C_MATRIX_CS5A_CF                   ((unsigned int) 0x1 <<  5) // (MATRIX) Chip Select 5 is assigned to the Static Memory Controller and the CompactFlash Logic (second slot) is activated.
#define AT91C_MATRIX_DBPUC    ((unsigned int) 0x1 <<  8) // (MATRIX) Data Bus Pull-up Configuration
// -------- MATRIX_USBPCR : (MATRIX Offset: 0x34) USB Pad Control Register -------- 
#define AT91C_MATRIX_USBPCR_PUON ((unsigned int) 0x1 << 30) // (MATRIX) PullUp On
#define AT91C_MATRIX_USBPCR_PUIDLE ((unsigned int) 0x1 << 31) // (MATRIX) PullUp Idle

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
// *****************************************************************************
typedef struct _AT91S_AIC {
	AT91_REG	 AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 AIC_FFSR; 	// Fast Forcing Status Register
} AT91S_AIC, *AT91PS_AIC;

// -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
#define AT91C_AIC_PRIOR       ((unsigned int) 0x7 <<  0) // (AIC) Priority Level
#define 	AT91C_AIC_PRIOR_LOWEST               ((unsigned int) 0x0) // (AIC) Lowest priority level
#define 	AT91C_AIC_PRIOR_HIGHEST              ((unsigned int) 0x7) // (AIC) Highest priority level
#define AT91C_AIC_SRCTYPE     ((unsigned int) 0x3 <<  5) // (AIC) Interrupt Source Type
#define 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       ((unsigned int) 0x0 <<  5) // (AIC) Internal Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        ((unsigned int) 0x0 <<  5) // (AIC) External Sources Code Label Low-level Sensitive
#define 	AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE    ((unsigned int) 0x1 <<  5) // (AIC) Internal Sources Code Label Positive Edge triggered
#define 	AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    ((unsigned int) 0x1 <<  5) // (AIC) External Sources Code Label Negative Edge triggered
#define 	AT91C_AIC_SRCTYPE_HIGH_LEVEL           ((unsigned int) 0x2 <<  5) // (AIC) Internal Or External Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_POSITIVE_EDGE        ((unsigned int) 0x3 <<  5) // (AIC) Internal Or External Sources Code Label Positive Edge triggered
// -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
#define AT91C_AIC_NFIQ        ((unsigned int) 0x1 <<  0) // (AIC) NFIQ Status
#define AT91C_AIC_NIRQ        ((unsigned int) 0x1 <<  1) // (AIC) NIRQ Status
// -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
#define AT91C_AIC_DCR_PROT    ((unsigned int) 0x1 <<  0) // (AIC) Protection Mode
#define AT91C_AIC_DCR_GMSK    ((unsigned int) 0x1 <<  1) // (AIC) General Mask

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
// *****************************************************************************
typedef struct _AT91S_PDC {
	AT91_REG	 PDC_RPR; 	// Receive Pointer Register
	AT91_REG	 PDC_RCR; 	// Receive Counter Register
	AT91_REG	 PDC_TPR; 	// Transmit Pointer Register
	AT91_REG	 PDC_TCR; 	// Transmit Counter Register
	AT91_REG	 PDC_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 PDC_RNCR; 	// Receive Next Counter Register
	AT91_REG	 PDC_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 PDC_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 PDC_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 PDC_PTSR; 	// PDC Transfer Status Register
} AT91S_PDC, *AT91PS_PDC;

// -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
#define AT91C_PDC_RXTEN       ((unsigned int) 0x1 <<  0) // (PDC) Receiver Transfer Enable
#define AT91C_PDC_RXTDIS      ((unsigned int) 0x1 <<  1) // (PDC) Receiver Transfer Disable
#define AT91C_PDC_TXTEN       ((unsigned int) 0x1 <<  8) // (PDC) Transmitter Transfer Enable
#define AT91C_PDC_TXTDIS      ((unsigned int) 0x1 <<  9) // (PDC) Transmitter Transfer Disable
// -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Debug Unit
// *****************************************************************************
typedef struct _AT91S_DBGU {
	AT91_REG	 DBGU_CR; 	// Control Register
	AT91_REG	 DBGU_MR; 	// Mode Register
	AT91_REG	 DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 DBGU_CSR; 	// Channel Status Register
	AT91_REG	 DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved1[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 DBGU_PTSR; 	// PDC Transfer Status Register
} AT91S_DBGU, *AT91PS_DBGU;

// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_RSTRX        ((unsigned int) 0x1 <<  2) // (DBGU) Reset Receiver
#define AT91C_US_RSTTX        ((unsigned int) 0x1 <<  3) // (DBGU) Reset Transmitter
#define AT91C_US_RXEN         ((unsigned int) 0x1 <<  4) // (DBGU) Receiver Enable
#define AT91C_US_RXDIS        ((unsigned int) 0x1 <<  5) // (DBGU) Receiver Disable
#define AT91C_US_TXEN         ((unsigned int) 0x1 <<  6) // (DBGU) Transmitter Enable
#define AT91C_US_TXDIS        ((unsigned int) 0x1 <<  7) // (DBGU) Transmitter Disable
#define AT91C_US_RSTSTA       ((unsigned int) 0x1 <<  8) // (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_PAR          ((unsigned int) 0x7 <<  9) // (DBGU) Parity type
#define 	AT91C_US_PAR_EVEN                 ((unsigned int) 0x0 <<  9) // (DBGU) Even Parity
#define 	AT91C_US_PAR_ODD                  ((unsigned int) 0x1 <<  9) // (DBGU) Odd Parity
#define 	AT91C_US_PAR_SPACE                ((unsigned int) 0x2 <<  9) // (DBGU) Parity forced to 0 (Space)
#define 	AT91C_US_PAR_MARK                 ((unsigned int) 0x3 <<  9) // (DBGU) Parity forced to 1 (Mark)
#define 	AT91C_US_PAR_NONE                 ((unsigned int) 0x4 <<  9) // (DBGU) No Parity
#define 	AT91C_US_PAR_MULTI_DROP           ((unsigned int) 0x6 <<  9) // (DBGU) Multi-drop mode
#define AT91C_US_CHMODE       ((unsigned int) 0x3 << 14) // (DBGU) Channel Mode
#define 	AT91C_US_CHMODE_NORMAL               ((unsigned int) 0x0 << 14) // (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
#define 	AT91C_US_CHMODE_AUTO                 ((unsigned int) 0x1 << 14) // (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define 	AT91C_US_CHMODE_LOCAL                ((unsigned int) 0x2 << 14) // (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define 	AT91C_US_CHMODE_REMOTE               ((unsigned int) 0x3 << 14) // (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXRDY        ((unsigned int) 0x1 <<  0) // (DBGU) RXRDY Interrupt
#define AT91C_US_TXRDY        ((unsigned int) 0x1 <<  1) // (DBGU) TXRDY Interrupt
#define AT91C_US_ENDRX        ((unsigned int) 0x1 <<  3) // (DBGU) End of Receive Transfer Interrupt
#define AT91C_US_ENDTX        ((unsigned int) 0x1 <<  4) // (DBGU) End of Transmit Interrupt
#define AT91C_US_OVRE         ((unsigned int) 0x1 <<  5) // (DBGU) Overrun Interrupt
#define AT91C_US_FRAME        ((unsigned int) 0x1 <<  6) // (DBGU) Framing Error Interrupt
#define AT91C_US_PARE         ((unsigned int) 0x1 <<  7) // (DBGU) Parity Error Interrupt
#define AT91C_US_TXEMPTY      ((unsigned int) 0x1 <<  9) // (DBGU) TXEMPTY Interrupt
#define AT91C_US_TXBUFE       ((unsigned int) 0x1 << 11) // (DBGU) TXBUFE Interrupt
#define AT91C_US_RXBUFF       ((unsigned int) 0x1 << 12) // (DBGU) RXBUFF Interrupt
#define AT91C_US_COMM_TX      ((unsigned int) 0x1 << 30) // (DBGU) COMM_TX Interrupt
#define AT91C_US_COMM_RX      ((unsigned int) 0x1 << 31) // (DBGU) COMM_RX Interrupt
// -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
#define AT91C_US_FORCE_NTRST  ((unsigned int) 0x1 <<  0) // (DBGU) Force NTRST in JTAG

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
// *****************************************************************************
typedef struct _AT91S_PIO {
	AT91_REG	 PIO_PER; 	// PIO Enable Register
	AT91_REG	 PIO_PDR; 	// PIO Disable Register
	AT91_REG	 PIO_PSR; 	// PIO Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PIO_OER; 	// Output Enable Register
	AT91_REG	 PIO_ODR; 	// Output Disable Registerr
	AT91_REG	 PIO_OSR; 	// Output Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PIO_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIO_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIO_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 PIO_SODR; 	// Set Output Data Register
	AT91_REG	 PIO_CODR; 	// Clear Output Data Register
	AT91_REG	 PIO_ODSR; 	// Output Data Status Register
	AT91_REG	 PIO_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIO_IER; 	// Interrupt Enable Register
	AT91_REG	 PIO_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIO_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIO_ISR; 	// Interrupt Status Register
	AT91_REG	 PIO_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIO_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIO_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 PIO_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIO_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIO_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 PIO_ASR; 	// Select A Register
	AT91_REG	 PIO_BSR; 	// Select B Register
	AT91_REG	 PIO_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved5[9]; 	// 
	AT91_REG	 PIO_OWER; 	// Output Write Enable Register
	AT91_REG	 PIO_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIO_OWSR; 	// Output Write Status Register
} AT91S_PIO, *AT91PS_PIO;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Clock Generator Controler
// *****************************************************************************
typedef struct _AT91S_CKGR {
	AT91_REG	 CKGR_MOR; 	// Main Oscillator Register
	AT91_REG	 CKGR_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 CKGR_PLLAR; 	// PLL A Register
	AT91_REG	 CKGR_PLLBR; 	// PLL B Register
} AT91S_CKGR, *AT91PS_CKGR;

// -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
#define AT91C_CKGR_MOSCEN     ((unsigned int) 0x1 <<  0) // (CKGR) Main Oscillator Enable
#define AT91C_CKGR_OSCBYPASS  ((unsigned int) 0x1 <<  1) // (CKGR) Main Oscillator Bypass
#define AT91C_CKGR_OSCOUNT    ((unsigned int) 0xFF <<  8) // (CKGR) Main Oscillator Start-up Time
// -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
#define AT91C_CKGR_MAINF      ((unsigned int) 0xFFFF <<  0) // (CKGR) Main Clock Frequency
#define AT91C_CKGR_MAINRDY    ((unsigned int) 0x1 << 16) // (CKGR) Main Clock Ready
// -------- CKGR_PLLAR : (CKGR Offset: 0x8) PLL A Register -------- 
#define AT91C_CKGR_DIVA       ((unsigned int) 0xFF <<  0) // (CKGR) Divider A Selected
#define 	AT91C_CKGR_DIVA_0                    ((unsigned int) 0x0) // (CKGR) Divider A output is 0
#define 	AT91C_CKGR_DIVA_BYPASS               ((unsigned int) 0x1) // (CKGR) Divider A is bypassed
#define AT91C_CKGR_PLLACOUNT  ((unsigned int) 0x3F <<  8) // (CKGR) PLL A Counter
#define AT91C_CKGR_OUTA       ((unsigned int) 0x3 << 14) // (CKGR) PLL A Output Frequency Range
#define 	AT91C_CKGR_OUTA_0                    ((unsigned int) 0x0 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_1                    ((unsigned int) 0x1 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_2                    ((unsigned int) 0x2 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_3                    ((unsigned int) 0x3 << 14) // (CKGR) Please refer to the PLLA datasheet
#define AT91C_CKGR_MULA       ((unsigned int) 0x7FF << 16) // (CKGR) PLL A Multiplier
#define AT91C_CKGR_SRCA       ((unsigned int) 0x1 << 29) // (CKGR) 
// -------- CKGR_PLLBR : (CKGR Offset: 0xc) PLL B Register -------- 
#define AT91C_CKGR_DIVB       ((unsigned int) 0xFF <<  0) // (CKGR) Divider B Selected
#define 	AT91C_CKGR_DIVB_0                    ((unsigned int) 0x0) // (CKGR) Divider B output is 0
#define 	AT91C_CKGR_DIVB_BYPASS               ((unsigned int) 0x1) // (CKGR) Divider B is bypassed
#define AT91C_CKGR_PLLBCOUNT  ((unsigned int) 0x3F <<  8) // (CKGR) PLL B Counter
#define AT91C_CKGR_OUTB       ((unsigned int) 0x3 << 14) // (CKGR) PLL B Output Frequency Range
#define 	AT91C_CKGR_OUTB_0                    ((unsigned int) 0x0 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_1                    ((unsigned int) 0x1 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_2                    ((unsigned int) 0x2 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_3                    ((unsigned int) 0x3 << 14) // (CKGR) Please refer to the PLLB datasheet
#define AT91C_CKGR_MULB       ((unsigned int) 0x7FF << 16) // (CKGR) PLL B Multiplier
#define AT91C_CKGR_USBDIV     ((unsigned int) 0x3 << 28) // (CKGR) Divider for USB Clocks
#define 	AT91C_CKGR_USBDIV_0                    ((unsigned int) 0x0 << 28) // (CKGR) Divider output is PLL clock output
#define 	AT91C_CKGR_USBDIV_1                    ((unsigned int) 0x1 << 28) // (CKGR) Divider output is PLL clock output divided by 2
#define 	AT91C_CKGR_USBDIV_2                    ((unsigned int) 0x2 << 28) // (CKGR) Divider output is PLL clock output divided by 4

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Power Management Controler
// *****************************************************************************
typedef struct _AT91S_PMC {
	AT91_REG	 PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 PMC_PLLAR; 	// PLL A Register
	AT91_REG	 PMC_PLLBR; 	// PLL B Register
	AT91_REG	 PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
} AT91S_PMC, *AT91PS_PMC;

// -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
#define AT91C_PMC_PCK         ((unsigned int) 0x1 <<  0) // (PMC) Processor Clock
#define AT91C_PMC_UHP         ((unsigned int) 0x1 <<  6) // (PMC) USB Host Port Clock
#define AT91C_PMC_UDP         ((unsigned int) 0x1 <<  7) // (PMC) USB Device Port Clock
#define AT91C_PMC_PCK0        ((unsigned int) 0x1 <<  8) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK1        ((unsigned int) 0x1 <<  9) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK2        ((unsigned int) 0x1 << 10) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK3        ((unsigned int) 0x1 << 11) // (PMC) Programmable Clock Output
#define AT91C_PMC_HCK0        ((unsigned int) 0x1 << 16) // (PMC) AHB UHP Clock Output
#define AT91C_PMC_HCK1        ((unsigned int) 0x1 << 17) // (PMC) AHB LCDC Clock Output
// -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
// -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
// -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
// -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
// -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
// -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
#define AT91C_PMC_CSS         ((unsigned int) 0x3 <<  0) // (PMC) Programmable Clock Selection
#define 	AT91C_PMC_CSS_SLOW_CLK             ((unsigned int) 0x0) // (PMC) Slow Clock is selected
#define 	AT91C_PMC_CSS_MAIN_CLK             ((unsigned int) 0x1) // (PMC) Main Clock is selected
#define 	AT91C_PMC_CSS_PLLA_CLK             ((unsigned int) 0x2) // (PMC) Clock from PLL A is selected
#define 	AT91C_PMC_CSS_PLLB_CLK             ((unsigned int) 0x3) // (PMC) Clock from PLL B is selected
#define AT91C_PMC_PRES        ((unsigned int) 0x7 <<  2) // (PMC) Programmable Clock Prescaler
#define 	AT91C_PMC_PRES_CLK                  ((unsigned int) 0x0 <<  2) // (PMC) Selected clock
#define 	AT91C_PMC_PRES_CLK_2                ((unsigned int) 0x1 <<  2) // (PMC) Selected clock divided by 2
#define 	AT91C_PMC_PRES_CLK_4                ((unsigned int) 0x2 <<  2) // (PMC) Selected clock divided by 4
#define 	AT91C_PMC_PRES_CLK_8                ((unsigned int) 0x3 <<  2) // (PMC) Selected clock divided by 8
#define 	AT91C_PMC_PRES_CLK_16               ((unsigned int) 0x4 <<  2) // (PMC) Selected clock divided by 16
#define 	AT91C_PMC_PRES_CLK_32               ((unsigned int) 0x5 <<  2) // (PMC) Selected clock divided by 32
#define 	AT91C_PMC_PRES_CLK_64               ((unsigned int) 0x6 <<  2) // (PMC) Selected clock divided by 64
#define AT91C_PMC_MDIV        ((unsigned int) 0x3 <<  8) // (PMC) Master Clock Division
#define 	AT91C_PMC_MDIV_1                    ((unsigned int) 0x0 <<  8) // (PMC) The master clock and the processor clock are the same
#define 	AT91C_PMC_MDIV_2                    ((unsigned int) 0x1 <<  8) // (PMC) The processor clock is twice as fast as the master clock
#define 	AT91C_PMC_MDIV_3                    ((unsigned int) 0x2 <<  8) // (PMC) The processor clock is four times faster than the master clock
// -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
// -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
#define AT91C_PMC_MOSCS       ((unsigned int) 0x1 <<  0) // (PMC) MOSC Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKA       ((unsigned int) 0x1 <<  1) // (PMC) PLL A Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKB       ((unsigned int) 0x1 <<  2) // (PMC) PLL B Status/Enable/Disable/Mask
#define AT91C_PMC_MCKRDY      ((unsigned int) 0x1 <<  3) // (PMC) Master Clock Status/Enable/Disable/Mask
#define AT91C_PMC_PCK0RDY     ((unsigned int) 0x1 <<  8) // (PMC) PCK0_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK1RDY     ((unsigned int) 0x1 <<  9) // (PMC) PCK1_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK2RDY     ((unsigned int) 0x1 << 10) // (PMC) PCK2_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK3RDY     ((unsigned int) 0x1 << 11) // (PMC) PCK3_RDY Status/Enable/Disable/Mask
// -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
// -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Reset Controller Interface
// *****************************************************************************
typedef struct _AT91S_RSTC {
	AT91_REG	 RSTC_RCR; 	// Reset Control Register
	AT91_REG	 RSTC_RSR; 	// Reset Status Register
	AT91_REG	 RSTC_RMR; 	// Reset Mode Register
} AT91S_RSTC, *AT91PS_RSTC;

// -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
#define AT91C_RSTC_PROCRST    ((unsigned int) 0x1 <<  0) // (RSTC) Processor Reset
#define AT91C_RSTC_ICERST     ((unsigned int) 0x1 <<  1) // (RSTC) ICE Interface Reset
#define AT91C_RSTC_PERRST     ((unsigned int) 0x1 <<  2) // (RSTC) Peripheral Reset
#define AT91C_RSTC_EXTRST     ((unsigned int) 0x1 <<  3) // (RSTC) External Reset
#define AT91C_RSTC_KEY        ((unsigned int) 0xFF << 24) // (RSTC) Password
// -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
#define AT91C_RSTC_URSTS      ((unsigned int) 0x1 <<  0) // (RSTC) User Reset Status
#define AT91C_RSTC_RSTTYP     ((unsigned int) 0x7 <<  8) // (RSTC) Reset Type
#define 	AT91C_RSTC_RSTTYP_GENERAL              ((unsigned int) 0x0 <<  8) // (RSTC) General reset. Both VDDCORE and VDDBU rising.
#define 	AT91C_RSTC_RSTTYP_WAKEUP               ((unsigned int) 0x1 <<  8) // (RSTC) WakeUp Reset. VDDCORE rising.
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             ((unsigned int) 0x2 <<  8) // (RSTC) Watchdog Reset. Watchdog overflow occured.
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             ((unsigned int) 0x3 <<  8) // (RSTC) Software Reset. Processor reset required by the software.
#define 	AT91C_RSTC_RSTTYP_USER                 ((unsigned int) 0x4 <<  8) // (RSTC) User Reset. NRST pin detected low.
#define AT91C_RSTC_NRSTL      ((unsigned int) 0x1 << 16) // (RSTC) NRST pin level
#define AT91C_RSTC_SRCMP      ((unsigned int) 0x1 << 17) // (RSTC) Software Reset Command in Progress.
// -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
#define AT91C_RSTC_URSTEN     ((unsigned int) 0x1 <<  0) // (RSTC) User Reset Enable
#define AT91C_RSTC_URSTIEN    ((unsigned int) 0x1 <<  4) // (RSTC) User Reset Interrupt Enable
#define AT91C_RSTC_ERSTL      ((unsigned int) 0xF <<  8) // (RSTC) User Reset Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
// *****************************************************************************
typedef struct _AT91S_SHDWC {
	AT91_REG	 SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SHDWC_SHSR; 	// Shut Down Status Register
} AT91S_SHDWC, *AT91PS_SHDWC;

// -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
#define AT91C_SHDWC_SHDW      ((unsigned int) 0x1 <<  0) // (SHDWC) Processor Reset
#define AT91C_SHDWC_KEY       ((unsigned int) 0xFF << 24) // (SHDWC) Shut down KEY Password
// -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
#define AT91C_SHDWC_WKMODE0   ((unsigned int) 0x3 <<  0) // (SHDWC) Wake Up 0 Mode Selection
#define 	AT91C_SHDWC_WKMODE0_NONE                 ((unsigned int) 0x0) // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE0_HIGH                 ((unsigned int) 0x1) // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE0_LOW                  ((unsigned int) 0x2) // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE0_ANYLEVEL             ((unsigned int) 0x3) // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK0    ((unsigned int) 0xF <<  4) // (SHDWC) Counter On Wake Up 0
#define AT91C_SHDWC_RTTWKEN   ((unsigned int) 0x1 << 16) // (SHDWC) Real Time Timer Wake Up Enable
// -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
#define AT91C_SHDWC_WAKEUP0   ((unsigned int) 0x1 <<  0) // (SHDWC) Wake Up 0 Status
#define AT91C_SHDWC_RTTWK     ((unsigned int) 0x1 << 16) // (SHDWC) Real Time Timer wake Up

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_RTTC {
	AT91_REG	 RTTC_RTMR; 	// Real-time Mode Register
	AT91_REG	 RTTC_RTAR; 	// Real-time Alarm Register
	AT91_REG	 RTTC_RTVR; 	// Real-time Value Register
	AT91_REG	 RTTC_RTSR; 	// Real-time Status Register
} AT91S_RTTC, *AT91PS_RTTC;

// -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
#define AT91C_RTTC_RTPRES     ((unsigned int) 0xFFFF <<  0) // (RTTC) Real-time Timer Prescaler Value
#define AT91C_RTTC_ALMIEN     ((unsigned int) 0x1 << 16) // (RTTC) Alarm Interrupt Enable
#define AT91C_RTTC_RTTINCIEN  ((unsigned int) 0x1 << 17) // (RTTC) Real Time Timer Increment Interrupt Enable
#define AT91C_RTTC_RTTRST     ((unsigned int) 0x1 << 18) // (RTTC) Real Time Timer Restart
// -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
#define AT91C_RTTC_ALMV       ((unsigned int) 0x0 <<  0) // (RTTC) Alarm Value
// -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
#define AT91C_RTTC_CRTV       ((unsigned int) 0x0 <<  0) // (RTTC) Current Real-time Value
// -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
#define AT91C_RTTC_ALMS       ((unsigned int) 0x1 <<  0) // (RTTC) Real-time Alarm Status
#define AT91C_RTTC_RTTINC     ((unsigned int) 0x1 <<  1) // (RTTC) Real-time Timer Increment

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_PITC {
	AT91_REG	 PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 PITC_PIIR; 	// Period Interval Image Register
} AT91S_PITC, *AT91PS_PITC;

// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
#define AT91C_PITC_PIV        ((unsigned int) 0xFFFFF <<  0) // (PITC) Periodic Interval Value
#define AT91C_PITC_PITEN      ((unsigned int) 0x1 << 24) // (PITC) Periodic Interval Timer Enabled
#define AT91C_PITC_PITIEN     ((unsigned int) 0x1 << 25) // (PITC) Periodic Interval Timer Interrupt Enable
// -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
#define AT91C_PITC_PITS       ((unsigned int) 0x1 <<  0) // (PITC) Periodic Interval Timer Status
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
#define AT91C_PITC_CPIV       ((unsigned int) 0xFFFFF <<  0) // (PITC) Current Periodic Interval Value
#define AT91C_PITC_PICNT      ((unsigned int) 0xFFF << 20) // (PITC) Periodic Interval Counter
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_WDTC {
	AT91_REG	 WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 WDTC_WDSR; 	// Watchdog Status Register
} AT91S_WDTC, *AT91PS_WDTC;

// -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
#define AT91C_WDTC_WDRSTT     ((unsigned int) 0x1 <<  0) // (WDTC) Watchdog Restart
#define AT91C_WDTC_KEY        ((unsigned int) 0xFF << 24) // (WDTC) Watchdog KEY Password
// -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
#define AT91C_WDTC_WDV        ((unsigned int) 0xFFF <<  0) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDFIEN     ((unsigned int) 0x1 << 12) // (WDTC) Watchdog Fault Interrupt Enable
#define AT91C_WDTC_WDRSTEN    ((unsigned int) 0x1 << 13) // (WDTC) Watchdog Reset Enable
#define AT91C_WDTC_WDRPROC    ((unsigned int) 0x1 << 14) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDDIS      ((unsigned int) 0x1 << 15) // (WDTC) Watchdog Disable
#define AT91C_WDTC_WDD        ((unsigned int) 0xFFF << 16) // (WDTC) Watchdog Delta Value
#define AT91C_WDTC_WDDBGHLT   ((unsigned int) 0x1 << 28) // (WDTC) Watchdog Debug Halt
#define AT91C_WDTC_WDIDLEHLT  ((unsigned int) 0x1 << 29) // (WDTC) Watchdog Idle Halt
// -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
#define AT91C_WDTC_WDUNF      ((unsigned int) 0x1 <<  0) // (WDTC) Watchdog Underflow
#define AT91C_WDTC_WDERR      ((unsigned int) 0x1 <<  1) // (WDTC) Watchdog Error

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
// *****************************************************************************
typedef struct _AT91S_TC {
	AT91_REG	 TC_CCR; 	// Channel Control Register
	AT91_REG	 TC_CMR; 	// Channel Mode Register (Capture Mode / Waveform Mode)
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 TC_CV; 	// Counter Value
	AT91_REG	 TC_RA; 	// Register A
	AT91_REG	 TC_RB; 	// Register B
	AT91_REG	 TC_RC; 	// Register C
	AT91_REG	 TC_SR; 	// Status Register
	AT91_REG	 TC_IER; 	// Interrupt Enable Register
	AT91_REG	 TC_IDR; 	// Interrupt Disable Register
	AT91_REG	 TC_IMR; 	// Interrupt Mask Register
} AT91S_TC, *AT91PS_TC;

// -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
#define AT91C_TC_CLKEN        ((unsigned int) 0x1 <<  0) // (TC) Counter Clock Enable Command
#define AT91C_TC_CLKDIS       ((unsigned int) 0x1 <<  1) // (TC) Counter Clock Disable Command
#define AT91C_TC_SWTRG        ((unsigned int) 0x1 <<  2) // (TC) Software Trigger Command
// -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
#define AT91C_TC_CLKS         ((unsigned int) 0x7 <<  0) // (TC) Clock Selection
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     ((unsigned int) 0x0) // (TC) Clock selected: TIMER_DIV1_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     ((unsigned int) 0x1) // (TC) Clock selected: TIMER_DIV2_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     ((unsigned int) 0x2) // (TC) Clock selected: TIMER_DIV3_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     ((unsigned int) 0x3) // (TC) Clock selected: TIMER_DIV4_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     ((unsigned int) 0x4) // (TC) Clock selected: TIMER_DIV5_CLOCK
#define 	AT91C_TC_CLKS_XC0                  ((unsigned int) 0x5) // (TC) Clock selected: XC0
#define 	AT91C_TC_CLKS_XC1                  ((unsigned int) 0x6) // (TC) Clock selected: XC1
#define 	AT91C_TC_CLKS_XC2                  ((unsigned int) 0x7) // (TC) Clock selected: XC2
#define AT91C_TC_CLKI         ((unsigned int) 0x1 <<  3) // (TC) Clock Invert
#define AT91C_TC_BURST        ((unsigned int) 0x3 <<  4) // (TC) Burst Signal Selection
#define 	AT91C_TC_BURST_NONE                 ((unsigned int) 0x0 <<  4) // (TC) The clock is not gated by an external signal
#define 	AT91C_TC_BURST_XC0                  ((unsigned int) 0x1 <<  4) // (TC) XC0 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC1                  ((unsigned int) 0x2 <<  4) // (TC) XC1 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC2                  ((unsigned int) 0x3 <<  4) // (TC) XC2 is ANDed with the selected clock
#define AT91C_TC_CPCSTOP      ((unsigned int) 0x1 <<  6) // (TC) Counter Clock Stopped with RC Compare
#define AT91C_TC_LDBSTOP      ((unsigned int) 0x1 <<  6) // (TC) Counter Clock Stopped with RB Loading
#define AT91C_TC_CPCDIS       ((unsigned int) 0x1 <<  7) // (TC) Counter Clock Disable with RC Compare
#define AT91C_TC_LDBDIS       ((unsigned int) 0x1 <<  7) // (TC) Counter Clock Disabled with RB Loading
#define AT91C_TC_ETRGEDG      ((unsigned int) 0x3 <<  8) // (TC) External Trigger Edge Selection
#define 	AT91C_TC_ETRGEDG_NONE                 ((unsigned int) 0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_ETRGEDG_RISING               ((unsigned int) 0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_ETRGEDG_FALLING              ((unsigned int) 0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_ETRGEDG_BOTH                 ((unsigned int) 0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVTEDG      ((unsigned int) 0x3 <<  8) // (TC) External Event Edge Selection
#define 	AT91C_TC_EEVTEDG_NONE                 ((unsigned int) 0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_EEVTEDG_RISING               ((unsigned int) 0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_EEVTEDG_FALLING              ((unsigned int) 0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_EEVTEDG_BOTH                 ((unsigned int) 0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVT         ((unsigned int) 0x3 << 10) // (TC) External Event  Selection
#define 	AT91C_TC_EEVT_TIOB                 ((unsigned int) 0x0 << 10) // (TC) Signal selected as external event: TIOB TIOB direction: input
#define 	AT91C_TC_EEVT_XC0                  ((unsigned int) 0x1 << 10) // (TC) Signal selected as external event: XC0 TIOB direction: output
#define 	AT91C_TC_EEVT_XC1                  ((unsigned int) 0x2 << 10) // (TC) Signal selected as external event: XC1 TIOB direction: output
#define 	AT91C_TC_EEVT_XC2                  ((unsigned int) 0x3 << 10) // (TC) Signal selected as external event: XC2 TIOB direction: output
#define AT91C_TC_ABETRG       ((unsigned int) 0x1 << 10) // (TC) TIOA or TIOB External Trigger Selection
#define AT91C_TC_ENETRG       ((unsigned int) 0x1 << 12) // (TC) External Event Trigger enable
#define AT91C_TC_WAVESEL      ((unsigned int) 0x3 << 13) // (TC) Waveform  Selection
#define 	AT91C_TC_WAVESEL_UP                   ((unsigned int) 0x0 << 13) // (TC) UP mode without atomatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN               ((unsigned int) 0x1 << 13) // (TC) UPDOWN mode without automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UP_AUTO              ((unsigned int) 0x2 << 13) // (TC) UP mode with automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          ((unsigned int) 0x3 << 13) // (TC) UPDOWN mode with automatic trigger on RC Compare
#define AT91C_TC_CPCTRG       ((unsigned int) 0x1 << 14) // (TC) RC Compare Trigger Enable
#define AT91C_TC_WAVE         ((unsigned int) 0x1 << 15) // (TC) 
#define AT91C_TC_ACPA         ((unsigned int) 0x3 << 16) // (TC) RA Compare Effect on TIOA
#define 	AT91C_TC_ACPA_NONE                 ((unsigned int) 0x0 << 16) // (TC) Effect: none
#define 	AT91C_TC_ACPA_SET                  ((unsigned int) 0x1 << 16) // (TC) Effect: set
#define 	AT91C_TC_ACPA_CLEAR                ((unsigned int) 0x2 << 16) // (TC) Effect: clear
#define 	AT91C_TC_ACPA_TOGGLE               ((unsigned int) 0x3 << 16) // (TC) Effect: toggle
#define AT91C_TC_LDRA         ((unsigned int) 0x3 << 16) // (TC) RA Loading Selection
#define 	AT91C_TC_LDRA_NONE                 ((unsigned int) 0x0 << 16) // (TC) Edge: None
#define 	AT91C_TC_LDRA_RISING               ((unsigned int) 0x1 << 16) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRA_FALLING              ((unsigned int) 0x2 << 16) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRA_BOTH                 ((unsigned int) 0x3 << 16) // (TC) Edge: each edge of TIOA
#define AT91C_TC_ACPC         ((unsigned int) 0x3 << 18) // (TC) RC Compare Effect on TIOA
#define 	AT91C_TC_ACPC_NONE                 ((unsigned int) 0x0 << 18) // (TC) Effect: none
#define 	AT91C_TC_ACPC_SET                  ((unsigned int) 0x1 << 18) // (TC) Effect: set
#define 	AT91C_TC_ACPC_CLEAR                ((unsigned int) 0x2 << 18) // (TC) Effect: clear
#define 	AT91C_TC_ACPC_TOGGLE               ((unsigned int) 0x3 << 18) // (TC) Effect: toggle
#define AT91C_TC_LDRB         ((unsigned int) 0x3 << 18) // (TC) RB Loading Selection
#define 	AT91C_TC_LDRB_NONE                 ((unsigned int) 0x0 << 18) // (TC) Edge: None
#define 	AT91C_TC_LDRB_RISING               ((unsigned int) 0x1 << 18) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRB_FALLING              ((unsigned int) 0x2 << 18) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRB_BOTH                 ((unsigned int) 0x3 << 18) // (TC) Edge: each edge of TIOA
#define AT91C_TC_AEEVT        ((unsigned int) 0x3 << 20) // (TC) External Event Effect on TIOA
#define 	AT91C_TC_AEEVT_NONE                 ((unsigned int) 0x0 << 20) // (TC) Effect: none
#define 	AT91C_TC_AEEVT_SET                  ((unsigned int) 0x1 << 20) // (TC) Effect: set
#define 	AT91C_TC_AEEVT_CLEAR                ((unsigned int) 0x2 << 20) // (TC) Effect: clear
#define 	AT91C_TC_AEEVT_TOGGLE               ((unsigned int) 0x3 << 20) // (TC) Effect: toggle
#define AT91C_TC_ASWTRG       ((unsigned int) 0x3 << 22) // (TC) Software Trigger Effect on TIOA
#define 	AT91C_TC_ASWTRG_NONE                 ((unsigned int) 0x0 << 22) // (TC) Effect: none
#define 	AT91C_TC_ASWTRG_SET                  ((unsigned int) 0x1 << 22) // (TC) Effect: set
#define 	AT91C_TC_ASWTRG_CLEAR                ((unsigned int) 0x2 << 22) // (TC) Effect: clear
#define 	AT91C_TC_ASWTRG_TOGGLE               ((unsigned int) 0x3 << 22) // (TC) Effect: toggle
#define AT91C_TC_BCPB         ((unsigned int) 0x3 << 24) // (TC) RB Compare Effect on TIOB
#define 	AT91C_TC_BCPB_NONE                 ((unsigned int) 0x0 << 24) // (TC) Effect: none
#define 	AT91C_TC_BCPB_SET                  ((unsigned int) 0x1 << 24) // (TC) Effect: set
#define 	AT91C_TC_BCPB_CLEAR                ((unsigned int) 0x2 << 24) // (TC) Effect: clear
#define 	AT91C_TC_BCPB_TOGGLE               ((unsigned int) 0x3 << 24) // (TC) Effect: toggle
#define AT91C_TC_BCPC         ((unsigned int) 0x3 << 26) // (TC) RC Compare Effect on TIOB
#define 	AT91C_TC_BCPC_NONE                 ((unsigned int) 0x0 << 26) // (TC) Effect: none
#define 	AT91C_TC_BCPC_SET                  ((unsigned int) 0x1 << 26) // (TC) Effect: set
#define 	AT91C_TC_BCPC_CLEAR                ((unsigned int) 0x2 << 26) // (TC) Effect: clear
#define 	AT91C_TC_BCPC_TOGGLE               ((unsigned int) 0x3 << 26) // (TC) Effect: toggle
#define AT91C_TC_BEEVT        ((unsigned int) 0x3 << 28) // (TC) External Event Effect on TIOB
#define 	AT91C_TC_BEEVT_NONE                 ((unsigned int) 0x0 << 28) // (TC) Effect: none
#define 	AT91C_TC_BEEVT_SET                  ((unsigned int) 0x1 << 28) // (TC) Effect: set
#define 	AT91C_TC_BEEVT_CLEAR                ((unsigned int) 0x2 << 28) // (TC) Effect: clear
#define 	AT91C_TC_BEEVT_TOGGLE               ((unsigned int) 0x3 << 28) // (TC) Effect: toggle
#define AT91C_TC_BSWTRG       ((unsigned int) 0x3 << 30) // (TC) Software Trigger Effect on TIOB
#define 	AT91C_TC_BSWTRG_NONE                 ((unsigned int) 0x0 << 30) // (TC) Effect: none
#define 	AT91C_TC_BSWTRG_SET                  ((unsigned int) 0x1 << 30) // (TC) Effect: set
#define 	AT91C_TC_BSWTRG_CLEAR                ((unsigned int) 0x2 << 30) // (TC) Effect: clear
#define 	AT91C_TC_BSWTRG_TOGGLE               ((unsigned int) 0x3 << 30) // (TC) Effect: toggle
// -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
#define AT91C_TC_COVFS        ((unsigned int) 0x1 <<  0) // (TC) Counter Overflow
#define AT91C_TC_LOVRS        ((unsigned int) 0x1 <<  1) // (TC) Load Overrun
#define AT91C_TC_CPAS         ((unsigned int) 0x1 <<  2) // (TC) RA Compare
#define AT91C_TC_CPBS         ((unsigned int) 0x1 <<  3) // (TC) RB Compare
#define AT91C_TC_CPCS         ((unsigned int) 0x1 <<  4) // (TC) RC Compare
#define AT91C_TC_LDRAS        ((unsigned int) 0x1 <<  5) // (TC) RA Loading
#define AT91C_TC_LDRBS        ((unsigned int) 0x1 <<  6) // (TC) RB Loading
#define AT91C_TC_ETRGS        ((unsigned int) 0x1 <<  7) // (TC) External Trigger
#define AT91C_TC_CLKSTA       ((unsigned int) 0x1 << 16) // (TC) Clock Enabling
#define AT91C_TC_MTIOA        ((unsigned int) 0x1 << 17) // (TC) TIOA Mirror
#define AT91C_TC_MTIOB        ((unsigned int) 0x1 << 18) // (TC) TIOA Mirror
// -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Interface
// *****************************************************************************
typedef struct _AT91S_TCB {
	AT91S_TC	 TCB_TC0; 	// TC Channel 0
	AT91_REG	 Reserved0[4]; 	// 
	AT91S_TC	 TCB_TC1; 	// TC Channel 1
	AT91_REG	 Reserved1[4]; 	// 
	AT91S_TC	 TCB_TC2; 	// TC Channel 2
	AT91_REG	 Reserved2[4]; 	// 
	AT91_REG	 TCB_BCR; 	// TC Block Control Register
	AT91_REG	 TCB_BMR; 	// TC Block Mode Register
} AT91S_TCB, *AT91PS_TCB;

// -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
#define AT91C_TCB_SYNC        ((unsigned int) 0x1 <<  0) // (TCB) Synchro Command
// -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
#define AT91C_TCB_TC0XC0S     ((unsigned int) 0x3 <<  0) // (TCB) External Clock Signal 0 Selection
#define 	AT91C_TCB_TC0XC0S_TCLK0                ((unsigned int) 0x0) // (TCB) TCLK0 connected to XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 ((unsigned int) 0x1) // (TCB) None signal connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                ((unsigned int) 0x2) // (TCB) TIOA1 connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                ((unsigned int) 0x3) // (TCB) TIOA2 connected to XC0
#define AT91C_TCB_TC1XC1S     ((unsigned int) 0x3 <<  2) // (TCB) External Clock Signal 1 Selection
#define 	AT91C_TCB_TC1XC1S_TCLK1                ((unsigned int) 0x0 <<  2) // (TCB) TCLK1 connected to XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 ((unsigned int) 0x1 <<  2) // (TCB) None signal connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                ((unsigned int) 0x2 <<  2) // (TCB) TIOA0 connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                ((unsigned int) 0x3 <<  2) // (TCB) TIOA2 connected to XC1
#define AT91C_TCB_TC2XC2S     ((unsigned int) 0x3 <<  4) // (TCB) External Clock Signal 2 Selection
#define 	AT91C_TCB_TC2XC2S_TCLK2                ((unsigned int) 0x0 <<  4) // (TCB) TCLK2 connected to XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 ((unsigned int) 0x1 <<  4) // (TCB) None signal connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                ((unsigned int) 0x2 <<  4) // (TCB) TIOA0 connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                ((unsigned int) 0x3 <<  4) // (TCB) TIOA2 connected to XC2

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Device Interface
// *****************************************************************************
typedef struct _AT91S_UDP {
	AT91_REG	 UDP_NUM; 	// Frame Number Register
	AT91_REG	 UDP_GLBSTATE; 	// Global State Register
	AT91_REG	 UDP_FADDR; 	// Function Address Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 UDP_IER; 	// Interrupt Enable Register
	AT91_REG	 UDP_IDR; 	// Interrupt Disable Register
	AT91_REG	 UDP_IMR; 	// Interrupt Mask Register
	AT91_REG	 UDP_ISR; 	// Interrupt Status Register
	AT91_REG	 UDP_ICR; 	// Interrupt Clear Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 UDP_RSTEP; 	// Reset Endpoint Register
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 UDP_CSR[6]; 	// Endpoint Control and Status Register
	AT91_REG	 Reserved3[2]; 	// 
	AT91_REG	 UDP_FDR[6]; 	// Endpoint FIFO Data Register
	AT91_REG	 Reserved4[3]; 	// 
	AT91_REG	 UDP_TXVC; 	// Transceiver Control Register
} AT91S_UDP, *AT91PS_UDP;

// -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- 
#define AT91C_UDP_FRM_NUM     ((unsigned int) 0x7FF <<  0) // (UDP) Frame Number as Defined in the Packet Field Formats
#define AT91C_UDP_FRM_ERR     ((unsigned int) 0x1 << 16) // (UDP) Frame Error
#define AT91C_UDP_FRM_OK      ((unsigned int) 0x1 << 17) // (UDP) Frame OK
// -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- 
#define AT91C_UDP_FADDEN      ((unsigned int) 0x1 <<  0) // (UDP) Function Address Enable
#define AT91C_UDP_CONFG       ((unsigned int) 0x1 <<  1) // (UDP) Configured
#define AT91C_UDP_ESR         ((unsigned int) 0x1 <<  2) // (UDP) Enable Send Resume
#define AT91C_UDP_RSMINPR     ((unsigned int) 0x1 <<  3) // (UDP) A Resume Has Been Sent to the Host
#define AT91C_UDP_RMWUPE      ((unsigned int) 0x1 <<  4) // (UDP) Remote Wake Up Enable
// -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- 
#define AT91C_UDP_FADD        ((unsigned int) 0xFF <<  0) // (UDP) Function Address Value
#define AT91C_UDP_FEN         ((unsigned int) 0x1 <<  8) // (UDP) Function Enable
// -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- 
#define AT91C_UDP_EPINT0      ((unsigned int) 0x1 <<  0) // (UDP) Endpoint 0 Interrupt
#define AT91C_UDP_EPINT1      ((unsigned int) 0x1 <<  1) // (UDP) Endpoint 0 Interrupt
#define AT91C_UDP_EPINT2      ((unsigned int) 0x1 <<  2) // (UDP) Endpoint 2 Interrupt
#define AT91C_UDP_EPINT3      ((unsigned int) 0x1 <<  3) // (UDP) Endpoint 3 Interrupt
#define AT91C_UDP_EPINT4      ((unsigned int) 0x1 <<  4) // (UDP) Endpoint 4 Interrupt
#define AT91C_UDP_EPINT5      ((unsigned int) 0x1 <<  5) // (UDP) Endpoint 5 Interrupt
#define AT91C_UDP_RXSUSP      ((unsigned int) 0x1 <<  8) // (UDP) USB Suspend Interrupt
#define AT91C_UDP_RXRSM       ((unsigned int) 0x1 <<  9) // (UDP) USB Resume Interrupt
#define AT91C_UDP_EXTRSM      ((unsigned int) 0x1 << 10) // (UDP) USB External Resume Interrupt
#define AT91C_UDP_SOFINT      ((unsigned int) 0x1 << 11) // (UDP) USB Start Of frame Interrupt
#define AT91C_UDP_WAKEUP      ((unsigned int) 0x1 << 13) // (UDP) USB Resume Interrupt
// -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- 
// -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- 
// -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- 
#define AT91C_UDP_ENDBUSRES   ((unsigned int) 0x1 << 12) // (UDP) USB End Of Bus Reset Interrupt
// -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- 
// -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- 
#define AT91C_UDP_EP0         ((unsigned int) 0x1 <<  0) // (UDP) Reset Endpoint 0
#define AT91C_UDP_EP1         ((unsigned int) 0x1 <<  1) // (UDP) Reset Endpoint 1
#define AT91C_UDP_EP2         ((unsigned int) 0x1 <<  2) // (UDP) Reset Endpoint 2
#define AT91C_UDP_EP3         ((unsigned int) 0x1 <<  3) // (UDP) Reset Endpoint 3
#define AT91C_UDP_EP4         ((unsigned int) 0x1 <<  4) // (UDP) Reset Endpoint 4
#define AT91C_UDP_EP5         ((unsigned int) 0x1 <<  5) // (UDP) Reset Endpoint 5
// -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- 
#define AT91C_UDP_TXCOMP      ((unsigned int) 0x1 <<  0) // (UDP) Generates an IN packet with data previously written in the DPR
#define AT91C_UDP_RX_DATA_BK0 ((unsigned int) 0x1 <<  1) // (UDP) Receive Data Bank 0
#define AT91C_UDP_RXSETUP     ((unsigned int) 0x1 <<  2) // (UDP) Sends STALL to the Host (Control endpoints)
#define AT91C_UDP_ISOERROR    ((unsigned int) 0x1 <<  3) // (UDP) Isochronous error (Isochronous endpoints)
#define AT91C_UDP_STALLSENT   ((unsigned int) 0x1 <<  3) // (UDP) Stall sent (Control, bulk, interrupt endpoints)
#define AT91C_UDP_TXPKTRDY    ((unsigned int) 0x1 <<  4) // (UDP) Transmit Packet Ready
#define AT91C_UDP_FORCESTALL  ((unsigned int) 0x1 <<  5) // (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints).
#define AT91C_UDP_RX_DATA_BK1 ((unsigned int) 0x1 <<  6) // (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes).
#define AT91C_UDP_DIR         ((unsigned int) 0x1 <<  7) // (UDP) Transfer Direction
#define AT91C_UDP_EPTYPE      ((unsigned int) 0x7 <<  8) // (UDP) Endpoint type
#define 	AT91C_UDP_EPTYPE_CTRL                 ((unsigned int) 0x0 <<  8) // (UDP) Control
#define 	AT91C_UDP_EPTYPE_ISO_OUT              ((unsigned int) 0x1 <<  8) // (UDP) Isochronous OUT
#define 	AT91C_UDP_EPTYPE_BULK_OUT             ((unsigned int) 0x2 <<  8) // (UDP) Bulk OUT
#define 	AT91C_UDP_EPTYPE_INT_OUT              ((unsigned int) 0x3 <<  8) // (UDP) Interrupt OUT
#define 	AT91C_UDP_EPTYPE_ISO_IN               ((unsigned int) 0x5 <<  8) // (UDP) Isochronous IN
#define 	AT91C_UDP_EPTYPE_BULK_IN              ((unsigned int) 0x6 <<  8) // (UDP) Bulk IN
#define 	AT91C_UDP_EPTYPE_INT_IN               ((unsigned int) 0x7 <<  8) // (UDP) Interrupt IN
#define AT91C_UDP_DTGLE       ((unsigned int) 0x1 << 11) // (UDP) Data Toggle
#define AT91C_UDP_EPEDS       ((unsigned int) 0x1 << 15) // (UDP) Endpoint Enable Disable
#define AT91C_UDP_RXBYTECNT   ((unsigned int) 0x7FF << 16) // (UDP) Number Of Bytes Available in the FIFO
// -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- 
#define AT91C_UDP_TXVDIS      ((unsigned int) 0x1 <<  8) // (UDP) 
#define AT91C_UDP_PUON        ((unsigned int) 0x1 <<  9) // (UDP) Pull-up ON

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
// *****************************************************************************
typedef struct _AT91S_MCI {
	AT91_REG	 MCI_CR; 	// MCI Control Register
	AT91_REG	 MCI_MR; 	// MCI Mode Register
	AT91_REG	 MCI_DTOR; 	// MCI Data Timeout Register
	AT91_REG	 MCI_SDCR; 	// MCI SD Card Register
	AT91_REG	 MCI_ARGR; 	// MCI Argument Register
	AT91_REG	 MCI_CMDR; 	// MCI Command Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 MCI_RSPR[4]; 	// MCI Response Register
	AT91_REG	 MCI_RDR; 	// MCI Receive Data Register
	AT91_REG	 MCI_TDR; 	// MCI Transmit Data Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 MCI_SR; 	// MCI Status Register
	AT91_REG	 MCI_IER; 	// MCI Interrupt Enable Register
	AT91_REG	 MCI_IDR; 	// MCI Interrupt Disable Register
	AT91_REG	 MCI_IMR; 	// MCI Interrupt Mask Register
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 MCI_RPR; 	// Receive Pointer Register
	AT91_REG	 MCI_RCR; 	// Receive Counter Register
	AT91_REG	 MCI_TPR; 	// Transmit Pointer Register
	AT91_REG	 MCI_TCR; 	// Transmit Counter Register
	AT91_REG	 MCI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 MCI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 MCI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 MCI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 MCI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 MCI_PTSR; 	// PDC Transfer Status Register
} AT91S_MCI, *AT91PS_MCI;

// -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
#define AT91C_MCI_MCIEN       ((unsigned int) 0x1 <<  0) // (MCI) Multimedia Interface Enable
#define AT91C_MCI_MCIDIS      ((unsigned int) 0x1 <<  1) // (MCI) Multimedia Interface Disable
#define AT91C_MCI_PWSEN       ((unsigned int) 0x1 <<  2) // (MCI) Power Save Mode Enable
#define AT91C_MCI_PWSDIS      ((unsigned int) 0x1 <<  3) // (MCI) Power Save Mode Disable
#define AT91C_MCI_SWRST       ((unsigned int) 0x1 <<  7) // (MCI) MCI Software reset
// -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
#define AT91C_MCI_CLKDIV      ((unsigned int) 0xFF <<  0) // (MCI) Clock Divider
#define AT91C_MCI_PWSDIV      ((unsigned int) 0x7 <<  8) // (MCI) Power Saving Divider
#define AT91C_MCI_PDCPADV     ((unsigned int) 0x1 << 14) // (MCI) PDC Padding Value
#define AT91C_MCI_PDCMODE     ((unsigned int) 0x1 << 15) // (MCI) PDC Oriented Mode
#define AT91C_MCI_BLKLEN      ((unsigned int) 0xFFF << 18) // (MCI) Data Block Length
// -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
#define AT91C_MCI_DTOCYC      ((unsigned int) 0xF <<  0) // (MCI) Data Timeout Cycle Number
#define AT91C_MCI_DTOMUL      ((unsigned int) 0x7 <<  4) // (MCI) Data Timeout Multiplier
#define 	AT91C_MCI_DTOMUL_1                    ((unsigned int) 0x0 <<  4) // (MCI) DTOCYC x 1
#define 	AT91C_MCI_DTOMUL_16                   ((unsigned int) 0x1 <<  4) // (MCI) DTOCYC x 16
#define 	AT91C_MCI_DTOMUL_128                  ((unsigned int) 0x2 <<  4) // (MCI) DTOCYC x 128
#define 	AT91C_MCI_DTOMUL_256                  ((unsigned int) 0x3 <<  4) // (MCI) DTOCYC x 256
#define 	AT91C_MCI_DTOMUL_1024                 ((unsigned int) 0x4 <<  4) // (MCI) DTOCYC x 1024
#define 	AT91C_MCI_DTOMUL_4096                 ((unsigned int) 0x5 <<  4) // (MCI) DTOCYC x 4096
#define 	AT91C_MCI_DTOMUL_65536                ((unsigned int) 0x6 <<  4) // (MCI) DTOCYC x 65536
#define 	AT91C_MCI_DTOMUL_1048576              ((unsigned int) 0x7 <<  4) // (MCI) DTOCYC x 1048576
// -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
#define AT91C_MCI_SCDSEL      ((unsigned int) 0xF <<  0) // (MCI) SD Card Selector
#define AT91C_MCI_SCDBUS      ((unsigned int) 0x1 <<  7) // (MCI) SD Card Bus Width
// -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
#define AT91C_MCI_CMDNB       ((unsigned int) 0x3F <<  0) // (MCI) Command Number
#define AT91C_MCI_RSPTYP      ((unsigned int) 0x3 <<  6) // (MCI) Response Type
#define 	AT91C_MCI_RSPTYP_NO                   ((unsigned int) 0x0 <<  6) // (MCI) No response
#define 	AT91C_MCI_RSPTYP_48                   ((unsigned int) 0x1 <<  6) // (MCI) 48-bit response
#define 	AT91C_MCI_RSPTYP_136                  ((unsigned int) 0x2 <<  6) // (MCI) 136-bit response
#define AT91C_MCI_SPCMD       ((unsigned int) 0x7 <<  8) // (MCI) Special CMD
#define 	AT91C_MCI_SPCMD_NONE                 ((unsigned int) 0x0 <<  8) // (MCI) Not a special CMD
#define 	AT91C_MCI_SPCMD_INIT                 ((unsigned int) 0x1 <<  8) // (MCI) Initialization CMD
#define 	AT91C_MCI_SPCMD_SYNC                 ((unsigned int) 0x2 <<  8) // (MCI) Synchronized CMD
#define 	AT91C_MCI_SPCMD_IT_CMD               ((unsigned int) 0x4 <<  8) // (MCI) Interrupt command
#define 	AT91C_MCI_SPCMD_IT_REP               ((unsigned int) 0x5 <<  8) // (MCI) Interrupt response
#define AT91C_MCI_OPDCMD      ((unsigned int) 0x1 << 11) // (MCI) Open Drain Command
#define AT91C_MCI_MAXLAT      ((unsigned int) 0x1 << 12) // (MCI) Maximum Latency for Command to respond
#define AT91C_MCI_TRCMD       ((unsigned int) 0x3 << 16) // (MCI) Transfer CMD
#define 	AT91C_MCI_TRCMD_NO                   ((unsigned int) 0x0 << 16) // (MCI) No transfer
#define 	AT91C_MCI_TRCMD_START                ((unsigned int) 0x1 << 16) // (MCI) Start transfer
#define 	AT91C_MCI_TRCMD_STOP                 ((unsigned int) 0x2 << 16) // (MCI) Stop transfer
#define AT91C_MCI_TRDIR       ((unsigned int) 0x1 << 18) // (MCI) Transfer Direction
#define AT91C_MCI_TRTYP       ((unsigned int) 0x3 << 19) // (MCI) Transfer Type
#define 	AT91C_MCI_TRTYP_BLOCK                ((unsigned int) 0x0 << 19) // (MCI) Block Transfer type
#define 	AT91C_MCI_TRTYP_MULTIPLE             ((unsigned int) 0x1 << 19) // (MCI) Multiple Block transfer type
#define 	AT91C_MCI_TRTYP_STREAM               ((unsigned int) 0x2 << 19) // (MCI) Stream transfer type
// -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
#define AT91C_MCI_CMDRDY      ((unsigned int) 0x1 <<  0) // (MCI) Command Ready flag
#define AT91C_MCI_RXRDY       ((unsigned int) 0x1 <<  1) // (MCI) RX Ready flag
#define AT91C_MCI_TXRDY       ((unsigned int) 0x1 <<  2) // (MCI) TX Ready flag
#define AT91C_MCI_BLKE        ((unsigned int) 0x1 <<  3) // (MCI) Data Block Transfer Ended flag
#define AT91C_MCI_DTIP        ((unsigned int) 0x1 <<  4) // (MCI) Data Transfer in Progress flag
#define AT91C_MCI_NOTBUSY     ((unsigned int) 0x1 <<  5) // (MCI) Data Line Not Busy flag
#define AT91C_MCI_ENDRX       ((unsigned int) 0x1 <<  6) // (MCI) End of RX Buffer flag
#define AT91C_MCI_ENDTX       ((unsigned int) 0x1 <<  7) // (MCI) End of TX Buffer flag
#define AT91C_MCI_RXBUFF      ((unsigned int) 0x1 << 14) // (MCI) RX Buffer Full flag
#define AT91C_MCI_TXBUFE      ((unsigned int) 0x1 << 15) // (MCI) TX Buffer Empty flag
#define AT91C_MCI_RINDE       ((unsigned int) 0x1 << 16) // (MCI) Response Index Error flag
#define AT91C_MCI_RDIRE       ((unsigned int) 0x1 << 17) // (MCI) Response Direction Error flag
#define AT91C_MCI_RCRCE       ((unsigned int) 0x1 << 18) // (MCI) Response CRC Error flag
#define AT91C_MCI_RENDE       ((unsigned int) 0x1 << 19) // (MCI) Response End Bit Error flag
#define AT91C_MCI_RTOE        ((unsigned int) 0x1 << 20) // (MCI) Response Time-out Error flag
#define AT91C_MCI_DCRCE       ((unsigned int) 0x1 << 21) // (MCI) data CRC Error flag
#define AT91C_MCI_DTOE        ((unsigned int) 0x1 << 22) // (MCI) Data timeout Error flag
#define AT91C_MCI_OVRE        ((unsigned int) 0x1 << 30) // (MCI) Overrun flag
#define AT91C_MCI_UNRE        ((unsigned int) 0x1 << 31) // (MCI) Underrun flag
// -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
// -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
// -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Two-wire Interface
// *****************************************************************************
typedef struct _AT91S_TWI {
	AT91_REG	 TWI_CR; 	// Control Register
	AT91_REG	 TWI_MMR; 	// Master Mode Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 TWI_IADR; 	// Internal Address Register
	AT91_REG	 TWI_CWGR; 	// Clock Waveform Generator Register
	AT91_REG	 Reserved1[3]; 	// 
	AT91_REG	 TWI_SR; 	// Status Register
	AT91_REG	 TWI_IER; 	// Interrupt Enable Register
	AT91_REG	 TWI_IDR; 	// Interrupt Disable Register
	AT91_REG	 TWI_IMR; 	// Interrupt Mask Register
	AT91_REG	 TWI_RHR; 	// Receive Holding Register
	AT91_REG	 TWI_THR; 	// Transmit Holding Register
} AT91S_TWI, *AT91PS_TWI;

// -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
#define AT91C_TWI_START       ((unsigned int) 0x1 <<  0) // (TWI) Send a START Condition
#define AT91C_TWI_STOP        ((unsigned int) 0x1 <<  1) // (TWI) Send a STOP Condition
#define AT91C_TWI_MSEN        ((unsigned int) 0x1 <<  2) // (TWI) TWI Master Transfer Enabled
#define AT91C_TWI_MSDIS       ((unsigned int) 0x1 <<  3) // (TWI) TWI Master Transfer Disabled
#define AT91C_TWI_SWRST       ((unsigned int) 0x1 <<  7) // (TWI) Software Reset
// -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
#define AT91C_TWI_IADRSZ      ((unsigned int) 0x3 <<  8) // (TWI) Internal Device Address Size
#define 	AT91C_TWI_IADRSZ_NO                   ((unsigned int) 0x0 <<  8) // (TWI) No internal device address
#define 	AT91C_TWI_IADRSZ_1_BYTE               ((unsigned int) 0x1 <<  8) // (TWI) One-byte internal device address
#define 	AT91C_TWI_IADRSZ_2_BYTE               ((unsigned int) 0x2 <<  8) // (TWI) Two-byte internal device address
#define 	AT91C_TWI_IADRSZ_3_BYTE               ((unsigned int) 0x3 <<  8) // (TWI) Three-byte internal device address
#define AT91C_TWI_MREAD       ((unsigned int) 0x1 << 12) // (TWI) Master Read Direction
#define AT91C_TWI_DADR        ((unsigned int) 0x7F << 16) // (TWI) Device Address
// -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
#define AT91C_TWI_CLDIV       ((unsigned int) 0xFF <<  0) // (TWI) Clock Low Divider
#define AT91C_TWI_CHDIV       ((unsigned int) 0xFF <<  8) // (TWI) Clock High Divider
#define AT91C_TWI_CKDIV       ((unsigned int) 0x7 << 16) // (TWI) Clock Divider
// -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
#define AT91C_TWI_TXCOMP      ((unsigned int) 0x1 <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_RXRDY       ((unsigned int) 0x1 <<  1) // (TWI) Receive holding register ReaDY
#define AT91C_TWI_TXRDY       ((unsigned int) 0x1 <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_OVRE        ((unsigned int) 0x1 <<  6) // (TWI) Overrun Error
#define AT91C_TWI_UNRE        ((unsigned int) 0x1 <<  7) // (TWI) Underrun Error
#define AT91C_TWI_NACK        ((unsigned int) 0x1 <<  8) // (TWI) Not Acknowledged
// -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
// -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
// -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Usart
// *****************************************************************************
typedef struct _AT91S_USART {
	AT91_REG	 US_CR; 	// Control Register
	AT91_REG	 US_MR; 	// Mode Register
	AT91_REG	 US_IER; 	// Interrupt Enable Register
	AT91_REG	 US_IDR; 	// Interrupt Disable Register
	AT91_REG	 US_IMR; 	// Interrupt Mask Register
	AT91_REG	 US_CSR; 	// Channel Status Register
	AT91_REG	 US_RHR; 	// Receiver Holding Register
	AT91_REG	 US_THR; 	// Transmitter Holding Register
	AT91_REG	 US_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 US_RTOR; 	// Receiver Time-out Register
	AT91_REG	 US_TTGR; 	// Transmitter Time-guard Register
	AT91_REG	 Reserved0[5]; 	// 
	AT91_REG	 US_FIDI; 	// FI_DI_Ratio Register
	AT91_REG	 US_NER; 	// Nb Errors Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 US_IF; 	// IRDA_FILTER Register
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 US_RPR; 	// Receive Pointer Register
	AT91_REG	 US_RCR; 	// Receive Counter Register
	AT91_REG	 US_TPR; 	// Transmit Pointer Register
	AT91_REG	 US_TCR; 	// Transmit Counter Register
	AT91_REG	 US_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 US_RNCR; 	// Receive Next Counter Register
	AT91_REG	 US_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 US_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 US_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 US_PTSR; 	// PDC Transfer Status Register
} AT91S_USART, *AT91PS_USART;

// -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_STTBRK       ((unsigned int) 0x1 <<  9) // (USART) Start Break
#define AT91C_US_STPBRK       ((unsigned int) 0x1 << 10) // (USART) Stop Break
#define AT91C_US_STTTO        ((unsigned int) 0x1 << 11) // (USART) Start Time-out
#define AT91C_US_SENDA        ((unsigned int) 0x1 << 12) // (USART) Send Address
#define AT91C_US_RSTIT        ((unsigned int) 0x1 << 13) // (USART) Reset Iterations
#define AT91C_US_RSTNACK      ((unsigned int) 0x1 << 14) // (USART) Reset Non Acknowledge
#define AT91C_US_RETTO        ((unsigned int) 0x1 << 15) // (USART) Rearm Time-out
#define AT91C_US_DTREN        ((unsigned int) 0x1 << 16) // (USART) Data Terminal ready Enable
#define AT91C_US_DTRDIS       ((unsigned int) 0x1 << 17) // (USART) Data Terminal ready Disable
#define AT91C_US_RTSEN        ((unsigned int) 0x1 << 18) // (USART) Request to Send enable
#define AT91C_US_RTSDIS       ((unsigned int) 0x1 << 19) // (USART) Request to Send Disable
// -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_USMODE       ((unsigned int) 0xF <<  0) // (USART) Usart mode
#define 	AT91C_US_USMODE_NORMAL               ((unsigned int) 0x0) // (USART) Normal
#define 	AT91C_US_USMODE_RS485                ((unsigned int) 0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                ((unsigned int) 0x2) // (USART) Hardware Handshaking
#define 	AT91C_US_USMODE_MODEM                ((unsigned int) 0x3) // (USART) Modem
#define 	AT91C_US_USMODE_ISO7816_0            ((unsigned int) 0x4) // (USART) ISO7816 protocol: T = 0
#define 	AT91C_US_USMODE_ISO7816_1            ((unsigned int) 0x6) // (USART) ISO7816 protocol: T = 1
#define 	AT91C_US_USMODE_IRDA                 ((unsigned int) 0x8) // (USART) IrDA
#define 	AT91C_US_USMODE_SWHSH                ((unsigned int) 0xC) // (USART) Software Handshaking
#define AT91C_US_CLKS         ((unsigned int) 0x3 <<  4) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CLKS_CLOCK                ((unsigned int) 0x0 <<  4) // (USART) Clock
#define 	AT91C_US_CLKS_FDIV1                ((unsigned int) 0x1 <<  4) // (USART) fdiv1
#define 	AT91C_US_CLKS_SLOW                 ((unsigned int) 0x2 <<  4) // (USART) slow_clock (ARM)
#define 	AT91C_US_CLKS_EXT                  ((unsigned int) 0x3 <<  4) // (USART) External (SCK)
#define AT91C_US_CHRL         ((unsigned int) 0x3 <<  6) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CHRL_5_BITS               ((unsigned int) 0x0 <<  6) // (USART) Character Length: 5 bits
#define 	AT91C_US_CHRL_6_BITS               ((unsigned int) 0x1 <<  6) // (USART) Character Length: 6 bits
#define 	AT91C_US_CHRL_7_BITS               ((unsigned int) 0x2 <<  6) // (USART) Character Length: 7 bits
#define 	AT91C_US_CHRL_8_BITS               ((unsigned int) 0x3 <<  6) // (USART) Character Length: 8 bits
#define AT91C_US_SYNC         ((unsigned int) 0x1 <<  8) // (USART) Synchronous Mode Select
#define AT91C_US_NBSTOP       ((unsigned int) 0x3 << 12) // (USART) Number of Stop bits
#define 	AT91C_US_NBSTOP_1_BIT                ((unsigned int) 0x0 << 12) // (USART) 1 stop bit
#define 	AT91C_US_NBSTOP_15_BIT               ((unsigned int) 0x1 << 12) // (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
#define 	AT91C_US_NBSTOP_2_BIT                ((unsigned int) 0x2 << 12) // (USART) 2 stop bits
#define AT91C_US_MSBF         ((unsigned int) 0x1 << 16) // (USART) Bit Order
#define AT91C_US_MODE9        ((unsigned int) 0x1 << 17) // (USART) 9-bit Character length
#define AT91C_US_CKLO         ((unsigned int) 0x1 << 18) // (USART) Clock Output Select
#define AT91C_US_OVER         ((unsigned int) 0x1 << 19) // (USART) Over Sampling Mode
#define AT91C_US_INACK        ((unsigned int) 0x1 << 20) // (USART) Inhibit Non Acknowledge
#define AT91C_US_DSNACK       ((unsigned int) 0x1 << 21) // (USART) Disable Successive NACK
#define AT91C_US_MAX_ITER     ((unsigned int) 0x1 << 24) // (USART) Number of Repetitions
#define AT91C_US_FILTER       ((unsigned int) 0x1 << 28) // (USART) Receive Line Filter
// -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXBRK        ((unsigned int) 0x1 <<  2) // (USART) Break Received/End of Break
#define AT91C_US_TIMEOUT      ((unsigned int) 0x1 <<  8) // (USART) Receiver Time-out
#define AT91C_US_ITERATION    ((unsigned int) 0x1 << 10) // (USART) Max number of Repetitions Reached
#define AT91C_US_NACK         ((unsigned int) 0x1 << 13) // (USART) Non Acknowledge
#define AT91C_US_RIIC         ((unsigned int) 0x1 << 16) // (USART) Ring INdicator Input Change Flag
#define AT91C_US_DSRIC        ((unsigned int) 0x1 << 17) // (USART) Data Set Ready Input Change Flag
#define AT91C_US_DCDIC        ((unsigned int) 0x1 << 18) // (USART) Data Carrier Flag
#define AT91C_US_CTSIC        ((unsigned int) 0x1 << 19) // (USART) Clear To Send Input Change Flag
// -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
#define AT91C_US_RI           ((unsigned int) 0x1 << 20) // (USART) Image of RI Input
#define AT91C_US_DSR          ((unsigned int) 0x1 << 21) // (USART) Image of DSR Input
#define AT91C_US_DCD          ((unsigned int) 0x1 << 22) // (USART) Image of DCD Input
#define AT91C_US_CTS          ((unsigned int) 0x1 << 23) // (USART) Image of CTS Input

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
// *****************************************************************************
typedef struct _AT91S_SSC {
	AT91_REG	 SSC_CR; 	// Control Register
	AT91_REG	 SSC_CMR; 	// Clock Mode Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 SSC_RCMR; 	// Receive Clock ModeRegister
	AT91_REG	 SSC_RFMR; 	// Receive Frame Mode Register
	AT91_REG	 SSC_TCMR; 	// Transmit Clock Mode Register
	AT91_REG	 SSC_TFMR; 	// Transmit Frame Mode Register
	AT91_REG	 SSC_RHR; 	// Receive Holding Register
	AT91_REG	 SSC_THR; 	// Transmit Holding Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 SSC_RSHR; 	// Receive Sync Holding Register
	AT91_REG	 SSC_TSHR; 	// Transmit Sync Holding Register
	AT91_REG	 Reserved2[2]; 	// 
	AT91_REG	 SSC_SR; 	// Status Register
	AT91_REG	 SSC_IER; 	// Interrupt Enable Register
	AT91_REG	 SSC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SSC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved3[44]; 	// 
	AT91_REG	 SSC_RPR; 	// Receive Pointer Register
	AT91_REG	 SSC_RCR; 	// Receive Counter Register
	AT91_REG	 SSC_TPR; 	// Transmit Pointer Register
	AT91_REG	 SSC_TCR; 	// Transmit Counter Register
	AT91_REG	 SSC_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SSC_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SSC_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SSC_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SSC_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SSC_PTSR; 	// PDC Transfer Status Register
} AT91S_SSC, *AT91PS_SSC;

// -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
#define AT91C_SSC_RXEN        ((unsigned int) 0x1 <<  0) // (SSC) Receive Enable
#define AT91C_SSC_RXDIS       ((unsigned int) 0x1 <<  1) // (SSC) Receive Disable
#define AT91C_SSC_TXEN        ((unsigned int) 0x1 <<  8) // (SSC) Transmit Enable
#define AT91C_SSC_TXDIS       ((unsigned int) 0x1 <<  9) // (SSC) Transmit Disable
#define AT91C_SSC_SWRST       ((unsigned int) 0x1 << 15) // (SSC) Software Reset
// -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
#define AT91C_SSC_CKS         ((unsigned int) 0x3 <<  0) // (SSC) Receive/Transmit Clock Selection
#define 	AT91C_SSC_CKS_DIV                  ((unsigned int) 0x0) // (SSC) Divided Clock
#define 	AT91C_SSC_CKS_TK                   ((unsigned int) 0x1) // (SSC) TK Clock signal
#define 	AT91C_SSC_CKS_RK                   ((unsigned int) 0x2) // (SSC) RK pin
#define AT91C_SSC_CKO         ((unsigned int) 0x7 <<  2) // (SSC) Receive/Transmit Clock Output Mode Selection
#define 	AT91C_SSC_CKO_NONE                 ((unsigned int) 0x0 <<  2) // (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
#define 	AT91C_SSC_CKO_CONTINOUS            ((unsigned int) 0x1 <<  2) // (SSC) Continuous Receive/Transmit Clock RK pin: Output
#define 	AT91C_SSC_CKO_DATA_TX              ((unsigned int) 0x2 <<  2) // (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
#define AT91C_SSC_CKI         ((unsigned int) 0x1 <<  5) // (SSC) Receive/Transmit Clock Inversion
#define AT91C_SSC_CKG         ((unsigned int) 0x3 <<  6) // (SSC) Receive/Transmit Clock Gating Selection
#define 	AT91C_SSC_CKG_NONE                 ((unsigned int) 0x0 <<  6) // (SSC) Receive/Transmit Clock Gating: None, continuous clock
#define 	AT91C_SSC_CKG_LOW                  ((unsigned int) 0x1 <<  6) // (SSC) Receive/Transmit Clock enabled only if RF Low
#define 	AT91C_SSC_CKG_HIGH                 ((unsigned int) 0x2 <<  6) // (SSC) Receive/Transmit Clock enabled only if RF High
#define AT91C_SSC_START       ((unsigned int) 0xF <<  8) // (SSC) Receive/Transmit Start Selection
#define 	AT91C_SSC_START_CONTINOUS            ((unsigned int) 0x0 <<  8) // (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
#define 	AT91C_SSC_START_TX                   ((unsigned int) 0x1 <<  8) // (SSC) Transmit/Receive start
#define 	AT91C_SSC_START_LOW_RF               ((unsigned int) 0x2 <<  8) // (SSC) Detection of a low level on RF input
#define 	AT91C_SSC_START_HIGH_RF              ((unsigned int) 0x3 <<  8) // (SSC) Detection of a high level on RF input
#define 	AT91C_SSC_START_FALL_RF              ((unsigned int) 0x4 <<  8) // (SSC) Detection of a falling edge on RF input
#define 	AT91C_SSC_START_RISE_RF              ((unsigned int) 0x5 <<  8) // (SSC) Detection of a rising edge on RF input
#define 	AT91C_SSC_START_LEVEL_RF             ((unsigned int) 0x6 <<  8) // (SSC) Detection of any level change on RF input
#define 	AT91C_SSC_START_EDGE_RF              ((unsigned int) 0x7 <<  8) // (SSC) Detection of any edge on RF input
#define 	AT91C_SSC_START_0                    ((unsigned int) 0x8 <<  8) // (SSC) Compare 0
#define AT91C_SSC_STOP        ((unsigned int) 0x1 << 12) // (SSC) Receive Stop Selection
#define AT91C_SSC_STTDLY      ((unsigned int) 0xFF << 16) // (SSC) Receive/Transmit Start Delay
#define AT91C_SSC_PERIOD      ((unsigned int) 0xFF << 24) // (SSC) Receive/Transmit Period Divider Selection
// -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
#define AT91C_SSC_DATLEN      ((unsigned int) 0x1F <<  0) // (SSC) Data Length
#define AT91C_SSC_LOOP        ((unsigned int) 0x1 <<  5) // (SSC) Loop Mode
#define AT91C_SSC_MSBF        ((unsigned int) 0x1 <<  7) // (SSC) Most Significant Bit First
#define AT91C_SSC_DATNB       ((unsigned int) 0xF <<  8) // (SSC) Data Number per Frame
#define AT91C_SSC_FSLEN       ((unsigned int) 0xF << 16) // (SSC) Receive/Transmit Frame Sync length
#define AT91C_SSC_FSOS        ((unsigned int) 0x7 << 20) // (SSC) Receive/Transmit Frame Sync Output Selection
#define 	AT91C_SSC_FSOS_NONE                 ((unsigned int) 0x0 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
#define 	AT91C_SSC_FSOS_NEGATIVE             ((unsigned int) 0x1 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
#define 	AT91C_SSC_FSOS_POSITIVE             ((unsigned int) 0x2 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
#define 	AT91C_SSC_FSOS_LOW                  ((unsigned int) 0x3 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
#define 	AT91C_SSC_FSOS_HIGH                 ((unsigned int) 0x4 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
#define 	AT91C_SSC_FSOS_TOGGLE               ((unsigned int) 0x5 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
#define AT91C_SSC_FSEDGE      ((unsigned int) 0x1 << 24) // (SSC) Frame Sync Edge Detection
// -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
// -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
#define AT91C_SSC_DATDEF      ((unsigned int) 0x1 <<  5) // (SSC) Data Default Value
#define AT91C_SSC_FSDEN       ((unsigned int) 0x1 << 23) // (SSC) Frame Sync Data Enable
// -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
#define AT91C_SSC_TXRDY       ((unsigned int) 0x1 <<  0) // (SSC) Transmit Ready
#define AT91C_SSC_TXEMPTY     ((unsigned int) 0x1 <<  1) // (SSC) Transmit Empty
#define AT91C_SSC_ENDTX       ((unsigned int) 0x1 <<  2) // (SSC) End Of Transmission
#define AT91C_SSC_TXBUFE      ((unsigned int) 0x1 <<  3) // (SSC) Transmit Buffer Empty
#define AT91C_SSC_RXRDY       ((unsigned int) 0x1 <<  4) // (SSC) Receive Ready
#define AT91C_SSC_OVRUN       ((unsigned int) 0x1 <<  5) // (SSC) Receive Overrun
#define AT91C_SSC_ENDRX       ((unsigned int) 0x1 <<  6) // (SSC) End of Reception
#define AT91C_SSC_RXBUFF      ((unsigned int) 0x1 <<  7) // (SSC) Receive Buffer Full
#define AT91C_SSC_CP0         ((unsigned int) 0x1 <<  8) // (SSC) Compare 0
#define AT91C_SSC_CP1         ((unsigned int) 0x1 <<  9) // (SSC) Compare 1
#define AT91C_SSC_TXSYN       ((unsigned int) 0x1 << 10) // (SSC) Transmit Sync
#define AT91C_SSC_RXSYN       ((unsigned int) 0x1 << 11) // (SSC) Receive Sync
#define AT91C_SSC_TXENA       ((unsigned int) 0x1 << 16) // (SSC) Transmit Enable
#define AT91C_SSC_RXENA       ((unsigned int) 0x1 << 17) // (SSC) Receive Enable
// -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
// -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
// -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// *****************************************************************************
typedef struct _AT91S_SPI {
	AT91_REG	 SPI_CR; 	// Control Register
	AT91_REG	 SPI_MR; 	// Mode Register
	AT91_REG	 SPI_RDR; 	// Receive Data Register
	AT91_REG	 SPI_TDR; 	// Transmit Data Register
	AT91_REG	 SPI_SR; 	// Status Register
	AT91_REG	 SPI_IER; 	// Interrupt Enable Register
	AT91_REG	 SPI_IDR; 	// Interrupt Disable Register
	AT91_REG	 SPI_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved0[4]; 	// 
	AT91_REG	 SPI_CSR[4]; 	// Chip Select Register
	AT91_REG	 Reserved1[48]; 	// 
	AT91_REG	 SPI_RPR; 	// Receive Pointer Register
	AT91_REG	 SPI_RCR; 	// Receive Counter Register
	AT91_REG	 SPI_TPR; 	// Transmit Pointer Register
	AT91_REG	 SPI_TCR; 	// Transmit Counter Register
	AT91_REG	 SPI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SPI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SPI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SPI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SPI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SPI_PTSR; 	// PDC Transfer Status Register
} AT91S_SPI, *AT91PS_SPI;

// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
#define AT91C_SPI_SPIEN       ((unsigned int) 0x1 <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS      ((unsigned int) 0x1 <<  1) // (SPI) SPI Disable
#define AT91C_SPI_SWRST       ((unsigned int) 0x1 <<  7) // (SPI) SPI Software reset
#define AT91C_SPI_LASTXFER    ((unsigned int) 0x1 << 24) // (SPI) SPI Last Transfer
// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
#define AT91C_SPI_MSTR        ((unsigned int) 0x1 <<  0) // (SPI) Master/Slave Mode
#define AT91C_SPI_PS          ((unsigned int) 0x1 <<  1) // (SPI) Peripheral Select
#define 	AT91C_SPI_PS_FIXED                ((unsigned int) 0x0 <<  1) // (SPI) Fixed Peripheral Select
#define 	AT91C_SPI_PS_VARIABLE             ((unsigned int) 0x1 <<  1) // (SPI) Variable Peripheral Select
#define AT91C_SPI_PCSDEC      ((unsigned int) 0x1 <<  2) // (SPI) Chip Select Decode
#define AT91C_SPI_FDIV        ((unsigned int) 0x1 <<  3) // (SPI) Clock Selection
#define AT91C_SPI_MODFDIS     ((unsigned int) 0x1 <<  4) // (SPI) Mode Fault Detection
#define AT91C_SPI_LLB         ((unsigned int) 0x1 <<  7) // (SPI) Clock Selection
#define AT91C_SPI_PCS         ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_DLYBCS      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Chip Selects
// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
#define AT91C_SPI_RD          ((unsigned int) 0xFFFF <<  0) // (SPI) Receive Data
#define AT91C_SPI_RPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
#define AT91C_SPI_TD          ((unsigned int) 0xFFFF <<  0) // (SPI) Transmit Data
#define AT91C_SPI_TPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
#define AT91C_SPI_RDRF        ((unsigned int) 0x1 <<  0) // (SPI) Receive Data Register Full
#define AT91C_SPI_TDRE        ((unsigned int) 0x1 <<  1) // (SPI) Transmit Data Register Empty
#define AT91C_SPI_MODF        ((unsigned int) 0x1 <<  2) // (SPI) Mode Fault Error
#define AT91C_SPI_OVRES       ((unsigned int) 0x1 <<  3) // (SPI) Overrun Error Status
#define AT91C_SPI_ENDRX       ((unsigned int) 0x1 <<  4) // (SPI) End of Receiver Transfer
#define AT91C_SPI_ENDTX       ((unsigned int) 0x1 <<  5) // (SPI) End of Receiver Transfer
#define AT91C_SPI_RXBUFF      ((unsigned int) 0x1 <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_TXBUFE      ((unsigned int) 0x1 <<  7) // (SPI) TXBUFE Interrupt
#define AT91C_SPI_NSSR        ((unsigned int) 0x1 <<  8) // (SPI) NSSR Interrupt
#define AT91C_SPI_TXEMPTY     ((unsigned int) 0x1 <<  9) // (SPI) TXEMPTY Interrupt
#define AT91C_SPI_SPIENS      ((unsigned int) 0x1 << 16) // (SPI) Enable Status
// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
#define AT91C_SPI_CPOL        ((unsigned int) 0x1 <<  0) // (SPI) Clock Polarity
#define AT91C_SPI_NCPHA       ((unsigned int) 0x1 <<  1) // (SPI) Clock Phase
#define AT91C_SPI_CSAAT       ((unsigned int) 0x1 <<  3) // (SPI) Chip Select Active After Transfer
#define AT91C_SPI_BITS        ((unsigned int) 0xF <<  4) // (SPI) Bits Per Transfer
#define 	AT91C_SPI_BITS_8                    ((unsigned int) 0x0 <<  4) // (SPI) 8 Bits Per transfer
#define 	AT91C_SPI_BITS_9                    ((unsigned int) 0x1 <<  4) // (SPI) 9 Bits Per transfer
#define 	AT91C_SPI_BITS_10                   ((unsigned int) 0x2 <<  4) // (SPI) 10 Bits Per transfer
#define 	AT91C_SPI_BITS_11                   ((unsigned int) 0x3 <<  4) // (SPI) 11 Bits Per transfer
#define 	AT91C_SPI_BITS_12                   ((unsigned int) 0x4 <<  4) // (SPI) 12 Bits Per transfer
#define 	AT91C_SPI_BITS_13                   ((unsigned int) 0x5 <<  4) // (SPI) 13 Bits Per transfer
#define 	AT91C_SPI_BITS_14                   ((unsigned int) 0x6 <<  4) // (SPI) 14 Bits Per transfer
#define 	AT91C_SPI_BITS_15                   ((unsigned int) 0x7 <<  4) // (SPI) 15 Bits Per transfer
#define 	AT91C_SPI_BITS_16                   ((unsigned int) 0x8 <<  4) // (SPI) 16 Bits Per transfer
#define AT91C_SPI_SCBR        ((unsigned int) 0xFF <<  8) // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS       ((unsigned int) 0xFF << 16) // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Consecutive Transfers

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Host Interface
// *****************************************************************************
typedef struct _AT91S_UHP {
	AT91_REG	 UHP_HcRevision; 	// Revision
	AT91_REG	 UHP_HcControl; 	// Operating modes for the Host Controller
	AT91_REG	 UHP_HcCommandStatus; 	// Command & status Register
	AT91_REG	 UHP_HcInterruptStatus; 	// Interrupt Status Register
	AT91_REG	 UHP_HcInterruptEnable; 	// Interrupt Enable Register
	AT91_REG	 UHP_HcInterruptDisable; 	// Interrupt Disable Register
	AT91_REG	 UHP_HcHCCA; 	// Pointer to the Host Controller Communication Area
	AT91_REG	 UHP_HcPeriodCurrentED; 	// Current Isochronous or Interrupt Endpoint Descriptor
	AT91_REG	 UHP_HcControlHeadED; 	// First Endpoint Descriptor of the Control list
	AT91_REG	 UHP_HcControlCurrentED; 	// Endpoint Control and Status Register
	AT91_REG	 UHP_HcBulkHeadED; 	// First endpoint register of the Bulk list
	AT91_REG	 UHP_HcBulkCurrentED; 	// Current endpoint of the Bulk list
	AT91_REG	 UHP_HcBulkDoneHead; 	// Last completed transfer descriptor
	AT91_REG	 UHP_HcFmInterval; 	// Bit time between 2 consecutive SOFs
	AT91_REG	 UHP_HcFmRemaining; 	// Bit time remaining in the current Frame
	AT91_REG	 UHP_HcFmNumber; 	// Frame number
	AT91_REG	 UHP_HcPeriodicStart; 	// Periodic Start
	AT91_REG	 UHP_HcLSThreshold; 	// LS Threshold
	AT91_REG	 UHP_HcRhDescriptorA; 	// Root Hub characteristics A
	AT91_REG	 UHP_HcRhDescriptorB; 	// Root Hub characteristics B
	AT91_REG	 UHP_HcRhStatus; 	// Root Hub Status register
	AT91_REG	 UHP_HcRhPortStatus[2]; 	// Root Hub Port Status Register
} AT91S_UHP, *AT91PS_UHP;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR LCD Controller
// *****************************************************************************
typedef struct _AT91S_LCDC {
	AT91_REG	 LCDC_BA1; 	// DMA Base Address Register 1
	AT91_REG	 LCDC_BA2; 	// DMA Base Address Register 2
	AT91_REG	 LCDC_FRMP1; 	// DMA Frame Pointer Register 1
	AT91_REG	 LCDC_FRMP2; 	// DMA Frame Pointer Register 2
	AT91_REG	 LCDC_FRMA1; 	// DMA Frame Address Register 1
	AT91_REG	 LCDC_FRMA2; 	// DMA Frame Address Register 2
	AT91_REG	 LCDC_FRMCFG; 	// DMA Frame Configuration Register
	AT91_REG	 LCDC_DMACON; 	// DMA Control Register
	AT91_REG	 LCDC_DMA2DCFG; 	// DMA 2D addressing configuration
	AT91_REG	 Reserved0[503]; 	// 
	AT91_REG	 LCDC_LCDCON1; 	// LCD Control 1 Register
	AT91_REG	 LCDC_LCDCON2; 	// LCD Control 2 Register
	AT91_REG	 LCDC_TIM1; 	// LCD Timing Config 1 Register
	AT91_REG	 LCDC_TIM2; 	// LCD Timing Config 2 Register
	AT91_REG	 LCDC_LCDFRCFG; 	// LCD Frame Config Register
	AT91_REG	 LCDC_FIFO; 	// LCD FIFO Register
	AT91_REG	 LCDC_MVAL; 	// LCD Mode Toggle Rate Value Register
	AT91_REG	 LCDC_DP1_2; 	// Dithering Pattern DP1_2 Register
	AT91_REG	 LCDC_DP4_7; 	// Dithering Pattern DP4_7 Register
	AT91_REG	 LCDC_DP3_5; 	// Dithering Pattern DP3_5 Register
	AT91_REG	 LCDC_DP2_3; 	// Dithering Pattern DP2_3 Register
	AT91_REG	 LCDC_DP5_7; 	// Dithering Pattern DP5_7 Register
	AT91_REG	 LCDC_DP3_4; 	// Dithering Pattern DP3_4 Register
	AT91_REG	 LCDC_DP4_5; 	// Dithering Pattern DP4_5 Register
	AT91_REG	 LCDC_DP6_7; 	// Dithering Pattern DP6_7 Register
	AT91_REG	 LCDC_PWRCON; 	// Power Control Register
	AT91_REG	 LCDC_CTRSTCON; 	// Contrast Control Register
	AT91_REG	 LCDC_CTRSTVAL; 	// Contrast Value Register
	AT91_REG	 LCDC_IER; 	// Interrupt Enable Register
	AT91_REG	 LCDC_IDR; 	// Interrupt Disable Register
	AT91_REG	 LCDC_IMR; 	// Interrupt Mask Register
	AT91_REG	 LCDC_ISR; 	// Interrupt Enable Register
	AT91_REG	 LCDC_ICR; 	// Interrupt Clear Register
	AT91_REG	 LCDC_GPR; 	// General Purpose Register
	AT91_REG	 LCDC_ITR; 	// Interrupts Test Register
	AT91_REG	 LCDC_IRR; 	// Interrupts Raw Status Register
	AT91_REG	 Reserved1[230]; 	// 
	AT91_REG	 LCDC_LUT_ENTRY[256]; 	// LUT Entries Register
} AT91S_LCDC, *AT91PS_LCDC;

// -------- LCDC_FRMP1 : (LCDC Offset: 0x8) DMA Frame Pointer 1 Register -------- 
#define AT91C_LCDC_FRMPT1     ((unsigned int) 0x3FFFFF <<  0) // (LCDC) Frame Pointer Address 1
// -------- LCDC_FRMP2 : (LCDC Offset: 0xc) DMA Frame Pointer 2 Register -------- 
#define AT91C_LCDC_FRMPT2     ((unsigned int) 0x1FFFFF <<  0) // (LCDC) Frame Pointer Address 2
// -------- LCDC_FRMCFG : (LCDC Offset: 0x18) DMA Frame Config Register -------- 
#define AT91C_LCDC_FRSIZE     ((unsigned int) 0x3FFFFF <<  0) // (LCDC) FRAME SIZE
#define AT91C_LCDC_BLENGTH    ((unsigned int) 0xF << 24) // (LCDC) BURST LENGTH
// -------- LCDC_DMACON : (LCDC Offset: 0x1c) DMA Control Register -------- 
#define AT91C_LCDC_DMAEN      ((unsigned int) 0x1 <<  0) // (LCDC) DAM Enable
#define AT91C_LCDC_DMARST     ((unsigned int) 0x1 <<  1) // (LCDC) DMA Reset (WO)
#define AT91C_LCDC_DMABUSY    ((unsigned int) 0x1 <<  2) // (LCDC) DMA Reset (WO)
#define AT91C_LCDC_DMAUPDT    ((unsigned int) 0x1 <<  3) // (LCDC) DMA Configuration Update
#define AT91C_LCDC_DMA2DEN    ((unsigned int) 0x1 <<  4) // (LCDC) 2D Addressing Enable
// -------- LCDC_DMA2DCFG : (LCDC Offset: 0x20) DMA 2D addressing configuration Register -------- 
#define AT91C_LCDC_ADDRINC    ((unsigned int) 0xFFFF <<  0) // (LCDC) Number of 32b words that the DMA must jump when going to the next line
#define AT91C_LCDC_PIXELOFF   ((unsigned int) 0x1F << 24) // (LCDC) Offset (in bits) of the first pixel of the screen in the memory word which contain it
// -------- LCDC_LCDCON1 : (LCDC Offset: 0x800) LCD Control 1 Register -------- 
#define AT91C_LCDC_BYPASS     ((unsigned int) 0x1 <<  0) // (LCDC) Bypass lcd_pccklk divider
#define AT91C_LCDC_CLKVAL     ((unsigned int) 0x1FF << 12) // (LCDC) 9-bit Divider for pixel clock frequency
#define AT91C_LCDC_LINCNT     ((unsigned int) 0x7FF << 21) // (LCDC) Line Counter (RO)
// -------- LCDC_LCDCON2 : (LCDC Offset: 0x804) LCD Control 2 Register -------- 
#define AT91C_LCDC_DISTYPE    ((unsigned int) 0x3 <<  0) // (LCDC) Display Type
#define 	AT91C_LCDC_DISTYPE_STNMONO              ((unsigned int) 0x0) // (LCDC) STN Mono
#define 	AT91C_LCDC_DISTYPE_STNCOLOR             ((unsigned int) 0x1) // (LCDC) STN Color
#define 	AT91C_LCDC_DISTYPE_TFT                  ((unsigned int) 0x2) // (LCDC) TFT
#define AT91C_LCDC_SCANMOD    ((unsigned int) 0x1 <<  2) // (LCDC) Scan Mode
#define 	AT91C_LCDC_SCANMOD_SINGLESCAN           ((unsigned int) 0x0 <<  2) // (LCDC) Single Scan
#define 	AT91C_LCDC_SCANMOD_DUALSCAN             ((unsigned int) 0x1 <<  2) // (LCDC) Dual Scan
#define AT91C_LCDC_IFWIDTH    ((unsigned int) 0x3 <<  3) // (LCDC) Interface Width
#define 	AT91C_LCDC_IFWIDTH_FOURBITSWIDTH        ((unsigned int) 0x0 <<  3) // (LCDC) 4 Bits
#define 	AT91C_LCDC_IFWIDTH_EIGTHBITSWIDTH       ((unsigned int) 0x1 <<  3) // (LCDC) 8 Bits
#define 	AT91C_LCDC_IFWIDTH_SIXTEENBITSWIDTH     ((unsigned int) 0x2 <<  3) // (LCDC) 16 Bits
#define AT91C_LCDC_PIXELSIZE  ((unsigned int) 0x7 <<  5) // (LCDC) Bits per pixel
#define 	AT91C_LCDC_PIXELSIZE_ONEBITSPERPIXEL      ((unsigned int) 0x0 <<  5) // (LCDC) 1 Bits
#define 	AT91C_LCDC_PIXELSIZE_TWOBITSPERPIXEL      ((unsigned int) 0x1 <<  5) // (LCDC) 2 Bits
#define 	AT91C_LCDC_PIXELSIZE_FOURBITSPERPIXEL     ((unsigned int) 0x2 <<  5) // (LCDC) 4 Bits
#define 	AT91C_LCDC_PIXELSIZE_EIGTHBITSPERPIXEL    ((unsigned int) 0x3 <<  5) // (LCDC) 8 Bits
#define 	AT91C_LCDC_PIXELSIZE_SIXTEENBITSPERPIXEL  ((unsigned int) 0x4 <<  5) // (LCDC) 16 Bits
#define 	AT91C_LCDC_PIXELSIZE_TWENTYFOURBITSPERPIXEL ((unsigned int) 0x5 <<  5) // (LCDC) 24 Bits
#define AT91C_LCDC_INVVD      ((unsigned int) 0x1 <<  8) // (LCDC) lcd datas polarity
#define 	AT91C_LCDC_INVVD_NORMALPOL            ((unsigned int) 0x0 <<  8) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVVD_INVERTEDPOL          ((unsigned int) 0x1 <<  8) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVFRAME   ((unsigned int) 0x1 <<  9) // (LCDC) lcd vsync polarity
#define 	AT91C_LCDC_INVFRAME_NORMALPOL            ((unsigned int) 0x0 <<  9) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVFRAME_INVERTEDPOL          ((unsigned int) 0x1 <<  9) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVLINE    ((unsigned int) 0x1 << 10) // (LCDC) lcd hsync polarity
#define 	AT91C_LCDC_INVLINE_NORMALPOL            ((unsigned int) 0x0 << 10) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVLINE_INVERTEDPOL          ((unsigned int) 0x1 << 10) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVCLK     ((unsigned int) 0x1 << 11) // (LCDC) lcd pclk polarity
#define 	AT91C_LCDC_INVCLK_NORMALPOL            ((unsigned int) 0x0 << 11) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVCLK_INVERTEDPOL          ((unsigned int) 0x1 << 11) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVDVAL    ((unsigned int) 0x1 << 12) // (LCDC) lcd dval polarity
#define 	AT91C_LCDC_INVDVAL_NORMALPOL            ((unsigned int) 0x0 << 12) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVDVAL_INVERTEDPOL          ((unsigned int) 0x1 << 12) // (LCDC) Inverted Polarity
#define AT91C_LCDC_CLKMOD     ((unsigned int) 0x1 << 15) // (LCDC) lcd pclk Mode
#define 	AT91C_LCDC_CLKMOD_ACTIVEONLYDISP       ((unsigned int) 0x0 << 15) // (LCDC) Active during display period
#define 	AT91C_LCDC_CLKMOD_ALWAYSACTIVE         ((unsigned int) 0x1 << 15) // (LCDC) Always Active
#define AT91C_LCDC_MEMOR      ((unsigned int) 0x1 << 31) // (LCDC) lcd pclk Mode
#define 	AT91C_LCDC_MEMOR_BIGIND               ((unsigned int) 0x0 << 31) // (LCDC) Big Endian
#define 	AT91C_LCDC_MEMOR_LITTLEIND            ((unsigned int) 0x1 << 31) // (LCDC) Little Endian
// -------- LCDC_TIM1 : (LCDC Offset: 0x808) LCDC Timing Config 1 Register -------- 
#define AT91C_LCDC_VFP        ((unsigned int) 0xFF <<  0) // (LCDC) Vertical Front Porch
#define AT91C_LCDC_VBP        ((unsigned int) 0xFF <<  8) // (LCDC) Vertical Back Porch
#define AT91C_LCDC_VPW        ((unsigned int) 0x3F << 16) // (LCDC) Vertical Synchronization Pulse Width
#define AT91C_LCDC_VHDLY      ((unsigned int) 0xF << 24) // (LCDC) Vertical to Horizontal Delay
// -------- LCDC_TIM2 : (LCDC Offset: 0x80c) LCDC Timing Config 2 Register -------- 
#define AT91C_LCDC_HBP        ((unsigned int) 0xFF <<  0) // (LCDC) Horizontal Back Porch
#define AT91C_LCDC_HPW        ((unsigned int) 0x3F <<  8) // (LCDC) Horizontal Synchronization Pulse Width
#define AT91C_LCDC_HFP        ((unsigned int) 0x3FF << 22) // (LCDC) Horizontal Front Porch
// -------- LCDC_LCDFRCFG : (LCDC Offset: 0x810) LCD Frame Config Register -------- 
#define AT91C_LCDC_LINEVAL    ((unsigned int) 0x7FF <<  0) // (LCDC) Vertical Size of LCD Module
#define AT91C_LCDC_HOZVAL     ((unsigned int) 0x7FF << 21) // (LCDC) Horizontal Size of LCD Module
// -------- LCDC_FIFO : (LCDC Offset: 0x814) LCD FIFO Register -------- 
#define AT91C_LCDC_FIFOTH     ((unsigned int) 0xFFFF <<  0) // (LCDC) FIFO Threshold
// -------- LCDC_MVAL : (LCDC Offset: 0x818) LCD Mode Toggle Rate Value Register -------- 
#define AT91C_LCDC_MVALUE     ((unsigned int) 0xFF <<  0) // (LCDC) Toggle Rate Value
#define AT91C_LCDC_MMODE      ((unsigned int) 0x1 << 31) // (LCDC) Toggle Rate Sel
#define 	AT91C_LCDC_MMODE_EACHFRAME            ((unsigned int) 0x0 << 31) // (LCDC) Each Frame
#define 	AT91C_LCDC_MMODE_MVALDEFINED          ((unsigned int) 0x1 << 31) // (LCDC) Defined by MVAL
// -------- LCDC_DP1_2 : (LCDC Offset: 0x81c) Dithering Pattern 1/2 -------- 
#define AT91C_LCDC_DP1_2_FIELD ((unsigned int) 0xFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP4_7 : (LCDC Offset: 0x820) Dithering Pattern 4/7 -------- 
#define AT91C_LCDC_DP4_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP3_5 : (LCDC Offset: 0x824) Dithering Pattern 3/5 -------- 
#define AT91C_LCDC_DP3_5_FIELD ((unsigned int) 0xFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP2_3 : (LCDC Offset: 0x828) Dithering Pattern 2/3 -------- 
#define AT91C_LCDC_DP2_3_FIELD ((unsigned int) 0xFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP5_7 : (LCDC Offset: 0x82c) Dithering Pattern 5/7 -------- 
#define AT91C_LCDC_DP5_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP3_4 : (LCDC Offset: 0x830) Dithering Pattern 3/4 -------- 
#define AT91C_LCDC_DP3_4_FIELD ((unsigned int) 0xFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP4_5 : (LCDC Offset: 0x834) Dithering Pattern 4/5 -------- 
#define AT91C_LCDC_DP4_5_FIELD ((unsigned int) 0xFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP6_7 : (LCDC Offset: 0x838) Dithering Pattern 6/7 -------- 
#define AT91C_LCDC_DP6_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_PWRCON : (LCDC Offset: 0x83c) LCDC Power Control Register -------- 
#define AT91C_LCDC_PWR        ((unsigned int) 0x1 <<  0) // (LCDC) LCD Module Power Control
#define AT91C_LCDC_GUARDT     ((unsigned int) 0x7F <<  1) // (LCDC) Delay in Frame Period
#define AT91C_LCDC_BUSY       ((unsigned int) 0x1 << 31) // (LCDC) Read Only : 1 indicates that LCDC is busy
#define 	AT91C_LCDC_BUSY_LCDNOTBUSY           ((unsigned int) 0x0 << 31) // (LCDC) LCD is Not Busy
#define 	AT91C_LCDC_BUSY_LCDBUSY              ((unsigned int) 0x1 << 31) // (LCDC) LCD is Busy
// -------- LCDC_CTRSTCON : (LCDC Offset: 0x840) LCDC Contrast Control Register -------- 
#define AT91C_LCDC_PS         ((unsigned int) 0x3 <<  0) // (LCDC) LCD Contrast Counter Prescaler
#define 	AT91C_LCDC_PS_NOTDIVIDED           ((unsigned int) 0x0) // (LCDC) Counter Freq is System Freq.
#define 	AT91C_LCDC_PS_DIVIDEDBYTWO         ((unsigned int) 0x1) // (LCDC) Counter Freq is System Freq divided by 2.
#define 	AT91C_LCDC_PS_DIVIDEDBYFOUR        ((unsigned int) 0x2) // (LCDC) Counter Freq is System Freq divided by 4.
#define 	AT91C_LCDC_PS_DIVIDEDBYEIGHT       ((unsigned int) 0x3) // (LCDC) Counter Freq is System Freq divided by 8.
#define AT91C_LCDC_POL        ((unsigned int) 0x1 <<  2) // (LCDC) Polarity of output Pulse
#define 	AT91C_LCDC_POL_NEGATIVEPULSE        ((unsigned int) 0x0 <<  2) // (LCDC) Negative Pulse
#define 	AT91C_LCDC_POL_POSITIVEPULSE        ((unsigned int) 0x1 <<  2) // (LCDC) Positive Pulse
#define AT91C_LCDC_ENA        ((unsigned int) 0x1 <<  3) // (LCDC) PWM generator Control
#define 	AT91C_LCDC_ENA_PWMGEMDISABLED       ((unsigned int) 0x0 <<  3) // (LCDC) PWM Generator Disabled
#define 	AT91C_LCDC_ENA_PWMGEMENABLED        ((unsigned int) 0x1 <<  3) // (LCDC) PWM Generator Disabled
// -------- LCDC_CTRSTVAL : (LCDC Offset: 0x844) Contrast Value Register -------- 
#define AT91C_LCDC_CVAL       ((unsigned int) 0xFF <<  0) // (LCDC) PWM Compare Value
// -------- LCDC_IER : (LCDC Offset: 0x848) LCDC Interrupt Enable Register -------- 
#define AT91C_LCDC_LNI        ((unsigned int) 0x1 <<  0) // (LCDC) Line Interrupt
#define AT91C_LCDC_LSTLNI     ((unsigned int) 0x1 <<  1) // (LCDC) Last Line Interrupt
#define AT91C_LCDC_EOFI       ((unsigned int) 0x1 <<  2) // (LCDC) End Of Frame Interrupt
#define AT91C_LCDC_UFLWI      ((unsigned int) 0x1 <<  4) // (LCDC) FIFO Underflow Interrupt
#define AT91C_LCDC_OWRI       ((unsigned int) 0x1 <<  5) // (LCDC) Over Write Interrupt
#define AT91C_LCDC_MERI       ((unsigned int) 0x1 <<  6) // (LCDC) Memory Error  Interrupt
// -------- LCDC_IDR : (LCDC Offset: 0x84c) LCDC Interrupt Disable Register -------- 
// -------- LCDC_IMR : (LCDC Offset: 0x850) LCDC Interrupt Mask Register -------- 
// -------- LCDC_ISR : (LCDC Offset: 0x854) LCDC Interrupt Status Register -------- 
// -------- LCDC_ICR : (LCDC Offset: 0x858) LCDC Interrupt Clear Register -------- 
// -------- LCDC_GPR : (LCDC Offset: 0x85c) LCDC General Purpose Register -------- 
#define AT91C_LCDC_GPRBUS     ((unsigned int) 0xFF <<  0) // (LCDC) 8 bits available
// -------- LCDC_ITR : (LCDC Offset: 0x860) Interrupts Test Register -------- 
// -------- LCDC_IRR : (LCDC Offset: 0x864) Interrupts Raw Status Register -------- 

// *****************************************************************************
//               REGISTER ADDRESS DEFINITION FOR AT91SAM9261
// *****************************************************************************
// ========== Register definition for SYS peripheral ========== 
#define AT91C_SYS_GPBR1 ((AT91_REG *) 	0xFFFFFD54) // (SYS) General Purpose Register 1
#define AT91C_SYS_GPBR3 ((AT91_REG *) 	0xFFFFFD5C) // (SYS) General Purpose Register 3
#define AT91C_SYS_GPBR2 ((AT91_REG *) 	0xFFFFFD58) // (SYS) General Purpose Register 2
#define AT91C_SYS_GPBR0 ((AT91_REG *) 	0xFFFFFD50) // (SYS) General Purpose Register 0
// ========== Register definition for SDRAMC peripheral ========== 
#define AT91C_SDRAMC_MR ((AT91_REG *) 	0xFFFFEA00) // (SDRAMC) SDRAM Controller Mode Register
#define AT91C_SDRAMC_IMR ((AT91_REG *) 	0xFFFFEA1C) // (SDRAMC) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC_LPR ((AT91_REG *) 	0xFFFFEA10) // (SDRAMC) SDRAM Controller Low Power Register
#define AT91C_SDRAMC_ISR ((AT91_REG *) 	0xFFFFEA20) // (SDRAMC) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC_IDR ((AT91_REG *) 	0xFFFFEA18) // (SDRAMC) SDRAM Controller Interrupt Disable Register
#define AT91C_SDRAMC_CR ((AT91_REG *) 	0xFFFFEA08) // (SDRAMC) SDRAM Controller Configuration Register
#define AT91C_SDRAMC_TR ((AT91_REG *) 	0xFFFFEA04) // (SDRAMC) SDRAM Controller Refresh Timer Register
#define AT91C_SDRAMC_MDR ((AT91_REG *) 	0xFFFFEA24) // (SDRAMC) SDRAM Memory Device Register
#define AT91C_SDRAMC_HSR ((AT91_REG *) 	0xFFFFEA0C) // (SDRAMC) SDRAM Controller High Speed Register
#define AT91C_SDRAMC_IER ((AT91_REG *) 	0xFFFFEA14) // (SDRAMC) SDRAM Controller Interrupt Enable Register
// ========== Register definition for SMC peripheral ========== 
#define AT91C_SMC_CTRL1 ((AT91_REG *) 	0xFFFFEC1C) // (SMC)  Control Register for CS 1
#define AT91C_SMC_PULSE7 ((AT91_REG *) 	0xFFFFEC74) // (SMC)  Pulse Register for CS 7
#define AT91C_SMC_PULSE6 ((AT91_REG *) 	0xFFFFEC64) // (SMC)  Pulse Register for CS 6
#define AT91C_SMC_SETUP4 ((AT91_REG *) 	0xFFFFEC40) // (SMC)  Setup Register for CS 4
#define AT91C_SMC_PULSE3 ((AT91_REG *) 	0xFFFFEC34) // (SMC)  Pulse Register for CS 3
#define AT91C_SMC_CYCLE5 ((AT91_REG *) 	0xFFFFEC58) // (SMC)  Cycle Register for CS 5
#define AT91C_SMC_CYCLE2 ((AT91_REG *) 	0xFFFFEC28) // (SMC)  Cycle Register for CS 2
#define AT91C_SMC_CTRL2 ((AT91_REG *) 	0xFFFFEC2C) // (SMC)  Control Register for CS 2
#define AT91C_SMC_CTRL0 ((AT91_REG *) 	0xFFFFEC0C) // (SMC)  Control Register for CS 0
#define AT91C_SMC_PULSE5 ((AT91_REG *) 	0xFFFFEC54) // (SMC)  Pulse Register for CS 5
#define AT91C_SMC_PULSE1 ((AT91_REG *) 	0xFFFFEC14) // (SMC)  Pulse Register for CS 1
#define AT91C_SMC_PULSE0 ((AT91_REG *) 	0xFFFFEC04) // (SMC)  Pulse Register for CS 0
#define AT91C_SMC_CYCLE7 ((AT91_REG *) 	0xFFFFEC78) // (SMC)  Cycle Register for CS 7
#define AT91C_SMC_CTRL4 ((AT91_REG *) 	0xFFFFEC4C) // (SMC)  Control Register for CS 4
#define AT91C_SMC_CTRL3 ((AT91_REG *) 	0xFFFFEC3C) // (SMC)  Control Register for CS 3
#define AT91C_SMC_SETUP7 ((AT91_REG *) 	0xFFFFEC70) // (SMC)  Setup Register for CS 7
#define AT91C_SMC_CTRL7 ((AT91_REG *) 	0xFFFFEC7C) // (SMC)  Control Register for CS 7
#define AT91C_SMC_SETUP1 ((AT91_REG *) 	0xFFFFEC10) // (SMC)  Setup Register for CS 1
#define AT91C_SMC_CYCLE0 ((AT91_REG *) 	0xFFFFEC08) // (SMC)  Cycle Register for CS 0
#define AT91C_SMC_CTRL5 ((AT91_REG *) 	0xFFFFEC5C) // (SMC)  Control Register for CS 5
#define AT91C_SMC_CYCLE1 ((AT91_REG *) 	0xFFFFEC18) // (SMC)  Cycle Register for CS 1
#define AT91C_SMC_CTRL6 ((AT91_REG *) 	0xFFFFEC6C) // (SMC)  Control Register for CS 6
#define AT91C_SMC_SETUP0 ((AT91_REG *) 	0xFFFFEC00) // (SMC)  Setup Register for CS 0
#define AT91C_SMC_PULSE4 ((AT91_REG *) 	0xFFFFEC44) // (SMC)  Pulse Register for CS 4
#define AT91C_SMC_SETUP5 ((AT91_REG *) 	0xFFFFEC50) // (SMC)  Setup Register for CS 5
#define AT91C_SMC_SETUP2 ((AT91_REG *) 	0xFFFFEC20) // (SMC)  Setup Register for CS 2
#define AT91C_SMC_CYCLE3 ((AT91_REG *) 	0xFFFFEC38) // (SMC)  Cycle Register for CS 3
#define AT91C_SMC_CYCLE6 ((AT91_REG *) 	0xFFFFEC68) // (SMC)  Cycle Register for CS 6
#define AT91C_SMC_SETUP6 ((AT91_REG *) 	0xFFFFEC60) // (SMC)  Setup Register for CS 6
#define AT91C_SMC_CYCLE4 ((AT91_REG *) 	0xFFFFEC48) // (SMC)  Cycle Register for CS 4
#define AT91C_SMC_PULSE2 ((AT91_REG *) 	0xFFFFEC24) // (SMC)  Pulse Register for CS 2
#define AT91C_SMC_SETUP3 ((AT91_REG *) 	0xFFFFEC30) // (SMC)  Setup Register for CS 3
// ========== Register definition for MATRIX peripheral ========== 
#define AT91C_MATRIX_USBPCR ((AT91_REG *) 	0xFFFFEE34) // (MATRIX)  Slave 4 Special Function Register
#define AT91C_MATRIX_MCFG ((AT91_REG *) 	0xFFFFEE00) // (MATRIX)  Master Configuration Register
#define AT91C_MATRIX_EBICSA ((AT91_REG *) 	0xFFFFEE30) // (MATRIX)  Slave 3 Special Function Register
#define AT91C_MATRIX_SCFG2 ((AT91_REG *) 	0xFFFFEE0C) // (MATRIX)  Slave Configuration Register 2
#define AT91C_MATRIX_VERSION ((AT91_REG *) 	0xFFFFEE44) // (MATRIX)  Version Register
#define AT91C_MATRIX_SCFG3 ((AT91_REG *) 	0xFFFFEE10) // (MATRIX)  Slave Configuration Register 3
#define AT91C_MATRIX_TCMR ((AT91_REG *) 	0xFFFFEE24) // (MATRIX)  Slave 0 Special Function Register
#define AT91C_MATRIX_SCFG1 ((AT91_REG *) 	0xFFFFEE08) // (MATRIX)  Slave Configuration Register 1
#define AT91C_MATRIX_SCFG4 ((AT91_REG *) 	0xFFFFEE14) // (MATRIX)  Slave Configuration Register 4
#define AT91C_MATRIX_SCFG0 ((AT91_REG *) 	0xFFFFEE04) // (MATRIX)  Slave Configuration Register 0
// ========== Register definition for AIC peripheral ========== 
#define AT91C_AIC_IVR   ((AT91_REG *) 	0xFFFFF100) // (AIC) IRQ Vector Register
#define AT91C_AIC_SMR   ((AT91_REG *) 	0xFFFFF000) // (AIC) Source Mode Register
#define AT91C_AIC_FVR   ((AT91_REG *) 	0xFFFFF104) // (AIC) FIQ Vector Register
#define AT91C_AIC_DCR   ((AT91_REG *) 	0xFFFFF138) // (AIC) Debug Control Register (Protect)
#define AT91C_AIC_EOICR ((AT91_REG *) 	0xFFFFF130) // (AIC) End of Interrupt Command Register
#define AT91C_AIC_SVR   ((AT91_REG *) 	0xFFFFF080) // (AIC) Source Vector Register
#define AT91C_AIC_FFSR  ((AT91_REG *) 	0xFFFFF148) // (AIC) Fast Forcing Status Register
#define AT91C_AIC_ICCR  ((AT91_REG *) 	0xFFFFF128) // (AIC) Interrupt Clear Command Register
#define AT91C_AIC_ISR   ((AT91_REG *) 	0xFFFFF108) // (AIC) Interrupt Status Register
#define AT91C_AIC_IMR   ((AT91_REG *) 	0xFFFFF110) // (AIC) Interrupt Mask Register
#define AT91C_AIC_IPR   ((AT91_REG *) 	0xFFFFF10C) // (AIC) Interrupt Pending Register
#define AT91C_AIC_FFER  ((AT91_REG *) 	0xFFFFF140) // (AIC) Fast Forcing Enable Register
#define AT91C_AIC_IECR  ((AT91_REG *) 	0xFFFFF120) // (AIC) Interrupt Enable Command Register
#define AT91C_AIC_ISCR  ((AT91_REG *) 	0xFFFFF12C) // (AIC) Interrupt Set Command Register
#define AT91C_AIC_FFDR  ((AT91_REG *) 	0xFFFFF144) // (AIC) Fast Forcing Disable Register
#define AT91C_AIC_CISR  ((AT91_REG *) 	0xFFFFF114) // (AIC) Core Interrupt Status Register
#define AT91C_AIC_IDCR  ((AT91_REG *) 	0xFFFFF124) // (AIC) Interrupt Disable Command Register
#define AT91C_AIC_SPU   ((AT91_REG *) 	0xFFFFF134) // (AIC) Spurious Vector Register
// ========== Register definition for PDC_DBGU peripheral ========== 
#define AT91C_DBGU_TCR  ((AT91_REG *) 	0xFFFFF30C) // (PDC_DBGU) Transmit Counter Register
#define AT91C_DBGU_RNPR ((AT91_REG *) 	0xFFFFF310) // (PDC_DBGU) Receive Next Pointer Register
#define AT91C_DBGU_TNPR ((AT91_REG *) 	0xFFFFF318) // (PDC_DBGU) Transmit Next Pointer Register
#define AT91C_DBGU_TPR  ((AT91_REG *) 	0xFFFFF308) // (PDC_DBGU) Transmit Pointer Register
#define AT91C_DBGU_RPR  ((AT91_REG *) 	0xFFFFF300) // (PDC_DBGU) Receive Pointer Register
#define AT91C_DBGU_RCR  ((AT91_REG *) 	0xFFFFF304) // (PDC_DBGU) Receive Counter Register
#define AT91C_DBGU_RNCR ((AT91_REG *) 	0xFFFFF314) // (PDC_DBGU) Receive Next Counter Register
#define AT91C_DBGU_PTCR ((AT91_REG *) 	0xFFFFF320) // (PDC_DBGU) PDC Transfer Control Register
#define AT91C_DBGU_PTSR ((AT91_REG *) 	0xFFFFF324) // (PDC_DBGU) PDC Transfer Status Register
#define AT91C_DBGU_TNCR ((AT91_REG *) 	0xFFFFF31C) // (PDC_DBGU) Transmit Next Counter Register
// ========== Register definition for DBGU peripheral ========== 
#define AT91C_DBGU_EXID ((AT91_REG *) 	0xFFFFF244) // (DBGU) Chip ID Extension Register
#define AT91C_DBGU_BRGR ((AT91_REG *) 	0xFFFFF220) // (DBGU) Baud Rate Generator Register
#define AT91C_DBGU_IDR  ((AT91_REG *) 	0xFFFFF20C) // (DBGU) Interrupt Disable Register
#define AT91C_DBGU_CSR  ((AT91_REG *) 	0xFFFFF214) // (DBGU) Channel Status Register
#define AT91C_DBGU_CIDR ((AT91_REG *) 	0xFFFFF240) // (DBGU) Chip ID Register
#define AT91C_DBGU_MR   ((AT91_REG *) 	0xFFFFF204) // (DBGU) Mode Register
#define AT91C_DBGU_IMR  ((AT91_REG *) 	0xFFFFF210) // (DBGU) Interrupt Mask Register
#define AT91C_DBGU_CR   ((AT91_REG *) 	0xFFFFF200) // (DBGU) Control Register
#define AT91C_DBGU_FNTR ((AT91_REG *) 	0xFFFFF248) // (DBGU) Force NTRST Register
#define AT91C_DBGU_THR  ((AT91_REG *) 	0xFFFFF21C) // (DBGU) Transmitter Holding Register
#define AT91C_DBGU_RHR  ((AT91_REG *) 	0xFFFFF218) // (DBGU) Receiver Holding Register
#define AT91C_DBGU_IER  ((AT91_REG *) 	0xFFFFF208) // (DBGU) Interrupt Enable Register
// ========== Register definition for PIOA peripheral ========== 
#define AT91C_PIOA_ODR  ((AT91_REG *) 	0xFFFFF414) // (PIOA) Output Disable Registerr
#define AT91C_PIOA_SODR ((AT91_REG *) 	0xFFFFF430) // (PIOA) Set Output Data Register
#define AT91C_PIOA_ISR  ((AT91_REG *) 	0xFFFFF44C) // (PIOA) Interrupt Status Register
#define AT91C_PIOA_ABSR ((AT91_REG *) 	0xFFFFF478) // (PIOA) AB Select Status Register
#define AT91C_PIOA_IER  ((AT91_REG *) 	0xFFFFF440) // (PIOA) Interrupt Enable Register
#define AT91C_PIOA_PPUDR ((AT91_REG *) 	0xFFFFF460) // (PIOA) Pull-up Disable Register
#define AT91C_PIOA_IMR  ((AT91_REG *) 	0xFFFFF448) // (PIOA) Interrupt Mask Register
#define AT91C_PIOA_PER  ((AT91_REG *) 	0xFFFFF400) // (PIOA) PIO Enable Register
#define AT91C_PIOA_IFDR ((AT91_REG *) 	0xFFFFF424) // (PIOA) Input Filter Disable Register
#define AT91C_PIOA_OWDR ((AT91_REG *) 	0xFFFFF4A4) // (PIOA) Output Write Disable Register
#define AT91C_PIOA_MDSR ((AT91_REG *) 	0xFFFFF458) // (PIOA) Multi-driver Status Register
#define AT91C_PIOA_IDR  ((AT91_REG *) 	0xFFFFF444) // (PIOA) Interrupt Disable Register
#define AT91C_PIOA_ODSR ((AT91_REG *) 	0xFFFFF438) // (PIOA) Output Data Status Register
#define AT91C_PIOA_PPUSR ((AT91_REG *) 	0xFFFFF468) // (PIOA) Pull-up Status Register
#define AT91C_PIOA_OWSR ((AT91_REG *) 	0xFFFFF4A8) // (PIOA) Output Write Status Register
#define AT91C_PIOA_BSR  ((AT91_REG *) 	0xFFFFF474) // (PIOA) Select B Register
#define AT91C_PIOA_OWER ((AT91_REG *) 	0xFFFFF4A0) // (PIOA) Output Write Enable Register
#define AT91C_PIOA_IFER ((AT91_REG *) 	0xFFFFF420) // (PIOA) Input Filter Enable Register
#define AT91C_PIOA_PDSR ((AT91_REG *) 	0xFFFFF43C) // (PIOA) Pin Data Status Register
#define AT91C_PIOA_PPUER ((AT91_REG *) 	0xFFFFF464) // (PIOA) Pull-up Enable Register
#define AT91C_PIOA_OSR  ((AT91_REG *) 	0xFFFFF418) // (PIOA) Output Status Register
#define AT91C_PIOA_ASR  ((AT91_REG *) 	0xFFFFF470) // (PIOA) Select A Register
#define AT91C_PIOA_MDDR ((AT91_REG *) 	0xFFFFF454) // (PIOA) Multi-driver Disable Register
#define AT91C_PIOA_CODR ((AT91_REG *) 	0xFFFFF434) // (PIOA) Clear Output Data Register
#define AT91C_PIOA_MDER ((AT91_REG *) 	0xFFFFF450) // (PIOA) Multi-driver Enable Register
#define AT91C_PIOA_PDR  ((AT91_REG *) 	0xFFFFF404) // (PIOA) PIO Disable Register
#define AT91C_PIOA_IFSR ((AT91_REG *) 	0xFFFFF428) // (PIOA) Input Filter Status Register
#define AT91C_PIOA_OER  ((AT91_REG *) 	0xFFFFF410) // (PIOA) Output Enable Register
#define AT91C_PIOA_PSR  ((AT91_REG *) 	0xFFFFF408) // (PIOA) PIO Status Register
// ========== Register definition for PIOB peripheral ========== 
#define AT91C_PIOB_OWDR ((AT91_REG *) 	0xFFFFF6A4) // (PIOB) Output Write Disable Register
#define AT91C_PIOB_MDER ((AT91_REG *) 	0xFFFFF650) // (PIOB) Multi-driver Enable Register
#define AT91C_PIOB_PPUSR ((AT91_REG *) 	0xFFFFF668) // (PIOB) Pull-up Status Register
#define AT91C_PIOB_IMR  ((AT91_REG *) 	0xFFFFF648) // (PIOB) Interrupt Mask Register
#define AT91C_PIOB_ASR  ((AT91_REG *) 	0xFFFFF670) // (PIOB) Select A Register
#define AT91C_PIOB_PPUDR ((AT91_REG *) 	0xFFFFF660) // (PIOB) Pull-up Disable Register
#define AT91C_PIOB_PSR  ((AT91_REG *) 	0xFFFFF608) // (PIOB) PIO Status Register
#define AT91C_PIOB_IER  ((AT91_REG *) 	0xFFFFF640) // (PIOB) Interrupt Enable Register
#define AT91C_PIOB_CODR ((AT91_REG *) 	0xFFFFF634) // (PIOB) Clear Output Data Register
#define AT91C_PIOB_OWER ((AT91_REG *) 	0xFFFFF6A0) // (PIOB) Output Write Enable Register
#define AT91C_PIOB_ABSR ((AT91_REG *) 	0xFFFFF678) // (PIOB) AB Select Status Register
#define AT91C_PIOB_IFDR ((AT91_REG *) 	0xFFFFF624) // (PIOB) Input Filter Disable Register
#define AT91C_PIOB_PDSR ((AT91_REG *) 	0xFFFFF63C) // (PIOB) Pin Data Status Register
#define AT91C_PIOB_IDR  ((AT91_REG *) 	0xFFFFF644) // (PIOB) Interrupt Disable Register
#define AT91C_PIOB_OWSR ((AT91_REG *) 	0xFFFFF6A8) // (PIOB) Output Write Status Register
#define AT91C_PIOB_PDR  ((AT91_REG *) 	0xFFFFF604) // (PIOB) PIO Disable Register
#define AT91C_PIOB_ODR  ((AT91_REG *) 	0xFFFFF614) // (PIOB) Output Disable Registerr
#define AT91C_PIOB_IFSR ((AT91_REG *) 	0xFFFFF628) // (PIOB) Input Filter Status Register
#define AT91C_PIOB_PPUER ((AT91_REG *) 	0xFFFFF664) // (PIOB) Pull-up Enable Register
#define AT91C_PIOB_SODR ((AT91_REG *) 	0xFFFFF630) // (PIOB) Set Output Data Register
#define AT91C_PIOB_ISR  ((AT91_REG *) 	0xFFFFF64C) // (PIOB) Interrupt Status Register
#define AT91C_PIOB_ODSR ((AT91_REG *) 	0xFFFFF638) // (PIOB) Output Data Status Register
#define AT91C_PIOB_OSR  ((AT91_REG *) 	0xFFFFF618) // (PIOB) Output Status Register
#define AT91C_PIOB_MDSR ((AT91_REG *) 	0xFFFFF658) // (PIOB) Multi-driver Status Register
#define AT91C_PIOB_IFER ((AT91_REG *) 	0xFFFFF620) // (PIOB) Input Filter Enable Register
#define AT91C_PIOB_BSR  ((AT91_REG *) 	0xFFFFF674) // (PIOB) Select B Register
#define AT91C_PIOB_MDDR ((AT91_REG *) 	0xFFFFF654) // (PIOB) Multi-driver Disable Register
#define AT91C_PIOB_OER  ((AT91_REG *) 	0xFFFFF610) // (PIOB) Output Enable Register
#define AT91C_PIOB_PER  ((AT91_REG *) 	0xFFFFF600) // (PIOB) PIO Enable Register
// ========== Register definition for PIOC peripheral ========== 
#define AT91C_PIOC_OWDR ((AT91_REG *) 	0xFFFFF8A4) // (PIOC) Output Write Disable Register
#define AT91C_PIOC_SODR ((AT91_REG *) 	0xFFFFF830) // (PIOC) Set Output Data Register
#define AT91C_PIOC_PPUER ((AT91_REG *) 	0xFFFFF864) // (PIOC) Pull-up Enable Register
#define AT91C_PIOC_CODR ((AT91_REG *) 	0xFFFFF834) // (PIOC) Clear Output Data Register
#define AT91C_PIOC_PSR  ((AT91_REG *) 	0xFFFFF808) // (PIOC) PIO Status Register
#define AT91C_PIOC_PDR  ((AT91_REG *) 	0xFFFFF804) // (PIOC) PIO Disable Register
#define AT91C_PIOC_ODR  ((AT91_REG *) 	0xFFFFF814) // (PIOC) Output Disable Registerr
#define AT91C_PIOC_PPUSR ((AT91_REG *) 	0xFFFFF868) // (PIOC) Pull-up Status Register
#define AT91C_PIOC_ABSR ((AT91_REG *) 	0xFFFFF878) // (PIOC) AB Select Status Register
#define AT91C_PIOC_IFSR ((AT91_REG *) 	0xFFFFF828) // (PIOC) Input Filter Status Register
#define AT91C_PIOC_OER  ((AT91_REG *) 	0xFFFFF810) // (PIOC) Output Enable Register
#define AT91C_PIOC_IMR  ((AT91_REG *) 	0xFFFFF848) // (PIOC) Interrupt Mask Register
#define AT91C_PIOC_ASR  ((AT91_REG *) 	0xFFFFF870) // (PIOC) Select A Register
#define AT91C_PIOC_MDDR ((AT91_REG *) 	0xFFFFF854) // (PIOC) Multi-driver Disable Register
#define AT91C_PIOC_OWSR ((AT91_REG *) 	0xFFFFF8A8) // (PIOC) Output Write Status Register
#define AT91C_PIOC_PER  ((AT91_REG *) 	0xFFFFF800) // (PIOC) PIO Enable Register
#define AT91C_PIOC_IDR  ((AT91_REG *) 	0xFFFFF844) // (PIOC) Interrupt Disable Register
#define AT91C_PIOC_MDER ((AT91_REG *) 	0xFFFFF850) // (PIOC) Multi-driver Enable Register
#define AT91C_PIOC_PDSR ((AT91_REG *) 	0xFFFFF83C) // (PIOC) Pin Data Status Register
#define AT91C_PIOC_MDSR ((AT91_REG *) 	0xFFFFF858) // (PIOC) Multi-driver Status Register
#define AT91C_PIOC_OWER ((AT91_REG *) 	0xFFFFF8A0) // (PIOC) Output Write Enable Register
#define AT91C_PIOC_BSR  ((AT91_REG *) 	0xFFFFF874) // (PIOC) Select B Register
#define AT91C_PIOC_PPUDR ((AT91_REG *) 	0xFFFFF860) // (PIOC) Pull-up Disable Register
#define AT91C_PIOC_IFDR ((AT91_REG *) 	0xFFFFF824) // (PIOC) Input Filter Disable Register
#define AT91C_PIOC_IER  ((AT91_REG *) 	0xFFFFF840) // (PIOC) Interrupt Enable Register
#define AT91C_PIOC_OSR  ((AT91_REG *) 	0xFFFFF818) // (PIOC) Output Status Register
#define AT91C_PIOC_ODSR ((AT91_REG *) 	0xFFFFF838) // (PIOC) Output Data Status Register
#define AT91C_PIOC_ISR  ((AT91_REG *) 	0xFFFFF84C) // (PIOC) Interrupt Status Register
#define AT91C_PIOC_IFER ((AT91_REG *) 	0xFFFFF820) // (PIOC) Input Filter Enable Register
// ========== Register definition for CKGR peripheral ========== 
#define AT91C_CKGR_MOR  ((AT91_REG *) 	0xFFFFFC20) // (CKGR) Main Oscillator Register
#define AT91C_CKGR_PLLBR ((AT91_REG *) 	0xFFFFFC2C) // (CKGR) PLL B Register
#define AT91C_CKGR_MCFR ((AT91_REG *) 	0xFFFFFC24) // (CKGR) Main Clock  Frequency Register
#define AT91C_CKGR_PLLAR ((AT91_REG *) 	0xFFFFFC28) // (CKGR) PLL A Register
// ========== Register definition for PMC peripheral ========== 
#define AT91C_PMC_PCER  ((AT91_REG *) 	0xFFFFFC10) // (PMC) Peripheral Clock Enable Register
#define AT91C_PMC_PCKR  ((AT91_REG *) 	0xFFFFFC40) // (PMC) Programmable Clock Register
#define AT91C_PMC_MCKR  ((AT91_REG *) 	0xFFFFFC30) // (PMC) Master Clock Register
#define AT91C_PMC_PLLAR ((AT91_REG *) 	0xFFFFFC28) // (PMC) PLL A Register
#define AT91C_PMC_PCDR  ((AT91_REG *) 	0xFFFFFC14) // (PMC) Peripheral Clock Disable Register
#define AT91C_PMC_SCSR  ((AT91_REG *) 	0xFFFFFC08) // (PMC) System Clock Status Register
#define AT91C_PMC_MCFR  ((AT91_REG *) 	0xFFFFFC24) // (PMC) Main Clock  Frequency Register
#define AT91C_PMC_IMR   ((AT91_REG *) 	0xFFFFFC6C) // (PMC) Interrupt Mask Register
#define AT91C_PMC_IER   ((AT91_REG *) 	0xFFFFFC60) // (PMC) Interrupt Enable Register
#define AT91C_PMC_MOR   ((AT91_REG *) 	0xFFFFFC20) // (PMC) Main Oscillator Register
#define AT91C_PMC_IDR   ((AT91_REG *) 	0xFFFFFC64) // (PMC) Interrupt Disable Register
#define AT91C_PMC_PLLBR ((AT91_REG *) 	0xFFFFFC2C) // (PMC) PLL B Register
#define AT91C_PMC_SCDR  ((AT91_REG *) 	0xFFFFFC04) // (PMC) System Clock Disable Register
#define AT91C_PMC_PCSR  ((AT91_REG *) 	0xFFFFFC18) // (PMC) Peripheral Clock Status Register
#define AT91C_PMC_SCER  ((AT91_REG *) 	0xFFFFFC00) // (PMC) System Clock Enable Register
#define AT91C_PMC_SR    ((AT91_REG *) 	0xFFFFFC68) // (PMC) Status Register
// ========== Register definition for RSTC peripheral ========== 
#define AT91C_RSTC_RCR  ((AT91_REG *) 	0xFFFFFD00) // (RSTC) Reset Control Register
#define AT91C_RSTC_RMR  ((AT91_REG *) 	0xFFFFFD08) // (RSTC) Reset Mode Register
#define AT91C_RSTC_RSR  ((AT91_REG *) 	0xFFFFFD04) // (RSTC) Reset Status Register
// ========== Register definition for SHDWC peripheral ========== 
#define AT91C_SHDWC_SHSR ((AT91_REG *) 	0xFFFFFD18) // (SHDWC) Shut Down Status Register
#define AT91C_SHDWC_SHMR ((AT91_REG *) 	0xFFFFFD14) // (SHDWC) Shut Down Mode Register
#define AT91C_SHDWC_SHCR ((AT91_REG *) 	0xFFFFFD10) // (SHDWC) Shut Down Control Register
// ========== Register definition for RTTC peripheral ========== 
#define AT91C_RTTC_RTSR ((AT91_REG *) 	0xFFFFFD2C) // (RTTC) Real-time Status Register
#define AT91C_RTTC_RTMR ((AT91_REG *) 	0xFFFFFD20) // (RTTC) Real-time Mode Register
#define AT91C_RTTC_RTVR ((AT91_REG *) 	0xFFFFFD28) // (RTTC) Real-time Value Register
#define AT91C_RTTC_RTAR ((AT91_REG *) 	0xFFFFFD24) // (RTTC) Real-time Alarm Register
// ========== Register definition for PITC peripheral ========== 
#define AT91C_PITC_PIVR ((AT91_REG *) 	0xFFFFFD38) // (PITC) Period Interval Value Register
#define AT91C_PITC_PISR ((AT91_REG *) 	0xFFFFFD34) // (PITC) Period Interval Status Register
#define AT91C_PITC_PIIR ((AT91_REG *) 	0xFFFFFD3C) // (PITC) Period Interval Image Register
#define AT91C_PITC_PIMR ((AT91_REG *) 	0xFFFFFD30) // (PITC) Period Interval Mode Register
// ========== Register definition for WDTC peripheral ========== 
#define AT91C_WDTC_WDCR ((AT91_REG *) 	0xFFFFFD40) // (WDTC) Watchdog Control Register
#define AT91C_WDTC_WDSR ((AT91_REG *) 	0xFFFFFD48) // (WDTC) Watchdog Status Register
#define AT91C_WDTC_WDMR ((AT91_REG *) 	0xFFFFFD44) // (WDTC) Watchdog Mode Register
// ========== Register definition for TC0 peripheral ========== 
#define AT91C_TC0_SR    ((AT91_REG *) 	0xFFFA0020) // (TC0) Status Register
#define AT91C_TC0_RC    ((AT91_REG *) 	0xFFFA001C) // (TC0) Register C
#define AT91C_TC0_RB    ((AT91_REG *) 	0xFFFA0018) // (TC0) Register B
#define AT91C_TC0_CCR   ((AT91_REG *) 	0xFFFA0000) // (TC0) Channel Control Register
#define AT91C_TC0_CMR   ((AT91_REG *) 	0xFFFA0004) // (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC0_IER   ((AT91_REG *) 	0xFFFA0024) // (TC0) Interrupt Enable Register
#define AT91C_TC0_RA    ((AT91_REG *) 	0xFFFA0014) // (TC0) Register A
#define AT91C_TC0_IDR   ((AT91_REG *) 	0xFFFA0028) // (TC0) Interrupt Disable Register
#define AT91C_TC0_CV    ((AT91_REG *) 	0xFFFA0010) // (TC0) Counter Value
#define AT91C_TC0_IMR   ((AT91_REG *) 	0xFFFA002C) // (TC0) Interrupt Mask Register
// ========== Register definition for TC1 peripheral ========== 
#define AT91C_TC1_RB    ((AT91_REG *) 	0xFFFA0058) // (TC1) Register B
#define AT91C_TC1_CCR   ((AT91_REG *) 	0xFFFA0040) // (TC1) Channel Control Register
#define AT91C_TC1_IER   ((AT91_REG *) 	0xFFFA0064) // (TC1) Interrupt Enable Register
#define AT91C_TC1_IDR   ((AT91_REG *) 	0xFFFA0068) // (TC1) Interrupt Disable Register
#define AT91C_TC1_SR    ((AT91_REG *) 	0xFFFA0060) // (TC1) Status Register
#define AT91C_TC1_CMR   ((AT91_REG *) 	0xFFFA0044) // (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC1_RA    ((AT91_REG *) 	0xFFFA0054) // (TC1) Register A
#define AT91C_TC1_RC    ((AT91_REG *) 	0xFFFA005C) // (TC1) Register C
#define AT91C_TC1_IMR   ((AT91_REG *) 	0xFFFA006C) // (TC1) Interrupt Mask Register
#define AT91C_TC1_CV    ((AT91_REG *) 	0xFFFA0050) // (TC1) Counter Value
// ========== Register definition for TC2 peripheral ========== 
#define AT91C_TC2_CMR   ((AT91_REG *) 	0xFFFA0084) // (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC2_CCR   ((AT91_REG *) 	0xFFFA0080) // (TC2) Channel Control Register
#define AT91C_TC2_CV    ((AT91_REG *) 	0xFFFA0090) // (TC2) Counter Value
#define AT91C_TC2_RA    ((AT91_REG *) 	0xFFFA0094) // (TC2) Register A
#define AT91C_TC2_RB    ((AT91_REG *) 	0xFFFA0098) // (TC2) Register B
#define AT91C_TC2_IDR   ((AT91_REG *) 	0xFFFA00A8) // (TC2) Interrupt Disable Register
#define AT91C_TC2_IMR   ((AT91_REG *) 	0xFFFA00AC) // (TC2) Interrupt Mask Register
#define AT91C_TC2_RC    ((AT91_REG *) 	0xFFFA009C) // (TC2) Register C
#define AT91C_TC2_IER   ((AT91_REG *) 	0xFFFA00A4) // (TC2) Interrupt Enable Register
#define AT91C_TC2_SR    ((AT91_REG *) 	0xFFFA00A0) // (TC2) Status Register
// ========== Register definition for TCB0 peripheral ========== 
#define AT91C_TCB0_BMR  ((AT91_REG *) 	0xFFFA00C4) // (TCB0) TC Block Mode Register
#define AT91C_TCB0_BCR  ((AT91_REG *) 	0xFFFA00C0) // (TCB0) TC Block Control Register
// ========== Register definition for UDP peripheral ========== 
#define AT91C_UDP_GLBSTATE ((AT91_REG *) 	0xFFFA4004) // (UDP) Global State Register
#define AT91C_UDP_FDR   ((AT91_REG *) 	0xFFFA4050) // (UDP) Endpoint FIFO Data Register
#define AT91C_UDP_RSTEP ((AT91_REG *) 	0xFFFA4028) // (UDP) Reset Endpoint Register
#define AT91C_UDP_FADDR ((AT91_REG *) 	0xFFFA4008) // (UDP) Function Address Register
#define AT91C_UDP_NUM   ((AT91_REG *) 	0xFFFA4000) // (UDP) Frame Number Register
#define AT91C_UDP_IDR   ((AT91_REG *) 	0xFFFA4014) // (UDP) Interrupt Disable Register
#define AT91C_UDP_IMR   ((AT91_REG *) 	0xFFFA4018) // (UDP) Interrupt Mask Register
#define AT91C_UDP_CSR   ((AT91_REG *) 	0xFFFA4030) // (UDP) Endpoint Control and Status Register
#define AT91C_UDP_IER   ((AT91_REG *) 	0xFFFA4010) // (UDP) Interrupt Enable Register
#define AT91C_UDP_ICR   ((AT91_REG *) 	0xFFFA4020) // (UDP) Interrupt Clear Register
#define AT91C_UDP_TXVC  ((AT91_REG *) 	0xFFFA4074) // (UDP) Transceiver Control Register
#define AT91C_UDP_ISR   ((AT91_REG *) 	0xFFFA401C) // (UDP) Interrupt Status Register
// ========== Register definition for PDC_MCI peripheral ========== 
#define AT91C_MCI_RNCR  ((AT91_REG *) 	0xFFFA8114) // (PDC_MCI) Receive Next Counter Register
#define AT91C_MCI_TCR   ((AT91_REG *) 	0xFFFA810C) // (PDC_MCI) Transmit Counter Register
#define AT91C_MCI_RCR   ((AT91_REG *) 	0xFFFA8104) // (PDC_MCI) Receive Counter Register
#define AT91C_MCI_TNPR  ((AT91_REG *) 	0xFFFA8118) // (PDC_MCI) Transmit Next Pointer Register
#define AT91C_MCI_RNPR  ((AT91_REG *) 	0xFFFA8110) // (PDC_MCI) Receive Next Pointer Register
#define AT91C_MCI_RPR   ((AT91_REG *) 	0xFFFA8100) // (PDC_MCI) Receive Pointer Register
#define AT91C_MCI_TNCR  ((AT91_REG *) 	0xFFFA811C) // (PDC_MCI) Transmit Next Counter Register
#define AT91C_MCI_TPR   ((AT91_REG *) 	0xFFFA8108) // (PDC_MCI) Transmit Pointer Register
#define AT91C_MCI_PTSR  ((AT91_REG *) 	0xFFFA8124) // (PDC_MCI) PDC Transfer Status Register
#define AT91C_MCI_PTCR  ((AT91_REG *) 	0xFFFA8120) // (PDC_MCI) PDC Transfer Control Register
// ========== Register definition for MCI peripheral ========== 
#define AT91C_MCI_RDR   ((AT91_REG *) 	0xFFFA8030) // (MCI) MCI Receive Data Register
#define AT91C_MCI_CMDR  ((AT91_REG *) 	0xFFFA8014) // (MCI) MCI Command Register
#define AT91C_MCI_IDR   ((AT91_REG *) 	0xFFFA8048) // (MCI) MCI Interrupt Disable Register
#define AT91C_MCI_DTOR  ((AT91_REG *) 	0xFFFA8008) // (MCI) MCI Data Timeout Register
#define AT91C_MCI_TDR   ((AT91_REG *) 	0xFFFA8034) // (MCI) MCI Transmit Data Register
#define AT91C_MCI_IER   ((AT91_REG *) 	0xFFFA8044) // (MCI) MCI Interrupt Enable Register
#define AT91C_MCI_MR    ((AT91_REG *) 	0xFFFA8004) // (MCI) MCI Mode Register
#define AT91C_MCI_IMR   ((AT91_REG *) 	0xFFFA804C) // (MCI) MCI Interrupt Mask Register
#define AT91C_MCI_CR    ((AT91_REG *) 	0xFFFA8000) // (MCI) MCI Control Register
#define AT91C_MCI_ARGR  ((AT91_REG *) 	0xFFFA8010) // (MCI) MCI Argument Register
#define AT91C_MCI_SDCR  ((AT91_REG *) 	0xFFFA800C) // (MCI) MCI SD Card Register
#define AT91C_MCI_SR    ((AT91_REG *) 	0xFFFA8040) // (MCI) MCI Status Register
#define AT91C_MCI_RSPR  ((AT91_REG *) 	0xFFFA8020) // (MCI) MCI Response Register
// ========== Register definition for TWI peripheral ========== 
#define AT91C_TWI_THR   ((AT91_REG *) 	0xFFFAC034) // (TWI) Transmit Holding Register
#define AT91C_TWI_IDR   ((AT91_REG *) 	0xFFFAC028) // (TWI) Interrupt Disable Register
#define AT91C_TWI_CWGR  ((AT91_REG *) 	0xFFFAC010) // (TWI) Clock Waveform Generator Register
#define AT91C_TWI_IADR  ((AT91_REG *) 	0xFFFAC00C) // (TWI) Internal Address Register
#define AT91C_TWI_RHR   ((AT91_REG *) 	0xFFFAC030) // (TWI) Receive Holding Register
#define AT91C_TWI_IER   ((AT91_REG *) 	0xFFFAC024) // (TWI) Interrupt Enable Register
#define AT91C_TWI_MMR   ((AT91_REG *) 	0xFFFAC004) // (TWI) Master Mode Register
#define AT91C_TWI_SR    ((AT91_REG *) 	0xFFFAC020) // (TWI) Status Register
#define AT91C_TWI_CR    ((AT91_REG *) 	0xFFFAC000) // (TWI) Control Register
#define AT91C_TWI_IMR   ((AT91_REG *) 	0xFFFAC02C) // (TWI) Interrupt Mask Register
// ========== Register definition for PDC_US0 peripheral ========== 
#define AT91C_US0_TCR   ((AT91_REG *) 	0xFFFB010C) // (PDC_US0) Transmit Counter Register
#define AT91C_US0_PTCR  ((AT91_REG *) 	0xFFFB0120) // (PDC_US0) PDC Transfer Control Register
#define AT91C_US0_RNCR  ((AT91_REG *) 	0xFFFB0114) // (PDC_US0) Receive Next Counter Register
#define AT91C_US0_PTSR  ((AT91_REG *) 	0xFFFB0124) // (PDC_US0) PDC Transfer Status Register
#define AT91C_US0_TNCR  ((AT91_REG *) 	0xFFFB011C) // (PDC_US0) Transmit Next Counter Register
#define AT91C_US0_RNPR  ((AT91_REG *) 	0xFFFB0110) // (PDC_US0) Receive Next Pointer Register
#define AT91C_US0_RCR   ((AT91_REG *) 	0xFFFB0104) // (PDC_US0) Receive Counter Register
#define AT91C_US0_TPR   ((AT91_REG *) 	0xFFFB0108) // (PDC_US0) Transmit Pointer Register
#define AT91C_US0_TNPR  ((AT91_REG *) 	0xFFFB0118) // (PDC_US0) Transmit Next Pointer Register
#define AT91C_US0_RPR   ((AT91_REG *) 	0xFFFB0100) // (PDC_US0) Receive Pointer Register
// ========== Register definition for US0 peripheral ========== 
#define AT91C_US0_RHR   ((AT91_REG *) 	0xFFFB0018) // (US0) Receiver Holding Register
#define AT91C_US0_NER   ((AT91_REG *) 	0xFFFB0044) // (US0) Nb Errors Register
#define AT91C_US0_IER   ((AT91_REG *) 	0xFFFB0008) // (US0) Interrupt Enable Register
#define AT91C_US0_CR    ((AT91_REG *) 	0xFFFB0000) // (US0) Control Register
#define AT91C_US0_THR   ((AT91_REG *) 	0xFFFB001C) // (US0) Transmitter Holding Register
#define AT91C_US0_CSR   ((AT91_REG *) 	0xFFFB0014) // (US0) Channel Status Register
#define AT91C_US0_BRGR  ((AT91_REG *) 	0xFFFB0020) // (US0) Baud Rate Generator Register
#define AT91C_US0_RTOR  ((AT91_REG *) 	0xFFFB0024) // (US0) Receiver Time-out Register
#define AT91C_US0_TTGR  ((AT91_REG *) 	0xFFFB0028) // (US0) Transmitter Time-guard Register
#define AT91C_US0_IDR   ((AT91_REG *) 	0xFFFB000C) // (US0) Interrupt Disable Register
#define AT91C_US0_MR    ((AT91_REG *) 	0xFFFB0004) // (US0) Mode Register
#define AT91C_US0_IF    ((AT91_REG *) 	0xFFFB004C) // (US0) IRDA_FILTER Register
#define AT91C_US0_FIDI  ((AT91_REG *) 	0xFFFB0040) // (US0) FI_DI_Ratio Register
#define AT91C_US0_IMR   ((AT91_REG *) 	0xFFFB0010) // (US0) Interrupt Mask Register
// ========== Register definition for PDC_US1 peripheral ========== 
#define AT91C_US1_PTCR  ((AT91_REG *) 	0xFFFB4120) // (PDC_US1) PDC Transfer Control Register
#define AT91C_US1_RCR   ((AT91_REG *) 	0xFFFB4104) // (PDC_US1) Receive Counter Register
#define AT91C_US1_RPR   ((AT91_REG *) 	0xFFFB4100) // (PDC_US1) Receive Pointer Register
#define AT91C_US1_PTSR  ((AT91_REG *) 	0xFFFB4124) // (PDC_US1) PDC Transfer Status Register
#define AT91C_US1_TPR   ((AT91_REG *) 	0xFFFB4108) // (PDC_US1) Transmit Pointer Register
#define AT91C_US1_TCR   ((AT91_REG *) 	0xFFFB410C) // (PDC_US1) Transmit Counter Register
#define AT91C_US1_RNPR  ((AT91_REG *) 	0xFFFB4110) // (PDC_US1) Receive Next Pointer Register
#define AT91C_US1_TNCR  ((AT91_REG *) 	0xFFFB411C) // (PDC_US1) Transmit Next Counter Register
#define AT91C_US1_RNCR  ((AT91_REG *) 	0xFFFB4114) // (PDC_US1) Receive Next Counter Register
#define AT91C_US1_TNPR  ((AT91_REG *) 	0xFFFB4118) // (PDC_US1) Transmit Next Pointer Register
// ========== Register definition for US1 peripheral ========== 
#define AT91C_US1_THR   ((AT91_REG *) 	0xFFFB401C) // (US1) Transmitter Holding Register
#define AT91C_US1_TTGR  ((AT91_REG *) 	0xFFFB4028) // (US1) Transmitter Time-guard Register
#define AT91C_US1_BRGR  ((AT91_REG *) 	0xFFFB4020) // (US1) Baud Rate Generator Register
#define AT91C_US1_IDR   ((AT91_REG *) 	0xFFFB400C) // (US1) Interrupt Disable Register
#define AT91C_US1_MR    ((AT91_REG *) 	0xFFFB4004) // (US1) Mode Register
#define AT91C_US1_RTOR  ((AT91_REG *) 	0xFFFB4024) // (US1) Receiver Time-out Register
#define AT91C_US1_CR    ((AT91_REG *) 	0xFFFB4000) // (US1) Control Register
#define AT91C_US1_IMR   ((AT91_REG *) 	0xFFFB4010) // (US1) Interrupt Mask Register
#define AT91C_US1_FIDI  ((AT91_REG *) 	0xFFFB4040) // (US1) FI_DI_Ratio Register
#define AT91C_US1_RHR   ((AT91_REG *) 	0xFFFB4018) // (US1) Receiver Holding Register
#define AT91C_US1_IER   ((AT91_REG *) 	0xFFFB4008) // (US1) Interrupt Enable Register
#define AT91C_US1_CSR   ((AT91_REG *) 	0xFFFB4014) // (US1) Channel Status Register
#define AT91C_US1_IF    ((AT91_REG *) 	0xFFFB404C) // (US1) IRDA_FILTER Register
#define AT91C_US1_NER   ((AT91_REG *) 	0xFFFB4044) // (US1) Nb Errors Register
// ========== Register definition for PDC_US2 peripheral ========== 
#define AT91C_US2_TNCR  ((AT91_REG *) 	0xFFFB811C) // (PDC_US2) Transmit Next Counter Register
#define AT91C_US2_RNCR  ((AT91_REG *) 	0xFFFB8114) // (PDC_US2) Receive Next Counter Register
#define AT91C_US2_TNPR  ((AT91_REG *) 	0xFFFB8118) // (PDC_US2) Transmit Next Pointer Register
#define AT91C_US2_PTCR  ((AT91_REG *) 	0xFFFB8120) // (PDC_US2) PDC Transfer Control Register
#define AT91C_US2_TCR   ((AT91_REG *) 	0xFFFB810C) // (PDC_US2) Transmit Counter Register
#define AT91C_US2_RPR   ((AT91_REG *) 	0xFFFB8100) // (PDC_US2) Receive Pointer Register
#define AT91C_US2_TPR   ((AT91_REG *) 	0xFFFB8108) // (PDC_US2) Transmit Pointer Register
#define AT91C_US2_RCR   ((AT91_REG *) 	0xFFFB8104) // (PDC_US2) Receive Counter Register
#define AT91C_US2_PTSR  ((AT91_REG *) 	0xFFFB8124) // (PDC_US2) PDC Transfer Status Register
#define AT91C_US2_RNPR  ((AT91_REG *) 	0xFFFB8110) // (PDC_US2) Receive Next Pointer Register
// ========== Register definition for US2 peripheral ========== 
#define AT91C_US2_RTOR  ((AT91_REG *) 	0xFFFB8024) // (US2) Receiver Time-out Register
#define AT91C_US2_CSR   ((AT91_REG *) 	0xFFFB8014) // (US2) Channel Status Register
#define AT91C_US2_CR    ((AT91_REG *) 	0xFFFB8000) // (US2) Control Register
#define AT91C_US2_BRGR  ((AT91_REG *) 	0xFFFB8020) // (US2) Baud Rate Generator Register
#define AT91C_US2_NER   ((AT91_REG *) 	0xFFFB8044) // (US2) Nb Errors Register
#define AT91C_US2_FIDI  ((AT91_REG *) 	0xFFFB8040) // (US2) FI_DI_Ratio Register
#define AT91C_US2_TTGR  ((AT91_REG *) 	0xFFFB8028) // (US2) Transmitter Time-guard Register
#define AT91C_US2_RHR   ((AT91_REG *) 	0xFFFB8018) // (US2) Receiver Holding Register
#define AT91C_US2_IDR   ((AT91_REG *) 	0xFFFB800C) // (US2) Interrupt Disable Register
#define AT91C_US2_THR   ((AT91_REG *) 	0xFFFB801C) // (US2) Transmitter Holding Register
#define AT91C_US2_MR    ((AT91_REG *) 	0xFFFB8004) // (US2) Mode Register
#define AT91C_US2_IMR   ((AT91_REG *) 	0xFFFB8010) // (US2) Interrupt Mask Register
#define AT91C_US2_IF    ((AT91_REG *) 	0xFFFB804C) // (US2) IRDA_FILTER Register
#define AT91C_US2_IER   ((AT91_REG *) 	0xFFFB8008) // (US2) Interrupt Enable Register
// ========== Register definition for PDC_SSC0 peripheral ========== 
#define AT91C_SSC0_TNPR ((AT91_REG *) 	0xFFFBC118) // (PDC_SSC0) Transmit Next Pointer Register
#define AT91C_SSC0_TCR  ((AT91_REG *) 	0xFFFBC10C) // (PDC_SSC0) Transmit Counter Register
#define AT91C_SSC0_RNCR ((AT91_REG *) 	0xFFFBC114) // (PDC_SSC0) Receive Next Counter Register
#define AT91C_SSC0_RPR  ((AT91_REG *) 	0xFFFBC100) // (PDC_SSC0) Receive Pointer Register
#define AT91C_SSC0_TPR  ((AT91_REG *) 	0xFFFBC108) // (PDC_SSC0) Transmit Pointer Register
#define AT91C_SSC0_RCR  ((AT91_REG *) 	0xFFFBC104) // (PDC_SSC0) Receive Counter Register
#define AT91C_SSC0_RNPR ((AT91_REG *) 	0xFFFBC110) // (PDC_SSC0) Receive Next Pointer Register
#define AT91C_SSC0_PTCR ((AT91_REG *) 	0xFFFBC120) // (PDC_SSC0) PDC Transfer Control Register
#define AT91C_SSC0_TNCR ((AT91_REG *) 	0xFFFBC11C) // (PDC_SSC0) Transmit Next Counter Register
#define AT91C_SSC0_PTSR ((AT91_REG *) 	0xFFFBC124) // (PDC_SSC0) PDC Transfer Status Register
// ========== Register definition for SSC0 peripheral ========== 
#define AT91C_SSC0_IMR  ((AT91_REG *) 	0xFFFBC04C) // (SSC0) Interrupt Mask Register
#define AT91C_SSC0_RFMR ((AT91_REG *) 	0xFFFBC014) // (SSC0) Receive Frame Mode Register
#define AT91C_SSC0_CR   ((AT91_REG *) 	0xFFFBC000) // (SSC0) Control Register
#define AT91C_SSC0_TFMR ((AT91_REG *) 	0xFFFBC01C) // (SSC0) Transmit Frame Mode Register
#define AT91C_SSC0_CMR  ((AT91_REG *) 	0xFFFBC004) // (SSC0) Clock Mode Register
#define AT91C_SSC0_IER  ((AT91_REG *) 	0xFFFBC044) // (SSC0) Interrupt Enable Register
#define AT91C_SSC0_RHR  ((AT91_REG *) 	0xFFFBC020) // (SSC0) Receive Holding Register
#define AT91C_SSC0_RCMR ((AT91_REG *) 	0xFFFBC010) // (SSC0) Receive Clock ModeRegister
#define AT91C_SSC0_SR   ((AT91_REG *) 	0xFFFBC040) // (SSC0) Status Register
#define AT91C_SSC0_RSHR ((AT91_REG *) 	0xFFFBC030) // (SSC0) Receive Sync Holding Register
#define AT91C_SSC0_THR  ((AT91_REG *) 	0xFFFBC024) // (SSC0) Transmit Holding Register
#define AT91C_SSC0_TCMR ((AT91_REG *) 	0xFFFBC018) // (SSC0) Transmit Clock Mode Register
#define AT91C_SSC0_IDR  ((AT91_REG *) 	0xFFFBC048) // (SSC0) Interrupt Disable Register
#define AT91C_SSC0_TSHR ((AT91_REG *) 	0xFFFBC034) // (SSC0) Transmit Sync Holding Register
// ========== Register definition for PDC_SSC1 peripheral ========== 
#define AT91C_SSC1_TNPR ((AT91_REG *) 	0xFFFC0118) // (PDC_SSC1) Transmit Next Pointer Register
#define AT91C_SSC1_RNPR ((AT91_REG *) 	0xFFFC0110) // (PDC_SSC1) Receive Next Pointer Register
#define AT91C_SSC1_TCR  ((AT91_REG *) 	0xFFFC010C) // (PDC_SSC1) Transmit Counter Register
#define AT91C_SSC1_PTCR ((AT91_REG *) 	0xFFFC0120) // (PDC_SSC1) PDC Transfer Control Register
#define AT91C_SSC1_PTSR ((AT91_REG *) 	0xFFFC0124) // (PDC_SSC1) PDC Transfer Status Register
#define AT91C_SSC1_TNCR ((AT91_REG *) 	0xFFFC011C) // (PDC_SSC1) Transmit Next Counter Register
#define AT91C_SSC1_TPR  ((AT91_REG *) 	0xFFFC0108) // (PDC_SSC1) Transmit Pointer Register
#define AT91C_SSC1_RCR  ((AT91_REG *) 	0xFFFC0104) // (PDC_SSC1) Receive Counter Register
#define AT91C_SSC1_RPR  ((AT91_REG *) 	0xFFFC0100) // (PDC_SSC1) Receive Pointer Register
#define AT91C_SSC1_RNCR ((AT91_REG *) 	0xFFFC0114) // (PDC_SSC1) Receive Next Counter Register
// ========== Register definition for SSC1 peripheral ========== 
#define AT91C_SSC1_IDR  ((AT91_REG *) 	0xFFFC0048) // (SSC1) Interrupt Disable Register
#define AT91C_SSC1_RHR  ((AT91_REG *) 	0xFFFC0020) // (SSC1) Receive Holding Register
#define AT91C_SSC1_IER  ((AT91_REG *) 	0xFFFC0044) // (SSC1) Interrupt Enable Register
#define AT91C_SSC1_CR   ((AT91_REG *) 	0xFFFC0000) // (SSC1) Control Register
#define AT91C_SSC1_RCMR ((AT91_REG *) 	0xFFFC0010) // (SSC1) Receive Clock ModeRegister
#define AT91C_SSC1_SR   ((AT91_REG *) 	0xFFFC0040) // (SSC1) Status Register
#define AT91C_SSC1_TSHR ((AT91_REG *) 	0xFFFC0034) // (SSC1) Transmit Sync Holding Register
#define AT91C_SSC1_CMR  ((AT91_REG *) 	0xFFFC0004) // (SSC1) Clock Mode Register
#define AT91C_SSC1_RSHR ((AT91_REG *) 	0xFFFC0030) // (SSC1) Receive Sync Holding Register
#define AT91C_SSC1_THR  ((AT91_REG *) 	0xFFFC0024) // (SSC1) Transmit Holding Register
#define AT91C_SSC1_RFMR ((AT91_REG *) 	0xFFFC0014) // (SSC1) Receive Frame Mode Register
#define AT91C_SSC1_TCMR ((AT91_REG *) 	0xFFFC0018) // (SSC1) Transmit Clock Mode Register
#define AT91C_SSC1_TFMR ((AT91_REG *) 	0xFFFC001C) // (SSC1) Transmit Frame Mode Register
#define AT91C_SSC1_IMR  ((AT91_REG *) 	0xFFFC004C) // (SSC1) Interrupt Mask Register
// ========== Register definition for PDC_SSC2 peripheral ========== 
#define AT91C_SSC2_RNCR ((AT91_REG *) 	0xFFFC4114) // (PDC_SSC2) Receive Next Counter Register
#define AT91C_SSC2_PTCR ((AT91_REG *) 	0xFFFC4120) // (PDC_SSC2) PDC Transfer Control Register
#define AT91C_SSC2_TCR  ((AT91_REG *) 	0xFFFC410C) // (PDC_SSC2) Transmit Counter Register
#define AT91C_SSC2_PTSR ((AT91_REG *) 	0xFFFC4124) // (PDC_SSC2) PDC Transfer Status Register
#define AT91C_SSC2_TNPR ((AT91_REG *) 	0xFFFC4118) // (PDC_SSC2) Transmit Next Pointer Register
#define AT91C_SSC2_RCR  ((AT91_REG *) 	0xFFFC4104) // (PDC_SSC2) Receive Counter Register
#define AT91C_SSC2_RNPR ((AT91_REG *) 	0xFFFC4110) // (PDC_SSC2) Receive Next Pointer Register
#define AT91C_SSC2_RPR  ((AT91_REG *) 	0xFFFC4100) // (PDC_SSC2) Receive Pointer Register
#define AT91C_SSC2_TNCR ((AT91_REG *) 	0xFFFC411C) // (PDC_SSC2) Transmit Next Counter Register
#define AT91C_SSC2_TPR  ((AT91_REG *) 	0xFFFC4108) // (PDC_SSC2) Transmit Pointer Register
// ========== Register definition for SSC2 peripheral ========== 
#define AT91C_SSC2_IMR  ((AT91_REG *) 	0xFFFC404C) // (SSC2) Interrupt Mask Register
#define AT91C_SSC2_IER  ((AT91_REG *) 	0xFFFC4044) // (SSC2) Interrupt Enable Register
#define AT91C_SSC2_THR  ((AT91_REG *) 	0xFFFC4024) // (SSC2) Transmit Holding Register
#define AT91C_SSC2_RFMR ((AT91_REG *) 	0xFFFC4014) // (SSC2) Receive Frame Mode Register
#define AT91C_SSC2_TFMR ((AT91_REG *) 	0xFFFC401C) // (SSC2) Transmit Frame Mode Register
#define AT91C_SSC2_IDR  ((AT91_REG *) 	0xFFFC4048) // (SSC2) Interrupt Disable Register
#define AT91C_SSC2_RSHR ((AT91_REG *) 	0xFFFC4030) // (SSC2) Receive Sync Holding Register
#define AT91C_SSC2_TCMR ((AT91_REG *) 	0xFFFC4018) // (SSC2) Transmit Clock Mode Register
#define AT91C_SSC2_RHR  ((AT91_REG *) 	0xFFFC4020) // (SSC2) Receive Holding Register
#define AT91C_SSC2_RCMR ((AT91_REG *) 	0xFFFC4010) // (SSC2) Receive Clock ModeRegister
#define AT91C_SSC2_CR   ((AT91_REG *) 	0xFFFC4000) // (SSC2) Control Register
#define AT91C_SSC2_SR   ((AT91_REG *) 	0xFFFC4040) // (SSC2) Status Register
#define AT91C_SSC2_CMR  ((AT91_REG *) 	0xFFFC4004) // (SSC2) Clock Mode Register
#define AT91C_SSC2_TSHR ((AT91_REG *) 	0xFFFC4034) // (SSC2) Transmit Sync Holding Register
// ========== Register definition for PDC_SPI0 peripheral ========== 
#define AT91C_SPI0_PTCR ((AT91_REG *) 	0xFFFC8120) // (PDC_SPI0) PDC Transfer Control Register
#define AT91C_SPI0_TCR  ((AT91_REG *) 	0xFFFC810C) // (PDC_SPI0) Transmit Counter Register
#define AT91C_SPI0_RPR  ((AT91_REG *) 	0xFFFC8100) // (PDC_SPI0) Receive Pointer Register
#define AT91C_SPI0_TPR  ((AT91_REG *) 	0xFFFC8108) // (PDC_SPI0) Transmit Pointer Register
#define AT91C_SPI0_PTSR ((AT91_REG *) 	0xFFFC8124) // (PDC_SPI0) PDC Transfer Status Register
#define AT91C_SPI0_RNCR ((AT91_REG *) 	0xFFFC8114) // (PDC_SPI0) Receive Next Counter Register
#define AT91C_SPI0_TNPR ((AT91_REG *) 	0xFFFC8118) // (PDC_SPI0) Transmit Next Pointer Register
#define AT91C_SPI0_RCR  ((AT91_REG *) 	0xFFFC8104) // (PDC_SPI0) Receive Counter Register
#define AT91C_SPI0_RNPR ((AT91_REG *) 	0xFFFC8110) // (PDC_SPI0) Receive Next Pointer Register
#define AT91C_SPI0_TNCR ((AT91_REG *) 	0xFFFC811C) // (PDC_SPI0) Transmit Next Counter Register
// ========== Register definition for SPI0 peripheral ========== 
#define AT91C_SPI0_IDR  ((AT91_REG *) 	0xFFFC8018) // (SPI0) Interrupt Disable Register
#define AT91C_SPI0_TDR  ((AT91_REG *) 	0xFFFC800C) // (SPI0) Transmit Data Register
#define AT91C_SPI0_SR   ((AT91_REG *) 	0xFFFC8010) // (SPI0) Status Register
#define AT91C_SPI0_CR   ((AT91_REG *) 	0xFFFC8000) // (SPI0) Control Register
#define AT91C_SPI0_CSR  ((AT91_REG *) 	0xFFFC8030) // (SPI0) Chip Select Register
#define AT91C_SPI0_RDR  ((AT91_REG *) 	0xFFFC8008) // (SPI0) Receive Data Register
#define AT91C_SPI0_MR   ((AT91_REG *) 	0xFFFC8004) // (SPI0) Mode Register
#define AT91C_SPI0_IER  ((AT91_REG *) 	0xFFFC8014) // (SPI0) Interrupt Enable Register
#define AT91C_SPI0_IMR  ((AT91_REG *) 	0xFFFC801C) // (SPI0) Interrupt Mask Register
// ========== Register definition for PDC_SPI1 peripheral ========== 
#define AT91C_SPI1_PTCR ((AT91_REG *) 	0xFFFCC120) // (PDC_SPI1) PDC Transfer Control Register
#define AT91C_SPI1_RNPR ((AT91_REG *) 	0xFFFCC110) // (PDC_SPI1) Receive Next Pointer Register
#define AT91C_SPI1_RCR  ((AT91_REG *) 	0xFFFCC104) // (PDC_SPI1) Receive Counter Register
#define AT91C_SPI1_TPR  ((AT91_REG *) 	0xFFFCC108) // (PDC_SPI1) Transmit Pointer Register
#define AT91C_SPI1_PTSR ((AT91_REG *) 	0xFFFCC124) // (PDC_SPI1) PDC Transfer Status Register
#define AT91C_SPI1_TNCR ((AT91_REG *) 	0xFFFCC11C) // (PDC_SPI1) Transmit Next Counter Register
#define AT91C_SPI1_RPR  ((AT91_REG *) 	0xFFFCC100) // (PDC_SPI1) Receive Pointer Register
#define AT91C_SPI1_TCR  ((AT91_REG *) 	0xFFFCC10C) // (PDC_SPI1) Transmit Counter Register
#define AT91C_SPI1_RNCR ((AT91_REG *) 	0xFFFCC114) // (PDC_SPI1) Receive Next Counter Register
#define AT91C_SPI1_TNPR ((AT91_REG *) 	0xFFFCC118) // (PDC_SPI1) Transmit Next Pointer Register
// ========== Register definition for SPI1 peripheral ========== 
#define AT91C_SPI1_IER  ((AT91_REG *) 	0xFFFCC014) // (SPI1) Interrupt Enable Register
#define AT91C_SPI1_RDR  ((AT91_REG *) 	0xFFFCC008) // (SPI1) Receive Data Register
#define AT91C_SPI1_SR   ((AT91_REG *) 	0xFFFCC010) // (SPI1) Status Register
#define AT91C_SPI1_IMR  ((AT91_REG *) 	0xFFFCC01C) // (SPI1) Interrupt Mask Register
#define AT91C_SPI1_TDR  ((AT91_REG *) 	0xFFFCC00C) // (SPI1) Transmit Data Register
#define AT91C_SPI1_IDR  ((AT91_REG *) 	0xFFFCC018) // (SPI1) Interrupt Disable Register
#define AT91C_SPI1_CSR  ((AT91_REG *) 	0xFFFCC030) // (SPI1) Chip Select Register
#define AT91C_SPI1_CR   ((AT91_REG *) 	0xFFFCC000) // (SPI1) Control Register
#define AT91C_SPI1_MR   ((AT91_REG *) 	0xFFFCC004) // (SPI1) Mode Register
// ========== Register definition for UHP peripheral ========== 
#define AT91C_UHP_HcInterruptStatus ((AT91_REG *) 	0x0050000C) // (UHP) Interrupt Status Register
#define AT91C_UHP_HcCommandStatus ((AT91_REG *) 	0x00500008) // (UHP) Command & status Register
#define AT91C_UHP_HcRhStatus ((AT91_REG *) 	0x00500050) // (UHP) Root Hub Status register
#define AT91C_UHP_HcInterruptDisable ((AT91_REG *) 	0x00500014) // (UHP) Interrupt Disable Register
#define AT91C_UHP_HcPeriodicStart ((AT91_REG *) 	0x00500040) // (UHP) Periodic Start
#define AT91C_UHP_HcControlCurrentED ((AT91_REG *) 	0x00500024) // (UHP) Endpoint Control and Status Register
#define AT91C_UHP_HcPeriodCurrentED ((AT91_REG *) 	0x0050001C) // (UHP) Current Isochronous or Interrupt Endpoint Descriptor
#define AT91C_UHP_HcBulkHeadED ((AT91_REG *) 	0x00500028) // (UHP) First endpoint register of the Bulk list
#define AT91C_UHP_HcRevision ((AT91_REG *) 	0x00500000) // (UHP) Revision
#define AT91C_UHP_HcBulkCurrentED ((AT91_REG *) 	0x0050002C) // (UHP) Current endpoint of the Bulk list
#define AT91C_UHP_HcRhDescriptorB ((AT91_REG *) 	0x0050004C) // (UHP) Root Hub characteristics B
#define AT91C_UHP_HcControlHeadED ((AT91_REG *) 	0x00500020) // (UHP) First Endpoint Descriptor of the Control list
#define AT91C_UHP_HcFmRemaining ((AT91_REG *) 	0x00500038) // (UHP) Bit time remaining in the current Frame
#define AT91C_UHP_HcHCCA ((AT91_REG *) 	0x00500018) // (UHP) Pointer to the Host Controller Communication Area
#define AT91C_UHP_HcLSThreshold ((AT91_REG *) 	0x00500044) // (UHP) LS Threshold
#define AT91C_UHP_HcRhPortStatus ((AT91_REG *) 	0x00500054) // (UHP) Root Hub Port Status Register
#define AT91C_UHP_HcInterruptEnable ((AT91_REG *) 	0x00500010) // (UHP) Interrupt Enable Register
#define AT91C_UHP_HcFmNumber ((AT91_REG *) 	0x0050003C) // (UHP) Frame number
#define AT91C_UHP_HcFmInterval ((AT91_REG *) 	0x00500034) // (UHP) Bit time between 2 consecutive SOFs
#define AT91C_UHP_HcControl ((AT91_REG *) 	0x00500004) // (UHP) Operating modes for the Host Controller
#define AT91C_UHP_HcBulkDoneHead ((AT91_REG *) 	0x00500030) // (UHP) Last completed transfer descriptor
#define AT91C_UHP_HcRhDescriptorA ((AT91_REG *) 	0x00500048) // (UHP) Root Hub characteristics A
// ========== Register definition for LCDC peripheral ========== 
#define AT91C_LCDC_DP4_7 ((AT91_REG *) 	0x00600820) // (LCDC) Dithering Pattern DP4_7 Register
#define AT91C_LCDC_PWRCON ((AT91_REG *) 	0x0060083C) // (LCDC) Power Control Register
#define AT91C_LCDC_LUT_ENTRY ((AT91_REG *) 	0x00600C00) // (LCDC) LUT Entries Register
#define AT91C_LCDC_TIM1 ((AT91_REG *) 	0x00600808) // (LCDC) LCD Timing Config 1 Register
#define AT91C_LCDC_CTRSTVAL ((AT91_REG *) 	0x00600844) // (LCDC) Contrast Value Register
#define AT91C_LCDC_ISR  ((AT91_REG *) 	0x00600854) // (LCDC) Interrupt Enable Register
#define AT91C_LCDC_IDR  ((AT91_REG *) 	0x0060084C) // (LCDC) Interrupt Disable Register
#define AT91C_LCDC_DP2_3 ((AT91_REG *) 	0x00600828) // (LCDC) Dithering Pattern DP2_3 Register
#define AT91C_LCDC_DP1_2 ((AT91_REG *) 	0x0060081C) // (LCDC) Dithering Pattern DP1_2 Register
#define AT91C_LCDC_FRMP1 ((AT91_REG *) 	0x00600008) // (LCDC) DMA Frame Pointer Register 1
#define AT91C_LCDC_LCDCON2 ((AT91_REG *) 	0x00600804) // (LCDC) LCD Control 2 Register
#define AT91C_LCDC_DP4_5 ((AT91_REG *) 	0x00600834) // (LCDC) Dithering Pattern DP4_5 Register
#define AT91C_LCDC_IRR  ((AT91_REG *) 	0x00600864) // (LCDC) Interrupts Raw Status Register
#define AT91C_LCDC_IER  ((AT91_REG *) 	0x00600848) // (LCDC) Interrupt Enable Register
#define AT91C_LCDC_MVAL ((AT91_REG *) 	0x00600818) // (LCDC) LCD Mode Toggle Rate Value Register
#define AT91C_LCDC_BA2  ((AT91_REG *) 	0x00600004) // (LCDC) DMA Base Address Register 2
#define AT91C_LCDC_DMA2DCFG ((AT91_REG *) 	0x00600020) // (LCDC) DMA 2D addressing configuration
#define AT91C_LCDC_ICR  ((AT91_REG *) 	0x00600858) // (LCDC) Interrupt Clear Register
#define AT91C_LCDC_FRMA2 ((AT91_REG *) 	0x00600014) // (LCDC) DMA Frame Address Register 2
#define AT91C_LCDC_LCDFRCFG ((AT91_REG *) 	0x00600810) // (LCDC) LCD Frame Config Register
#define AT91C_LCDC_FRMP2 ((AT91_REG *) 	0x0060000C) // (LCDC) DMA Frame Pointer Register 2
#define AT91C_LCDC_LCDCON1 ((AT91_REG *) 	0x00600800) // (LCDC) LCD Control 1 Register
#define AT91C_LCDC_FRMCFG ((AT91_REG *) 	0x00600018) // (LCDC) DMA Frame Configuration Register
#define AT91C_LCDC_DP5_7 ((AT91_REG *) 	0x0060082C) // (LCDC) Dithering Pattern DP5_7 Register
#define AT91C_LCDC_GPR  ((AT91_REG *) 	0x0060085C) // (LCDC) General Purpose Register
#define AT91C_LCDC_FIFO ((AT91_REG *) 	0x00600814) // (LCDC) LCD FIFO Register
#define AT91C_LCDC_CTRSTCON ((AT91_REG *) 	0x00600840) // (LCDC) Contrast Control Register
#define AT91C_LCDC_DP3_4 ((AT91_REG *) 	0x00600830) // (LCDC) Dithering Pattern DP3_4 Register
#define AT91C_LCDC_FRMA1 ((AT91_REG *) 	0x00600010) // (LCDC) DMA Frame Address Register 1
#define AT91C_LCDC_TIM2 ((AT91_REG *) 	0x0060080C) // (LCDC) LCD Timing Config 2 Register
#define AT91C_LCDC_BA1  ((AT91_REG *) 	0x00600000) // (LCDC) DMA Base Address Register 1
#define AT91C_LCDC_DP3_5 ((AT91_REG *) 	0x00600824) // (LCDC) Dithering Pattern DP3_5 Register
#define AT91C_LCDC_DP6_7 ((AT91_REG *) 	0x00600838) // (LCDC) Dithering Pattern DP6_7 Register
#define AT91C_LCDC_DMACON ((AT91_REG *) 	0x0060001C) // (LCDC) DMA Control Register
#define AT91C_LCDC_IMR  ((AT91_REG *) 	0x00600850) // (LCDC) Interrupt Mask Register
#define AT91C_LCDC_ITR  ((AT91_REG *) 	0x00600860) // (LCDC) Interrupts Test Register
// ========== Register definition for LCDC_16B_TFT peripheral ========== 
#define AT91C_TFT_DP4_7 ((AT91_REG *) 	0x00600820) // (LCDC_16B_TFT) Dithering Pattern DP4_7 Register
#define AT91C_TFT_PWRCON ((AT91_REG *) 	0x0060083C) // (LCDC_16B_TFT) Power Control Register
#define AT91C_TFT_LUT_ENTRY ((AT91_REG *) 	0x00600C00) // (LCDC_16B_TFT) LUT Entries Register
#define AT91C_TFT_TIM1  ((AT91_REG *) 	0x00600808) // (LCDC_16B_TFT) LCD Timing Config 1 Register
#define AT91C_TFT_CTRSTVAL ((AT91_REG *) 	0x00600844) // (LCDC_16B_TFT) Contrast Value Register
#define AT91C_TFT_ISR   ((AT91_REG *) 	0x00600854) // (LCDC_16B_TFT) Interrupt Enable Register
#define AT91C_TFT_IDR   ((AT91_REG *) 	0x0060084C) // (LCDC_16B_TFT) Interrupt Disable Register
#define AT91C_TFT_DP2_3 ((AT91_REG *) 	0x00600828) // (LCDC_16B_TFT) Dithering Pattern DP2_3 Register
#define AT91C_TFT_DP1_2 ((AT91_REG *) 	0x0060081C) // (LCDC_16B_TFT) Dithering Pattern DP1_2 Register
#define AT91C_TFT_FRMP1 ((AT91_REG *) 	0x00600008) // (LCDC_16B_TFT) DMA Frame Pointer Register 1
#define AT91C_TFT_LCDCON2 ((AT91_REG *) 	0x00600804) // (LCDC_16B_TFT) LCD Control 2 Register
#define AT91C_TFT_DP4_5 ((AT91_REG *) 	0x00600834) // (LCDC_16B_TFT) Dithering Pattern DP4_5 Register
#define AT91C_TFT_IRR   ((AT91_REG *) 	0x00600864) // (LCDC_16B_TFT) Interrupts Raw Status Register
#define AT91C_TFT_IER   ((AT91_REG *) 	0x00600848) // (LCDC_16B_TFT) Interrupt Enable Register
#define AT91C_TFT_MVAL  ((AT91_REG *) 	0x00600818) // (LCDC_16B_TFT) LCD Mode Toggle Rate Value Register
#define AT91C_TFT_BA2   ((AT91_REG *) 	0x00600004) // (LCDC_16B_TFT) DMA Base Address Register 2
#define AT91C_TFT_DMA2DCFG ((AT91_REG *) 	0x00600020) // (LCDC_16B_TFT) DMA 2D addressing configuration
#define AT91C_TFT_ICR   ((AT91_REG *) 	0x00600858) // (LCDC_16B_TFT) Interrupt Clear Register
#define AT91C_TFT_FRMA2 ((AT91_REG *) 	0x00600014) // (LCDC_16B_TFT) DMA Frame Address Register 2
#define AT91C_TFT_LCDFRCFG ((AT91_REG *) 	0x00600810) // (LCDC_16B_TFT) LCD Frame Config Register
#define AT91C_TFT_FRMP2 ((AT91_REG *) 	0x0060000C) // (LCDC_16B_TFT) DMA Frame Pointer Register 2
#define AT91C_TFT_LCDCON1 ((AT91_REG *) 	0x00600800) // (LCDC_16B_TFT) LCD Control 1 Register
#define AT91C_TFT_FRMCFG ((AT91_REG *) 	0x00600018) // (LCDC_16B_TFT) DMA Frame Configuration Register
#define AT91C_TFT_DP5_7 ((AT91_REG *) 	0x0060082C) // (LCDC_16B_TFT) Dithering Pattern DP5_7 Register
#define AT91C_TFT_GPR   ((AT91_REG *) 	0x0060085C) // (LCDC_16B_TFT) General Purpose Register
#define AT91C_TFT_FIFO  ((AT91_REG *) 	0x00600814) // (LCDC_16B_TFT) LCD FIFO Register
#define AT91C_TFT_CTRSTCON ((AT91_REG *) 	0x00600840) // (LCDC_16B_TFT) Contrast Control Register
#define AT91C_TFT_DP3_4 ((AT91_REG *) 	0x00600830) // (LCDC_16B_TFT) Dithering Pattern DP3_4 Register
#define AT91C_TFT_FRMA1 ((AT91_REG *) 	0x00600010) // (LCDC_16B_TFT) DMA Frame Address Register 1
#define AT91C_TFT_TIM2  ((AT91_REG *) 	0x0060080C) // (LCDC_16B_TFT) LCD Timing Config 2 Register
#define AT91C_TFT_BA1   ((AT91_REG *) 	0x00600000) // (LCDC_16B_TFT) DMA Base Address Register 1
#define AT91C_TFT_DP3_5 ((AT91_REG *) 	0x00600824) // (LCDC_16B_TFT) Dithering Pattern DP3_5 Register
#define AT91C_TFT_DP6_7 ((AT91_REG *) 	0x00600838) // (LCDC_16B_TFT) Dithering Pattern DP6_7 Register
#define AT91C_TFT_DMACON ((AT91_REG *) 	0x0060001C) // (LCDC_16B_TFT) DMA Control Register
#define AT91C_TFT_IMR   ((AT91_REG *) 	0x00600850) // (LCDC_16B_TFT) Interrupt Mask Register
#define AT91C_TFT_ITR   ((AT91_REG *) 	0x00600860) // (LCDC_16B_TFT) Interrupts Test Register

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM9261
// *****************************************************************************
#define AT91C_PIO_PA0        ((unsigned int) 1 <<  0) // Pin Controlled by PA0
#define AT91C_PA0_SPI0_MISO ((unsigned int) AT91C_PIO_PA0) //  SPI0 Master In Slave
#define AT91C_PA0_MCDA0    ((unsigned int) AT91C_PIO_PA0) //  Multimedia Card A Data 0
#define AT91C_PIO_PA1        ((unsigned int) 1 <<  1) // Pin Controlled by PA1
#define AT91C_PA1_SPI0_MOSI ((unsigned int) AT91C_PIO_PA1) //  SPI0 Master Out Slave
#define AT91C_PA1_MCCDA    ((unsigned int) AT91C_PIO_PA1) //  Multimedia Card A Command
#define AT91C_PIO_PA10       ((unsigned int) 1 << 10) // Pin Controlled by PA10
#define AT91C_PA10_DTXD     ((unsigned int) AT91C_PIO_PA10) //  DBGU Debug Transmit Data
#define AT91C_PA10_PCK3     ((unsigned int) AT91C_PIO_PA10) //  PMC Programmable clock Output 3
#define AT91C_PIO_PA11       ((unsigned int) 1 << 11) // Pin Controlled by PA11
#define AT91C_PA11_TSYNC    ((unsigned int) AT91C_PIO_PA11) //  Trace Synchronization Signal
#define AT91C_PA11_SCK1     ((unsigned int) AT91C_PIO_PA11) //  USART1 Serial Clock
#define AT91C_PIO_PA12       ((unsigned int) 1 << 12) // Pin Controlled by PA12
#define AT91C_PA12_TCLK     ((unsigned int) AT91C_PIO_PA12) //  Trace Clock
#define AT91C_PA12_RTS1     ((unsigned int) AT91C_PIO_PA12) //  USART1 Ready To Send
#define AT91C_PIO_PA13       ((unsigned int) 1 << 13) // Pin Controlled by PA13
#define AT91C_PA13_TPS0     ((unsigned int) AT91C_PIO_PA13) //  Trace ARM Pipeline Status 0
#define AT91C_PA13_CTS1     ((unsigned int) AT91C_PIO_PA13) //  USART1 Clear To Send
#define AT91C_PIO_PA14       ((unsigned int) 1 << 14) // Pin Controlled by PA14
#define AT91C_PA14_TPS1     ((unsigned int) AT91C_PIO_PA14) //  Trace ARM Pipeline Status 1
#define AT91C_PA14_SCK2     ((unsigned int) AT91C_PIO_PA14) //  USART2 Serial Clock
#define AT91C_PIO_PA15       ((unsigned int) 1 << 15) // Pin Controlled by PA15
#define AT91C_PA15_TPS2     ((unsigned int) AT91C_PIO_PA15) //  Trace ARM Pipeline Status 2
#define AT91C_PA15_RTS2     ((unsigned int) AT91C_PIO_PA15) //  USART2 Ready To Send
#define AT91C_PIO_PA16       ((unsigned int) 1 << 16) // Pin Controlled by PA16
#define AT91C_PA16_TPK0     ((unsigned int) AT91C_PIO_PA16) //  Trace Packet Port 0
#define AT91C_PA16_CTS2     ((unsigned int) AT91C_PIO_PA16) //  USART2 Clear To Send
#define AT91C_PIO_PA17       ((unsigned int) 1 << 17) // Pin Controlled by PA17
#define AT91C_PA17_TPK1     ((unsigned int) AT91C_PIO_PA17) //  Trace Packet Port 1
#define AT91C_PA17_TF1      ((unsigned int) AT91C_PIO_PA17) //  SSC1 Transmit Frame Sync
#define AT91C_PIO_PA18       ((unsigned int) 1 << 18) // Pin Controlled by PA18
#define AT91C_PA18_TPK2     ((unsigned int) AT91C_PIO_PA18) //  Trace Packet Port 2
#define AT91C_PA18_TK1      ((unsigned int) AT91C_PIO_PA18) //  SSC1 Transmit Clock
#define AT91C_PIO_PA19       ((unsigned int) 1 << 19) // Pin Controlled by PA19
#define AT91C_PA19_TPK3     ((unsigned int) AT91C_PIO_PA19) //  Trace Packet Port 3
#define AT91C_PA19_TD1      ((unsigned int) AT91C_PIO_PA19) //  SSC1 Transmit Data
#define AT91C_PIO_PA2        ((unsigned int) 1 <<  2) // Pin Controlled by PA2
#define AT91C_PA2_SPI0_SPCK ((unsigned int) AT91C_PIO_PA2) //  SPI0 Serial Clock
#define AT91C_PA2_MCCK     ((unsigned int) AT91C_PIO_PA2) //  Multimedia Card Clock
#define AT91C_PIO_PA20       ((unsigned int) 1 << 20) // Pin Controlled by PA20
#define AT91C_PA20_TPK4     ((unsigned int) AT91C_PIO_PA20) //  Trace Packet Port 4
#define AT91C_PA20_RD1      ((unsigned int) AT91C_PIO_PA20) //  SSC1 Receive Data
#define AT91C_PIO_PA21       ((unsigned int) 1 << 21) // Pin Controlled by PA21
#define AT91C_PA21_TPK5     ((unsigned int) AT91C_PIO_PA21) //  Trace Packet Port 5
#define AT91C_PA21_RK1      ((unsigned int) AT91C_PIO_PA21) //  SSC1 Receive Clock
#define AT91C_PIO_PA22       ((unsigned int) 1 << 22) // Pin Controlled by PA22
#define AT91C_PA22_TPK6     ((unsigned int) AT91C_PIO_PA22) //  Trace Packet Port 6
#define AT91C_PA22_RF1      ((unsigned int) AT91C_PIO_PA22) //  SSC1 Receive Frame Sync
#define AT91C_PIO_PA23       ((unsigned int) 1 << 23) // Pin Controlled by PA23
#define AT91C_PA23_TPK7     ((unsigned int) AT91C_PIO_PA23) //  Trace Packet Port 7
#define AT91C_PA23_RTS0     ((unsigned int) AT91C_PIO_PA23) //  USART0 Ready To Send
#define AT91C_PIO_PA24       ((unsigned int) 1 << 24) // Pin Controlled by PA24
#define AT91C_PA24_TPK8     ((unsigned int) AT91C_PIO_PA24) //  Trace Packet Port 8
#define AT91C_PA24_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PA24) //  SPI1 Peripheral Chip Select 1
#define AT91C_PIO_PA25       ((unsigned int) 1 << 25) // Pin Controlled by PA25
#define AT91C_PA25_TPK9     ((unsigned int) AT91C_PIO_PA25) //  Trace Packet Port 9
#define AT91C_PA25_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PA25) //  SPI1 Peripheral Chip Select 2
#define AT91C_PIO_PA26       ((unsigned int) 1 << 26) // Pin Controlled by PA26
#define AT91C_PA26_TPK10    ((unsigned int) AT91C_PIO_PA26) //  Trace Packet Port 10
#define AT91C_PA26_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PA26) //  SPI1 Peripheral Chip Select 3
#define AT91C_PIO_PA27       ((unsigned int) 1 << 27) // Pin Controlled by PA27
#define AT91C_PA27_TPK11    ((unsigned int) AT91C_PIO_PA27) //  Trace Packet Port 11
#define AT91C_PA27_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA27) //  SPI0 Peripheral Chip Select 1
#define AT91C_PIO_PA28       ((unsigned int) 1 << 28) // Pin Controlled by PA28
#define AT91C_PA28_TPK12    ((unsigned int) AT91C_PIO_PA28) //  Trace Packet Port 12
#define AT91C_PA28_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA28) //  SPI0 Peripheral Chip Select 2
#define AT91C_PIO_PA29       ((unsigned int) 1 << 29) // Pin Controlled by PA29
#define AT91C_PA29_TPK13    ((unsigned int) AT91C_PIO_PA29) //  Trace Packet Port 13
#define AT91C_PA29_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA29) //  SPI0 Peripheral Chip Select 3
#define AT91C_PIO_PA3        ((unsigned int) 1 <<  3) // Pin Controlled by PA3
#define AT91C_PA3_SPI0_NPCS0 ((unsigned int) AT91C_PIO_PA3) //  SPI0 Peripheral Chip Select 0
#define AT91C_PIO_PA30       ((unsigned int) 1 << 30) // Pin Controlled by PA30
#define AT91C_PA30_TPK14    ((unsigned int) AT91C_PIO_PA30) //  Trace Packet Port 14
#define AT91C_PA30_A23      ((unsigned int) AT91C_PIO_PA30) //  Address Bus bit 23
#define AT91C_PIO_PA31       ((unsigned int) 1 << 31) // Pin Controlled by PA31
#define AT91C_PA31_TPK15    ((unsigned int) AT91C_PIO_PA31) //  Trace Packet Port 15
#define AT91C_PA31_A24      ((unsigned int) AT91C_PIO_PA31) //  Address Bus bit 24
#define AT91C_PIO_PA4        ((unsigned int) 1 <<  4) // Pin Controlled by PA4
#define AT91C_PA4_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA4) //  SPI0 Peripheral Chip Select 1
#define AT91C_PA4_MCDA1    ((unsigned int) AT91C_PIO_PA4) //  Multimedia Card A Data 1
#define AT91C_PIO_PA5        ((unsigned int) 1 <<  5) // Pin Controlled by PA5
#define AT91C_PA5_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA5) //  SPI0 Peripheral Chip Select 2
#define AT91C_PA5_MCDA2    ((unsigned int) AT91C_PIO_PA5) //  Multimedia Card A Data 2
#define AT91C_PIO_PA6        ((unsigned int) 1 <<  6) // Pin Controlled by PA6
#define AT91C_PA6_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA6) //  SPI0 Peripheral Chip Select 3
#define AT91C_PA6_MCDA3    ((unsigned int) AT91C_PIO_PA6) //  Multimedia Card A Data 3
#define AT91C_PIO_PA7        ((unsigned int) 1 <<  7) // Pin Controlled by PA7
#define AT91C_PA7_TWD      ((unsigned int) AT91C_PIO_PA7) //  TWI Two-wire Serial Data
#define AT91C_PA7_PCK0     ((unsigned int) AT91C_PIO_PA7) //  PMC Programmable clock Output 0
#define AT91C_PIO_PA8        ((unsigned int) 1 <<  8) // Pin Controlled by PA8
#define AT91C_PA8_TWCK     ((unsigned int) AT91C_PIO_PA8) //  TWI Two-wire Serial Clock
#define AT91C_PA8_PCK1     ((unsigned int) AT91C_PIO_PA8) //  PMC Programmable clock Output 1
#define AT91C_PIO_PA9        ((unsigned int) 1 <<  9) // Pin Controlled by PA9
#define AT91C_PA9_DRXD     ((unsigned int) AT91C_PIO_PA9) //  DBGU Debug Receive Data
#define AT91C_PA9_PCK2     ((unsigned int) AT91C_PIO_PA9) //  PMC Programmable clock Output 2
#define AT91C_PIO_PB0        ((unsigned int) 1 <<  0) // Pin Controlled by PB0
#define AT91C_PB0_LCDVSYNC ((unsigned int) AT91C_PIO_PB0) //  LCD Vertical Synchronization
#define AT91C_PIO_PB1        ((unsigned int) 1 <<  1) // Pin Controlled by PB1
#define AT91C_PB1_LCDHSYNC ((unsigned int) AT91C_PIO_PB1) //  LCD Horizontal Synchronization
#define AT91C_PIO_PB10       ((unsigned int) 1 << 10) // Pin Controlled by PB10
#define AT91C_PB10_LCDD5    ((unsigned int) AT91C_PIO_PB10) //  LCD Data Bus Bit 5
#define AT91C_PB10_LCDD10   ((unsigned int) AT91C_PIO_PB10) //  LCD Data Bus Bit 10
#define AT91C_PIO_PB11       ((unsigned int) 1 << 11) // Pin Controlled by PB11
#define AT91C_PB11_LCDD6    ((unsigned int) AT91C_PIO_PB11) //  LCD Data Bus Bit 6
#define AT91C_PB11_LCDD11   ((unsigned int) AT91C_PIO_PB11) //  LCD Data Bus Bit 11
#define AT91C_PIO_PB12       ((unsigned int) 1 << 12) // Pin Controlled by PB12
#define AT91C_PB12_LCDD7    ((unsigned int) AT91C_PIO_PB12) //  LCD Data Bus Bit 7
#define AT91C_PB12_LCDD12   ((unsigned int) AT91C_PIO_PB12) //  LCD Data Bus Bit 12
#define AT91C_PIO_PB13       ((unsigned int) 1 << 13) // Pin Controlled by PB13
#define AT91C_PB13_LCDD8    ((unsigned int) AT91C_PIO_PB13) //  LCD Data Bus Bit 8
#define AT91C_PB13_LCDD13   ((unsigned int) AT91C_PIO_PB13) //  LCD Data Bus Bit 13
#define AT91C_PIO_PB14       ((unsigned int) 1 << 14) // Pin Controlled by PB14
#define AT91C_PB14_LCDD9    ((unsigned int) AT91C_PIO_PB14) //  LCD Data Bus Bit 9
#define AT91C_PB14_LCDD14   ((unsigned int) AT91C_PIO_PB14) //  LCD Data Bus Bit 14
#define AT91C_PIO_PB15       ((unsigned int) 1 << 15) // Pin Controlled by PB15
#define AT91C_PB15_LCDD10   ((unsigned int) AT91C_PIO_PB15) //  LCD Data Bus Bit 10
#define AT91C_PB15_LCDD15   ((unsigned int) AT91C_PIO_PB15) //  LCD Data Bus Bit 15
#define AT91C_PIO_PB16       ((unsigned int) 1 << 16) // Pin Controlled by PB16
#define AT91C_PB16_LCDD11   ((unsigned int) AT91C_PIO_PB16) //  LCD Data Bus Bit 11
#define AT91C_PB16_LCDD19   ((unsigned int) AT91C_PIO_PB16) //  LCD Data Bus Bit 19
#define AT91C_PIO_PB17       ((unsigned int) 1 << 17) // Pin Controlled by PB17
#define AT91C_PB17_LCDD12   ((unsigned int) AT91C_PIO_PB17) //  LCD Data Bus Bit 12
#define AT91C_PB17_LCDD20   ((unsigned int) AT91C_PIO_PB17) //  LCD Data Bus Bit 20
#define AT91C_PIO_PB18       ((unsigned int) 1 << 18) // Pin Controlled by PB18
#define AT91C_PB18_LCDD13   ((unsigned int) AT91C_PIO_PB18) //  LCD Data Bus Bit 13
#define AT91C_PB18_LCDD21   ((unsigned int) AT91C_PIO_PB18) //  LCD Data Bus Bit 21
#define AT91C_PIO_PB19       ((unsigned int) 1 << 19) // Pin Controlled by PB19
#define AT91C_PB19_LCDD14   ((unsigned int) AT91C_PIO_PB19) //  LCD Data Bus Bit 14
#define AT91C_PB19_LCDD22   ((unsigned int) AT91C_PIO_PB19) //  LCD Data Bus Bit 22
#define AT91C_PIO_PB2        ((unsigned int) 1 <<  2) // Pin Controlled by PB2
#define AT91C_PB2_LCDDOTCK ((unsigned int) AT91C_PIO_PB2) //  LCD Dot Clock
#define AT91C_PB2_PCK0     ((unsigned int) AT91C_PIO_PB2) //  PMC Programmable clock Output 0
#define AT91C_PIO_PB20       ((unsigned int) 1 << 20) // Pin Controlled by PB20
#define AT91C_PB20_LCDD15   ((unsigned int) AT91C_PIO_PB20) //  LCD Data Bus Bit 15
#define AT91C_PB20_LCDD23   ((unsigned int) AT91C_PIO_PB20) //  LCD Data Bus Bit 23
#define AT91C_PIO_PB21       ((unsigned int) 1 << 21) // Pin Controlled by PB21
#define AT91C_PB21_TF0      ((unsigned int) AT91C_PIO_PB21) //  SSC0 Transmit Frame Sync
#define AT91C_PB21_LCDD16   ((unsigned int) AT91C_PIO_PB21) //  LCD Data Bus Bit 16
#define AT91C_PIO_PB22       ((unsigned int) 1 << 22) // Pin Controlled by PB22
#define AT91C_PB22_TK0      ((unsigned int) AT91C_PIO_PB22) //  SSC0 Transmit Clock
#define AT91C_PB22_LCDD17   ((unsigned int) AT91C_PIO_PB22) //  LCD Data Bus Bit 17
#define AT91C_PIO_PB23       ((unsigned int) 1 << 23) // Pin Controlled by PB23
#define AT91C_PB23_TD0      ((unsigned int) AT91C_PIO_PB23) //  SSC0 Transmit Data
#define AT91C_PB23_LCDD18   ((unsigned int) AT91C_PIO_PB23) //  LCD Data Bus Bit 18
#define AT91C_PIO_PB24       ((unsigned int) 1 << 24) // Pin Controlled by PB24
#define AT91C_PB24_RD0      ((unsigned int) AT91C_PIO_PB24) //  SSC0 Receive Data
#define AT91C_PB24_LCDD19   ((unsigned int) AT91C_PIO_PB24) //  LCD Data Bus Bit 19
#define AT91C_PIO_PB25       ((unsigned int) 1 << 25) // Pin Controlled by PB25
#define AT91C_PB25_RK0      ((unsigned int) AT91C_PIO_PB25) //  SSC0 Receive Clock
#define AT91C_PB25_LCDD20   ((unsigned int) AT91C_PIO_PB25) //  LCD Data Bus Bit 20
#define AT91C_PIO_PB26       ((unsigned int) 1 << 26) // Pin Controlled by PB26
#define AT91C_PB26_RF0      ((unsigned int) AT91C_PIO_PB26) //  SSC0 Receive Frame Sync
#define AT91C_PB26_LCDD21   ((unsigned int) AT91C_PIO_PB26) //  LCD Data Bus Bit 21
#define AT91C_PIO_PB27       ((unsigned int) 1 << 27) // Pin Controlled by PB27
#define AT91C_PB27_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PB27) //  SPI1 Peripheral Chip Select 1
#define AT91C_PB27_LCDD22   ((unsigned int) AT91C_PIO_PB27) //  LCD Data Bus Bit 22
#define AT91C_PIO_PB28       ((unsigned int) 1 << 28) // Pin Controlled by PB28
#define AT91C_PB28_SPI1_NPCS0 ((unsigned int) AT91C_PIO_PB28) //  SPI1 Peripheral Chip Select 0
#define AT91C_PB28_LCDD23   ((unsigned int) AT91C_PIO_PB28) //  LCD Data Bus Bit 23
#define AT91C_PIO_PB29       ((unsigned int) 1 << 29) // Pin Controlled by PB29
#define AT91C_PB29_SPI1_SPCK ((unsigned int) AT91C_PIO_PB29) //  SPI1 Serial Clock
#define AT91C_PB29_IRQ2     ((unsigned int) AT91C_PIO_PB29) //  Interrupt input 2
#define AT91C_PIO_PB3        ((unsigned int) 1 <<  3) // Pin Controlled by PB3
#define AT91C_PB3_LCDDEN   ((unsigned int) AT91C_PIO_PB3) //  LCD Data Enable
#define AT91C_PIO_PB30       ((unsigned int) 1 << 30) // Pin Controlled by PB30
#define AT91C_PB30_SPI1_MISO ((unsigned int) AT91C_PIO_PB30) //  SPI1 Master In Slave
#define AT91C_PB30_IRQ1     ((unsigned int) AT91C_PIO_PB30) //  Interrupt input 1
#define AT91C_PIO_PB31       ((unsigned int) 1 << 31) // Pin Controlled by PB31
#define AT91C_PB31_SPI1_MOSI ((unsigned int) AT91C_PIO_PB31) //  SPI1 Master Out Slave
#define AT91C_PB31_PCK2     ((unsigned int) AT91C_PIO_PB31) //  PMC Programmable clock Output 2
#define AT91C_PIO_PB4        ((unsigned int) 1 <<  4) // Pin Controlled by PB4
#define AT91C_PB4_LCDCC    ((unsigned int) AT91C_PIO_PB4) //  LCD Contrast Control
#define AT91C_PB4_LCDD2    ((unsigned int) AT91C_PIO_PB4) //  LCD Data Bus Bit 2
#define AT91C_PIO_PB5        ((unsigned int) 1 <<  5) // Pin Controlled by PB5
#define AT91C_PB5_LCDD0    ((unsigned int) AT91C_PIO_PB5) //  LCD Data Bus Bit 0
#define AT91C_PB5_LCDD3    ((unsigned int) AT91C_PIO_PB5) //  LCD Data Bus Bit 3
#define AT91C_PIO_PB6        ((unsigned int) 1 <<  6) // Pin Controlled by PB6
#define AT91C_PB6_LCDD1    ((unsigned int) AT91C_PIO_PB6) //  LCD Data Bus Bit 1
#define AT91C_PB6_LCDD4    ((unsigned int) AT91C_PIO_PB6) //  LCD Data Bus Bit 4
#define AT91C_PIO_PB7        ((unsigned int) 1 <<  7) // Pin Controlled by PB7
#define AT91C_PB7_LCDD2    ((unsigned int) AT91C_PIO_PB7) //  LCD Data Bus Bit 2
#define AT91C_PB7_LCDD5    ((unsigned int) AT91C_PIO_PB7) //  LCD Data Bus Bit 5
#define AT91C_PIO_PB8        ((unsigned int) 1 <<  8) // Pin Controlled by PB8
#define AT91C_PB8_LCDD3    ((unsigned int) AT91C_PIO_PB8) //  LCD Data Bus Bit 3
#define AT91C_PB8_LCDD6    ((unsigned int) AT91C_PIO_PB8) //  LCD Data Bus Bit 6
#define AT91C_PIO_PB9        ((unsigned int) 1 <<  9) // Pin Controlled by PB9
#define AT91C_PB9_LCDD4    ((unsigned int) AT91C_PIO_PB9) //  LCD Data Bus Bit 4
#define AT91C_PB9_LCDD7    ((unsigned int) AT91C_PIO_PB9) //  LCD Data Bus Bit 7
#define AT91C_PIO_PC0        ((unsigned int) 1 <<  0) // Pin Controlled by PC0
#define AT91C_PC0_SMOE     ((unsigned int) AT91C_PIO_PC0) //  SmartMedia Output Enable
#define AT91C_PC0_NCS6     ((unsigned int) AT91C_PIO_PC0) //  Chip Select 6
#define AT91C_PIO_PC1        ((unsigned int) 1 <<  1) // Pin Controlled by PC1
#define AT91C_PC1_SMWE     ((unsigned int) AT91C_PIO_PC1) //  SmartMedia Write Enable
#define AT91C_PC1_NCS7     ((unsigned int) AT91C_PIO_PC1) //  Chip Select 7
#define AT91C_PIO_PC10       ((unsigned int) 1 << 10) // Pin Controlled by PC10
#define AT91C_PC10_RTS0     ((unsigned int) AT91C_PIO_PC10) //  USART0 Ready To Send
#define AT91C_PC10_SCK0     ((unsigned int) AT91C_PIO_PC10) //  USART0 Serial Clock
#define AT91C_PIO_PC11       ((unsigned int) 1 << 11) // Pin Controlled by PC11
#define AT91C_PC11_CTS0     ((unsigned int) AT91C_PIO_PC11) //  USART0 Clear To Send
#define AT91C_PC11_FIQ      ((unsigned int) AT91C_PIO_PC11) //  AIC Fast Interrupt Input
#define AT91C_PIO_PC12       ((unsigned int) 1 << 12) // Pin Controlled by PC12
#define AT91C_PC12_TXD1     ((unsigned int) AT91C_PIO_PC12) //  USART1 Transmit Data
#define AT91C_PC12_NCS6     ((unsigned int) AT91C_PIO_PC12) //  Chip Select 6
#define AT91C_PIO_PC13       ((unsigned int) 1 << 13) // Pin Controlled by PC13
#define AT91C_PC13_RXD1     ((unsigned int) AT91C_PIO_PC13) //  USART1 Receive Data
#define AT91C_PC13_NCS7     ((unsigned int) AT91C_PIO_PC13) //  Chip Select 7
#define AT91C_PIO_PC14       ((unsigned int) 1 << 14) // Pin Controlled by PC14
#define AT91C_PC14_TXD2     ((unsigned int) AT91C_PIO_PC14) //  USART2 Transmit Data
#define AT91C_PC14_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PC14) //  SPI1 Peripheral Chip Select 2
#define AT91C_PIO_PC15       ((unsigned int) 1 << 15) // Pin Controlled by PC15
#define AT91C_PC15_RXD2     ((unsigned int) AT91C_PIO_PC15) //  USART2 Receive Data
#define AT91C_PC15_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PC15) //  SPI1 Peripheral Chip Select 3
#define AT91C_PIO_PC16       ((unsigned int) 1 << 16) // Pin Controlled by PC16
#define AT91C_PC16_D16      ((unsigned int) AT91C_PIO_PC16) //  Data Bus [16]
#define AT91C_PC16_TCLK0    ((unsigned int) AT91C_PIO_PC16) //  Timer Counter 0 external clock input
#define AT91C_PIO_PC17       ((unsigned int) 1 << 17) // Pin Controlled by PC17
#define AT91C_PC17_D17      ((unsigned int) AT91C_PIO_PC17) //  Data Bus [17]
#define AT91C_PC17_TCLK1    ((unsigned int) AT91C_PIO_PC17) //  Timer Counter 1 external clock input
#define AT91C_PIO_PC18       ((unsigned int) 1 << 18) // Pin Controlled by PC18
#define AT91C_PC18_D18      ((unsigned int) AT91C_PIO_PC18) //  Data Bus [18]
#define AT91C_PC18_TCLK2    ((unsigned int) AT91C_PIO_PC18) //  Timer Counter 2 external clock input
#define AT91C_PIO_PC19       ((unsigned int) 1 << 19) // Pin Controlled by PC19
#define AT91C_PC19_D19      ((unsigned int) AT91C_PIO_PC19) //  Data Bus [19]
#define AT91C_PC19_TIOA0    ((unsigned int) AT91C_PIO_PC19) //  Timer Counter 0 Multipurpose Timer I/O Pin A
#define AT91C_PIO_PC2        ((unsigned int) 1 <<  2) // Pin Controlled by PC2
#define AT91C_PC2_NWAIT    ((unsigned int) AT91C_PIO_PC2) //  NWAIT
#define AT91C_PC2_IRQ0     ((unsigned int) AT91C_PIO_PC2) //  Interrupt input 0
#define AT91C_PIO_PC20       ((unsigned int) 1 << 20) // Pin Controlled by PC20
#define AT91C_PC20_D20      ((unsigned int) AT91C_PIO_PC20) //  Data Bus [20]
#define AT91C_PC20_TIOB0    ((unsigned int) AT91C_PIO_PC20) //  Timer Counter 0 Multipurpose Timer I/O Pin B
#define AT91C_PIO_PC21       ((unsigned int) 1 << 21) // Pin Controlled by PC21
#define AT91C_PC21_D21      ((unsigned int) AT91C_PIO_PC21) //  Data Bus [21]
#define AT91C_PC21_TIOA1    ((unsigned int) AT91C_PIO_PC21) //  Timer Counter 1 Multipurpose Timer I/O Pin A
#define AT91C_PIO_PC22       ((unsigned int) 1 << 22) // Pin Controlled by PC22
#define AT91C_PC22_D22      ((unsigned int) AT91C_PIO_PC22) //  Data Bus [22]
#define AT91C_PC22_TIOB1    ((unsigned int) AT91C_PIO_PC22) //  Timer Counter 1 Multipurpose Timer I/O Pin B
#define AT91C_PIO_PC23       ((unsigned int) 1 << 23) // Pin Controlled by PC23
#define AT91C_PC23_D23      ((unsigned int) AT91C_PIO_PC23) //  Data Bus [23]
#define AT91C_PC23_TIOA2    ((unsigned int) AT91C_PIO_PC23) //  Timer Counter 2 Multipurpose Timer I/O Pin A
#define AT91C_PIO_PC24       ((unsigned int) 1 << 24) // Pin Controlled by PC24
#define AT91C_PC24_D24      ((unsigned int) AT91C_PIO_PC24) //  Data Bus [24]
#define AT91C_PC24_TIOB2    ((unsigned int) AT91C_PIO_PC24) //  Timer Counter 2 Multipurpose Timer I/O Pin B
#define AT91C_PIO_PC25       ((unsigned int) 1 << 25) // Pin Controlled by PC25
#define AT91C_PC25_D25      ((unsigned int) AT91C_PIO_PC25) //  Data Bus [25]
#define AT91C_PC25_TF2      ((unsigned int) AT91C_PIO_PC25) //  SSC2 Transmit Frame Sync
#define AT91C_PIO_PC26       ((unsigned int) 1 << 26) // Pin Controlled by PC26
#define AT91C_PC26_D26      ((unsigned int) AT91C_PIO_PC26) //  Data Bus [26]
#define AT91C_PC26_TK2      ((unsigned int) AT91C_PIO_PC26) //  SSC2 Transmit Clock
#define AT91C_PIO_PC27       ((unsigned int) 1 << 27) // Pin Controlled by PC27
#define AT91C_PC27_D27      ((unsigned int) AT91C_PIO_PC27) //  Data Bus [27]
#define AT91C_PC27_TD2      ((unsigned int) AT91C_PIO_PC27) //  SSC2 Transmit Data
#define AT91C_PIO_PC28       ((unsigned int) 1 << 28) // Pin Controlled by PC28
#define AT91C_PC28_D28      ((unsigned int) AT91C_PIO_PC28) //  Data Bus [28]
#define AT91C_PC28_RD2      ((unsigned int) AT91C_PIO_PC28) //  SSC2 Receive Data
#define AT91C_PIO_PC29       ((unsigned int) 1 << 29) // Pin Controlled by PC29
#define AT91C_PC29_D29      ((unsigned int) AT91C_PIO_PC29) //  Data Bus [29]
#define AT91C_PC29_RK2      ((unsigned int) AT91C_PIO_PC29) //  SSC2 Receive Clock
#define AT91C_PIO_PC3        ((unsigned int) 1 <<  3) // Pin Controlled by PC3
#define AT91C_PC3_A25_CFRNW ((unsigned int) AT91C_PIO_PC3) //  Address Bus[25] / Compact Flash Read Not Write
#define AT91C_PIO_PC30       ((unsigned int) 1 << 30) // Pin Controlled by PC30
#define AT91C_PC30_D30      ((unsigned int) AT91C_PIO_PC30) //  Data Bus [30]
#define AT91C_PC30_RF2      ((unsigned int) AT91C_PIO_PC30) //  SSC2 Receive Frame Sync
#define AT91C_PIO_PC31       ((unsigned int) 1 << 31) // Pin Controlled by PC31
#define AT91C_PC31_D31      ((unsigned int) AT91C_PIO_PC31) //  Data Bus [31]
#define AT91C_PC31_PCK1     ((unsigned int) AT91C_PIO_PC31) //  PMC Programmable clock Output 1
#define AT91C_PIO_PC4        ((unsigned int) 1 <<  4) // Pin Controlled by PC4
#define AT91C_PC4_NCS4_CFCS0 ((unsigned int) AT91C_PIO_PC4) //  Chip Select 4 / CompactFlash Chip Select 0
#define AT91C_PIO_PC5        ((unsigned int) 1 <<  5) // Pin Controlled by PC5
#define AT91C_PC5_NCS5_CFCS1 ((unsigned int) AT91C_PIO_PC5) //  Chip Select 5 / CompactFlash Chip Select 1
#define AT91C_PIO_PC6        ((unsigned int) 1 <<  6) // Pin Controlled by PC6
#define AT91C_PC6_CFCE1    ((unsigned int) AT91C_PIO_PC6) //  CompactFlash Chip Enable 1
#define AT91C_PIO_PC7        ((unsigned int) 1 <<  7) // Pin Controlled by PC7
#define AT91C_PC7_CFCE2    ((unsigned int) AT91C_PIO_PC7) //  CompactFlash Chip Enable 2
#define AT91C_PIO_PC8        ((unsigned int) 1 <<  8) // Pin Controlled by PC8
#define AT91C_PC8_TXD0     ((unsigned int) AT91C_PIO_PC8) //  USART0 Transmit Data
#define AT91C_PC8_PCK2     ((unsigned int) AT91C_PIO_PC8) //  PMC Programmable clock Output 2
#define AT91C_PIO_PC9        ((unsigned int) 1 <<  9) // Pin Controlled by PC9
#define AT91C_PC9_RXD0     ((unsigned int) AT91C_PIO_PC9) //  USART0 Receive Data
#define AT91C_PC9_PCK3     ((unsigned int) AT91C_PIO_PC9) //  PMC Programmable clock Output 3

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM9261
// *****************************************************************************
#define AT91C_ID_FIQ    ((unsigned int)  0) // Advanced Interrupt Controller (FIQ)
#define AT91C_ID_SYS    ((unsigned int)  1) // System Interrupt
#define AT91C_ID_PIOA   ((unsigned int)  2) // Parallel IO Controller A
#define AT91C_ID_PIOB   ((unsigned int)  3) // Parallel IO Controller B
#define AT91C_ID_PIOC   ((unsigned int)  4) // Parallel IO Controller C
#define AT91C_ID_US0    ((unsigned int)  6) // USART 0
#define AT91C_ID_US1    ((unsigned int)  7) // USART 1
#define AT91C_ID_US2    ((unsigned int)  8) // USART 2
#define AT91C_ID_MCI    ((unsigned int)  9) // Multimedia Card Interface
#define AT91C_ID_UDP    ((unsigned int) 10) // USB Device Port
#define AT91C_ID_TWI    ((unsigned int) 11) // Two-Wire Interface
#define AT91C_ID_SPI0   ((unsigned int) 12) // Serial Peripheral Interface 0
#define AT91C_ID_SPI1   ((unsigned int) 13) // Serial Peripheral Interface 1
#define AT91C_ID_SSC0   ((unsigned int) 14) // Serial Synchronous Controller 0
#define AT91C_ID_SSC1   ((unsigned int) 15) // Serial Synchronous Controller 1
#define AT91C_ID_SSC2   ((unsigned int) 16) // Serial Synchronous Controller 2
#define AT91C_ID_TC0    ((unsigned int) 17) // Timer Counter 0
#define AT91C_ID_TC1    ((unsigned int) 18) // Timer Counter 1
#define AT91C_ID_TC2    ((unsigned int) 19) // Timer Counter 2
#define AT91C_ID_UHP    ((unsigned int) 20) // USB Host Port
#define AT91C_ID_LCDC   ((unsigned int) 21) // LCD Controller
#define AT91C_ID_IRQ0   ((unsigned int) 29) // Advanced Interrupt Controller (IRQ0)
#define AT91C_ID_IRQ1   ((unsigned int) 30) // Advanced Interrupt Controller (IRQ1)
#define AT91C_ID_IRQ2   ((unsigned int) 31) // Advanced Interrupt Controller (IRQ2)
#define AT91C_ALL_INT   ((unsigned int) 0xE03FFFDF) // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM9261
// *****************************************************************************
#define AT91C_BASE_SYS       ((AT91PS_SYS) 	0xFFFFEA00) // (SYS) Base Address
#define AT91C_BASE_SDRAMC    ((AT91PS_SDRAMC) 	0xFFFFEA00) // (SDRAMC) Base Address
#define AT91C_BASE_SMC       ((AT91PS_SMC) 	0xFFFFEC00) // (SMC) Base Address
//#define AT91C_BASE_MATRIX    ((AT91PS_MATRIX) 	0xFFFFEE00) // (MATRIX) Base Address
extern AT91PS_MATRIX AT91C_BASE_MATRIX;
//#define AT91C_BASE_AIC       ((AT91PS_AIC) 	0xFFFFF000) // (AIC) Base Address
extern AT91PS_AIC AT91C_BASE_AIC;
#define AT91C_BASE_PDC_DBGU  ((AT91PS_PDC) 	0xFFFFF300) // (PDC_DBGU) Base Address
#define AT91C_BASE_DBGU      ((AT91PS_DBGU) 	0xFFFFF200) // (DBGU) Base Address
//#define AT91C_BASE_PIOA      ((AT91PS_PIO) 	0xFFFFF400) // (PIOA) Base Address
#define AT91C_BASE_PIOB      ((AT91PS_PIO) 	0xFFFFF600) // (PIOB) Base Address
#define AT91C_BASE_PIOC      ((AT91PS_PIO) 	0xFFFFF800) // (PIOC) Base Address
#define AT91C_BASE_CKGR      ((AT91PS_CKGR) 	0xFFFFFC20) // (CKGR) Base Address
//#define AT91C_BASE_PMC       ((AT91PS_PMC) 	0xFFFFFC00) // (PMC) Base Address
extern AT91PS_PMC AT91C_BASE_PMC;
#define AT91C_BASE_RSTC      ((AT91PS_RSTC) 	0xFFFFFD00) // (RSTC) Base Address
#define AT91C_BASE_SHDWC     ((AT91PS_SHDWC) 	0xFFFFFD10) // (SHDWC) Base Address
#define AT91C_BASE_RTTC      ((AT91PS_RTTC) 	0xFFFFFD20) // (RTTC) Base Address
#define AT91C_BASE_PITC      ((AT91PS_PITC) 	0xFFFFFD30) // (PITC) Base Address
#define AT91C_BASE_WDTC      ((AT91PS_WDTC) 	0xFFFFFD40) // (WDTC) Base Address
#define AT91C_BASE_TC0       ((AT91PS_TC) 	0xFFFA0000) // (TC0) Base Address
#define AT91C_BASE_TC1       ((AT91PS_TC) 	0xFFFA0040) // (TC1) Base Address
#define AT91C_BASE_TC2       ((AT91PS_TC) 	0xFFFA0080) // (TC2) Base Address
#define AT91C_BASE_TCB0      ((AT91PS_TCB) 	0xFFFA0000) // (TCB0) Base Address
//#define AT91C_BASE_UDP       ((AT91PS_UDP) 	0xFFFA4000) // (UDP) Base Address
extern AT91PS_UDP AT91C_BASE_UDP;
#define AT91C_BASE_PDC_MCI   ((AT91PS_PDC) 	0xFFFA8100) // (PDC_MCI) Base Address
#define AT91C_BASE_MCI       ((AT91PS_MCI) 	0xFFFA8000) // (MCI) Base Address
#define AT91C_BASE_TWI       ((AT91PS_TWI) 	0xFFFAC000) // (TWI) Base Address
#define AT91C_BASE_PDC_US0   ((AT91PS_PDC) 	0xFFFB0100) // (PDC_US0) Base Address
#define AT91C_BASE_US0       ((AT91PS_USART) 	0xFFFB0000) // (US0) Base Address
#define AT91C_BASE_PDC_US1   ((AT91PS_PDC) 	0xFFFB4100) // (PDC_US1) Base Address
#define AT91C_BASE_US1       ((AT91PS_USART) 	0xFFFB4000) // (US1) Base Address
#define AT91C_BASE_PDC_US2   ((AT91PS_PDC) 	0xFFFB8100) // (PDC_US2) Base Address
#define AT91C_BASE_US2       ((AT91PS_USART) 	0xFFFB8000) // (US2) Base Address
#define AT91C_BASE_PDC_SSC0  ((AT91PS_PDC) 	0xFFFBC100) // (PDC_SSC0) Base Address
#define AT91C_BASE_SSC0      ((AT91PS_SSC) 	0xFFFBC000) // (SSC0) Base Address
#define AT91C_BASE_PDC_SSC1  ((AT91PS_PDC) 	0xFFFC0100) // (PDC_SSC1) Base Address
#define AT91C_BASE_SSC1      ((AT91PS_SSC) 	0xFFFC0000) // (SSC1) Base Address
#define AT91C_BASE_PDC_SSC2  ((AT91PS_PDC) 	0xFFFC4100) // (PDC_SSC2) Base Address
#define AT91C_BASE_SSC2      ((AT91PS_SSC) 	0xFFFC4000) // (SSC2) Base Address
#define AT91C_BASE_PDC_SPI0  ((AT91PS_PDC) 	0xFFFC8100) // (PDC_SPI0) Base Address
#define AT91C_BASE_SPI0      ((AT91PS_SPI) 	0xFFFC8000) // (SPI0) Base Address
#define AT91C_BASE_PDC_SPI1  ((AT91PS_PDC) 	0xFFFCC100) // (PDC_SPI1) Base Address
#define AT91C_BASE_SPI1      ((AT91PS_SPI) 	0xFFFCC000) // (SPI1) Base Address
#define AT91C_BASE_UHP       ((AT91PS_UHP) 	0x00500000) // (UHP) Base Address
#define AT91C_BASE_LCDC      ((AT91PS_LCDC) 	0x00600000) // (LCDC) Base Address
#define AT91C_BASE_LCDC_16B_TFT ((AT91PS_LCDC) 	0x00600000) // (LCDC_16B_TFT) Base Address

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM9261
// *****************************************************************************
// ITCM
#define AT91C_ITCM 	 ((char *) 	0x00100000) // Maximum ITCM Area base address
#define AT91C_ITCM_SIZE	 ((unsigned int) 0x00010000) // Maximum ITCM Area size in byte (64 Kbytes)
// DTCM
#define AT91C_DTCM 	 ((char *) 	0x00200000) // Maximum DTCM Area base address
#define AT91C_DTCM_SIZE	 ((unsigned int) 0x00010000) // Maximum DTCM Area size in byte (64 Kbytes)
// IRAM
#define AT91C_IRAM 	 ((char *) 	0x00300000) // Maximum Internal SRAM base address
#define AT91C_IRAM_SIZE	 ((unsigned int) 0x00028000) // Maximum Internal SRAM size in byte (160 Kbytes)
// IRAM_MIN
#define AT91C_IRAM_MIN	 ((char *) 	0x00300000) // Minimum Internal RAM base address
#define AT91C_IRAM_MIN_SIZE	 ((unsigned int) 0x00008000) // Minimum Internal RAM size in byte (32 Kbytes)
// IROM
#define AT91C_IROM 	 ((char *) 	0x00400000) // Internal ROM base address
#define AT91C_IROM_SIZE	 ((unsigned int) 0x00008000) // Internal ROM size in byte (32 Kbytes)
// EBI_CS0
#define AT91C_EBI_CS0	 ((char *) 	0x10000000) // EBI Chip Select 0 base address
#define AT91C_EBI_CS0_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 0 size in byte (262144 Kbytes)
// EBI_CS1
#define AT91C_EBI_CS1	 ((char *) 	0x20000000) // EBI Chip Select 1 base address
#define AT91C_EBI_CS1_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 1 size in byte (262144 Kbytes)
// EBI_SDRAM
#define AT91C_EBI_SDRAM	 ((char *) 	0x20000000) // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_SIZE	 ((unsigned int) 0x10000000) // SDRAM on EBI Chip Select 1 size in byte (262144 Kbytes)
// EBI_SDRAM_16BIT
#define AT91C_EBI_SDRAM_16BIT	 ((char *) 	0x20000000) // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_16BIT_SIZE	 ((unsigned int) 0x02000000) // SDRAM on EBI Chip Select 1 size in byte (32768 Kbytes)
// EBI_SDRAM_32BIT
#define AT91C_EBI_SDRAM_32BIT	 ((char *) 	0x20000000) // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_32BIT_SIZE	 ((unsigned int) 0x04000000) // SDRAM on EBI Chip Select 1 size in byte (65536 Kbytes)
// EBI_CS2
#define AT91C_EBI_CS2	 ((char *) 	0x30000000) // EBI Chip Select 2 base address
#define AT91C_EBI_CS2_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 2 size in byte (262144 Kbytes)
// EBI_CS3
#define AT91C_EBI_CS3	 ((char *) 	0x40000000) // EBI Chip Select 3 base address
#define AT91C_EBI_CS3_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 3 size in byte (262144 Kbytes)
// EBI_SM
#define AT91C_EBI_SM	 ((char *) 	0x40000000) // SmartMedia on Chip Select 3 base address
#define AT91C_EBI_SM_SIZE	 ((unsigned int) 0x10000000) // SmartMedia on Chip Select 3 size in byte (262144 Kbytes)
// EBI_CS4
#define AT91C_EBI_CS4	 ((char *) 	0x50000000) // EBI Chip Select 4 base address
#define AT91C_EBI_CS4_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 4 size in byte (262144 Kbytes)
// EBI_CF0
#define AT91C_EBI_CF0	 ((char *) 	0x50000000) // CompactFlash 0 on Chip Select 4 base address
#define AT91C_EBI_CF0_SIZE	 ((unsigned int) 0x10000000) // CompactFlash 0 on Chip Select 4 size in byte (262144 Kbytes)
// EBI_CS5
#define AT91C_EBI_CS5	 ((char *) 	0x60000000) // EBI Chip Select 5 base address
#define AT91C_EBI_CS5_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 5 size in byte (262144 Kbytes)
// EBI_CF1
#define AT91C_EBI_CF1	 ((char *) 	0x60000000) // CompactFlash 1 on Chip Select 5 base address
#define AT91C_EBI_CF1_SIZE	 ((unsigned int) 0x10000000) // CompactFlash 1 on Chip Select 5 size in byte (262144 Kbytes)
// EBI_CS6
#define AT91C_EBI_CS6	 ((char *) 	0x70000000) // EBI Chip Select 6 base address
#define AT91C_EBI_CS6_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 6 size in byte (262144 Kbytes)
// EBI_CS7
#define AT91C_EBI_CS7	 ((char *) 	0x80000000) // EBI Chip Select 7 base address
#define AT91C_EBI_CS7_SIZE	 ((unsigned int) 0x10000000) // EBI Chip Select 7 size in byte (262144 Kbytes)

#endif
