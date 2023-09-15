
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL	      1
#define SPI_SPEED 	1500000	
                            
#define ADC_CHANNEL       0	
#define DAC_CHANNEL       0

void boton (void);
char buffer[5];
char buffer1[5];
uint16_t get_ADC(int channel);
uint16_t get_DAC(int channel1);	
uint8_t chan = 1;
int main(void)
{
    uint16_t ADCvalue;
    uint16_t DACvalue;
	
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) {
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}

    wiringPiSetup();
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);



	 while(1){
       
	/*   
      
        if(chan == 0){
            digitalWrite(10,LOW);
            ADCvalue = get_ADC(ADC_CHANNEL);
		    printf("Valor de la conversión: %d\n", ADCvalue);
		    fflush(stdout);
		    usleep(1000);
            digitalWrite(10,HIGH);
			
        }*/

     //   if (chan == 1){
            digitalWrite(11,LOW);
            DACvalue = get_DAC(DAC_CHANNEL);
	    DACvalue =;
	    printf("Valor: %d\n", DACvalue);
			
    //    }
	
	
		
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

	wiringPiSPIDataRW(ADC_chan, spiData, 2);	


	resultado = (spiData[0] << 8) | spiData[1];

	return(resultado);
}


uint16_t get_DAC(int DAC_chan)
{
    uint8_t spiData[2];	
	uint16_t resultado1;

	if((DAC_chan < 0) || (DAC_chan > 1))
		DAC_chan = 0;



	
	spiData[0] = 0b00110000 | (DAC_chan << 8);  
												
	spiData[1] = 0;	

	wiringPiSPIDataRW( DAC_chan, spiData, 2);	
	resultado1 = (spiData[0] << 12) | spiData[1];

	return(resultado1);
}
