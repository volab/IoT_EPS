/**
 @file cnano.h
 @author J.SORANZO
 @date 25/01/2019
 @copyright 2018 CC0
 @version git versionning
 @brief header file of the class CNano
*/

#ifndef CNANO_H
#define CNANO_H
#include <nanoI2CIOExpLib.h>

/**
* @class CNano CNano.h
* @brief The purpose of this class is to replace Cmcp class in the project...
 @detail We decide to replace MCP23017 digitalioexpander by nanoI2CIOExpander to provide access to 8 digitals I/O and 
 more important 6 analog inputs
 This class will be used by CPowerPlug as base class
*/
class CNano {
    public:
        static void init();
    protected:
        static CNanoI2CIOExpander _nano;
        static bool _initDone;       
};

#endif