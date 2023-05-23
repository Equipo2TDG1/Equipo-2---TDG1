#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // Crear un objeto NRF24L01 y especificar los pines CE y CSN

struct AnalogData {
  int level;
};

AnalogData analogData;

void setup() {
  Serial.begin(9600);  // Establecer la velocidad de comunicación del monitor serial en 9600

  radio.begin();       // Inicializar el módulo NRF24L01
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Establecer la dirección de lectura del canal de comunicación
  radio.setPALevel(RF24_PA_HIGH);            // Configurar la potencia de recepción

  radio.startListening();  // Establecer el módulo NRF24L01 en modo de recepción
}

void loop() {
  if (radio.available()) {
    radio.read(&analogData, sizeof(analogData));  // Leer los datos recibidos

    // Imprimir el valor analógico en el monitor serial
    Serial.print("Valor Analógico recibido: ");
    Serial.println(analogData.level);
  }
}