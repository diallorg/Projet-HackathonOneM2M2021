# Sensor node LoRa

## Download and install Arduino IDE for arduino Uno

Download Arduino version 1.8.9 and the DHT11 library
- Recover the DHT11 sensor, cables, and the UCA LoRa which will serve as Sender
![img](https://hackster.imgix.net/uploads/attachments/1372383/image_RDrwhTs6Px.png?auto=compress%2Cformat&w=740&h=555&fit=max) <br/>
Connect the components following the wiring diagram below:
![img](https://hackster.imgix.net/uploads/attachments/1372383/image_RDrwhTs6Px.png?auto=compress%2Cformat&w=740&h=555&fit=max) <br/>
- Check the Pin of the arduino code retrieved from the GIT so that it corresponds to the connect the pin.
- Configure the arduino IDE by following the procedure 5.1.2. with the folowing parameters : <br/>
<i>
Card type: Arduino Pro or Pro mini <br/>
Processor: ATMEGA 328P (3.3V 8MHz) <br/>
Port: The COM that you connected to the pc <br/>
</i>

## Functionality of this code

The code in the wifi sensor node or the lora Node differs on the support for interacting with the onem2m platform.
In this case the LoRa node sends the REST request to the oneM2M platform over LoRa protocol. The rest of the code is indetic with the one of WiFi Node.

## Run the sensorNodeLoRa receivercode

- Open the the program LoRaReceiverFinal.ino
- Upload and run the code on the UCA board
- The LoRa node sends the REST request to the oneM2M platform over LoRa
- An execution trace of data recieved can be see on the TTY com port display of your computer
