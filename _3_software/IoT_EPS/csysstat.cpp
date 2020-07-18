/**
 @file csysstat.cpp
 @author J.SORANZO
 @date 05/2019
 @copyright 2019 CC0
 @version git versionning
 @brief implementation file of CSysStatus class
*/

// #include "csysstat.h"
#include "IoT_EPS.h"


/** 
 @fn sysError::sysError( errGravity_t grav,  gColor_t c1, gColor_t c2, String errMsg)
 @brief Third constructor
 @param grav gavity error (low med high or fatal)
 @param c1 color 1 from FastLED library
 @param c2 color 2
 @param errMsg Error message


Use this constructor when gravity is fatal
*/
sysError::sysError( errGravity_t grav,  gColor_t c1, gColor_t c2, String errMsg){
    _displayColor1 = c1;
    _displayColor2 = c2;
    _err = false;
    _gravity = grav;
    _errMsg = errMsg;
    _forceSystemStartOnFatalError = true;
}

/** 
 @fn void sysError::err( bool errorState )
 @brief to set the error...
 @param errorState true when a error occur
 @return no return alue

When a fatal error is fired...
*/
extern CRGB colorLeds[];
void sysError::err( bool errorState ){
    DEFDPROMPT( "System error handler")
    _err = errorState;
    if (_err) DSPL( dPrompt + _errMsg );
    if ( _gravity == fatal && _err && !_forceSystemStartOnFatalError ){
        for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
        FastLED.show();
        delay(500);
        while (1){ 
            for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = _displayColor1;
            FastLED.show();
            delay(FLASH_ERROR_PERIODE/2);	
            for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = _displayColor2;
            FastLED.show();
            delay(FLASH_ERROR_PERIODE/2);			
            yield();
        }
    }
}

void CSysStatus::initCBITTimer(){
    _prevMillisCbit = millis();
}


bool CSysStatus::isCbitTime(){
    if ( millis() - _prevMillisCbit < CBIT_TIME ) return false;
    _prevMillisCbit = millis();
    return true;
}

/** 
 @fn void CSysStatus::display()
 @brief Allow to display system status in the console...
 @return no return value and no parameter

Call by SerialComand
*/
void CSysStatus::display(){
    DEFDPROMPT( "System status" );
    DSPL( dPrompt + fsErr.getMsg() + " : " + (fsErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + nanoErr.getMsg() + " : " + (nanoErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + rtcErr.getMsg() + " : " + (rtcErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + confFileErr.getMsg() + " : " + (confFileErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + credFileErr.getMsg() + " : " + (credFileErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + filesErr.getMsg() + " : " + (filesErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + plugParamErr.getMsg() + " : " + (plugParamErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + ntpErr.getMsg() + " : " + (ntpErr.isErr()?"ERROR":"no error") );
    
}

CSysStatus sysStatus;