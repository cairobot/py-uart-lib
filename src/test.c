/*
 * author:   
 * file:     test.c
 * version:  0.0.0-r0
 * since:    
 * desc:
 */

#include "test.h"

/*****************************************************************************
 * V A R I A B L E S                                                         *
 *****************************************************************************/
struct {
        struct serial_port *sp;
        uint8_t flags;
        char *device;
        speed_t baud;
        FILE *infile;
        FILE *outfile;
        uint8_t readbuff[BUFFSIZE];
} options = {
        .sp = NULL,
        .flags = 0,
        .device = NULL,
        .baud = B0,
        .infile = NULL,
        .outfile = NULL,
};

/*****************************************************************************
 * C O D E                                                                   *
 *****************************************************************************/

void int_hdlr(int sig) {
        signal(sig, SIG_IGN);
        if (options.sp != NULL) {
                if (options.sp->fd >= 0) {
                        close(options.sp->fd);
                }
        }
        exit(0);
}

speed_t get_baud(int arg) {
        switch (arg) {
                default:
                case 0:
                        return B0;
                case 50:
                        return B50;
                case 75:
                        return B75;
                case 110:
                        return B110;
                case 134:
                        return B134;
                case 150:
                        return B150;
                case 200:
                        return B200;
                case 300:
                        return B300;
                case 600:
                        return B600;
                case 1200:
                        return B1200;
                case 1800:
                        return B1800;
                case 2400:
                        return B2400;
                case 4800:
                        return B4800;
                case 9600:
                        return B9600;
                case 19200:
                        return B19200;
                case 38400:
                        return B38400;
        }
}

int main(int argc, char **argv) {
        int c, rd, err;
        uint8_t rd0;
        uint8_t esc = 0;

        // signal(SIGINT, &int_hdlr);
        struct sigaction act;
        act.sa_handler = &int_hdlr;
        sigaction(SIGINT, &act, NULL);


        for (int i = 0; i < argc; i++) {
                printf("a %d: %s\n", i, argv[i]);
        }


        while ((c = getopt(argc, argv, opstr)) != -1) {
                switch(c) {
                        case 0:
                        default:
                                break;
                        case 'v':
                                options.flags |= O_VERBOSE;
                                break;
                        case 'd':
                                options.device = malloc(strlen(optarg));
                                memcpy(options.device, optarg, strlen(optarg));
                                break;
                        case 'b':
                                options.baud = get_baud(atoi(optarg));
                                break;
                        case 'i':
                                if (strcmp("-", optarg) == 0)
                                        break;
                                else
                                        options.infile = fopen(optarg, "r");
                                if (options.infile == NULL)
                                        printef(errno, "failed to open infile: %s\n", optarg);
                                break;
                        case 'o':
                                if (strcmp("-", optarg) == 0)
                                        break;
                                else
                                        options.outfile = fopen(optarg, "w");
                                if (options.outfile == NULL)
                                        printef(errno, "failed to open outfile: %s\n", optarg);
                                break;
                        case 'n':
                                options.flags |= O_NONEWLINE;
                                break;
                        case 'e':
                                options.flags |= O_ENESC;
                                break;
                        case 'x':
                                options.flags |= O_EXIT;
                                break;


                }
        }

        /* ensure input infile associated */
        if (options.infile == NULL) {
                options.infile = stdin;
        }

        /* ensure output file is associated */
        if (options.outfile == NULL) {
                options.outfile = stdout;
        }

        /* ensure device specified */
        if (options.device == NULL) {
                err = ENODEV;
                printef(err, "no device specified\n");
                return err;
        }

        /* ensure baud specified */
        if (options.baud == B0) {
                err = ENOBAUD;
                printef(err, "no baud rate specified\n");
                return err;
        }

        /* ensure input infile not null */
        if (options.infile == NULL) {
                err = ENOFILE;
                printef(err, "no input infile specified\n");
                return err;
        }

        /* allocate space for the serial_port struct */
        options.sp = malloc(sizeof(struct serial_port));

        /* init port */
        if (serial_port_init(options.sp, options.device) == SP_NOK) {
                err = errno;
                printef(err, "failed to initialize serial port\n");
                return err;
        }

        /* setup port */
        if (serial_port_setup(options.sp, 8, options.baud, STOP_ONE, PARITY_NONE) == SP_NOK) {
                err = errno;
                printef(err, "failed to set up serial port\n");
                return err;
        }

        /* commit setup */
        if (serial_port_check_setup(options.sp) == SP_NOK) {
                err = errno;
                printef(err, "failed to commit changes to port\n");
                return err;
        }

        while (1) {
                if ((rd = fgetc(options.infile)) != EOF) {
                        rd0 = (uint8_t)(rd & 0xff);
                        if ((options.flags & O_NONEWLINE) && (rd0 == '\n')) {
                                continue;
                        } else if ((esc == 0) && (options.flags & O_ENESC) && (rd0 == '\\')) {
                                /* we escaped with \ */
                                esc = 1;
                        } else if (esc) {
                                esc = 0;
                        }
                        serial_port_write(options.sp, &rd0, 1);
                }
                rd = serial_port_read(options.sp, options.readbuff, BUFFSIZE);
                if (rd > 0) {
                        options.readbuff[rd] = 0;
                        fprintf(options.outfile, "%s", options.readbuff);
                        fflush(options.outfile);
                }
                if (options.flags & O_EXIT)
                        break;
        }
        if (options.sp != NULL) {
                if (options.sp->fd >= 0) {
                        close(options.sp->fd);
                }
        }
}