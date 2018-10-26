

#include "credential.h"

/**
@class Credential credential.h
@brief Read credential from credential.json filebuf

Credentials.json sould be in the data directory of your sketch in the SPIFFS of the ESP8266
*/

/**
@fn Credential::Credential()
@brief only one constructor 
*/

Credential::Credential(){
    _ssid ="";
    _pass = "";
}

/**
@fn bool Credential::readFromJson()
@brief the methodes to read the filebuf
@return a booleen true on success  
*/
bool Credential::readFromJson(){
    DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounting FS..."));

    if (SPIFFS.begin()) {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounted file system"));
        if (SPIFFS.exists("/credentials.json")) {
            //file exists, reading and loading
            DEBUGPORT.println(F("<VoLAB reading wifi credit.> reading config file"));
            File configFile = SPIFFS.open("/credentials.json", "r");
            if (configFile) {
                DEBUGPORT.println( F("\topened config file") );
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    _ssid = json["ssid"].as<String>();
                    _pass = json["pass"].as<String>();
                } else {
                    DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to load json config"));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to open /credentials.json"));
            return false;
        }

    } else {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to mount FS"));
        return false;
    }
 

}