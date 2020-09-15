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
        void begin( ESP8266WiFiClass * pWiFi);


    private:
        Credential _wifiCred;
        ESP8266WiFiClass *_pWiFi;


};


#endif