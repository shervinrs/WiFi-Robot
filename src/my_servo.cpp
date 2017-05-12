// https://www.dfrobot.com/wiki/index.php/URM37_V4.0_Ultrasonic_Sensor_(SKU:SEN0001)

#include <Arduino.h>
#include "my_servo.h"

unsigned int DistanceMeasured = 0;

 void PWM_Mode_Setup()  {
   pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
   digitalWrite(URTRIG,HIGH);                 // Set to HIGH
   pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
}

unsigned int PWM_Mode()  {
  //Serial.print("Distance Measured=");
  digitalWrite(URTRIG, LOW);                  // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, HIGH);
  unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;  // reading Pin PWM will output pulses
  if(LowLevelTime>=45000)  {                   // the reading is invalid
    //Serial.print("Invalid");
    DistanceMeasured = 0;
  }
  else  {
    DistanceMeasured = LowLevelTime /50;      // every 50us low level pulse stands for 1cm
    //Serial.print(DistanceMeasured);
    //Serial.println("cm");
  }

  return DistanceMeasured;
}
