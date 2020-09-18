/**
 @file CWifiLink.h
 @author J.SORANZO
 @date 05/09/2020
 @copyright 2020 CC0
 @version git versionning
 @brief header file of the class CWifiLink
*/

#ifndef CWIFILINK_H
#define CWIFILINK_H

#include "IoT_EPS.h"

class CWifiLink{
    public:
        CWifiLink();
        ~CWifiLink();
        void begin( ESP8266WiFiClass &wifiRef, const bool simpleManualMode );
        // void begin( ESP8266WiFiClass * pWiFi, ESP8266WiFiClass &wifiRef);


    private:
        Credential _wifiCred;
        // ESP8266WiFiClass *_pWiFi;
        ESP8266WiFiClass _wifiRef;
        


};


#endif