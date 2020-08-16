/**
 @file CServerWeb.h
 @author J.SORANZO / VoLAB
 @date 15/08/2020
 @copyright 2020 CC0
 @version git versionning
 @brief heardr file of the class CServerWeb web of the project IoT_EPS
*/
#include "IoT_EPS.h"
#include "CRtc.h"
//#include "cpowerplug.h"

#ifndef CWEBSERVEUR_H
#define CWEBSERVEUR_H


/**
 * @brief cserverWeb class
 * 
 * 
 */
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
    void notFoundHandler();
    void handleFileList();
    void handleHelp();
    void handleEdit();

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
    //static and public for CPowerPlug usage

};

#endif