#include <stdio.h>
#include "serialmanager.h"

int main(){
    int err;
    err =setup_serial(B38400,BLOCK);
    if (err == -1)
    {
	printf("error occured\n");
	return -1;

    }
    serial_write("hey",3);
    char h;
    while(1)
    {	serial_read(&h,1);
	printf("%c\n",h);
	serial_write(&h, 1);
    }
}
