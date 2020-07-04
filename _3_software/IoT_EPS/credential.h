/**
* @file credential.h
* @author J.SORANZO & Pierre
* @date 24 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief header file of the Credential class

@details a class to read wifi credential from credentials.json

*/

#include "IoT_EPS.h"

#ifndef CREDENTIAL_H
#define CREDENTIAL_H

// #include <Arduino.h>
// #include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson


class Credential{
    public:
        Credential();
        bool ready = false;
        void begin(){ ready = readFromJson(); }
       
        String getSsidString(){ return _ssid;}
        String getPassString(){ return _pass;}
        const char* getSsid(){ return _ssid.c_str(); }
        const char* getPass(){ return _pass.c_str(); }
        String getSoftApSsidString(){ return _softApSsid;}
        String getSoftApPassString(){ return _softApPass;}
        const char* getSoftApSsid(){ return _softApSsid.c_str(); }
        const char* getSoftApPass(){ return _softApPass.c_str(); }        
        
        
    private:
        String _ssid;
        String _pass;
        String _softApSsid;
        String _softApPass;
        bool readFromJson();

};


#endif