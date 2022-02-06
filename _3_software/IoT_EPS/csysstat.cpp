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
    /** @todo [NECESSARY] and easy : comment cleaning */
    // if ( _gravity == fatal && _err && !_forceSystemStartOnFatalError ){
    //     for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = CRGB::Black;
    //     FastLED.show();
    //     delay(500);
    //     while (1){ 
    //         for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = _displayColor1;
    //         FastLED.show();
    //         delay(FLASH_ERROR_PERIODE/2);	
    //         for ( int i = 0; i < NBRPLUGS ; i++ ) colorLeds[i] = _displayColor2;
    //         FastLED.show();
    //         delay(FLASH_ERROR_PERIODE/2);			
    //         yield();
    //     }
    // }
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

    /** DONE [NECESSARY] add wifiSoftSoftAPErr and wifiErr with the new sysErrorTable usage
     * it si not necessary to modify this method.
    */
    DSPL( dPrompt + F("display") );
    sysError *sError;

    for ( int i=0; i < NBR_OF_SYSTEM_ERROR; i++){
        sError = sysErrorTable[i];
        DSPL( dPrompt + sError->getMsg() + " : " + (sError->isErr()?"ERROR":"no error") );
    }
    DSPL( dPrompt + F("System global error : ") + (isSystemok()?"OK":"ErrOr") );
    DSPL( dPrompt + F("Number of fatal error : ") + String( isThereFatalError() ));
}


/** 
 @fn bool CSysStatus::isSystemok()
 @return true if system has no error at all.


*/

/* [NECESSARY] obsolete method same as howManyError but keep for now...*/
bool CSysStatus::isSystemok(){
    bool result = true;
    sysError *sError;
    _fatalErrorCpt = 0;
    
    for ( int i=0; i < NBR_OF_SYSTEM_ERROR; i++){
        sError = sysErrorTable[i];
        result = result && !( sError->isErr() );
        if ( sError->isErr() && sError->getGravity() == sysError::fatal ) _fatalErrorCpt++;
    }  

    /** DONE [NECESSARY] add wifiSoftSoftAPErr and wifiErr (not necessary with sysErrorTable*/
    return result;
}

int8_t CSysStatus::isThereFatalError(){ 
    isSystemok(); // to update the counter
    return _fatalErrorCpt; 
}

/** 
 @fn int8_t CSysStatus::howManyError()
 @return The number of error.

Method developped specially for oled display
*/
int8_t CSysStatus::howManyError(){
    int8_t cpt = 0;

    sysError *sError;
    for ( int i=0; i < NBR_OF_SYSTEM_ERROR; i++){
        sError = sysErrorTable[i];
        if (sError->isErr() ) cpt++;
    } 
    return cpt;
}

String CSysStatus::getMsg( int8_t n){
    DEFDPROMPT("Csystatus getMsg")
    int8_t cpt = 0;
    sysError *sError;
    int i;
    for ( i=0; i < NBR_OF_SYSTEM_ERROR; i++){
        sError = sysErrorTable[i];
        if (sError->isErr() ) cpt++;
        if (cpt == n) break;
    }
    // DSPL( dPrompt  + F("En erreur: ") + String(i) );
    return sysErrorTable[i]->getMsg();
    /** DONE [NECESSARY] add wifiSoftSoftAPErr and wifiErr  not necessayr with new sysErrorTable */

    /** DONE [NECESSARY] best way to return error message will be to creat an array in howmanyError
     * method and find it here */




}

CSysStatus sysStatus;