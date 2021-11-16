# HEPHAESTUS PROJECT

## Description 
Hephaestus: is a forest fire prevention tool that serves the fire brigade by locating the different
areas of risk using temperature, wind, CO2, GPS, and humidity sensors, allowing the firemen to take action
before a fire ignites.


## Components
- NodeMCU ESP8266 V0.9
- DHT11 (IDUINO MODULE SE052) -----> PIN D3 (GPIO 0)
- Flame Sensor KY026 -----> PIN A0
- Buzzer -----> PIN D6 (GPIO 12)
![img](https://zupimages.net/up/21/45/f0l3.png)
## Prerequisites 
### Arduino libraries
- Timer-Master
- Adafruit_ESP8266
- DHT_Sensor_Library
- Adafruit_sensor-master
### Configuration

Arduino --> Preferences --> Search for "Additional Boards Mager URLs" : https://arduino.esp8266.com/stable/package_esp8266com_index.json

Tools --> Board --> Board Manager --> Search for "ESP8266" --> Install

Select in Board --> ESP8266 Boards --> NodeMCU 0.9 
## Start

Run the sensorNodeWiFi code

Open the file sensor-nodeV9.ino in the IDE
In the code, replace the "ssid" and "password" variables with the ssid and the password of the wifi on which the mn-cse server is hosted. Upload the program to the ESP8266.
Functionality of this code

Creation of the Application Entity SensorNodeWifi on the Gateway
Creation of "temperature", "humidity", "flame-sensor", "wind" containers
Creation of the Content instances in the associated containers,
Every 5 secondes , the code Retrieve values from the sensor-nodes : DHT11 Humidity and Temperature, Anemometer, Flame Sensor (used for detection & alarm)
Sending the data values to Middle-Node
Creation of the Content Instance in "temperature" containing the value retrieved from the DHT11 temperature sensor.
Creation of the Content Instance in "humidity" containing the value retrieved from the DHT11 humidity sensor.
Creation of the "FIRE" Content Instance in "flame-sensor" if the value retrieved from the flame-sensor is less than 400, ie a flame is detected under 40 cm away from the sensor, and triggering of the buzzer. (used for detection & alarm)

