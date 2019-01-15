/**
* @file IoT_EPS.ino
@mainpage
* @author J.SORANZO & Pierre
* @date 20 Oct 2018
* @copyright 2018 CC0
* @version 1.0
* @brief EPS Electrical Power Strip software

@tableofcontents

@section dependencies Lib dependencies
- Utilisation de la bibliothèque ESP8266WiFi version 1.0
- Utilisation de la bibliothèque ESP8266WebServer version 1.0 
- Utilisation de la bibliothèque ArduinoJson version 5.13.2 
- Utilisation de la bibliothèque Wire version 1.0
- Utilisation de la bibliothèque RTClib version 1.2.0
- Utilisation de la bibliothèque ESP8266mDNS
- Utilisation de la bibliothèque Adafruit_MCP23017_Arduino_Library version 1.0.3
- Utilisation de la bibliothèque FastLED version 3.2.1
- Utilisation de la bibliothèque NTPClient version 3.1.0

@section wifi WIFIs connexions

If credentials are found in SPIFFS are found plugs try to connect about 20 times (time out = 10s).

If it can't reach WIFI network it switch to acces point mode.

In Access point mode default add is 192.168.95.42. Ssid and pass are those store in the SPIFFS credential.json

In station mode, when WIFI is not reachable, it switchs in softAP mode and WIFI LED fash shortly in 2s period.
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

CRtc rtc;

/** @todo get IP and server port from config3.json*/
ESP8266WebServer server ( 80 );
IPAddress apIP(192, 168, 95, 42);


CPowerPlug plugs[NBRPLUGS];

// bool errRTCinit = true;
bool errFS = true;

/** @todo see for add colorLEd array in the class CPowerPlug as a static member*/
CRGB colorLeds[NUM_LEDS]; /**< @brief  not very satisfy for this globale ! It should be in the 
CpowerPlug class*/


bool simpleManualMode = false;

Flasher wifiLed;

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
    
	SerialCommand::init();
	
    cParam.begin();
    wifiCred.begin();
	
	
    
    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                           //
    /////////////////////////////////////////////////////////////////////////////
    rtc.begin();
    // Wire.beginTransmission(DS3231_ADDRESS);
    // errRTCinit = Wire.endTransmission();
    if ( !rtc.initErr ){
        if (rtc.lostPower()){
            DSPL( dPrompt + "une remise a l'heure est necessaire");
            //errRTCinit = true;
            /** @todo enable or not ? errRTCinit due to lots power*/
        }
    }
    if ( rtc.initErr ) {
        DSPL(dPrompt + F("ERR : Couldn't find RTC"));
        /** @todo Stop EPS and warn with colors and others LED ,
        cause without right time EPS dosen't work. No manual mode shall work */
    } else {
        // errRTCinit = false;
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
    plugs[3].readFromJson();
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        colorLeds[i] = plugs[i].getColor();
        /** @todo creat a pointer in CPowerPlug to one position off colorLeds*/
    }
    FastLED.setBrightness(5); /**< @brief normaly in the json config file*/
    /** @todo Read the general brightness of color LED in JSON config file*/
    FastLED.show();
	
    simpleManualMode = plugs[0].bp.directRead();
	/////////////////////////////////////////////////////////////////////////////
    //  WIFI start                                                             //
    /////////////////////////////////////////////////////////////////////////////

	wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_FAST );
	
	if ( !simpleManualMode ){
		int tryCount = 0;
		if (cParam.ready){
			DSPL( dPrompt + F("Wifi mode = ") + cParam.getWifiMode() );
		}
		WiFi.setAutoConnect(false); //to allways control wifi connection
		DSP( dPrompt + F("Mode autoconnect : "));
		DSPL( WiFi.getAutoConnect()?"enabled":"disabled");
		DSPL( dPrompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );

		if ( wifiCred.ready ){ 
			if ( cParam.getWifiMode() == "client" ){ // Station WIFI mode
				WiFi.mode(WIFI_STA);
				WiFi.begin( wifiCred.getSsid(), wifiCred.getPass() );
				DSPL(  dPrompt + F("Try to join : ") + wifiCred.getSsid() );
				wifiLedFlash( wifiLed, WIFILED_FLASH_COUNT );
				// wifiLedFlash( WIFILED_FLASH_FAST, WIFILED_FLASH_COUNT );
				wifiLed.begin( WIFILED, WIFILED_FLASH_SLOW, WIFILED_FLASH_SLOW );
				while (WiFi.status() != WL_CONNECTED) {
					delay(500);
					// digitalWrite( WIFILED , !digitalRead( WIFILED ) );
					wifiLed.update();
					DSP(".");
					//a normal acces should came in 10 try
					tryCount++;
					if (tryCount == MAX_WIFI_CONNECT_RETRY ) break;
					
				}
				wifiLed.stop();
                pinMode( WIFILED, OUTPUT );
				digitalWrite( WIFILED, HIGH);
				DSPL( dPrompt + F("Number of Station wifi try : ") + (String)tryCount );
				if ( WiFi.status() == WL_CONNECTED){
					DSPL(  dPrompt + F("Adresse Wifi.localIP Station mode : ") \
						+ WiFi.localIP().toString() );  
				} else { WiFi.disconnect(); }
			}
			if ( cParam.getWifiMode() == "softAP" || tryCount == MAX_WIFI_CONNECT_RETRY ){
				//WIFI soft Access Point mode
				DSPL( dPrompt + F("Try softAccess") );
				wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_SLOW );
				wifiLedFlash( wifiLed , WIFILED_FLASH_COUNT );
				DSP("\n" + dPrompt + F("softAP : "));
				WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
				DSPL(WiFi.softAP(wifiCred.getSsid(),
					wifiCred.getPass() )?F("Ready"):F("Failed!"));
				DSPL(  dPrompt + F("Adresse configured IP : ") + apIP.toString() );
				cParam.setWifiMode( "softAP" ); // not in the config file just for temorary mode
				DSPL( dPrompt + F("SSID = ") + wifiCred.getSsid() );
				// digitalWrite( WIFILED, LOW);
				wifiLed.begin( WIFILED, WIFILED_SOFTAP_FLASH, WIFILED_SOFTAP_PERIOD );
				// to prepare for loop
			}
		}
		MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
		DSPL( dPrompt + F("Host name that not work with Android is : ") + cParam.getHostName() );
	
	} else {
		DSPL(  dPrompt + F("Enter in simple manual mode") );
		cParam.setWifiMode( "No wifi" );
		simpleManualModeChaser();
	}
    
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
	if ( !simpleManualMode ){
		server.on("/list", HTTP_GET, handleFileList);
		server.on("/PlugConfig", HTTP_GET, handlePlugConfig );
		server.on("/plugonoff", HTTP_POST, handlePlugOnOff );
		server.on("/edit", HTTP_GET, [](){
			if(!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
		});
		server.on("/help", HTTP_GET, [](){
			if(!handleFileRead("/help.htm")) server.send(404, "text/plain", "FileNotFound");
		});
        /** @todo test FSBBrowserNG from https://github.com/gmag11/FSBrowserNG */
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

		server.on( "/time", displayTime );

		server.on ( "/inline", []() {
			server.send ( 200, "text/plain", "this works as well" );
		} );
		// server.onNotFound ( handleNotFound );
		server.begin();
		Serial.println ( "HTTP server started" );
	
	}
	
	SerialCommand::displayCommandsList();
    

}

/////////////////////////////////////////////////////////////////////////////
//        LOOP                                                             //
/////////////////////////////////////////////////////////////////////////////
unsigned long prevMillis = millis();
void loop(){

    DEFDPROMPT("in the loop")
    if ( !simpleManualMode ) server.handleClient();

    SerialCommand::process();
	
	if ( cParam.getWifiMode() == "softAP" ) wifiLed.update();

    FastLED.show();
    for ( int i = 0; i < NBRPLUGS ; i++ ) plugs[i].bp.update();
    for ( int i = 0; i < NBRPLUGS ; i++ ){

        /** @todo replace usage of reading in json by _mode member of pplug class*/
        if ( plugs[i].bp.clic() ){
            plugs[i].handleBpClic();
        }
        // else if plugs[i].bp.longClic(){ plugs[i].return2ManuelMode() }
        /** @todo developp return2ManuelMode of the  CPowerPlug class*/
        if ( plugs[i].isItTimeToSwitch() ){
            DSPL( dPrompt + "It is time for : " + plugs[i].getPlugName() );
            plugs[i].switchAtTime();
        }
    }
    yield();
}


/////////////////////////////////////////////////////////////////////////////
//  Simple local functions                                                 //
/////////////////////////////////////////////////////////////////////////////

void wifiLedFlash( int speed, int count ){
    for ( int i = 0; i < count ; i++ ){
        digitalWrite( WIFILED , !digitalRead( WIFILED ) );
        delay( speed );        
    }
    digitalWrite( WIFILED, LOW);
}

//second implementation with Flasher
void wifiLedFlash( Flasher led, int count ){
	while ( led.getChangeStateCpt() < count ){
		led.update();
		yield();
	}
    led.stop();
}

void simpleManualModeChaser(){
	for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
	FastLED.show();
	delay(500);
	
	for (int i=0; i < 20; i++){
		for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
		FastLED.show();
		delay(200);	
		for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Red;
		FastLED.show();
		delay(200);				
	}
	
	//restaur Color Leds state
	for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = plugs[i].getColor();    
	FastLED.show();
}
