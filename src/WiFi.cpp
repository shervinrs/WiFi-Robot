#include "SparkFunESP8266WiFi.h"
#include "WiFi.h"
#include "util/ESP8266_AT.h"
#include <SoftwareSerial.h>
#include "sensors.h"
#include "motors.h"

// global values
extern int CommandValue = 0;

//////////////////////////////
// WiFi Network Definitions //
//////////////////////////////
// Replace these two character strings with the name and
// password of your WiFi network.
// const char mySSID[] = "Alk3bi";
// const char myPSK[] = "s1234567";

const char mySSID[] = "FasterThanYou";
const char myPSK[] = "deerleeder";
//////////////////////////////
// ESP8266Server definition //g
//////////////////////////////
// server object used towards the end of the demo.
// (This is only global because it's called in both setup()
// and loop()).
ESP8266Server server = ESP8266Server(80);

//////////////////
// HTTP Strings //
//////////////////
const char destServer[] = "example.com";
const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String httpRequest = "GET / HTTP/1.1\n"
                           "Host: example.com\n"
                           "Connection: close\n\n";

// errorLoop prints an error code, then loops forever.
void errorLoop(int error) {
  Serial.print(F("Error: "));
  Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

// serialTrigger prints a message, then waits for something
// to come in from the serial port.
void serialTrigger(String message) {
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}

void initializeESP8266() {
  // esp8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  // true
  int test = esp8266.begin(9600);
  if (test != true) {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266() {
  esp8266.reset();

  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use esp8266.getMode() to check which mode it's in:
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_AP) { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_AP);
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setAP();
  if (retVal < 0) {           // If it's not in AP mode.
    retVal = esp8266.setAP(); // try again
    if (retVal < 0) {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }

  retVal = esp8266.setSoftAPIP();
  if (retVal < 0) {
    Serial.println(F("softAP IP could not be set correctly"));
  } else {
    Serial.println(F("Mode set to AP"));
  }
}

void displayConnectInfo() {
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0) {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }
  /*
    // esp8266.localIP returns an IPAddress variable with the
    // ESP8266's current local IP address.
    IPAddress myIP = esp8266.localIP();
    Serial.print(F("My IP: "));
    Serial.println(myIP);
  */
}

void clientDemo() {
  // To use the ESP8266 as a TCP client, use the
  // ESP8266Client class. First, create an object:
  ESP8266Client client;

  // ESP8266Client connect([server], [port]) is used to
  // connect to a server (const char * or IPAddress) on
  // a specified port.
  // Returns: 1 on success, 2 on already connected,
  // negative on fail (-1=TIMEOUT, -3=FAIL).
  int retVal = client.connect(destServer, 80);
  if (retVal <= 0) {
    Serial.println(F("Failed to connect to server."));
    return;
  }

  // print and write can be used to send data to a connected
  // client connection.
  client.print(httpRequest);

  // available() will return the number of characters
  // currently in the receive buffer.
  while (client.available())
    Serial.write(client.read()); // read() gets the FIFO char

  // connected() is a boolean return value - 1 if the
  // connection is active, 0 if it's closed.
  if (client.connected())
    client.stop(); // stop() closes a TCP connection.
}

void serverSetup() {
  // begin initializes a ESP8266Server object. It will
  // start a server on the port specified in the object's
  // constructor (in global area)
  server.begin();
  Serial.print(F("Server started! Go to 192.168.1.1"));
  // Serial.println(esp8266.localIP());
  Serial.println();
}

void CheckForCommand() {
  //ESP8266Client client = server.available(50);

  //if (client) {
    if (esp8266.find("+IPD")) {
      //delay(50);
      if (esp8266.find("?")) {
        String msg;
        msg = esp8266.readStringUntil(' ');     // read the message
        String command = msg.substring(0, 3);
        String valueStr = msg.substring(4); // next 3 characters inform the desired angle
        CommandValue = valueStr.toInt(); // convert to integer
        NewCommand = true;
  	   }
    }
}
