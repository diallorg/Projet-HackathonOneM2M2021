#include <ESP8266WiFi.h>
#include "Timer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 0
#define DHTTYPE    DHT11 
///////////////Parameters/////////////////
// WIFI params
const char* ssid = "LPiOTIA";
const char* password = "";
//const char* ssid = "LPiOTIA";
//const char* password = "";

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// CSE params
const char* host = "192.168.143.139";
const int httpPort = 8282;

// AE params
const int aePort   = 80;
//const char* origin   = "Cae-device1";
//const char* origin   = "Cae-SensorNode";
//const char* origin   = "Cae-nodemcu";
const char* origin   = " admin:admin";
///////////////////////////////////////////

Timer t;

WiFiServer server(aePort);
int sensorPin = A0; // select the input pin for LDR 
//int sensorValue = 0; // variable to store the value coming from the sensor 
int temperatureValue = 0; // variable to store the value coming from the temperature sensor 
int humudityValue = 0; // variable to store the value coming from the humidity sensor 
void setup() {

    Serial.begin(115200);
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    /*Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    // Et ou est la valeur courante de temperature ? 
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.*/
    
    dht.humidity().getSensor(&sensor);
    /*Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    // Et ou est la valeur courante de humidity ? */
    delayMS = sensor.min_delay / 1000;

    delay(10);

    // Configure pin 5 for LED control
    /*pinMode(5, OUTPUT);
    digitalWrite(5, 0);*/

    Serial.println();
    Serial.println();

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
      String resultat = send("/~/mn-cse/mn-name",2,"{\"m2m:ae\":{\"rn\":\"sensorNodeIUTInfo\",\"api\":\"mydevice1.company.com\",\"rr\":\"true\",\"poa\":[\"http://"+WiFi.localIP().toString()+":"+aePort+"\"]}}");
  
    if(resultat=="HTTP/1.1 201 Created || HTTP/1.1 409 Conflict"){
       // Create Container resource for temperature semsor 
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"temperature\"}}");

       // Create ContentInstance resource for temperature instance value
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo/temperature",4,"{\"m2m:cin\":{\"con\":\"20\"}}");

       // Create Container resource for humidity sensor
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"humidity\"}}");
    
       // Create ContentInstance resource for humidity instance value
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo/humidity",4,"{\"m2m:cin\":{\"con\":\"100\"}}");

       
       // Create Container resource for the alarm (led)
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo",3,"{\"m2m:cnt\":{\"rn\":\"alarm\"}}");
       // Create ContentInstance for the alarm 
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo/alarm",4,"{\"m2m:cin\":{\"con\":\"OFF\"}}");
       // Create Subscription to the alarm control 
       send("/~/mn-cse/mn-name/sensorNodeIUTInfo/alarm",23,"{\"m2m:sub\":{\"rn\":\"alarm_sub\",\"nu\":[\"Cae-SensorNode\"],\"nct\":1}}");
      }
      //every 5 seconds, call the push fonction that reads and sets the sensors values 
      t.every(1000*5, push);
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

  // Switch the Alarme state according to the received value
  if (req.indexOf("ON") != -1){
    digitalWrite(5, 1);
  }else if (req.indexOf("OFF") != -1){
    digitalWrite(5, 0);
  }else{
    Serial.println("invalid request");
    client.stop();
    return;
  }
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
               "Connection: close\r\n\n" + 
               rep;

  Serial.println(req+"\n");
  Serial.println(req);

  // Send the HTTP request
  client.print(req);
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
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
  if (isnan(eventT.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(eventT.temperature);
    Serial.println(F("°C"));
    String data = String()+"{\"m2m:cin\":{\"con\":\""+eventT.temperature+"\"}}";
    send("/~/mn-cse/mn-name/sensorNodeIUTInfo/temperature",4,data);
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
    send("/~/mn-cse/mn-name/sensorNodeIUTInfo/humidity",4,data);
  }
}
