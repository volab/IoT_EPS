/**
 @file cswitchnano.h
 @author J.SORANZO
 @date 22/02/2019
 @copyright 2018 CC0
 @version git versionning
 @brief header file of the class CSwitchNano derived from CNanoI2CIOExpander
*/

#ifndef _CSWITCHNANO_H
#define _CSWITCHNANO_H
#include <nanoI2CIOExpLib.h>
#include <Arduino.h>

#define DEBOUNCE_COEFF 5
 
/**
* @class CSwitchNano cswitchnano.h
* @brief a Class to manage switch input with debounce connected to nanoI2CIOExpander
*/
class CSwitchNano : public CNanoI2CIOExpander{
    public:
        void update();
        void begin( int pin, unsigned long samplePeriod, int mode );
        int getState(){ return _state; }
        /** @todo [OPTION] add rise() and fall() method if needed. See for integration
        in CNanoI2CIOExpander*/
        int digitalRead(){ return CNanoI2CIOExpander::digitalRead( _pin ); }
    private:
        int _pin;
        int _samplePeriod;
        int _state;
        int _prevState;
        int _mode; //INPUT_PULLUP or INPUT
        unsigned long _prevMillis;
        unsigned long _lastDebounceTime;
    
};

#endif