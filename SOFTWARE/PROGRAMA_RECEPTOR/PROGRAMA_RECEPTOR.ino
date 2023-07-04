// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


#define CE_PIN  22
#define CSN_PIN 21

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN);

int analogData = 0; // this must match dataToSend in the TX
bool newData = false;

const float MIN_HUMIDITY = 819.0370370370371;  // Minimum humidity value
const float MAX_HUMIDITY = 4062.05;            // Maximum humidity value

//===========

void setup()
{

   Serial.begin(9600);
   delay(3000);
   Serial.println("SimpleRx Starting");
   radio.begin();
   radio.setDataRate( RF24_250KBPS );
   radio.openReadingPipe(1, thisSlaveAddress);
   radio.startListening();
   pinMode(36, INPUT);
}

//=============

void loop()
{
   getData();
   showData();
}

//==============

float calculateHumidity(int analogValue) {
  float humidity = map(analogValue, MAX_HUMIDITY, MIN_HUMIDITY, 0, 100);
  return humidity;
}


void getData()
{
   if ( radio.available() )
   {
      radio.read( &analogData, sizeof(analogData) );
      newData = true;
   }
}

void showData()
{
   if (newData == true)
   {
      float humidityPercentage = calculateHumidity(analogData);
      Serial.print("Humidity: ");
      Serial.print(humidityPercentage);
      Serial.println("%");
      newData = false;
   }
}
