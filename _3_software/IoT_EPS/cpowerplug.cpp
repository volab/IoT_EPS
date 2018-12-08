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




void CPowerPlug::begin( int pin , int onOffLedPin, int mode ){
    if (!_initDone) init();
    _pin = pin;
    _onOffLedPin = onOffLedPin;
    _mode = mode;
    _state = OFF;
    updateOutputs();
    _mcp.pinMode( _pin, OUTPUT );
    _mcp.pinMode( _onOffLedPin, OUTPUT );

}

void CPowerPlug::on(){

    DEFDPROMPT( "CPOwerPlug")
    // if ( _pin == 0){
    if ( !_initDone){
        DSPL( dPrompt + F(" plug not started (call .begin().") );
    }
    _state = ON ;
    updateOutputs();
}

void CPowerPlug::off(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        DSPL( dPrompt + F(" plug not started (call .begin().") );
    }
    _state = OFF ;
    updateOutputs();
}

void CPowerPlug::toggle(){
    DEFDPROMPT( "CPOwerPlug")
    if (_pin == 0){
        /** @todo  check _initDone fonctionality */
        DSPL( dPrompt + F(" plug not started (call .begin().") );
    }
    _state = !_state ;
    updateOutputs();
}

bool CPowerPlug::isItTimeToSwitch(){
    /** @todo complete isItTimeToSwitch */
    return (true); //to to change ths one ;-)
}

void CPowerPlug::updateOutputs(){
    _mcp.digitalWrite( _pin, _state );
    _mcp.digitalWrite( _onOffLedPin, _state );    
}

bool CPowerPlug::readFromJson(){
    String sState, sMode;
    DEFDPROMPT("reading config values for " + getPlugName())
    DSPL( dPrompt +F("Mounting FS..."));
    if (SPIFFS.begin()) {
        DEBUGPORT.println(dPrompt + F("File system mounted "));
        if (SPIFFS.exists( CONFIGFILENAME )) {
            //file exists, reading and loading
            DSP(dPrompt + F("reading config file... "));
            File configFile = SPIFFS.open( CONFIGFILENAME , "r");
            if (configFile) {
                DSPL( F("Config file is open ") );
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
                    DSPL( dPrompt + "Mode = " + sMode );
                    DSPL( dPrompt + "Etat = " + sState );
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

        