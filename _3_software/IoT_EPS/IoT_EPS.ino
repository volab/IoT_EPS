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
- Utilisation de la bibliothèque ESP8266WebServer version 1.0
- Utilisation de la bibliothèque ArduinoJson version 5.13.2
- Utilisation de la bibliothèque Wire version 1.0
- Utilisation de la bibliothèque RTClib version 1.2.0
- Utilisation de la bibliothèque ESP8266mDNS
- Utilisation de la bibliothèque Adafruit_MCP23017_Arduino_Library version 1.0.3
- Utilisation de la bibliothèque FastLED version 3.2.1
- Utilisation de la bibliothèque nanoI2CIOExpLib version 1.0
- Utilisation de la bibliothèque NTPClient version 3.1.0 

@section wifi WIFIs connexions

If credentials are found in SPIFFS are found plugs try to connect about 20 times (time out = 10s).

If it can't reach WIFI network it switch to acces point mode.

In Access point mode default add is 192.168.95.42. Ssid and pass are those store in the SPIFFS credential.json

In station mode, when WIFI is not reachable, it switchs in softAP mode and WIFI LED fash shortly in 2s period.

*/

/**
 @page pageTodo Macro roadmap
 @tableofcontents
  doxygen todo list is not enought ! It is a good practice to highlight on certain ligne of code.
  Here I want to trace major features implementations.
 
 @li add I and i like commands for softAP_SSID and soft_AP pass (more then 8c)
 @li improve <W> commande to display the good SSID regardless of real connected mode 
 @li config power led economy mode 50% todo put it in the config3.json
 @li change config3 to config4 (see softdev.rst)
 @li configuration page (see softdev.rst)
 @li generate a unic server name  
 @li bug report when json is no reachable !
 @li review work without RTC component strategy
 @li review work without NTP access strategy
 @li define rtc component versus NTP update strategy 
 @li improve error handling
 @li power measurment
 @li manage sun and winter hour change
 
*/


#include "IoT_EPS.h"
#include "ESP8266FtpServer.h"
FtpServer ftpSrv;

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
// IPAddress apIP(192, 168, 95, 42);


// CPowerPlug plugs[NBRPLUGS];
CPowerPlug *plugs;

// bool errRTCinit = true;
bool errFS = true;

/** @todo see for add colorLEd array in the class CPowerPlug as a static member*/
/** @todo convert colorLeds array in dynamic version as for plugs array */
CRGB colorLeds[NUM_LEDS]; /**< @brief  not very satisfy for this globale ! It should be in the 
CpowerPlug class*/


bool simpleManualMode = false;

Flasher wifiLed;

CSwitchNano mainPowerSiwtch;
int mainPowerSwitchState;
int mainPowerPrevState = 0;
CSwitchNano specialBp;

CNanoI2CIOExpander nanoioExp; //just for main pow led

// CFlasherNanoExp extraLed;

// bool allLedsOn = true;
CTempo allLeds;
bool restartTempoLed = false;

void setup(){
    DEFDPROMPT("setUp") // define dPrompt String
    DateTime now;
    DEBUGPORT.begin(DEBUGSPEED);
    DSPL();
    DSPL( dPrompt + F("Sketch start..."));

    /////////////////////////////////////////////////////////////////////////////
    //     file system check                                                   //
    /////////////////////////////////////////////////////////////////////////////
    DSPL( dPrompt + " Build : " + __DATE__ + " @ " + __TIME__);
    errFS = !SPIFFS.begin(); // to check if it's possible to begin twice the SPIFFS
    //next time is in cParam.begin
    // The response was already in the code : about line 300
    //secon time commented on 2019/03
    if (errFS){
        DSPL( dPrompt + F("error in Opening File System") );
        //can we work without file system ? No
        fatalError();
    } else DSPL( dPrompt + F("File system corectly Open @ setup level") );
    
    ftpSrv.begin("esp8266","esp8266");
    
	SerialCommand::init();
    // extraLed.begin( 9, 100, 500, 4, 5000 );
    
    cParam.begin();
    if ( !cParam.ready ) {
        DSPL( dPrompt + F("cParam default values. Potential fatal error") );
        // fatalErro();
    }
 
    /////////////////////////////////////////////////////////////////////////////
    //     I2C bus check                                                    //
    ///////////////////////////////////////////////////////////////////////////// 
    CNano::init();
    rtc.begin();
    if ( !nanoioExp.test() && rtc.initErr){
        DSPL(dPrompt + F("I2C bus fatal error !"));
        /** @todo re- enable funcion call fatalError after debug */
        //fatalError();
    }
  
    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                    //
    /////////////////////////////////////////////////////////////////////////////
    rtc.begin();
    if ( rtc.initErr ) {
        DSPL(dPrompt + F("ERR : Couldn't find RTC"));
        /** @todo Stop EPS and warn with colors and others LED ,
        cause without right time EPS dosen't work.
        Except perhaps the manual mode ! */
    } else {
        if (rtc.lostPower()){
            DSPL( dPrompt + "une remise a l'heure est necessaire");
            /** @todo enable or not ? errRTCinit due to lots power*/
        }
        // errRTCinit = false;0
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
    //     Main power                                                          //
    /////////////////////////////////////////////////////////////////////////////    
    // Cmcp::init();
    
    
    mainPowerSiwtch.begin( MAINSWITCHPIN, 5, INPUT_PULLUP );
    mainPowerSwitchState = !mainPowerSiwtch.digitalRead(); //open circuit = plug OFF
    mainPowerPrevState = mainPowerSwitchState; // for the loop
    
    // CNano::_nano.pinMode( MAINPOWLED, OUTPUT ); // _nano is protected
    // CNano::_nano.digitalWrite( MAINPOWLED, mainPowerSwitchState );
    nanoioExp.pinMode( MAINPOWLED, OUTPUT );
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
    
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(colorLeds, NUM_LEDS);

    /** @todo test if CNano::initOk = true - if not don't start anything*/
    plugs[0].begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, BP0, CPowerPlug::modeId("MANUEL") );
    plugs[0].setColor( CRGB::Red );
    plugs[0].setPlugName( HTML_JSON_REDPLUGNAME );
    if ( mainPowerSwitchState ) plugs[0].readFromJson( true );
    else  plugs[0].handleBpLongClic(); //change due to clone mode bug
    
    /** @todo improve error check from CPowerPlug::readFromJson*/
    /** @todo add pin, pinLed and color to json file*/
    /** @todo + le nombre de plug pour rendre cette séquense dynamic*/
    
    plugs[1].begin( PLUG1PIN, PLUG1_ONOFFLEDPIN, BP1, CPowerPlug::modeId("MANUEL") );
    plugs[1].setColor( CRGB::Green );
    plugs[1].setPlugName( HTML_JSON_GREENPLUGNAME );
    if ( mainPowerSwitchState ) plugs[1].readFromJson( true );
    else  plugs[1].handleBpLongClic();
    plugs[2].begin( PLUG2PIN, PLUG2_ONOFFLEDPIN, BP2, CPowerPlug::modeId("MANUEL") );
    plugs[2].setColor( CRGB::Blue );
    plugs[2].setPlugName( HTML_JSON_BLUEPLUGNAME );
    if ( mainPowerSwitchState ) plugs[2].readFromJson( true );
    else  plugs[2].handleBpLongClic();
    // plugs[2].setColor( CRGB::Purple );
    plugs[3].begin( PLUG3PIN, PLUG3_ONOFFLEDPIN, BP3, CPowerPlug::modeId("MANUEL") );
    plugs[3].setColor( CRGB::Yellow );
    plugs[3].setPlugName( HTML_JSON_YELLOWPLUGNAME );
    if ( mainPowerSwitchState ) plugs[3].readFromJson( true );
    else  plugs[3].handleBpLongClic();
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        colorLeds[i] = plugs[i].getColor();
        /** @todo creat a pointer in CPowerPlug to one position off colorLeds*/
        plugs[i].setMainPow( mainPowerSwitchState );
    }
    // FastLED.setBrightness(5);
    FastLED.setBrightness( cParam.getLedsLuminosity() );
    FastLED.show();
	
    /** @todo document simpleManualMode with no wifi at all */
    simpleManualMode = plugs[0].bp.directRead();
	/////////////////////////////////////////////////////////////////////////////
    //  WIFI start                                                             //
    /////////////////////////////////////////////////////////////////////////////
    wifiCred.begin();    
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
        //strcpy(reinterpret_cast<char*>(conf.ssid), ssid); dans le fichier ESP8266WiFiSTA.cpp
        DSPL( "." );
        
        if ( cParam.getWifiMode() == "client" && wifiCred.ready
                || cParam.getWifiMode() == "Station" ){ // Station WIFI mode
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
            DSPL( dPrompt + F("\nNumber of Station wifi try : ") + (String)tryCount );
            if ( WiFi.status() == WL_CONNECTED){
                DSPL(  dPrompt + F("Adresse Wifi.localIP Station mode : ") \
                    + WiFi.localIP().toString() );  
            } else { WiFi.disconnect(); }
        }
        if ( cParam.getWifiMode() == "softAP" || tryCount == MAX_WIFI_CONNECT_RETRY
                || !wifiCred.ready ){
            //WIFI soft Access Point mode
            //        bool mode(WiFiMode_t);
            //        WiFiMode_t getMode();
//cf. https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiGeneric.h
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/generic-class.html
//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiType.h
            displayWifiMode();           
            WiFi.begin();
            WiFi.disconnect( true ); 
WiFi.softAPdisconnect();            
            WiFi.mode(WIFI_AP);
            
            displayWifiMode();
            DSPL( dPrompt + F("Try softAccess") );
            wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_SLOW );
            wifiLedFlash( wifiLed , WIFILED_FLASH_COUNT );
            
            IPAddress apIP = cParam.getIPAdd();
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            cParam.setWifiMode( "softAP" ); // not in the config file just for temorary mode
            /** @todo review the interest of keeping code below! */
            if ( wifiCred.ready ){
                DSPL( dPrompt + "Try soft AP with : " + wifiCred.getSoftApSsid() 
                        + " and " + wifiCred.getSoftApPass() );
                DSP( dPrompt + F("softAP : "));
                DSPL(WiFi.softAP(wifiCred.getSoftApSsid(),
                    wifiCred.getSoftApPass() )?F("Ready"):F("Failed!"));
                IPAddress myIP = WiFi.softAPIP();
                DSPL( dPrompt + "SoftAP returned IP address = " + myIP.toString()  );
            }
            // digitalWrite( WIFILED, LOW);
            wifiLed.begin( WIFILED, WIFILED_SOFTAP_FLASH, WIFILED_SOFTAP_PERIOD );
            // to prepare for loop
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
    // if (!SPIFFS.begin()){
        // DSPL(dPrompt + F("SPIFFS Mount failed"));
    // } else {
        // DSPL(dPrompt + F("SPIFFS Mount succesfull"));
    // }
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
    server = new ESP8266WebServer( cParam.getServerPort() );
	if ( !simpleManualMode ){
        if ( cParam.getWifiMode() == "softAP" ) {
            server->on("/", HTTP_GET, handleSoftAPIndex );
            DSPL( dPrompt + F("******************reg page") );
        }
        server->on("/ChangeCred", HTTP_POST, handleNewCred );
		server->on("/list", HTTP_GET, handleFileList);
		server->on("/PlugConfig", HTTP_GET, handlePlugConfig );
		// server->on("/", HTTP_POST, handlePlugOnOff ); 
		server->on("/plugonoff", HTTP_POST, handlePlugOnOff ); 
		server->on("/edit", HTTP_GET, [](){
			if(!handleFileRead("/edit.htm")) server->send(404, "text/plain", "FileNotFound");
		});
		server->on("/help", HTTP_GET, [](){
			if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
		});
        /** @todo test FSBBrowserNG from https://github.com/gmag11/FSBrowserNG */
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

		server->on ( "/inline", []() {
			server->send ( 200, "text/plain", "this works as well" );
		} );
		server->begin();
		Serial.println ( "HTTP server started" );
	
	}
	
	SerialCommand::displayCommandsList();
    DSPL( dPrompt + "Leds On config : " + String( cParam.getAllLedsOnTime() ) );
    DSPL( dPrompt + "Leds On lumi : " + String( cParam.getLedsLuminosity() ) );

    if (cParam.getAllLedsOnTime() != -1 ){
        allLeds.begin();
        allLeds.start( cParam.getAllLedsOnTime()*1000 );
    }

}

/////////////////////////////////////////////////////////////////////////////
//        LOOP                                                             //
/////////////////////////////////////////////////////////////////////////////
bool cycleState = false;
void loop(){
    // cycleState = !cycleState;
    // digitalWrite( WIFILED, cycleState); 
    // static unsigned long prevMillis = millis();
    // static bool prevAllLedsOn;
    // prevAllLedsOn = allLedsOn;
    DEFDPROMPT("in the loop")
    if ( !simpleManualMode ) server->handleClient();
    
    ftpSrv.handleFTP();
    
    mainPowerSiwtch.update();
    specialBp.update();
    
    SerialCommand::process();

    // extraLed.update();  
    
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
            pinMode( WIFILED, OUTPUT );
            digitalWrite( WIFILED, LOW);
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
                pinMode( WIFILED, OUTPUT );
                digitalWrite( WIFILED, HIGH);                
            }
            nanoioExp.digitalWrite( MAINPOWLED, mainPowerSwitchState );
            restartTempoLed = false;
        }
    }
    // if ( millis() - prevMillis >= cParam.getAllLedsOnTime() &&
        // cParam.getAllLedsOnTime() != -1  ){
        // for ( int i = 0; i < 4 ; i++ ){
           // plugs[i].setColor( CRGB::Black ); 
        // }            
        // allLedsOn = false;
    // }

    /////////////////////////////////////////////////////////////////////////////
    //  manage bps                                                            //
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
        // int etatBP = specialBp.getState();
        // DSPL( dPrompt + F("SPBp state = ") + String( etatBP ) );
        if ( !specialBp.getState() && !allLeds.enCours() ){
            DSPL( dPrompt + F("LEDs wake up ! ") + String( restartTempoLed ) );
            restartTempoLed = true;
        } 
    }        
 
    /////////////////////////////////////////////////////////////////////////////
    //  main power switch actions                                              //
    /////////////////////////////////////////////////////////////////////////////
	mainPowerSwitchState = !mainPowerSiwtch.getState();    
    if ( mainPowerSwitchState != mainPowerPrevState){ //main power switch change state
        mainPowerPrevState = mainPowerSwitchState;
        if (mainPowerSwitchState == HIGH ){ 
            DSPL( dPrompt + F("main power switched ON."));
            restartTempoLed = true;
            for ( int i = 0; i < NBRPLUGS ; i++ ){                
                plugs[i].setMainPow( true );
                colorLeds[i] = plugs[i].getColor(); //restaure color LED
            }
            //restaure wifiLed state
            /** @todo restaure wifi LED in AP mode */
            if ( WiFi.status() == WL_CONNECTED ){
                digitalWrite( WIFILED, HIGH);   
            }
        } else {
            DSPL( dPrompt + F("main power switched OFF and all plugs are in manual state.") );
            for ( int i = 0; i < NBRPLUGS ; i++ ){
                plugs[i].off();
                plugs[i].handleBpLongClic();
                plugs[i].setMainPow( false );
                colorLeds[i] = CRGB::Black;
            }            
            FastLED.show();
            digitalWrite( WIFILED, LOW);  //stop wifi LED  
        }
        nanoioExp.digitalWrite( MAINPOWLED, mainPowerSwitchState );
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


/** 
 @fn void fatalError()
 @brief flash 4 color LED 50ms/50ms in RED for all time
 @return no return value and no parameter
*/
void fatalError(){
    for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
    FastLED.show();
    delay(500);
    while (1){     
        for (int i=0; i < 20; i++){
            for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
            FastLED.show();
            delay(50);	
            for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Red;
            FastLED.show();
            delay(50);				
        }
        yield();
    }
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