/*! 
 * \file SerialCommand.cpp
 * \author Gregg E. Berman
 * \author J.SORANZO (only for adaptations)
 **********************************************************************
 * \copyright 2013-2015 
 *
 * Part of DCC++ BASE STATION for the Arduino
 *********************************************************************
 * reused for Electrical Power Strip (EPS) :
 * all command are suppressed from DCC++
 
 * New command for EPS: for real complete list see SerialCommand::displayCommandsList
 
< C > check DS3231 time

< S > for set DS3231 date, format JJ MM AAAA HH MM SS

< H HH > set DS3231 hours
@todo implement this

< s > for station status and COM connections

return see in the code for all informations.

 @section usage Usage
 Include SerialCommand.h
 @subsection setup in the setup function
 call SerialCommand::init(); 
 @subsection loop In the loop function
 call SerialCommand::process();
 
 */

// DCC++ BASE STATION COMMUNICATES VIA THE SERIAL PORT USING SINGLE-CHARACTER TEXT COMMANDS
// WITH OPTIONAL PARAMTERS, AND BRACKETED BY < AND > SYMBOLS.  SPACES BETWEEN PARAMETERS
// ARE REQUIRED.  SPACES ANYWHERE ELSE ARE IGNORED.  A SPACE BETWEEN THE SINGLE-CHARACTER
// COMMAND AND THE FIRST PARAMETER IS ALSO NOT REQUIRED.

// See SerialCommand::parse() below for defined text commands.

#include "SerialCommand.h"
#include "CRtc.h"
#include "configParam.h"
#include "cEpsStrTime.h"
// #include <Array.h>
// #include <nanoI2CIOExpLib.h>

//for ntp
#include <NTPClient.h>
#include <WiFiUdp.h> 
// #include <TimeLib.h>
#define SECPERHOURS (int)3600

extern int __heap_start, *__brkval;
extern ConfigParam cParam; /**< @brief to display wifi mode non static member ! */
// extern CNanoI2CIOExpander ioexp;

///////////////////////////////////////////////////////////////////////////////

char SerialCommand::commandString[MAX_COMMAND_LENGTH+1];

///////////////////////////////////////////////////////////////////////////////

void SerialCommand::init(){
  sprintf(commandString,"");
} // SerialCommand:SerialCommand

///////////////////////////////////////////////////////////////////////////////

void SerialCommand::process(){
  char c;

    while(INTERFACE.available()>0){    // while there is data on the serial line
        c=INTERFACE.read();
        if(c=='<')                    // start of new command
            sprintf(commandString,"");
        else if(c=='>')               // end of new command
           parse(commandString);                    
        else if(strlen(commandString)<MAX_COMMAND_LENGTH)
        // if comandString still has space, append character
        //just read from serial line
           sprintf(commandString,"%s%c",commandString,c);     // otherwise, character is ignored (but continue to look for '<' or '>')
    } // while

} // SerialCommand:process
   
///////////////////////////////////////////////////////////////////////////////

void SerialCommand::parse(char *com){
    /** @todo remove after debug of nextCheckedDay */
CEpsStrTime hDebut;	
String s;
int h,m, deux, trois, n;
DateTime now;
String date;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "fr.pool.ntp.org");
RTC_DS3231 rtc;
DateTime NTPTime;
bool errNTPinit = true;
//int timeZone = 2; // Paris heure d'été
int timeZone = 1; // Paris heure d'hiver
	
 /** @todo instnaciate command for set Hours, minutes, seconds separatly */
 /** @todo perhaps instanciate other commands to check hardware */
 /** @todo add commands to change and/or display config.json keys */
    switch(com[0]){
		case 'S':
			CRtc::adjust( com+1 );
			break;
        case 's':
        timeClient.begin();
        errNTPinit = !timeClient.forceUpdate();
        timeClient.setTimeOffset( timeZone * SECPERHOURS );
        // setTime(  timeClient.getEpochTime() );
        NTPTime = DateTime( timeClient.getEpochTime() );
        if (!errNTPinit) {
            RTC_DS3231::adjust( NTPTime );
            INTERFACE.println( "Time set :");
            CRtc::displayTime();
        }
            break;
		case 'C':   
			CRtc::displayTime();
			break;
		case 'J': //display config.json
		case 'j':
			ConfigParam::displayJson();
			break;
		case 'E':      // <s>
			INTERFACE.print("<iElectrical Power Strip ");
			// INTERFACE.print(ARDUINO_TYPE);
			INTERFACE.print(": BUILD ");
			INTERFACE.print(__DATE__);
			INTERFACE.print(" ");
			INTERFACE.print(__TIME__);
			INTERFACE.println(", COM TYPE : SERIAL >");
			break;        
		case 'h': 
		case 'H':
			displayCommandsList();
			break;      
		case 'W':
		case 'w':
			cParam.displayWifiMode();
			break;
            /** @todo remove after debug of computeNextTime */
        case 'D':
        case 'd':
        /** @todo remove after debug of the hebdo mode */
            // INTERFACE.println( "Before scaning : " +String(com+1) );
            n = sscanf( com+1,"%d:%d %d", &h, &m, &deux);
            if ( n == 3){  
                hDebut = CEpsStrTime( String(h)+":"+String(m), CEpsStrTime::HHMM );
                // INTERFACE.println( " h debut is "+ hDebut.isValid?"valid":"not valid" );
                if (hDebut.isValid) hDebut.computeNextTime( deux );
            }
            // INTERFACE.println( "after scan : " + String(n) );
        case 't':
        case 'T':
            now = CRtc::now();
            date = (String)now.day() + "/" + (String)now.month() + "/" + (String)now.year();
            INTERFACE.println( date );
            break;
        case 'N':
            //available for next use
            break;
        
 
/***** PRINT CARRIAGE RETURN IN SERIAL MONITOR WINDOW  ****/       
		case ' ':     // < >                
			INTERFACE.println("");
			break;  
	} // switch
}; // SerialCommand::parse

///////////////////////////////////////////////////////////////////////////////

void SerialCommand::displayCommandsList(){
	String list = "Serial Command list :\n";
	list += F("<h> ou <H> display this list\n");
	list += F("<E> display status\n");
	list += F("<C> Check DS3231 date\n");
	list += F("<S JJ/MM/AAAA HH:MM:SS> returns code <O>\n");
    list += F("<s> set DS3231 by NTP server\n");
	list += F("<J> or <j> for display config.json\n");
	list += F("<W> or <w> display WIFI mode\n");
    /** @todo remove after debug of nextCheckedDay */
    list += F("<D or d HH:MM days>\n");
    list += F("<T or t various_param> for code test\n");
    //list += F("<N> \n");
	INTERFACE.print( list );
}


