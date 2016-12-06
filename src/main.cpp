#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "sensors.h"
#include "Timer.h"

int count = 0;
Timer t;

void callback() {
  count++;
  lcd.setCursor(0, 3);
  lcd.print(count);
  CheckForCommand();
}

void setup() {
  t.every(100, callback);

  // set up LCD size
  lcd.begin(20, 4);
  Serial.begin(9600);

  // serialTrigger(F("Press any key to begin."));

  initializeESP8266();
  connectESP8266();
  displayConnectInfo();

  // serialTrigger(F("Press any key to connect client."));
  // clientDemo();

  serverSetup();

  lcd.setCursor(0, 0);
  lcd.print("Initialized");

  //Timer.attachInterrupt(callback);
}

void loop() {
  t.update();

  if (flag3) {
    lcd.setCursor(0, 1);
    lcd.print(CommandValue);

    lcd.setCursor(0, 0);
    lcd.print("Data Received");

    lcd.setCursor(0, 1);

    switch (CommandValue) {
    case FORWARD:
      lcd.print("Forward ");
      break;
    case BACKWARD:
      lcd.print("Backward");
      break;
    case LEFT:
      lcd.print("Left    ");
      break;
    case RIGHT:
      lcd.print("Right   ");
      break;

      flag3 = false;
    }
  }
}
