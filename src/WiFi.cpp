#include "SparkFunESP8266WiFi.h"
#include "WiFi.h"
#include "motors.h"
#include "util/ESP8266_AT.h"
#include <SoftwareSerial.h>

extern int CommandValue = 0;      // received movement direction from wifi
extern bool NewCommand = false;   // is new command available from base station?

ESP8266Server server = ESP8266Server(80);  // starting server

// loop forever if there is an error
void errorLoop(int error) {
  Serial.print(F("Error: "));
  Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

// for showin data on serial port (not used anymore)
void serialTrigger(String message) {
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}

// ESP8266 initializtion, it checks for ESP8266 availability
void initializeESP8266() {
  int test = esp8266.begin(9600);
  if (test != true) {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

// put ESP8266 in access point mode
void connectESP8266() {
  esp8266.reset();

  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_AP) {
    retVal = esp8266.setMode(ESP8266_MODE_AP); // this mode and its procedure is added to the library
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setAP();   // setAP is added to the library to initialize the board in access point mode
  if (retVal < 0) {           // If it's not in AP mode.
    retVal = esp8266.setAP(); // try again
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setSoftAPIP();   // set IP related data for the board
  if (retVal < 0) {
    Serial.println(F("softAP IP could not be set correctly"));
  } else {
    Serial.println(F("Mode set to AP"));
  }
}

// this function was used for station mode
void displayConnectInfo() {
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);

  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0) {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }
}

// begin the server
void serverSetup() {
  server.begin();
  Serial.print(F("Server started! Go to 192.168.1.1"));
  // Serial.println(esp8266.localIP());
  Serial.println();
}

// check for new commands
void CheckForCommand() {
  NewCommand = false;
  if (esp8266.find("+IPD")) {   // this is the tag for beginning of a received request
    // delay(50);
    if (esp8266.find("?")) {    // required data is after ? in the received data
      String msg;
      msg = esp8266.readStringUntil(' '); // read the message
      String command = msg.substring(0, 3);
      String valueStr = msg.substring(4);
      CommandValue = valueStr.toInt();    // command is a number between 0-4 and its functionality is defined in motors.h
      NewCommand = true;
    }
  }
}
