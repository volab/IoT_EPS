/**
* @file cmcp.cpp
* @author J.SORANZO
* @date nov;=, 2018
* @copyright 2018 CC0
* @version git versionning
* @brief implementation file of the Cmcp class
@details Cmcp is a mother class to manange MCP23017 initialisation

This class is used by CPowerPlug as outputs and perhaps by buttons as inputs

MCP components sould be replaced by an ARDUINO nano used as an I2C io Expander with analog inputs
*/

#include "cmcp.h"

bool Cmcp::_initDone = false;
Adafruit_MCP23017 Cmcp::_mcp;

void Cmcp::init(){
    _initDone = true;
    _mcp.begin();
}