
#include "IoT_EPS.h"
#include "CRtc.h"

#ifndef CWEBSERVEUR_H
#define CWEBSERVEUR_H



class CServerWeb{

private:
    /* data */
    CRtc *_pRtc = nullptr;
    ESP8266WebServer *_pServer;
    ConfigParam *_pcParam = nullptr;
public:
    CServerWeb(/* args */);
    ~CServerWeb();
    void init( CRtc * rtc, ConfigParam *cparam );
    void displayTime();

};

#endif