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
 - Utilisation de la bibliothèque FastCRC-master version 1.31

@section wifi WIFIs connexions

If credentials are found in SPIFFS, IoT_EPS tries to connect about 20 times (time out = 10s).

If it can't reach WIFI network it switch to acces point mode.

In Access point mode default add is 192.168.95.42. Ssid and pass are those store in the SPIFFS credential.json

In station mode, when WIFI is not reachable, it switchs in softAP mode and WIFI LED fash shortly in 2s period.


 @bug Serial command < d > delete file with space in their name !

 @section How it works (this code)

 ??? In July 2020, I realised that I don't know how my code works in details. 
 
 By the usage of a lost
 of external lib like FastLED, ESP8266Webserver, RTClib... A lot of global variables, a very very 
 long main code here. I decide to refactor my code. A very hard task.

 ESP8266Webserver librairy documentation
*/

/**
 @page pageTodo Macro roadmap
 @tableofcontents
  doxygen todo list is not enought ! It is a good practice to highlight on certain ligne of code.
  Here I want to trace major features implementations.

 @li rewrite more OO of main code 
 @li test restore defConfig.json when firstBoot 
 @li see hardware.rst file
 
 @li power plugs current measurements
 @li manage summer and winter hour change
 @li if i say to you utf-8 ?!

 @li document FATAL errors color (see xlsx dedicate file)
 @li regarder pour recharger la page index lors d'un changement d'état par BP(pas forcément an mode AP)
 impossible this is the navigator to ask for a page and html refresh param is not a good idea !
 @li code, bugs and todo review : remove all unused commented code (cleanup)
*/

//Dev system objet juin 2020

#include "IoT_EPS.h"
#include "ESP8266FtpServer.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
FtpServer ftpSrv;
CSystem sysIoteps;
CServerWeb webServeur;
CWifiLink wifilnk;

CJsonIotEps jsonData;



Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#warning SSD1306_LCDHEIGHT
	
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


CRtc rtc;

ConfigParam cParam; /**< @brief to hold the configuration parameters*/
Credential wifiCred;
CPowerPlug *plugs;

CRGB colorLeds[NUM_LEDS]; /**< @brief  not very satisfy for this globale ! It should be in the 
CpowerPlug class as a static member*/
//It is used with FastLED that it should be concidered as a common ressource
//It is not very important because cpowerplug instance never drive these LED !
//Yes near 342 line : colorLeds[i] = plugs[i].getColor();


CFlasherNanoExp wifiLed;
/** DONE 13/07/2019 [NECESSARY] check if it is possible to remove Flasher class (CNanoI2CIOExp used)
if yes remove Flasher.cpp and .h from source files */

CSwitchNano specialBp;
CNanoI2CIOExpander nanoioExp; //just for main pow led
WiFiUDP ntpUDP;

bool simpleManualMode = false;
int mainPowerSwitchState;
int mainPowerPrevState = 0;
CTempo allLeds;
bool restartTempoLed = false;

/** @todo
 - [OPTION 1] see for add colorLEd array in the class CPowerPlug as a static member
 - [NECESSARY for 1 and 2 plug strip] convert colorLeds array in dynamic version as for plugs array */





void setup(){
    DEBUGPORT.begin(DEBUGSPEED);
    DEFDPROMPT("setUp") // define dPrompt String

    display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADD );
    display.clearDisplay();

    // int timeZone = OFFSET_HEURE;
    String buildInfo =  String(__DATE__) + " @ " + String(__TIME__);

    sysIoteps.init( ntpUDP, &sysStatus, &SPIFFS, &cParam, necessaryFileList, NECESSARY_FILE_NBR
                    , buildInfo, &WiFi, &nanoioExp, &display, &jsonData );

    DSPL( dPrompt + F("Check json integrity after System init "));
    jsonData.printFileIntegrity();

    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(colorLeds, NUM_LEDS);
    FastLED.setBrightness( DEFAULT_LED_LUMINOSITY ); //default value for error display
    
    ftpSrv.begin("esp8266","esp8266");
    
	SerialCommand::init();

    /////////////////////////////////////////////////////////////////////////////
    // Watchdog check                                                          //
    ///////////////////////////////////////////////////////////////////////////// 
    watchdog.begin();
    DSPL( dPrompt + F("watchdog test ") );
    sysStatus.watchdogErr.err( !watchdog.test() );
    if ( !sysStatus.watchdogErr.isErr() ){
        DSPL( "watchdog OK"); //normaly if error we did not reach
        //this point unless _forceSystemStartOnFatalError is true for debug
        watchdog.setTimeout( cParam.getSTAMaxRetries() );
        watchdog.setRefreshPeriod( cParam.getSTAMaxRetries()/3 );  
        DSPL( dPrompt + F("watchdog set to ") + String( cParam.getSTAMaxRetries() ) + F("s.") );
        //oled message
        display.println("* watchdog ok");
        display.display();
    } else {
        DSPL( dPrompt + F("watchdog is not set due to errors."));
        display.println("* watchdog error");
        display.display();
    }

    /////////////////////////////////////////////////////////////////////////////
    //     Main power first check                                              //
    /////////////////////////////////////////////////////////////////////////////    
    pinMode( MAINSWITCHPIN, INPUT_PULLUP);
    nanoioExp.digitalWrite( MAINPOWLED, 0);
    nanoioExp.pinMode( MAINPOWLED, OUTPUT ); 
    mainPowerSwitchState = !digitalRead( MAINSWITCHPIN ); //open circuit = plug OFF
    webServeur.setMPSstVar( mainPowerSwitchState );    
    
    nanoioExp.digitalWrite( MAINPOWLED, mainPowerSwitchState );
    DSPL( dPrompt + "Main power state : " +  ( mainPowerSwitchState?"ON":"OFF") );
    specialBp.begin( SPECIALBP, 20, INPUT_PULLUP );

  
    /////////////////////////////////////////////////////////////////////////////
    //     Plugs init and config                                                        //
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
    
    /** todo : no ! It is not a user config  [OPTION] add pin, pinLed and color to json file*/
    /** todo : no it should stay  as a define 
    [NECESSARY for 2 and 1 plugs strip] + the number of plug to make this sequence dynamic*/

    /* DONE test if CNano::initOk = true - if not don't start anything - this is fatal error*/
    plugs[0].begin( PLUG0PIN, PLUG0_ONOFFLEDPIN, BP0, CRGB::Red
                    , HTML_JSON_REDPLUGNAME, CPowerPlug::modeId("MANUEL") );   
    plugs[1].begin( PLUG1PIN, PLUG1_ONOFFLEDPIN, BP1, CRGB::Green
                    , HTML_JSON_GREENPLUGNAME, CPowerPlug::modeId("MANUEL") );   
    plugs[2].begin( PLUG2PIN, PLUG2_ONOFFLEDPIN, BP2, CRGB::Blue
                    , HTML_JSON_BLUEPLUGNAME, CPowerPlug::modeId("MANUEL") );
    plugs[3].begin( PLUG3PIN, PLUG3_ONOFFLEDPIN, BP3, CRGB::Yellow
                    , HTML_JSON_YELLOWPLUGNAME, CPowerPlug::modeId("MANUEL") );

    sysIoteps.setPlugsAdd( plugs ); // cause of the new plugs above

    sysStatus.plugParamErr.err( 
        !jsonData.loadJsonPlugParam( cParam.getNumberOfPlugs(), mainPowerSwitchState ) );
    
    // for (int i = 0; i < NBRPLUGS; i++ ){
    //     if ( mainPowerSwitchState ) sysStatus.plugParamErr.err( !plugs[i].readFromJson( true ) );
    //     else  plugs[i].handleBpLongClic(); //force OFF is main power off  
        
    // }

    //note: 07/08/2021 : in the above code we can't call _pPlugs in sysIoteps cause it is a private
    // member.

    



    /* DONE : document simpleManualMode with no wifi at all */
    simpleManualMode = plugs[0].bp.directRead();


    //               123456789+123456789+1

    display.println("Check main power sw"); //L2
    display.display();
    delay(200);

    /////////////////////////////////////////////////////////////////////////////
    //     Main power wait ON (the purpose is to maintain Wifi off)            //
    ///////////////////////////////////////////////////////////////////////////// 
    if ( !mainPowerSwitchState ){
        DSPL( dPrompt + "Wait main power switch ON");
        for ( int i = 0; i < 4 ; i++ ) colorLeds[i] = CRGB::Black;
        FastLED.show();
        do {
            mainPowerSwitchState = !digitalRead( MAINSWITCHPIN ); //open circuit = plug OFF
            webServeur.setMPSstVar( mainPowerSwitchState );
            yield();
            if ( watchdog.isItTimeTo() ) watchdog.refresh();
            DSPL("Wait main power");
        } while( !mainPowerSwitchState );        
    }
    DSPL( dPrompt + "Main power ON");
    mainPowerPrevState = mainPowerSwitchState; // for the loop
    nanoioExp.digitalWrite( MAINPOWLED, 1);

    display.println("Main power on"); //L3
    display.display();
    delay(200);    


// with this way of doing it, we loose LED and other stuffs managment    
    // replace by WIFI_OFF no ?
    /** @todo [OPTION] try  WIFI_OFF when power is off */
    for ( int i = 0; i < NBRPLUGS ; i++ ){
        colorLeds[i] = plugs[i].getColor();
        plugs[i].setMainPow( mainPowerSwitchState );
    }
    FastLED.setBrightness( cParam.getLedsLuminosity() );
    FastLED.show();
        
	/////////////////////////////////////////////////////////////////////////////
    //  WIFI start                                                             //
    /////////////////////////////////////////////////////////////////////////////
    wifilnk.begin( WiFi, simpleManualMode, &cParam, &sysStatus, &wifiLed,
                    &FastLED, colorLeds, plugs, &display );

    DSPL( dPrompt + "NTP enable ? " + String(sysStatus.ntpEnabled?"TRUE":"FALSE") );
    /////////////////////////////////////////////////////////////////////////////
    //  Server configurations                                                  //
    /////////////////////////////////////////////////////////////////////////////
    //Code replaced by webserver class August 2020
    if ( !simpleManualMode ){
        webServeur.init( &rtc, &cParam, plugs, &restartTempoLed, &WiFi );
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //  Time server check                                                     //
    /////////////////////////////////////////////////////////////////////////////
    sysIoteps.timeServerCheck();


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

    //Check internet access

    if ( (WiFi.getMode() == WIFI_STA || WiFi.getMode() == WIFI_AP_STA) 
            && WiFi.status() == WL_CONNECTED ){
        HTTPClient http;
        DSPL( dPrompt + F("[HTTP] begin...") );
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
    display.clearDisplay();
    sysIoteps.oledLoopBackScreen();    
    sysIoteps.oledDisplayDate();
    sysIoteps.oledDisplaySate();
    sysIoteps.oledDisplayIps();
    
    /////////////////////////////////////////////////////////////////////////////
    //  Setup watchdog                                                         //
    /////////////////////////////////////////////////////////////////////////////
    String err = sysStatus.watchdogErr.isErr()?"Erreur":"tout va bien";
    DSPL( dPrompt + "track WD if wd error state changed : " + err);
    watchdog.setTimeout( 10 );
    watchdog.setRefreshPeriod( 5 );
    DSPL( dPrompt + F("Watchdog set to 10s with a refresh period to 5s") );
    DSPL( dPrompt + F("Loop start") );


}

/////////////////////////////////////////////////////////////////////////////
//        LOOP                                                             //
/////////////////////////////////////////////////////////////////////////////
bool cycleState = false;

void loop(){
    static unsigned long prevMillis = millis();

    //CRtc rtc; // why a new local instance ?
    //Commented on 30/09/2020 to force global variable rtc usage on top of this file
    //global instance is initialized by CSystem whith a NTP server pointer

    DEFDPROMPT("in the loop")
    /////////////////////////////////////////////////////////////////////////////
    //  CBIT : Continus Built In Test Start                                    //
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


    if ( sysStatus.isCbitTime() ){
        //perform others CBIT
        //files acces
        DSPL(dPrompt + F("It is time to check necessary file accessibility !") );
        bool fileExist = true;
        for ( String s : necessaryFileList ){
            bool b = SPIFFS.exists(s);
            fileExist &= b;
            if (!b) DSPL( dPrompt + F("file : ") + s + F(" is not found") );
        }
        sysStatus.filesErr.err( !fileExist );

        //internet access
        if ( (WiFi.getMode() == WIFI_STA || WiFi.getMode() == WIFI_AP_STA)
              && WiFi.status() == WL_CONNECTED ){
            HTTPClient http;
            DSPL(dPrompt + F("It is time to check Internet health !") );
            http.begin( INTERNET_HEALTH_TARGET ); //HTTP
            // start connection and send HTTP header
            int httpCode = http.GET();
            // httpCode will be negative on error
            if(httpCode < 0) {
                DSPL(dPrompt + "[HTTP] GET... failed, error: " + http.errorToString(httpCode) );
                sysStatus.internetErr.err( true );
            } else {
                sysStatus.internetErr.err( false ); //bug internet error correction
            }
            http.end();
        }

        if (sysStatus.ntpEnabled){
            bool rtcPreviousErr = sysStatus.ntpErr.isErr();
            rtc.update(); //this check NTP access and update sysStatus
            DSP( dPrompt + F("Check NTP access : " ) );
            if ( sysStatus.ntpErr.isErr() != rtcPreviousErr ){
                cParam.write2Json( "ntpError", ( sysStatus.ntpErr.isErr()?"ON":"OFF") );
            }
            DSPL( sysStatus.ntpErr.isErr()?"ERROR":"OK" );
            /** @todo: check the use of configjson param : ntperror see softDev.rst 
             * JSON structure vs variables chapter
            */
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
    //  oled refresh display if necessary                                      //
    /////////////////////////////////////////////////////////////////////////////
    sysIoteps.oledLoopChangeDispayIf();
    
    /////////////////////////////////////////////////////////////////////////////
    //  Some little jobs : specialBp, ftp, SerialProcess...                    //
    /////////////////////////////////////////////////////////////////////////////
    if ( !simpleManualMode ) webServeur.serviceClient();
    // if ( !simpleManualMode ) server->handleClient();
    
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
        if ( restartTempoLed ){ //on an event do not switch off Leds
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
    webServeur.setMPSstVar( mainPowerSwitchState );
/** @todo [OPTION] recover debounce function */    
    if ( !mainPowerSwitchState) { //main power switch change state
            DSPL( dPrompt + F("main power switched OFF and all plugs return in manual state.") );
            for ( int i = 0; i < NBRPLUGS ; i++ ){
                plugs[i].off();
                plugs[i].handleBpLongClic(); // to set all plug in manual state
                plugs[i].setMainPow( false );
                colorLeds[i] = CRGB::Black;
            }            
            FastLED.show();
            wifiLed.low();
            //watchdog.enableRefresh( false ); //doesn't work crash json file
            sysIoteps.oledDsiplayShutDown();
            watchdog.setTimeout( 2 );
            while( 1 )yield(); //another way to stop AtinyWD refresh.
            //ESP.restart();
    }

    //Main loop Oled displays
    //cparam has ip adresse

    // Store json file if needed
    // if cParam.storeNeeded or for i in 4 plug[i].storeNeeded
    if ( jsonData.checkIfStoreNeeded() ){
        jsonData.storeJson();
    }

    yield();
}
