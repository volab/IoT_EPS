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


void CPowerPlug::begin( int pin , int onOffLedPin, int mode ){
    _pin = pin;
    _onOffLedPin = onOffLedPin;
    _mode = mode;
    _state = OFF;
    _mcp.digitalWrite( _pin, _state );
    _mcp.digitalWrite( _onOffLedPin, _state );
    _mcp.pinMode( _pin, OUTPUT );
    _mcp.pinMode( _onOffLedPin, OUTPUT );

}


bool CPowerPlug::_initDone = false;
Adafruit_MCP23017 CPowerPlug::_mcp;

void CPowerPlug::init(){
    _initDone = true;
    _mcp.begin();
}