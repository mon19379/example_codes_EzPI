#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>


//Hilo ADC
#define SPI_CHANNEL	      0	// Canal SPI, 0 ó 1
#define SPI_SPEED 	1500000	// Velocidad de la comunicación SPI (reloj, en HZ)  Máx de 3.6 MHz con VDD = 5V, 1.2 MHz con VDD = 2.7V
#define ADC_CHANNEL    1 

//Hilo I2C
#define RTC_ADDR 0x68 //Se define el registro del sensor RTC DS3231

//Hilo STP
#define STEP_PIN 22   //Pin para el paso
#define DIR_PIN 23  // Pin de dirección
#define ENABLE 21

//Variables hilo ADC
char buffer[5]; //buffer de datos
uint16_t get_ADC(int channel); //Prototipo de función
uint16_t leds[] = {2,3,5,4}; //Arreglo con los numeros de pin de las LEDS
uint16_t val; /// Variable para mapeo

//Variables hilo Buzzer
uint8_t bot;
uint8_t bot1;
uint8_t flag = 0;
uint8_t flag1 = 1;
int f;

//Variables hilo I2C
uint8_t SEC, MIN, H, DAY, MONTH, YEAR; //Se definen variables

//Variables hilo Servo
int i;
char comando[100];

//Variables UART
int fd;



void ADC(void*ptr){
    
    uint16_t ADCvalue; //Variable para valor de ADC

    while(1){
        ADCvalue = get_ADC(ADC_CHANNEL); //Se llama la función para enviar configuración y datos por SPI
        fflush(stdout); //Se limpia el buffer de salida
        usleep(1000); //usleep para tener un retraso de 1000us o 1ms
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
    
    pthread_exit(0);
}
void Buzzer(void*ptr){
    while(1){
        //Se lee el estado de los botones
        bot = digitalRead(27);
        bot1 = digitalRead(6);

        
        if (bot == HIGH){//Boton para encender buzzer
            flag == 0;
        }

        else{
            flag = 1;
        }
        //Condicional para generar una señal cuadrada a cierta frecuencia encendiendo y apagando un pin
        if(flag == 1){
            digitalWrite(25, HIGH);
            delay(1000/f);
            digitalWrite(25,LOW);
            delay(1000/f);
        }

        if(bot1 == LOW){ //Boton para apagar buzzer
            flag = 0;
        }
    }
    pthread_exit(0);
}
void RTC(void*ptr){

    while(1){
        // Leer la hora y la fecha
        SEC = wiringPiI2CReadReg8(fd, 0x00);
        MIN = wiringPiI2CReadReg8(fd, 0x01);
        H = wiringPiI2CReadReg8(fd, 0x02);
        DAY = wiringPiI2CReadReg8(fd, 0x04);
        MONTH = wiringPiI2CReadReg8(fd, 0x05);
        YEAR = wiringPiI2CReadReg8(fd, 0x06);
        
        // Imprimir la hora y la fecha
        printf("Hora: %02x:%02x:%02x\n", H, MIN, SEC);
        printf("Fecha: %02x/%02x/%02x\n", DAY, MONTH, YEAR);
        
        delay(1000); // Espera 1 segundo
    }
    pthread_exit(0);
}
void Servo(void*ptr){
    system(" gpio mode 26 pwm"); //Se establece el pin 26 como salida PWM
     //Se configura en modo MS, de tal manera que el Duty cycle se interprete como el
    //tiempo que la PWM esta en alto en relación con el período total. 
    //Por lo que el valor que se le establece representa la duración en estado alto
    system(" gpio pwm-ms"); 
    system(" gpio pwmc 192"); //Divisor del clock para frecuencia  
    system(" gpio pwmr 2000"); // Tasa de actualización de la señal
    //f en Hz = 19.2MHz / pwmc / pwmr
    // en este caso tenemos 19.2MHz/192/2000 = 50Hz para un servo motor
    
    //ciclo for para ir modificando el valor que modifica el ciclo de trabajo
    for (int i = 0; i < 250; i++){
    sprintf(comando,"gpio pwm 26 %d" ,i);
    system(comando);
    }   
    
}
void STP(void*ptr){
    while(1){
        for(int i = 0; i< 200;i++){ // Ciclo para dar una vuelta completa, 200 steps para una vuelta completa
        
            digitalWrite(STEP_PIN, HIGH);
            delayMicroseconds(1000); //Controlar velocidad de giro
            digitalWrite(STEP_PIN, LOW);
            delayMicroseconds(1000);            
        }
    }
    pthread_exit(0);
}
void UART(void*ptr){
    while(1){
		
		if(serialDataAvail(fd)){
			char recibido = serialGetchar(fd);
			buffer[ind++] = recibido;
			
			if(recibido == '\n'){
				
			printf("Esto envió el arduino: %s\n", buffer);
			
			ind = 0;
			memset(buffer,0,sizeof(buffer));
			}
		} 

	
		serialPuts(fd,"hola, esto es una prueba del EzPi\n");
		usleep(1000);

	}
    serialClose(fd);
    pthread_exit(0);
}
int main (void){
    wiringPiSetup();
    pinMode(2, OUTPUT);//Pin 2 wiring pi como salida (LED1)
    pinMode(3, OUTPUT);//Pin 3 wiring pi como salida (LED2)
    pinMode(4, OUTPUT);//Pin 4 wiring pi como salida (LED4)
    pinMode(5, OUTPUT);//Pin 5 wiring pi como salida (LED3)
    pinMode(25, OUTPUT);//Pin 25 como salida (Pin del buzzer)
    pullUpDnControl(27, PUD_UP);//Se configuran pines 6 y 27 como entradas con resistencia pull-up
    pullUpDnControl(6, PUD_UP);
    f = 400; //Se define frecuencia para buzzer
    pinMode(STEP_PIN, OUTPUT);//Pin 22 wiring pi como salida (STEP)
    pinMode(DIR_PIN, OUTPUT);//Pin 23 wiring pi como salida (DIR)
    pinMode(ENABLE, OUTPUT);//Pin 21 wiring pi como salida (EN)
    digitalWrite(ENABLE, LOW);  // Cambiar a HIGH para apagar el módulo
    digitalWrite(DIR_PIN, HIGH);  // Cambiar a LOW para invertir la dirección 

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0) { //Se inicializa el SPI de WiringPi
		printf("wiringPiSPISetup falló.\n");
		return(-1);
	}

    if ((fd = wiringPiI2CSetup(RTC_ADDR)) == -1) { //Se inicializa I2C de WiringPi
        printf("Error al abrir la conexión I2C con el RTC\n");
        return (-1);
    }

    if ((fd = serialOpen ("/dev/ttyS0", 115200)) < 0) { //Se abre el puerto serial ttyS0
	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	return (-1) ;

}

    wiringPiI2CWriteReg8(fd, 0x00, 0b00100011);  // Configura el registro de control
    wiringPiI2CWriteReg8(fd, 0x01, 0x01);        
    wiringPiI2CWriteReg8(fd, 0x02, 0x17);        
    wiringPiI2CWriteReg8(fd, 0x03, 0x10);        
    wiringPiI2CWriteReg8(fd, 0x04, 0x23);  


    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;
    pthread_t thread6;
  

    pthread_create(&thread1, NULL, (void*)&ADC, NULL);
    pthread_create(&thread2, NULL, (void*)&Buzzer, NULL);
    pthread_create(&thread3, NULL, (void*)&RTC, NULL);
    pthread_create(&thread4, NULL, (void*)&Servo, NULL);
    pthread_create(&thread5, NULL, (void*)&STP, NULL);
    pthread_create(&thread6, NULL, (void*)&UART, NULL);

    pthread_join (thread1,NULL);
    pthread_join (thread2,NULL);
    pthread_join (thread3,NULL);
    pthread_join (thread4,NULL);
    pthread_join (thread5,NULL);
    pthread_join (thread6,NULL);

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
	resultado = (spiData[0] << 8) | spiData[1]; //Se construye variable de 3 bytes para el resultado

	return(resultado);
}