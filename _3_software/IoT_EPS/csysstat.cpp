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
 @fn sysError( errGravity_t grav,  gColor_t c1, gColor_t c2)
 @brief Third constructor
 @param grav gavity error (low med high or fatal)
 @param c1 from FastLED library
 @param c3


Use this constructor when gravity is fatal
*/
sysError::sysError( errGravity_t grav,  gColor_t c1, gColor_t c2){
    _displayColor1 = c1;
    _displayColor2 = c2;
    _err = false;
    _gravity = grav;
}

/** 
 @fn void sysError::err( bool errorState )
 @brief to set the error...
 @param errorState true when a error occur
 @return no return alue

When a fatal error is fired...
*/
void sysError::err( bool errorState ){
    /** @todo implement err method */
    _err = errorState;
    if ( _gravity == fatal && _err){
        //do blink c1, c2 color
    }
}




/** 
 @fn void CSysStatus::display()
 @brief Allow to display system status in the console...
 @return no return value and no parameter

Call by SerialComand
*/
void CSysStatus::display(){
    DEFDPROMPT( "System status" );
    DSPL( dPrompt + F("i2c status : ") + (i2cErr.isErr()?"ERROR":"no error") );
    DSPL( dPrompt + F("rtc status : ") + (rtcErr.isErr()?"ERROR":"no error") );
}

CSysStatus sysStatus;