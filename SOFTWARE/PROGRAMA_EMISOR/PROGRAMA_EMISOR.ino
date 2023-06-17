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
  radio.openWritingPipe(0xF0F0F0F0E1LL);  // Dirección de escritura del canal de comunicación
  radio.setPALevel(RF24_PA_HIGH);         // Configurar la potencia de transmisión
}

void loop() {
  analogData.level = analogRead(A0);  // Leer el valor analógico del pin A0

  // Imprimir el valor analógico en el monitor serial
  Serial.print("Valor Analógico: ");
  Serial.println(analogData.level);

  // Enviar los datos analógicos a través del NRF24L01
  radio.write(&analogData, sizeof(analogData));

  delay(2000);  // Esperar 2 segundos antes de realizar la próxima lectura y envío de datos
}
