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