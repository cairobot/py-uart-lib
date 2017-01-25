/*
 * author:   
 * file:     errorhdl.c
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#include "errorhdl.h"

/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/
const char *errpat = "Error [%04x]: ";


/*****************************************************************************
 * C O D E                                                                   *
 *****************************************************************************/
int fprintef(FILE *stream, int num, const char *fmt, ...) {
        int ret;
        fprintf(stream, errpat, num);
        va_list args;
        va_start(args, fmt);
        ret = vfprintf(stream, fmt, args);
        va_end(args);
        return ret;
}

int printef(int num, const char *fmt, ...) {
        int ret;
        fprintf(stderr, errpat, num);
        va_list args;
        va_start(args, fmt);
        ret = vfprintf(stderr, fmt, args);
        va_end(args);
        return ret;
}

int sprintef(char *str, int num, const char *fmt, ...);
int snprintef(char *str, size_t size, int num, const char *fmt, ...);