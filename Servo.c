/**************************************************************************************************************************************************/
// Servo.c
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite la creación de una PWM para controlar un servomotor utilizando la  Rasbperry Pi.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

//variables
int i;
char comando[100];


int main() {
    
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
 
    return 0;
}


