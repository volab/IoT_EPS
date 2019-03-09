/**
* @file cEpsStrTime.cpp
* @author J.SORANZO
* @date
* @copyright 2018 CC0
* @version git versionning
* @brief Implementation file for CEpsStrTime class

*/

#include "IoT_EPS.h"
// #include "cEpsStrTime.h"
// #include "debugSerialPort.h"
#include <ctype.h>


/** 
@fn CEpsStrTime::CEpsStrTime( String val )
@brief second constructor that set the value, check validity and convert to seconds
@param val Time value as String
@return nothing of course
*/
CEpsStrTime::CEpsStrTime( String val ){
    setValue( val );
}

CEpsStrTime::CEpsStrTime( String val, Mode_t mode ){
	_mode = mode; 
    setValue( val );
}

/** 
@fn void CEpsStrTime::setValue( String val )
@brief Set the string time value, check validity and convert to seconds
@param val the String time value
@return nothing
*/
void CEpsStrTime::setValue( String val ){
    _sValue = val;
    isValid = checkValidity();
}
    
/** 
@fn bool CEpsStrTime::checkValidity()
@brief Check Stirng time validity and convert in seconds
@return false if wrong input and _seconds = -1
*/
bool CEpsStrTime::checkValidity(){
	int pos;
    DEFDPROMPT( "CEpsStrTime::checkValidity")
    _seconds = -1;
    isValid = false;
	if ( _sValue == NOT_FOUND \
		|| _sValue == HTML_OFFDURATION_DEFAULT_VALUE \
		|| _sValue == HTML_ENDTIME_DEFAULT_VALUE		){
	   return isValid;
	}
	pos = _sValue.indexOf( TIME_STRING_SEPARATOR );
	if (_mode == MMMSS ){
		int minutes = 0;
		DSPL( dPrompt +"MMM:SS mode check");
		if (pos != -1 ){ //mmm:ss possible form 
		
			String sTmp = _sValue.substring( 0, pos );
			sTmp.trim();
			if (sTmp.length() > 3) return isValid; //max 3 digits
			/** @warning Warning if Minutes max value becomes > 999*/
			minutes = sTmp.toInt();
			DSPL( dPrompt + F("minutes : ") + sTmp );
			sTmp = _sValue.substring( pos +1 );
			sTmp.trim();
			_seconds = sTmp.toInt();
			if (sTmp.length() >  2 || _seconds > 59 || _seconds < 0 ){
				_seconds = -1;
				return isValid;
			}
			_seconds = minutes*60 + _seconds;
		} else { //mmm only possible form
			if (_sValue.length() > 3) return isValid; //max 3 digits)
			for (char c : _sValue) if( !isdigit(c) ) return isValid;
			_seconds = 60 * _sValue.toInt();
		}
		DSPL( dPrompt + F("Secondes converties : ") + _seconds );
		// if (_seconds > (_maxDuration*60) && _mode == MMMSS){
		if (_seconds > (_maxDuration*60) ){
			_seconds = -1;
			return isValid;
		}
		isValid = true;
		return isValid;		
	} else if ( _mode == HHMM ){ //HH:MM mode
		DSPL( dPrompt +"HH:MM mode check");
		if ( pos == -1 )return isValid; //check presence of :
        // DSPL( dPrompt + F("after pos check") );
		if ( _sValue.length() > 5 ) return isValid; // max 5 digits
        // DSPL( dPrompt + F("after length") );
		int h, m;
		if (sscanf( _sValue.c_str(), "%d:%d", &h,  &m) !=2 ) return isValid;
        // DSPL( dPrompt + F("after scan check") );
		if (h > 23 && m > 59)return isValid;
		isValid = true;
        _seconds = h * 3600 + m * 60;
		DSPL( dPrompt + h + " hours and " + m + " minutes.");
		return isValid;
	} else { //MMM only mode
        DSPL( dPrompt +"MMM mode check");
        if ( pos != -1 ) return isValid; // no ':' allowed
        // DSPL(dPrompt + F("After pos check") );
        if ( _sValue.length() > 3 ) return isValid; // max 3 digits
        // DSPL(dPrompt + F("After length check") );
        for (char c : _sValue) if( !isdigit(c) ) return isValid;
        // DSPL(dPrompt + F("After digit check") );
        if ( _sValue.toInt() > _maxDuration ) return isValid;
        DSPL(dPrompt + F("After duraction check") );
        _seconds = _sValue.toInt() * 60;
		isValid = true;
		return isValid;        
    }

}

/** 
@fn uint32_t  CEpsStrTime::computeNextTime()
@brief calculate next time to switch the plug

@return unix time form

*/
uint32_t  CEpsStrTime::computeNextTime( uint8_t CheckedDays ){
    String s_daysOfTheWeek[7] = { "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
    DEFDPROMPT( "CEpsStrTime::computeNextTime" );
	uint32_t future = CRtc::now().unixtime();
    String page = "";
    displayUnixTime( future );
	if ( _mode == MMMSS || _mode == MMM){
		future += _seconds;		
	} else if ( !CheckedDays ) { //HH:MM mode
		int h, m;
		DateTime now = CRtc::now();
		sscanf( _sValue.c_str(), "%d:%d", &h,  &m);
		DateTime futurDT = DateTime( now.year(), now.month(), now.day(), h, m);
        // heure calculée est antérieur. Exemple il est 16:00 et on veut arrêter à 06:00
		if ( futurDT.unixtime() < now.unixtime() ) futurDT = futurDT + TimeSpan( 1, 0, 0, 0);
		future = futurDT.unixtime();
	} else {/* //HH:MM with day of week */
    // <d 18:00 63>
        DateTime now = CRtc::now();
        uint8_t nextDay = nextCheckedDay( CheckedDays, now.dayOfTheWeek() );
        int h, m;
        sscanf( _sValue.c_str(), "%d:%d", &h,  &m);
        DateTime futurDT = DateTime( now.year(), now.month(), now.day(), h, m);
        futurDT = futurDT + TimeSpan( nextDay, 0, 0, 0);
        // computed date is before current (in other words computed is in the past).
        //Example it is 16:00 and we want to stop at 06:00
		if ( futurDT.unixtime() < now.unixtime() ) {
            nextDay = nextCheckedDay( CheckedDays, now.dayOfTheWeek()+1 );
            futurDT = futurDT + TimeSpan( nextDay+1, 0, 0, 0);
        }
        future = futurDT.unixtime();
        DSPL( dPrompt + F("HH:MM mode with day of week") );
        DSPL( dPrompt + F("To day is ") + (String)now.dayOfTheWeek() +\
            F(" in other words : ") + s_daysOfTheWeek[ now.dayOfTheWeek() ] );
    }
	page = "future = ";
	page += unixTime2String( future );
	DSPL( dPrompt + page );  
	return future;
}

/** 
@fn void CEpsStrTime::displayUnixTime()
@brief A function to dsiplay in debug consol the time in a human readable form
@param time2Display the inpput time in unix form
@return nothing
*/
void CEpsStrTime::displayUnixTime( uint32_t time2Display ){
    DEFDPROMPT( "disp. time : ");
    String sDate = unixTime2String( time2Display );
    DSPL( dPrompt + sDate );
}


/** 
@fn String CEpsStrTime::unixTime2String( uint32_t time2Display )
@brief Converts a unix time to a human readable string
@param time2Display must be in unix time 
@return String in french format jj/mm/aaaa hh:mm:ss
*/
String CEpsStrTime::unixTime2String( uint32_t time2Display ){
    DateTime now = DateTime( time2Display );
    String sDate = "";
    // uint8_t day = now.dayOfTheWeek();
// switch ( day ){
	// case 0: sDate = HTMLREQ_SUNDAY;	break;
	// case 1: sDate = HTMLREQ_MONDAY  break;
	// case 2: sDate = HTMLREQ_TUESDAY  break;
	// case 3: sDate = HTMLREQ_WEDNESTDAY  break;
	// case 4: sDate = HTMLREQ_THURSDAY  break;
	// case 5: sDate = HTMLREQ_FRIDAY  break;
	// case 6: sDate = HTMLREQ_SATURDAY  break;
// }
    String daysParam[7];
    daysParam[0] = HTMLREQ_SUNDAY;
    daysParam[1] = HTMLREQ_MONDAY;
    daysParam[2] = HTMLREQ_TUESDAY;
    daysParam[3] = HTMLREQ_WEDNESTDAY;
    daysParam[4] = HTMLREQ_THURSDAY;
    daysParam[5] = HTMLREQ_FRIDAY;
    daysParam[6] = HTMLREQ_SATURDAY;
    sDate = daysParam[ now.dayOfTheWeek() ] + " ";
    sDate += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    sDate += (String)now.hour()+":"+(String)now.minute()+":";
    sDate += (String)now.second();
    return sDate;    
}

/** 
 @fn uint8_t CEpsStrTime::nextCheckedDay( uint8_t days, uint8_t day )
 @brief a private methode to find the first next checked day...
 @param days a byte that's represente checked day (one bit/day start at bit0 for sunday)
 @param day The number of the current day (Sunday = 0)
 @return number of days between current day and the next checked day in the week.
 0 meens that is the same day

This method is write for hebdo mode to find in number of days between current day and the next
checked day.

Checked days are coded on a byte with bit 0 reprensent sunday and bit 6 the saturday. Of course
1 in the bit meens that the corresponding day is checked.
*/
// test paterns
// <d 18:15 6 2>
uint8_t CEpsStrTime::nextCheckedDay( uint8_t days, uint8_t day ){
    uint8_t returnVal;
    DEFDPROMPT( "nextCheckDay");
    DSPL( dPrompt + F("inputs : ") + String(days, BIN) + F(" days and day : ") + day );
    int i;
    for ( i = day; i <= 6 ; i++) if ( bitRead(days, i) ) break;
    if ( i == 7 ) for ( i = 0; i < day; i++ ) if ( bitRead(days, i) ) break;
    // DSPL( dPrompt + F("i = ") + String(i) );
    returnVal = (i<day) ? (7-day+i) : (i-day);
    DSPL(dPrompt + F("return value : ")+ String(returnVal) );
    return  returnVal;
}
    
    