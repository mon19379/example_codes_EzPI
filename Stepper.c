#include <stdio.h>
#include <wiringPi.h>

#define STEP_PIN 21   //Pin para el paso
#define DIR_PIN 22   // Pin de dirección

int main() {
    wiringPiSetup();
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    int delayMicros = 1000;  
    
    digitalWrite(DIR_PIN, HIGH);  // Cambiar a LOW para invertir la dirección 
    while(1){
        for (int i = 0; i < 200; i++) {  // 200 pasos para una vuelta completa 
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delayMicros);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delayMicros);
    }

    }

    return 0;
}
