#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>

int main(){

    int fd;
 if ((fd = serialOpen ("/dev/ttyS0", 115200)) < 0)
{
	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	return 1 ;

}

if (wiringPiSetup () == -1)
 {
	 fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
	 return 1 ;
 }

	while(1){

	
	serialPuts(fd,"hola");
    usleep(2100000);

	}
		serialClose(fd);
        return 0;


}
