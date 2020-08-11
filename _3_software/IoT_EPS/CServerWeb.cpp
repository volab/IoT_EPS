#include "IoT_EPS.h"


//A global variable need by ESP8266WebServer
extern ESP8266WebServer *server; //a pointeur that allow change the port dynamicly

CServerWeb::CServerWeb(/* args */)
{
}

CServerWeb::~CServerWeb()
{
}

void CServerWeb::init( CRtc * prtc, ConfigParam *pcParam ){
    //big warning if _rtc is initialised with a local variable !!!!
    _pRtc = prtc;
    _pcParam = pcParam;
    server = new ESP8266WebServer( 80 );
    // server = new ESP8266WebServer( pcParam->getServerPort() );
    // _pServer->on( "/time", std::bind(&CServerWeb::displayTime, this) );
    server->on( "/time", std::bind(&CServerWeb::displayTime, this) );
    server->begin();
}

void CServerWeb::serviceClient(){
    DEFDPROMPT("ServiceWeb");
    // DSPL( dPrompt );
    server->handleClient();
}


// can't have parameters like rtc caus it is used as a callback function in 
// server->on
void CServerWeb::displayTime(){
    String page;
    DateTime now;
    // now = rtc.now();
    if ( _pRtc == NULL )return;

    now = _pRtc->now();
    page = "<html><head>";
    page += "<meta http-equiv='refresh' content='5'/>";
    page += "<title>IoT EPS display Time</title>";
    page += "<style>";
    page += "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }";
    page += "</style></head><body><h1>IoT EPS time!</h1>";
    page += "<a href=\"index.html\">Accueil</a><p>";
    page += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    page += (String)now.hour()+":"+(String)now.minute()+":";
    page += (String)now.second();
    page += "</p></body></html>";

    server->send ( 200, "text/html", page );

    
}
