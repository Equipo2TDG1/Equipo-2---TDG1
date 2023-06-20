/******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"
#include <SPI.h>
#include <RF24.h>

RF24 radio(22, 21);  // Crear un objeto NRF24L01 y especificar los pines CE y CSN

struct AnalogData {
  int level;
};

AnalogData analogData;

/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBFF-SKS8shDEAVTBErrHFycDQzCuvVyLob";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Jorge's Galaxy A72";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "zahh2486";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = ""; // Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

// void callback(char *topic, byte *payload, unsigned int length)
// {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   for (int i = 0; i < length; i++)
//   {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  // ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  radio.begin();       // Inicializar el módulo NRF24L01
  radio.openReadingPipe(1,0xF0F0F0F0E1LL);  // Establecer la dirección de lectura del canal de comunicación
  radio.setPALevel(RF24_PA_HIGH);            // Configurar la potencia de recepción

  radio.startListening();  // Establecer el módulo NRF24L01 en modo de recepción

  timer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, value); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();

  if (radio.available()) {
    radio.read(&analogData, sizeof(analogData));  // Leer los datos recibidos

    // Imprimir el valor analógico en el monitor serial
    Serial.print("Valor Analógico recibido: ");
    Serial.println(analogData.level);
  }
}
