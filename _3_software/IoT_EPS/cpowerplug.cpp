/**
* @file cpowerplug.cpp
* @author J.Soranzo
* @date 10/11/2018
* @copyright see project readme
* @project Electrical Strip Power 
* @version 1.0
* @brief This class is the plug class
*/

#include "cpowerplug.h"
#include "debugSerialPort.h"




void CPowerPlug::begin( int pin , int onOffLedPin, int mode ){
    if (!_initDone) init();
    _pin = pin;
    _onOffLedPin = onOffLedPin;
    _mode = mode;
    _state = OFF;
    updateOutputs();
    _mcp.pinMode( _pin, OUTPUT );
    _mcp.pinMode( _onOffLedPin, OUTPUT );

}

void CPowerPlug::on(){
    if (_pin == 0){
        DSPL( dPrompt + F(" plug not started (call .begin().") );
    }
    _state = ON ;
    updateOutputs();
}

void CPowerPlug::off(){
    _state = OFF ;
    updateOutputs();
}

void CPowerPlug::toggle(){
    _state = !_state ;
    updateOutputs();
}

bool CPowerPlug::isItTimeToSwitch(){
    
    return (true); //to to change ths one ;-)
}

void CPowerPlug::updateOutputs(){
    _mcp.digitalWrite( _pin, _state );
    _mcp.digitalWrite( _onOffLedPin, _state );    
}



        