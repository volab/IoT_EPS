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
    if ( _sValue == NOT_FOUND || _sValue == HTML_OFFDURATION_DEFAULT_VALUE ){
       return false;
    }
    int minutes = 0;
    int pos = _sValue.indexOf( TIME_STRING_SEPARATOR );
    if (pos != -1 ){        
        minutes = _sValue.substring( 0, pos -1 ).toInt();
        _seconds = minutes*60 + _sValue.substring( pos +1 ).toInt();
    } else _seconds = 60 * _sValue.toInt();
    DSPL( dPrompt + "Secondes converties : " + _seconds );
    if (_seconds > _maxDuration && _mode == MMMSS){
        _seconds = -1;
        return false;
    }
    return true;
}