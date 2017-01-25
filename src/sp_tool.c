/*
 * author:   
 * file:     sp_tool.c
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#include "sp_tool.h"

/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/



/*****************************************************************************
 * C O D E                                                                   *
 *****************************************************************************/

int serial_port_init(struct serial_port *sp, const char *name) {
        int namelen = strlen(name);
        memset(sp, 0, sizeof(*sp));


        sp->d_name = malloc(namelen * sizeof(char));
        if (sp->d_name == NULL) {
                errno = ENOMEM;
                return SP_NOK;
        }

        memcpy(sp->d_name, name, namelen);
        sp->d_name[namelen] = 0;
        memset(&sp->tty, 0, sizeof(sp->tty));
        
        sp->fd = open(sp->d_name, O_RDWR | O_NOCTTY | O_SYNC);
        // sp->fd = open(sp->d_name, O_RDWR);
        if (sp->fd < 0) {
                errno = ENOFD;
                return SP_NOK;
        }
        if (tcgetattr(sp->fd, &sp->tty) != 0) {
                errno = ETGETATT;
                return SP_NOK;
        }
        return SP_OK;
}

int serial_port_setup(struct serial_port *sp, uint8_t csbits, speed_t baude, uint8_t stop, uint8_t parity) {
        /* disable ignore breaks */
        sp->tty.c_iflag &= ~IGNBRK;
        
        /* disable software flow control */
        sp->tty.c_iflag &= ~(IXON | IXOFF | IXANY);

        /* disable hardware flow control */
        sp->tty.c_cflag &= ~CRTSCTS;

        /* enable reading */
        sp->tty.c_cflag |= CREAD;

        /* ignore modem control lines */
        sp->tty.c_cflag |= CLOCAL;

        /* set bit per byte */
        switch (csbits) {
                case 5:
                        sp->tty.c_cflag = CS5;
                        break;
                case 6:
                        sp->tty.c_cflag = CS6;
                        break;
                case 7:
                        sp->tty.c_cflag = CS7;
                        break;
                case 8:
                default:
                        sp->tty.c_cflag = CS8;
                        break;
        }

        /* set the speed */
        cfsetospeed(&sp->tty, baude);
        cfsetispeed(&sp->tty, baude);

        /* set two stop bits */
        if (stop == STOP_TWO) {
                sp->tty.c_cflag |= CSTOPB;
        } else if (stop == STOP_ONE) {
                sp->tty.c_cflag &= ~CSTOPB;
        } else {
                errno = EINVAL;
                return SP_NOK;
        }

        /* set no parity */
        sp->tty.c_cflag &= ~(PARENB | PARODD);

        switch (parity) {
                case 0:
                        break;
                case 1:
                        sp->tty.c_cflag |= PARENB;
                case 2:
                        sp->tty.c_cflag |= PARODD;
                        break;
                default:
                        errno = EINVAL;
                        return SP_NOK;
                        break;
        }

        sp->tty.c_cc[VMIN] = 0;                          /* noneblocking read */
        sp->tty.c_cc[VTIME] = 5;                         /* 0.5 secs read timeout */

        return SP_OK;
}

int serial_port_check_setup(struct serial_port *sp) {
        int e;
        if ((e = tcsetattr(sp->fd, TCSANOW, &sp->tty)) != 0) {
                errno = ETGETATT;
                return SP_NOK;
        }
        return SP_OK;
}

int serial_port_write(struct serial_port *sp, unsigned char *data, size_t len) {
        return write(sp->fd, data, len);
}

int serial_port_read(struct serial_port *sp, unsigned char *buff, size_t len) {
        return read(sp->fd, buff, len);
}

int serial_port_close(struct serial_port *sp) {
        return close(sp->fd);
}