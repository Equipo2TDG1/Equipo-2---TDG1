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

// Este ejemplo recupera el último valor de una variable de la API de Ubidots   
// utilizando el protocolo TCP.         

/****************************************                       
* Incluir bibliotecas 
****** *********************************/ 
#incluir <Ubidots.h>        

/******* ********************************                       
* Definir constantes 
************** **************************/     
                 
// Sus credenciales GPRS, si las hay      
const char *APN = "Pon_el_APN_aquí"; 
const char *USUARIO = "Pon_el_usuario_APN_aquí"; 
const char *PASS = "Pon_el_APN_pwd_aquí"; 
const char *FICHA = "Pon_tu_ficha_de_Ubidots_aquí"; 
const char *DEVICE_LABEL = "
const char *VARIABLE_LABEL = "Pon_tu_variable_API_etiqueta";           

Cliente de Ubidots (TOKEN, APN, USUARIO, PASS); 

/****************************************                       
* Funciones auxiliares 
****** *********************************/                            

// Pon aquí tus funciones auxiliares 
/******* ********************************                       
* Funciones principales 
************** **************************/ 

void setup() {                       
  Serial.begin(115200);                       
  cliente.setDebug(verdadero); // Establecer verdadero para que los mensajes de depuración estén disponibles }      
                                     
void loop() { 
  float value = analogRead(A0); // Lectura del pin analógico A0
  cliente.add(VARIABLE_LABEL, valor); 
  if(client.send()){ 
    Serial.println("¡Datos enviados a Ubidots con éxito!") 
  }                                        
  delay(5000);                    
}
