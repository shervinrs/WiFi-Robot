// # Editor    : Jiang from DFRobot
// # Data      : 24.07.2012

// # Product name:ultrasonic scanner Kit
// # Product SKU:SEN0001
// # Version :  0.2

// # Description:
// # The Sketch for scanning 180 degree area 4-500cm detecting range

// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 3 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// # Pin mode: PWM
// # Working Mode: PWM passive control mode.
// # If it is your first time to use it,please make sure the two jumpers to the right hand
// # side of the device are set to TTL mode. You'll also find a secondary jumper on
// # the left hand side, you must break this connection or you may damage your device.

// https://www.dfrobot.com/wiki/index.php/URM37_V4.0_Ultrasonic_Sensor_(SKU:SEN0001)

#include <Arduino.h>
#include "my_servo.h"

unsigned int DistanceMeasured = 0;

 void PWM_Mode_Setup()  {
   pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
   digitalWrite(URTRIG,HIGH);                 // Set to HIGH
   pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
}

unsigned int PWM_Mode()  {                    // a low pull on pin COMP/TRIG  triggering a sensor reading
  //Serial.print("Distance Measured=");
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);                 // reading Pin PWM will output pulses
  unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
  if(LowLevelTime>=45000)  {                   // the reading is invalid.
    //Serial.print("Invalid");
    DistanceMeasured = 0;
  }
  else  {
    DistanceMeasured = LowLevelTime /50;      // every 50us low level stands for 1cm
    //Serial.print(DistanceMeasured);
    //Serial.println("cm");
  }

  return DistanceMeasured;
}
