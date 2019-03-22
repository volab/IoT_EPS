/**
* @file configParam.cpp
* @author J.SORANZO
* @date dec, 2018
* @copyright 2018 CC0
* @version git versionning
* @brief Implementation file of the ConfigParam class

@details This class read from json file and store wifi mode and host name 
*/

#include "IoT_EPS.h"
// #include  "configParam.h"

/**
@fn bool ConfigParam::readFromJson()
@brief the methode to read the file config parameters...
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
        DSPL(dPrompt + F("File system mounted "));
        // if (SPIFFS.exists("/config.json")) {
        if (SPIFFS.exists( CONFIGFILENAME)) {
            //file exists, reading and loading
            DSPL(dPrompt + F("reading config file"));
            File configFile = SPIFFS.open( CONFIGFILENAME, "r");
            
            if (configFile) {
                DSPL( F("\tconfig file opened ") );
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    String s_IpAdd = json["general"]["IP"].as<String>();
                    _addIP.fromString( s_IpAdd );
                    _numberOfPlugs = json["general"]["numberOfPlugs"].as<String>().toInt();
                    _serverPort = json["general"]["Port"].as<String>().toInt();
                    _wifimode = json["general"]["wifimode"].as<String>();
                    _host = json["general"]["hostName"].as<String>();
                    _allLedsOnTime = json["general"]["allLedsOnTime"].as<String>().toInt();
                    _ledsGlobalLuminosity = \
                        json["general"]["ledsGlobalLuminosity"].as<String>().toInt();
                } else {
                    DEBUGPORT.println(dPrompt + F("Failed to load json config"));
                    return false;
                }
                configFile.close();
                return true;
            }
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += CONFIGFILENAME;
            DEBUGPORT.println(dPrompt);
            return false;
        }
    } else {
        DEBUGPORT.println( dPrompt + F("Failed to mount FS"));
        return false;
    }  
}

/** 
 @fn void ConfigParam::displayJson()
 @brief A function to display config json file...
 @return no return value and no parameter

This function is call by SerialCommand. It works with debugSerialPort
*/
void ConfigParam::displayJson(){
	DEFDPROMPT("Display json")
    if (SPIFFS.begin()) {
        if (SPIFFS.exists( CONFIGFILENAME)) {
            //file exists, reading and loading
            // DSPL(dPrompt + F("reading config file"));
            File configFile = SPIFFS.open( CONFIGFILENAME, "r");
            
            if (configFile) {
                // DSPL( F("\tconfig file opened ") );
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                json.prettyPrintTo(DEBUGPORT);
				DSPL( );
            }
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += CONFIGFILENAME;
            DSPL(dPrompt);
        }
    } else {
        DSPL( dPrompt + F("Failed to mount FS"));
    }  	
}

/** 
 @fn void ConfigParam::displayWifiMode()
 @brief A function to display cactual wifi mode...
 @return no return value and no parameter

This function is call by SerialCommand. It works with debugSerialPort
*/
void ConfigParam::displayWifiMode(){
	DEFDPROMPT("WIFI DATA")
	DSPL( dPrompt + F("Mode = ") + _wifimode );
	Credential wifiCred;
	wifiCred.begin();
    if ( wifiCred.ready){
        DSPL( dPrompt + F("SSID = ") + (String)wifiCred.getSsid() );
        DSPL( dPrompt + F("pass = ") + (String)wifiCred.getPass() );
    }
	
}

/** @todo doc. void ConfigParam::write2Json( String param, String value ) */
void ConfigParam::write2Json( String param, String value ){
    DEFDPROMPT( "write config param to jSon");
    File configFile = SPIFFS.open( CONFIGFILENAME , "r+");
    //DSPL( dPrompt);
    if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
            JsonObject& plug = json["general"]; 
            DSPL( dPrompt + " general : " + param + " = " + value);
            plug[param] = value; 
            configFile.seek(0, SeekSet);
            json.prettyPrintTo(configFile);
            // plug.prettyPrintTo(Serial);
            // DSPL();
        } else {
            DEBUGPORT.println(dPrompt + F("Failed to load json config"));
            // return false;
        }
        configFile.close();
        // return true;  
/** @todo perhaps add error handling as in readFromJson()*/        
    }     
}

/** @todo doc. void ConfigParam::chgSSID( String value ) */
void ConfigParam::chgSSID( String value ){
    DEFDPROMPT( "write credentials SSID");
    File configFile = SPIFFS.open( "/credentials.json" , "r+");
    //DSPL( dPrompt);
    if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
            DSPL( dPrompt + " written SSID = " + value);
            json["ssid"] = value; 
            configFile.seek(0, SeekSet);
            json.prettyPrintTo(configFile);
            // plug.prettyPrintTo(Serial);
            // DSPL();
        } else {
            DEBUGPORT.println(dPrompt + F("Failed to load json credentials"));
            // return false;
        }
        configFile.close();
        // return true;  
/** @todo perhaps add error handling as in readFromJson()*/        
    }     
}