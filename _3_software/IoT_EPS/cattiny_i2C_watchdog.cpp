/**
 @file cattiny_i2C_watchdog.cpp
 @author J.SORANZO
 @date 23/07/2019
 @copyright 2019 CC0
 @version git versionning
 @brief implementation file of the class CATtinyI2CWatchdog
*/

// #include "cattiny_i2C_watchdog.h"
#include "IoT_EPS.h"

void CATtinyI2CWatchdog::begin(){
    
}
void CATtinyI2CWatchdog::refresh(){
    
}
void CATtinyI2CWatchdog::setTimeout( byte val ){
    
}
void CATtinyI2CWatchdog::setSleepTime( byte val ){
    
}
void CATtinyI2CWatchdog::storeEeprom(){
    
}
void CATtinyI2CWatchdog::resetToFactiory(){
    
}
void CATtinyI2CWatchdog::setI2Cadd( byte add ){
    
}

/** 
 @fn bool CATtinyI2CWatchdog::isItTimeTo()
 @brief This metod to check if it is time to refresh watchdog... 
 @return true if it is time

It use the parameter WATCHDOGREFRESHPERIOD.

This method is intended to use in the loop to save bandwidth of I2C bus

Usage : if ( isItTimeToS() ) refresh();
*/
bool CATtinyI2CWatchdog::isItTimeTo(){
    if ( millis() - _prevMillis > WATCHDOGREFRESHPERIOD ){
        _prevMillis = millis();
        return true;
    } else return false;
}

//Private
int  CATtinyI2CWatchdog::_readRegister( int add ){
    
}
void CATtinyI2CWatchdog::_writeRegister( int add, int val){
    
}


CATtinyI2CWatchdog watchdog;