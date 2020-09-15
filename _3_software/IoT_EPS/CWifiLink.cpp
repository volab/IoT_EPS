/**
 @file CWifiLink.cpp
 @author J.SORANZO
 @date 05/09/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Implementation file of the class CWifiLink
*/ 


#include "CWifiLink.h"

// void CWifiLink::begin( ESP8266WiFiClass * pWiFi, ESP8266WiFiClass &wifiRef ){
void CWifiLink::begin( ESP8266WiFiClass &wifiRef ){
    // _pWiFi = pWiFi;
    _wifiRef = wifiRef;
    _wifiCred.begin( );
}