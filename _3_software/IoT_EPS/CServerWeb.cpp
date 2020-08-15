/**
 @file CServerWeb.cpp
 @author J.SORANZO
 @date 15/08/2020
 @copyright 2020 CC0
 @version git versioning
 @brief Implementation file of CServerWeb class
*/
#include "CServerWeb.h"



//A global variable need by ESP8266WebServer
//extern ESP8266WebServer *server; //a pointeur that allow change the port dynamicly

CServerWeb::CServerWeb(/* args */)
{
}

CServerWeb::~CServerWeb()
{
}


/**
@fn CServerWeb::init()
@brief Iot_EPS web server initialisation method
@param prtc a class RTC pointer
@return no return value
*/
void CServerWeb::init( CRtc * prtc, ConfigParam *pcParam, CPowerPlug *pPlugs
                        , bool *restartTempoLed ){
    //big warning if _rtc is initialised with a local variable !!!!
    _pRtc = prtc;
    _pcParam = pcParam;
    _pPlugs = pPlugs;
    mainPowerSwitchState = 0;
    _pRestartTempoLed = restartTempoLed;
    // server = new ESP8266WebServer( 80 );
    server = new ESP8266WebServer( _pcParam->getServerPort() );

    //Register handlers in the web server
    server->on( "/time", std::bind(&CServerWeb::displayTime, this) );
    server->on("/list", HTTP_GET, std::bind(&CServerWeb::handleFileList, this) );
    server->on("/plugonoff", HTTP_POST,std::bind(&CServerWeb::handlePlugOnOff, this) ); 
    server->onNotFound( std::bind(&CServerWeb::notFoundHandler, this) );
    // server->on("/help", HTTP_GET, [](){
	// // 		if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
	// // 	});
    server->on("/help", HTTP_GET, std::bind(&CServerWeb::handleHelp, this) );
	// 		if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
	// 	});

    server->begin();
}

/**
@fn CServerWeb::notFoundHandler()
@brief Web server page not found handler function
@return no param and return value
*/
void CServerWeb::notFoundHandler(){
    if(!handleFileRead(server->uri()))
        server->send(404, "text/plain", "IoTEPS : FileNotFound");   
}

/**
@fn CServerWeb::serviceClient()
@brief Web server client handle
@return not param and no return value

Just a wrapper on the official method to be called from main program
*/
void CServerWeb::serviceClient(){
    DEFDPROMPT("ServiceWeb");
    // DSPL( dPrompt );
    server->handleClient();
}


// can't have parameters like rtc caus it is used as a callback function in 
// server->on
void CServerWeb::displayTime(){
    String page;
    DateTime now;
    // now = rtc.now();
    if ( _pRtc == NULL )return;

    now = _pRtc->now();
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

    server->send ( 200, "text/html", page );

    
}

/**
@fn CServerWeb::handlePlugOnOff()
@brief IoT_EPS web server handel plug on or off actions...
@return not param and no return value

This method handel request that come from client web browser in the form:
192.168.1.42/plugonoff?COLOR=redPlug&Mode=Manuel&State=ON

Possible requests:

- Mode=Manuel&State=ON&dureeOff=299 : dureeOff on minutes only
- Mode=Manuel&State=ON&dureeOff=299:59 : dureeOff on minutes and seconds
- Mode=Manuel&State=ON&hFin=23:59 : hFin only one format HH:MM
- Mode=Manuel&State=OFF
- Mode=Manuel&State=ON

*/
void CServerWeb::handlePlugOnOff(){
    DEFDPROMPT("Plug on/off")
    bool requestAP;
    if ( !mainPowerSwitchState ){
        server->send(404, "text/plain", "Page not found");
        return;
    }
    /////////////////////////////////////////////////////////////////////////////
    //      DISPLAY URI                                                        //
    /////////////////////////////////////////////////////////////////////////////
    String uriReceived = server->uri();
    DSPL( dPrompt + F(" Received uri = ") + uriReceived );
    IPAddress clientIP = server->client().remoteIP();
    IPAddress modeAPIP = _pcParam->getIPAdd();
    
    DSPL( dPrompt + F("client IP = ") + clientIP.toString() );
    DSPL( dPrompt + F("Soft AP IP : ") + modeAPIP.toString()  );
    modeAPIP[3] = 0;
    clientIP[3] = 0;
    DSPL( dPrompt + F("new IP = ") + clientIP.toString() );
    if ( clientIP == modeAPIP ){
       DSPL( dPrompt + F("soft AP request") ); 
       requestAP = true;
    } else {
       DSPL( dPrompt + F("Station network request") ); 
       requestAP = false;
    } 
    DSPL( dPrompt + " nbr de parametres : "+(String)server->args() );
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server->args() ; i++ ){
        allArgs += server->argName( i ) + "=" + server->arg( i ) + HTML_ALLARGS_SEPARATOR;
    }
    DSPL( dPrompt + allArgs);
    /////////////////////////////////////////////////////////////////////////////
    *_pRestartTempoLed = true;
    String plugColor = server->arg("COLOR");
    DSPL( dPrompt + " Plug color = " + plugColor );
    String plugVal = server->arg("State");
    DSPL( dPrompt + " State = " + plugVal);
    String duree = server->arg("DUREE");
    DSPL( dPrompt + " Duree val = " + duree);
    String mode = server->arg(JSON_PARAMNAME_MODE);
    DSPL( dPrompt + " Mode = " + mode);
    int i;
    
    for ( i = 0; i < 4 ; i++ ){
        //DSPL( dPrompt + "plugName : " + plugs[i].getPlugName() );
        if ( _pPlugs[i].getPlugName() == plugColor ) break;
    }
    String returnVal;
    if (i == 4){
        returnVal = " couleur invalide";
        DSPL( dPrompt + returnVal);
    } else {
        _pPlugs[i].handleHtmlReq( allArgs ); 
        returnVal = "OK";
    }
   
    // String returnPage = allArgs + "\n" + returnVal ;
    // server->send(200, "text/plain", returnPage ); 
    // if ( cParam.getWifiMode() == "softAP" )
    if ( requestAP )
        handleSoftAPIndex();
    else
        handleFileRead("/");
    /** DONE see above 13/07/2019 in APmode this return to Station page */
    
}


//The work:
   // server = new ESP8266WebServer( cParam.getServerPort() );
    // DSPL( dPrompt + "Server port : " + (String)cParam.getServerPort() );
	// if ( !simpleManualMode ){
    //     if ( cParam.getFirstBoot() == ConfigParam::YES 
    //             || cParam.getFirstBoot() == ConfigParam::TRY ){
    //         server->on("/", HTTP_GET, firstBootHtmlForm );
    //         DSPL( dPrompt + "First boot procedure");
    //     } else if ( cParam.getWifiMode() == "softAP" ) {
    //         server->on("/", HTTP_GET, handleSoftAPIndex );
    //         DSPL( dPrompt + F("******************reg page") );
    //     }
    //     server->on("/ChangeCred", HTTP_POST, handleNewCred );
    //     /** DONE 13/07/2019 update handleNewCred to reflect changes in credentials.json */
    //     //Note: The above function is disabled as long as the handleNewCred function has
    //     //not been updated
	// 	                                        server->on("/list", HTTP_GET, handleFileList);
	// 	// server->on("/PlugConfig", HTTP_GET, handlePlugConfig );
    //     server->on("/cfgsend", HTTP_POST, handleIOTESPConfiguration );
    //     server->on("/cfgpage", HTTP_GET, handelIOTESPConfPage );
	// 	                                        server->on("/plugonoff", HTTP_POST, handlePlugOnOff ); 
    //     server->on("/firstBoot", HTTP_POST, handleFirstBoot);
	// 	server->on("/edit", HTTP_GET, [](){
	// 		if(!handleFileRead("/edit.htm")) server->send(404, "text/plain", "FileNotFound");
	// 	});
	// 	server->on("/help", HTTP_GET, [](){
	// 		if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
	// 	});
    //     /** @todo [OPTION] test FSBBrowserNG from https://github.com/gmag11/FSBrowserNG */
	// 	server->on("/edit", HTTP_PUT, handleFileCreate);
	// 	server->on("/edit", HTTP_DELETE, handleFileDelete);
	// 	//first callback is called after the request has ended with all parsed arguments
	// 	//second callback handles file uploads at that location
	// 	server->on("/edit", HTTP_POST, [](){ server->send(200, "text/plain", ""); }, handleFileUpload);

	// 	//called when the url is not defined here
	// 	//use it to load content from SPIFFS
    //     server->on("/", HTTP_GET, handleIndex );
	// 	server->onNotFound([](){
    //         if(!handleFileRead(server->uri()))
    //             server->send(404, "text/plain", "FileNotFound");
	// 	}
    //     );    



	// 	// server->on ( "/inline", []() {
	// 		// server->send ( 200, "text/plain", "this works as well" );
	// 	// } );

		// DSPL ( dPrompt + F("HTTP server started" ) );
	
	// }

/**
 @fn CServerWeb::handleFileRead(String path)
 @brief IoT_EPS a web server private method to handle file read request from others methods
 @param path a string that represent the path of the file to bo served
 @return

*/
bool CServerWeb::handleFileRead(String path){
  DEBUGPORT.println("handleFileRead: " + path);
  
  //if ( cParam.getFirstBoot() or firstBoot == tryStation ){ firstBootHtmlForm() }
  if(path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    DEBUGPORT.println("handleFileRead _path : " + path);
    DEBUGPORT.println("handleFileRead _contenttype : " + contentType);
    server->streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}


/**
 @fn String CServerWeb::getContentType(String filename)
 @brief IoT_EPS a private methode of the webserver to determin the html content type
 @param filename the name of the fiel with its extension to determine 
 @return the content type as a string

Supported extension : .htm, .html, .css, .js, .png, .gif, .jpg, .ico, .xml, .pdf, .zip, .gz, .json

*/
String CServerWeb::getContentType(String filename){
  if(server->hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  else if(filename.endsWith(".json")) return "application/json";
  return "text/plain";
}

/**
 @fn void CServerWeb::handleSoftAPIndex()
 @brief IoT_EPS Web server method to handle soft app index.html page
*/
void CServerWeb::handleSoftAPIndex(){
 
    handleFileRead( APMODEINDEXPAGENAME );

}

/** 
@fn String extractParamFromHtmlReq( String allRecParam, String param )
@brief to extract a parameter from all parameter
@param allRecParam a concatened String containing all received parameters build in handlePlugOnOff()
@param param the parameter to extract
@return the value of the parameter or "nf" for not found or "" empty
*/
String CServerWeb::extractParamFromHtmlReq( String allRecParam, String param ){
    DEFDPROMPT("extract param");
    DSPL( dPrompt + F("Search for : ") + param);
    param +="=";
    int pos = allRecParam.indexOf( param );
    //DSPL( dPrompt + "Pos brut = " + (String)pos);
    if ( pos == -1 ) return RETURN_NOT_FOUND_VALUE;
    pos += param.length();
    int fin = allRecParam.indexOf( HTML_ALLARGS_SEPARATOR, pos );
    //DSPL( dPrompt + "fin = " +(String)fin );
    return allRecParam.substring( pos, fin );
}

/**
@fn void CServerWeb::handleFileList()
@brief IoT_EPS web server method to handle /list?dir html reques
@return not param and no return value

This function is provided by core spiffs example
*/
void CServerWeb::handleFileList() {
    //usage exemple ipaddr/list?dir=/
  if(!server->hasArg("dir")) {server->send(500, "text/plain", "BAD ARGS"); return;}
  
  String path = server->arg("dir");
  DEBUGPORT.println("handleFileList: " + path);
  Dir dir = SPIFFS.openDir(path);
  path = String();

  String output = "[";
  while(dir.next()){
    File entry = dir.openFile("r");
    if (output != "[") output += ",\n";
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir)?"dir":"file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  
  output += "]";
  server->send(200, "text/json", output);
}


/**
 * @brief 
 * 
 */
void CServerWeb::handleHelp(){
    if(!handleFileRead("/help.htm")) server->send(404, "text/plain", "FileNotFound");
}