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

extern DateTime rtc;

/** 
@fn CEpsStrTime::CEpsStrTime( String val )
@brief second constructor that set the valu and check validity
@param Time value as String
@return nothing of course
*/
CEpsStrTime::CEpsStrTime( String val ){
    setValue( val );
}

/** 
@fn _completeFunctionPrototype
@brief Set the string time value, checkvalidity and convert to seconds
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
        DSPL( dPrompt + "minutes : " + sTmp );
        sTmp = _sValue.substring( pos +1 );
        sTmp.trim();
        _seconds = sTmp.toInt();
        if (sTmp.length() >  2 || _seconds > 59 || _seconds < 0 ){
            _seconds = -1;
            return isValid;
        }
        _seconds = minutes*60 + _seconds;
    } else _seconds = 60 * _sValue.toInt();
    DSPL( dPrompt + "Secondes converties : " + _seconds );
    if (_seconds > (_maxDuration*60) && _mode == MMMSS){
        _seconds = -1;
        return isValid;
    }
    isValid = true;
    return isValid;
}


uint32_t  CEpsStrTime::computeNextTime(){
    /** @todo take into account other modes*/
    DEFDPROMPT( "CEpsStrTime::computeNextTime" );
    RTC_DS3231 rtc;
    DateTime now;
    DateTime future;
    now = rtc.now();
    String page = "";
    page += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    page += (String)now.hour()+":"+(String)now.minute()+":";
    page += (String)now.second();
    DSPL( dPrompt + page );
    future = DateTime( now.unixtime() + _seconds );
    page = "future = ";
    page += (String)future.day() +"/"+(String)future.month()+"/"+(String)future.year()+" ";
    page += (String)future.hour()+":"+(String)future.minute()+":";
    page += (String)future.second();
    DSPL( dPrompt + page );  
    _nextTimeToSwitch = future.unixtime();
    return _nextTimeToSwitch;
}


