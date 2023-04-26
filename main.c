#include <ThingSpeak.h>

#include <DHT.h>
#include <DHT_U.h>

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

//dht definitions
#define DHTPIN 23
#define DHTTYPE DHT11 

//thingspeak definitions
#define CHANNEL_ID  2096412
#define CHANNEL_API_KEY "96K7XHSV1WW2U7EZ"


//WIFI fields
const char* ssid = "iPhone de Vinicius";
const char* password =  "Hanselvi";

//thingspeak field
WiFiClient client;

//dht field
DHT dht (DHTPIN,DHTTYPE);

void setup() {
Serial.begin(115200);

//conexao com wifi e DHT11
WiFi.begin(ssid, password);

dht.begin();
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");

 ThingSpeak.begin(client);


}

void loop() {
  //leitura constante de temperatura e humidade
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();



 if (isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("C: \n");
  Serial.print(temperature);
  delay(500);
  Serial.print("\n humidade: \n");
  Serial.print(humidity);


  ThingSpeak.writeField(CHANNEL_ID,1,temperature,CHANNEL_API_KEY);
  ThingSpeak.writeField(CHANNEL_ID,2,humidity,CHANNEL_API_KEY);

  delay(15000);
}
