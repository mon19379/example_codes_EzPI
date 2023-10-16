#include <wiringPi.h>
#include <stdio.h>

#define SERVO_PIN 18  

int main(void) {
    if (wiringPiSetupGpio() == -1) {
        printf("Error al inicializar WiringPi.\n");
        return 1;
    }

    pinMode(SERVO_PIN, PWM_OUTPUT);

    printf("Moviendo el servo...\n");

    while (1) {
        for (int i = 50; i <= 250; i++) {
            pwmWrite(SERVO_PIN, i);
            delay(10);
        }

        for (int i = 250; i >= 50; i--) {
            pwmWrite(SERVO_PIN, i);
            delay(10);
        }
    }

    return 0;
}
