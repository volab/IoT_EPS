/**
* @file CRtc.h
* @author J.SORANZO
* @date 25/12/2018
* @copyright 2018 CC0
* @version git versionning
* @brief header file of the class CRtc
*/

#include "IoT_EPS.h"

#ifndef CRTC_HEADER_H
#define CRTC_HEADER_H
// #include <Wire.h>
// #include <RTClib.h>


/**
* @class CRtc CRtc.h
* @brief Simple class to handle Rtc component

*/
class CRtc : public RTC_DS3231
{
public:
	CRtc(){ RTC_DS3231(); }
	bool begin( void );
    bool begin( NTPClient *p_tc );
	static bool initErr; 
	static void displayTime(); /**< @brief a static function to display time in debug screen*/
	static void adjust( char *c );
    static void adjustH( char *c );
    
    //bool isItTimeToUpdate();
    void update();
private:
    unsigned long lastMillis;
    unsigned long _updatesCpt;
    static NTPClient *p_timeClient;
};


#endif

