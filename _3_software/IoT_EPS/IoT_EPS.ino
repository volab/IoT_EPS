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
 - Utilisation de la bibliothèque ESP8266mDNS prise dans le dossier \2.4.1\\libraries\\ESP8266mDNS (legacy)
 - Utilisation de la bibliothèque FastLED version 3.2.1
 - Utilisation de la bibliothèque nanoI2CIOExpLib version 3.1
 - Utilisation de la bibliothèque NTPClient version 3.1.0

@section wifi WIFIs connexions

If credentials are found in SPIFFS are found plugs try to connect about 20 times (time out = 10s).

If it can't reach WIFI network it switch to acces point mode.

In Access point mode default add is 192.168.95.42. Ssid and pass are those store in the SPIFFS credential.json

In station mode, when WIFI is not reachable, it switchs in softAP mode and WIFI LED fash shortly in 2s period.


 @bug Serial command < d > delete file with space in their name !
*/

/**
 @page pageTodo Macro roadmap
 @tableofcontents
  doxygen todo list is not enought ! It is a good practice to highlight on certain ligne of code.
  Here I want to trace major features implementations.
  
 @li test restore defConfig.json when firstBoot 
 @li implement STA_AP mode in a new git branch
 @li see hardware.rst file
 
 @li power plugs current measurements
 @li manage summer and winter hour change
 @li if i say to you utf-8 ?!

 @li document FATAL errors color (see xlsx dedicate file)
 @li regarder pour recharger la page index lors d'un changement d'état par BP(pas forcément an mode AP)
 impossible this is the navigator to ask for a page and html refresh param is not a good idea !
 @li code, bugs and todo review : remove all unused commented code (cleanup)
*/


#include "IoT_EPS.h"
#include "ESP8266FtpServer.h"
FtpServer ftpSrv;

#include <ESP8266HTTPClient.h>


/** 
@fn void wifiLedFlash( int speed )
@brief a simple function to flash wifi led n times before connection
@param flashing speed
@return nothing

function is defined at the end of this file.

There is 2 flashing speeds one for AP mode and one for Station mode
*/
void wifiLedFlash( int speed, int count ); //defined at eh end of the rpesent file

ConfigParam cParam; /**< @brief to hold the configuration parameters*/
Credential wifiCred;

CRtc rtc;

ESP8266WebServer *server;

CPowerPlug *plugs;

// bool errFS = true;

CRGB colorLeds[NUM_LEDS]; /**< @brief  not very satisfy for this globale ! It should be in the 
CpowerPlug class*/


bool simpleManualMode = false;

CFlasherNanoExp wifiLed;
/** DONE 13/07/2019 [NECESSARY] check if it is possible to remove Flasher class (CNanoI2CIOExp used)
if yes remove Flasher.cpp and .h from source files */

// CSwitchNano mainPowerSiwtch;
int mainPowerSwitchState;
int mainPowerPrevState = 0;
CSwitchNano specialBp;

CNanoI2CIOExpander nanoioExp; //just for main pow led

// CFlasherNanoExp extraLed;

CTempo allLeds;
bool restartTempoLed = false;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTPSERVER);



/** @todo
 - [OPTION 1] see for add colorLEd array in the class CPowerPlug as a static member
 - [NECESSARY for 1 and 2 plug strip] convert colorLeds array in dynamic version as for plugs array */

void setup(){
    DateTime NTPTime;
    int timeZone = OFFSET_HEURE; 
    
    delay(1000);//a try to correct the powerup pb
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite( LED_BUILTIN, LOW ); //warning D4 BP blueu plug
    delay(1000);
    digitalWrite( LED_BUILTIN, HIGH ); //warning D4 BP blueu plug
    pinMode(LED_BUILTIN, INPUT);
    
    DEFDPROMPT("setUp") // define dPrompt String
    DateTime now;
    DEBUGPORT.begin(DEBUGSPEED);
    // Serial.setDebugOutput(true); //Serial debug of Wifi lib
    DSPL();
    DSPL( dPrompt + F("Sketch start..."));
    pinMode( BP1, INPUT_PULLUP );
    //pinMode( BP3, INPUT_PULLUP );
    if ( !(digitalRead(BP1) ) ){
        DSPL( dPrompt + F("Special action take place..." ) );
        // place special actions here
        // example sysStatus._forceSystemStartOnFatalError = true;
        cParam.creatDefaultJson();
    }
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(colorLeds, NUM_LEDS);
    FastLED.setBrightness( DEFAULT_LED_LUMINOSITY ); //default value for error display
    /////////////////////////////////////////////////////////////////////////////
    //     file system check                                                   //
    /////////////////////////////////////////////////////////////////////////////
    DSPL( dPrompt + " Build : " + __DATE__ + " @ " + __TIME__);
    
    sysStatus.fsErr.err( !SPIFFS.begin() ); 

    DSPL( dPrompt + F("File system corectly Open @ setup level") );
    /////////////////////////////////////////////////////////////////////////////
    //  Start of the check necessary files  presence                           //
    /////////////////////////////////////////////////////////////////////////////
    DSPL(dPrompt + F("File check !") );
    bool fileExist = true;
    for ( String s : necessaryFileList ){
        bool b = SPIFFS.exists(s);
        fileExist &= b;
        DSPL( dPrompt + F("file : ") + s + F(" is ") + (b?F("present"):F("not found")) );
    }
    DSPL( dPrompt + F("Result all files are present : ") + (fileExist?"OK":"ERROR") );
    sysStatus.filesErr.err( !fileExist );

    // if (SPIFFS.exists("/index.html")) {
        // DSPL( dPrompt + F("html index file found."));
    // } else {
        // DSPL( dPrompt + F("html index file not found."));
    // }
    // String str = "";
    // Dir dir = SPIFFS.openDir("/");
    // while (dir.next()) {
        // str += dir.fileName();
        // str += " / ";
        // str += dir.fileSize();
        // str += "\r\n";
    // }
    // Serial.print(str);
    // FSInfo filseSystemInfo;/**< @brief file system information to display it*/
    // SPIFFS.info( filseSystemInfo ); 
    
    // DSPL( dPrompt + F("SPIFFS total bytes : ") + (String)filseSystemInfo.totalBytes );
    // DSPL( dPrompt + F("SPIFFS used bytes : ") + (String)filseSystemInfo.usedBytes );
    // DSPL( dPrompt + F("SPIFFS max open files : ") + (String)filseSystemInfo.maxOpenFiles );
    // DSPL( dPrompt + F("SPIFFS max path lenght : ") + (String)filseSystemInfo.maxPathLength );
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    ftpSrv.begin("esp8266","esp8266");
    
	SerialCommand::init();
    /////////////////////////////////////////////////////////////////////////////
    //     Config param check                                                  //
    /////////////////////////////////////////////////////////////////////////////
    cParam.begin();
    sysStatus.confFileErr.err( !cParam.ready );
    DSPL( dPrompt + F("json mac add : ") + cParam.getMacAdd() );
    DSPL( dPrompt + F("Board Sation MAC add = ") + WiFi.macAddress() );
    if ( cParam.getMacAdd() == WiFi.macAddress() ) DSPL( dPrompt + "equal add");
    else {
        DSPL( dPrompt + "diff add, write to json");
        cParam.write2Json( "macAdd", WiFi.macAddress() );
    }
    DSPL( dPrompt + F("json Soft AP mac add : ") + cParam.getSoftAPMacAdd() );
    DSPL( dPrompt + F("Board Soft AP MAC add = ") + WiFi.softAPmacAddress() );
    if ( cParam.getSoftAPMacAdd() == WiFi.softAPmacAddress() ) DSPL( dPrompt + "equal add");
    else {
        DSPL( dPrompt + "diff add, write to json");
        cParam.write2Json( "softAP_macAdd", WiFi.softAPmacAddress() );
    }
    /////////////////////////////////////////////////////////////////////////////
    //     I2C bus check                                                       //
    ///////////////////////////////////////////////////////////////////////////// 
    CNano::init();

    int cpt = 1;
    do{
        if ( !nanoioExp.test() ){
            DSPL( dPrompt + "i2cRecov" + " number " + cpt);
            SerialCommand::i2c_recovery();
        } else cpt = 9;
        
        cpt++;
    } while (cpt < I2C_RETRIES );
    if (cpt != 10) sysStatus.nanoErr.err( true );
    DSPL(dPrompt + F("Nano test ok"));
    /////////////////////////////////////////////////////////////////////////////
    // Watchdog check                                                          //
    ///////////////////////////////////////////////////////////////////////////// 
    watchdog.begin();
    DSP( dPrompt + F("watchdog test ") );
    sysStatus.watchdogErr.err( !watchdog.test() ); 
    DSPL( "OK");
    watchdog.setTimeout( cParam.getSTAMaxRetries() );
    watchdog.setRefreshPeriod( cParam.getSTAMaxRetries()/3 );  
    DSPL( dPrompt + F("watchdog set to ") + String( cParam.getSTAMaxRetries() ) + F("s.") );
    
    
    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                    //
    /////////////////////////////////////////////////////////////////////////////
    rtc.begin();
    sysStatus.rtcErr.err( rtc.initErr );
    if (rtc.lostPower()){
        DSPL( dPrompt + "une remise a l'heure est necessaire");
    }
    now = rtc.now();
    String message = dPrompt + F("DS3231 Start date : ");
    message += (String)now.day()+"/"+(String)now.month()+"/";
    message += (String)now.year()+" ";
    message += (String)now.hour()+":"+ (String)now.minute()+":";
    message += (String)now.second();      
    DSPL( message);

    /////////////////////////////////////////////////////////////////////////////
    //     Main power first check                                              //
    /////////////////////////////////////////////////////////////////////////////    
    pinMode( MAINSWITCHPIN, INPUT_PULLUP);
    nanoioExp.digitalWrite( MAINPOWLED, 0);
    nanoioExp.pinMode( MAINPOWLED, OUTPUT ); 
    mainPowerSwitchState = !digitalRead( MAINSWITCHPIN ); //open circuit = plug OFF    
    
    nanoioExp.digitalWrite( MAINPOWLED, mainPowerSwitchState );
    DSPL( dPrompt + "Main power state : " +  ( mainPowerSwitchState?"ON":"OFF") );
    specialBp.begin( SPECIALBP, 20, INPUT_PULLUP );

  
    /////////////////////////////////////////////////////////////////////////////
    //     Plugs config                                                        //
    /////////////////////////////////////////////////////////////////////////////
    delete [] plugs;
    DSPL( dPrompt + F("number of plugs : ") + cParam.getNumberOfPlugs() );
    plugs = new CPowerPlug[ cParam.getNumberOfPlugs() ];
    //if above dosen't work see @
    //https://arduino.stackexchange.com/questions/3774/how-can-i-declare-an-array-of-variable-size-globally
    ////First you create a pointer for the memory space to be separated for the set you're creating
    // int* myArray;
    // int arrSize; //Then you define the variable that will determine the amount 
    // of elements the array is going to have, you can give it a value whenever you want as long 
    // as this int is defined before the values in myArray are set 
    // myArray=(int*)calloc(arrSize,sizeof(int)) 
    //Here, you establish that the instance myArray (whose memory space has already been separated 
    // through the creation of the pointer) will be separated into arrSize amount of elements of type 
    // int with a maximum memory value (in bytes) equal to the maximum available 
    // for the int type variables
    


    /* done test if CNano::initOk = true - if not don't start anything - this is fatal error*/
    plugs[0].begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, BP0, CPowerPlug::modeId("MANUEL") );
    plugs[0].setColor( CRGB::Red );
    plugs[0].setPlugName( HTML_JSON_REDPLUGNAME );
    if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[0].readFromJson( true ) );
    else  plugs[0].handleBpLongClic(); //change due to clone mode bug
    /** todo : no ! It is not a user config  [OPTION] add pin, pinLed and color to json file*/
    /** todo : no it should stay  as a #define 
    [NECESSARY for 2 and 1 plugs strip] + the number of plug to make this sequence dynamic*/
    
    plugs[1].begin( PLUG1PIN, PLUG1_ONOFFLEDPIN, BP1, CPowerPlug::modeId("MANUEL") );
    plugs[1].setColor( CRGB::Green );
    plugs[1].setPlugName( HTML_JSON_GREENPLUGNAME );
    if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[1].readFromJson( true ) );
    else  plugs[1].handleBpLongClic();
    plugs[2].begin( PLUG2PIN, PLUG2_ONOFFLEDPIN, BP2, CPowerPlug::modeId("MANUEL") );
    plugs[2].setColor( CRGB::Blue );
    plugs[2].setPlugName( HTML_JSON_BLUEPLUGNAME );
    if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[2].readFromJson( true ) );
    else  plugs[2].handleBpLongClic();
    // plugs[2].setColor( CRGB::Purple );
    plugs[3].begin( PLUG3PIN, PLUG3_ONOFFLEDPIN, BP3, CPowerPlug::modeId("MANUEL") );
    plugs[3].setColor( CRGB::Yellow );
    plugs[3].setPlugName( HTML_JSON_YELLOWPLUGNAME );
    if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[3].readFromJson( true ) );
    else  plugs[3].handleBpLongClic();
      
	
    /* done : document simpleManualMode with no wifi at all */
    simpleManualMode = plugs[0].bp.directRead();

    /////////////////////////////////////////////////////////////////////////////
    //     Main power wait ON (the purpose is to maintain Wifi off)            //
    ///////////////////////////////////////////////////////////////////////////// 
    if ( !mainPowerSwitchState ){
        DSPL( dPrompt + "Wait main power switch ON");
        for ( int i = 0; i < 4 ; i++ ) colorLeds[i] = CRGB::Black;
        FastLED.show();
        do {
            mainPowerSwitchState = !digitalRead( MAINSWITCHPIN ); //open circuit = plug OFF
            yield();
            if ( watchdog.isItTimeTo() ) watchdog.refresh();
        } while( !mainPowerSwitchState );        
    }
    DSPL( dPrompt + "Main power ON"); 
    mainPowerPrevState = mainPowerSwitchState; // for the loop
    nanoioExp.digitalWrite( MAINPOWLED, 1);
// with this way of doing it, we loose LED and other stuffs managment    
    // replace by WIFI_OFF no ?
    /** @todo [OPTION] try  WIFI_OFF when power is off */
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        colorLeds[i] = plugs[i].getColor();
        /** @todo [OPTION]creat a pointer in CPowerPlug to one position off colorLeds*/
        plugs[i].setMainPow( mainPowerSwitchState );
    }
    FastLED.setBrightness( cParam.getLedsLuminosity() );
    FastLED.show();
        
	/////////////////////////////////////////////////////////////////////////////
    //  WIFI start                                                             //
    /////////////////////////////////////////////////////////////////////////////
    wifiCred.begin();
    sysStatus.credFileErr.err( !wifiCred.ready );
	wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_FAST );
	if ( !simpleManualMode ){
		int tryCount = 0;
        DSPL( dPrompt + F("Wifi mode = ") + cParam.getWifiMode() );
		WiFi.setAutoConnect(false); //to allways control wifi connection
		DSP( dPrompt + F("Mode autoconnect : "));
		DSPL( WiFi.getAutoConnect()?"enabled":"disabled");
		DSPL( dPrompt + F("Wifi is connected ? ") +  String(WiFi.isConnected()?"Yes":"No") );
        WiFi.persistent(false);
        /*******************************************************************************************
        
        *******************************************************************************************/
        DSPL( dPrompt + F("Wifi def mode in FLASH : ") + String(wifi_get_opmode_default	() ) );
        softap_config	config;
        wifi_softap_get_config_default(&config);
        DSPL( dPrompt + "Wifi default soft AP param:" );
        DSPL( dPrompt + "SSID len : " + config.ssid_len );
        DSP( dPrompt + F("Stored SSID :") );
        for ( int i = 0; i < config.ssid_len ; i++ ){
            DSP( char(config.ssid[i]) );
        }
        DSPL( "." );
        /////////////////////////////////////////////////////////////////////////////
        //  Station mode                                                           //
        /////////////////////////////////////////////////////////////////////////////
        if ( cParam.getWifiMode() == "client" && !sysStatus.credFileErr.isErr()
                || cParam.getWifiMode() == "Station" ){ // Station WIFI mode    
            // WiFi.mode(WIFI_STA);
            WiFi.mode(WIFI_AP_STA);
            //void config(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
            if ( !cParam.getDHCPMode() ){
                IPAddress staIP = cParam.getStaIP();
                IPAddress staGateway = cParam.getStaGatewayIP();
                IPAddress DNS1;
                DNS1.fromString( "8.8.8.8");
                /** NO we decide to leave in the code as it is. change DNS as a config param */
                WiFi.config( staIP, staGateway, IPAddress(255, 255, 255, 0), DNS1 );
                DSPL( dPrompt + F("No DHCP mode, static IP add") );
            } 
            WiFi.begin( wifiCred.getSsid(), wifiCred.getPass() );
            DSPL(  dPrompt + F("Try to join : ") + wifiCred.getSsid() );
            wifiLedFlash( wifiLed, WIFILED_FLASH_COUNT );
            wifiLed.begin( WIFILED, WIFILED_FLASH_SLOW, WIFILED_FLASH_SLOW );
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                wifiLed.update();
                DSP(".");
                //a normal acces should came in 18 try
                tryCount++;
                if ( watchdog.isItTimeTo() ) watchdog.refresh();
                if (tryCount == cParam.getSTAMaxRetries() ) break;  
            }
            wifiLed.stop();
            wifiLed.high();
            DSP( "\n" + dPrompt + F("\nNumber of Station wifi try : ") + (String)tryCount );
            DSPL( ", max was : " + String( cParam.getSTAMaxRetries() ) );
            if ( WiFi.status() == WL_CONNECTED){
                sysStatus.ntpEnabled = true;
                DSPL(  dPrompt + F("Adresse Wifi.localIP Station mode : ") \
                    + WiFi.localIP().toString() );
                if ( cParam.getFirstBoot() == ConfigParam::TRY ){
                    ConfigParam::write2Json( "firstBoot", "OFF" );
                }                    
            } else { WiFi.disconnect(); }
        }
        /////////////////////////////////////////////////////////////////////////////
        //  soft AP mode                                                           //
        /////////////////////////////////////////////////////////////////////////////
        // if ( cParam.getWifiMode() == "softAP" || tryCount == cParam.getSTAMaxRetries()
                // // || !wifiCred.ready ){
                // || sysStatus.credFileErr.isErr() ){
        if( 1 ){
            //WIFI soft Access Point mode
            //        bool mode(WiFiMode_t);
            //        WiFiMode_t getMode();
//cf. https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiGeneric.h
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/generic-class.html
//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiType.h
            displayWifiMode();           
            // WiFi.begin();
            // WiFi.disconnect( true ); 
            // WiFi.softAPdisconnect();            
            // WiFi.mode(WIFI_AP);
            
            displayWifiMode();
            DSPL( dPrompt + F("Try softAccess") );
            // wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_SLOW );
            // wifiLedFlash( wifiLed , WIFILED_FLASH_COUNT );
            
            IPAddress apIP = cParam.getIPAdd();
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            // cParam.setWifiMode( "softAP" ); // not in the config file just for temorary mode
            /** DONE review the interest of keeping code below! */
            //As it is only debug informations leave it. When debug define will be turn off
            //this peace of code should desapear at the coompilation time.
            if ( wifiCred.ready ){
                DSPL( dPrompt + "Try soft AP with : " + wifiCred.getSoftApSsid() 
                        + " and " + wifiCred.getSoftApPass() );
                DSP( dPrompt + F("softAP : "));
                DSPL(WiFi.softAP(wifiCred.getSoftApSsid(),
                    wifiCred.getSoftApPass() )?F("Ready"):F("Failed!"));
                IPAddress myIP = WiFi.softAPIP();
                DSPL( dPrompt + "SoftAP returned IP address = " + myIP.toString()  );
            }
            // wifiLed.begin( WIFILED, WIFILED_SOFTAP_FLASH, WIFILED_SOFTAP_PERIOD );
            // to prepare for loop
            // sysStatus.ntpEnabled = false;
        }
		DSPL( dPrompt + F("Host name that not work with Android is : ") + cParam.getHostName() );
		// MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
        /** @todo [OPTION] mDNS.begin issue on github #4417 https://github.com/esp8266/Arduino/issues/4417
        try : LEAmDNS - Multicast DNS Responder #5442 -for now leav commented*/

	
	} else {
		DSPL(  dPrompt + F("Enter in simple manual mode") );
		cParam.setWifiMode( "No wifi" );
		simpleManualModeChaser();
	}
    
    /////////////////////////////////////////////////////////////////////////////
    //  Server configurations                                                  //
    /////////////////////////////////////////////////////////////////////////////
    server = new ESP8266WebServer( cParam.getServerPort() );
	if ( !simpleManualMode ){
        if ( cParam.getFirstBoot() == ConfigParam::YES 
                || cParam.getFirstBoot() == ConfigParam::TRY ){
            server->on("/", HTTP_GET, firstBootHtmlForm );
            DSPL( dPrompt + "First boot procedure");
        } else if ( cParam.getWifiMode() == "softAP" ) {
            server->on("/", HTTP_GET, handleSoftAPIndex );
            DSPL( dPrompt + F("******************reg page") );
        }
        server->on("/ChangeCred", HTTP_POST, handleNewCred );
        /** DONE 13/07/2019 update handleNewCred to reflect changes in credentials.json */
        //Note: The above function is disabled as long as the handleNewCred function has
        //not been updated
		server->on("/list", HTTP_GET, handleFileList);
		// server->on("/PlugConfig", HTTP_GET, handlePlugConfig );
        server->on("/cfgsend", HTTP_POST, handleIOTESPConfiguration );
        server->on("/cfgpage", HTTP_GET, handelIOTESPConfPage );
		server->on("/plugonoff", HTTP_POST, handlePlugOnOff ); 
        server->on("/firstBoot", HTTP_POST, handleFirstBoot);
		server->on("/edit", HTTP_GET, [](){
			if(!handleFileRead("/edit.htm")) server->send(404, "text/plain", "FileNotFound");
		});
		server->on("/help", HTTP_GET, [](){
			if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
		});
        /** @todo [OPTION] test FSBBrowserNG from https://github.com/gmag11/FSBrowserNG */
		server->on("/edit", HTTP_PUT, handleFileCreate);
		server->on("/edit", HTTP_DELETE, handleFileDelete);
		//first callback is called after the request has ended with all parsed arguments
		//second callback handles file uploads at that location
		server->on("/edit", HTTP_POST, [](){ server->send(200, "text/plain", ""); }, handleFileUpload);

		//called when the url is not defined here
		//use it to load content from SPIFFS
		server->onNotFound([](){
            if(!handleFileRead(server->uri()))
                server->send(404, "text/plain", "FileNotFound");
		}
        );    

		server->on( "/time", displayTime );

		// server->on ( "/inline", []() {
			// server->send ( 200, "text/plain", "this works as well" );
		// } );
		server->begin();
		Serial.println ( "HTTP server started" );
	
	}
    
    /////////////////////////////////////////////////////////////////////////////
    //  Time server check                                                     //
    /////////////////////////////////////////////////////////////////////////////
    // if ((wifi is on station mode connected))
    if( sysStatus.ntpEnabled){
        timeClient.begin();
        // errNTPinit = !timeClient.forceUpdate();
        sysStatus.ntpErr.err( !timeClient.forceUpdate() ) ;
        if ( !sysStatus.ntpErr.isErr() ){
            timeClient.setTimeOffset( timeZone * SECPERHOURS );
            // setTime(  timeClient.getEpochTime() );
            NTPTime = DateTime( timeClient.getEpochTime() );
            if (rtc.lostPower()){
                RTC_DS3231::adjust( NTPTime );
                DSPL( dPrompt + F("DS3231 set to NTP time due to power lost.") );
                CRtc::displayTime();
            }
            cParam.write2Json( "ntpError", "OFF" );
        } else { cParam.write2Json( "ntpError", "ON" ); }
    }


    /////////////////////////////////////////////////////////////////////////////
    //  Setup last operations                                                  //
    /////////////////////////////////////////////////////////////////////////////    
	SerialCommand::displayCommandsList();
    DSPL( dPrompt + "Leds On config : " + String( cParam.getAllLedsOnTime() ) );
    DSPL( dPrompt + "Leds On lumi : " + String( cParam.getLedsLuminosity() ) );

    if (cParam.getAllLedsOnTime() != -1 ){
        allLeds.begin();
        allLeds.start( cParam.getAllLedsOnTime()*1000 );
    }

    sysStatus.initCBITTimer();

    if ( WiFi.getMode() == WIFI_STA && WiFi.status() == WL_CONNECTED ){
        HTTPClient http;
        DSPL( dPrompt + F("[HTTP] begin...") );
        // configure targed server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin( INTERNET_HEALTH_TARGET ); //HTTP

        DSPL( dPrompt + F("[HTTP] GET... ") + INTERNET_HEALTH_TARGET );
        // start connection and send HTTP header
        int httpCode = http.GET();
        DSPL( dPrompt + "[HTTP] GET... code: " + String(httpCode) ) ;
        // httpCode will be negative on error
        if(httpCode < 0) {
            DSPL(dPrompt + F("[HTTP] GET... failed, error: ") + http.errorToString(httpCode) );
        }
        http.end();        
    }

    /////////////////////////////////////////////////////////////////////////////
    //  Setup watchdog                                                         //
    /////////////////////////////////////////////////////////////////////////////    
    watchdog.setTimeout( 10 );
    watchdog.setRefreshPeriod( 5 );    
    
}

/////////////////////////////////////////////////////////////////////////////
//        LOOP                                                             //
/////////////////////////////////////////////////////////////////////////////
bool cycleState = false;

void loop(){
    static unsigned long prevMillis = millis();
    DEFDPROMPT("in the loop")
    /////////////////////////////////////////////////////////////////////////////
    //  CBIT : Continus Built In Test                                          //
    /////////////////////////////////////////////////////////////////////////////
    //I2C
    // 3 CBIT times defined in IoT_ESP.h:
    //      RTC_UPDATE_PERIOD 15 //every 15mn
    //      I2C_CBIT_TEST_PERIOD 60 * 1000 //ms it smells millis() ;-)
    //      CBIT_TIME 60000 // period of CBIt in ms
    if ( millis() - prevMillis > I2C_CBIT_TEST_PERIOD){
        prevMillis = millis();
        int cpt = 1;
        do{
            if ( !nanoioExp.test( true ) ){
                DSPL( dPrompt + "i2cRecov" + " number " + cpt);
                SerialCommand::i2c_recovery();
            } else cpt = 9;
            
            cpt++;
        } while (cpt < I2C_RETRIES );
        if (cpt != 10) sysStatus.nanoErr.err( true ); 
    }
    // DSPL( dPrompt + (sysStatus.ntpEnabled?"yes":"no") );
    //NTP and RTC test
    if (sysStatus.ntpEnabled){
        bool rtcPreviousErr = sysStatus.ntpErr.isErr();
        rtc.update(); //this check NTP access and update sysStatus
        if ( sysStatus.ntpErr.isErr() != rtcPreviousErr ){
            cParam.write2Json( "ntpErr", ( sysStatus.ntpErr.isErr()?"ON":"OFF") );
        } 
    }
  

    if ( sysStatus.isCbitTime() ){
        //perform others CBIT
        DSPL(dPrompt + F("It is time to check necessary file accessibility !") );
        bool fileExist = true;
        for ( String s : necessaryFileList ){
            bool b = SPIFFS.exists(s);
            fileExist &= b;
            if (!b) DSPL( dPrompt + F("file : ") + s + F(" is not found") );
        }
        sysStatus.filesErr.err( !fileExist );
        
        if ( WiFi.getMode() == WIFI_STA && WiFi.status() == WL_CONNECTED ){
            HTTPClient http;
            DSPL(dPrompt + F("It is time to check Internet health !") );
            http.begin( INTERNET_HEALTH_TARGET ); //HTTP
            // start connection and send HTTP header
            int httpCode = http.GET();
            // httpCode will be negative on error
            if(httpCode < 0) {
                DSPL(dPrompt + "[HTTP] GET... failed, error: " + http.errorToString(httpCode) );
                sysStatus.internetErr.err( true );
            }
            http.end();
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    //  CBIT : Continus Built In Test End                                      //
    /////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////
    //  watchdog refresh                                                       //
    /////////////////////////////////////////////////////////////////////////////
    if ( watchdog.isItTimeTo() ) {
        //DSPL( dPrompt + F("TimeToRefresh wd") ) ;
        watchdog.refresh();
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //  Some little jobs : specialBp, ftp, SerialProcess...                    //
    /////////////////////////////////////////////////////////////////////////////
    if ( !simpleManualMode ) server->handleClient();
    
    ftpSrv.handleFTP();
    specialBp.update();
    
    SerialCommand::process(); 
    
    /////////////////////////////////////////////////////////////////////////////
    //  manage leds                                                            //
    /////////////////////////////////////////////////////////////////////////////
    FastLED.show(); 
    if ( cParam.getWifiMode() == "softAP" ) wifiLed.update();
    if (cParam.getAllLedsOnTime() != -1 ){  
        allLeds.update();
        if ( allLeds.finie ){
            DSPL( dPrompt + F("leds : it is time to switch off") );
            for ( int i = 0; i < 4 ; i++ ){
                colorLeds[i] = CRGB::Black;
                plugs[i].manageLeds( false );
            }
            wifiLed.stop();
            wifiLed.low();
            allLeds.stop();
            if ( cParam.getPowLedEconomyMode() ) nanoioExp.digitalWrite( MAINPOWLED, LOW );
        }
        if ( restartTempoLed ){
            for ( int i = 0; i < 4 ; i++ ){
                colorLeds[i] = plugs[i].getColor();
                plugs[i].manageLeds( true );
            }
            allLeds.start( cParam.getAllLedsOnTime()*1000 );
            if ( cParam.getWifiMode() == "softAP" ){
                wifiLed.begin( WIFILED, WIFILED_SOFTAP_FLASH, WIFILED_SOFTAP_PERIOD );
            } else {
                wifiLed.high();
            }
            nanoioExp.digitalWrite( MAINPOWLED, mainPowerSwitchState );
            restartTempoLed = false;
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //  manage bps + plugs time to switch                                      //
    /////////////////////////////////////////////////////////////////////////////     
    if ( mainPowerPrevState == HIGH && cParam.ready ){
        for ( int i = 0; i < NBRPLUGS ; i++ ){
            plugs[i].bp.update();
            if ( plugs[i].flashLedReq() ){ 
            // flashLedReq can be turned ON by plugs[i].handleBpDoubleClic
            // ie by simple clic and special BP simultanusly
                plugs[i].onOffFlasher.update();
                int flashCount =( plugs[i].getMode() + 1) *2;
                if ( plugs[i].getState() ) flashCount++;
                if ( plugs[i].onOffFlasher.getChangeStateCpt() >= flashCount ){
                    // DSPL( dPrompt + F("flash count condition ") + String(flashCount) );
                    plugs[i].handleBpDoubleClic(); //ie : stop flasher
                } 
            }
            if ( plugs[i].bp.clic() ){
                // DSPL( dPrompt + F("I10 state : ") + (specialBp.getState()?"ON":"OFF") );
                restartTempoLed = true;
                if ( specialBp.getState() ){ //input pull up so 1 means no action on BP
                    plugs[i].handleBpClic();
                } else {
                    plugs[i].handleBpDoubleClic();
                }   
            } 
            if ( plugs[i].isItTimeToSwitch() ){
                DSPL( dPrompt + "It is time for : " + plugs[i].getPlugName() );
                plugs[i].switchAtTime();
            }
            if ( plugs[i].bp.longClic() ){
                restartTempoLed = true;
                plugs[i].handleBpLongClic();
            }            
        }
        //led wake up
        if ( !specialBp.getState() && !allLeds.enCours() ){
            DSPL( dPrompt + F("LEDs wake up ! ") + String( restartTempoLed ) );
            restartTempoLed = true;
        } 
    }        
 
    /////////////////////////////////////////////////////////////////////////////
    //  main power switch actions                                              //
    /////////////////////////////////////////////////////////////////////////////
	mainPowerSwitchState = !digitalRead( MAINSWITCHPIN );
/** @todo [OPTION] recover debounce function */    
    if ( !mainPowerSwitchState) { //main power switch change state
            DSPL( dPrompt + F("main power switched OFF and all plugs are in manual state.") );
            for ( int i = 0; i < NBRPLUGS ; i++ ){
                plugs[i].off();
                plugs[i].handleBpLongClic();
                plugs[i].setMainPow( false );
                colorLeds[i] = CRGB::Black;
            }            
            FastLED.show();
            wifiLed.low();
            //watchdog.enableRefresh( false ); //doesn't work crash json file
            watchdog.setTimeout( 2 );
            while( 1 )yield(); //another way to stop AtinyWD refresh.
            //ESP.restart();
    }

    yield();
}


/////////////////////////////////////////////////////////////////////////////
//  Simple local functions                                                 //
/////////////////////////////////////////////////////////////////////////////

void wifiLedFlash( CFlasherNanoExp led, int count ){
    
	while ( led.getChangeStateCpt() < count ){
		led.update();
		yield();
	}
    led.stop();
}

/** 
 @fn void simpleManualModeChaser()
 @brief Flash 4 colored LEDs in PURPLE 200ms/200ms 20 times and restaure colors to indicate
 Simple Manual mode activation
 @return no return value and no parameter
*/
void simpleManualModeChaser(){
	for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
	FastLED.show();
	delay(500);
	
	for (int i=0; i < 20; i++){
		for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
		FastLED.show();
		delay(200);	
		for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Purple;
		FastLED.show();
		delay(200);				
	}
	
	//restaure Color Leds state
	for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = plugs[i].getColor();    
	FastLED.show();
}


void displayWifiMode(){
    DEFDPROMPT("WiFi mode")
    DSP( dPrompt ) ;
    String s_wifiMode;
    //WIFI_OFF = 0, WIFI_STA = 1, WIFI_AP = 2, WIFI_AP_STA = 3
    switch ( WiFi.getMode() ){
        case 0: s_wifiMode = F("WIFI_OFF"); break;
        case 1: s_wifiMode = F("WIFI_STA"); break;
        case 2: s_wifiMode = F("WIFI_AP"); break;
        case 3: s_wifiMode = F("WIFI_STA and AP"); break;
        default : s_wifiMode = F("???");
    }
    DSPL( s_wifiMode );
}