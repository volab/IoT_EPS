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

#include <FastCRC.h> // https://github.com/FrankBoesing/FastCRC

class HashPrint : public Print {
public:
    HashPrint() {
      _hash = _hasher.crc32(NULL, 0);
    }

    virtual size_t write(uint8_t c) {
        _hash = _hasher.crc32_upd(&c, 1);
    }

    uint32_t hash() const {
        return _hash;
    }

private:
    FastCRC32 _hasher;
    uint32_t _hash;
};


class CJsonIotEps{

    public:
        enum jsonFileIntegrity_t { KEEP_MASTER, KEEP_COPY1, TRY_MASTER, FILES_ERROR };

        bool init( ConfigParam *pcParam, CPowerPlug *plugs );

        jsonFileIntegrity_t checkJsonFilesIntegrity();
        void storeJson();
        bool loadJsonConfigParam();
        //bool loadJsonPlugParam(int plugNumber);
        

    private:
        //JsonObject* _json;
        
        ConfigParam *_pcParam;
        CPowerPlug *_pPlugs;
        
        jsonFileIntegrity_t _jsonFileIntegrity = FILES_ERROR;
        bool _fileLoaded = false;

        uint32_t _hashFile( File jsonFile );


};


#endif