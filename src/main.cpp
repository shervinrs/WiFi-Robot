#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "sensors.h"



void setup() {
  // set up LCD size
  lcd.begin(20, 4);

  Serial.begin(9600);

  //serialTrigger(F("Press any key to begin."));

  initializeESP8266();
  connectESP8266();
  displayConnectInfo();

  //serialTrigger(F("Press any key to connect client."));
  //clientDemo();

  serverSetup();

  lcd.setCursor(0, 1);
  lcd.print("Second Line");

  lcd.setCursor(14, 1);
  lcd.print("30");

  lcd.setCursor(10, 3);
  lcd.print("Fourth Line");

  lcd.setCursor(0, 0);
  lcd.print("Mew, world!");

}

void loop() {
  serverDemo();


}
