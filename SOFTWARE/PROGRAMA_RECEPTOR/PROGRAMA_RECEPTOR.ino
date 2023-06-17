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
const char *DEVICE_LABEL = "Pon_tu_dispositivo_API_etiqueta";
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
  client.setDebug(true);// Establecer verdadero para que los mensajes de depuración estén disponibles 
} 

void loop() { 
  float value = client.get(DEVICE_LABEL, VARIABLE_LABEL); 
  if(value!=ERROR_VALUE){ 
    Serial.print("Obteniendo el valor de la variable: "); 
    Serial.println(valor);
  } 
  retraso (5000); 
} 
