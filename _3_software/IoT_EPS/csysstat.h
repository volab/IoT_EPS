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
        // sysError( errGravity_t grav ){ _err = false; _gravity = grav; };
        sysError( errGravity_t grav, String s ){ _err = false; _gravity = grav; _errMsg = s; };
        // sysError( errGravity_t grav,  gColor_t c1, gColor_t c2);
        sysError( errGravity_t grav,  gColor_t c1, gColor_t c2, String s);
        void err( bool errorState );
        bool isErr(){ return _err; }
        String getMsg(){ return _errMsg; }
        bool _forceSystemStartOnFatalError; /**< @brief for debug purpose only, prevent system
        to blink big led and stay in this loop indefinitly        */
        
    private:
        bool _err = false;
        errGravity_t _gravity = low;
        gColor_t _displayColor1 = CRGB::Black;
        gColor_t _displayColor2 = CRGB::Black;
        String _errMsg;
        
};

class CSysStatus {
    public:
        /** 
         @fn CSysStatus::CSysStatus()
         @brief CSysSattus constructor...
         @return no return value and no parameter

        Allow to creat and initialize erros variables
        */
        CSysStatus():
              fsErr( sysError::fatal, CRGB::Red, CRGB::Black, "File system error" )
            , nanoErr( sysError::fatal, CRGB::Red, CRGB::Blue, "Nano error" )
            , rtcErr( sysError::fatal, CRGB::Brown, CRGB::Black, "DS3231 error" ) 
            , confFileErr( sysError::fatal, CRGB::Red, CRGB::Yellow, "Config file error" )
            , credFileErr( sysError::medium, "Credential error" )
            , filesErr( sysError::fatal, CRGB::OrangeRed, CRGB::Black, "Necessary files error" )
            , plugParamErr( sysError::fatal, CRGB::Red, CRGB::Snow, "Plug's file error"  )
            , ntpErr( sysError::low, "NTP error")
            , internetErr( sysError::fatal, CRGB::RoyalBlue, CRGB::OrangeRed, "Internet access error" )
            , watchdogErr( sysError::fatal, CRGB::Snow, CRGB::Black, "watchdog error")
            {
            
        }
        // CSysStatus();
        sysError fsErr;
        sysError nanoErr;
        sysError rtcErr;
        // sysError i2cErr;
        sysError confFileErr; //config4.json gen parma part error
        sysError credFileErr;
        sysError filesErr;
        sysError plugParamErr;
        sysError ntpErr;
        sysError internetErr;
        sysError watchdogErr;


        // sysError *nanoErr = new sysError( sysError::fatal, CRGB::RoyalBlue, CRGB::Black);
        
        
        // bool ntpErr = false;
        // bool jsonFileErr = false;
        // bool credFileErr = false;
        
        bool ntpEnabled = false; //set to true when Station mode is ok
        bool wifiErr = false;
        
        void display();
        
        void initCBITTimer();
        bool isCbitTime();

        /**  @brief Return anded global system state */
        bool isSystemok();
       
    private:
        unsigned long _prevMillisCbit;
};

extern CSysStatus sysStatus;

#endif

