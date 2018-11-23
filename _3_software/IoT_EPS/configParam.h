

//#pragma once
#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H
#include "debugSerialPort.h"


class ConfigParam{
    public:
        bool ready = false;
        void begin(){ ready = readFromJson(); } //pour le moment
        String getWifiMode(){ return _wifimode; }
        String getYellowState(){ return _yellowPlugState; }
        String getHostName(){ return _host; }
    
    private:
        String _wifimode = "softAP" ; //default value
        String _yellowPlugState;
        String _redPlugState;
        String _greenPlugState;
        String _bluePlugState;
        String _host= "PowerStrip";
        bool readFromJson();
        // String d_prompt = "<VoLAB reading config param.>"; //stand for debug prompt
        
    
};

#endif
