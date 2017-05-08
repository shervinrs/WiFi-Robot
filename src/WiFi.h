#ifndef _WiFi_H
#define _WiFi_H

void errorLoop(int error);
void initializeESP8266();
void connectESP8266();
void displayConnectInfo();
void serverSetup();
void CheckForCommand();
void serialTrigger(String message);

extern int CommandValue;
extern bool NewCommand;

#endif
