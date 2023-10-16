#include "pwm.h"
#include <wiringPi.h>
#include <unistd.h>
#include <stdint.h>

void generatePWM(uint16_t pin, uint16_t periodo){

    pinMode(pin, OUTPUT);

    uint16_t tiempoON = periodo / 2;

    while(1){
        digitalWrite(pin,HIGH);
        usleep(tiempoON);
        digitalWrite(pinLOW);
        usleep(periodo - tiempoON);
    }

}