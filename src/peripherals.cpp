#include "peripherals.h"
#include <Arduino.h>

#define LIGHTSENSOR_PIN A0
#define TEMPSENSOR_PIN A1
#define BACKIR_PIN 38
#define FRONTIR_PIN 13

extern LiquidCrystal lcd(22, 24, 30, 32, 34, 36);
extern bool NewCommand = false;
extern int BackIR = COLLISION;
extern int FrontIR = COLLISION;

int calcTemp(int atemp){
  atemp = log(10000.0*((1024.0/atemp-1)));
  atemp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * atemp * atemp ))* atemp );
  atemp = atemp - 273.15;            // Convert Kelvin to Celcius
  atemp = (atemp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return atemp;
}

int ReadLightSensor() {
  return analogRead(LIGHTSENSOR_PIN);
}

int ReadTempSensor() {
  return calcTemp(analogRead(TEMPSENSOR_PIN));
}

bool BackCollision() {
  return digitalRead(BACKIR_PIN);
}

bool FrontCollision() {
  return digitalRead(FRONTIR_PIN);
}
