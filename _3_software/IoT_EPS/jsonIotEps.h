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
        enum jsonFileIntegrity_t { KEEP_MASTER, KEEP_COPY, FILES_ERROR };

        bool init( ConfigParam *pcParam, CPowerPlug *plugs );

        void checkJsonFilesIntegrity();
        void storeJson();
        bool loadJsonConfigParam();
        //bool loadJsonPlugParam(int plugNumber);
        

    private:
        //JsonObject* _json;
        
        ConfigParam *_pcParam;
        CPowerPlug *_pPlugs;
        
        jsonFileIntegrity_t _jsonFileIntegrity = FILES_ERROR;
        //needed
        // ConfigParma *
        // CPlugs * to set theirs attributs


};


#endif