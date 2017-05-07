#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
#include "motors.h"
#include "peripherals.h"
#include "TimerOne.h"
#include "my_servo.h"

bool timer300 = false;

unsigned long time = 0;
unsigned long urmTimer = 0;
int pos = 0;  // variable to store the servo position
bool up = true;

Servo myservo;

void callback() {
  timer300 = true; // will do its related operation in main loop
}

void setup() {
  Timer1.initialize(300000); // 300ms
  Timer1.attachInterrupt(callback);

  // set up LCD size
  //lcd.begin(20, 4);

  Serial.begin(9600);

  // Wi-Fi initializtion
  //initializeESP8266();
  //connectESP8266();
  //serverSetup();

  // servo setup
  myservo.attach(10); // Pin 9 to control servo
  PWM_Mode_Setup();

  delay(500);
}

void loop() {
  if(millis()-time>=20){                           // interval 0.02 seconds
    time=millis();                                 // get the current time of programme
    if(up){                                        // judge the condition
     if(pos>=0 && pos<=179){
       pos=pos+1;                                  // in steps of 1 degree
       myservo.write(pos);                         // tell servo to go to position in variable 'pos'
     }
     if(pos>179)  up= false;                       // assign the variable again
   }
    else {
     if(pos>=1 && pos<=180){
       pos=pos-1;
       myservo.write(pos);
     }
     if(pos<1)  up=true;
   }
  }

  if(millis()-urmTimer>50){
    urmTimer=millis();
    PWM_Mode();
  }


  /*
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
  */
}
