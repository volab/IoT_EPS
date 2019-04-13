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
#include <nanoI2CIOExpLib.h>
#include <ESP8266WiFi.h>
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

void i2c_scan();
void i2c_recovery();
void i2c_plantoir();

#define SDAPIN D2
#define CLKPIN D1
#define SCL D1
#define SDA D2

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
// CEpsStrTime hDebut;	
String s;
String key,value;
char k[40];
char v[40];
int h,m, deux, trois, n;
DateTime now;
String date;

CNanoI2CIOExpander nanoI2C;
bool nineState;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "fr.pool.ntp.org");
RTC_DS3231 rtc;
DateTime NTPTime;
bool errNTPinit = true;
int timeZone = 2; // Paris heure d'été
// int timeZone = 1; // Paris heure d'hiver

nanoI2C.pinMode( 9, OUTPUT );
//nanoI2C.pinMode( 8, INPUT_PULLUP );
int eightState;
	
 /** @todo perhaps instanciate other commands to check hardware */
 //ABDGKLMQUVXYZ
 //bdefgjklmnpqruvxyz 
    switch(com[0]){
		case 'C':   
			CRtc::displayTime();
			break;
		case 'E':      // 
			INTERFACE.print("<iElectrical Power Strip ");
			// INTERFACE.print(ARDUINO_TYPE);
			INTERFACE.print(": BUILD ");
			INTERFACE.print(__DATE__);
			INTERFACE.print(" ");
			INTERFACE.print(__TIME__);
			INTERFACE.println(", COM TYPE : SERIAL >");
			break;
        case 'F': //Find I2C
            i2c_scan();
            break; 
		case 'h': 
		case 'H':
			displayCommandsList();
			break;
         case 'I': //I for wifi Id
            n = sscanf( com+1,"%s", v );
            if ( n == 1){
                value = String(v);
                INTERFACE.println("new SSID : " + value);
                ConfigParam::chgSSID( value );
            } else {
                INTERFACE.println("Warning this command riquires only ONE parameter !");
            }
            break;
		case 'J': //display config.json
			ConfigParam::displayJson();
			break;
        case 'N': //nano I2C IO expander test
            nanoI2C.test();
            break;
        case 'O': //nano I2C IO expander test
            INTERFACE.println("D11 out test HIGH");           
            nanoI2C.digitalWrite( 9, HIGH );
            break;
        case 'P': //P for parameter
            n = sscanf( com+1,"%s %s", k, v );
            if ( n == 2){
                key = String(k);
                value = String(v);
                INTERFACE.println("Parametres : " + key + " value : " + value);
                ConfigParam::write2Json( key, value );
            } else {
                INTERFACE.println("Warning this command riquires 2 parameters !");
            }
            break;
        case 'R': //recovery I2C         
            i2c_recovery();
            break;             
		case 'S':
			CRtc::adjust( com+1 );
			break;
		case 'T':
			CRtc::adjustH( com+1 );
			break;
		case 'W':
			cParam.displayWifiMode();
			break;
            
        case 'a': //recovery I2C         
            INTERFACE.print("IP add = ");
            INTERFACE.println( WiFi.localIP().toString() );
            INTERFACE.print("softAP IP add = ");
            INTERFACE.println( WiFi.softAPIP().toString() );
            break; 
        case 'c': //recovery I2C         
            i2c_plantoir();
            break;
        case 'i': //i for wifi pass
            n = sscanf( com+1,"%s", v );
            if ( n == 1){
                value = String(v);
                INTERFACE.println("new pass : " + value);
                ConfigParam::chgWifiPass( value );
            } else {
                INTERFACE.println("Warning this command riquires only ONE parameter !");
            }
            break;            
        case 'o': //nano I2C IO expander test
            INTERFACE.println("D11 out test low");           
            nanoI2C.digitalWrite( 9, LOW );
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
        case 't':
            now = CRtc::now();
            date = (String)now.day() + "/" + (String)now.month() + "/" + (String)now.year();
            INTERFACE.println( date );
            break;

        case 'w' : //for WiFi.diagFunction     
            WiFi.printDiag(Serial);
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
    list += F("<T HH:MM:SS> returns code <O>\n");
    list += F("<s> set DS3231 by NTP server\n");
	list += F("<J> for display config.json\n");
	list += F("<W> display WIFI mode\n");
    list += F("<P key value> write config parameter in json WARNING\n");
    list += F("<I _newSSID> write SSID in credentials WARNING\n");
    list += F("<i _wifiPass> write SSID password in credentials WARNING\n");
    list += F("<t various_param> for code test\n");
    list += F("<N> nano IO expander test\n");
    list += F("<O> nano out test HIGH\n");
    list += F("<o> nano out test low\n");
    list += F("<F> Find I2C device I2C scan\n");
    list += F("<R> I2C recovery\n");
    list += F("<c> I2C crash\n");
    list += F("<a> for Ip address\n");
    list += F("<w> for WiFi.printDig function\n");
	INTERFACE.print( list );
}

void i2c_scan(){
    INTERFACE.println( F("Scanning (SDA : SCL) - D2 : D1") );
    byte error;
    for (int address = 1; address < 127; address++ )  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0){
            INTERFACE.print("I2C device found at address 0x");
            if (address < 16) INTERFACE.print("0");
            INTERFACE.print(address, HEX);
            INTERFACE.println("  !");
            // nDevices++;
        } else if (error == 4) {
            INTERFACE.print("Unknow error at address 0x");
            if (address < 16) INTERFACE.print("0");
            INTERFACE.println(address, HEX);
        }
    } 
}

void i2c_plantoir(){
    Serial.println("Starting I2C crach");
    //try i2c bus recovery at 100kHz = 5uS high, 5uS low
    pinMode(SDAPIN, OUTPUT);//keeping SDA high during recovery
    digitalWrite(SDAPIN, HIGH);
    pinMode(CLKPIN, OUTPUT);
    for (int i = 0; i < 10; i++) { //9nth cycle acts as NACK
        digitalWrite(CLKPIN, HIGH);
        delayMicroseconds(5);
        digitalWrite(CLKPIN, LOW);
        delayMicroseconds(5);
    }

    //a STOP signal (SDA from low to high while CLK is high)
    digitalWrite(SDAPIN, LOW);
    delayMicroseconds(5);
    digitalWrite(CLKPIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(SDAPIN, HIGH);
    delayMicroseconds(2);
    //bus status is now : FREE

    Serial.println("bus recovery done, you can start a scan");
    //return to power up mode
    pinMode(SDAPIN, INPUT);
    pinMode(CLKPIN, INPUT);
    delay(1000);
    //pins + begin advised in https://github.com/esp8266/Arduino/issues/452
    // Wire.pins(SDAPIN, CLKPIN); //this changes default values for sda and clock as well
    // Wire.begin(SDAPIN, CLKPIN);
    Wire.begin();
    //only pins: no signal on clk and sda
    //only begin: no signal on clk, no signal on sda
    // code above dosen't work
      
}

void i2c_recovery(){
    
    Serial.println("Starting I2C bus recovery");
    delay(2000);
  pinMode(SDA, OUTPUT); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, OUTPUT);
  digitalWrite( SDA, LOW );
  digitalWrite( SCL, LOW );
  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master. 
  INTERFACE.println("I2C bus error SCL is low ! Error 1");
    // return 1; //I2C bus error. Could not clear SCL clock line held low
    return ;
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
    INTERFACE.println("I2C still low after 2 sec error ! Error 2");
      // return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
      return;
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
  INTERFACE.println("I2C SDA still low  ! Error 3");
    // return 3; // I2C bus error. Could not clear. SDA data line held low
    return;
  }
INTERFACE.println("Recovery ends with no known error");
  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  
  Wire.begin();
  // return 0; // all ok   
return;  
}




