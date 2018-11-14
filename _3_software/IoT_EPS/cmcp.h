/**
@ file cmcp.h
*/

#ifndef _CMCP_H
#define _CMCP_H
#include <Adafruit_MCP23017.h>

class Cmcp {
    public:
        static void init();
    protected:
        static Adafruit_MCP23017 _mcp;
        static bool _initDone;
};

#endif