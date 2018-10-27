
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

// String wifi_ssid_s;
// String wifipass_s;

ConfigParam cParam;
Credential wifiCred;

RTC_DS3231 rtc;

ESP8266WebServer server ( 80 );

IPAddress apIP(192, 168, 95, 42);

/*
 server.serveStatic("/img", SPIFFS, "/img");
server.serveStatic("/", SPIFFS, "/index.html");
https://github.com/esp8266/Arduino/issues/1942
*/
bool errRTCinit = true;
void setup(){
    String d_prompt = "<VoLAB setup >";
    DateTime now;
    DEBUGPORT.begin(9600);
    DEBUGPORT.println();
    DEBUGPORT.println( d_prompt + F("Sketch start..."));
    
    cParam.begin();
    wifiCred.begin();
    rtc.begin();
    Wire.beginTransmission(DS3231_ADDRESS);
    errRTCinit = Wire.endTransmission();
    // if (error) dsLed.error();
    // if (! rtc.begin()) {
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
        DEBUGPORT.println( "Wifi mode = "+ cParam.getWifiMode() );
    }
    

    DEBUGPORT.print( " \n" + d_prompt + F("Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( d_prompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );
    WiFi.setAutoConnect(false);
    DEBUGPORT.print("\n" + d_prompt + F("Mode autoconnect :"));
    DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
    DEBUGPORT.println( d_prompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );

    if ( wifiCred.ready ){
    // DEBUGPORT.printf("SSID : %s, pass : %s", wifi_ssid_s.c_str(), wifipass_s.c_str());
        DEBUGPORT.print("\n" + d_prompt + F("softAP :"));
        WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
        DEBUGPORT.println(WiFi.softAP(wifiCred.getSsid(),
            wifiCred.getPass() )?F("Ready"):F("Failed!"));        
    }
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
    server.serveStatic("/", SPIFFS, "/index.html");
    server.serveStatic("/index.html", SPIFFS, "/index.html");
    server.serveStatic("/help.html", SPIFFS, "/help.html");
    server.on( "/time", displayTime );
	// server.on ( "/", handleRoot );
	// server.on ( "/test.svg", drawGraph );
	server.on ( "/inline", []() {
		server.send ( 200, "text/plain", "this works as well" );
	} );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );
    
    // server.serveStatic("/", SPIFFS, "/index.html");
    // server.begin();
}


void loop(){
    // Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    server.handleClient();
    // delay(3000);

    yield();
}

