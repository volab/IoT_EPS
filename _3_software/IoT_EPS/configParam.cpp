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

void ConfigParam::begin(){
    _wifimode = "softAP" ; //default value
    _host= "PowerStrip";
    String ipad = DEFAULTIPADD;
    _addIP.fromString( ipad );
    _numberOfPlugs = 4;
    _serverPort = 80;
    // _allLedsOnTime = 30;
    _allLedsOnTime = -1;
    
    _ledsGlobalLuminosity = 5;    
    ready = readFromJson();
}

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
                    String s_IpAdd = json["general"]["softAP_IP"].as<String>();
                    _addIP.fromString( s_IpAdd );
                    _numberOfPlugs = json["general"]["numberOfPlugs"].as<String>().toInt();
                    _serverPort = json["general"]["softAP_port"].as<String>().toInt();
                    // _wifimode = json["general"]["wifimode"].as<String>();
                    String startInAPMode = json["general"]["startInAPMode"].as<String>();
                    if ( startInAPMode == "OFF") _wifimode = "Station";
                    else _wifimode = "softAP";
                    _firstBoot = (json["general"]["firstBoot"].as<String>() == "ON");
                    _host = json["general"]["hostName"].as<String>();
                    _allLedsOnTime = json["general"]["allLedsOnTime"].as<String>().toInt();
                    _ledsGlobalLuminosity = \
                        json["general"]["ledsGlobalLuminosity"].as<String>().toInt();
                    _powerLedEconomyMode = (json["general"]["powerLedEconomyMode"].as<String>() == "ON");
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
        DSPL( dPrompt + F("SSID for Station mode = ") + (String)wifiCred.getSsid() );
        DSPL( dPrompt + F("pass for Station mode = ") + (String)wifiCred.getPass() );
        DSPL( dPrompt + F("Sation MAC add = ") + WiFi.macAddress() );
        DSPL( dPrompt + F("SSID for sofAP mode = ") + (String)wifiCred.getSoftApSsid() );
        DSPL( dPrompt + F("pass for sofAP mode = ") + (String)wifiCred.getSoftApPass() ); 
        DSPL( dPrompt + F("Acces Point MAC add = ") + WiFi.softAPmacAddress() );
    } else DSPL(dPrompt + F("Credentials error") );
	
}

/** @todo doc. void ConfigParam::write2Json( String param, String value ) */
void ConfigParam::write2Json( String param, String value  ){
    DEFDPROMPT( "write config param to jSon");
    File configFile = SPIFFS.open( CONFIGFILENAME , "r");
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
            // configFile.seek(0, SeekSet);
            configFile.close();
            configFile = SPIFFS.open( CONFIGFILENAME , "w");
            json.printTo(configFile);
            // plug.prettyPrintTo(Serial);
            // DSPL();
        } else {
            DEBUGPORT.println(dPrompt + F("Failed to load json config"));
            // return false;
        }
        configFile.close();
        // return true;  
/** @todo perhaps add error handling as in readFromJson() */ 
      
    }     
}

/** 
 @fn void ConfigParam::chgSSID( String value )
 @brief a short static function call in SerialCommand.cpp to change Wifi SSID
 @param value : password as a String
 @return no return
*/
void ConfigParam::chgSSID( String value ){
    DEFDPROMPT( "write credentials SSID");
    _write2CredJson( "ssid", value );  
}

/** 
 @fn void ConfigParam::chgWifiPass( String value )
 @brief a short static function call in SerialCommand.cpp to change Wifi Pass
 @param value : password as a String
 @return no return
*/
void ConfigParam::chgWifiPass( String value ){
    DEFDPROMPT( "write credentials password");
    _write2CredJson( "pass", value );
}

void ConfigParam::_write2CredJson( String param, String value ){
    DEFDPROMPT( "write to credentials");
    File configFile = SPIFFS.open( "/credentials.json" , "r");
    // File configFile = SPIFFS.open( file.c_str() , "r");
    //DSPL( dPrompt);
    if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
            DSPL( dPrompt + " written WiFi "+ param +" : " + value);
            json[param] = value; 
            // configFile.seek(0, SeekSet);
            configFile.close();
            configFile = SPIFFS.open( "/credentials.json" , "w");
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