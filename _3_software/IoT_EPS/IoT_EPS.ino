
/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @vesrion 1.0

* @brief EPS Electrical Power Strip software
*/

#include "IoT_EPS.h"

RTC_DS3231 rtc;

void setup(){
    DEBUGPORT.begin(9600);
    DEBUGPORT.println();
    DEBUGPORT.println( F("<VoLAB> Sketch start..."));

    DEBUGPORT.print(F("\n<VoLAB> Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );
    WiFi.setAutoConnect(false);
    DEBUGPORT.print(F("\n<VoLAB> Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );

    DEBUGPORT.print(F("\n<VoLAB> softAP :"));
    DEBUGPORT.print(WiFi.softAP("PowerStrip", "XXXXXXXXX")?F("Ready"):F("Failed!"));


}

void loop(){
    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    delay(3000);

    yield();
}
