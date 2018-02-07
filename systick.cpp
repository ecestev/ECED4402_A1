/*
 * File: systick.cpp
 * Source: http://lh.ece.dal.ca/eced4402/SysTick.c
 * Modified By: Stephen Sampson
 * Original Date: 9/25/2017
 * Revised Date:
 * Purpose: Systick function definitions
 */

#include "systick.h"
#include "globals.h"

void SysTickStart(void) {
    // Set the clock source to internal and enable the counter to interrupt
    ST_CTRL_R |= ST_CTRL_CLK_SRC | ST_CTRL_ENABLE;
}

void SysTickStop(void) {
    // Clear the enable bit to stop the counter
    ST_CTRL_R &= ~(ST_CTRL_ENABLE);
}

void SysTickPeriod(unsigned long Period) {
    /*
     For an interrupt, must be between 2 and 16777216 (0x100.0000 or 2^24)
     */
    ST_RELOAD_R = Period - 1;  /* 1 to 0xff.ffff */
}

void SysTickIntEnable(void) {
    // Set the interrupt bit in STCTRL
    ST_CTRL_R |= ST_CTRL_INTEN;
    count = 0;
}

void SysTickIntDisable(void) {
    // Clear the interrupt bit in STCTRL
    ST_CTRL_R &= ~(ST_CTRL_INTEN);
}

extern "C" void SysTickHandler(void) {
    __asm(" cpsid   i");
    elapsed = TRUE;
    count++;
    __asm(" cpsie   i");
}


