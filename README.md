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
![img](https://zupimages.net/up/21/45/d8of.png)
## Prerequisites
### Arduino libraries
- Timer-Master
- Adafruit_ESP8266
- DHT_Sensor_Library
- Adafruit_sensor-master
### Configuration
Go to Arduino --> Preferences --> Enter in "Additional Boards Boards Manager URLs" : https://arduino.esp8266.com/stable/package_esp8266com_index.json

Go to Tools --> Board --> Boards Manager --> Research "ESP8266" --> Install

Select in Board --> ESP8266 Boards --> NodeMCU 0.9
## Start
Open the Arduino program and replace variables "ssid" and "password" by your wifi values 
Download the program on the ESP8266.
## What it does
### Initialisation
- Creation of the Application Entity
- Creation of Containers "temperature", "humidity", "flame-sensor"
- Creation of Content Instance "OFF" dans le container "flame-sensor"
### Acquisition des valeurs des capteurs
- DHT11 Humidity and Temperature
- Flame Sensor
### Envoi des requêtes HTTP sur Middle-Node
- Creation of Content Instance in "temperature" container with the current value  of  DHT11 sensor
- Same for humidity
- Creation of Content Instance "FIRE" in "flame-sensor" container setting initialized to ON and setted to OFF if the collected value is less than  400
- Emission of buzzer if flame is ON 


