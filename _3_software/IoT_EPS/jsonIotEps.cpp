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


/**
 @fn bool CJsonIotEps::checkIfStoreNeeded()
 @brief Check if CParam or CPowerPlugs store json file is needed
 @return true if store is needed
*/
bool CJsonIotEps::checkIfStoreNeeded(){
    bool retVal = false;
    DEFDPROMPT("JsonIotEps");
    
    if ( _pcParam->_jsonWriteRequest ){
        retVal=true;
    } else { //if true no need to test plug causeonly one json file
        for (int i = 0; i < _pcParam->getNumberOfPlugs(); i++ ){
            retVal |= _pPlugs[i]._jsonWriteRequest;
            _pPlugs[i]._jsonWriteRequest = false; //to be remove after test
        }
    }

    return retVal;
}



/**
 @fn void CJsonIotEps::printFileIntegrity()
 @brief Print file integrity for debug purpose
 @return no param and no return
*/
void CJsonIotEps::printFileIntegrity(){
    DEFDPROMPT("Json file integrity print function");

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

void CJsonIotEps::storeJson(){
    DEFDPROMPT( "CJsonIotEps store json method" );
    DSPL( dPrompt + F("*********JSON WRITE REQUESTED***************"));




    //to remember
    _pcParam->_jsonWriteRequest = false;
    for (int i = 0; i < _pcParam->getNumberOfPlugs(); i++ ){
        _pPlugs[i]._jsonWriteRequest = false;
    }
    return;
}

void CJsonIotEps::_storeJsonOnFile(String file_name){

    DEFDPROMPT( "CJsonIotEps store one json method" );

    File configFile = SPIFFS.open( file_name , "r");
    // DSPL( dPrompt);
    if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        configFile.close();
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {






            // JsonObject& plug = json[_plugName]; 
            // DSPL( dPrompt + _plugName + " : " + param + " = " + value);
            // plug[param] = value; 
            // configFile.seek(0, SeekSet);
            // configFile.close();
            configFile = SPIFFS.open( CONFIGFILENAME , "w");
            json.printTo(configFile);
            // json.prettyPrintTo(configFile);
            // plug.prettyPrintTo(Serial);
            // DSPL();
        } else {
            DEBUGPORT.println(dPrompt + F("Failed to load json config"));
            // return false;
        }
        //configFile.close();
        // return true;        
    }
}

/**
 @fn bool CJsonIotEps::loadJsonPlugParam( int plugNumber, int mainPowerSwitchState )
 @brief Check the integrity of json file
 @param plugNumber : Number of plugs in the system
 @param mainPowerSwitchState : to decide if we stat normaly or if we need to stop all plugs.
 @return a booleen true if all is ok.

 Need the integrity is checked before use it
*/
bool CJsonIotEps::loadJsonPlugParam( int plugNumber, int mainPowerSwitchState ){
    bool returnVal = false;
    String sState, sMode, sHDebut, sHFin, sDureeOn, sDureeOff;
    String sClonedPlug, sOnOffCount, sNextTime2switch, sPause;
    String sNickName;
    String sJours[7];
    bool writeReq = false;

    DEFDPROMPT( "Load Json Plugs Data");
    DSPL( dPrompt + F("Enter in the fonction. ")  );
    if ( _jsonFileIntegrity != FILES_ERROR ){
        File file = SPIFFS.open( _fileNameToLoad, "r");
        DSPL( dPrompt + F("File open ") + _fileNameToLoad );
        if (file){
            size_t size = file.size();
            std::unique_ptr<char[]> buf(new char[size]);
            file.readBytes(buf.get(), size);
            file.close();
            DynamicJsonBuffer jsonBuffer;
            JsonObject& json = jsonBuffer.parseObject(buf.get());
            if (json.success()){
                for (int i = 0; i < plugNumber; i++ ){
                    if ( mainPowerSwitchState == 1 ){ // 1 if switch is on
                        JsonObject& plug = json[_pPlugs[i].getPlugName()];
                        sNickName = plug["nickName"].as<String>();
                        sState = plug["State"].as<String>();
                        sPause = plug[JSON_PARAMNAME_PAUSE].as<String>();
                        sMode = plug["Mode"].as<String>();
                        sHDebut = plug["hDebut"].as<String>();
                        sHFin = plug["hFin"].as<String>();
                        sDureeOn = plug["dureeOn"].as<String>();
                        sDureeOff = plug["dureeOff"].as<String>();
                        sClonedPlug = plug["clonedPlug"].as<String>();
                        sOnOffCount = plug["onOffCount"].as<String>();
                        sNextTime2switch = plug[JSON_PARAMNAME_NEXTSWITCH].as<String>();

                        

                        DSPL( dPrompt + F("Plug name : ") + _pPlugs[i].getPlugName() );
                        DSPL( dPrompt + F("Nick name : ") + sNickName );
                        DSPL( dPrompt + F("Etat = ") + sState );
                        DSPL( dPrompt + F("Pause state = ") + sPause );
                        DSPL( dPrompt + F("Mode = ") + sMode );
                        DSPL( dPrompt + F("Start time = ") + sHDebut );
                        DSPL( dPrompt + F("End time = ") + sHFin );
                        DSPL( dPrompt + F("on duration = ") + sDureeOn );
                        DSPL( dPrompt + F("off duration = ") + sDureeOff );
                        DSPL( dPrompt + F("Cloned plug = ") + sClonedPlug );
                        DSPL( dPrompt + F("Relay on off count = ") + sOnOffCount );
                        DSPL( dPrompt + F("next time to switch = ") + sNextTime2switch );
                        /////////////////////////////////////////////////////////////////////////////
                        //    plugs member updates                                                  //
                        /////////////////////////////////////////////////////////////////////////////
                        _pPlugs[i]._nickName = sNickName;
                        _pPlugs[i]._state = (sState == "ON");
                        _pPlugs[i]._pause = ( sPause == "ON" );
                        _pPlugs[i]._mode = _pPlugs[i].modeId( sMode ); 
                        _pPlugs[i]._hDebut = CEpsStrTime( sHDebut, CEpsStrTime::HHMM);
                        _pPlugs[i]._hFin = CEpsStrTime( sHFin, CEpsStrTime::HHMM );
                        _pPlugs[i]._dureeOn = CEpsStrTime( sDureeOn, CEpsStrTime::MMM );
                        _pPlugs[i]._dureeOff = CEpsStrTime( sDureeOff, CEpsStrTime::MMM );
                        _pPlugs[i]._clonedPlug = sClonedPlug;
                        _pPlugs[i]._onOffCount = sOnOffCount.toInt();             
                        _pPlugs[i]._nextTimeToSwitch = sNextTime2switch.toInt();
                        
                        /////////////////////////////////////////////////////////////////////////////
                        //    special for days of Hebdo mode                                       //
                        /////////////////////////////////////////////////////////////////////////////
                        DSPL( dPrompt + "Jours : ");
                        JsonArray& plugJours = plug["Jours"];
                        _pPlugs[i]._daysOnWeek = 0;
                        for ( int i = 0; i < 7 ; i++ ){
                            sJours[i] = plugJours[i].as<String>();
                            // DSPL( dPrompt + "jours " + (String)i + " = " + sJours[i] );
                            if (sJours[i] == "ON"){
                                DSPL( "Jours " + (String)i + " est ON. " );
                                bitSet( _pPlugs[i]._daysOnWeek, i);
                            } else {
                                DSPL( "Jours " + (String)i + " est OFF. " );
                            } 
                        }
                        DSPL("");                        
                    } else { // main power switch is off stop all plugs
                    //plugs return to manual mode OFF state.
                        _pPlugs[i].handleBpLongClic();
                        writeReq = writeReq | _pPlugs[i]._jsonWriteRequest;
                        _pPlugs[i]._jsonWriteRequest = false;
                    }
                }
            }
            if ( writeReq ){
                storeJson();
            }
            returnVal = true;
        }

    } else {
        DSPL( dPrompt + F("Json file integrity error") );
    }


    return (returnVal);
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
    // could be KEEP_MASTER

    //if only H0 != 0 we can try to use it
    if (H0 !=0 && H1 == 0 && H2 ==0 ){ _jsonFileIntegrity = TRY_MASTER; }
    // could be KEEP_MASTER

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

    //Check file spacial Tag Values (Version an TAG)
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