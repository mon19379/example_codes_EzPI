/**************************************************************************************************************************************************/
// ADC.c
// Basado en la adaptación de Dr. Luis Alberto Rivera del código tomado de: https://projects.drogon.net/raspberry-pi/wiringpi/
//Adaptado y comentado por: Francisco José Montúfar Gudiel
//Programa que configura la comunicación SPI entre la Rasbperry Pi (maestro)
//y un conversor A/D MCP3002 (esclavo), y continuamente manda y recibe 2 bytes.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>


#define SPI_CHANNEL	      0	// Canal SPI, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)  Máx de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define arch "archivo.csv"	//se define archivo .CSV                      
#define ADC_CHANNEL    1   	// Canal A/D del MCP3002, 0 ó 1
char buffer[5]; //buffer de datos
uint16_t get_ADC(int channel); //Prototipo de función
uint16_t leds[] = {2,3,5,4}; //Arreglo con los numeros de pin de las LEDS
uint16_t val; /// Variable para mapeo

int main(void)
{
    uint16_t ADCvalue; //Variable para valor de ADC
    wiringPiSetup(); //Se inicializa WiringPi
    pinMode(2, OUTPUT);//Pin 2 wiring pi como salida (LED1)
    pinMode(3, OUTPUT);//Pin 3 wiring pi como salida (LED2)
    pinMode(4, OUTPUT);//Pin 4 wiring pi como salida (LED4)
    pinMode(5, OUTPUT);//Pin 5 wiring pi como salida (LED3)
    FILE *csv = fopen(arch,"w"); //Se abre archivo .CSV en modo escritura
	
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) { //Se inicializa el SPI de WiringPi
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}


    
    while(1){
		ADCvalue = get_ADC(ADC_CHANNEL); //Se llama la función para enviar configuración y datos por SPI
		printf("Valor de la conversión: %d\n", ADCvalue);//Se despliega el valor de la conversión ADC
		fflush(stdout); //Se limpia el buffer de salida
		usleep(1000); //usleep para tener un retraso de 1000us o 1ms
		fprintf(csv,"%d\n",ADCvalue);//Se escribe en formato decimal y un enter el valor del ADC en el archivo .CSV
		val = ADCvalue*4/1022;//Mapeo de datos para tener un valor equivalente de 0-1023 y 0-4
	
		for(int i = 0; i < 4; i++){//Ciclo for para que en cada iteración vaya comparando con el valor mapeado para ir encendiendo las LEDS.
			if(i < val){
				
				digitalWrite(leds[i],HIGH);
			}
			
			else{
				digitalWrite(leds[i],LOW);
				
			}
			
			
		}
		
	}
	fclose(csv);//Se concluye la escritura de datos en el .CSV
	return 0; 
}

uint16_t get_ADC(int ADC_chan) //Función para configurar el MCP3002 y enviar los datos del canal seleccionado
{
	uint8_t spiData[2];	//Dos bytes a enviar
	uint16_t resultado;

	
	if((ADC_chan < 0) || (ADC_chan > 1)) //Condición para asegurarse de utilizar canales validos (0 o 1)
		ADC_chan = 0;					 //Si el canal es menor a cero o mayor a uno, se pone el canal cero por defecto

	spiData[0] = 0b01101000 | (ADC_chan << 4);  //Se construye byte de configuración 01MC1000. M = 1 -> Single ended  C = canal
	spiData[1] = 0;							

	wiringPiSPIDataRW(SPI_CHANNEL, spiData, 2); //Se envían 2 bytes por SPI	
	resultado = (spiData[0] << 8) | spiData[1]; //Se construye variable de 2 bytes para el resultado

	return(resultado);
}
