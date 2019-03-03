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
#include <IPAddress.h>


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
        IPAddress getIPAdd(){ return _addIP; }
        int getNumberOfPlugs(){ return _numberOfPlugs; }
        int getServerPort(){ return _serverPort; }
        long getAllLedsOnTime(){ return _allLedsOnTime; }
        int getLedsLuminosity(){return _ledsGlobalLuminosity; }
        
    
    private:
        String _wifimode = "softAP" ; //default value
        String _host= "PowerStrip";
        bool readFromJson();
        IPAddress _addIP;
        int _numberOfPlugs;
        int _serverPort;
        long _allLedsOnTime;
        //in seconds (not unsigned cause -1 could serve to allways on in future)
        int _ledsGlobalLuminosity;

};

#endif
