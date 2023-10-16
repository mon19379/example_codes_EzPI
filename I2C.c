#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RTC_ADDR 0x68

uint16_t fd;
uint16_t min;
uint16_t h;
uint16_t segs;
uint16_t n;
uint16_t day;
uint16_t month;
uint16_t year;

int main(){
    
    if ((fd = wiringPiI2CSetup(RTC_ADDR)) == -1) {
    printf("Error al abrir la conexión I2C con el RTC\n");
    return 1;
    }

    wiringPiI2CWrite(fd, 0xD0);
    wiringPiI2CWrite(fd, 0);
    wiringPiI2CWrite(fd, 0b00000000);
    wiringPiI2CWrite(fd, 0b00000000);
    wiringPiI2CWrite(fd, 0b00100011);
    wiringPiI2CWrite(fd, 1);
    wiringPiI2CWrite(fd, 0x17);
    wiringPiI2CWrite(fd, 0x10);
    wiringPiI2CWrite(fd, 0x23);

    while(1){
        wiringPiI2CWrite (fd, 0xD1);
        wiringPiI2CWrite(fd, 0);
        segs = wiringPiI2CRead(fd);
        min = wiringPiI2CRead(fd);
        h =  wiringPiI2CRead(fd);
        na =  wiringPiI2CRead(fd);
        day =  wiringPiI2CRead(fd);
        month = wiringPiI2CRead(fd);
        year = wiringPiI2CRead(fd);


    }

    return 0;
}



