#include <wiringPi.h>
#include <stdio.h>

#define PWM_PIN 18

int valor_variable;
char comando[100];
int main() {
    if (wiringPiSetupGpio() == -1) {
        fprintf(stderr, "Error al inicializar WiringPi\n");
        return 1;
    }

    /* system(" gpio mode 18 pwm");
    system(" gpio pwm-ms");
    system(" gpio pwmc 192");
    system(" gpio pwmr 2000");


    snprintf(comando, sizeof(comando), "gpio pwm %d", valor_variable);
    system(comando);
 */

    pinMode(PWM_PIN, PWM_OUTPUT);
    
    // Configuraciones de PWM
    pwmSetMode(PWM_MODE_MS);  
    pwmSetClock(192);         
    pwmSetRange(2000);        

    // Establece el valor PWM
    pwmWrite(PWM_PIN, 150);
    delay(2000);  

    // Cambia el valor PWM
    pwmWrite(PWM_PIN, 200);
    delay(2000);  

    return 0;
}


