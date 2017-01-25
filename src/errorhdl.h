/*
 * author:   
 * file:     errorhdl.h
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#ifndef __ERRORHDL_H_
#define __ERRORHDL_H_

/*****************************************************************************
 * I N C L U D E S                                                           *
 *****************************************************************************/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>


/*****************************************************************************
 * S T R U C T S                                                             *
 *****************************************************************************/



/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/



/*****************************************************************************
 * P R O T O T Y P E S                                                       *
 *****************************************************************************/
int fprintef(FILE *stream, int num, const char *fmt, ...);
int printef(int num, const char *fmt, ...);
int sprintef(char *str, int num, const char *fmt, ...);
int snprintef(char *str, size_t size, int num, const char *fmt, ...);


#endif