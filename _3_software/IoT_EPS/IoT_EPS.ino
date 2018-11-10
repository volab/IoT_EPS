
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
    String d_prompt = "<VoLAB setup >";
    DateTime now;
    DEBUGPORT.begin(DEBUGSPEED);
    DEBUGPORT.println();
    DEBUGPORT.println( d_prompt + F("Sketch start..."));
    
    cParam.begin();
    wifiCred.begin();
    rtc.begin();
    Wire.beginTransmission(DS3231_ADDRESS);
    errRTCinit = Wire.endTransmission();
    
    // mcp.begin();
    CPowerPlug::init();
    plug0.begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, OFF );
    
    //mcp.pinMode( PLUG0, OUTPUT );
    // mcp.pinMode( PLUG1, OUTPUT );
    // mcp.pinMode( PLUG2, OUTPUT );

    if ( errRTCinit ) {
        DEBUGPORT.println(d_prompt + F("ERR : Couldn't find RTC"));
    } else {
        errRTCinit = false;
        now = rtc.now();
        String message = d_prompt + F("DS3231 Start date : ");
        // sprintf(buf, "<VoLAB> DS3231 Start date : %d/%d/%d %d:%d:%d", 
        message += (String)now.day()+"/"+(String)now.month()+"/";
        message += (String)now.year()+" ";
        message += (String)now.hour()+":"+ (String)now.minute()+":";
        message += (String)now.second();      
        DEBUGPORT.println( message);
    } 
    if (cParam.ready){
        DEBUGPORT.println( d_prompt + F("Wifi mode = ") + cParam.getWifiMode() );
    }
    

    // DEBUGPORT.print( " \n" + d_prompt + F("Mode autoconnect :"));
    // DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    //DEBUGPORT.println( d_prompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );
    WiFi.setAutoConnect(false);
    DEBUGPORT.print("\n" + d_prompt + F("Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( d_prompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );

    if ( wifiCred.ready ){
        if ( cParam.getWifiMode() == "client" ){
            WiFi.mode(WIFI_STA);
            WiFi.begin( wifiCred.getSsid(), wifiCred.getPass() );
            DEBUGPORT.println(  d_prompt + F("Try to join : ") + wifiCred.getSsid() );
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                DEBUGPORT.print(".");
            }
             DEBUGPORT.println();
        } else { //mode softAP
        // DEBUGPORT.printf("SSID : %s, pass : %s", wifi_ssid_s.c_str(), wifipass_s.c_str());
            DEBUGPORT.print("\n" + d_prompt + F("softAP : "));
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
            DEBUGPORT.println(WiFi.softAP(wifiCred.getSsid(),
                wifiCred.getPass() )?F("Ready"):F("Failed!"));
              
        }
        DEBUGPORT.println(  d_prompt + F("Adresse Wifi.localIP : ") + WiFi.localIP().toString() );
        // DEBUGPORT.println( WiFi.localIP() );
        DEBUGPORT.println(  d_prompt + F("Adresse configured IP : ") + apIP.toString() );          
    }
    
    
    MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
    
    if (!SPIFFS.begin()){
        DEBUGPORT.println(d_prompt + F("SPIFFS Mount failed"));
    } else {
        DEBUGPORT.println(d_prompt + F("SPIFFS Mount succesfull"));
    }
  // reading file
/////////////////////////////////////////////////////////////////////////////
//  Debut test lecture fichier index.html                                  //
/////////////////////////////////////////////////////////////////////////////
    if (SPIFFS.exists("/index.html")) {
        DEBUGPORT.println( d_prompt + F("index file found."));
    } else {
        DEBUGPORT.println( d_prompt + F("fichier index introuvable."));
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

