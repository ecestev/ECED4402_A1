/*
 * File: globals.h
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date:
 * Purpose: This file contains external declarations for global variables/objects
 * as well as state enumerations and defines.
 */

#pragma once
#include "clock.h"
#include "queue.h"

extern queue UART0_TX_BUFFER;
extern queue UART0_RX_BUFFER;

extern int state;   // 0 = Monitor, 1 = Display Current Time, 2 = Stopwatch
extern clock tod, stopwatch;

#define TRUE    1
#define FALSE   0

enum states{MONITOR, TIME, STOPWATCH};



