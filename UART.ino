/**************************************************************************************************************************************************/
// UART.ino
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite el uso del protocolo UART utilizando Arduino Nano
/**************************************************************************************************************************************************/


void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 bps
}

void loop() {
  // Espera hasta que haya datos disponibles en el puerto serie
  while (Serial.available() > 0) {
    // Lee el dato recibido
    String recibido= Serial.readStringUntil('\n');


    // Imprime el dato en el Monitor Serie
    // Serial.print("Received: ");
    //Serial.println(receivedString);

    if (recibido == "hola, esto es una prueba del EzPi") { //Si lo que recibe de la RPi es ese string, el arduino contesta
      Serial.println("Arduino responde: Hola desde Arduino!");
      delay(1000);
    }
  }
}