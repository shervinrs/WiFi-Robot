#ifndef _WiFi_H
#define _WiFi_H

void errorLoop(int error);
void initializeESP8266();
void connectESP8266();
void displayConnectInfo();
void clientDemo();
void serverSetup();
void serverDemo();
void serialTrigger(String message);

#endif
