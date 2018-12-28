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

/** 
@fn int CPowerPlug::modeId( String mode )
@brief A method to convert String mode into its id
@param mode the mode in String format
@return the equivalent id

The purpose of this is to replace an enum caus here we have the need to gat both the text form
for all json and html and the its id in numericla form for other functionnality like for loop.

A possible workaround will be:

@code {.cpp}
	for ( String s : CPowerPlug::modes){
		if (sMode == s);//do the job
	}

@endcode
*/
int CPowerPlug::modeId( String mode ){
    int i;
    for ( i = 0; i <  5 ; i++ ){
	//for ( i : modes ){
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
@brief  method that change state of the plug but not only
@return nothig and no input paramter

This methods doesn't change physical output but call updateOutputs.

It also update json file
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


/** 
@fn void CPowerPlug::off()
@brief method that change state of the plug but not only
@return nothig and no input paramter

This methods doesn't change physical output but call updateOutputs.

It also update json file
*/
void CPowerPlug::off(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    bool prevState = _state;
    _state = OFF ;
    updateOutputs( prevState != _state ); //to count only real plug switch
    writeToJson( JSON_PARAMNAME_STATE, "OFF" );
}

/** 
@fn void CPowerPlug::toggle()
@brief toggle stat

see on() and off() methode

*/
void CPowerPlug::toggle(){
    DEFDPROMPT( "CPOwerPlug")
    if (!_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    _state = !_state ;
    updateOutputs();
    writeToJson( JSON_PARAMNAME_STATE, _state?"ON":"OFF" );
}

/** 
@fn bool CPowerPlug::isItTimeToSwitch()
@brief this function check if it is time to switch the plug
@return return true if it is time to switch the plug value and no parameter

Do not compute new time to switch
*/
bool CPowerPlug::isItTimeToSwitch(){
    if ( _nextTimeToSwitch == 0 ) return false;
    // RTC_DS3231 rtc;
    if ( CRtc::now().unixtime() > _nextTimeToSwitch ) return true;
    return false;
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
/////////////////////////////////////////////////////////////////////////////
//    Reading from file                                                    //
/////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////
//    member updates                                                       //
/////////////////////////////////////////////////////////////////////////////
                    _mode = modeId( sMode );
                    _state = (sState == "ON");                    
                    _nextTimeToSwitch = sNextTime2switch.toInt();
/** @todo continue to converts and store the string parameters
 in the members of the class
*/
/////////////////////////////////////////////////////////////////////////////
//    debug displays                                                       //
/////////////////////////////////////////////////////////////////////////////
                    DSPL( dPrompt + "Mode = " + sMode );
                    DSPL( dPrompt + "Etat = " + sState );
                    DSPL( dPrompt + F("Start time = ") + sHDebut );
                    DSPL( dPrompt + F("End time = ") + sHFin );
                    DSPL( dPrompt + F("on duration = ") + sDureeOn );
                    DSPL( dPrompt + F("off duration = ") + sDureeOff );
                    DSPL( dPrompt + F("Cloned plug = ") + sClonedPlug );
                    DSPL( dPrompt + F("Relay on off count = ") + sOnOffCount );
                    if ( _nextTimeToSwitch ){
                        DSPL( dPrompt + F("Next time to switch : ") + \
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
    DSPL( dPrompt + F("Traitements pour : ") + _plugName );
    param = JSON_PARAMNAME_MODE;
    mode = extractParamFromHtmlReq( allRecParam, param );
    DSPL( dPrompt + "Mode = " + mode );
    _mode = modeId( mode );

    prevMode = readFromJson( param ); //why ? For bp acquit
    writeToJson( param, mode );
    if ( mode == MANUAL_MODE){
		/////////////////////////////////////////////////////////////////////////////
		//    Compute MANUAL MODE                                                  //
		/////////////////////////////////////////////////////////////////////////////
        DSPL( dPrompt + F("Manual mode actions ") );
        //manual mode parameters :
        //State
        if ( mode != prevMode ) bp.acquit(); //to reset previus memorised pushed bp
        param = JSON_PARAMNAME_STATE;
        state = extractParamFromHtmlReq( allRecParam, param );
        DSPL( dPrompt + _plugName + F(" : extracted state = ") + state);
        if (state != NOT_FOUND ){
            if (state == "ON") {
				on(); 
				/////////////////////////////////////////////////////////////////////////////
				//    Compute MANUAL MODE  : dureeOff                                      //
				/////////////////////////////////////////////////////////////////////////////
				param = JSON_PARAMNAME_OFFDURATION;
				CEpsStrTime dureeOff;
				dureeOff.setMode( CEpsStrTime::MMMSS );
				dureeOff = (CEpsStrTime)extractParamFromHtmlReq( allRecParam, param );
				_nextTimeToSwitch = 0;
				DSPL( dPrompt + "dureeOff validity : " + \
                    (dureeOff.isValid?"valid":"invalid") );
				if (dureeOff.isValid){
					DSPL( dPrompt + _plugName + " : extracted dureeoff en secondes = " + \
						(String)dureeOff.getSeconds() );
					writeToJson( param, dureeOff.getStringVal() );
					_nextTimeToSwitch = dureeOff.computeNextTime();
				} else writeToJson( param, "" );
				/////////////////////////////////////////////////////////////////////////////
				//    Compute MANUAL MODE  : hFin                                          //
				/////////////////////////////////////////////////////////////////////////////
				param = JSON_PARAMNAME_ENDTIME;
				// String hFin = extractParamFromHtmlReq( allRecParam, param );    
				CEpsStrTime hFin;
				// hFin.setMode( CEpsStrTime::HHMM );
				hFin = CEpsStrTime(extractParamFromHtmlReq( allRecParam, param ),\
					CEpsStrTime::HHMM );
				DSPL( dPrompt + "hFin validity : " + (hFin.isValid?"valid":"invalid") );
				if ( hFin.isValid && !dureeOff.isValid ){
					_nextTimeToSwitch = hFin.computeNextTime();
					writeToJson( param, hFin.getStringVal() );
					DSPL( dPrompt + _plugName + F(" : extracted hFin as String = ") + \
						(String)hFin.getStringVal() ); 
				}
				DSPL( dPrompt + "nt2s : " + CEpsStrTime::unixTime2String( _nextTimeToSwitch ) );
				writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
				
			}else { //state == "OFF"
				_nextTimeToSwitch = 0;
                writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
                writeToJson( JSON_PARAMNAME_ENDTIME, "" );
				writeToJson( JSON_PARAMNAME_OFFDURATION, "" );
                writeToJson( JSON_PARAMNAME_ONDURATION, "" );
                writeToJson( JSON_PARAMNAME_STARTTIME, "" );
				off();
			}
        }
    } else if ( mode == TIMER_MODE ){
		/////////////////////////////////////////////////////////////////////////////
		//    Compute TIMER MODE                                                  //
		/////////////////////////////////////////////////////////////////////////////
        DSPL( dPrompt + F("Timer mode actions") );
        if ( mode != prevMode ) bp.acquit(); //to reset previus memorised pushed bp
        param = JSON_PARAMNAME_ONDURATION;
        CEpsStrTime dureeOn;
        dureeOn = (CEpsStrTime)extractParamFromHtmlReq( allRecParam, param );
        _nextTimeToSwitch = 0; 
        DSPL( dPrompt + "dureeOn validity : " + \
            (dureeOn.isValid?"valid":"invalid") );     
        if (dureeOn.isValid){
            DSPL( dPrompt + _plugName + " : extracted dureeOn en secondes = " + \
                (String)dureeOn.getSeconds() );
            writeToJson( param, dureeOn.getStringVal() );
            _nextTimeToSwitch = dureeOn.computeNextTime();
            // param = JSON_PARAMNAME_STATE;
            state = extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_STATE );
            DSPL( dPrompt + _plugName + F(" : extracted state = ") + state);
            if (state != NOT_FOUND ){
                if (state == "ON") {
                    on();
                    writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch ); 
                } else {
                    off();
                    writeToJson( JSON_PARAMNAME_NEXTSWITCH, "0" );
                }
            }             
        } else { //onDuration not valid
            writeToJson( JSON_PARAMNAME_ONDURATION, "" ); 
            // writeToJson( JSON_PARAMNAME_MODE, prevMode );
            writeToJson( JSON_PARAMNAME_MODE, MANUAL_MODE );
            writeToJson( JSON_PARAMNAME_NEXTSWITCH, "0" );
            off();
        }        
           
    } else if ( mode == CYCLIC_MODE ){
        DSPL( dPrompt + F("Cyclic mode actions") ); 
        //cyclic mode parameters
        //dureeOn//dureeOff//hDebut
    } else if ( HEBDO_MODE ){
        DSPL( dPrompt + F("Hebdo mode actions") );
        //hebdo mode parameters
        //hdebut hFin
    } else if ( mode ==  CLONE_MODE){
        DSPL( dPrompt + F("clone mode actions") );
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
    DSPL( dPrompt + F("Search for : ") + param);
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

/** 
 @fn void CPowerPlug::switchAtTime()
 @brief after call isItTimeToSwitch, this fucntion switch the plug as needed and...
 @return no return value and no parameter

Compute next time to switch if necessary regardless of _mode
*/
void CPowerPlug::switchAtTime(){
    String sMode = modes[ _mode ];
    if ( sMode == MANUAL_MODE ){
        off();
        _nextTimeToSwitch = 0;
        writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
        writeToJson( JSON_PARAMNAME_ENDTIME, "" );
        writeToJson( JSON_PARAMNAME_OFFDURATION, "" );
        writeToJson( JSON_PARAMNAME_ONDURATION, "" );
        writeToJson( JSON_PARAMNAME_STARTTIME, "" );
        
    } else if ( sMode == TIMER_MODE ){
        off();
        _nextTimeToSwitch = 0;
        writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );      
    }
}


void CPowerPlug::handleBpClic(){
    String sMode = getStringMode();
    if ( sMode == MANUAL_MODE ){
        if ( _state ) {
            if ( _nextTimeToSwitch )
                switchAtTime(); //force off and reset nt2s
            else off();
        } else on();   
    } else if ( sMode == TIMER_MODE ){
        //restart timer
        //if on jsut restart timer
        //if off put on and restart timer
        //restart timer is compute new nextTimeToSwitch
        CEpsStrTime dureeOn;
        dureeOn = (CEpsStrTime)readFromJson( JSON_PARAMNAME_ONDURATION );
        _nextTimeToSwitch = dureeOn.computeNextTime();
        writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
        on();
    }
    bp.acquit();    
}