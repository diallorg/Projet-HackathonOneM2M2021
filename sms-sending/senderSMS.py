import serial
import RPi.GPIO as GPIO      
import os, time
 
lvA 
vitProp 
lien 
# Creation of 3 variables to send 3 different messages
a = 'Alerte : ' + str(lvA) + '\n'
v = 'Vitesse de propagation estimee : ' + str(vitProp) + '\n'
l = 'Location :' + str(lien) +'\n'
print(a)
print(v)
print(l)
# Activation of the serial port
phone = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1)

#Code to send the message
phone.write(b'AT\r\n')
time.sleep(1)

phone.write(b'AT+CMGF=1\r\n')
time.sleep(1)

phone.write(b'AT+CNMI=2,1,0,0,0\r\n')
time.sleep(1)

phone.write(b'AT+CMGS=\<destination number phone>\r\n')
time.sleep(1)

phone.write(bytes(a, encoding='utf=8'))
phone.write(bytes(v, encoding='utf=8'))
phone.write(bytes(l, encoding='utf=8'))
time.sleep(2)

phone.write(b'\x1A') #Sending SMS
time.sleep(2)

