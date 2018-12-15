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
    updateOutputs();
    _mcp.pinMode( _pin, OUTPUT );
    _mcp.pinMode( _onOffLedPin, OUTPUT );
    bp.begin( bpPin );

}


void CPowerPlug::on(){
    DEFDPROMPT( "CPOwerPlug")
    // if ( _pin == 0){
    if ( !_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    _state = ON ;
    updateOutputs();
    writeToJson( JSON_PARAMNAME_STATE, "ON" );
}

void CPowerPlug::off(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    _state = OFF ;
    updateOutputs();
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
@return no return value and no parameter
*/
void CPowerPlug::updateOutputs(){
    _mcp.digitalWrite( _pin, _state );
    _mcp.digitalWrite( _onOffLedPin, _state );   
/** @todo write the state in the config json file*/    
}

/** 
@fn bool CPowerPlug::readFromJson()
@brief read from json  configuration file the parameters for the instancied plug

Search are made in the file on the name of the plug as redPlug for exemple
@return a booleen true if all is ok
*/
bool CPowerPlug::readFromJson(){
    String sState, sMode, sHDebut, sHFin, sDureeOn, sDureeOff;
    String sClonedPlug, sOnOffCount;
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
                    DSPL( dPrompt + "Mode = " + sMode );
                    DSPL( dPrompt + "Etat = " + sState );
                    DSPL( dPrompt + "Start time = " + sHDebut );
                    DSPL( dPrompt + "End time = " + sHFin );
                    DSPL( dPrompt + "on duration = " + sDureeOn );
                    DSPL( dPrompt + "off duration = " + sDureeOff );
                    DSPL( dPrompt + "Cloned plug = " + sClonedPlug );
                    DSPL( dPrompt + "Relay on off count = " + sOnOffCount );
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
@param parma the parameter to retrieve
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
    DEFDPROMPT( "CPlug handle html param");
    DSPL( dPrompt + allRecParam);
    DSPL( dPrompt + "Traitements pour : " + _plugName );
    param = JSON_PARAMNAME_MODE;
    mode = extractParamFromHtmlReq( allRecParam, param );
    DSPL( dPrompt + "Mode = " + mode );
    // _mode = modeId( mode );
    // DSPL( dPrompt + "_mode =" + (String)_mode);
    writeToJson( param, mode );
    if ( mode == MANUAL_MODE){
        DSPL( dPrompt + "Manual mode actions ");
        //manual mode parameters :
        //State
        param = JSON_PARAMNAME_STATE;
        state = extractParamFromHtmlReq( allRecParam, param );
        DSPL( dPrompt + _plugName + " : extracted state = " + state);
        if (state != "nf"){
            if (state == "ON") on(); else off();
            //writeToJson( param, state );
        }
        param = JSON_PARAMNAME_OFFDURATION;
        String dureeOff = extractParamFromHtmlReq( allRecParam, param );
        //possible value : a number of minutes before off
        // max value = MANUEL_MODE_MAXOFFDURATION
        // "nf" parameter not found
        // "en minutes" or something like that
        DSPL( dPrompt + _plugName + " : extracted dureeoff as int = " + dureeOff.toInt() );
        //duree avant arret dureeOff si dureeOff then calculate hFin and work only with hFin
        //ou
        //heure arret : hFin
        // ou rien
        
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
    DSPL( dPrompt + "Pos brut = " + (String)pos);
    if ( pos == -1 ) return RETURN_NOT_FOUND_VALUE;
    pos += param.length();
    int fin = allRecParam.indexOf( "/", pos );
    DSPL( dPrompt + "fin = " +(String)fin );
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