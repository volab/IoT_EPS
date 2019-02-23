/**
 @file cswitchnano.cpp
 @author J.SORANZO
 @date 22/02/2019
 @copyright 2018 CC0
 @version git versionning
 @brief implemnetation file of the class CSwitchNano
*/

#include "cswitchnano.h"

/** 
 @fn void CSwitchNano::begin( int pin, unsigned long samplePeriod, int mode )
 @brief To configure the switch parameters
 @param pin the pin number wher the switch is connected on the ARDUINO Nano I2C IO expander (D2 is 0)
 @param samplePeriod in milliseconds
 @param mode INPUT or INPUT_PULLUP
 @return no return value

*/
void CSwitchNano::begin( int pin, unsigned long samplePeriod, int mode ){
    _pin = pin;
    /** @todo test if mode == INPUT_PULLUP or INPUT only not output */
    _mode = mode;
    pinMode( pin, _mode );
    _samplePeriod = samplePeriod;
    _prevMillis = millis();
    _state = false;
    _prevState = false;
    if (!initOk) CNanoI2CIOExpander::begin();
}

/** 
 @fn void CSwitchNano::update
 @brief check if swith has changed...
 @return no return value and no parameter

use ( DEBOUNCE_COEFF * sample periode ) as debounce time
DEBOUNCE_COEFF is defined in cswitchnano.h
*/
void CSwitchNano::update(){
    int currentState;
    if ( millis() - _prevMillis >= _samplePeriod ){
        currentState = CNanoI2CIOExpander::digitalRead( _pin );
        _prevMillis = millis();
        if ( currentState != _prevState ) _lastDebounceTime = millis();

        if ( ( currentState != _state ) 
            && ( millis() - _lastDebounceTime > (DEBOUNCE_COEFF * _samplePeriod) ) ){
                //stable
            _state = currentState;            
        }
        _prevState = currentState;
    }   
}


