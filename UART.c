/**************************************************************************************************************************************************/
// UART.c
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite el uso del protocolo UART utilizando la  Rasbperry Pi.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/

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
wiringPiSetup();

if ((fd = serialOpen ("/dev/ttyS0", 115200)) < 0) { //Se abre el puerto serial ttyS0
	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	return (-1) ;

}

	while(1){

	serialPuts(fd,"hola");//se envía un string
    usleep(2000000);//
	}

	serialClose(fd);// se cierra el puerto serial
    return 0;
}
