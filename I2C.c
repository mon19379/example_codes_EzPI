/**************************************************************************************************************************************************/
// I2C.c
//Fesarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que configura I2C entre la Rasbperry Pi (maestro)
//y RTC DS3231 (esclavo).
//Se usan funciones de la librería wiringPi.
//Recuerde compilar usando -lwiringPi
/**************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RTC_ADDR 0x68 //Se define el registro del sensor RTC DS3231

uint8_t SEC, MIN, H, DAY, MONTH, YEAR; //Se definen variables

int main() {
    int fd;
    
    if ((fd = wiringPiI2CSetup(RTC_ADDR)) == -1) { //Se inicializa I2C de WiringPi
        printf("Error al abrir la conexión I2C con el RTC\n");
        return (-1);
    }

    // Configuración del RTC
    wiringPiI2CWriteReg8(fd, 0x00, 0X00);  // Configura segundos
    wiringPiI2CWriteReg8(fd, 0x01, 0x19);  // Configura minutos    
    wiringPiI2CWriteReg8(fd, 0x02, 0x13);  // Configura horas      
    wiringPiI2CWriteReg8(fd, 0x04, 0x27);  // Configura dia
    wiringPiI2CWriteReg8(fd, 0x05, 0x11);  // Configura mes
    wiringPiI2CWriteReg8(fd, 0x06, 0x23);  // Configura año
  

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
