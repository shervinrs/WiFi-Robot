#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "peripherals.h"
#include "TimerOne.h"

bool timer300 = false;

void callback() {
  timer300 = true; // will do its related operation in main loop
}

void setup() {
  Timer1.initialize(300000); // 300ms
  Timer1.attachInterrupt(callback);

  // set up LCD size
  lcd.begin(20, 4);
  Serial.begin(9600);

  initializeESP8266();
  connectESP8266();
  displayConnectInfo();

  serverSetup();

  lcd.setCursor(0, 0);
  lcd.print("Initialized");
}

void loop() {
  if (timer300) {
    CheckForCommand();

    if (!NewCommand) {
      lcd.setCursor(0, 0);
      lcd.print("Waiting for command ");
      lcd.setCursor(0, 1);
      lcd.print("Stop                ");
      carStop();
    }

    if (BackIR == OPEN) {
      lcd.setCursor(0, 3);
      lcd.print("No Collision        ");
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print("Collision           ");
    }

    if (FrontIR == OPEN) {
      lcd.setCursor(0, 2);
      lcd.print("No Collision        ");
    }
    else {
      lcd.setCursor(0, 2);
      lcd.print("Collision           ");
    }
    timer300 = false;
  }

  BackIR = BackCollision();
  FrontIR  = FrontCollision();

  if (BackIR == COLLISION && CommandValue == BACKWARD) {
    NewCommand = false;
    carStop();
  }

  if (FrontIR == COLLISION && CommandValue == FORWARD) {
    NewCommand = false;
    carStop();
  }

  if (NewCommand) {
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
}
