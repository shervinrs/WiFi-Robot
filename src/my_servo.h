#ifndef _SERVO_H
#define _SERVO_H

#include <Servo.h>                                  // Include Servo library

#define URECHO 2         // PWM Output 0-25000US,Every 50US represent 1cm
#define URTRIG 4         // PWM trigger pin

unsigned int PWM_Mode();
void PWM_Mode_Setup();

extern Servo myservo;                                      // create servo object to control a servo

#endif
