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
// #include <Array.h>

#include "credential.h"
#include "configParam.h"
#include "serverFunction.h"
#include "bouton.h"

#define NBRPLUGS 4
#define NUM_LEDS NBRPLUGS /**< for fastLED class */
#define DATA_PIN D7 /**< for fastLED class strip data pin*/
#define CLOCK_PIN D8 /**< for fastLED class strip data pin*/

#define CONFIGFILENAME "/config3.json"


#include "Cmcp.h"
#include "CPowerPlug.h"
#include "debugSerialPort.h"

#define HTML_JSON_REDPLUGNAME "redPlug"
#define HTML_JSON_GREENPLUGNAME "greenPlug"
#define HTML_JSON_BLUEPLUGNAME "bluePlug"
#define HTML_JSON_YELLOWPLUGNAME "yellowPlug"

/** @todo define other parameters Json names*/
#define JSON_PARAMNAME_MODE "Mode"
#define MANUAL_MODE "Manuel"
#define TIMER_MODE "Minuterie"
#define CYCLIC_MODE "Cyclique"
#define HEBDO_MODE "Hebdomadaire"
#define CLONE_MODE "Clone"
#define JSON_PARAMNAME_STATE "State"
#define JSON_PARAMNAME_ONDURATION "dureeOn"
#define JSON_PARAMNAME_OFFDURATION "dureeOff"
#define JSON_PARAMNAME_STARTTIME "hDebut"
#define JSON_PARAMNAME_ENDTIME "hFin"
#define JSON_PARAMNAME_ONOFCOUNT "onOffCount"

#define MANUEL_MODE_MAXOFFDURATION 300 //mn
#define TIMER_MODE_MAXONDURATION 300 //mn

#define FLASHERTIME 500

#define PLUG0PIN 0 // MPC23017 numbering pin21 PORTA.0
#define PLUG1PIN 1
#define PLUG2PIN 2
#define PLUG3PIN 3
#define PLUG0_ONOFFLEDPIN 4
#define PLUG1_ONOFFLEDPIN 5
#define PLUG2_ONOFFLEDPIN 6
#define PLUG3_ONOFFLEDPIN 7


#define BP0 D6 
#define BP1 D5
#define BP2 D4
#define BP3 D3

#define WIFILED D0
#define WIFILED_FLASH_FAST 100
#define WIFILED_FLASH_SLOW 500
#define WIFILED_FLASH_COUNT 20


#endif
