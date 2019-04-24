/**
 @file _fileName_cpp_or_h
 @author J.SORANZO
 @date _date
 @copyright 2019 CC0
 @version git versionning
 @brief _briefText
*/

// #include "csysstat.h"
#include "IoT_EPS.h"

void CSysStatus::display(){
    DEFDPROMPT( "System status" );
    DSPL( dPrompt + F("i2c status : ") + (i2cErr?"ERROR":"no error") );
    DSPL( dPrompt + F("rtc status : ") + (rtcErr?"ERROR":"no error") );
}

CSysStatus sysStatus;