#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "sensors.h"
#include "TimerOne.h"

#define COLLISION 0
#define OPEN 1

int count = 0;
int IR0 = 0;
int IR1 = 0;

void callback() {
  timer200 = true;
}

void setup() {
  Timer1.initialize(300000);
  Timer1.attachInterrupt(callback);

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
}

void loop() {
  if (timer200) {
    CheckForCommand();

    if (!NewCommand) {
      lcd.setCursor(0, 0);
      lcd.print("Waiting for command ");
      lcd.setCursor(0, 1);
      lcd.print("Stop                ");
      carStop();
    }

    if (IR0 == OPEN) {
      lcd.setCursor(0, 3);
      lcd.print("No Collision        ");
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print("Collision           ");
      if (CommandValue == BACKWARD) {
        NewCommand = false;
        carStop();
      }
    }

    if (IR1 == OPEN) {
      lcd.setCursor(0, 2);
      lcd.print("No Collision        ");
    }
    else {
      lcd.setCursor(0, 2);
      lcd.print("Collision           ");
      if (CommandValue == FORWARD) {
        NewCommand = false;
        carStop();
      }
    }

    timer200 = false;
  }

  if (NewCommand) {
    count++;
    lcd.setCursor(0, 3);
    lcd.print(count);

    lcd.setCursor(0, 1);
    lcd.print(CommandValue);

    lcd.setCursor(0, 0);
    lcd.print("Data Received       ");

    lcd.setCursor(0, 1);

    switch (CommandValue) {
    case FORWARD:
      lcd.print("Forward             ");
      carAdvance(100,100);
      break;
    case BACKWARD:
      lcd.print("Backward            ");
      carBack(100,100);
      break;
    case LEFT:
      lcd.print("Left                ");
      carTurnLeft(100,100);
      break;
    case RIGHT:
      lcd.print("Right               ");
      carTurnRight(100,100);
      break;
    }

    NewCommand = false;
  }


IR0 = digitalRead(38);
IR1  = digitalRead(13);


}
