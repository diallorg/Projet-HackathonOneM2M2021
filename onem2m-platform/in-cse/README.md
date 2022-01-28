# HEPHAESTUS PROJECT

## Description 
Hephaestus: is a forest fire prevention tool that serves the fire brigade by locating the different
areas of risk using temperature, wind, CO2, GPS and humidity sensors, allowing the firemen to take action
before a fire ignites.

## Infrastructure-node branch
This branch contains the repository and the documentation of how is made the infrastructure-node.

## How it works
The infrastructure-node is the oneM2M infrastructure-node server that will show current authentificated gateways (middle-node servers). The infrastructure-node server is hosted on a raspberry pi with raspbianOS.

## IN-CSE configuration
The following modifcation has been wrote on the configuration file at /in-cse/configuration/config.ini :
```
  org.eclipse.om2m.cseBaseAddress=192.168.143.151
```

## Steps of installation

### 1. Raspberry Pi Setup
- Installing Raspbian OS with micro sd card flashed (https://www.raspberrypi.com/documentation/computers/getting-started.html#installing-the-operating-system).
- Update all packages on Raspbian with the terminal (Ctrl + Alt + T) :
```bash
  sudo apt-get update
  sudo apt-get upgrade
```
- Connect the raspberry pi to your local network.

### 2. IN-CSE Setup
- Clone the infrastructure-node project on the raspberry pi.
- You may have to edit the configuration file with your local IP address :
```
  org.eclipse.om2m.cseBaseAddress=XXX.XXX.XXX.XXX
```
- Go to /server/in-cse/ and enter the following command on a terminal (Ctrl + Alt + T) :
```bash
  sudo bash ./start.sh
```
- Wait until the middle-node has correctly started.
- Open a web browser and go to http://localhost:8080/webpage.
- The credentials are admin and admin.
- Press Login.
- If the gateway project is running, you should see it in the in-name content.
