#include "SparkFunESP8266WiFi.h"
#include "WiFi.h"
#include "motors.h"
#include "peripherals.h"
#include "util/ESP8266_AT.h"
#include <SoftwareSerial.h>

extern int CommandValue = 0;

ESP8266Server server = ESP8266Server(80);

void errorLoop(int error) {
  Serial.print(F("Error: "));
  Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

void serialTrigger(String message) {
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}

void initializeESP8266() {
  int test = esp8266.begin(9600);
  if (test != true) {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266() {
  esp8266.reset();

  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_AP) {
    retVal = esp8266.setMode(ESP8266_MODE_AP);
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setAP();
  if (retVal < 0) {           // If it's not in AP mode.
    retVal = esp8266.setAP(); // try again
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setSoftAPIP();
  if (retVal < 0) {
    Serial.println(F("softAP IP could not be set correctly"));
  } else {
    Serial.println(F("Mode set to AP"));
  }
}

void displayConnectInfo() {
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);

  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0) {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }
}

void serverSetup() {
  server.begin();
  Serial.print(F("Server started! Go to 192.168.1.1"));
  // Serial.println(esp8266.localIP());
  Serial.println();
}

void CheckForCommand() {
  NewCommand = false;
  if (esp8266.find("+IPD")) {
    // delay(50);
    if (esp8266.find("?")) {
      String msg;
      msg = esp8266.readStringUntil(' '); // read the message
      String command = msg.substring(0, 3);
      String valueStr = msg.substring(4);
      CommandValue = valueStr.toInt();
      NewCommand = true;
    }
  }
}
