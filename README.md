# The Simplest Weather Station
A simple Weather Station using 3 LEDs and a NodeMCU with the help of IFTTT and Adafruit IO.

The LED's state correspond to three indicators:
* Green LED ON: It has been predicted to rain
* Yellow LED ON: It has been predicted that temperatures have dropped below 10ºC
* Red LED ON: It has beens predicted that temperatures have risen above 30ºC

IFTTT will have some triggers configured and send some data to Adafruit.IO platform when some weather prediction is true. The NodeMCU will be able to read the data stored in a given feed on Adafruit.IO, execute some logic and turn LEDs on.

## Adding NodeMCU to Arduino IDE:

You can learn how to do it here:
> https://github.com/esp8266/Arduino

## Libraries needed:

The following libraries will be used for our Arduino code. Download the following libraries:

* Arduino http client library (https://github.com/arduino-libraries/ArduinoHttpClient)
* Arduino IO library (https://github.com/adafruit/Adafruit_IO_Arduino)
* Adafruit MQTT library (https://github.com/adafruit/Adafruit_MQTT_Library)

Navigate to Sketch-> Include Library -> Manage Libraries on your Arduino IDE and add the libraries above.

## Adafruit IO:

Adafruit IO is a datalogging service availabe for communicating a microcontroller to the Web. With it you can download data from the cloud.

Sign up at https://io.adafruit.com/ and create a new feed give it a name. In my case it's called *mybabyiotproject*. With it you can store commands received from the IFTTT App and read them with the NodeMCU.

You will need to insert your username and api key from the website in the code.

## IFTTT:

Create the following applets on the IFTTT app:

* Press a button to send the message "button" to the Adafruit IO feed. With this widget you can turn ON and OFF the built in LED from the micro-controller.

* Current condition changes to rain (Weather Underground).

* Current condition changes to clear (Weather Underground).

* Current temperature drops below 10ºC (Weather Underground). Sends the command 'cold' to the feed.

* Current temperature rises above 10ºC (Weather Underground). Sends the command 'offcold' to the feed.

* Current temperature rises above 30ºC (Weather Underground). Sends the command 'hot' to the feed.

* Current temperature drops below 30ºC (Weather Underground). Sends the command 'offhot' to the feed.

## WI-FI connection

Specify your router SSID and password to configure ESP8266 Wi-fi connection.
