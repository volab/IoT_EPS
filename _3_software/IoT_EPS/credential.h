/**
* @file credential.h
* @author J.SORANZO & Pierre
* @date 24 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief a class to read wifi credential from credentials.json

*/

#ifndef CREDENTIAL_H
#define CREDENTIAL_H

// #include <Arduino.h>
// #include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include "IoT_EPS.h"

class Credential{
    public:
        Credential(){};
        String getSsidString(){ return _ssid;};
        String getPassString(){ return _pass;};
        const char* getSsid(){ return _ssid.c_str(); };
        const char* getPass(){ return _pass.c_str(); };
        bool readFromJson();
    private:
        String _ssid;
        String _pass;
};


#endif