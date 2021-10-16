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

//#include <Esp.h>

void ConfigParam::begin( ){
    _wifimode = "" ; //default value
    _host= "";
    String ipad = "0.0.0.0";
    _addIP.fromString( ipad );
    _numberOfPlugs = 1;
    _serverPort = 0;
    // _allLedsOnTime = 30;
    _allLedsOnTime = -1;
    
    _ledsGlobalLuminosity = 1;   
    //ready = readFromJson();
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
    bool returnVal;
    DEFDPROMPT("reading config param.")

    DSPL( dPrompt +F("Mounting FS..."));
    ///SPIFFS Opning
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
///Config file read
                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    ///Parameters updated with those of the config file read
                    String s_IpAdd = json["general"]["softAP_IP"].as<String>();
                    _addIP.fromString( s_IpAdd );
                    _numberOfPlugs = json["general"]["numberOfPlugs"].as<String>().toInt();
                    _serverPort = json["general"]["softAP_port"].as<String>().toInt();
                    String startInAPMode = json["general"]["startInAPMode"].as<String>();
                    if ( startInAPMode == "OFF") _wifimode = "Station";
                    else _wifimode = "softAP";
                    String s_FirstBootTmp = json["general"]["firstBoot"].as<String>();
                    //possible value are "ON" "OFF" or "TRYSTA"
                    if ( s_FirstBootTmp == "ON") _firstBoot = YES;
                    else if ( s_FirstBootTmp == "OFF" )_firstBoot = NO;
                    else if ( s_FirstBootTmp == "TRYSTA" )_firstBoot = TRY;
                    else _firstBoot = YES; // default value
                    _STAmaxWifiConnectionRetries = \
                            json["general"]["STAmaxWifiConnectionRetry"].as<String>().toInt();
                    _host = json["general"]["hostName"].as<String>();
                    _allLedsOnTime = json["general"]["allLedsOnTime"].as<String>().toInt();
                    _ledsGlobalLuminosity = \
                        json["general"]["ledsGlobalLuminosity"].as<String>().toInt();
                    _powerLedEconomyMode = \
                            (json["general"]["powerLedEconomyMode"].as<String>() == "ON");
                    _macAdd = json["general"]["macAdd"].as<String>();
                    _softAPMacAdd = json["general"]["softAP_macAdd"].as<String>();
                    _DHCPMode = ( json["general"]["dhcp_mode"].as<String>() == "ON" );
                    String s_tmpIP = json["general"]["staIP"].as<String>();
                    _staIP.fromString( s_tmpIP );
                    s_tmpIP = json["general"]["staGateway"].as<String>();
                    _staGateway.fromString( s_tmpIP );
                    if (_firstBoot == YES ) _wifimode = "softAP";
                    returnVal = true;
                } else {
                    DEBUGPORT.println(dPrompt + F("Failed to load json config"));     
                    returnVal = false;
                }
                ///Config file closing
                configFile.close();
            } else { returnVal = false; } // not realy the bug but... configFile ko
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += CONFIGFILENAME;
            DEBUGPORT.println(dPrompt);
            returnVal = false;
        }
    } else { //normaly do not arrive cause there is a file system check before - 18/05/2019
        DEBUGPORT.println( dPrompt + F("Failed to mount FS"));
        returnVal = false;
    }  
    return returnVal; //to supresse return value warning 26/06/2021
}

/** 
 @fn String ConfigParam::readFromJsonParam( String parameter, String section )
 @brief a static function to retrieve one parameter from json
 @param parameter the parameter to retrive
 @param section the section from the parameter should to be retrived 
 @return a string tha containe the parameter or empty string if not found


*/
String ConfigParam::readFromJsonParam( String parameter, String section ){
    DEFDPROMPT("reading one parameter from config")
    String paramVal = "";
    // DSPL( dPrompt +F("Mounting FS..."));
    if (SPIFFS.begin()) {
        // DSPL(dPrompt + F("File system mounted "));
        // if (SPIFFS.exists("/config.json")) {
        if (SPIFFS.exists( CONFIGFILENAME)) {
            //file exists, reading and loading
            DSPL(dPrompt + F("reading config file"));
            File configFile = SPIFFS.open( CONFIGFILENAME, "r");
            // File configFile = SPIFFS.open( CONFIGFILENAME_COPY1, "r");
            DSPL( dPrompt + CONFIGFILENAME );
            // DSPL( dPrompt + CONFIGFILENAME_COPY1 );
            if (configFile) {
                // DSPL( F("\tconfig file opened ") );
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);
                // std::unique_ptr<char[]> buf(new char[500]);
                
                // configFile.readBytes(buf.get(), 500);
                configFile.readBytes(buf.get(), size);
                // for (int i = 0; i < 500; i++){Serial.write(buf[i]); }
                DSPL( dPrompt + "Free mem : " + String( ESP.getFreeHeap() ));
                DSPL();
                // DynamicJsonBuffer jsonBuffer;
                // JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.prettyPrintTo(DEBUGPORT); DSPL();
                // if (json.success()) {
                //     DSPL( dPrompt + "Param : " + parameter + " from " + section );
                //     paramVal = json[section][parameter].as<String>();
                // } else {
                //     DEBUGPORT.println(dPrompt + F("Failed to load json config"));
                // }
                configFile.close();
                DSPL( dPrompt + "Free mem after close: " + String( ESP.getFreeHeap() ));
            }
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += CONFIGFILENAME;
            DSPL(dPrompt);
        }
    } else { //normaly do not arrive cause there is a file system check before - 18/05/2019
        DSPL( dPrompt + F("Failed to mount FS"));
    }
    return paramVal;
}

/** 
 @fn void ConfigParam::displayJson()
 @brief A function to display config json file...
 @return no return value and no parameter

This function is call by SerialCommand. It works with debugSerialPort
*/
void ConfigParam::displayJson( String file ){
	DEFDPROMPT("Display json")
    DSPL( dPrompt + F("Json file: ") + file );
    if (SPIFFS.begin()) {
        // if (SPIFFS.exists( CONFIGFILENAME)) {
        if (SPIFFS.exists( file)) {
            //file exists, reading and loading
            // DSPL(dPrompt + F("reading config file"));
            // File configFile = SPIFFS.open( CONFIGFILENAME, "r");
            File configFile = SPIFFS.open( file, "r");
            DSPL( dPrompt + "Free mem : " + String( ESP.getFreeHeap() ));
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
            dPrompt += file;
            DSPL(dPrompt);
        }
    } else {
        DSPL( dPrompt + F("Failed to mount FS"));
    }  	
}

/** 
 @fn void ConfigParam::displayJsonGeneral()
 @brief A function to display config json file general part only...
 @return no return value and no parameter

This function is call by SerialCommand. It works with debugSerialPort
*/
void ConfigParam::displayJsonGeneral(){
	DEFDPROMPT("Display json General part")
    if (SPIFFS.begin()) {
        String file = CONFIGFILENAME;
        if (SPIFFS.exists( file)) {
            File configFile = SPIFFS.open( file, "r");
            if (configFile) {
                size_t size = configFile.size();
                DSPL( dPrompt + "Config file size : " + (String)size ) ;
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                JsonObject& jsonGen = json["general"];
                jsonGen.prettyPrintTo(DEBUGPORT);
				DSPL( );
            }
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += file;
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
	DSPL( dPrompt + F("Expected mode = ") + _wifimode );
    String s_mode;
//WIFI_AP, WIFI_STA, WIFI_AP_STA or WIFI_OFF
    switch (WiFi.getMode()){
        case WIFI_AP:
            s_mode = F("AP");
            break;
        case WIFI_STA:
            s_mode = F("Station");
            break;
        case WIFI_AP_STA:
            s_mode = F("Sation and AP");
            break;
        case WIFI_OFF:
            s_mode = F("WiFi off");
            break;
        default : 
            s_mode = F("Unknow");        
    };
    DSPL( dPrompt + F("Returned by WiFi.getMode() = ") + s_mode );
	Credential wifiCred;
	wifiCred.begin();
    if ( wifiCred.ready){
        DSPL( dPrompt + F("SSID for Station mode = ") + (String)wifiCred.getSsid() );
        DSPL( dPrompt + F("pass for Station mode = ") + (String)wifiCred.getPass() );
        DSPL( dPrompt + F("Sation MAC add = ") + WiFi.macAddress() );
        DSPL( dPrompt + F("SSID for sofAP mode = ") + (String)wifiCred.getSoftApSsid() );
        DSPL( dPrompt + F("pass for sofAP mode = ") + (String)wifiCred.getSoftApPass() ); 
        DSPL( dPrompt + F("Acces Point MAC add = ") + WiFi.softAPmacAddress() );
        DSPL( dPrompt + F("Host name that dosen't work on Android = ") + getHostName() );
    } else DSPL(dPrompt + F("Credentials error") );
	
}

/** 
 @fn void ConfigParam::write2Json( String param, String value, String file )
 @brief write to a json file one parameter only...
 @param param parameter name (case sensitive)
 @param value the value of the parameter to be written
 @param file complete file path (don't forget / in front of it)
 @return no return value

The file nema parameter has a default valeur (see in configParam.h)
*/
void ConfigParam::write2Json( String param, String value, String file ){
    DEFDPROMPT( "write  param to jSon file (obsolete)");

    _jsonWriteRequest = true;
    /** done [NECESSARY] remove below code*/

    // File configFile = SPIFFS.open( CONFIGFILENAME , "r");
    // File configFile = SPIFFS.open( file , "r");
    // DSPL( dPrompt + file);
    // if (configFile) {
    //     size_t size = configFile.size();
    //     // Allocate a buffer to store contents of the file.
    //     std::unique_ptr<char[]> buf(new char[size]);
    //     configFile.readBytes(buf.get(), size);
    //     DynamicJsonBuffer jsonBuffer;
    //     JsonObject& json = jsonBuffer.parseObject(buf.get());
    //     if (json.success()) {
    //         JsonObject& plug = json["general"]; // main level
    //         DSPL( dPrompt + " general : " + param + " = " + value);
    //         plug[param] = value; 
    //         configFile.close();
    //         configFile = SPIFFS.open( file , "w");
    //         json.printTo(configFile);
    //     } else {
    //         DEBUGPORT.println(dPrompt + F("Failed to load json config"));
    //     }
    //     configFile.close();
    // }     
}

/** 
 @fn void ConfigParam::chgSSID( String value, String key  )
 @brief a short static function call in SerialCommand.cpp to change Wifi SSID
 @param value : password as a String
 @param key : the key with a defult value see in .h file
 @return no return
*/
void ConfigParam::chgSSID(  String value, String key ){
    DEFDPROMPT( "write credentials SSID");
    // _write2CredJson( "ssid", value );  
    write2Json( key, value, "/credentials.json" );  
}

/** 
 @fn void ConfigParam::chgWifiPass( String value, String key  )
 @brief a short static function call in SerialCommand.cpp to change Wifi Pass
 @param value : password as a String
 @param key : the key with a defult value see in .h file
 @return no return
*/
void ConfigParam::chgWifiPass(  String value, String key ){
    DEFDPROMPT( "write credentials password");
    // _write2CredJson( "pass", value );
    write2Json( key, value, "/credentials.json" );
    //dosen't work because there is on level
    // more "general" in the config and not in the credential file
    //i add a general level in credentials file ;-)
}

/** 
 @fn void ConfigParam::creatDefaultJson()
 @brief copy defconfig.json to config4.json for repairing purpose
 @return no return value and no parameter

This special method is designed to try to repair a corrupted config4.json file.
It could be activate by PB1 @ startup time
*/
void ConfigParam::creatDefaultJson(){
    DEFDPROMPT( "creat default config json" );
   
    if ( SPIFFS.begin() ){
        if ( SPIFFS.exists( DEFCONFIGFILENAME )){
            DSPL( dPrompt + DEFCONFIGFILENAME + F(" exist...") );
            if ( SPIFFS.exists( CONFIGFILENAME ) ){
                DSPL( dPrompt + F("Deleting existing ") + CONFIGFILENAME );
            }
            //SPIFFS.copy(); // doesn't exit !
            File src = SPIFFS.open( DEFCONFIGFILENAME , "r" );
            File dest = SPIFFS.open( CONFIGFILENAME , "w" );
            for (int i = 0; i < src.size(); i++){
                uint8_t c = src.read();
                dest.write(c);
            }
            src.close();
            dest.close();
            DSPL( dPrompt + "file is copied");
        }
    }
    
}

