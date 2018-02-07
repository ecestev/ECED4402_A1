/*
 * File: process_cmd.cpp
 * Author: Stephen Sampson
 * Original Date: 9/24/2017
 * Revised Date:
 * Purpose:
 */

#include "process_cmd.h"
#include "globals.h"
#include "uart.h"
#include <stdio.h>
#include <ctype.h>


/* Table of valid command strings, callback functions and argument parameters */
tCmdLineEntry CmdTable[] =
{
    {"HELP",    CMD_help,   0},
    {"TIME",    CMD_time,   0},
    {"SET",     CMD_set,    1},
    {"GO",      CMD_go,     0},
    {"CLS",     CMD_cls,    0},
    { 0, 0, 0 }
};


int CMD_Process(void) {
    std::string to_parse;
    std::string cmd = "";
    std::string arg = "";
    int pos = 0;
    int num_args = 0;
    int len = 0;
    tCmdLineEntry *CmdEntry;

    /* Build string from UART0 RX Buffer */
    while(!UART0_RX_BUFFER.empty()){
        to_parse += toupper(UART0_RX_BUFFER.dequeue());
    }

    /* Count number of spaces in UART0 RX Buffer */
    for(unsigned i = 0; i < to_parse.length(); i++) {
        if(to_parse.at(i) == ' '){
            if(pos == 0){
                pos = i;
            }
            num_args++;
        }
    }

    len = to_parse.length();
    if(pos>0){
        cmd = to_parse.substr(0,pos);
        arg = to_parse.substr(pos+1, len);
    } else {
        cmd = to_parse;
    }

    CmdEntry = &CmdTable[0];
    while(CmdEntry->pcCmd){
        if(cmd == CmdEntry->pcCmd && num_args == CmdEntry->args){
            return(CmdEntry->pfnCmd(num_args, arg));
        }
        CmdEntry++;
    }
    UART0_printf("\n\rInvalid Command: ", false);
    UART0_printf(cmd, false);
    UART0_printf("\n\r", false);
    return CMDLINE_BAD_CMD;
}


int CMD_help(int argc, std::string arg) {
    UART0_printf("\n \n "
            "\r------------------------------- \n \r"
            "Available Commands: \n \r"
            "------------------------------- \n \r"
            " help  : Display list of commands. \n \r"
            " time  : Display current time-of-day HH:MM:SS.t. \n \r"
            " set   : Set current time-of-day HH:MM:SS. \n \r"
            " go    : Start the stopwatch. \n \r"
            " cls   : Clear the terminal screen \n \n \r", false);

    return CMD_SUCCESS;
}

int CMD_time(int argc, std::string arg) {
    UART0_printf("\n\rDisplaying Current Time-Of-Day \n \r", false);
    state = TIME;
    return CMD_SUCCESS;
}

int CMD_set(int argc, std::string arg) {
    UART0_printf("\n\rSetting Time of Day \n \r", false);
    std::string hr = "", min = "", sec = "";
    int pos = 0;
    int len = arg.length();

    for(unsigned i = 0; i < len; i++)
        if(arg.at(i) == ':'){
            pos = i;
            break;
        }

    hr = arg.substr(0,pos);
    arg = arg.substr(pos+1, len);

    len = arg.length();

    for(unsigned i = 0; i < len; i++)
        if(arg.at(i) == ':'){
            pos = i;
            break;
        }

    min = arg.substr(0,pos);
    sec = arg.substr(pos+1, len);

    tod.set(hr, min, sec);

    state = MONITOR;

    return CMD_SUCCESS;
}

int CMD_go(int argc, std::string arg) {
    UART0_printf("\n\rStarting Stopwatch... \n \r", false);
    state = STOPWATCH;
    stopwatch.reset();
    return CMD_SUCCESS;
}


int CMD_cls(int argc, std::string arg) {
    UART0_printf("\033c", false);
    return CMD_SUCCESS;
}
