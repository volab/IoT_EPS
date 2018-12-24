/**
* @file cEpsStrTime.cpp
* @author J.SORANZO
* @date
* @copyright 2018 CC0
* @version git versionning
* @brief Implementation file for CEpsStrTime class

*/

#include "IoT_EPS.h"
// #include "cEpsStrTime.h"
// #include "debugSerialPort.h"


/** 
@fn CEpsStrTime::CEpsStrTime( String val )
@brief second constructor that set the value, check validity and convert to seconds
@param val Time value as String
@return nothing of course
*/
CEpsStrTime::CEpsStrTime( String val ){
    setValue( val );
}

/** 
@fn void CEpsStrTime::setValue( String val )
@brief Set the string time value, check validity and convert to seconds
@param val the String time value
@return nothing
*/
void CEpsStrTime::setValue( String val ){
    _sValue = val;
    isValid = checkValidity();
}
    
/** 
@fn bool CEpsStrTime::checkValidity()
@brief Check Stirng time validity and convert in seconds
@return false if wrong input and _seconds = -1
*/
bool CEpsStrTime::checkValidity(){
    DEFDPROMPT( "CEpsStrTime::checkValidity")
    /** @todo take into account hh:mm mode */
    _seconds = -1;
    isValid = false;
    if ( _sValue == NOT_FOUND || _sValue == HTML_OFFDURATION_DEFAULT_VALUE ){
       return isValid;
    }
    int minutes = 0;
    int pos = _sValue.indexOf( TIME_STRING_SEPARATOR );
    if (pos != -1 ){        
        String sTmp = _sValue.substring( 0, pos );
        sTmp.trim();
        if (sTmp.length() > 3) return isValid; //max 3 digits
        /** @todo Warning if Minutes max value becomes > 999*/
        minutes = sTmp.toInt();
        DSPL( dPrompt + F("minutes : ") + sTmp );
        sTmp = _sValue.substring( pos +1 );
        sTmp.trim();
        _seconds = sTmp.toInt();
        if (sTmp.length() >  2 || _seconds > 59 || _seconds < 0 ){
            _seconds = -1;
            return isValid;
        }
        _seconds = minutes*60 + _seconds;
    } else _seconds = 60 * _sValue.toInt();
    DSPL( dPrompt + F("Secondes converties : ") + _seconds );
    if (_seconds > (_maxDuration*60) && _mode == MMMSS){
        _seconds = -1;
        return isValid;
    }
    isValid = true;
    return isValid;
}

/** 
@fn uint32_t  CEpsStrTime::computeNextTime()
@brief calculate next time to switch the plug

@return unix time form

In this first implementation for manual mode it takes no input param ,
but in future, it should take into account others mode
*/
uint32_t  CEpsStrTime::computeNextTime(){
    /** @todo take into account other modes*/
    DEFDPROMPT( "CEpsStrTime::computeNextTime" );
    RTC_DS3231 rtc;
    DateTime now;
    now = rtc.now();
    String page = "";
    displayUnixTime( now.unixtime() );
    uint32_t future = now.unixtime() + _seconds;
    page = "future = ";
    page += unixTime2String( future );
    DSPL( dPrompt + page );  
    return future;
}

/** 
@fn void CEpsStrTime::displayUnixTime()
@brief A function to dsiplay in debug consol the time in a human readable form
@param time2Display the inpput time in unix form
@return nothing
*/
void CEpsStrTime::displayUnixTime( uint32_t time2Display ){
    DEFDPROMPT( "disp. time : ");
    String sDate = unixTime2String( time2Display );
    DSPL( dPrompt + sDate );
}


/** 
@fn String CEpsStrTime::unixTime2String( uint32_t time2Display )
@brief Converts a unix time to a human readable string
@param time2Display must be in unix time 
@return String in french format jj/mm/aaaa hh:mm:ss
*/
String CEpsStrTime::unixTime2String( uint32_t time2Display ){
    DateTime now = DateTime( time2Display );
    String sDate = "";
    sDate += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    sDate += (String)now.hour()+":"+(String)now.minute()+":";
    sDate += (String)now.second();
    return sDate;    
} 
