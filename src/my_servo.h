#ifndef _SERVO_H
#define _SERVO_H

#include <Servo.h>       // include Servo library

#define URECHO 2         // PWM Output 0-25000US, every 50us represent 1cm
#define URTRIG 4         // PWM trigger pin

unsigned int PWM_Mode(); // for measuring obstacle distance
void PWM_Mode_Setup();   // for pin initilization of ultrasonic sensor

#endif
