/**
 @file csysstat.h
 @author J.SORANZO
 @date 24/04/2019
 @copyright 2019 CC0
 @version git versionning
 @brief CCsysStatt class header file
*/

#ifndef CSYSSTAT_H
#define CSYSSTAT_H
#include <FastLED.h>

class sysError {
    public:
        typedef CRGB::HTMLColorCode gColor_t;
        enum  errGravity_t { low, medium, high, fatal };
        sysError(){ _err = false; };
        sysError( errGravity_t grav ){ _err = false; _gravity = grav; };
        sysError( errGravity_t grav,  gColor_t c1, gColor_t c2);
        void err( bool errorState );
        bool isErr(){ return _err; }
        
    private:
        bool _err = false;
        errGravity_t _gravity = low;
        gColor_t _displayColor1 = CRGB::Black;
        gColor_t _displayColor2 = CRGB::Black;
};

class CSysStatus {
    public:
        // CSysStatus();
        sysError rtcErr;
        sysError i2cErr;
        sysError nanoErr;
        sysError fsErr;
        sysError confFileErr;
        /** 
         @fn CSysStatus::CSysStatus()
         @brief CSysSattus constructor...
         @return no return value and no parameter

        Allow to creat and initialize erros variables
        */
        CSysStatus():
              nanoErr( sysError::fatal, CRGB::RoyalBlue, CRGB::Black )
            , rtcErr( sysError::fatal, CRGB::Brown, CRGB::Black )
            , i2cErr( sysError::fatal, CRGB::Red, CRGB::Black )
            , fsErr( sysError::fatal, CRGB::Red, CRGB::Blue )
            , confFileErr( sysError::fatal, CRGB::Red, CRGB::Yellow )
            
            {
            
        }

        // sysError *nanoErr = new sysError( sysError::fatal, CRGB::RoyalBlue, CRGB::Black);
        
        
        bool ntpErr = false;
        bool jsonFileErr = false;
        bool credFileErr = false;
        
        bool wifiErr = false;
        sysError internetErr;
        void display();
       
    private:

};

extern CSysStatus sysStatus;

#endif

