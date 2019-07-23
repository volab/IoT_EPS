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

//==============================================================================================================
// ATMEL ATTINY85 PINOUTS used for watchdog purpose
//                          o-\/-+ 
//                  Reset  1|    |8  VCC 
//      Factory Reset Pin  2|    |7  I2C-SCL to ESP
//      (debug) Serial TX  3|    |6  Reset output to ESP
//                    GND  4|    |5  I2C-SDA to ESP
//                          +----+ 
//==============================================================================================================

// I2C command structure uses one or two bytes:
// 
//   <cmd>,[value]
//
// Commands below 0x80 are used to write data to register in settings struct
//
// Commands starting at 0x80 are special commands:
// Command 0x80 = store settings to EEPROM
// Command 0x81 = reset to factory default settings
// Command 0x82 = set I2C address, factory default = 0x26
// Command 0x83 = set pointer to settings struct for I2C readings
// Command 0x84 = reset statistics counters
// Command 0x85 = simulate (test) watchdog timeout
// Command 0xA5 = reset watchdog timer value to 0
//
*/


class CATtinyI2CWatchdog {
    public:
        void begin();
        void refresh();
        void setTimeout( byte val );
        void setSleepTime( byte val );
        void storeEeprom();
        void resetToFactiory();
        void setI2Cadd( byte add );
        bool isItTimeTo();
        
        /** @todo 
getTimeout
getTimeOutCounter
...        */
        
    private:
        int _readRegister( int add );
        void _writeRegister( int add, int val);
        unsigned long _prevMillis;
        
};

extern CATtinyI2CWatchdog watchdog;

#endif