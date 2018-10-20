
/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @vesrion 1.0
* @brief EPS Electrical Power Strip software

@section dependencies Lib dependencies
Utilisation de la bibliothèque ESP8266WiFi version 1.0

Utilisation de la bibliothèque ArduinoJson version 5.13.2

Utilisation de la bibliothèque Wire version 1.0

Utilisation de la bibliothèque RTClib version 1.2.0
*/

#include "IoT_EPS.h"

String wifi_ssid_s;
String wifipass_s;

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

/*
Work on global variables
wifi_ssid_s
wifipass_s
*/
bool readWifiCredit(){
    DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounting FS..."));

    if (SPIFFS.begin()) {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounted file system"));
        if (SPIFFS.exists("/creditentials.json")) {
            //file exists, reading and loading
            DEBUGPORT.println(F("<VoLAB reading wifi credit.> reading config file"));
            File configFile = SPIFFS.open("/creditentials.json", "r");
            if (configFile) {
                DEBUGPORT.println( F("\topened config file") );
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    wifi_ssid_s = json["ssid"].as<String>();
                    wifipass_s = json["pass"].as<String>();
                } else {
                    DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to load json config"));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to open /config.json"));
            return false;
        }

    } else {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to mount FS"));
        return false;
    }
 }
