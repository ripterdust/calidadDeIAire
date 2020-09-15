#include <WiFi.h>

/* Constantes de los datos de la red*/
const char* SSID = "abc";
const char* pass = "12345678";

// Sitio a donde se va a pedir los datos
const char* host = "www.google.com";
void conection(){
  //Cosas de la conexión acá
  // Conectándome a la red wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectándose a: ");
  Serial.println(SSID);

  // Haciendo la conexión
  WiFi.begin(SSID, pass);

  while(WiFi.status() != WL_CONNECTED){
      delay(10);
      Serial.print(".");
    }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    pinMode(2, OUTPUT);
    
    
  }
}
void setup() {
  Serial.begin(115200);
  delay(10);
  conection();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_DISCONNECTED){
    
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
    WiFi.disconnect();
    WiFi.begin(SSID, pass);
    Serial.println("Desconectado");
  }
  if(WiFi.status() != WL_DISCONNECTED){
    digitalWrite(2, HIGH);
    Serial.println("Conectado");
    }
  

}
