/**************************************************************************************************************************************************/
// Stepper.c
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite la el uso de un driver A4988 para un NEMA 17 utilizando la  Rasbperry Pi.
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/


#include <stdio.h>
#include <wiringPi.h>

#define STEP_PIN 22   //Pin para el paso
#define DIR_PIN 23  // Pin de dirección
#define ENABLE 21

int main() {
    wiringPiSetup();//Se inicializa WiringPi
    pinMode(STEP_PIN, OUTPUT);//Pin 22 wiring pi como salida (STEP)
    pinMode(DIR_PIN, OUTPUT);//Pin 23 wiring pi como salida (DIR)
    pinMode(ENABLE, OUTPUT);//Pin 21 wiring pi como salida (EN)
    digitalWrite(ENABLE, LOW);  // Cambiar a HIGH para apagar el módulo
    digitalWrite(DIR_PIN, HIGH);  // Cambiar a LOW para invertir la dirección 

    while(1){
        
        for(int i = 0; i< 200;i++){ // Ciclo para dar una vuelta completa, 200 steps para una vuelta completa

        
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(1000); //Controlar velocidad de giro
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(1000);
        
        }

    }

    return 0;
}
