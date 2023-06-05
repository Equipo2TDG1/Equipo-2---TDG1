#define SensorPin A0 

void setup() { 
  Serial.begin(9600);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  delay(1000);

  float sensorValue = analogRead(SensorPin);
  Serial.println(sensorValue);
  delay(1000);
  digitalWrite(4, LOW);
  delay(28000);
} 