/**
* @file IoT_EPS\IoT_EPS.h
* @author J.SORANZO
* @date 20 Oct 2018
* @copyright 2018 CC0
* @brief global application header file
*/

#ifndef IOT_EPS_HEADER
#define  IOT_EPS_HEADER
#include <Arduino.h>
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>
//needed for library
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <Wire.h>
#include <RTClib.h>
#include <ESP8266mDNS.h>
#include <Adafruit_MCP23017.h>
#include "credential.h"
#include "configParam.h"
#include "serverFunction.h"

#define DEBUGPORT Serial
#define DEBUGSPEED 115200

#define FLASHERTIME 500

#define PLUG0 0 // MPC23017 numbering pin21 PORTA.0
#define PLUG1 1
#define PLUG2 2
#define PLUG3 3
#define BP0 8 // MCP PORTB.0 pin 1
#define BP1 9
#define BP2 10
#define BP3 11



#endif
