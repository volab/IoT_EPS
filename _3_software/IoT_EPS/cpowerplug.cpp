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

// extern RTC_DS3231 rtc;



const String CPowerPlug::modes[5] = { MANUAL_MODE, TIMER_MODE, CYCLIC_MODE, HEBDO_MODE, CLONE_MODE };

/** 
@fn int CPowerPlug::modeId( String mode )
@brief A method to convert String mode into its id...
@param mode the mode in String format
@return the equivalent id

The purpose of this is to replace an enum cause here we have the need to get both the text form
for all json and html and its id in numerical form for other functionnalities like for loop.

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
        if ( mode == modes[i] ) break;
    }
    return i;
}


void CPowerPlug::begin( int pin , int onOffLedPin, int bpPin
                        , plugColor_t color, String name, int mode ){
    if (!_initDone) init();
    _pin = pin;
    _onOffLedPin = onOffLedPin;
    _mode = mode;
    _state = OFF;
    updateOutputs( false );
    _nano.pinMode( _pin, OUTPUT );
    _nano.pinMode( _onOffLedPin, OUTPUT );
    bp.begin( bpPin );
    _pause = false;
    _plugName = name ;
    _couleur = color;
}



/** 
@fn void CPowerPlug::on()
@brief  method that change state of the plug but not only...
@return nothig and no input paramter

This methods doesn't change physical output but call updateOutputs.

It also update json file
*/
void CPowerPlug::on(){
    DEFDPROMPT( "CPOwerPlug")
    if ( !_initDone){
        DSPL( dPrompt + F(" plug not started, call .begin().") );
    }
    bool prevState = _state;
    _state = ON ;
    updateOutputs( prevState != _state ); //to count only real plug switch
    writeToJson( JSON_PARAMNAME_STATE, "ON" );
    /** @todo [NECESSARY]replace above by __jsonWriteRequest  */
    

}


/** 
@fn void CPowerPlug::off()
@brief method that change state of the plug but not only...
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
    /** @todo [NECESSARY]replace above by __jsonWriteRequest  */
}

/** 
@fn void CPowerPlug::toggle()
@brief toggle stat...

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
    /** @todo [NECESSARY]replace above by __jsonWriteRequest  */
}

/** 
@fn bool CPowerPlug::isItTimeToSwitch()
@brief this function check if it is time to switch the plug...
@return return true if it is time to switch the plug

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
 @brief update the state of the physical outputs...
 @param writeToJsonCount a boolean to enable onOff counter to be inc in json (for begin purpose)
 @return no return value 

This function read and write onoffcount in the json file
*/
void CPowerPlug::updateOutputs( bool writeToJsonCount ){
    DEFDPROMPT( "updateOutputs");
    _nano.digitalWrite( _pin, _state );
    if ( _ledOn ) _nano.digitalWrite( _onOffLedPin, _state );
    if ( writeToJsonCount ){
        _onOffCount++;
        DSPL(dPrompt + F("Nouvelle valeur du compteur ON/OFF: ") + _onOffCount + " de : " + _plugName );
        writeToJson( JSON_PARAMNAME_ONOFCOUNT, "" ); //to set the flag
        /** @todo [NECESSARY]replace above by __jsonWriteRequest  */
        
    }

   
}

/** 
@fn bool CPowerPlug::readFromJson( bool restaurePhyState )
@brief read from json  configuration file the parameters for the instancied plug

Search are made in the file on the name of the plug as redPlug for exemple
 @param restaurePhyState to restaure plug relay output state if needed

 @return a booleen true if all is ok
*/
// bool CPowerPlug::readFromJson(){

/** @todo [NECESSARY] check if this method is alway needed */

bool CPowerPlug::readFromJson( bool restaurePhyState ){
    String sState, sMode, sHDebut, sHFin, sDureeOn, sDureeOff;
    String sClonedPlug, sOnOffCount, sNextTime2switch, sPause;
    String sJours[7];
    //comment du due to clone bug
    // if (!restaurePhyState){ //manuel mode and off for main powwer swith is off
        // handleBpLongClic();
        // return true;
    // }
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
                    sPause = plug[JSON_PARAMNAME_PAUSE].as<String>();
/////////////////////////////////////////////////////////////////////////////
//    member updates                                                       //
/////////////////////////////////////////////////////////////////////////////
                    _mode = modeId( sMode );
                    _state = (sState == "ON");                    
                    _nextTimeToSwitch = sNextTime2switch.toInt();
                    _pause = ( sPause == "ON" );
/////////////////////////////////////////////////////////////////////////////
//    Restaure physical state                                              //
/////////////////////////////////////////////////////////////////////////////
                    if ( restaurePhyState ){
                        if ( _state && (!_pause) ) on(); else off();
                    }                     
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
/////////////////////////////////////////////////////////////////////////////
//    special for days of Hebdo mode                                       //
/////////////////////////////////////////////////////////////////////////////
                    DSP( dPrompt + "Jours : ");
                    JsonArray& plugJours = plug["Jours"];
                    for ( int i = 0; i < 7 ; i++ ){
                        sJours[i] = plugJours[i].as<String>();
                        // DSPL( dPrompt + "jours " + (String)i + " = " + sJours[i] );
                        if (sJours[i] == "ON"){
                            DSP( "Jours " + (String)i + " est ON. " );
                            bitSet( _daysOnWeek, i);
                        }   
                    }
                    DSPL("");
/////////////////////////////////////////////////////////////////////////////
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

    return true; // non reachable line just for warning
}

/** 
@fn String CPowerPlug::readFromJson( String param )
@brief second implementation of this function, to read only one parameter of the curent plug
@param param the parameter to retrieve
@return the value of the parameter or "nf" if not found
*/

/** @todo [NECESSARY] check if this method is alway needed */
// use by CPowerPlug::handleHtmlReq 22/01/2022
// use by CPowerPlug::switchAtTime() it should use members no ?

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

    /** @todo [optionnal] change if structure to remove next line */
    return ""; //just for warning no reachable line !
}

/** 
@fn void CPowerPlug::handleHtmlReq()
@brief treat all html received parameter and write in json config file...
@param allRecParam Received parameters as a String.  
@return nothing

allRecParam is created by handlePlugOnOff in serverFunction.cpp
*/
void CPowerPlug::handleHtmlReq( String allRecParam ){
    String param, mode, state;
    String prevMode;
    DEFDPROMPT( "CPlug handle html param");
    DSPL( dPrompt + allRecParam);
    DSPL( dPrompt + F("Traitements pour : ") + _plugName );
    param = JSON_PARAMNAME_MODE;
    //mode = extractParamFromHtmlReq( allRecParam, param );
    mode = CServerWeb::extractParamFromHtmlReq( allRecParam, param );
    DSPL( dPrompt + "Mode = " + mode );
    

    prevMode = readFromJson( param ); //why ? For bp acquit
    // do not change if all is not valid
    // _mode = modeId( mode );
    // writeToJson( param, mode );
    /** DONE in the html navigator by javascript test all case invalid parameter entered */
    if ( mode == MANUAL_MODE){
        /////////////////////////////////////////////////////////////////////////////
        //    Compute MANUAL MODE                                                  //
        /////////////////////////////////////////////////////////////////////////////
        DSPL( dPrompt + F("Manual mode actions ") );
        //manual mode parameters :
        //State
        if ( mode != prevMode ) bp.acquit(); //to reset previously memorised pushed bp
        param = JSON_PARAMNAME_STATE;
        state = CServerWeb::extractParamFromHtmlReq( allRecParam, param );
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
                dureeOff = (CEpsStrTime)CServerWeb::extractParamFromHtmlReq( allRecParam, param );
                _nextTimeToSwitch = 0;
                DSPL( dPrompt + "dureeOff validity : " + \
                    (dureeOff.isValid?"valid":"invalid") );
                if (dureeOff.isValid){
                    DSPL( dPrompt + _plugName + " : extracted dureeoff in seconds = " + \
                        (String)dureeOff.getSeconds() );
                    //writeToJson( param, dureeOff.getStringVal() );
                    _dureeOff.setValue( dureeOff.getStringVal() );
                    _nextTimeToSwitch = dureeOff.computeNextTime();
                    _jsonWriteRequest = true;
                } else writeToJson( param, "" );
                /////////////////////////////////////////////////////////////////////////////
                //    Compute MANUAL MODE  : hFin                                          //
                /////////////////////////////////////////////////////////////////////////////
                param = JSON_PARAMNAME_ENDTIME;
                // String hFin = CServerWeb::extractParamFromHtmlReq( allRecParam, param );    
                CEpsStrTime hFin;
                // hFin.setMode( CEpsStrTime::HHMM );
                hFin = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, param ),\
                    CEpsStrTime::HHMM );
                DSPL( dPrompt + "hFin validity : " + (hFin.isValid?"valid":"invalid") );
                if ( hFin.isValid && !dureeOff.isValid ){
                    _nextTimeToSwitch = hFin.computeNextTime();
                    writeToJson( param, hFin.getStringVal() );
                    _hFin.setValue( hFin.getStringVal() );
                    DSPL( dPrompt + _plugName + F(" : extracted hFin as String = ") + \
                        (String)hFin.getStringVal() ); 
                }
                DSPL( dPrompt + "nt2s : " + CEpsStrTime::unixTime2String( _nextTimeToSwitch ) );
                writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
                
            }else { //state == "OFF"
                _nextTimeToSwitch = 0;
                _hFin.setValue( "" );
                _dureeOn.setValue("");
                _dureeOff.setValue("");
                //writeToJson( JSON_PARAMNAME_STARTTIME, "" ); //just for boolean set
                _jsonWriteRequest = true;
                _daysOnWeek = 0;
                writeDaysToJson();
                off();
            }
            _mode = modeId( mode );
            writeToJson( JSON_PARAMNAME_MODE, mode );
        }
    } else if ( mode == TIMER_MODE ){
        /////////////////////////////////////////////////////////////////////////////
        //    Compute TIMER MODE                                                  //
        /////////////////////////////////////////////////////////////////////////////
        DSPL( dPrompt + F("Timer mode actions") );
        if ( mode != prevMode ) bp.acquit(); //to reset previus memorised pushed bp
        param = JSON_PARAMNAME_ONDURATION;
        CEpsStrTime dureeOn;
        dureeOn = (CEpsStrTime)CServerWeb::extractParamFromHtmlReq( allRecParam, param );
        _nextTimeToSwitch = 0; 
        DSPL( dPrompt + "dureeOn validity : " + \
            (dureeOn.isValid?"valid":"invalid") );     
        if (dureeOn.isValid){
            DSPL( dPrompt + _plugName + " : extracted dureeOn en secondes = " + \
                (String)dureeOn.getSeconds() );
            writeToJson( param, "" ); //kept only for _jsonWriteRequest set to true
            _dureeOn.setValue( dureeOn.getStringVal() );
            _dureeOff.setValue( "" );
            _nextTimeToSwitch = dureeOn.computeNextTime();
            // param = JSON_PARAMNAME_STATE;
            state = CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_STATE );
            DSPL( dPrompt + _plugName + F(" : extracted state = ") + state);
            if (state != NOT_FOUND ){
                if (state == "ON") {
                    on();
                    writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch ); 
                } else {
                    off();
                    writeToJson( JSON_PARAMNAME_NEXTSWITCH, "0" );
                    _nextTimeToSwitch = 0;
                }
            }
            _mode = modeId( mode );
            writeToJson( JSON_PARAMNAME_MODE, mode );            
        } else { //onDuration not valid
            DSPL( dPrompt + "TIMER mode : an invalid parameter was entered, no change made");

        }        
           
    } else if ( mode == CYCLIC_MODE ){
        /////////////////////////////////////////////////////////////////////////////
        //    Compute CYCLIC MODE                                                  //
        /////////////////////////////////////////////////////////////////////////////
        DSPL( dPrompt + F("Cyclic mode actions") ); 
        if ( mode != prevMode ) bp.acquit(); //to reset previus memorised pushed bp
        String pauseRequested = CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_PAUSE );
        if ( pauseRequested == "ON" ){
            if (_state) {
                off();
                writeToJson( JSON_PARAMNAME_PAUSE, "ON" ); // only kept to set _jsonWriteRequest to true
                _pause = true;
                DSPL( dPrompt + F("mise en pause HTML")  );
                return;
            }     
        } else if (_pause){
            on();
            writeToJson( JSON_PARAMNAME_PAUSE, "OFF" );
            _pause = false;
            DSPL( dPrompt + F("sortie de pause par HTML") );
            return;
        }
        CEpsStrTime dureeOn;
        dureeOn = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_ONDURATION ), \
            CEpsStrTime::MMM );
        DSPL(dPrompt + "extracted duree on : " + dureeOn.getStringVal() );
        CEpsStrTime dureeOff;
        dureeOff = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_OFFDURATION ), \
            CEpsStrTime::MMM ); 
        DSPL(dPrompt + "extracted duree off : " + dureeOff.getStringVal() );
        //cyclic mode parameters
        //dureeOn//dureeOff//[hDebut]
        CEpsStrTime hDebut;
        hDebut = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_STARTTIME ), \
            CEpsStrTime::HHMM );
        if ( dureeOn.isValid && dureeOff.isValid ){
            if ( hDebut.isValid ){
                off();
                writeToJson( JSON_PARAMNAME_STARTTIME, hDebut.getStringVal() );
                _nextTimeToSwitch = hDebut.computeNextTime();
            } else {
                on();
                writeToJson( JSON_PARAMNAME_STARTTIME, "" );
                _nextTimeToSwitch = dureeOn.computeNextTime();
            }
            /** @todo [NECESSARY] keep only one writeToJson Call to set _jsonWriteRequest */
            //writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
            //writeToJson( JSON_PARAMNAME_ONDURATION, dureeOn.getStringVal() );
            _dureeOn.setValue( dureeOn.getStringVal() );
            //writeToJson( JSON_PARAMNAME_OFFDURATION, dureeOff.getStringVal() );
            _dureeOff.setValue( dureeOff.getStringVal() ) ;
            _mode = modeId( mode );
            writeToJson( JSON_PARAMNAME_MODE, mode );            
        } else { //onDuration and/or offDuration not valid
            DSPL( dPrompt + "CYCLIC mode : an invalid parameter was found, no change made");
        } 
    } else if ( mode == HEBDO_MODE ){
        DSPL( dPrompt + F("Hebdo mode actions") );
        /////////////////////////////////////////////////////////////////////////////
        //    Compute HEBDO MODE                                                  //
        /////////////////////////////////////////////////////////////////////////////
        //hebdo mode parameters
        //hdebut hFin
        String pauseRequested = CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_PAUSE );
        if ( pauseRequested == "ON" ){
            if (_state) {
                off();
                writeToJson( JSON_PARAMNAME_PAUSE, "ON" );
                _pause = true;
                DSPL( dPrompt + F("mise en pause HTML")  );
                return;
            }     
        } else if (_pause){
            on();
            writeToJson( JSON_PARAMNAME_PAUSE, "OFF" );
            _pause = false;
            DSPL( dPrompt + F("sortie de pause par HTML") );
            return;
        }        
        CEpsStrTime hDebut, hFin;
        hDebut = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_STARTTIME ),\
            CEpsStrTime::HHMM );
         hFin = CEpsStrTime(CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_ENDTIME ),\
            CEpsStrTime::HHMM );   
        if (hDebut.isValid && hFin.isValid ){
            String daysParam[7];
            daysParam[0] = HTMLREQ_SUNDAY;
            daysParam[1] = HTMLREQ_MONDAY;
            daysParam[2] = HTMLREQ_TUESDAY;
            daysParam[3] = HTMLREQ_WEDNESTDAY;
            daysParam[4] = HTMLREQ_THURSDAY;
            daysParam[5] = HTMLREQ_FRIDAY;
            daysParam[6] = HTMLREQ_SATURDAY;
            uint8_t newDayOfWeek = 0;
            for ( int i = 0; i < 7 ; i++ ){
                if ( CServerWeb::extractParamFromHtmlReq( allRecParam, daysParam[i] ) != NOT_FOUND )
                    bitSet ( newDayOfWeek, i );
            }
            //if all is valid
            writeToJson( JSON_PARAMNAME_STARTTIME, hDebut.getStringVal() );
            writeToJson( JSON_PARAMNAME_ENDTIME, hFin.getStringVal() );
            _daysOnWeek = newDayOfWeek;
            writeDaysToJson();
            // prepare data for in or out of bounds test
            DateTime now = CRtc::now();
            int h, m;
            DateTime toDay_hDebut_DT, toDay_hFin_DT;
            sscanf( hDebut.getStringVal().c_str(),"%d:%d", &h, &m);
            toDay_hDebut_DT = DateTime( now.year(), now.month(), now.day(),h,m,0);
            sscanf( hFin.getStringVal().c_str(),"%d:%d", &h, &m);
            toDay_hFin_DT = DateTime( now.year(), now.month(), now.day(),h,m,0);
            DSPL( dPrompt + F("To day H debut : ") + \
                CEpsStrTime::unixTime2String( toDay_hDebut_DT.unixtime() ) ); 
            DSPL( dPrompt + F("To day H fin : ") + \
                CEpsStrTime::unixTime2String( toDay_hFin_DT.unixtime() ) );
            // test if now is in bounds or out of bounds    
            if ( now.unixtime() < toDay_hFin_DT.unixtime() && \
                now.unixtime() > toDay_hDebut_DT.unixtime() && \
                bitRead( _daysOnWeek, now.dayOfTheWeek() ) ){
                on();
                _nextTimeToSwitch = hFin.computeNextTime();
                DSPL( dPrompt + F("In bounds, possible next time : ") + \
                    CEpsStrTime::unixTime2String( _nextTimeToSwitch ) );
            } //current date/time (now) is out of the limits 
            else {
                _nextTimeToSwitch = hDebut.computeNextTime( _daysOnWeek );
                DSPL( dPrompt + F("Out of bounds, possible next time : ") + \
                    CEpsStrTime::unixTime2String( _nextTimeToSwitch ) );
                if ( _state) off(); // confirme off 
            }
            writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
            _mode = modeId( mode );
            writeToJson( JSON_PARAMNAME_MODE, mode );             
        } //not all valid
        else {
            DSPL( dPrompt + "HEBDO mode : an invalid parameter was found, no change made");
        }
    } else if ( mode == CLONE_MODE){//clode mode parameters
        DSPL( dPrompt + F("clone mode actions") );
        /////////////////////////////////////////////////////////////////////////////
        //    Compute CLONE MODE                                                  //
        /////////////////////////////////////////////////////////////////////////////        
        CPowerPlug clonedPlug;
        String clonedPlugName = CServerWeb::extractParamFromHtmlReq( allRecParam, JSON_PARAMNAME_CLONEDPLUG );
        DSPL( dPrompt + "cloned plug find name =  " + clonedPlugName );
        clonedPlug.setPlugName( clonedPlugName );
        // parameters to be cloned : state, pause, mode, hdeb, hfin, don, doff
        // , days and nextTimeToSwitch
        clonedPlug.readFromJson( false ); //to populate clonedPlugName members _mode, _state...
        String clonedParamsNames[CLONEDPARAMNUMBER] = { JSON_PARAMNAME_STARTTIME
                                                       , JSON_PARAMNAME_ENDTIME
                                                       , JSON_PARAMNAME_ONDURATION
                                                       , JSON_PARAMNAME_OFFDURATION
                                                       , JSON_PARAMNAME_STATE
                                                       , JSON_PARAMNAME_PAUSE
                                                       , JSON_PARAMNAME_MODE
                                                       , JSON_PARAMNAME_NEXTSWITCH
                                                       };
        String clonedParamsVal[CLONEDPARAMNUMBER];
        for (int i = 0; i < CLONEDPARAMNUMBER; i++){
            clonedParamsVal[i] = clonedPlug.readFromJson( clonedParamsNames[i] );
        }
        _mode = clonedPlug.getMode();;
        _state = clonedPlug.getState();
        if ( _state ) on(); else off();
        _nextTimeToSwitch = clonedPlug.getNextT2Switch();
        _daysOnWeek = clonedPlug.getDays();
        _pause = clonedPlug.getPause();
        for (int i = 0; i < CLONEDPARAMNUMBER; i++){
            writeToJson(  clonedParamsNames[i], clonedParamsVal[i] );
        }        
        writeDaysToJson();
        writeToJson(  JSON_PARAMNAME_CLONEDPLUG, clonedPlugName );
    } 
}
/** 
fn String CPowerPlug::extractParamFromHtmlReq( String allRecParam, String param )
brief to extract a parameter from all parameter
param allRecParam a concatened String containing all received parameters build in handlePlugOnOff()
param param the parameter to extract
return the value of the parameter or "nf" for not found or "" empty
*/
/*
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

}
*/

/** 
@fn void CPowerPlug::writeToJson( String param, String value )
@brief this function write a parameter to json config file for the _name plug
@param param name of the parameter to be written
@param value the value of the parameter to be written in the json file
@return nothing

Writes value on parma for _plugName plug of course !
*/
void CPowerPlug::writeToJson( String param, String value ){
    DEFDPROMPT( "CPower plug write to jSo (not real write)");
DSPL( dPrompt + _plugName + " : " + param + " with " + value );
    _jsonWriteRequest = true;
    /** done remove below code 29/12/2021 */

}

/** 
 @fn void CPowerPlug::writeDaysToJson()
 @brief Method to write checked day of hebdo mode on json config file
 @return no return value and no parameter

It works on _dayOfWeek member
*/
void CPowerPlug::writeDaysToJson(){
    DEFDPROMPT( "write days to jSon");
    DSPL( dPrompt + F("write needed set to true") );

    _jsonWriteRequest = true;

    /** done remove below code 29/12/2021*/
}

/** 
 @fn void CPowerPlug::switchAtTime()
 @brief after call isItTimeToSwitch, this fucntion switch the plug as needed and...
 @return no return value and no parameter

Compute next time to switch if necessary regardless of _mode
*/
void CPowerPlug::switchAtTime(){
    DEFDPROMPT( "switch at Time");
    String sMode = modes[ _mode ];
    /** @todo this method should use class members intead of readFromJson link to readFromJson usefullness */
    if ( sMode == MANUAL_MODE ){
        off();
        _nextTimeToSwitch = 0;

        _dureeOff.setValue("");
        _dureeOn.setValue("");
        _hDebut.setValue("");
        _hFin.setValue("");

        _jsonWriteRequest = true;
    } else if ( sMode == TIMER_MODE ){
        off();
        _nextTimeToSwitch = 0;
        _jsonWriteRequest = true;
    
    } else if ( sMode == CYCLIC_MODE ){
        CEpsStrTime duree;
        if (_state){
            off();
            duree = (CEpsStrTime)readFromJson( (String)JSON_PARAMNAME_OFFDURATION ); 
        } else { //off state
            if (!_pause){
                on();
                duree = (CEpsStrTime)readFromJson( (String)JSON_PARAMNAME_ONDURATION );   
            } else { //in pause
                duree = (CEpsStrTime)readFromJson( (String)JSON_PARAMNAME_OFFDURATION );
                _pause = false;
                writeToJson( JSON_PARAMNAME_PAUSE, "OFF" );
                DSPL( dPrompt + F("sortie de pause sur mise off") );
            }
        }
        _nextTimeToSwitch = duree.computeNextTime();

    } else if ( sMode == HEBDO_MODE ){
        DSP( dPrompt + F("Hebdo mise") );
        CEpsStrTime nextHour;
        if (_state){
            off();
            DSPL( F("OFF") );
            nextHour = CEpsStrTime(readFromJson( (String)JSON_PARAMNAME_STARTTIME ),\
                CEpsStrTime::HHMM ); 
        } else {
            if (!_pause){            
                on();
                nextHour = CEpsStrTime(readFromJson( (String)JSON_PARAMNAME_ENDTIME ),\
                    CEpsStrTime::HHMM ); 
            } else {
                nextHour = CEpsStrTime(readFromJson( (String)JSON_PARAMNAME_STARTTIME ),\
                    CEpsStrTime::HHMM ); 
                _pause = false;
                writeToJson( JSON_PARAMNAME_PAUSE, "OFF" );
                DSPL( dPrompt + F("sortie de pause sur mise off") );                    
            }
        };
        _nextTimeToSwitch =  nextHour.computeNextTime( _daysOnWeek ); 
    }

    _jsonWriteRequest = true;
}

/** 
 @fn void CPowerPlug::handleBpClic()
 @brief A function that handle action of the push button simple clic
 @return no return value and no parameter
*/
void CPowerPlug::handleBpClic(){
    DEFDPROMPT("handleClic")
    String sMode = getStringMode();
    //DSPL( dPrompt);
    if ( sMode == MANUAL_MODE ){
        if ( _state ) {
            if ( _nextTimeToSwitch )
                switchAtTime(); //force off and reset nt2s
            else off();
        } else on();   
    } else if ( sMode == TIMER_MODE ){
        //restart timer
        //if on just restart timer
        //if off put on and restart timer
        //restart timer is computed with new nextTimeToSwitch
        CEpsStrTime dureeOn;
        dureeOn = (CEpsStrTime)readFromJson( (String)JSON_PARAMNAME_ONDURATION );
        _nextTimeToSwitch = dureeOn.computeNextTime();
        writeToJson( JSON_PARAMNAME_NEXTSWITCH, (String)_nextTimeToSwitch );
        on();
    } else if ( sMode == CYCLIC_MODE || sMode == HEBDO_MODE){
        //when on, a short bp action put plug to off but stay in mode for next time to switch
        //a second action on push button 
        if (_state) {
            off();
            writeToJson( JSON_PARAMNAME_PAUSE, "ON" );
            _pause = true;
            DSPL( dPrompt + F("mise en pause BP")  );
        } else if (_pause){
            on();
            writeToJson( JSON_PARAMNAME_PAUSE, "OFF" );
            _pause = false;
            DSPL( dPrompt + F("sortie de pause par BP") );
        }
    } else {
        DSPL( dPrompt + F("WARNING aucun mode valid !") );
    }
    bp.acquit();    
}
/** 
 @fn void CPowerPlug::handleBpClic()
 @brief A function that handle action of the push button long clic...
 @return no return value and no parameter
 
 All modes return to Manuel mode, plugs is switch to off.
*/
void CPowerPlug::handleBpLongClic(){
    String mode;
    DEFDPROMPT("handleLongClic");
    DSPL( dPrompt );

    bool prevState = _state;
    _state = OFF ;
    updateOutputs( prevState != _state ); //to count only real plug switch  
    _nextTimeToSwitch = 0;
    _pause = false;
    mode = MANUAL_MODE;
    _mode = modeId( mode );
    _daysOnWeek = 0;    

    _jsonWriteRequest = true;
    bp.acquit();    
}

/** 
 @fn void CPowerPlug::handleBpDoubleClic()
 @brief A function that handle action of the push button double clic...
 @return no return value and no parameter
 
 flash led 1 time in mode manual
 2 time in timer
 3 time cycle
 4 time in hebdo mode
 Flash on or flash off regarless of _state attribute
*/
void CPowerPlug::handleBpDoubleClic(){

    DEFDPROMPT( "handleBpDoubleClic");
    if ( !_flashLed ){
        DSPL( dPrompt + F("flash mode : 1 for manual, 2 timer, 3 cyclique, 4 hebdo.") );
        // int flashCounter = _mode + 1 ; unused variable warning
        // if (_state)flashCounter++;
        // onOffFlasher.begin( _onOffLedPin, 100, 500, flashCounter, 3000);
        onOffFlasher.begin( _onOffLedPin, 100, 500, 5, 5000); // a great number (loop that stop flashing)
        // DSPL( dPrompt + F("changt sate cpt : ") + String( onOffFlasher.getChangeStateCpt() ) );
        if ( _state) onOffFlasher.reverseMode();
        _flashLed = true;
    } else {
        onOffFlasher.stop();
        DSPL( dPrompt + F("flash mode : stop.") );
        _flashLed = false;
        _nano.pinMode( _onOffLedPin, OUTPUT );
        _nano.digitalWrite( _onOffLedPin, _state );
    }
    bp.acquit(); 
    
}

/** 
 @fn void CPowerPlug::manageLeds( bool ledState )
 @brief this function switch on or off plug leds (for now only one led)
 @param ledState input state off led
 @return no return
*/
void CPowerPlug::manageLeds( bool ledState ){
    _ledOn = ledState;
    if ( _ledOn ){
        _nano.digitalWrite( _onOffLedPin, _state );
    } else {
        _nano.digitalWrite( _onOffLedPin, LOW );
    }
}
