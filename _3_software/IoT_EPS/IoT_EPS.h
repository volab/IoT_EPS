/**
* @file IoT_EPS\IoT_EPS.h
* @author J.SORANZO
* @date 20 Oct 2018
* @copyright 2018 CC0
* @brief global application header file
*/

#ifndef IOT_EPS_HEADER
#define  IOT_EPS_HEADER

#define NTPSERVER "fr.pool.ntp.org"
// #define OFFSET_HEURE 2 //ETE
#define OFFSET_HEURE 1 //Hiver
/** @todo [NECESSARY]Passage heure d'hiver/été : soit automatique soit configurable via l'interface */
#define DEFAULT_PREFIX_NAME "ESP_IOT"
#define FIRSTBOOTFORMFILENAME "/firstboot.htm"
#define CONFIGFORMFILENAME "/config_tag.htm"
#define APMODEINDEXPAGENAME "/apmodeindex.htm"
/** @todo [NECESSARY] (integration) replace config_tag.htm by the right file name and or the right file */
#define DEFAULT_LED_LUMINOSITY 15
#define FLASH_ERROR_PERIODE 500 //ms

#define INTERNET_HEALTH_TARGET "http://www.google.fr/"

#define NOT_FOUND "nf" //return code for extractParam()
#define HTML_ALLARGS_SEPARATOR "|"

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
#define SECPERHOURS (int)3600

// #include <ESP8266Ping.h>
// #include <Pinger.h>



#define CONFIGFILENAME "/config4.json"
#define DEFCONFIGFILENAME "/defConfig.json"
#define CREDENTIALFILENAME "/credentials.json"


#include "SerialCommand.h"
#include "debugSerialPort.h"
#include "credential.h"
#define MAX_WIFI_CONNECT_RETRY 30 /**< @brief In Station mode number of try before to switch to access point connection*/
#include "configParam.h"
#include "serverFunction.h"
#include "bouton.h"
#include "cEpsStrTime.h"
// #include "Flasher.h"
#include "CRtc.h"
#include "cswitchnano.h"
#include "csysstat.h"
#include "cattiny_i2C_watchdog.h"
#define RTC_UPDATE_PERIOD 15 //every 15mn
#define RTC_ALLOWED_TIME_ERROR 20//seconds
#define I2C_CBIT_TEST_PERIOD 60 * 1000 //ms it smells millis() ;-)
#define I2C_RETRIES 5
#define CBIT_TIME 60000 // period of CBIt in ms

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

#define HTML_EMPLACEMENT_NAME "emplacement"
#define HTML_SOFTAPIP_NAME "softAP_IP"
#define HTML_ALLLEDSONTIME_NAME "allLedsOnTime"
#define HTML_LEDLUM_NAME "ledsGlobalLuminosity"
#define HTML_POWERLEDECO_NAME "powerLedEconomyMode"
#define HTML_SOFTAPPORT_NAME "softAP_port"
#define HTML_STATIONIP_NAME "staIP"
#define HTML_HOSTNAME_NAME "hostName"
#define HTML_STAGATEWAY_NAME "staGateway"
#define HTML_MAXRETRY_NAME "STAmaxWifiConnectionRetry"
#define HTML_FIRSTBOOT_NAME "firstBoot"
#define HTML_REDPLUGNICK_NAME "redPlug_nickName"
#define HTML_GREENPLUGNICK_NAME "greenPlug_nickName"
#define HTML_BLUEPLUGNICK_NAME "bluePlug_nickName"
#define HTML_YELLOWPLUGNICK_NAME "yellowPlug_nickName"
#define HTML_STARTINAP_NAME "startInAPMode"
#define HTML_DHCPMODE_NAME "dhcp_mode"

#define PALCEHOLDERTAG "pH_"

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

#include "csystem.h"

const String necessaryFileList[] ={
      "/index.html"
    , "/config4.json"
    , "/firstboot.html"
    // and why no credentials file ? because on firstboot we creat it
    // and after ???
    /** @todo [NECESSARY to check]possible bug if credentials disapear - in case of change cred we check
if file exist and tag an fsErr if not */
    // , "config.html"
    , "/js/main.js"
    , "/js/plug.js"
    , "/js/regExPatern.js"
    , "/js/table.js"
    // , "/js/jquery-3.3.1.min.js"
    // , "/js/bootstrap.min.js"
    , "/css/sidebar.css"
    , "/css/style.css"
    // , "/css/bootstrap.min.css"
    // , "/defConfig.json"
};

#endif
