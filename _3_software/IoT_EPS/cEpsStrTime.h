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
* @brief a class to hold and manipulate our different time values in String format...

Our time values are hDebut, hFin, dureeOn, dureeOff...

They can be H:M, H:MM, HH:M, HH:MM, MMM, MM, M, M:S, M:SS, MM:S, MM:SS, MMM:S, MMM:SS

Minutes files in MMM is limited to 300
*/
class CEpsStrTime //: public String
{
public:
    enum Mode_t { MMMSS = 1, HHMM, MMM };

    CEpsStrTime(){};
    CEpsStrTime( String val );
    CEpsStrTime( String val, Mode_t mode );
    bool isValid = false;
    void setValue( String val );
    void setMode( Mode_t mode ){ _mode = mode; }
    long getSeconds(){ return _seconds; } /**< @brief return time in seconds but warning
        it is not the full date in Unix form.*/
    void setMaxDuration( long val ){ _maxDuration = val; } 
    String getStringVal(){ return _sValue; }/**< @brief to get the String format of the time
    value for json write purposes*/
    
    uint32_t computeNextTime( uint8_t daysOfWeek = 0 );
    
    static void displayUnixTime( uint32_t time2Display ); /**< @brief for debug purpose*/
    static String unixTime2String( uint32_t time2Display );
 
private:   
    uint8_t nextCheckedDay( uint8_t days, uint8_t day );

private:
    Mode_t _mode = MMMSS ; 
    String _sValue;
    long _seconds;
    long _maxDuration = TIME_MAX_DURATION ; /**< @brief why ? Why to use a class member and not
    juste MACRO def ? */
    bool checkValidity( );
    
    
};

#endif