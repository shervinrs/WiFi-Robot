#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "TimerOne.h"
#include "my_servo.h"

bool timer300 = false;
int Distance = 0;

void callback() {
  timer300 = true;   // it will activate its related operation in main loop
}

void setup() {
  Timer1.initialize(300000);   // 300ms
  Timer1.attachInterrupt(callback);

  Serial.begin(9600);   // initialize the serial interface to PC

  // Wi-Fi initializtion
  initializeESP8266();
  connectESP8266();
  serverSetup();

  // ultrasonic sensor setup
  PWM_Mode_Setup();

  delay(500);
}

void loop() {
  if (timer300) {   // executes every 300ms
    CheckForCommand();   // check for new command from PC (through wifi)

    Distance = PWM_Mode();   // measure the current distance
    if ((Distance < 20) && (CommandValue == FORWARD) && NewCommand) {   // do not move if there is an obstacle within 20cm
      NewCommand = false;
    }

    if (!NewCommand) {
      carStop();
    }

    timer300 = false;
  }

  // if there is a valid command, apply the command to the motors
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
    NewCommand = false;   // disable command flag to apply it once
  }
}
