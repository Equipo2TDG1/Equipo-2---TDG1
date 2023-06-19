#include <SPI.h>
#include <RF24.h>

RF24 radio(22, 21);  // Crear un objeto NRF24L01 y especificar los pines CE y CSN (GPIO22 y GPIO21 en el ESP32 DevKit V1)

struct AnalogData {
  int level;
};

AnalogData analogData;

void setup() {
  Serial.begin(9600);  // Establecer la velocidad de comunicación del monitor serial en 9600

  radio.begin();       // Inicializar el módulo NRF24L01
  radio.openWritingPipe(0xF0F0F0F0E1LL);  // Dirección de escritura del canal de comunicación
  radio.setPALevel(RF24_PA_HIGH);         // Configurar la potencia de transmisión

  pinMode(36, INPUT);  // Configurar el pin GPIO35 (análogo) como entrada para el sensor de humedad
}

void loop() {
  analogData.level = analogRead(36);  // Leer el valor analógico del pin GPIO35 (D35)

  // Imprimir el valor analógico en el monitor serial
  Serial.print("Valor Analógico: ");
  Serial.println(analogData.level);

  // Enviar los datos analógicos a través del NRF24L01
  radio.write(&analogData, sizeof(analogData));

  delay(2000);  // Esperar 2 segundos antes de realizar la próxima lectura y envío de datos
}

