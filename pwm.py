import RPi.GPIO as GPIO
from time import sleep #Se imprtan las librerias

GPIO.setwarnings(False) #Se deshabilitan las advertencias
GPIO.setmode(GPIO.BCM) #Se establece el pinout (BCM)
GPIO.setup(12,GPIO.OUT) #Se configura el pin a utilizar
senal = GPIO.PWM(12,50) #se crea una pwm con frecuencia de 50 Hz en el pin 12
senal.start(0) #Se inicializa la señal


while True: 
    
#Ciclo for para mover el servo cambiando el ciclo de trabajo de 0 a 100)
	for x in range(0,100,1):
		senal.ChangeDutyCycle(x)
		sleep(0.01)
	sleep(0.5)

#Ciclo for para mover el servo cambiando el ciclo de trabajo de 100 a 0)
	for x in range(100,0,-1):
		senal.ChangeDutyCycle(x)
		sleep(0.01)
	sleep(0.5)