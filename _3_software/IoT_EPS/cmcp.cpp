/**
@ file cmcp.cpp
*/

#include "cmcp.h"

bool Cmcp::_initDone = false;
Adafruit_MCP23017 Cmcp::_mcp;

void Cmcp::init(){
    _initDone = true;
    _mcp.begin();
}