#include <Arduino.h>
#include "motors.h"

int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 47;     //M1 Direction Control
int directionPin_M1b = 49;     //M1 Direction Control
int directionPin_M2 = 51;     //M2 Direction Control
int directionPin_M2b = 53;     //M2 Direction Control

void carStop(){                 //  Motor Stop
  digitalWrite(speedPin_M2,0);
  digitalWrite(directionPin_M1,LOW);
  digitalWrite(directionPin_M1b,HIGH);
  digitalWrite(speedPin_M1,0);
  digitalWrite(directionPin_M2,LOW);
  digitalWrite(directionPin_M2b,HIGH);
}

void carBack(int leftSpeed,int rightSpeed){         //Move backward
  digitalWrite(directionPin_M1,HIGH);
  digitalWrite(directionPin_M1b,LOW);
  analogWrite (speedPin_M1,rightSpeed);

  digitalWrite(directionPin_M2,HIGH);
  digitalWrite(directionPin_M2b,LOW);
  analogWrite (speedPin_M2,leftSpeed);              //PWM Speed Control
}

void carAdvance(int leftSpeed,int rightSpeed){       //Move forward
  analogWrite (speedPin_M1,rightSpeed);
  digitalWrite(directionPin_M1,LOW);
  digitalWrite(directionPin_M1b,HIGH);

  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M2,LOW);
  digitalWrite(directionPin_M2b,HIGH);
}

void carTurnLeft(int leftSpeed,int rightSpeed){      //Turn Left
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,LOW);
  digitalWrite(directionPin_M1b,HIGH);
  analogWrite (speedPin_M1,rightSpeed);
  digitalWrite(directionPin_M2,HIGH);
  digitalWrite(directionPin_M2b,LOW);
}
void carTurnRight(int leftSpeed,int rightSpeed){      //Turn Right
  analogWrite (speedPin_M2,leftSpeed);
  digitalWrite(directionPin_M1,HIGH);
  digitalWrite(directionPin_M1b,LOW);
  analogWrite (speedPin_M1,rightSpeed);
  digitalWrite(directionPin_M2,LOW);
  digitalWrite(directionPin_M2b,HIGH);
}
