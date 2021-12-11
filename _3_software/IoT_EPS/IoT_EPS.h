/**
* @file IoT_EPS\IoT_EPS.h
* @author J.SORANZO
* @date 20 Oct 2018
* @copyright 2018 CC0
* @brief global application header file
*/

#ifndef IOT_EPS_HEADER
#define  IOT_EPS_HEADER

#include "config.h"
#include "config_advanced.h"


#include <Arduino.h>
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>

//needed for library
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <Wire.h>
#include <RTClib.h>
#include <ESP8266mDNS.h>
// #include <Adafruit_MCP23017.h>
/** DONE 13/07/2019 [NECESSARY] try to remove Adafruit_MCP23017.h */
#include <FastLED.h>
// #include <Array.h>
#include <nanoI2CIOExpLib.h>
// #include "nanoI2CIOExpLib.h"
#include <user_interface.h> //espressif SDK function
//Arduino\Croquis\hardware\esp8266com\esp8266\tools\sdk\include

#include <NTPClient.h>
#include <WiFiUdp.h> 


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #include <ESP8266Ping.h>
// #include <Pinger.h>

#include "SerialCommand.h"
#include "debugSerialPort.h"
#include "credential.h"
#define MAX_WIFI_CONNECT_RETRY 30 /**< @brief In Station mode number of try before to switch to access point connection*/

#include "configParam.h"

#include "bouton.h"
#include "cnano.h"
#include "cEpsStrTime.h"

#include "CPowerPlug.h"
#include "jsonIotEps.h"
#include "CRtc.h"
#include "CServerWeb.h"
//#include "serverFunction.h"
#include "csysstat.h"
#include "CWifiLink.h"
#include "oledMessages.h"


// #include "Flasher.h"
// #include "CRtc.h"
#include "cswitchnano.h"

#include "cattiny_i2C_watchdog.h"




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

#define JSON_SSID_NAME "ssid" //for station mode
#define JSON_PPASS_NAME "pass"
#define JSON_APSSID_NAME "softApSsid" //for AP mode
#define JSON_APPASS_NAME "softApPass"

 

// #include "Cmcp.h"


#include "tempo.h"

// #define WIFILED D0

#include "csystem.h"

// const String necessaryFileList[ NECESSARY_FILE_NBR ] ={
//       "/index.html"
//     , "/config4.json"
//     , "/config4copie1.json"
//     , "/config4copie2.json"
//     /** @todo [NECESSARY] only one of the 3 json file is necessary to run !!!*/
//     , "/firstboot.html"
//     // and why no credentials file ? because on firstboot we creat it
//     // and after ???
//     /** @todo [NECESSARY to check]possible bug if credentials disapear - in case of change cred we check
// if file exist and tag an fsErr if not */
//     // , "config.html"
//     , "/js/main.js"
//     , "/js/plug.js"
//     , "/js/regExPatern.js"
//     , "/js/table.js"
//     // , "/js/jquery-3.3.1.min.js"
//     // , "/js/bootstrap.min.js"
//     , "/css/sidebar.css"
//     , "/css/style.css"
//     // , "/css/bootstrap.min.css"
//     // , "/defConfig.json"
//     //config_tag.htm ?
// };

#endif
