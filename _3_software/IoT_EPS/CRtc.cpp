/**
* @file CRtc.cpp
* @author J.SORANZO
* @date 25/12/2018
* @copyright 2018 CC0
* @version git versionning
* @brief Implementation file of CRtc 
*/

#include "CRtc.h"
#include "debugSerialPort.h"

bool CRtc::initErr = false;


/** 
@fn bool CRtc::begin( void )
@brief extend RTC_DS3231::begin to add error handling capability
@return 
*/
bool CRtc::begin( void ){
	RTC_DS3231::begin();
	Wire.beginTransmission(DS3231_ADDRESS);
    initErr = Wire.endTransmission();
	return initErr;
}


/** 
 @fn static void displayTime()
 @return no return value and no parameter
 
 This function work with debugSerial.h
 
 It displays time from DS3231
 
 This function could have used CEpsStrTime::displayUnixTime but it creat a depndency between this 2 class
*/
void CRtc::displayTime(){
	DEFDPROMPT( "DS3231 Time")
    DateTime now = RTC_DS3231::now();
    String sDate = "";
    sDate += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    sDate += (String)now.hour()+":"+(String)now.minute()+":";
    sDate += (String)now.second();
	DSPL( dPrompt + sDate );
	
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
	DEFDPROMPT( "CRtc::adjsut");
	DSP( dPrompt );
	DSPL( c );
	switch (sscanf( c, "%d/%d/%d %d:%d:%d", &j,&m,&a,&hh,&mm,&ss) ){
		case 6:
		// DSPL( dPrompt + "case 6");
		//DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
			RTC_DS3231::adjust( DateTime( a, m, j, hh, mm, ss) );
			DSPL("<O>");
			displayTime();
			break;
		default :
			DSPL( "<X>");
	}
}