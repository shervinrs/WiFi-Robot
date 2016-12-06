#ifndef _MOTORS_H
#define _MOTORS_H

#define FORWARD 1
#define BACKWARD 4
#define LEFT 2
#define RIGHT 3
#define STOP 0

void carStop();
void carBack(int leftSpeed,int rightSpeed);
void carAdvance(int leftSpeed,int rightSpeed);
void carTurnLeft(int leftSpeed,int rightSpeed);
void carTurnRight(int leftSpeed,int rightSpeed);

#endif
