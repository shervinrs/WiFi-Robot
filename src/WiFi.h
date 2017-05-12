#ifndef _WiFi_H
#define _WiFi_H

void errorLoop(int error);           // loop forever if there is an error
void initializeESP8266();            // ESP8266 initializtion, it checks for ESP8266 availability
void connectESP8266();               // put ESP8266 in access point mode
void displayConnectInfo();           // this function was used for station mode
void serverSetup();                  // begin the server
void CheckForCommand();              // check for new commands
void serialTrigger(String message);  // for showin data on serial port (not used anymore)

extern int CommandValue;             // received movement direction from wifi
extern bool NewCommand;              // is new command available from base station?

#endif
