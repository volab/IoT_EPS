/**
* @file cpowerplug.cpp
* @author J.Soranzo
* @date 10/11/2018
* @copyright see project readme 
* @version 1.0
* @brief This class is the plug class for Electrical Power Strip project
*/

#include "cpowerplug.h"
#include "debugSerialPort.h"

extern RTC_DS3231 rtc;

const String CPowerPlug::modes[5] = { MANUAL_MODE, TIMER_MODE, CYCLIC_MODE, HEBDO_MODE, CLONE_MODE };


int CPowerPlug::modeId( String mode ){
    int i;
    for ( i = 0; i <  5 ; i++ ){
        if ( mode == modes[i] ) break;
    }
    return i;
}

void CPowerPlug::begin( int pin , int onOffLedPin, int bpPin, int mode ){
    if (!_initDone) init();
    _pin = pin;
    _onOffLedPin = onOffLedPin;
    _mode = mode;
    _state = OFF;
    updateOutputs( false );
    _mcp.pinMode( _pin, OUTPUT );
    _mcp.pinMode( _onOffLedPin, OUTPUT );
    bp.begin( bpPin );
}

/** 
@fn void CPowerPlug::on()
@brief méthode qui met le plug sur ON mais n'effectue pas la sortie physique
@return pas de paramètre ni de valeur de retour. Travail sur les membres de la classe

Cette méthode lit et écrit directment dans le fichier json pour l'état du plug
*/
void CPowerPlug::on(){
    DEFDPROMPT( "CPOwerPlug")
    // if ( _pin == 0){
    if ( !_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    bool prevState = _state;
    _state = ON ;
    updateOutputs( prevState != _state ); //to count only real plug switch
    writeToJson( JSON_PARAMNAME_STATE, "ON" );

}

void CPowerPlug::off(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    _state = OFF ;
    bool prevState = _state;
    updateOutputs( prevState != _state ); //to count only real plug switch
    writeToJson( JSON_PARAMNAME_STATE, "OFF" );
}

void CPowerPlug::toggle(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        /** @todo  check _initDone fonctionality */
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    _state = !_state ;
    updateOutputs();
    writeToJson( JSON_PARAMNAME_STATE, _state?"ON":"OFF" );
}

/** 
@fn bool CPowerPlug::isItTimeToSwitch()
@brief when completed, this function check if it is time to switch the plug
@return no return value and no parameter
*/
bool CPowerPlug::isItTimeToSwitch(){
    /** @todo complete isItTimeToSwitch */
    return (true); //to do change this one ;-)
}

/** 
@fn void CPowerPlug::updateOutputs()
@brief update the state of the physical outputs
@param writeToJsonCount a booleen to enable onOff counter to be inc in json (for begin purpose)
@return no return value 

This function read and write onoffcount in the json file
*/
void CPowerPlug::updateOutputs( bool writeToJsonCount ){
    DEFDPROMPT( "updateOutputs");
    _mcp.digitalWrite( _pin, _state );
    _mcp.digitalWrite( _onOffLedPin, _state );
    if ( writeToJsonCount ){
        String strCount = readFromJson( JSON_PARAMNAME_ONOFCOUNT );
        // int iCount = strCount.toInt();
        // strCount = String( iCount++ );
        strCount = String( strCount.toInt() + 1 );
        DSPL(dPrompt + "nouvelle valeur du compteur : " + strCount);
        writeToJson( JSON_PARAMNAME_ONOFCOUNT, strCount );        
    }

   
}

/** 
@fn bool CPowerPlug::readFromJson()
@brief read from json  configuration file the parameters for the instancied plug

Search are made in the file on the name of the plug as redPlug for exemple
@return a booleen true if all is ok
*/
bool CPowerPlug::readFromJson(){
    String sState, sMode, sHDebut, sHFin, sDureeOn, sDureeOff;
    String sClonedPlug, sOnOffCount, sNextTime2switch;
    String sJours[7];
    DEFDPROMPT("reading config values for " + getPlugName())
    // DSPL( dPrompt +F("Mounting FS..."));
    if (SPIFFS.begin()) {
        // DEBUGPORT.println(dPrompt + F("File system mounted "));
        if (SPIFFS.exists( CONFIGFILENAME )) {
            //file exists, reading and loading
            // DSP(dPrompt + F("reading config file... "));
            File configFile = SPIFFS.open( CONFIGFILENAME , "r");
            if (configFile) {
                // DSPL( F("Config file is open ") );
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);
                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    JsonObject& plug = json[getPlugName()];
                    sState = plug["State"].as<String>();
                    sMode = plug["Mode"].as<String>();
                    sHDebut = plug["hDebut"].as<String>();
                    sHFin = plug["hFin"].as<String>();
                    sDureeOn = plug["dureeOn"].as<String>();
                    sDureeOff = plug["dureeOff"].as<String>();
                    sClonedPlug = plug["clonedPlug"].as<String>();
                    sOnOffCount = plug["onOffCount"].as<String>();
                    sNextTime2switch = plug[JSON_PARAMNAME_NEXTSWITCH].as<String>();
                    DSPL( dPrompt + "Mode = " + sMode );
                    _mode = modeId( sMode );
                    DSPL( dPrompt + "Etat = " + sState );
                    _state = (sState == "ON");
                    DSPL( dPrompt + "Start time = " + sHDebut );
                    DSPL( dPrompt + "End time = " + sHFin );
                    DSPL( dPrompt + "on duration = " + sDureeOn );
                    DSPL( dPrompt + "off duration = " + sDureeOff );
                    DSPL( dPrompt + "Cloned plug = " + sClonedPlug );
                    DSPL( dPrompt + "Relay on off count = " + sOnOffCount );
                    
                    _nextTimeToSwitch = sNextTime2switch.toInt();
                    if ( _nextTimeToSwitch ){
                        DSPL( dPrompt + "Next time to switch : " + \
                        CEpsStrTime::unixTime2String( _nextTimeToSwitch ));
                    }

                    DSP( dPrompt + "Jours : ");
                    JsonArray& plugJours = plug["Jours"];
                    for ( int i = 0; i < 7 ; i++ ){
                        sJours[i] = plugJours[i].as<String>();
                        // DSPL( dPrompt + "jours " + (String)i + " = " + sJours[i] );
                        if (sJours[i] == "ON"){
                            DSP( "Jours " + (String)i + " est ON. " );
                        }   
                    }
                    DSPL("");
/** @todo converts and store the string parameter in the members of the class*/
/** @todo update output regarless of mode and the state of main power switch*/
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
@fn String CPowerPlug::readFromJson( String param )
@brief second implementation of this function, to read only one parameter of the curent plug
@param param the parameter to retrieve
@return the value of the parameter or "nf" if not found
*/
String CPowerPlug::readFromJson( String param ){
    String sRetValue;
    DEFDPROMPT("reading from Json for " + getPlugName() + "pamameter : " + param )
    if (SPIFFS.begin()) {
        if (SPIFFS.exists( CONFIGFILENAME )) {
            File configFile = SPIFFS.open( CONFIGFILENAME , "r");
            if (configFile) {
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);
                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                if (json.success()) {
                    JsonObject& plug = json[getPlugName()];
                    sRetValue = plug[param].as<String>();
                } else {
                    DEBUGPORT.println(dPrompt + F("Failed to load json config"));
                    return RETURN_NOT_FOUND_VALUE;
                }
                configFile.close();
                return sRetValue;
            }
        } else {
            dPrompt += F("Failed to open ");
            dPrompt += CONFIGFILENAME;
            DEBUGPORT.println(dPrompt);
            return RETURN_NOT_FOUND_VALUE;
        }

    } else {
        DEBUGPORT.println( dPrompt + F("Failed to mount FS"));
        return RETURN_NOT_FOUND_VALUE;
    }    
}

/** 
@fn void CPowerPlug::handleHtmlReq()
@brief treat all html received parameter and write in json config file
@param allRecParam Received parameters as a String
@return nothing
*/
void CPowerPlug::handleHtmlReq( String allRecParam ){
    String param, mode, state;
    String prevMode;
    DEFDPROMPT( "CPlug handle html param");
    DSPL( dPrompt + allRecParam);
    DSPL( dPrompt + "Traitements pour : " + _plugName );
    param = JSON_PARAMNAME_MODE;
    mode = extractParamFromHtmlReq( allRecParam, param );
    DSPL( dPrompt + "Mode = " + mode );
    _mode = modeId( mode );
    // DSPL( dPrompt + "_mode =" + (String)_mode);
    prevMode = readFromJson( param ); //why ? For bp acquit
    writeToJson( param, mode );
    if ( mode == MANUAL_MODE){
        DSPL( dPrompt + "Manual mode actions ");
        //manual mode parameters :
        //State
        if ( mode != prevMode ) bp.acquit(); //to reset previus memorised pushed bp
        param = JSON_PARAMNAME_STATE;
        state = extractParamFromHtmlReq( allRecParam, param );
        DSPL( dPrompt + _plugName + " : extracted state = " + state);
        if (state != NOT_FOUND ){
            if (state == "ON") on(); else off();
            /** @todo review this statement it should not be so easy it should take into 
            account time and perhaps previous state*/
            //writeToJson( param, state ); //done in on off methods
        }
        
        param = JSON_PARAMNAME_OFFDURATION;
        CEpsStrTime dureeOff;
        dureeOff.setMode( CEpsStrTime::MMMSS );
        dureeOff = (CEpsStrTime)extractParamFromHtmlReq( allRecParam, param );
        DSPL( dPrompt + _plugName + " : extracted dureeoff en secondes = " + (String)dureeOff.getSeconds() );
        if (dureeOff.isValid){
            writeToJson( param, dureeOff.getStringVal() );
            //Calculate nextTimeToSwith and write to json
            _nextTimeToSwitch = dureeOff.computeNextTime();
            DSPL( dPrompt + "nt2s : " + CEpsStrTime::unixTime2String( _nextTimeToSwitch ) );
            writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
        }
        //duree avant arret dureeOff if dureeOff then calculate hFin and work only with hFin
        //ou
        //heure arret : hFin
        // ou rien
        param = JSON_PARAMNAME_ENDTIME;
        String hFin = extractParamFromHtmlReq( allRecParam, param );        
        DSPL( dPrompt + _plugName + " : extracted hFin as int = " + hFin.toInt() );
        //valid hFin or dureeOff
        //write to json and clean other data
    } else if ( mode == TIMER_MODE ){
        DSPL( dPrompt + "Timer mode actiuons" );
        //Timer mode parameters
        //dureeOn
    } else if ( mode == CYCLIC_MODE ){
        DSPL( dPrompt + "Cyclic mode actions" ); 
        //cyclic mode parameters
        //dureeOn//dureeOff//hDebut
    } else if ( HEBDO_MODE ){
        DSPL( dPrompt + "Hebdo mode actions" );
        //hebdo mode parameters
        //hdebut hFin
    } else if ( mode ==  CLONE_MODE){
        DSPL( dPrompt + "clone mode actions" );
        //clode mode parameters
    }
/** @todo complete this function !*/ 
}
/** 
@fn String CPowerPlug::extractParamFromHtmlReq( String allRecParam, String param )
@brief to extract a parameter from all parameter
@param allRecParam a concatened String containing all received parameters build in handlePlugOnOff()
@param param the parameter to extract
@return the value of the parameter or "nf" for not found or "" empty
*/
String CPowerPlug::extractParamFromHtmlReq( String allRecParam, String param ){
    DEFDPROMPT("extract param");
    DSPL( dPrompt + "Search for : " + param);
    param +="=";
    int pos = allRecParam.indexOf( param );
    //DSPL( dPrompt + "Pos brut = " + (String)pos);
    if ( pos == -1 ) return RETURN_NOT_FOUND_VALUE;
    pos += param.length();
    int fin = allRecParam.indexOf( "/", pos );
    //DSPL( dPrompt + "fin = " +(String)fin );
    return allRecParam.substring( pos, fin );
    /** @todo remove debug informations*/
}

/** 
@fn void CPowerPlug::writeToJson( String param, String value )
@brief this function write a parameter to json config file for the _name plug
@param param name of the parameter to be written
@param value the value of the parameter to be written in the json file
@return nothing

Writes value on parma for _plugName plug of course !
*/
void CPowerPlug::writeToJson( String param, String value ){
    DEFDPROMPT( "write to jSon");
    File configFile = SPIFFS.open( CONFIGFILENAME , "r+");
    // DSPL( dPrompt);
    if (configFile) {
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
            JsonObject& plug = json[_plugName]; 
            DSPL( dPrompt + _plugName + " : " + param + " = " + value);
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