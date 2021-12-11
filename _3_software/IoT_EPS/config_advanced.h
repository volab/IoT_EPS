/**
* @file config.h
* @author J.SORANZO
* @date 08/12/2021
* @copyright 2021 CC0
* @brief all application parameters
*/

#ifndef _CONFIG_ADVANCED_H
#define _CONFIG_ADVANCED_H

#include <WString.h>

#define CONFIGFILENAME "/config4.json"
#define DEFCONFIGFILENAME "/defConfig.json"
#define CREDENTIALFILENAME "/credentials.json"
#define CONFIGFILENAME_COPY1 "/config4copie1.json"
#define CONFIGFILENAME_COPY2 "/config4copie2.json"

#define HTML_ALLARGS_SEPARATOR "|"
#define SECPERHOURS (int)3600

#define NOT_FOUND "nf" //return code for extractParam()

#define FLASHERTIME 500 //ms

#define PLUG0PIN 0 // MPC23017 numbering pin21 PORTA.0
#define PLUG1PIN 1
#define PLUG2PIN 2
#define PLUG3PIN 3
#define PLUG0_ONOFFLEDPIN 4
#define PLUG1_ONOFFLEDPIN 5
#define PLUG2_ONOFFLEDPIN 6
#define PLUG3_ONOFFLEDPIN 7

#define DATA_PIN D7 /**< for fastLED class strip data pin*/
#define CLOCK_PIN D8 /**< for fastLED class strip data pin*/

// #define MAINSWITCHPIN 8 //nanoI2CIOExpander pin D10
#define MAINSWITCHPIN D0 //Direct on ESP pin
#define SPECIALBP 10 //to ask plug state
#define MAINPOWLED 9 //nanoI2CIOExpander pin D11

#define BP0 D6 
#define BP1 D5
#define BP2 D4
#define BP3 D3

#define WIFILED 8 //nanoI2CIOExpander pin D10
#define WIFILED_FLASH_FAST 100
#define WIFILED_FLASH_SLOW 500
#define WIFILED_FLASH_COUNT 20
#define WIFILED_SOFTAP_FLASH 50
#define WIFILED_SOFTAP_PERIOD 2000

#define OLED_XPOS_STARTLIGN 6
#define OLED_YPOS_FOR_DATE 11
#define OLED_YPOS_FOR_STATE 22
#define OLED_YPOS_FOR_LAN_IPADD 41
#define OLED_YPOS_FOR_AP_IPADD 50

#define NBR_OF_SYSTEM_ERROR 11

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

#define NECESSARY_FILE_NBR 11

const String necessaryFileList[ NECESSARY_FILE_NBR ] ={
      "/index.html"
    , "/config4.json"
    , "/config4copie1.json"
    , "/config4copie2.json"
    /** @todo [NECESSARY] only one of the 3 json file is necessary to run !!!*/
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
    //config_tag.htm ?
};


#endif