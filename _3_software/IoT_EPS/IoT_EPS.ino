/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief EPS Electrical Power Strip software

@section dependencies Lib dependencies
- Utilisation de la bibliothèque ESP8266WiFi version 1.0
- Utilisation de la bibliothèque ESP8266WebServer version 1.0 
- Utilisation de la bibliothèque ArduinoJson version 5.13.2 
- Utilisation de la bibliothèque Wire version 1.0
- Utilisation de la bibliothèque RTClib version 1.2.0
- Utilisation de la bibliothèque ESP8266mDNS
- Utilisation de la bibliothèque Adafruit_MCP23017_Arduino_Library version 1.0.3
- Utilisation de la bibliothèque FastLED version 3.2.1
*/


#include "IoT_EPS.h"

/** 
@fn void wifiLedFlash( int speed )
@brief a simple function to flash wifi led n times before connection
@param flashing speed
@return nothing

function is defined at the end of this file.

There is 2 flashing speeds one for AP mode and one for Station mode
*/
void wifiLedFlash( int speed, int count );

ConfigParam cParam; /**< @brief to hold the configuration parameters*/
Credential wifiCred;

RTC_DS3231 rtc;

ESP8266WebServer server ( 80 );

IPAddress apIP(192, 168, 95, 42);

// Adafruit_MCP23017 mcp;

// CPowerPlug plug0{ RED };
// CPowerPlug plug0( ROUGE );
CPowerPlug plugs[NBRPLUGS];

bool errRTCinit = true;
bool errFS = true;

CRGB colorLeds[NUM_LEDS]; /**< @brief  not very satisfy for this globale ! It should be in the 
CpowerPlug class*/
/** @todo see for add colorLEd array in the class CPowerPlug as a static member*/


void setup(){

    DEFDPROMPT("setUp") // define dPrompt String
    DateTime now;
    DEBUGPORT.begin(DEBUGSPEED);
    DSPL();
    DSPL( dPrompt + F("Sketch start..."));

    DSPL( dPrompt + " Build : " + __DATE__ + " @ " + __TIME__);
    errFS = !SPIFFS.begin(); // to check if it's possible to begin twice the SPIFFS
    //next time is in cParam.begin
    // The response was already in the code : about line
    if (errFS) DSPL( dPrompt + F("error in Oping Fil System") );
    else DSPL( dPrompt + F("File system corectly Open @ setup level") );
    
    cParam.begin();
    wifiCred.begin();
    
    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                           //
    /////////////////////////////////////////////////////////////////////////////
    rtc.begin();
    Wire.beginTransmission(DS3231_ADDRESS);
    errRTCinit = Wire.endTransmission();
    if ( !errRTCinit ){
        if (rtc.lostPower()){
            DSPL( dPrompt + "une remise à l'heure est nécessaire");
            //errRTCinit = true;
            /** @todo enable or not ? errRTCinit due to lots power*/
        }
    }
    if ( errRTCinit ) {
        DSPL(dPrompt + F("ERR : Couldn't find RTC"));
    } else {
        errRTCinit = false;
        /** @todo check time validity */
        now = rtc.now();
        String message = dPrompt + F("DS3231 Start date : ");
        // sprintf(buf, "<VoLAB> DS3231 Start date : %d/%d/%d %d:%d:%d", 
        message += (String)now.day()+"/"+(String)now.month()+"/";
        message += (String)now.year()+" ";
        message += (String)now.hour()+":"+ (String)now.minute()+":";
        message += (String)now.second();      
        DSPL( message);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //     Plugs config                                                        //
    /////////////////////////////////////////////////////////////////////////////
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(colorLeds, NUM_LEDS);
    
    Cmcp::init();
    plugs[0].begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, BP0, CPowerPlug::modeId("MANUEL") );
    plugs[0].setColor( CRGB::Red );
    plugs[0].setPlugName( HTML_JSON_REDPLUGNAME );
    plugs[0].readFromJson();
    /** @todo improve error check from CPowerPlug::readFromJson*/
    /** @todo add pin, pinLed and color to json file*/
    /** @todo + le nombre de plug pour rendre cette séquense dynamic*/
    
    plugs[1].begin( PLUG1PIN, PLUG1_ONOFFLEDPIN, BP1, CPowerPlug::modeId("MANUEL") );
    plugs[1].setColor( CRGB::Green );
    plugs[1].setPlugName( HTML_JSON_GREENPLUGNAME );
    plugs[1].readFromJson();
    plugs[2].begin( PLUG2PIN, PLUG2_ONOFFLEDPIN, BP2, CPowerPlug::modeId("MANUEL") );
    plugs[2].setColor( CRGB::Blue );
    plugs[2].setPlugName( HTML_JSON_BLUEPLUGNAME );
    plugs[2].readFromJson();
    // plugs[2].setColor( CRGB::Purple );
    plugs[3].begin( PLUG3PIN, PLUG3_ONOFFLEDPIN, BP3, CPowerPlug::modeId("MANUEL") );
    plugs[3].setColor( CRGB::Yellow );
    plugs[3].setPlugName( HTML_JSON_YELLOWPLUGNAME );
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        colorLeds[i] = plugs[i].getColor();
        /** @todo creat a pointer in CPowerPlug to one position off colorLeds*/
    }
    FastLED.setBrightness(5); /**< @brief normaly in the json config file*/
    /** @todo Read the general brightness of color LED in JSON config file*/
    FastLED.show();
    
    /////////////////////////////////////////////////////////////////////////////
    //  WIFI start                                                             //
    /////////////////////////////////////////////////////////////////////////////
    digitalWrite( WIFILED, LOW );
    pinMode( WIFILED, OUTPUT );
    if (cParam.ready){
        DSPL( dPrompt + F("Wifi mode = ") + cParam.getWifiMode() );
    }
    WiFi.setAutoConnect(false);
    DSP( dPrompt + F("Mode autoconnect : "));
    DSPL( WiFi.getAutoConnect()?"enabled":"disabled");
    DSPL( dPrompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );

    if ( wifiCred.ready ){ // Station wIFI mode
        if ( cParam.getWifiMode() == "client" ){
            WiFi.mode(WIFI_STA);
            WiFi.begin( wifiCred.getSsid(), wifiCred.getPass() );
            DSPL(  dPrompt + F("Try to join : ") + wifiCred.getSsid() );
            wifiLedFlash( WIFILED_FLASH_FAST, WIFILED_FLASH_COUNT );
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                digitalWrite( WIFILED , !digitalRead( WIFILED ) );
                DSP(".");
            }
            digitalWrite( WIFILED, HIGH);
            DSPL();
            DSPL(  dPrompt + F("Adresse Wifi.localIP : ") + WiFi.localIP().toString() );  
        } else { //WIFI soft Access Point mode
            wifiLedFlash( WIFILED_FLASH_SLOW, WIFILED_FLASH_COUNT/2 );
            DSP("\n" + dPrompt + F("softAP : "));
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
            DSPL(WiFi.softAP(wifiCred.getSsid(),
                wifiCred.getPass() )?F("Ready"):F("Failed!"));
            DSPL(  dPrompt + F("Adresse configured IP : ") + apIP.toString() ); 
            digitalWrite( WIFILED, HIGH);
        }
    }
    MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
    
   /////////////////////////////////////////////////////////////////////////////
    //  Start of the check index.html file presence  (check file system)       //
    /////////////////////////////////////////////////////////////////////////////
    if (!SPIFFS.begin()){
        DSPL(dPrompt + F("SPIFFS Mount failed"));
    } else {
        DSPL(dPrompt + F("SPIFFS Mount succesfull"));
    }
/** @todo cleanup the .ino code to remove all unnecessary code like displaying SPIFFS health*/
    if (SPIFFS.exists("/index.html")) {
        DSPL( dPrompt + F("html index file found."));
    } else {
        DSPL( dPrompt + F("html index file not found."));
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
    FSInfo filseSystemInfo;/**< @brief file system information to display it*/
    SPIFFS.info( filseSystemInfo ); 
    
    DSPL( dPrompt + F("SPIFFS total bytes : ") + (String)filseSystemInfo.totalBytes );
    DSPL( dPrompt + F("SPIFFS used bytes : ") + (String)filseSystemInfo.usedBytes );
    DSPL( dPrompt + F("SPIFFS max open files : ") + (String)filseSystemInfo.maxOpenFiles );
    DSPL( dPrompt + F("SPIFFS max path lenght : ") + (String)filseSystemInfo.maxPathLength );
    
    /////////////////////////////////////////////////////////////////////////////
    //  Server configurations                                                  //
    /////////////////////////////////////////////////////////////////////////////
    server.on("/list", HTTP_GET, handleFileList);
    server.on("/PlugConfig", HTTP_GET, handlePlugConfig );
    server.on("/plugonoff", HTTP_POST, handlePlugOnOff );
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
    FastLED.show();
    for ( int i = 0; i < NBRPLUGS ; i++ ) plugs[i].bp.update();
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        String sMode = plugs[i].readFromJson( JSON_PARAMNAME_MODE );
        if ( plugs[i].bp.clic() ){
            if (sMode == MANUAL_MODE){
                plugs[i].toggle();
                plugs[i].bp.acquit();
            }
            
        }
    }
    yield();
}

void wifiLedFlash( int speed, int count ){
    for ( int i = 0; i < count ; i++ ){
        digitalWrite( WIFILED , !digitalRead( WIFILED ) );
        delay( speed );        
    }
    digitalWrite( WIFILED, LOW);
}

