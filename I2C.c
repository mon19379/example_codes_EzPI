#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RTC_ADDR 0x68

uint8_t SEC, MIN, H, DAY, MONTH, YEAR;

int main() {
    int fd;
    
    if ((fd = wiringPiI2CSetup(RTC_ADDR)) == -1) {
        printf("Error al abrir la conexión I2C con el RTC\n");
        return 1;
    }

    // Configura el reloj RTC
    wiringPiI2CWriteReg8(fd, 0x00, 0b00100011);  // Configura el registro de control
    wiringPiI2CWriteReg8(fd, 0x01, 0x01);        
    wiringPiI2CWriteReg8(fd, 0x02, 0x17);        
    wiringPiI2CWriteReg8(fd, 0x03, 0x10);        
    wiringPiI2CWriteReg8(fd, 0x04, 0x23);        

    while (1) {
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

    return 0;
}
