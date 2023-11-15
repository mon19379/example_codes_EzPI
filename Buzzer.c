#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <time.h>

int bot;
int bot1;
int flag = 0;
int flag1 = 1;

int main(){
wiringPiSetup();
pinMode(25, OUTPUT);
pullUpDnControl(27, PUD_UP);
pullUpDnControl(26, PUD_UP);
f = (1/2959)/2;


while(1){
    bot = digitalRead(27);
    bot1 = digitalRead(26);

    if (bot == HIGH){
        flag == 0;
    }

    else{
        flag = 1;
    }

    if(flag == 1){
        digitalWrite(25, HIGH);
        delay(f);
        digitalWrite(25,LOW);
        delay(f);
    }

    if(bot == HIGH){
        flag = 0;
    }

}

}