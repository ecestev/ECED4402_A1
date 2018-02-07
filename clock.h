/*
 * File: clock.h
 * Author: Stephen Sampson
 * Original Date: 9/23/2017
 * Revised Date: 10/01/2017
 * Purpose: This file contains the structure of the clock class used
 * to create time of day and stopwatch objects.
 */

#pragma once
#include <string>

class clock {
private:
    int HH;                         // var to hold clock's hour value
    int MM;                         // var to hold clock's minute value
    int SS;                         // var to hold clock's second value
    int TEN;                        // var to hold clock's tenths value
    std::string time;               // string to hold formatted clock time
public:
    clock();
    ~clock();
    void set(std::string hour, std::string min, std::string sec);
    void reset(void);
    void update(void);
    void display(void);
};

