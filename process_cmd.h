/**
 * File: process_cmd.h
 * Author: Stephen Sampson
 * Original Date: 9/24/2017
 * Revised Date:
 * Purpose:
 */

#pragma once
#include <string>
enum CMD_PROCESS_CODES { CMDLINE_BAD_CMD = -1, CMD_SUCCESS};

typedef int (*pfnCmdLine)(int argc, std::string arg);

/* Structure for an entry in the command list table. Adapted from TI Library "utils/cmdline.h" */
typedef struct {
    const char *pcCmd;
    pfnCmdLine pfnCmd;
    const int args;
} tCmdLineEntry;

/* Prototypes */
int CMD_Process(void);
extern int CMD_help (int argc, std::string arg);
extern int CMD_time (int argc, std::string arg);
extern int CMD_set (int argc, std::string arg);
extern int CMD_go(int argc, std::string arg);
extern int CMD_cls(int argc, std::string arg);

