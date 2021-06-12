/**
 @file cattiny_i2C_watchdog.cpp
 @author J.SORANZO
 @date 23/07/2019
 @copyright 2019 CC0
 @version git versionning
 @brief implementation file of the class CATtinyI2CWatchdog
*/

//#include "cattiny_i2C_watchdog.h"

#include "IoT_EPS.h"

/** 
 @fn bool CATtinyI2CWatchdog::test()
 @brief This method test readability of the 4 PID value on ATtiny85 I2C watchdog ...
 @return true if there is no error

This method test only I2C accessibility to WD not the timer nor the reset founction.
*/
bool CATtinyI2CWatchdog::test(){
    //DEFDPROMPT( "wd test");
    _writeRegister( SETREADPOINTER, PID );
    int val0 = _readRegister( 0 );
    _writeRegister( SETREADPOINTER, PID+1 );
    int val1 = _readRegister( 0 );
    _writeRegister( SETREADPOINTER, PID+2 );
    int val2 = _readRegister( 0 );    
    _writeRegister( SETREADPOINTER, PID+3 );
    int val3 = _readRegister( 0 ); 
    if (   ( val0 == PIDVAL0 )
        && ( val1 == PIDVAL1 )
        && ( val2 == PIDVAL2 )
        && ( val3 == PIDVAL3 ) ) return true;
    else return false;
}

/** 
 @fn void CATtinyI2CWatchdog::begin()
 @brief Method to start watchdog
 @return no return value and no parameter

 This method start the Wire object (for I2C) and initialyze somme members.
 This method dont realy start the timer. A the begining the watchodog is in stoped state.
 To start the timer use setTimeout method.
*/
void CATtinyI2CWatchdog::begin(){
    Wire.begin();
    _prevMillis = millis();
    _refreshEnabled = true ;
    _refreshPeriod = WATCHDOGREFRESHPERIOD;
}

/** 
 @fn vvoid CATtinyI2CWatchdog::refresh()
 @brief As its name imply a method to refresh watchdog
 @return no return value and no parameter
*/
void CATtinyI2CWatchdog::refresh(){
    if ( _refreshEnabled ) _writeRegister( REFRESH, 0 );
}

/** 
 @fn void CATtinyI2CWatchdog::setTimeout( byte val )
 @brief Set the value of the timeout of the watchdog in seconds
 @param val Timeout in seconds
 @return no return value
*/
void CATtinyI2CWatchdog::setTimeout( byte val ){
    _writeRegister( TIMEOUT, val );
}

/** 
 @fn void CATtinyI2CWatchdog::setSleepTime( byte val )
 @brief set sleep time in seconds...
 @param val The sleep time value in seconds
 @return no return value

After a watchdog reset, during this time watchdog component wait.
It allow ESP8266 to restart...
*/
void CATtinyI2CWatchdog::setSleepTime( byte val ){
    _writeRegister( SLEEP, val );    
}

/** 
 @fn void CATtinyI2CWatchdog::storeEeprom()
 @brief A special method to store all parameter in the ATtiny85 watchdog EEPROM
 @return no return value and no parameter
*/
void CATtinyI2CWatchdog::storeEeprom(){
    _writeRegister( STORE, 0 );
}

/** 
 @fn void CATtinyI2CWatchdog::resetToFactory()
 @brief This method load parameters written in the source code
 @return no return value and no parameter
*/
void CATtinyI2CWatchdog::resetToFactory(){
    _writeRegister( RESTOREDEFAULT, 0 );
}

/** 
 @fn void CATtinyI2CWatchdog::setI2Cadd( byte add )
 @brief Set the I2C add (factory default = 0x26)...
 @param add The address
 @return no return value
 
Address of the component change dynamically and immediately
*/
void CATtinyI2CWatchdog::setI2Cadd( byte add ){
    _writeRegister( SETI2CADD, add );
    _tinyAdd = add;
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
    if ( millis() - _prevMillis > _refreshPeriod*1000 ){
        _prevMillis = millis();
        return true;
    } else return false;
}

//Private
int  CATtinyI2CWatchdog::_readRegister( int add ){
    Wire.beginTransmission( _tinyAdd );
    Wire.write((uint8_t)add);
    Wire.endTransmission();
    Wire.requestFrom( _tinyAdd, (uint8_t)1 );
    return (int)Wire.read();     
}
void CATtinyI2CWatchdog::_writeRegister( int add, int val){
    Wire.beginTransmission( _tinyAdd );
    Wire.write((uint8_t)add);
    Wire.write((uint8_t)val);
    Wire.endTransmission();    
}


CATtinyI2CWatchdog watchdog;