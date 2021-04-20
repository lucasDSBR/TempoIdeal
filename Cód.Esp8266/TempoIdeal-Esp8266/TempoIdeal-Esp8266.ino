#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <FirebaseESP8266.h>
 

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

//#define FPM_SLEEP_MAX_TIME           0xFFFFFFF
#define WIFI_SSID "ID"
#define WIFI_PASSWORD "Password"
#define FIREBASE_HOST "HOST"
#define FIREBASE_AUTH "HASH"

FirebaseData fbdo;
void setup() 
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Conectando ao ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Conectado!");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  dht.setup(4, DHTesp::DHT11);
}
 
void loop() 
{
  Serial.print("Estou acordado!");
  float h = dht.getHumidity();
  float t = dht.getTemperature();  
  int s = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Umidade: ");  
  Serial.print(h);
  
  Serial.print("%  Temperatura: ");  
  Serial.print(t);  
  Serial.println("°C ");

  Serial.print("Sensação térmica: ");
  Serial.print(s);
  Serial.println(".");
   
  Firebase.setFloat(fbdo,"Temperatura: ",t);
  Firebase.setFloat(fbdo,"Umidade: ",h);
  Firebase.setInt(fbdo,"Sensação Térmica: ",s);
  Serial.println("deep sleep por 5 minutos, volto já!");
  wifi_set_sleep_type(NONE_SLEEP_T);
  delay(300000);
}
