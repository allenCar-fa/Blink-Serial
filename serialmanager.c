#include "serialmanager.h"


//For Nanopi M1 Uart 1
#define PORT "/dev/ttyS1"

// For Raspberry pi
//#define PORT "/dev/serial0"

struct termios config;

int fd;


int setup_serial(int baud_rate, int block){
    set_baudrate(baud_rate);

    if(block == UNBLOCK)
	fd = open(PORT,O_RDWR | O_NOCTTY | O_NONBLOCK);
    else
	fd = open(PORT,O_RDWR | O_NOCTTY);
  
    if(fd == -1)
	return -1;

      printf("Port openned\n");
    
    if(tcgetattr(fd,&config) < 0 )
	return -1;

    printf("attribute set \n");
    
    config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                     INLCR | PARMRK | INPCK | ISTRIP | IXON);
    config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    config.c_cflag &= ~(CSIZE | PARENB);
    config.c_cflag |= CS8;
    config.c_cc[VMIN]  = 1;
    config.c_cc[VTIME] = 0;

    if(cfsetispeed(&config, BAUD_RATE) < 0 || cfsetospeed(&config, BAUD_RATE) < 0)
	return -1;

    printf("speed set\n");
    
    if(tcsetattr(fd, TCSAFLUSH, &config) < 0)
	return -1;
    tcflush(fd, TCIOFLUSH);

    printf("conf set\n");
    return 0;
}


// returns 0 if no characters available and -1 if error occured 
ssize_t serial_read(char *buff,int buff_size){
    ssize_t err;
    err = read(fd,buff,buff_size);
    
    return err;
}


//returns -1 if error occured and else for numbered of written characters
ssize_t serial_write(char *buff,int buff_size){
    ssize_t err;
    err = write(fd,buff,buff_size);
    tcdrain(fd);
    fsync(fd);
    return err;
}
