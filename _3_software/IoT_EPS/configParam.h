

//#pragma once
#ifndef CONFIGPARAM_H
#define CONFIGPARAM_H



class ConfigParam{
    public:
        bool ready = false;
        void begin(){ ready = readFromJson(); } //pour le moment
        String getWifiMode(){ return _wifimode; }
        String getYellowState(){ return _yellowPlugState; }
    
    private:
        String _wifimode = "softAP" ; //default value
        String _yellowPlugState;
        String _redPlugstate;
        String _greenPlugState;
        String _bluePlugState;
        bool readFromJson();
        String d_prompt = "<VoLAB reading config param.>"; //stand for debug prompt
    
};

#endif
