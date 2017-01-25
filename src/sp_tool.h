/*
 * author:   
 * file:     sp_tool.h
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#ifndef __SP_TOOL_H_
#define __SP_TOOL_H_

#define SP_NOK          0
#define SP_OK           1


#define STOP_ONE        0
#define STOP_TWO        1

#define PARITY_NONE     0
#define PARITY_EVEN     1
#define PARITY_ODD      2

#define ENOFD           0x101
#define ETGETATT        0x102


/*****************************************************************************
 * I N C L U D E S                                                           *
 *****************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


/*****************************************************************************
 * S T R U C T S                                                             *
 *****************************************************************************/
struct serial_port {
        char *d_name;
        int fd;
        struct termios tty;
};


/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/



/*****************************************************************************
 * P R O T O T Y P E S                                                       *
 *****************************************************************************/
int serial_port_init(struct serial_port *sp, const char *name);
int serial_port_setup(struct serial_port *sp, uint8_t csbits, speed_t baude, uint8_t stop, uint8_t parity);
int serial_port_check_setup(struct serial_port *sp);
int serial_port_write(struct serial_port *sp, unsigned char *data, size_t len);
int serial_port_read(struct serial_port *sp, unsigned char *buff, size_t len);
int serial_port_close(struct serial_port *sp);

#endif