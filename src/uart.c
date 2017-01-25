/*
 * author:   
 * file:     uart.c
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#include "uart.h"

/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/
struct serial_port sps[MAX_UARTS];
int pos = 0;


/*****************************************************************************
 * C O D E                                                                   *
 *****************************************************************************/
int uart_open(const char *dev) {
        int err;
        if (pos == MAX_UARTS)
                return -1;
        err = serial_port_init(&sps[pos], dev);
        if (err == SP_NOK)
                return -1;
        err = serial_port_setup(&sps[pos], 8, B9600, STOP_ONE, PARITY_NONE);
        if (err == SP_NOK)
                return -1;
        err = serial_port_check_setup(&sps[pos]);
        if (err == SP_NOK)
                return -1;
        pos++;
        return pos-1;
}

int uart_write(int hdl, uint8_t *dat, size_t len) {
        if (hdl >= pos)
                return -1;
        return serial_port_write(&sps[hdl], dat, len);
}

int uart_read(int hdl, uint8_t *dat, size_t len) {
        if (hdl >= pos)
                return -1;
        return serial_port_read(&sps[hdl], dat, len);
}

int uart_close(int hdl) {
        if (hdl >= pos)
                return -1;
        return serial_port_close(&sps[hdl]);
}

int uart_dbug_pos(void) {
        return pos;
}