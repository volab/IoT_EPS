/**
* @file cmcp.h
* @author J.SORANZO
* @date nov;=, 2018
* @copyright 2018 CC0
* @version git versionning
* @brief header file of the Cmcp class
@details Cmcp is a mother class to manange MCP23017 initialisation

This class is used by CPowerPlug as outputs and perhaps by buttons as inputs

MCP components sould be replaced by an ARDUINO nano used as an I2C io Expander with analog inputs
*/

#ifndef _CMCP_H
#define _CMCP_H
#include <Adafruit_MCP23017.h>
/**
* @class Cmcp cmcp.h
* @brief This class is design to handle the init of MCP23017 components
*/
class Cmcp {
    public:
        static void init();
    protected:
        static Adafruit_MCP23017 _mcp;
        static bool _initDone;
};

#endif