/**
* @file CRtc.cpp
* @author J.SORANZO
* @date 25/12/2018
* @copyright 2018 CC0
* @version git versionning
* @brief Implementation file of CRtc 
*/

#include "IoT_EPS.h"
#include "CRtc.h"
// #include "debugSerialPort.h"

bool CRtc::initErr = false;


NTPClient *CRtc::p_timeClient = nullptr;


/** 
@fn bool CRtc::begin( void )
@brief extend RTC_DS3231::begin to add error handling capability
@return 
*/
bool CRtc::begin( void ){
	RTC_DS3231::begin();
	Wire.beginTransmission(DS3231_ADDRESS);
    initErr = Wire.endTransmission();
    lastMillis = millis();
	return initErr;
}

bool CRtc::begin( NTPClient *p_tc ){
    
    p_timeClient = p_tc; //only used by displayTime and update methods
    begin();
    return true; // this line will be never reach -only here to supress a compil warn.
}

/** 
 @fn static void CRtc::displayTime()
 @return no return value and no parameter
 
 This function work with debugSerial.h
 
 It displays time from DS3231
 
 This function could have used CEpsStrTime::displayUnixTime but it creat a depndency between this 2 class
*/

void CRtc::displayTime(){ //static !
    unsigned long NTPTime;

	DEFDPROMPT( "DS3231 Time")
    DateTime now = RTC_DS3231::now();
    String sDate = "";
    sDate += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    sDate += (String)now.hour()+":"+(String)now.minute()+":";
    sDate += (String)now.second();
	DSPL( dPrompt + sDate );
    unsigned long RTCTime = RTC_DS3231::now().unixtime();
    DSPL( dPrompt + "unix local time : " + RTCTime );
    if ( p_timeClient != nullptr ){
        NTPTime = p_timeClient->getEpochTime();
        DSPL( dPrompt + "NTP time : " + String(p_timeClient->getEpochTime() ) );
        DSPL( dPrompt + "time error avant force update: " + String( abs(NTPTime-RTCTime) ) );    
    }

    if ( p_timeClient != nullptr ){
        sysStatus.ntpErr.err( !p_timeClient->forceUpdate() );
    } else {
        DSPL( dPrompt + "pointeur p_timeClient non initialisé ");
        return;
    }
    
    if ( sysStatus.ntpErr.isErr() ) return ;
    //unsigned long NTPTime = 0;
    NTPTime = p_timeClient->getEpochTime();
    DSPL( dPrompt + "NTP time : " + String(p_timeClient->getEpochTime() ) );
    DSPL( dPrompt + "time error : " + String( abs(NTPTime-RTCTime) ) );
    //DSPL( dPrompt + "Next time check" + String(millis() - lastMillis ) );
	
}

/** 
 @fn void CRtc::adjust( char *c )
 @brief a function to manualy adjust DS3231 when there is no WIFI at all
 @param c a c_string that containt JJ/MM/AAAA HH:MM:SS
 @return no return value

It converts the input c string into de DateTime class and call DS3231::adjust
*/
void CRtc::adjust( char *c ){
    int a;
	int j, m, hh, mm, ss;
	// DEFDPROMPT( "CRtc::adjsut");
	// DSP( dPrompt );
	// DSPL( c );
	switch (sscanf( c, "%d/%d/%d %d:%d:%d", &j,&m,&a,&hh,&mm,&ss) ){
		case 6:
			RTC_DS3231::adjust( DateTime( a, m, j, hh, mm, ss) );
			DSPL("<O>");
			displayTime();
			break;
		default :
			DSPL( "<X>");
	}
}

/** 
 @fn void CRtc::adjustH( char *c )
 @brief a function to manualy adjust DS3231 only HH:MM:SS when there is no WIFI at all
 @param c a c_string that containtHH:MM:SS
 @return no return value

It converts the input c string into de DateTime class and call DS3231::adjust
*/
void CRtc::adjustH( char *c ){
    DateTime now = RTC_DS3231::now();
	int hh, mm, ss;
	// DEFDPROMPT( "CRtc::adjsut");
	// DSP( dPrompt );
	// DSPL( c );
	switch (sscanf( c, "%d:%d:%d", &hh,&mm,&ss) ){
		case 3:
			RTC_DS3231::adjust( DateTime( now.year(), now.month(), now.day(), hh, mm, ss) );
			DSPL("<O>");
			// displayTime();
			break;
		default :
			DSPL( "<X>");
	}
}

/** 
 @fn void CRtc::update()
 @brief Check if it is time to check clock system versus NTP server and if it is do it
 @return no return value and no parameter

*/
void CRtc::update(){
    DEFDPROMPT( "DS3231 update");
    if (millis() - lastMillis < (RTC_UPDATE_PERIOD * 60 * 1000 ) ) return;
    DSPL( dPrompt + F("time to check clock system" ) );
    DateTime now = RTC_DS3231::now();
    String sDate = "";
    sDate += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    sDate += (String)now.hour()+":"+(String)now.minute()+":";
    sDate += (String)now.second();
	DSPL( dPrompt + sDate );
    
    if ( p_timeClient != nullptr ){
        sysStatus.ntpErr.err( !p_timeClient->forceUpdate() );
    } else {
        DSPL( dPrompt + "pointeur p_timeClient non initialisé ");
        return;
    }
    lastMillis = millis();
    if ( sysStatus.ntpErr.isErr() ) return ;
    //unsigned long NTPTime = 0;
    unsigned long NTPTime = p_timeClient->getEpochTime();
    unsigned long RTCTime = RTC_DS3231::now().unixtime();
    DSPL( dPrompt + F("Delta time = ") + String(abs( RTCTime - NTPTime )) );
    if ( abs( RTCTime - NTPTime ) < RTC_ALLOWED_TIME_ERROR ) return;
    // if ntp.unix time - rtc unix time < 15s return;
    RTC_DS3231::adjust( NTPTime );
    DSPL( dPrompt + F("DS3231 time updated" ) );
    /** @todo [OPTION] perhpas save a counter of updates */
    //read cpt from eeprom or file
    _updatesCpt++;
    //write cpt to eeprom or file
}
