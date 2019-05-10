/**
* @file IoT_EPS\IoT_EPS.h
* @author J.SORANZO
* @date 20 Oct 2018
* @copyright 2018 CC0
* @brief global application header file
*/

#ifndef IOT_EPS_HEADER
#define  IOT_EPS_HEADER

#define DEFAULT_PREFIX_NAME "ESP_IOT"
#define FIRSTBOOTFORMFILENAME "/firstboot.htm"

#define NOT_FOUND "nf" //return code for extractParam()

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
/** @todo try to remove Adafruit_MCP23017.h0 */
#include <FastLED.h>
// #include <Array.h>
#include <nanoI2CIOExpLib.h>
// #include "nanoI2CIOExpLib.h"
#include <user_interface.h> //espressif SDK function
//Arduino\Croquis\hardware\esp8266com\esp8266\tools\sdk\include

#define CONFIGFILENAME "/config4.json"
#include "SerialCommand.h"
#include "debugSerialPort.h"
#include "credential.h"
#include "configParam.h"
#include "serverFunction.h"
#include "bouton.h"
#include "cEpsStrTime.h"
#include "Flasher.h"
#include "CRtc.h"
#include "cswitchnano.h"
#include "csysstat.h"

// #define FBTAG_STASSID "default_STA_SSID"
// #define FBTAG_STAPWD "pwd_STA"
#define FBTAG_APSSID "default_AP_SSID" 
#define FBTAG_APPWD "azertyuiop"
#define FBTAG_WARNIG_STAACCES_IMPOSSIBLE "<!--FB_WARNING_TAG-->"
#define FB_WARNING_STAACCES_IMPOSSIBLE_MESS "<div id=\"FB_STA_WARNING\">Connexion impossible, vérifiez vos identifiants</div>"
#define FB_PARAMNAME_MODE "mode_selector"
#define FB_PARAMVAL_MODEAP "AP"
#define FB_PARAMVAL_MODESTA "STA"
#define FB_PARAMNAME_STASSID "STA_SSID"
#define FB_PARAMNAME_STAPASS "STA_PWD"
#define FB_PARAMNAME_APSSID "AP_SSID"
#define FB_PARAMNAME_APPASS "AP_PWD"

 
#define DEFAULTIPADD "192.168.95.42"
#define NBRPLUGS 4
#define NUM_LEDS NBRPLUGS /**< for fastLED class */
#define DATA_PIN D7 /**< for fastLED class strip data pin*/
#define CLOCK_PIN D8 /**< for fastLED class strip data pin*/



// #include "Cmcp.h"
#include "cnano.h"
#include "CPowerPlug.h"
#include "tempo.h"

#define HTML_JSON_REDPLUGNAME "redPlug"
#define HTML_JSON_GREENPLUGNAME "greenPlug"
#define HTML_JSON_BLUEPLUGNAME "bluePlug"
#define HTML_JSON_YELLOWPLUGNAME "yellowPlug"

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
#define JSON_PARAMNAME_NEXTSWITCH "nextTimeToSwitch"
#define JSON_PARAMNAME_PAUSE "Pause"
#define JSON_PARAMNAME_CLONEDPLUG "clonedPlug"

#define CLONEDPARAMNUMBER 8

#define HTMLREQ_SUNDAY "Dimanche" //it is allthough the value in html request
#define HTMLREQ_MONDAY "Lundi"
#define HTMLREQ_TUESDAY "Mardi"
#define HTMLREQ_WEDNESTDAY "Mercredi"
#define HTMLREQ_THURSDAY "Jeudi"
#define HTMLREQ_FRIDAY "Vendredi"
#define HTMLREQ_SATURDAY "Samedi"



#define TIME_STRING_SEPARATOR ":"

#define HTML_OFFDURATION_DEFAULT_VALUE "en minutes"
#define HTML_ENDTIME_DEFAULT_VALUE "HH:MM"


#define MANUEL_MODE_MAXOFFDURATION 300 //mn
#define TIMER_MODE_MAXONDURATION 300 //mn


#define FLASHERTIME 500 //ms


#define PLUG0PIN 0 // MPC23017 numbering pin21 PORTA.0
#define PLUG1PIN 1
#define PLUG2PIN 2
#define PLUG3PIN 3
#define PLUG0_ONOFFLEDPIN 4
#define PLUG1_ONOFFLEDPIN 5
#define PLUG2_ONOFFLEDPIN 6
#define PLUG3_ONOFFLEDPIN 7

// #define MAINSWITCHPIN 8 //nanoI2CIOExpander pin D10
#define MAINSWITCHPIN D0 //Direct on ESP pin
#define SPECIALBP 10 //to ask plug state
#define MAINPOWLED 9 //nanoI2CIOExpander pin D11

#define BP0 D6 
#define BP1 D5
#define BP2 D4
#define BP3 D3

// #define WIFILED D0
#define WIFILED 8 //nanoI2CIOExpander pin D10
#define WIFILED_FLASH_FAST 100
#define WIFILED_FLASH_SLOW 500
#define WIFILED_FLASH_COUNT 20
#define WIFILED_SOFTAP_FLASH 50
#define WIFILED_SOFTAP_PERIOD 2000
#define MAX_WIFI_CONNECT_RETRY 30 /**< @brief In Station mode number of try before to switch to access point connection*/



#endif
