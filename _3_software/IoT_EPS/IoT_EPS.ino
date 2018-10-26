
/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief EPS Electrical Power Strip software

@section dependencies Lib dependencies
Utilisation de la bibliothèque ESP8266WiFi version 1.0

Utilisation de la bibliothèque ArduinoJson version 5.13.2

Utilisation de la bibliothèque Wire version 1.0

Utilisation de la bibliothèque RTClib version 1.2.0
*/






#include "IoT_EPS.h"

// String wifi_ssid_s;
// String wifipass_s;

ConfigParam cParam;
Credential wifiCred;

RTC_DS3231 rtc;

void setup(){
    DEBUGPORT.begin(9600);
    DEBUGPORT.println();
    DEBUGPORT.println( F("<VoLAB> Sketch start..."));
    
    cParam.begin();
    wifiCred.begin();

    if (cParam.ready){
        DEBUGPORT.println( "Wifi mode = "+ cParam.getWifiMode() );
    }
    

    DEBUGPORT.print(F("\n<VoLAB> Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );
    WiFi.setAutoConnect(false);
    DEBUGPORT.print(F("\n<VoLAB> Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );

    if ( wifiCred.ready ){
    // DEBUGPORT.printf("SSID : %s, pass : %s", wifi_ssid_s.c_str(), wifipass_s.c_str());
        DEBUGPORT.print(F("\n<VoLAB> softAP :"));
        DEBUGPORT.println(WiFi.softAP(wifiCred.getSsid(),
            wifiCred.getPass() )?F("Ready"):F("Failed!"));        
    }
}


void loop(){
    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    delay(3000);

    yield();
}

