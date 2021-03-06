/*
 * File: uart.cpp
 * Source: http://lh.ece.dal.ca/eced4402/Tiva_UART_EchoV1.c
 * Original Author: Emad Khan
 * Modified By: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date:
 * Purpose: UART function definitions.
 */

#include "uart.h"
#include "queue.h"
#include "globals.h"

void UART0_Init(void) {
    volatile int wait;

    /* Initialize UART0 */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCUART_GPIOA;   // Enable Clock Gating for UART0
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCGPIO_UART0;   // Enable Clock Gating for PORTA
    wait = 0; // give time for the clocks to activate

    UART0_CTL_R &= ~UART_CTL_UARTEN;        // Disable the UART
    wait = 0;   // wait required before accessing the UART config regs

    // Setup the BAUD rate
    UART0_IBRD_R = 8;   // IBRD = int(16,000,000 / (16 * 115,200)) = 8.680555555555556
    UART0_FBRD_R = 44;  // FBRD = int(.680555555555556 * 64 + 0.5) = 44.05555555555556

    UART0_LCRH_R = (UART_LCRH_WLEN_8);  // WLEN: 8, no parity, one stop bit, without FIFOs)

    GPIO_PORTA_AFSEL_R = 0x3;        // Enable Receive and Transmit on PA1-0
    GPIO_PORTA_PCTL_R = (0x01) | ((0x01) << 4);         // Enable UART RX/TX pins on PA1-0
    GPIO_PORTA_DEN_R = EN_DIG_PA0 | EN_DIG_PA1;        // Enable Digital I/O on PA1-0

    UART0_CTL_R = UART_CTL_UARTEN;        // Enable the UART
    wait = 0; // wait; give UART time to enable itself.

    processing = false;

}

void InterruptEnable(unsigned long InterruptIndex) {
/* Indicate to CPU which device is to interrupt */
if(InterruptIndex < 32)
    NVIC_EN0_R = 1 << InterruptIndex;       // Enable the interrupt in the EN0 Register
else
    NVIC_EN1_R = 1 << (InterruptIndex - 32);    // Enable the interrupt in the EN1 Register
}

void UART0_IntEnable(unsigned long flags) {
    /* Set specified bits for interrupt */
    UART0_IM_R |= flags;
}


extern "C" void UART0_IntHandler(void) {
/*
 * Simplified UART ISR - handles receive and xmit interrupts
 * Application signalled when data received
 */
    __asm(" cpsid   i");
    if (UART0_MIS_R & UART_INT_RX) {
        /* RECV done - clear interrupt and make char available to application */
        UART0_ICR_R |= UART_INT_RX;
        Data = UART0_DR_R;
        GotData = TRUE;
    }

    if (UART0_MIS_R & UART_INT_TX) {
        /* XMIT done - clear interrupt */
        UART0_ICR_R |= UART_INT_TX;
        if(!UART0_TX_BUFFER.empty()){
            UART0_DR_R = UART0_TX_BUFFER.dequeue();
        }
    }
    __asm(" cpsie   i");
}


void UART0_printf(std::string toprint, bool overwrite) {
    if(overwrite)
        UART0_TX_BUFFER.enqueue('\r');
    for(unsigned i = 0; i < toprint.length(); i++) {
         UART0_TX_BUFFER.enqueue(toprint.at(i));
    }
    if(overwrite)
        UART0_TX_BUFFER.enqueue(' ');
    UART0_DR_R = UART0_TX_BUFFER.dequeue();
}
