
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <LoRa.h>

#define DHTPIN 3 //remettre2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// CSE params
const char* host = "192.168.143.139";
const int httpPort = 8282;

// AE params
const int aePort   = 80;
const char* origin   = " admin:admin";
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
int counter = 0;
int temperature = 0;
int flamePin = A0; // select the input pin for LDR
int flameVal;



void setup() {

  pinMode(2, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
  if (!LoRa.begin(865E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  delayMS = sensor.min_delay / 1000;



//  Init one m2m 
  //// Create AE resource for sensor node 
  //String resultat = send("/~/mn-cse/mn-name",2,"{\"m2m:ae\":{\"rn\":\"sensorNodeLora\",\"api\":\"mydevice1.company.com\",\"rr\":\"true\",\"poa\":[loraID]}}");
  String resultat = createReqHttp("/~/mn-cse/mn-name", 2, "{\"m2m:ae\":{\"rn\":\"sensorNodeLora\",\"api\":\"mydevice1.company.com\",\"rr\":\"true\",\"poa\":[loraID]}}" );
  Serial.println(resultat);
  LoRa.beginPacket();
  LoRa.print(resultat);
  LoRa.endPacket();
  delay(delayMS);
  

   //Create Container resource for temperature sensor 
  //    send("/~/mn-cse/mn-name/sensorNodeLora",3,"{\"m2m:cnt\":{\"rn\":\"temperature\"}}");
  resultat = createReqHttp("/~/mn-cse/mn-name/sensorNodeLora", 3, "{\"m2m:cnt\":{\"rn\":\"temperature\"}}" );
  Serial.println(resultat);
  LoRa.beginPacket();
  LoRa.print(resultat);
  LoRa.endPacket();
  delay(delayMS);
   
  // Create Container resource for humidity sensor 
  //    send("/~/mn-cse/mn-name/sensorNodeLora",3,"{\"m2m:cnt\":{\"rn\":\"humidity\"}}");
  resultat = createReqHttp("/~/mn-cse/mn-name/sensorNodeLora", 3, "{\"m2m:cnt\":{\"rn\":\"humidity\"}}" );
  Serial.println(resultat);
  LoRa.beginPacket();
  LoRa.print(resultat);
  LoRa.endPacket();
  delay(delayMS);

  // Create Container resource for the flame sensor (ky-026)
       //send("/~/mn-cse/gateway/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"flame\"}}");
       resultat = createReqHttp("/~/mn-cse/mn-name/sensorNodeLora", 3, "{\"m2m:cnt\":{\"rn\":\"flame\"}}" );
       Serial.println(resultat);
       LoRa.beginPacket();
       LoRa.print(resultat);
       LoRa.endPacket();
       delay(delayMS);  
}
String createReqHttp(String url, int ty, String rep ){
// prepare the HTTP request
  String req = String()+ "POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "X-M2M-Origin: " + origin + "\r\n" +
               //"X-M2M-Origin:" + " admin:admin" + "\r\n" +
               "Content-Type: application/json;ty="+ty+"\r\n" +
               "Content-Length: "+ rep.length()+"\r\n"
               "Connection: close\r\n\n" + 
               rep;

  Serial.println(req+"\n");
  
  return req;
}

void loop() {

 
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    temperature = event.temperature;
  }

  // Create ContentInstance resource for temperature instance value
  //     send("/~/mn-cse/mn-name/sensorNodeLora/temperature",4,"{\"m2m:cin\":{\"con\":\"20\"}}");
  
  delay(delayMS);
  LoRa.beginPacket();
  LoRa.print("/~/mn-cse/mn-name/sensorNodeLora/temperature");
  LoRa.print(";");
  LoRa.print("4");
  LoRa.print(";");
  LoRa.print("{\"m2m:cin\":{\"con\":");
  LoRa.print(temperature);
  LoRa.print ("}}");
  LoRa.endPacket();

  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    }

 
   // Create ContentInstance resource for humidity instance value
   //    send("/~/mn-cse/mn-name/sensorNodeIUTInfo/humidity",4,"{\"m2m:cin\":{\"con\":\"100\"}}");

  delay(delayMS);
  LoRa.beginPacket();
  LoRa.print("/~/mn-cse/mn-name/sensorNodeLora/humidity");
  LoRa.print(";");
  LoRa.print("4");
  LoRa.print(";");
  LoRa.print("{\"m2m:cin\":{\"con\":");
  LoRa.print(event.relative_humidity);
  LoRa.print ("}}");
  LoRa.endPacket();

//Get flame value
  flameVal = analogRead(flamePin); 
  Serial.println(flameVal);

 if (flameVal < 400){
    Serial.println("FIRE");
    digitalWrite(2, 1);
    delay(2000);
    digitalWrite(2, 0);
    LoRa.print("FIRE");
 }
 else {
  LoRa.print(" No fire");
 }

  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Create ContentInstance for the flame sensor 
       //send("/~/mn-cse/gateway/sensorNodeIUTInfo/flame",4,"{\"m2m:cin\":{\"con\":\"OFF\"}}");
  LoRa.beginPacket();
  LoRa.print("/~/mn-cse/mn-name/sensorNodeLora/flame");
  LoRa.print(";");
  LoRa.print("4");
  LoRa.print(";");
  LoRa.print("{\"m2m:cin\":{\"con\":");
  LoRa.print(flameVal);
  LoRa.print ("}}");
  LoRa.endPacket();
  
 

  delay(delayMS);
}
