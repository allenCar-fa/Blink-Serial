#include <stdio.h>
#include "serialmanager.h"

int main(){
    
    setup_serial(38400,BLOCK);
    char h;
    while(1)
    {	serial_read(&h,1);
	printf("%c\n",h);
    }
}
