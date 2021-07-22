/**
* @file jsonIotEps.h
* @author J.SORANZO
* @date 2021
* @copyright 2021 CC0
* @version 1.0
* @brief header file of the CJsonIotEps class
*/

#include "IoT_EPS.h"
//#pragma once
#ifndef CJSONIOTEPS_H
#define CJSONIOTEPS_H

class CJsonIotEps{

    public:

        bool init();
        void storeJson();
        bool loadJson();
        

    private:
        JsonObject* _json;
        //needed
        // ConfigParma *
        // CPlugs * to set theirs attributs

};


#endif