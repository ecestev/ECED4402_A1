/*
 * File: systick.h
 * Source: http://lh.ece.dal.ca/eced4402/SysTick.c
 * Modified By: Stephen Sampson
 * Original Date: 9/25/2017
 * Revised Date:
 * Purpose: SysTick defines and prototypes
 */

// SysTick Registers
// SysTick Control and Status Register (STCTRL)
#define ST_CTRL_R   (*((volatile unsigned long *)0xE000E010))
// Systick Reload Value Register (STRELOAD)
#define ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))

// SysTick defines
#define ST_CTRL_COUNT      0x00010000  // Count Flag for STCTRL
#define ST_CTRL_CLK_SRC    0x00000004  // Clock Source for STCTRL
#define ST_CTRL_INTEN      0x00000002  // Interrupt Enable for STCTRL
#define ST_CTRL_ENABLE     0x00000001  // Enable for STCTRL

// Maximum period
#define MAX_WAIT           0x18B820   /* 2^24 */

/* Global to signal SysTick interrupt */
volatile bool elapsed;
// global variable to count number of interrupts on PORTF0 (falling edge)
volatile int count;

/* SysTick function prototypes */
void SysTickStart(void);
void SysTickStop(void);
void SysTickPeriod(unsigned long Period);
void SysTickIntEnable(void);
void SysTickIntDisable(void);
extern "C" void SysTickHandler(void);


