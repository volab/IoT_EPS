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

class CSysStatus {
    public:
        bool rtcErr = false;
        bool i2cErr = false;
        bool nanoErr = false;
        bool fsErr  = false;
        bool ntpErr = false;
        bool jsoFileErr = false;
        bool credFileErr = false;
        bool confFileErr = false;
        void display();
};

extern CSysStatus sysStatus;

#endif

