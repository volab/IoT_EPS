/**
* @file SerialCommand.h
* @author J.SORANZO for the adaptations
* @date
* @copyright COPYRIGHT (c) 2013-2015 Gregg E. Berman
* @version 1.0
* @brief header file for SerialCommand structure

This is part of Part of DCC++ BASE STATION for the Arduino
 
*/

/**********************************************************************
SerialCommand.h
COPYRIGHT (c) 2013-2015 Gregg E. Berman
**********************************************************************/

#ifndef SerialCommand_h
#define SerialCommand_h

//VoLAB add - 2018:07
#include "Arduino.h"

#define INTERFACE Serial /**< @brief Only for SerialCommand usage*/

#define  MAX_COMMAND_LENGTH         30
//<D JJ MM AAAA HH MM SS>
//1234567890123456789012345

struct SerialCommand{
  static char commandString[MAX_COMMAND_LENGTH+1];
  static void init();
  static void parse(char *);
  static void process();
  static void displayCommandsList();
}; // SerialCommand
  
#endif




