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



/**
* @class CEpsStrTime cEpsStrTime.h
* @brief a class to hold and manipulate our different time values in String format

Our time values are hDebut, hFin, dureeOn, dureeOff...

They can be H:M, H:MM, HH:M, HH:MM, MMM, MM, M, M:S, M:SS, MM:S, MM:SS, MMM:S, MMM:SS

Minutes files in MMM is limited to 300
*/
class CEpsStrTime : public String
{
public:
	
    CEpsStrTime();
    CEpsStrTime( String val ){ _sValue = val; }
    bool checkValidity();
    long getSeconds(){ return _seconds; };
    String getStringVal(){ return _sValue; }/**< @brief to get the String format of the time
    value for json write purposes*/

private:
	
    String _sValue;
    long _seconds;    
    
};

#endif