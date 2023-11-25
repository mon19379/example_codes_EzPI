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


#define SPI_CHANNEL	      0	// Canal SPI, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)
#define arch "archivo.csv"                            // Máxima de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL    1   	// Canal A/D del MCP3002, 0 ó 1
char buffer[5];
uint16_t get_ADC(int channel);
uint16_t x;	
uint16_t leds[] = {2,3,5,4};
uint16_t val;

int main(void)
{
    uint16_t ADCvalue;
    wiringPiSetup();
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    FILE *csv = fopen(arch,"w");
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}


    
    while(1){
      
		 

		ADCvalue = get_ADC(ADC_CHANNEL);
		printf("Valor de la conversión: %d\n", ADCvalue);
		fflush(stdout);
		usleep(1000);
		fprintf(csv,"%d\n",ADCvalue);
		val = ADCvalue*4/1022;
		
		
		for(int i = 0; i < 4; i++){
			if(i < val){
				
				digitalWrite(leds[i],HIGH);
			}
			
			else{
				digitalWrite(leds[i],LOW);
				
			}
			
			
		}
		

		
	}
   
  fclose(csv);
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
