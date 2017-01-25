/*
 * author:   
 * file:     test.h
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#ifndef __TEST_H_
#define __TEST_H_


#define ENODEV          0x110
#define ENOBAUD         0x120
#define ENOFILE         0x130

#define BUFFSIZE        1024

#define O_VERBOSE       0x01
#define O_NONEWLINE     0x02
#define O_ENESC         0x04
#define O_EXIT          0x08


/*****************************************************************************
 * I N C L U D E S                                                           *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include "sp_tool.h"
#include "errorhdl.h"


/*****************************************************************************
 * S T R U C T S                                                             *
 *****************************************************************************/



/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/
const char *device = "/dev/tty.PL2303-00002014";
const char *opstr = "vd:b:i:o:nex";



/*****************************************************************************
 * P R O T O T Y P E S                                                       *
 *****************************************************************************/
void int_hdlr(int sig);
speed_t get_baud(int arg);
int main(int argc, char **argv);


#endif