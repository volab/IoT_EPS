/**
* @file Flasher.cpp
* @author J.SORANZO & Gilles Debussy
* @date 25/12/2018
* @copyright 2018 CC0
* @version 1.0
* @brief Implementation file of Flasher class 

Orginaly for VOR-O13 project and reused here.
*/
#include "Flasher.h"
#include <Arduino.h>
//#include "debugSerialPort.h"

/** 
 @fn void Flasher::begin( int pin, unsigned long ton, unsigned long toff)
 @brief to prepare Led Flashing
 @param pin the pin number where the LED is connected (anode connection and cathod to ground)
 @param ton time during the LED is switched on in milliseconds
 @param toff time during the LED is switched off in milliseconds
 @return no return value
 This function puts pin in output mode and xrite it to 0 (low state ie off)
*/
void Flasher::begin( int pin, unsigned long ton, unsigned long toff){
    _pin = pin;
    _ton = ton;
    _toff = toff;
    pinMode( _pin, OUTPUT);
    _ledState = 0;
    _previousMillis = 0;
    _changeStateCpt = 0;
    digitalWrite( _pin, _ledState );
    _flasherEnable = true;
}
/** 
@fn void Flasher::update()
@brief This function should be call periodicly
@return no param and no return value

Function check time with millis function and switch LED if necessary
*/
void Flasher::update(){
    if (_flasherEnable ){
        if ( (millis()-_previousMillis  > _ton) && (_ledState == 1) ){
            _ledState = 0;
            _previousMillis = millis();
            digitalWrite( _pin, _ledState );
            _changeStateCpt++;
        } else if ( (millis()-_previousMillis  > _toff) && (_ledState == 0) ){
            _ledState = 1 ;
            _previousMillis = millis();
            digitalWrite( _pin, _ledState );
            _changeStateCpt++;
        }  
    }
}
/** 
@fn void Flasher::stop()
@brief this function stop LED 
@return no param and no return value

Warning this function doesn't no prevent update() to work (except that the pin is in input mode)
I had _flasherEnable to prevent this behavior (8/3/2019)
*/
void Flasher::stop(){
    digitalWrite( _pin, 0 );
    _ledState = 0;
    pinMode( _pin, INPUT );
    _changeStateCpt = 0;
    _flasherEnable = false;
}