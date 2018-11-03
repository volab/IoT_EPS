

#include "IoT_EPS.h"
// #include  "configParam.h"

/**
@fn bool ConfigParam::readFromJson()
@brief the methode to read the file config parameters
@return a booleen true on success  
*/
bool ConfigParam::readFromJson(){
    DEBUGPORT.println( d_prompt +F(" mounting FS..."));
    if (SPIFFS.begin()) {
        DEBUGPORT.println(d_prompt + F(" file system mounted "));
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            DEBUGPORT.println(d_prompt + F(" reading config file"));
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                DEBUGPORT.println( F("\tconfig file opened ") );
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    _wifimode = json["wifimode"].as<String>();
                    _yellowPlugState = json["yellowPlugState"].as<String>();
                    _redPlugState = json["redPlugState"].as<String>();
                    _greenPlugState = json["greenPlugState"].as<String>();
                    _bluePlugState = json["bluePlugState"].as<String>();
                    _host = json["hostName"].as<String>();
                } else {
                    DEBUGPORT.println(d_prompt + F(" failed to load json config"));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            DEBUGPORT.println(d_prompt + F(" failed to open /config.json"));
            return false;
        }

    } else {
        DEBUGPORT.println( d_prompt + F(" failed to mount FS"));
        return false;
    }
 
    
}
