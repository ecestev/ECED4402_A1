/*
 * File: clock.cpp
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date: 10/01/2017
 * Purpose: This file contains the structure of the clock class used
 * to create time of day and stopwatch objects.
 */

#include <clock.h>
#include "globals.h"
#include "uart.h"
#include <sstream>
#include <stdio.h>

/* Constructor - Initialize Object Vars */
clock::clock() {
    HH = 0;
    MM = 0;
    SS = 0;
    TEN = 0;
    time = "";
}

/* Member function to set object's hour, minute, and second variables */
void clock::set(std::string hour, std::string min, std::string sec){
    sscanf(hour.c_str(), "%d", &HH);
    sscanf(min.c_str(), "%d", &MM);
    sscanf(sec.c_str(), "%d", &SS);
}

/* Member function to reset object's private variables */
void clock::reset(void){
    HH = 0;
    MM = 0;
    SS = 0;
    TEN = 0;
    time = "";
}

/* Member function to update object's hour, minute, and second variables.
 * This function is called on SysTick event */
void clock::update(void){
    TEN++;
        if(TEN>9){
            TEN = 0;
            SS ++;
        }

        if(SS>59){
            SS = 0;
            MM ++;
        }
        if(MM>59){
            MM = 0;
            HH ++;
        }
        if(HH>23){
            SS = 0;
            MM = 0;
            HH = 0;
        }
}

/* Member function to display formatted string containing objects hour,
 * minute, second, and tenths variables separated by appropriate punctuation */
void clock::display(void){
    std::stringstream todss;
    todss << HH << ":" << MM << ":" << SS << "." << TEN;
    todss >> time;
    UART0_printf(time, true);
}

/* destructor */
clock::~clock(){

}


