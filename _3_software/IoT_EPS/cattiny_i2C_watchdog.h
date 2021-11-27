/**
 @file cattiny_i2C_watchdog.h
 @author J.SORANZO
 @date 23/07/2019
 @copyright 2019 CC0
 @version git versionning
 @brief CATtinyI2CWatchdog class header file

Auto implement watchdog instance 
*/


#ifndef _CATTINYI2CWATCHDOG_H
#define _CATTINYI2CWATCHDOG_H

#ifndef WATCHDOGREFRESHPERIOD
#define WATCHDOGREFRESHPERIOD 2 //seconds
#endif



/**
* @class CATtinyI2CWatchdog cattiny_i2C_watchdog.h
* @brief This class is to use with https://github.com/letscontrolit/ESPEasySlaves design

================================================================================================<BR>
ATMEL ATTINY85 PINOUTS used for watchdog purpose<BR>

                         o-\/-+ 
                 Reset  1|    |8  VCC 
     Factory Reset Pin  2|    |7  I2C-SCL to ESP
     (debug) Serial TX  3|    |6  Reset output to ESP
                   GND  4|    |5  I2C-SDA to ESP
                         +----+ 
================================================================================================<BR>

I2C command structure uses one or two bytes:

  < cmd >,[ value ]

Commands below 0x80 are used to write data to register in settings struct

Commands starting at 0x80 are special commands:
 @code {.unparsed}
    Command 0x80 = store settings to EEPROM
    Command 0x81 = reset to factory default settings
    Command 0x82 = set I2C address, factory default = 0x26
    Command 0x83 = set pointer to settings struct for I2C readings
    Command 0x84 = reset statistics counters
    Command 0x85 = simulate (test) watchdog timeout
    Command 0xA5 = reset watchdog timer value to 0
 @endcode

 @code {.cpp}
  unsigned long PID;                        // (B0-3) 4 byte ID, wipes eeprom if missing
  int           Version;                    // (B4/5) Version, change if struct changes, wipes eeprom
  byte          TimeOut;                    // (B6)   Timeout in seconds
  byte          Action;                     // (B7)   Action on timeout, 1 = reset target
  byte          ResetPin;                   // (B8)   Reset output pin to toggle
  byte          Sleep;                      // (B9)   After reset, do nothing for x seconds
  byte          I2CAddress;                 // (B10)  Listen to this I2C Address (0x26 default)
  byte          I2CLoadThreshold;           // (B11)  Threshold for I2C bus load
  byte          ResetCounter;               // (B12)  Seconds counter for WD reset status
  byte          SleepCounter;               // (B13)  Seconds counter for sleep time
  byte          TargetResetCount;           // (B14)  Counts number of target resets
  byte          I2CBusInitCount;            // (B15)  Counts I2C bus init calls
  byte          I2CBusErrorCount;           // (B16)  Counts I2C bus threshold exceptions
  byte          Status;                     // (B17)  Status byte
  byte          LastResetCause;             // (B18)  Last reset cause code 
 @endcode
 
*/

#include <Arduino.h>
#include <Wire.h>

//define adds
#define PID              0
#define VERSION          4
#define TIMEOUT          6
#define ACTION           7
#define RESETPIN         8
#define SLEEP            9
#define I2CADDRESS       10
#define I2CLOADTHRESHOLD 11
#define RESETCOUNTER     12
#define SLEEPCOUNTER     13
#define TARGETRESETCOUNT 14
#define I2CBUSINITCOUNT  15
#define I2CBUSERRORCOUNT 16
#define STATUS           17
#define LASTRESETCAUSE   18


#define PIDVAL0 0x9D //157d
#define PIDVAL1 0x56 //86d
#define PIDVAL2 0x1C
#define PIDVAL3 0X78


//define special commands
#define STORE 0x80 //store settings to EEPROM
#define RESTOREDEFAULT 0x81 //reset to factory default settings
#define SETI2CADD 0x82 //set I2C address, factory default = 0x26
#define SETREADPOINTER 0x83 //set pointer to settings struct for I2C readings
#define RESETSTAT 0x84 //reset statistics counters
#define WDSIMUL 0x85 //simulate (test) watchdog timeout
#define REFRESH 0xA5 //reset watchdog timer value to 0

#define TINYADD 0x26

class CATtinyI2CWatchdog {
    public:
        void begin();
        void refresh();
        void setTimeout( byte val );
        void setSleepTime( byte val );
        void storeEeprom();
        void resetToFactory();
        void setI2Cadd( byte add );
        bool isItTimeTo();
        bool test();
        void setRefreshPeriod( unsigned long val ){ _refreshPeriod = val; }
        /** 
        @brief a method to enable or disable refresh feature
        @param val if true refresh is enable
        */
        void enableRefresh( bool val ){ _refreshEnabled = val; }
        
        /** @todo  [NECESSARY only for lib but not for IoT EPS project]
 - getTimeout<BR>
 - getTimeOutCounter
...        */
        
    private:
        int _readRegister( int add );
        void _writeRegister( int add, int val);
        unsigned long _prevMillis;
        bool _refreshEnabled = true;
        uint8_t _tinyAdd = TINYADD;
        unsigned long _refreshPeriod;
        
};

extern CATtinyI2CWatchdog watchdog;

#endif