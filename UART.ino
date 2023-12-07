/**************************************************************************************************************************************************/
// UART.ino
//Desarrollado y comentado por: Francisco José Montúfar Gudiel
//Programa que permite el uso del protocolo UART utilizando un ESP32 para comunicarse con una Raspberry Pi 3b+
/**************************************************************************************************************************************************/
void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17); //se inician los puertos seriales Serial.begin(baud, paridad, rx, tx)
  Serial2.setRxBufferSize(10000); //Se establece el tamaño del buffer
  pinMode(5, OUTPUT);
}

void loop() {

  // Espera hasta que haya datos disponibles en el puerto serie
  while (Serial2.available() > 0) {
    // Lee el dato recibido
    String receivedString = Serial2.readStringUntil('\n');


    // Imprime el dato en el Monitor Serie
    //NOTA: SI SE DESEA VER QUE RECIBE EL ARDUINO, USAR EL CODIGO  DE LAS LINEAS 16-18
    //Serial2.print("Received: ");
    // Serial2.println(receivedString);
    //delay(1000);


    if (receivedString == "hola, esto es una prueba del EzPi") { //Si lo recibido de la Rpi es esa frase, que se cumpla la condición.
      Serial2.println("ESP32 responde: Hola dice el ESP!"); //Se envía a la Rpi una respuesta
      delay(1000);
      digitalWrite(5,HIGH);
      delay(10);
      digitalWrite(5,LOW);
      

       }
    }
  }
