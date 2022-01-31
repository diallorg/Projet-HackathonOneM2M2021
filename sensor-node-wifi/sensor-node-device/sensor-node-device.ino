
#include <ESP8266WiFi.h>
#include "Timer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 0
#define DHTTYPE    DHT11 
///////////////Parameters/////////////////
// WIFI params
const char* ssid = "OnePlus Alex";
const char* password = "12345678";

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// CSE params
const char* host = "192.168.71.187";
const int httpPort = 8282;

// AE params
const int aePort   = 80;

const char* origin   = " admin:admin";
///////////////////////////////////////////

Timer t;

WiFiServer server(aePort);
int flamePin = A0; // select the input pin for LDR 
int buzzPin = 12; //  Pin du Buzzer D6 (GPIO12)
int temperatureValue = 0; // variable to store the value coming from the temperature sensor 
int humudityValue = 0; // variable to store the value coming from the humidity sensor 
int flameVal;


void setup() {

    Serial.begin(115200);
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;

    delay(10);
    Serial.println();
    Serial.println();
    
    pinMode(12, OUTPUT);
    // Connect to WIFI network
    Serial.print("Connecting to ");
    Serial.println(ssid);
 
    WiFi.persistent(false);
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Start HTTP server
    server.begin();
    Serial.println("Server started");

    // Create AE resource for sensor node 
      String resultat = send("/~/mn-cse/gateway",2,"{\"m2m:ae\":{\"rn\":\"sensorNodeIUTInfo\",\"api\":\"mydevice1.company.com\",\"lbl\":[“Type/sensorNodeWifi Category/HTG Location/43.736627,7.152139”],\"rr\":\"true\",\"poa\":[\"http://"+WiFi.localIP().toString()+":"+aePort+"\"]}}");
  
    if(resultat=="HTTP/1.1 201 Created" || "HTTP/1.1 409 Conflict"){
      
       // Create Container resource for temperature semsor 
       send("/~/mn-cse/gateway/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"temperature\"}}");

       // Create Container resource for humidity sensor
       send("/~/mn-cse/gateway/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"humidity\"}}");
    
      // Create Container resource for the flame sensor (ky-026)
       send("/~/mn-cse/gateway/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"flame\"}}");
       
       // Create ContentInstance for the flame sensor 
       send("/~/mn-cse/gateway/sensorNodeIUTInfo/flame",4,"{\"m2m:cin\":{\"con\":\"OFF\"}}");
       
       }
       
      //every 5 seconds, call the push fonction that reads and sets the sensors values 
      t.every(500*5, push);
  }

// Method in charge of receiving event from the CSE
void loop(){
  t.update();
  // Check if a client is connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  // Read the request
  String req = client.readString();
  Serial.println(req);
  client.flush();
 
  // Send HTTP response to the client
  String s = "HTTP/1.1 200 OK\r\n";
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}


// Method in charge of sending request to the CSE
String send(String url,int ty, String rep) {

  // Connect to the CSE address
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
 
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "error";
  }
  // prepare the HTTP request
  String req = String()+ "POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "X-M2M-Origin: " + origin + "\r\n" +
               //"X-M2M-Origin:" + " admin:admin" + "\r\n" +
               "Content-Type: application/json;ty="+ty+"\r\n" +
               "Content-Length: "+ rep.length()+"\r\n"
               "Connection: keep-alive\r\n\n" + 
               rep;

  Serial.println(req+"\n");
  Serial.println(req);

  // Send the HTTP request
  client.print(req);
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
      //client.stop();
      return "error";
    }
  }

  // Read the HTTP response
  String res="";
  if(client.available()){
    res = client.readStringUntil('\r');
    Serial.print(res);
  }
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  Serial.println();
  return res;

  

}

// Sensor function that reads and pushes sensors values in oneM2M infrastructure 
void push(){
 
  Serial.println("ENVOI");
  sensors_event_t eventT;
  dht.temperature().getEvent(&eventT);
  flameVal = analogRead(flamePin); 
  Serial.println(flameVal);
  
  if (flameVal < 400){
    Serial.println("---------------------FIRE---------------------");
    digitalWrite(12, HIGH);
    delay(2000);
    digitalWrite(12, LOW);
    String dat_on =String()+"{\"m2m:cin\":{\"con\":\""+"ON"+"\"}}";
    send("/~/mn-cse/gateway/sensorNodeIUTInfo/flame",4,dat_on);
    }
    
  else {
    Serial.println("---------------------ALL IS GOOD---------------------");
    String dat_off =String()+"{\"m2m:cin\":{\"con\":\""+"OFF"+"\"}}";
    send("/~/mn-cse/gateway/sensorNodeIUTInfo/flame",4,dat_off);
  }
  
  if (isnan(eventT.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(eventT.temperature);
    Serial.println(F("°C"));
    String data = String()+"{\"m2m:cin\":{\"con\":\""+eventT.temperature+"\"}}";
    send("/~/mn-cse/gateway/sensorNodeIUTInfo/temperature",4,data);
  }
  
  sensors_event_t eventH;
  dht.humidity().getEvent(&eventH);
  if (isnan(eventH.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(eventH.relative_humidity);
    Serial.println(F("%"));
    String data = String()+"{\"m2m:cin\":{\"con\":\""+eventH.relative_humidity+"\"}}";
    send("/~/mn-cse/gateway/sensorNodeIUTInfo/humidity",4,data);
  }
}
