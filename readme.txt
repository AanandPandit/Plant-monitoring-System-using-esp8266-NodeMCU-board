This folder contains 
1. 	'plant_monitoring_system.aia'
2. 	'plant_monitoring_system.apk'
3. 	'Plant monitoring system.ino'
4. 	Fonts used in apk.
5. 	Icons used in apk.
6. 	Connections drawing

ABOUT PROJECT
--------------

|_____________________________________________________________________________________________|
|/ This project is based on monitoring the plant. 					     \|
|/ Materials Required : esp8266 board, breadboard, dht11, soil moisture sensor, jumper wires.\|
|---------------------------------------------------------------------------------------------|
 
Procedure to connect: 
1. Connect dht11 1st pin (+) to 3v3 of esp8266.
2. Connect dht11 2nd pin (out) to D1 of esp8266.
3. Connect dht11 4th pin (-) to GND of esp8266. Leave the 3rd pin as it is.

4. Connect soil moisture sensor (+) pin to 3v3 of esp8266.
5. Connect soil moisture sensor (-) pin to GND of esp8266.
6. Connect soil moisture sensor (out) pin to A0 of esp8266.

7. Connect all 3 LEDs to (+) pins to D0, D2, D3 of esp8266 respectively and (-) pins to GND.

9. Upload the code to esp8266.

8. Go to https://thingspeak.com/ and create the channel and setup.

9. Go to https://ai2.appinventor.mit.edu/ for mit app inventor and import the .aia file and make changes Read API key, Write API key, Home URL of Web Viewer.



Project by : AANAND PANDIT
