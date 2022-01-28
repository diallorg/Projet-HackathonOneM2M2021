# HEPHAESTUS PROJECT

## Description 
Hephaestus: is a forest fire prevention tool that serves the fire brigade by locating the different
areas of risk using temperature, wind, CO2, GPS and humidity sensors, allowing the firemen to take action
before a fire ignites.

## Gateway branch
This branch contains the repository and the documentation of how is made the gateway.

## How it works
The gateway is the oneM2M middle-node server that will retrieve data from applications entities. The middle-node server is hosted on a raspberry pi with raspbianOS.

## MN-CSE configuration
To allow the mn-cse to anthentificate itself on the in-cse, the following modifcations has been wrote on the configuration file at /mn-cse/configuration/config.ini :
```
  org.eclipse.om2m.cseBaseName=gateway
  org.eclipse.om2m.cseBaseAddress=192.168.143.139
  org.eclipse.om2m.remoteCseAddress=192.168.143.151
```

## Steps of installation

### 1. Raspberry Pi Setup
- Installing Raspbian OS with micro sd card flashed (https://www.raspberrypi.com/documentation/computers/getting-started.html#installing-the-operating-system).
- Update all packages on Raspbian with the terminal (Ctrl + Alt + T) :
```bash
  sudo apt-get update
  sudo apt-get upgrade
```
- Connect the raspberry pi to your local network

### 2. MN-CSE Setup
- Clone the gateway projet on the raspberry pi.
- You may have to edit the configuration file with your local IP addresses :
```
  org.eclipse.om2m.cseBaseAddress=XXX.XXX.XXX.XXX
  org.eclipse.om2m.remoteCseAddress=XXX.XXX.XXX.XXX
```
- Go to /gateway/mn-cse/ and enter the following command on a terminal (Ctrl + Alt + T) :
```bash
  sudo bash ./start.sh
```
- Wait until the middle-node has correctly started
- Open a web browser and go to http://localhost:8282/webpage
- The credentials are admin and admin
- Press Login 
