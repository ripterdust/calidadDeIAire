#include "WiFi.h"

const char* ssid = "OLAFITO";
const char* password = "pecsi123";

void setup(){

    Serial.begin(115200);
    Serial.println('Probando wifi');

    WiFi.begin(ssid, password);
    while (WiFi.status() == WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wifi conectado");
    
}