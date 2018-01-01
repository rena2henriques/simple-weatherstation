// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************ Adafruit IO Configuration *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "UUUUUUUUUUUUUUUUU"
#define IO_KEY         "KKKKKKKKKKKKKKKKK"

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "NNNNNNNNNNNNNNNN"
#define WIFI_PASS       "PPPPPPPPPPPPPPPP"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

AdafruitIO_Feed *command = io.feed("mybabyiotproject"); // set up the 'command' feed

int state = 0;
int LED_HOT = 5;
int LED_COLD = 4;
int LED_RAIN = 15;

void setup() {
  
  // start the serial connection
  Serial.begin(115200);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);  

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_HOT, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_COLD, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_RAIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_HOT, LOW);
  digitalWrite(LED_COLD, LOW);
  digitalWrite(LED_RAIN, LOW);
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever a message
// is received from Adafruit IO. it was attached to
// the feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  String commandStr = data->toString(); // store the incoming commands in a string
  
  Serial.print("received <- ");
  Serial.println(commandStr);
  
  // if virtual push button was pressed
  if (commandStr.equalsIgnoreCase("button")){
    Serial.println("Virtual push button");
    if (state == 0) {
      // LED ON
      digitalWrite(LED_BUILTIN, LOW);
      state = 1;
    } else {
      // LED OFF
      digitalWrite(LED_BUILTIN, HIGH);
      state = 0;
    }
  }

  if (commandStr.equalsIgnoreCase("rain")){
    Serial.println("It's raining!");
      // LED ON
      digitalWrite(LED_RAIN, LOW);
  }

  if (commandStr.equalsIgnoreCase("clear")){
    Serial.println("It isn't raining!");
    // LED OFF
      digitalWrite(LED_RAIN, HIGH);
  }

  // drops below 30ºC
  if (commandStr.equalsIgnoreCase("offhot")){
    if ( digitalRead(LED_HOT) == LOW)
      digitalWrite(LED_HOT, HIGH);
  }

  // rises above 30ºC
  if (commandStr.equalsIgnoreCase("hot")){
    Serial.println("It's hot outside, but man's not hot!");
      digitalWrite(LED_HOT, LOW);
  }

  // rises above 10ºC
  if (commandStr.equalsIgnoreCase("offcold")){
    if ( digitalRead(LED_COLD) == LOW)
      digitalWrite(LED_COLD, HIGH);
  }

  // drops below 10ºC
  if (commandStr.equalsIgnoreCase("cold")){
    Serial.println("It's cold outside, wear your jacket!");
      digitalWrite(LED_COLD, LOW);
  }
  
 
} 




