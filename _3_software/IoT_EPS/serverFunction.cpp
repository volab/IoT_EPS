
// #include "serverFunction.h"
#include "IoT_EPS.h"

extern RTC_DS3231 rtc;

/*
void handleRoot() {
	char temp[400];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;

	snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Jojo Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from Jojo ESP01. ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

		hr, min % 60, sec % 60
	);
	server.send ( 200, "text/html", temp );
}
*/

void handleNotFound() {

	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}

	server.send ( 404, "text/plain", message );

}

void displayTime(){
    String page;
    DateTime now;
    now = rtc.now();
    page = "<html><head>";
    page += "<meta http-equiv='refresh' content='5'/>";
    page += "<title>IoT EPS display Time</title>";
    page += "<style>";
    page += "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }";
    page += "</style></head><body><h1>IoT EPS time!</h1>";
    page += "<a href=\"index.html\">Accueil</a><p>";
    page += (String)now.day() +"/"+(String)now.month()+"/"+(String)now.year()+" ";
    page += (String)now.hour()+":"+(String)now.minute()+":";
    page += (String)now.second();
    page += "</p></body></html>";
    server.send ( 200, "text/html", page );
    
}