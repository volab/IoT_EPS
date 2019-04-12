

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
    DEFDPROMPT("reading credentials")
    DSPL(dPrompt + F("mounting FS..."));

    if (SPIFFS.begin()) {
        DSPL(dPrompt + F("File system mounted"));
        if (SPIFFS.exists("/credentials.json")) {
            //file exists, reading and loading
            DSPL(dPrompt + F("Reading credit. file"));
            File configFile = SPIFFS.open("/credentials.json", "r");
            if (configFile) {
                DSPL( F("\tCredit. file is opened") );
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
                    _softApSsid = json["softApSsid"].as<String>();
                    _softApPass = json["sodtApPass"].as<String>();
                } else {
                    DSPL(dPrompt + F("Failed to parse json credentials file."));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            DSPL(dPrompt + F(" failed to open /credentials.json"));
            return false;
        }

    } else {
        DSPL(dPrompt + F(" failed to mount FS"));
        return false;
    }
 

}