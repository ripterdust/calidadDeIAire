#include "ThingSpeak.h"
#include "WiFi.h"
#include "DHT.h"

// ANCHOR - Estos son los pines que se utilizaran para conectar el sensor

#define pin1 13       //Pin del DHT11.
#define pin2 32       //Pin del DHT22.


// ANCHOR - Configurando el router 
const char* ssid = "OLAFITO";                   //SSID de vuestro router.
const char* password = "pecsi123";                //Contraseña de vuestro router.


// ANCHOR - Estos son los datos del canal de ThingSpeak
unsigned long channelID = 1128073;                //ID de vuestro canal.
const char* WriteAPIKey = "63V3LPO7JRE5IJH7";     //Write API Key de vuestro canal.


// ANCHOR - Inicializando el wifi
WiFiClient client;


// ANCHOR - Inicializando el sensor
DHT dht1(pin1, DHT11);    //El azul.

// NOTE - Esta función es la que funciona para leer el sensor.
void leerdht1() {
  
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();

  while (isnan(t1) || isnan(h1)){
    Serial.println("Lectura fallida en el sensor DHT11, repitiendo lectura...");
    delay(2000);
    t1 = dht1.readTemperature();
    h1 = dht1.readHumidity();
  }

  Serial.print("Temperatura DHT11: ");
  Serial.print(t1);
  Serial.println(" ºC.");

  Serial.print("Humedad DHT11: ");
  Serial.print(h1);
  Serial.println(" %."); 

  Serial.println("-----------------------");
  Serial.println();

  ThingSpeak.setField (1,t1);
  ThingSpeak.setField (2,h1);

}


// ANCHOR - Función principal (Sólo se ejecuta al inicio)
void setup() {
  Serial.begin(115200);
  Serial.println("Test de sensores:");

  WiFi.begin(ssid,password);
  while (WiFi.status() == WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado!");

  ThingSpeak.begin(client);

  dht1.begin();

 
}
// NOTE - Código que se repite cíclicamente 
void loop() {

  delay(1000);
  leerdht1();

  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak!");
  delay(16000);
}

