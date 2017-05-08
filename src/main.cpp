#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
//#include "peripherals.h"
#include "TimerOne.h"
#include "my_servo.h"

bool timer300 = false;
int Distance = 0;

void callback() {
  timer300 = true; // will do its related operation in main loop
}

void setup() {
  Timer1.initialize(300000); // 300ms
  Timer1.attachInterrupt(callback);

  Serial.begin(9600);

  // Wi-Fi initializtion
  initializeESP8266();
  connectESP8266();
  serverSetup();

  // servo setup
  //myservo.attach(10); // Pin 10 to control servo
  PWM_Mode_Setup();

  delay(500);
}

void loop() {
  if (timer300) {
    CheckForCommand();

    Distance = PWM_Mode();
    if ((Distance < 20) && CommandValue == FORWARD) {
      NewCommand = false;
    }

    if (!NewCommand) {
      carStop();
    }

    timer300 = false;
  }

  if (NewCommand) {
    switch (CommandValue) {
    case FORWARD:
      carAdvance(100,100);
      break;
    case BACKWARD:
      carBack(100,100);
      break;
    case LEFT:
      carTurnLeft(100,100);
      break;
    case RIGHT:
      carTurnRight(100,100);
      break;
    }
    NewCommand = false;
  }
}
