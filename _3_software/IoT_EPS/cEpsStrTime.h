/**
* @file cEpsStrTime.h
* @author J.SORANZO
* @date 20/12/2018
* @copyright 2018 CC0
* @version git
* @brief Header file for CEpsStrTime class
*/

#ifndef CEPSSTRTIME_H
#define CEPSSTRTIME_H

#include <Arduino.h>

#define TIME_MAX_DURATION 300



/**
* @class CEpsStrTime cEpsStrTime.h
* @brief a class to hold and manipulate our different time values in String format

Our time values are hDebut, hFin, dureeOn, dureeOff...

They can be H:M, H:MM, HH:M, HH:MM, MMM, MM, M, M:S, M:SS, MM:S, MM:SS, MMM:S, MMM:SS

Minutes files in MMM is limited to 300
*/
class CEpsStrTime //: public String
{
public:
    enum Mode_t { MMMSS = 1, HHMM };

    CEpsStrTime(){};
    CEpsStrTime( String val );
    bool isValid = false;
    void setValue( String val );
    void setMode( Mode_t mode ){ _mode = mode; }
    long getSeconds(){ return _seconds; }
    void setMaxDuration( long val ){ _maxDuration = val; } 
    String getStringVal(){ return _sValue; }/**< @brief to get the String format of the time
    value for json write purposes*/
    
    uint32_t computeNextTime();
    /** @todo write a method to display _nextTimeToSwitch in human readable form*/

private:
	
    Mode_t _mode = MMMSS ; 
    String _sValue;
    long _seconds;
    long _maxDuration = TIME_MAX_DURATION ;
    bool checkValidity();
    uint32_t _nextTimeToSwitch;
};

#endif