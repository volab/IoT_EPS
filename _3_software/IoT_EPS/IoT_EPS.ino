
/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief EPS Electrical Power Strip software

@section dependencies Lib dependencies
Utilisation de la bibliothèque ESP8266WiFi version 1.0

Utilisation de la bibliothèque ArduinoJson version 5.13.2

Utilisation de la bibliothèque Wire version 1.0

Utilisation de la bibliothèque RTClib version 1.2.0
*/

#include "IoT_EPS.h"


ConfigParam cParam;
Credential wifiCred;

RTC_DS3231 rtc;

ESP8266WebServer server ( 80 );

IPAddress apIP(192, 168, 95, 42);

// Adafruit_MCP23017 mcp;

// CPowerPlug plug0{ RED };
CPowerPlug plug0( ROUGE );

bool errRTCinit = true;
void setup(){
    #ifdef DEBUG
    String dPrompt = F("<VoLAB setup >");
    #else
    String dPrompt = "";    
    #endif
    DateTime now;
    DEBUGPORT.begin(DEBUGSPEED);
    DSPL();
    DSPL( dPrompt + F("Sketch start..."));
    
    cParam.begin();
    wifiCred.begin();
    rtc.begin();
    Wire.beginTransmission(DS3231_ADDRESS);
    errRTCinit = Wire.endTransmission();
    
    // mcp.begin();
    Cmcp::init();
    plug0.begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, OFF );
    
    //mcp.pinMode( PLUG0, OUTPUT );
    // mcp.pinMode( PLUG1, OUTPUT );
    // mcp.pinMode( PLUG2, OUTPUT );

    if ( errRTCinit ) {
        DSPL(dPrompt + F("ERR : Couldn't find RTC"));
    } else {
        errRTCinit = false;
        now = rtc.now();
        String message = dPrompt + F("DS3231 Start date : ");
        // sprintf(buf, "<VoLAB> DS3231 Start date : %d/%d/%d %d:%d:%d", 
        message += (String)now.day()+"/"+(String)now.month()+"/";
        message += (String)now.year()+" ";
        message += (String)now.hour()+":"+ (String)now.minute()+":";
        message += (String)now.second();      
        DSPL( message);
    } 
    if (cParam.ready){
        DSPL( dPrompt + F("Wifi mode = ") + cParam.getWifiMode() );
    }
    

    // DSP( " \n" + dPrompt + F("Mode autoconnect :"));
    // DSPL( WiFi.getAutoConnect()?"enabled":"disabled");
    //DSPL( dPrompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );
    WiFi.setAutoConnect(false);
    DSP("\n" + dPrompt + F("Mode autoconnect :"));
    DSPL( WiFi.getAutoConnect()?"enabled":"disabled");
    DSPL( dPrompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );

    if ( wifiCred.ready ){
        if ( cParam.getWifiMode() == "client" ){
            WiFi.mode(WIFI_STA);
            WiFi.begin( wifiCred.getSsid(), wifiCred.getPass() );
            DSPL(  dPrompt + F("Try to join : ") + wifiCred.getSsid() );
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                DSP(".");
            }
            DSPL();
            DSPL(  dPrompt + F("Adresse configured IP : ") + apIP.toString() );
            
        } else { //mode softAP
        // DSPf("SSID : %s, pass : %s", wifi_ssid_s.c_str(), wifipass_s.c_str());
            DSP("\n" + dPrompt + F("softAP : "));
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
            DSPL(WiFi.softAP(wifiCred.getSsid(),
                wifiCred.getPass() )?F("Ready"):F("Failed!"));
            DSPL(  dPrompt + F("Adresse Wifi.localIP : ") + WiFi.localIP().toString() );  
        }
    }
    
    
    MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
    
    if (!SPIFFS.begin()){
        DSPL(dPrompt + F("SPIFFS Mount failed"));
    } else {
        DSPL(dPrompt + F("SPIFFS Mount succesfull"));
    }
  // reading file
/////////////////////////////////////////////////////////////////////////////
//  Debut test lecture fichier index.html                                  //
/////////////////////////////////////////////////////////////////////////////
    if (SPIFFS.exists("/index.html")) {
        DSPL( dPrompt + F("html index file found."));
    } else {
        DSPL( dPrompt + F("fichier html index introuvable."));
    }
String str = "";
Dir dir = SPIFFS.openDir("/");
while (dir.next()) {
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
}
Serial.print(str);
/////////////////////////////////////////////////////////////////////////////
//  Fin                                                                       //
/////////////////////////////////////////////////////////////////////////////
    server.on("/list", HTTP_GET, handleFileList);
    server.on("/edit", HTTP_GET, [](){
        if(!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
    });
    server.on("/help", HTTP_GET, [](){
        if(!handleFileRead("/help.htm")) server.send(404, "text/plain", "FileNotFound");
    });
    server.on("/edit", HTTP_PUT, handleFileCreate);
    server.on("/edit", HTTP_DELETE, handleFileDelete);
    //first callback is called after the request has ended with all parsed arguments
    //second callback handles file uploads at that location
    server.on("/edit", HTTP_POST, [](){ server.send(200, "text/plain", ""); }, handleFileUpload);

    //called when the url is not defined here
    //use it to load content from SPIFFS
    server.onNotFound([](){
    if(!handleFileRead(server.uri()))
        server.send(404, "text/plain", "FileNotFound");
    });    

    // server.serveStatic("/", SPIFFS, "/index.html");
    // server.serveStatic("/index.html", SPIFFS, "/index.html");
    // server.serveStatic("/help.html", SPIFFS, "/help.html");
    server.on( "/time", displayTime );

	server.on ( "/inline", []() {
		server.send ( 200, "text/plain", "this works as well" );
	} );
	// server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );

}

unsigned long prevMillis = millis();
void loop(){
    static bool statePlug0 = false;
    // Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    server.handleClient();
    // delay(3000);
    if ( millis() - prevMillis >= FLASHERTIME){
        prevMillis = millis();
        statePlug0 = !statePlug0 ;
        // mcp.digitalWrite( PLUG0, statePlug0 );
    }

    yield();
}

