/*
 * File: main.cpp
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date: 10/01/2017
 * Purpose: This file contains the main program flow for the simple monitor.
 */

#include "uart.h"
#include "systick.h"
#include "queue.h"
#include "globals.h"
#include "process_cmd.h"
#include "clock.h"

/* Create UART RX and TX Buffers */
queue UART0_TX_BUFFER(512);
queue UART0_RX_BUFFER(128);

/* Create Time-of-day and Stopwatch Objects */
clock tod, stopwatch;

/* Start in Monitor Mode */
int state = MONITOR;

void main(void) {

    /* Initialize UART */
    UART0_Init();                               // Initialize UART0
    InterruptEnable(INT_VEC_UART0);             // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts

    /* Initialize SYSTICK */
    SysTickPeriod(MAX_WAIT);                    // Set SysTick Period
    SysTickIntEnable();                         // Enable SysTick Interrupts
    SysTickStart();                             // Set Clock Source and Enable Counter

    /* Enable Interrupts */
    __asm(" cpsie   i");                        // Enable Master (CPU) Interrupts

    /* Print Welcome Banner */
    UART0_printf("\n\n\r-------------------------------\n\r"
            "ECED4402 - Real Time Systems\n\r"
            "Assignment #1 - A Simple Monitor\n\r"
            "Stephen Sampson B00568374\n\r"
            "Fall 2017\n\r"
            "-------------------------------\n\n\n\r", false);

    /* Main Program Execution */
    while(1) {
        GotData = FALSE;
        elapsed = FALSE;
        while (!GotData && !elapsed) ;
        /* Control broke from while loop due to a character being input */
        if(GotData){
            state = MONITOR;
            /* If enter was pressed, start building string from RX queue */
            if(Data == '\r'){
                /* See if string exists within CmdTable and call appropriate handler */
                CMD_Process();
                /* Otherwise, enter was not pressed, echo char and continue adding input characters to queue */
            } else {
                UART0_DR_R = Data;
                UART0_RX_BUFFER.enqueue(Data);
            }
        /* Control broke from while loop due to a SysTick interrupt (exception) */
        } else {
            // Update current time-of-day
            tod.update();
            switch(state){
            case TIME:         // Display Current Time
                tod.display();
                break;
            case STOPWATCH:   // Update and Display Stopwatch
                stopwatch.update();
                stopwatch.display();
                break;
            default:         // Do nothing, Monitor Mode
                break;
            }
        }
    }
}
