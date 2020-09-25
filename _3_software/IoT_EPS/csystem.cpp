/**
 @file csystem.cpp
 @author J.SORANZO
 @date 30/06/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Fichier d'implémentation de la classe system pour englober tout le system
*/

#include "csystem.h"


/**
 @fn void CSystem::init( WiFiUDP &ntpUDP, CSysStatus *psysStat )
 @brief IoT_EPS system init method
 @param ntpUDP just for NTPClient init, this parameter is not kept
 @param psysStat a pointer on global variable sysStatus
 @return no return val

Start RTc DS3231 and nothing else @25/09/2020
*/
void CSystem::init( WiFiUDP &ntpUDP, CSysStatus *psysStat ){

    DEFDPROMPT( "CSystem::init" )

    String message;

    _psysStat = psysStat;
 
    delay(1000);//a try to correct the powerup pb
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite( LED_BUILTIN, LOW ); //warning D4 BP bleue plug
    delay(1000);
    digitalWrite( LED_BUILTIN, HIGH ); //warning D4 BP bleue plug
    pinMode(LED_BUILTIN, INPUT);
    
    
    DateTime now;

    DSPL();
    DSPL( dPrompt + F("Sketch start..."));
    pinMode( BP1, INPUT_PULLUP );


    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                    //
    /////////////////////////////////////////////////////////////////////////////

    _pTimeclient = new NTPClient(ntpUDP, NTPSERVER);
    _rtc.begin( _pTimeclient );
    _psysStat->rtcErr.err( _rtc.initErr );
    if (_rtc.lostPower()){
        DSPL( dPrompt + "une remise a l'heure est necessaire");
    }
    now = _rtc.now();
    message = dPrompt + F("DS3231 Start date : ");
    message += (String)now.day()+"/"+(String)now.month()+"/";
    message += (String)now.year()+" ";
    message += (String)now.hour()+":"+ (String)now.minute()+":";
    message += (String)now.second();      
    DSPL( message);

     
        
}


/**
 @fn void CSystem::timeServerCheck()
 @brief IoT_EPS Check time server access
 @return not param and no return value

Need to be called after Wifi init cause _psysStat->ntpEnabled set by Wifi link
*/
void CSystem::timeServerCheck(){
/////////////////////////////////////////////////////////////////////////////
    //  Time server check                                                     //
    /////////////////////////////////////////////////////////////////////////////
    // if ((wifi is on station mode connected))
    int timeZone = OFFSET_HEURE;
    DateTime NTPTime;
    DEFDPROMPT( "CSystem::timeServerCheck" )

    // String message = dPrompt;
    // message += "Addr of systat globally  0x";
    // message += String( (unsigned long)(&sysStatus) , HEX );
    // DSPL( message );
    // message = dPrompt;
    // message += "Addr of systat locally 0x";
    // message += String( (unsigned long)(&_sysStat) , HEX );
    // DSPL( message );

    // DSPL( dPrompt + "NTP enable ? globally " + String(sysStatus.ntpEnabled?"TRUE":"FALSE") );
    // DSPL( dPrompt + "NTP enable ? locally  " + String(_sysStat.ntpEnabled?"TRUE":"FALSE") );
    // CSysStatus *psysStat = &sysStatus;
    // Serial.print("sysStatus add : 0x");
    // Serial.println( (unsigned long)(psysStat), HEX );

    if( _psysStat->ntpEnabled){
        DSPL(dPrompt + "check started");
        _pTimeclient->begin();

        _psysStat->ntpErr.err( !_pTimeclient->forceUpdate() ) ;
        if ( !_psysStat->ntpErr.isErr() ){
            _pTimeclient->setTimeOffset( timeZone * SECPERHOURS );
            // setTime(  timeClient.getEpochTime() );
            NTPTime = DateTime( _pTimeclient->getEpochTime() );
            String sDate = "";
            sDate += (String)NTPTime.day() +"/"+(String)NTPTime.month()+"/"+(String)NTPTime.year()+" ";
            sDate += (String)NTPTime.hour()+":"+(String)NTPTime.minute()+":";
            sDate += (String)NTPTime.second();
            DSPL( dPrompt + "NTP Time : " + sDate );
            
            if (_rtc.lostPower()){
                RTC_DS3231::adjust( NTPTime );
                DSPL( dPrompt + F("DS3231 set to NTP time due to power lost.") );
                // CRtc::displayTime();
            }
            _cParam.write2Json( "ntpError", "OFF" );
        } else { 
            DSPL( dPrompt +"NTP ERROR");
            _cParam.write2Json( "ntpError", "ON" ); }
    }    
}