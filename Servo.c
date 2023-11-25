#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PWM_PIN 26

int valor_variable = 200;
int i;
char comando[100];
int main() {
    if (wiringPiSetupGpio() == -1) {
        fprintf(stderr, "Error al inicializar WiringPi\n");
        return 1;
    }

    system(" gpio mode 26 pwm");
    system(" gpio pwm-ms");
    system(" gpio pwmc 192");
    system(" gpio pwmr 2000");
    
    for (int i = 0; i < 250; i++){
    sprintf(comando,"gpio pwm 26 %d" ,i);
    system(comando);
 }   
 



    return 0;
}


