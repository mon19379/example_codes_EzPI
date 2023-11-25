#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>

void incremento(void);
void decremento(void);
void cont(void);
uint16_t bot1;
uint16_t bot2;
uint16_t contador;
uint16_t flag1;
uint16_t flag2;
uint16_t bit;
uint16_t bit2;

uint16_t leds[] = {2,3,5,4};

int main(){
    wiringPiSetup();
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(27, INPUT);
    pinMode(6, INPUT);
    pullUpDnControl(27, PUD_UP);
    pullUpDnControl(6, PUD_UP);

    while(1){
        bot1 = digitalRead(27);
        bot2 = digitalRead(6);

        if(bot1 == 1){
            flag1 = 1;
        }

        else if(flag1 == 1 && bot1 == 0){
            flag1= 0;
            contador++;
            incremento();
        }


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


void incremento(void){
    for (int i = 0; i < 4; i++) {
        bit = (contador >> i) & 1; 
        digitalWrite(leds[i], bit);
  }

}

void decremento(void){
    for (int i = 0; i < 4; i++) {
        bit2 = (contador >> i) & 1; 
        digitalWrite(leds[i], bit2);
  }

}
