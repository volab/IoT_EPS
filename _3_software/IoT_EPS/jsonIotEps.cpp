/**
* @file cpowerplug.cpp
* @author J.Soranzo
* @date 10/11/2018
* @copyright see project readme 
* @version 1.0
* @brief This class is the plug class for Electrical Power Strip project
*/

#include "jsonIotEps.h"

bool CJsonIotEps::init( ConfigParam *pcParam, CPowerPlug *plugs){
    return true;
}


void CJsonIotEps::storeJson(){
    return;
}

bool CJsonIotEps::loadJsonConfigParam(){
    bool fileLoaded = false;

    int H0, H1;

    //compute HO hash of config4.json


    // compute H1 of config4copy1.json

    if ( H0 == H1 ){
        // master ok
        //load config4.json
    }
    return true;
}

void CJsonIotEps::checkJsonFilesIntegrity(){


    _jsonFileIntegrity = FILES_ERROR;
/*
    DEFDPROMPT("Check Json Integrity")

    DSPL( dPrompt +F("Mounting FS..."));
    ///SPIFFS Opning
    if (SPIFFS.begin()) {
        DSPL(dPrompt + F("File system mounted "));
        // if (SPIFFS.exists("/config.json")) {
        if (SPIFFS.exists( CONFIGFILENAME)) {
            //file exists, reading and loading
            DSPL(dPrompt + F("reading Json file master"));
            File configFile = SPIFFS.open( CONFIGFILENAME, "r");
            
            if (configFile) {
                DSPL( F("\tJson file opened ") );
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);
///Config file read
                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {

                }
            }
        }
    } */
}