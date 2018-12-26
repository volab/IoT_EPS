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
 
 * New command for EPS:
 
< C > check DS3231 time

< D > for date, format JJ MM AAAA HH MM SS

< H HH > set DS3231 hours

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

extern int __heap_start, *__brkval;


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
  
    switch(com[0]){
		case 'S': 
			// trame.send();
			INTERFACE.print("<S>\n");
			break;
		case 'C':   
			CRtc::displayTime();
			break;
		case 'c':
			// trame.continusSwitch = OFF;
			INTERFACE.print("<c>\n");
			break;
		case 's':      // <s>
/*
 *    returns status messages containing track power status, throttle status, turn-out status, and a version number
 *    NOTE: this is very useful as a first command for an interface to send to this sketch in order to verify connectivity and update any GUI to reflect actual throttle and turn-out settings
 *    
 *    returns: series of status messages that can be read by an interface to determine status of DCC++ Base Station and important settings
 */
			INTERFACE.print("<iElectrical Power Strip ");
			// INTERFACE.print(ARDUINO_TYPE);
			INTERFACE.print(": BUILD ");
			INTERFACE.print(__DATE__);
			INTERFACE.print(" ");
			INTERFACE.print(__TIME__);


			INTERFACE.println(", COM TYPE : SERIAL >");
  
			break;        
		case 'b':      // <b CAB CV BIT VALUE>
			// mRegs->writeCVBitMain(com+1);
			break;      
		case '0':     // <0>
			// digitalWrite(SIGNAL_ENABLE_PIN_PROG,LOW);
			// digitalWrite(SIGNAL_ENABLE_PIN_MAIN,LOW);
			INTERFACE.print("<p0>");
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
	list += F("<s> display status\n");
	list += F("<C> Check DS3231 date\n");
	INTERFACE.println( list );
}


