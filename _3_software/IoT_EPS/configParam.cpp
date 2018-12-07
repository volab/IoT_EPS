

#include "IoT_EPS.h"
// #include  "configParam.h"

/**
@fn bool ConfigParam::readFromJson()
@brief the methode to read the file config parameters
@return a booleen true on success 

This code is greatly inspired from ARDUINO/ESP core "configFile" exemple

A very hard line is:

std::unique_ptr<char[]> buf(new char[size]);

It allow to creat a DynamicJsonBuffer without size  
*/
bool ConfigParam::readFromJson(){
    DEFDPROMPT("reading config param.")

    DSPL( dPrompt +F("Mounting FS..."));
    if (SPIFFS.begin()) {
        DEBUGPORT.println(dPrompt + F("File system mounted "));
        // if (SPIFFS.exists("/config.json")) {
        if (SPIFFS.exists("/config2.json")) {
            //file exists, reading and loading
            DEBUGPORT.println(dPrompt + F("reading config file"));
            File configFile = SPIFFS.open("/config2.json", "r");
            
            if (configFile) {
                DEBUGPORT.println( F("\tconfig file opened ") );
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    
                    _wifimode = json["general"]["wifimode"].as<String>();
                    // _yellowPlugState = json["yellowPlugState"].as<String>();
                    // _redPlugState = json["redPlugState"].as<String>();
                    // _greenPlugState = json["greenPlugState"].as<String>();
                    // _bluePlugState = json["bluePlugState"].as<String>();
                    _host = json["general"]["hostName"].as<String>();
                } else {
                    DEBUGPORT.println(dPrompt + F("Failed to load json config"));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            DEBUGPORT.println(dPrompt + F("Failed to open /config2.json"));
            return false;
        }

    } else {
        DEBUGPORT.println( dPrompt + F("Failed to mount FS"));
        return false;
    }
 
    
}
