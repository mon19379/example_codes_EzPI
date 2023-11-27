/**************************************************************************************************************************************************/
// Buzzer.c
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite el uso de un Buzzer pasivo utilizando la Rasbperry Pi.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

//Variables a utilizar
int bot;
int bot1;
int flag = 0;
int flag1 = 1;
int f;

int main(){
wiringPiSetup();//Se inicializa WiringPi
pinMode(25, OUTPUT);//Pin 25 como salida (Pin del buzzer)
pullUpDnControl(27, PUD_UP);//Se configuran pines 6 y 27 como entradas con resistencia pull-up
pullUpDnControl(6, PUD_UP);
f = 400; //Se define frecuencia


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

}
