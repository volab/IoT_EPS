/**
* @file configParam.h
* @author J.SORANZO
* @date 2018
* @copyright 2018 CC0
* @version 1.0
* @brief header file of the ConfigParam class
*/

//#pragma once
#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H
#include "debugSerialPort.h"


class ConfigParam{
    public:
        bool ready = false;
        void begin(){ ready = readFromJson(); } //pour le moment
        String getWifiMode(){ return _wifimode; }
		void setWifiMode( String mode ){ _wifimode = mode ; }
        String getHostName(){ return _host; }
		static void displayJson();
		void displayWifiMode();
        static void write2Json( String param, String value );
        static void chgSSID( String value );
    
    private:
        String _wifimode = "softAP" ; //default value
        String _host= "PowerStrip";
        bool readFromJson();
        
    
};

#endif
