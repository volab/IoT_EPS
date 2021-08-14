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
    _pcParam = pcParam;
    _pPlugs = plugs;
    return true;
}


void CJsonIotEps::storeJson(){
    return;
}



/**
 @fn bool CJsonIotEps::loadJsonConfigParam()
 @brief Check the integrity of json file
 @return a booleen true if all is ok.

 Need the integrity is checked before use it
*/
bool CJsonIotEps::loadJsonConfigParam(){
    //bool _fileLoaded = false;
    DEFDPROMPT("CJson Config Param Loading")
    bool returnVal = false;

    if ( _jsonFileIntegrity != FILES_ERROR ){
        File file = SPIFFS.open( _fileNameToLoad, "r");
        if (file){
            size_t size = file.size();
            std::unique_ptr<char[]> buf(new char[size]);
            file.readBytes(buf.get(), size);
            file.close();
            DynamicJsonBuffer jsonBuffer;
            JsonObject& json = jsonBuffer.parseObject(buf.get());
            if (json.success()){
                String s_IpAdd = json["general"]["softAP_IP"].as<String>();
                _pcParam->_addIP.fromString( s_IpAdd );
                _pcParam->_numberOfPlugs = json["general"]["numberOfPlugs"].as<String>().toInt();
                _pcParam->_serverPort = json["general"]["softAP_port"].as<String>().toInt();
                String startInAPMode = json["general"]["startInAPMode"].as<String>();
                if ( startInAPMode == "OFF") _pcParam->_wifimode = "Station";
                else _pcParam->_wifimode = "softAP";
                String s_FirstBootTmp = json["general"]["firstBoot"].as<String>();
                //possible value are "ON" "OFF" or "TRYSTA"
                if ( s_FirstBootTmp == "ON") _pcParam->_firstBoot = ConfigParam::YES;
                else if ( s_FirstBootTmp == "OFF" ) _pcParam->_firstBoot = ConfigParam::NO;
                else if ( s_FirstBootTmp == "TRYSTA" ) _pcParam->_firstBoot = ConfigParam::TRY;
                else _pcParam->_firstBoot = ConfigParam::YES; // default value
                _pcParam->_STAmaxWifiConnectionRetries = \
                        json["general"]["STAmaxWifiConnectionRetry"].as<String>().toInt();
                _pcParam->_host = json["general"]["hostName"].as<String>();
                _pcParam->_allLedsOnTime = json["general"]["allLedsOnTime"].as<String>().toInt();
                _pcParam->_ledsGlobalLuminosity = \
                    json["general"]["ledsGlobalLuminosity"].as<String>().toInt();
                _pcParam->_powerLedEconomyMode = \
                        (json["general"]["powerLedEconomyMode"].as<String>() == "ON");
                _pcParam->_macAdd = json["general"]["macAdd"].as<String>();
                _pcParam->_softAPMacAdd = json["general"]["softAP_macAdd"].as<String>();
                _pcParam->_DHCPMode = ( json["general"]["dhcp_mode"].as<String>() == "ON" );
                String s_tmpIP = json["general"]["staIP"].as<String>();
                _pcParam->_staIP.fromString( s_tmpIP );
                s_tmpIP = json["general"]["staGateway"].as<String>();
                _pcParam->_staGateway.fromString( s_tmpIP );
                if (_pcParam->_firstBoot == ConfigParam::YES ) _pcParam->_wifimode = "softAP";
                _pcParam->_emplacement = json["general"]["emplacement"].as<String>();
                returnVal = true;
                /** @todo [NECESSARY] clear usage of NTP error */ 
            } else {
                DSPL(dPrompt + F("Failed to load json config"));     
                returnVal = false;
            }  
        }
        DSPL( dPrompt + F("Config param loaded : "));
        DSPL( dPrompt + F(" - emplacement : ") + _pcParam->_emplacement );
        DSPL( dPrompt + F(" - Number of plugs : ") + String(_pcParam->_numberOfPlugs) );
        DSPL( dPrompt + F(" - All Led On Time : ") + String(_pcParam->_allLedsOnTime)  );
        DSPL( dPrompt + F(" - LEDs Global illum : ") + String(_pcParam->_ledsGlobalLuminosity) );
        DSPL( dPrompt + F(" - Power Led economy mode : ") +  _pcParam->_powerLedEconomyMode );
        String firstBoot_s;
        switch (_pcParam->_firstBoot){
            case ConfigParam::YES:
                firstBoot_s = "YES";
                break;
            case ConfigParam::NO:
                firstBoot_s = "NO";
                break;
            case ConfigParam::TRY:
                firstBoot_s = "TRY";
                break;            
            default:
                break;
        }
        DSPL( dPrompt + F(" - First boot : ") +  firstBoot_s );
        DSPL( dPrompt + F(" - Host name : ") +  _pcParam->_host );
        DSPL( dPrompt + F(" - Strat in AP mode (_wifiMode) : ") + _pcParam->_wifimode  );
        DSP( dPrompt + F(" - Soft AP IP add (_addIP) : " )); _pcParam->_addIP.printTo(Serial);DSPL();
        DSPL( dPrompt + F(" - Soft AP port (_serverPort): ") + String(_pcParam->_serverPort)  );
        DSPL( dPrompt + F(" - DHCP mode  : ") + (_pcParam->_DHCPMode?"ON":"OFF")  );
        DSP( dPrompt + F(" - Station IP address  : ") );_pcParam->_staIP.printTo(Serial);DSPL();
        DSP( dPrompt + F(" - Station gateway IP address  : ") ); _pcParam->_staGateway.printTo(Serial);DSPL();
        DSPL( dPrompt + F(" - MAC address  : ") +  _pcParam->_macAdd  );
        DSPL( dPrompt + F(" - Soft AP MAC address  : ") + _pcParam->_softAPMacAdd  );
        DSPL( dPrompt + F(" - MAX Wifi connexion retry  : ") + String(_pcParam->_STAmaxWifiConnectionRetries)  );
        //DSPL( dPrompt + F(" - TNP Error  : ") +   ); //CSysSattus::ntpErr
    }
 
    return returnVal;
}
/**
 @fn CJsonIotEps::jsonFileIntegrity_t CJsonIotEps::checkJsonFilesIntegrity()
 @brief Check the integrity of json file
 @return jsonFileIntegrity Value.
*/
CJsonIotEps::jsonFileIntegrity_t CJsonIotEps::checkJsonFilesIntegrity(){ 
    uint32_t H0 = 0;
    uint32_t H1 = 0;
    uint32_t H2 = 0;
    _jsonFileIntegrity = FILES_ERROR;

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
            if (configFile) { H0 = _hashFile( configFile ); }
            DSPL(dPrompt + "H0 = " + String(H0));
        }
        if (SPIFFS.exists( CONFIGFILENAME_COPY1 )) {
            DSPL(dPrompt + F("reading Json file copy1"));
            File configFile = SPIFFS.open( CONFIGFILENAME_COPY1, "r");
            if (configFile) { H1 = _hashFile( configFile ); }
            DSPL(dPrompt + "H1 = " + String(H1));
        }
        if (SPIFFS.exists( CONFIGFILENAME_COPY2 )) {
            DSPL(dPrompt + F("reading Json file copy2"));
            File configFile = SPIFFS.open( CONFIGFILENAME_COPY2, "r");
            if (configFile) { H2 = _hashFile( configFile ); }
            DSPL(dPrompt + "H2 = " + String( H2 ));
        }        
    }

    if ( H0 !=0 && H0 == H1 ){ _jsonFileIntegrity = KEEP_MASTER; } //best situation
    if ( H0 !=0 && H0 == H2 ){ _jsonFileIntegrity = KEEP_MASTER; } //low probability
    //cause it means that copy1 corrupted and not master and copy2
    //sequence of wrtites is master, copy1 and at the end copy2
    if ( H1 !=0 && H1 == H2 ){ _jsonFileIntegrity = KEEP_COPY1; }
    //2 possibilities:
    //master is realy corrupted
    //master is good and there was a shut down just before the first copy

    //if (H0, H1 and H2 !=0) and H0 != H1 != H2 (all hash values are differents)
    //this situation corresponds to a good master write but wrong write at the time of first copy
    //In this case master is good and has a hash value, copy1 is wrong and has a diffrent hash value
    //regardless of master and copy2 and copy2 is good but is out of date and has a third hash value
    if ( H0 != H1 && H0 != H1 && H1 != H2 ){ _jsonFileIntegrity = TRY_MASTER; }

    //if only H0 != 0 we can try to use it
    if (H0 !=0 && H1 == 0 && H2 ==0 ){ _jsonFileIntegrity = TRY_MASTER; }

    //If all hash value are 0 there is no file : it is a fatal error
    
    switch (_jsonFileIntegrity){
        case KEEP_MASTER:
            DSPL( dPrompt + F("Keep master"));
            _fileNameToLoad = CONFIGFILENAME;
            break;
        case KEEP_COPY1:
            DSPL( dPrompt + F("Keep copy"));
            _fileNameToLoad = CONFIGFILENAME_COPY1;
            break;  
        case TRY_MASTER:
            DSPL( dPrompt + F("Try master"));
            _fileNameToLoad = CONFIGFILENAME;
            break;
        case FILES_ERROR:
            DSPL( dPrompt + F("Fatal file error"));
            _fileNameToLoad = "";
            break;           
        default:
            break;
    }

    if ( _jsonFileIntegrity != FILES_ERROR ){
        File file = SPIFFS.open( _fileNameToLoad, "r");
        _jsonVersion = "";
        _jsonTag = "";
        if (file){
            size_t size = file.size();
            std::unique_ptr<char[]> buf(new char[size]);
            file.readBytes(buf.get(), size);
            DynamicJsonBuffer jsonBuffer;
            JsonObject& json = jsonBuffer.parseObject(buf.get());
            if (json.success()) {
                _jsonVersion = json["general"]["jsonVersion"].as<String>();
                _jsonTag = json["general"]["jsonTag"].as<String>();
                DSPL( dPrompt + F("JSON file read version : ") + _jsonVersion );
            }
        }
        file.close();
        if ( ( _jsonVersion != JSON_VERSION ) || ( _jsonTag != JSON_TAG ) ){
            _jsonFileIntegrity = FILES_ERROR;
            _fileNameToLoad = "";
        }

    DSPL( dPrompt + F("after Tag and version check."));
    switch (_jsonFileIntegrity){
        case KEEP_MASTER:
            DSPL( dPrompt + F("Keep master"));
            _fileNameToLoad = CONFIGFILENAME;
            break;
        case KEEP_COPY1:
            DSPL( dPrompt + F("Keep copy"));
            _fileNameToLoad = CONFIGFILENAME_COPY1;
            break;  
        case TRY_MASTER:
            DSPL( dPrompt + F("Try master"));
            _fileNameToLoad = CONFIGFILENAME;
            break;
        case FILES_ERROR:
            DSPL( dPrompt + F("Fatal file error"));
            _fileNameToLoad = "";
            break;           
        default:
            break;
    }


    }

    return _jsonFileIntegrity;
}

uint32_t CJsonIotEps::_hashFile( File jsonFile ){
    HashPrint hashPrint;
    uint32_t hVal = 0;
    DEFDPROMPT("Hasfile")
    DSPL( F("\tJson file opened ") );
    size_t size = jsonFile.size();
    DSPL( dPrompt + "json file size : " + (String)size ) ;
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);
    jsonFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());
    // json.printTo(DEBUGPORT);
    if (json.success()) {
        json.printTo(hashPrint);
        hVal = hashPrint.hash();
        //DSPL(dPrompt + "H0 =" +String(H0));
    }
    jsonFile.close();
    return hVal;  
}