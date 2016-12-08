#ifndef _SENSORS_H
#define _SENSORS_H

#include <LiquidCrystal.h>

#define COLLISION 0
#define OPEN 1

extern LiquidCrystal lcd;
extern bool NewCommand;

extern int BackIR;
extern int FrontIR;

int ReadLightSensor();
int ReadTempSensor();
bool BackCollision();
bool FrontCollision();

#endif
