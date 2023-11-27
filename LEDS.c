/**************************************************************************************************************************************************/
// LEDS.c
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite la el uso de LEDS y de botones utilizando la  Rasbperry Pi.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>

void incremento(void);//Prototipo
void decremento(void);//Prototipo
void cont(void); //Prototipo

//Variables 
uint8_t bot1;
uint8_t bot2;
uint8_t contador;
uint8_t flag1;
uint8_t flag2;
uint8_t bit;
uint8_t bit2;
uint8_t leds[] = {2,3,5,4};  //Arreglo con los numeros de pin de las LEDS

int main(){
    wiringPiSetup();//Se inicializa WiringPi
    pinMode(2, OUTPUT);//Pin 2 wiring pi como salida (LED1)
    pinMode(3, OUTPUT);//Pin 3 wiring pi como salida (LED2)
    pinMode(4, OUTPUT);//Pin 4 wiring pi como salida (LED4)
    pinMode(5, OUTPUT);//Pin 5 wiring pi como salida (LED3)
    pinMode(27, INPUT);//Pin 27 wiring pi como entrada (Boton 1)
    pinMode(6, INPUT);//Pin 6 wiring pi como entrada (Boton 2)
    pullUpDnControl(27, PUD_UP);//Boton 1 en pull-up
    pullUpDnControl(6, PUD_UP);//Boton 2 en pull-up

    while(1){
        //Se lee el estado de los botones
        bot1 = digitalRead(27);
        bot2 = digitalRead(6);

        //antirebote
        if(bot1 == 1){
            flag1 = 1;
        }

        else if(flag1 == 1 && bot1 == 0){
            flag1= 0;
            contador++;
            incremento();
        }

        //antirebote
        if(bot2 == 1){
            flag2 = 1;
        }

        else if(flag2 == 1 && bot2 == 0){
            flag2 = 0;
            contador--;
            decremento();
        }

    }
}

//Función para incrementar un contador y encender las LEDS acorde al valor
void incremento(void){
    for (int i = 0; i < 4; i++) {
        bit = (contador >> i) & 1; 
        digitalWrite(leds[i], bit);
  }

}
//Función para decrementar un contador y encender las LEDS acorde al valor
void decremento(void){
    for (int i = 0; i < 4; i++) {
        bit2 = (contador >> i) & 1; 
        digitalWrite(leds[i], bit2);
  }

}
