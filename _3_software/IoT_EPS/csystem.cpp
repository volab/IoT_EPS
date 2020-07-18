/**
 @file csystem.cpp
 @author J.SORANZO
 @date 30/06/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Fichier d'implémentation de la classe system pour englober tout le system
*/

#include "csystem.h"

void CSystem::init(){
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


    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                    //
    /////////////////////////////////////////////////////////////////////////////
    _rtc.begin();
    _sysStat.rtcErr.err( _rtc.initErr );
    if (_rtc.lostPower()){
        DSPL( dPrompt + "une remise a l'heure est necessaire");
    }
    now = _rtc.now();
    String message = dPrompt + F("DS3231 Start date : ");
    message += (String)now.day()+"/"+(String)now.month()+"/";
    message += (String)now.year()+" ";
    message += (String)now.hour()+":"+ (String)now.minute()+":";
    message += (String)now.second();      
    DSPL( message);

     _timeClient= new NTPClient(_ntpUDP, NTPSERVER);
    /////////////////////////////////////////////////////////////////////////////
    //  Time server check                                                     //
    /////////////////////////////////////////////////////////////////////////////
    // if ((wifi is on station mode connected))
    if( _sysStat.ntpEnabled){
        _timeClient->begin();
        // errNTPinit = !timeClient.forceUpdate();
        _sysStat.ntpErr.err( !_timeClient->forceUpdate() ) ;
        if ( !_sysStat.ntpErr.isErr() ){
            _timeClient->setTimeOffset( timeZone * SECPERHOURS );
            // setTime(  timeClient.getEpochTime() );
            NTPTime = DateTime( _timeClient->getEpochTime() );
            if (_rtc.lostPower()){
                RTC_DS3231::adjust( NTPTime );
                DSPL( dPrompt + F("DS3231 set to NTP time due to power lost.") );
                // CRtc::displayTime();
            }
            _cParam.write2Json( "ntpError", "OFF" );
        } else { _cParam.write2Json( "ntpError", "ON" ); }
    }        
}