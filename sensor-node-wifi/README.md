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
## Prérequis
### Arduino libraries
- Timer-Master
- Adafruit_ESP8266
- DHT_Sensor_Library
- Adafruit_sensor-master
### Configuration
Go to Arduino --> Preferences --> Enter in "URL de gestionnaire de carte" : https://arduino.esp8266.com/stable/package_esp8266com_index.json

Go to Tools --> Type de carte --> Gestionnaire de carte --> Rechercher "ESP8266" --> Installer

Selectionner dans Type de carte --> ESP8266 Boards --> NodeMCU 0.9
## Start
Ouvrir le programme Arduino, remplacer les variables "ssid" et "password" par le ssid et le password du wifi sur lequel est hebergé le serveur mn-cse.
Téléverser le programme sur l'ESP8266.
## What it does
### Initialisation
- Création de l'Application Entity
- Création des Containers "temperature", "humidity", "flame-sensor"
- Création du Content Instance "OFF" dans le container "flame-sensor"
### Acquisition des valeurs des capteurs
- DHT11 Humidité et Temperature
- Flame Sensor
### Envoi des requêtes HTTP sur Middle-Node
- Création de Content Instance dans "temperature" contenant la valeur acquise du capteur DHT11 concernant la temperature
- Création de Content Instance dans "humidity" contenant la valeur acquise du capteur DHT11 concernant l'humidité
- Création du Content Instance "FIRE" dans "flame-sensor" si la valeur acquise du capteur flame-sensor est inférieure à 400 soit à la présence d'une flamme aux environs de 40 cm du capteur et déclenchement du buzzer.



