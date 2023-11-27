
/**************************************************************************************************************************************************/
// DAC.c
//Basado en el código por: Luis Alberto Rivera
//Adaptado y comentado por: Francisco José Montúfar Gudiel
//Programa que configura la comunicación SPI entre la Rasbperry Pi (maestro)
//y un conversor D/A MCP4921 (esclavo), y continuamente manda 2 bytes.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h> 
#include <wiringPi.h>
#include <wiringPiSPI.h>
#define SPI_CANAL 1 // Canal SPI de la Raspberry Pi, 0 ó 1
#define SPI_VEL 15000000// Velocidad de la comunicación SPI (reloj, en HZ)  Máx de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V

uint16_t inf; //variable para configuración DAC
uint16_t SPI_manda_recibe(uint16_t); // Prototipo


int main(void)
{
uint16_t a_enviar = 0, recibido; // variables de 2 bytes


if(wiringPiSPISetup(SPI_CANAL, SPI_VEL) < 0) {//Se inicializa el SPI de WiringPi
printf("wiringPiSPISetup falló\n");
return(-1) ;
}


while(1)
{
a_enviar++; //Datos a enviar al conversor D/A, un contador ascendente.

if(a_enviar > 4095){ //Como el conversor es de 12 bits, se limita a que cuando el contador llegue a 4095, se reinicie
    a_enviar = 0;    //Esto forma una señal diente de sierra
}
recibido = SPI_manda_recibe(a_enviar); // Devuelve los datos generados en la función
printf("Rec: 0x%04X\n", recibido); //Se despliegan los datos en Hexadecimal para verificar que es lo que se está enviando
usleep(100); //Frecuencia del diente de sierra 
fflush(stdout);//Se limpia buffer de salida

}
return 0;
}

uint16_t SPI_manda_recibe(uint16_t valor)//Función para configurar el MCP4921 y enviar los datos 

{

uint8_t dato[2]; // buffer para la comunicación por SPI
uint16_t resultado1;

//Se realiza un or entre una variable de 2 bytes y el parametro de la función para dejar los primeros 4 bits de configuración fijos
inf = 0b0111000000000000 | valor; 

//Se separa variable de 16 bits en dos variables de 1 byte c/u
dato[0] = (0b00000000 | (inf >> 8)); //Or con el byte más significativo para tener los  4 bits de configuración y 4 bits de datos
dato[1] = (0b00000000 | inf); //Or con el byte menos significativo para tener los restantes 8 bits de datos


wiringPiSPIDataRW(SPI_CANAL, dato, 2); //Se envían 2 bytes por SPI

return(inf);
}




