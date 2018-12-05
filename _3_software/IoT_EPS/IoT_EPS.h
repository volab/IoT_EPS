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
#include <FastLED.h>

#include "credential.h"
#include "configParam.h"
#include "serverFunction.h"

#define NBRPLUGS 4
#define NUM_LEDS NBRPLUGS /**< for fastLED class */
#define DATA_PIN D7 /**< for fastLED class strip data pin*/
#define CLOCK_PIN D8 /**< for fastLED class strip data pin*/

#include "Cmcp.h"
#include "CPowerPlug.h"
#include "debugSerialPort.h"

#define HTML_JSON_REDPLUGNAME "redPlug"
#define HTML_JSON_GREENPLUGNAME "greenPlug"
#define HTML_JSON_BLUEPLUGNAME "bluePlug"
#define HTML_JSON_YELLOWPLUGNAME "yellowPlug"

#define FLASHERTIME 500

#define PLUG0PIN 0 // MPC23017 numbering pin21 PORTA.0
#define PLUG1PIN 1
#define PLUG2PIN 2
#define PLUG3PIN 3
#define PLUG0_ONOFFLEDPIN 4
#define PLUG1_ONOFFLEDPIN 5
#define PLUG2_ONOFFLEDPIN 6
#define PLUG3_ONOFFLEDPIN 7


#define BP0 D3 
#define BP1 D4
#define BP2 D5
#define BP3 D6



#endif
