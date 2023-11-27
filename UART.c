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
char buffer[250];
uint8_t ind;

int main(){
	int fd;
	
	if ((fd = serialOpen ("/dev/ttyS0", 115200)) < 0)
	{
	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	return (-1) ;

	}

	while(1){
		
		if(serialDataAvail(fd)){ //Verifica que hayan datos en el puerto serial
			char recibido = serialGetchar(fd); //guarda los caracteres recibidos en una variable
			buffer[ind++] = recibido; //Se guardan cada caracter en un arreglo
			
			if(recibido == '\n'){//cuando lea un enter es por que ya se envió todo
				
			printf("Esto envió el arduino: %s\n", buffer);// se imprime lo recibido
			
			ind = 0;
			memset(buffer,0,sizeof(buffer)); //se limpia el buffer para volver a recibir datos
			}
		} 

	
		serialPuts(fd,"hola, esto es una prueba del EzPi\n");// se envía un string
		usleep(1000); //tiempo de espera

	}
		serialClose(fd);
        return 0;


}
