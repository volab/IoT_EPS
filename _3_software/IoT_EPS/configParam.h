/**
* @file configParam.h
* @author J.SORANZO
* @date 2018
* @copyright 2018 CC0
* @version 1.0
* @brief header file of the ConfigParam class
*/

#include "IoT_EPS.h"
//#pragma once
#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H


#include "debugSerialPort.h"
#include <IPAddress.h>
// #define CONFIGFILENAME "/config4.json"


class ConfigParam{
    public:

    enum firstBootVal { YES, NO, TRY };
    
        bool ready = false;
        void begin(); //pour le moment
        String getWifiMode(){ return _wifimode; }
		void setWifiMode( String mode ){ _wifimode = mode ; }
        String getHostName(){ return _host; }
		static void displayJson( String file = CONFIGFILENAME );
		void displayWifiMode();
        static void displayJsonGeneral();
        
        static void chgSSID( String value, String key = "ssid" );
        static void chgWifiPass( String value, String key = "pass" );
        IPAddress getIPAdd(){ return _addIP; }
        int getNumberOfPlugs(){ return _numberOfPlugs; }
        int getServerPort(){ return _serverPort; }
        long getAllLedsOnTime(){ return _allLedsOnTime; }
        int getLedsLuminosity(){return _ledsGlobalLuminosity; }
        /** @todo read _powerLedEconomyMode parameter in the config file...*/
        bool getPowLedEconomyMode(){ return _powerLedEconomyMode; } 
        firstBootVal getFirstBoot(){ return _firstBoot; }
        static void write2Json( String param, String value, String file = CONFIGFILENAME );
        // static void _write2CredJson( String param, String value );
        unsigned int getSTAMaxRetries(){ return _STAmaxWifiConnectionRetries; }
        
    
    private:
        String _wifimode = "softAP" ; //default value
        String _host= "PowerStrip";
        bool readFromJson();
        IPAddress _addIP;
        int _numberOfPlugs = 4;
        int _serverPort;
        long _allLedsOnTime;
        bool _powerLedEconomyMode = false;
        //in seconds (not unsigned cause -1 could serve to allways on in future)
        int _ledsGlobalLuminosity;
        firstBootVal _firstBoot;
        unsigned int _STAmaxWifiConnectionRetries = MAX_WIFI_CONNECT_RETRY ;
        

};

#endif
