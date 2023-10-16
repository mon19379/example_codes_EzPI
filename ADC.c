/* adc_SPI_wiringPi.c
 Basado en la adaptación de Dr. Luis Alberto Rivera del código tomado de: https://projects.drogon.net/raspberry-pi/wiringpi/
 Adaptado y comentado por: Francisco José Montúfar Gudiel
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <softPwm.h>

#define SPI_CHANNEL	      0	// Canal SPI, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL       0	// Canal A/D del MCP3002, 0 ó 1
#define archive "archivo.txt"
void boton (void);
char buffer[5];
uint16_t get_ADC(int channel);
uint16_t x;	

int main(void)
{
    uint16_t ADCvalue;
	wiringPiSetup();
	softPwmCreate(12, 0, 180); 
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}


    
    while(1){
      

		ADCvalue = get_ADC(ADC_CHANNEL);
		printf("Valor de la conversión: %d\n", ADCvalue);
		fflush(stdout);
		usleep(1000);
		x = (ADCvalue/1023)*180;
		softPwmWrite (12, x);

		
	}
   

  return 0;
}

uint16_t get_ADC(int ADC_chan)
{
	uint8_t spiData[2];	
	uint16_t resultado;

	
	if((ADC_chan < 0) || (ADC_chan > 1))
		ADC_chan = 0;



	
	spiData[0] = 0b01101000 | (ADC_chan << 4);  
	spiData[1] = 0;	

	wiringPiSPIDataRW(SPI_CHANNEL, spiData, 2);	
	resultado = (spiData[0] << 8) | spiData[1];

	return(resultado);
}
