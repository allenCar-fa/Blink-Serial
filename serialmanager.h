#ifndef __SERIAL_MANAGER__
#define __SERIAL_MANAGER__

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int BAUD_RATE;

#define set_baudrate(A) BAUD_RATE = A;

#define BLOCK 1
#define UNBLOCK 0

int setup_serial(int baud_rate, int block);
ssize_t serial_read(char *buff,int buff_size);
ssize_t serial_write(char *buff,int buff_size);

#define serial_readch(A) serial_read(A,1)

#endif
