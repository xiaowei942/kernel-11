/*
 * arch/arm/mach-at91/pm_slow_clock.S
 *
 *  Copyright (C) 2006 Savin Zlobec
 *
 * AT91SAM9 support:
 *  Copyright (C) 2007 Anti Sullin <anti.sullin@artecdesign.ee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/linkage.h>
#include <asm/hardware.h>
#include <asm/arch/at91_pmc.h>

#ifdef CONFIG_ARCH_AT91RM9200
#include <asm/arch/at91rm9200_mc.h>
#elif defined(CONFIG_ARCH_AT91CAP9)
#include <asm/arch/at91cap9_ddrsdr.h>
#else
#include <asm/arch/at91sam926x_sdramc.h>
#endif

/*
 * When SLOWDOWN_MASTER_CLOCK is defined we will also slow down the Master
 * clock during suspend by adjusting its prescalar and divisor.
 * NOTE: This hasn't been shown to be stable on SAM9s; and on the RM9200 there
 *       are errata regarding adjusting the prescalar and divisor.
 */
#undef SLOWDOWN_MASTER_CLOCK

#define MCKRDY_TIMEOUT		1000
#define MOSCRDY_TIMEOUT 	1000
#define PLLALOCK_TIMEOUT	1000
#define PLLBLOCK_TIMEOUT	1000


/*
 * Wait until master clock is ready (after switching master clock source)
 */
	.macro wait_mckrdy
	mov	r4, #MCKRDY_TIMEOUT
1:	sub	r4, r4, #1
	cmp	r4, #0
	beq	2f
	ldr	r3, [r1, #(AT91_PMC_SR - AT91_PMC)]
	tst	r3, #AT91_PMC_MCKRDY
	beq	1b
2:
	.endm

/*
 * Wait until master oscillator has stabilized.
 */
	.macro wait_moscrdy
	mov	r4, #MOSCRDY_TIMEOUT
1:	sub	r4, r4, #1
	cmp	r4, #0
	beq	2f
	ldr	r3, [r1, #(AT91_PMC_SR - AT91_PMC)]
	tst	r3, #AT91_PMC_MOSCS
	beq	1b
2:
	.endm

/*
 * Wait until PLLA has locked.
 */
	.macro wait_pllalock
	mov	r4, #PLLALOCK_TIMEOUT
1:	sub	r4, r4, #1
	cmp	r4, #0
	beq	2f
	ldr	r3, [r1, #(AT91_PMC_SR - AT91_PMC)]
	tst	r3, #AT91_PMC_LOCKA
	beq	1b
2:
	.endm

/*
 * Wait until PLLB has locked.
 */
	.macro wait_pllblock
	mov	r4, #PLLBLOCK_TIMEOUT
1:	sub	r4, r4, #1
	cmp	r4, #0
	beq	2f
	ldr	r3, [r1, #(AT91_PMC_SR - AT91_PMC)]
	tst	r3, #AT91_PMC_LOCKB
	beq	1b
2:
	.endm

	.text

ENTRY(at91_slow_clock)
	/* Save registers on stack */
	stmfd	sp!, {r0 - r12, lr}

	/*
	 * Register usage:
	 *  R1 = Base address of AT91_PMC
	 *  R2 = Base address of AT91_SDRAMC (or AT91_SYS on AT91RM9200)
	 *  R3 = temporary register
	 *  R4 = temporary register
	 */
	ldr	r1, .at91_va_base_pmc
	ldr	r2, .at91_va_base_sdramc

	/* Drain write buffer */
	mcr	p15, 0, r0, c7, c10, 4

#ifdef CONFIG_ARCH_AT91RM9200
	/* Put SDRAM in self-refresh mode */
	mov	r3, #1
	str	r3, [r2, #AT91_SDRAMC_SRR]
#elif defined(CONFIG_ARCH_AT91CAP9)
	/* Enable SDRAM self-refresh mode */
	ldr	r3, [r2, #AT91_DDRSDRC_LPR - AT91_DDRSDRC]
	str	r3, .saved_sam9_lpr

	mov	r3, #AT91_DDRSDRC_LPCB_SELF_REFRESH
	str	r3, [r2, #AT91_DDRSDRC_LPR - AT91_DDRSDRC]
#else
	/* Enable SDRAM self-refresh mode */
	ldr	r3, [r2, #AT91_SDRAMC_LPR - AT91_SDRAMC]
	str	r3, .saved_sam9_lpr

	mov	r3, #AT91_SDRAMC_LPCB_SELF_REFRESH
	str	r3, [r2, #AT91_SDRAMC_LPR - AT91_SDRAMC]
#endif

	/* Save Master clock setting */
	ldr	r3, [r1, #(AT91_PMC_MCKR - AT91_PMC)]
	str	r3, .saved_mckr

	/*
	 * Set the Master clock source to slow clock
	 */
	bic	r3, r3, #AT91_PMC_CSS
	str	r3, [r1, #(AT91_PMC_MCKR - AT91_PMC)]

	wait_mckrdy

#ifdef SLOWDOWN_MASTER_CLOCK
	/*
	 * Set the Master Clock PRES and MDIV fields.
	 *
	 * See AT91RM9200 errata #27 and #28 for details.
	 */
	mov	r3, #0
	str	r3, [r1, #(AT91_PMC_MCKR - AT91_PMC)]

	wait_mckrdy
#endif

	/* Save PLLA setting and disable it */
	ldr	r3, [r1, #(AT91_CKGR_PLLAR - AT91_PMC)]
	str	r3, .saved_pllar

	mov	r3, #AT91_PMC_PLLCOUNT
	orr	r3, r3, #(1 << 29)		/* bit 29 always set */
	str	r3, [r1, #(AT91_CKGR_PLLAR - AT91_PMC)]

	wait_pllalock

	/* Save PLLB setting and disable it */
	ldr	r3, [r1, #(AT91_CKGR_PLLBR - AT91_PMC)]
	str	r3, .saved_pllbr

	mov	r3, #AT91_PMC_PLLCOUNT
	str	r3, [r1, #(AT91_CKGR_PLLBR - AT91_PMC)]

	wait_pllblock

	/* Turn off the main oscillator */
	ldr	r3, [r1, #(AT91_CKGR_MOR - AT91_PMC)]
	bic	r3, r3, #AT91_PMC_MOSCEN
	str	r3, [r1, #(AT91_CKGR_MOR - AT91_PMC)]

	/* Wait for interrupt */
	mcr	p15, 0, r0, c7, c0, 4

	/* Turn on the main oscillator */
	ldr	r3, [r1, #(AT91_CKGR_MOR - AT91_PMC)]
	orr	r3, r3, #AT91_PMC_MOSCEN
	str	r3, [r1, #(AT91_CKGR_MOR - AT91_PMC)]

	wait_moscrdy

	/* Restore PLLB setting */
	ldr	r3, .saved_pllbr
	str	r3, [r1, #(AT91_CKGR_PLLBR - AT91_PMC)]

	wait_pllblock

	/* Restore PLLA setting */
	ldr	r3, .saved_pllar
	str	r3, [r1, #(AT91_CKGR_PLLAR - AT91_PMC)]

	wait_pllalock

#ifdef SLOWDOWN_MASTER_CLOCK
	/*
	 * First set PRES if it was not 0,
	 * than set CSS and MDIV fields.
	 *
	 * See AT91RM9200 errata #27 and #28 for details.
	 */
	ldr	r3, .saved_mckr
	tst	r3, #AT91_PMC_PRES
	beq	2f
	and	r3, r3, #AT91_PMC_PRES
	str	r3, [r1, #(AT91_PMC_MCKR - AT91_PMC)]

	wait_mckrdy
#endif

	/*
	 * Restore master clock setting
	 */
2:	ldr	r3, .saved_mckr
	str	r3, [r1, #(AT91_PMC_MCKR - AT91_PMC)]

	wait_mckrdy

#ifdef CONFIG_ARCH_AT91RM9200
	/* Do nothing - self-refresh is automatically disabled. */
#elif defined(CONFIG_ARCH_AT91CAP9)
	/* Restore LPR on AT91CAP9 */
	ldr	r3, .saved_sam9_lpr
	str	r3, [r2, #AT91_DDRSDRC_LPR - AT91_DDRSDRC]
#else
	/* Restore LPR on AT91SAM9 */
	ldr	r3, .saved_sam9_lpr
	str	r3, [r2, #AT91_SDRAMC_LPR - AT91_SDRAMC]
#endif

	/* Restore registers, and return */
	ldmfd	sp!, {r0 - r12, pc}


.saved_mckr:
	.word 0

.saved_pllar:
	.word 0

.saved_pllbr:
	.word 0

.saved_sam9_lpr:
	.word 0

.at91_va_base_pmc:
	.word AT91_VA_BASE_SYS + AT91_PMC

#ifdef CONFIG_ARCH_AT91RM9200
.at91_va_base_sdramc:
	.word AT91_VA_BASE_SYS
#elif defined(CONFIG_ARCH_AT91CAP9)
.at91_va_base_sdramc:
	.word AT91_VA_BASE_SYS + AT91_DDRSDRC
#else
.at91_va_base_sdramc:
	.word AT91_VA_BASE_SYS + AT91_SDRAMC
#endif

ENTRY(at91_slow_clock_sz)
	.word .-at91_slow_clock
