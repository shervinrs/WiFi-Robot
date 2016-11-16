#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"

void setup() {
  /* For WiFi Module
  Serial.begin(9600);
  initializeESP8266();
  connectESP8266();
  displayConnectInfo();

  serialTrigger(F("Press any key to connect client."));
  clientDemo();

  serialTrigger(F("Press any key to test server."));
  serverSetup();
*/
}

void loop() {
  //serverDemo(); // For WiFi Module
  carAdvance(100,100);
  delay(1000);
  carBack(100,100);
  delay(1000);
  carTurnLeft(250,250);
  delay(1000);
  carTurnRight(250,250);
  delay(1000);
}
