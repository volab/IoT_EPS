
#include "IoT_EPS.h"
#include "CRtc.h"
//#include "cpowerplug.h"

#ifndef CWEBSERVEUR_H
#define CWEBSERVEUR_H



class CServerWeb{

private:
    /* data */
    CRtc *_pRtc = nullptr;
    ESP8266WebServer *server;
    ConfigParam *_pcParam = nullptr;
    int mainPowerSwitchState = 0;
    CPowerPlug *_pPlugs;
    bool *_pRestartTempoLed;
    bool handleFileRead(String path);
    String getContentType(String filename);
    void handleSoftAPIndex();

public:
    CServerWeb(/* args */);
    ~CServerWeb();
    void init( CRtc * rtc, ConfigParam *cparam, CPowerPlug *plugs
                , bool *restartTempoLed );
    void setMPSstVar( int mainPowerSwitchStateVal ){mainPowerSwitchState = mainPowerSwitchStateVal;}
    void displayTime();
    void serviceClient();
    void handlePlugOnOff();
    static String extractParamFromHtmlReq( String allRecParam, String param );
    //static and public for CpowerPlug usage

};

#endif