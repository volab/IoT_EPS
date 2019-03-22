

#include "IoT_EPS.h"

extern RTC_DS3231 rtc;

//==================================================================================================
// FSBrowser samples functions integration 
// begin

String getContentType(String filename){
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
  return "text/plain";
}



bool handleFileRead(String path){
  DEBUGPORT.println("handleFileRead: " + path);
  
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


File fsUploadFile; // cette variable doit être globale
//la fonction l'utilise plusieurs fois
//eventuellement pourrait être static
void handleFileUpload(){
    
  if(server->uri() != "/edit") return;
  HTTPUpload& upload = server->upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    DEBUGPORT.print("handleFileUpload Name: "); DEBUGPORT.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    //DEBUGPORT.print("handleFileUpload Data: "); DEBUGPORT.println(upload.currentSize);
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile)
      fsUploadFile.close();
    DEBUGPORT.print("handleFileUpload Size: "); DEBUGPORT.println(upload.totalSize);
  }
}

void handleFileDelete(){
  if(server->args() == 0) return server->send(500, "text/plain", "BAD ARGS");
  String path = server->arg(0);
  DEBUGPORT.println("handleFileDelete: " + path);
  if(path == "/")
    return server->send(500, "text/plain", "BAD PATH");
  if(!SPIFFS.exists(path))
    return server->send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server->send(200, "text/plain", "");
  path = String();
}

void handleFileCreate(){
  if(server->args() == 0)
    return server->send(500, "text/plain", "BAD ARGS");
  String path = server->arg(0);
  DEBUGPORT.println("handleFileCreate: " + path);
  if(path == "/")
    return server->send(500, "text/plain", "BAD PATH");
  if(SPIFFS.exists(path))
    return server->send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if(file)
    file.close();
  else
    return server->send(500, "text/plain", "CREATE FAILED");
  server->send(200, "text/plain", "");
  path = String();
}

void handleFileList() {
    //usage ipaddr/list?dir=/
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

//end
//==================================================================================================


//==================================================================================================
 
/** 
@fn void displayTime()
To display the current time from DS3231

HTML text is in the c code as String page var
*/
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
    server->send ( 200, "text/html", page );
    
}

void handlePlugConfig(){
    
    DEFDPROMPT("Plug config")
    DSPL( dPrompt + " nbr de parametres : "+(String)server->args() );
    DSPL( dPrompt + " plug = " + server->arg( "plug"));
    DSPL( dPrompt + " mode = " + server->arg( "mode"));
    server->send(200, "text/plain", "OK");
}

/** 
@fn void handlePlugOnOff()
@brief this the handler for html request
@return nothing and no parameter

This function is activated when a request is received from the client's browser.

It creats a concatened String of all parameters.

This the allArgs local var that is passed to CPowerPlug::extractParamFromHtmlReq.

Example:

Received args : COLOR=redPlug/ State=OFF/ Mode=Hebdomadaire/ dureeOn=210/ dureeOff=en minutes/ 
hDebut=17:10/ hFin=HH:MM/ clonedPlug=greenPlug/ 
OK
*/
// extern CPowerPlug plugs[4];
extern CPowerPlug *plugs;
extern bool restartTempoLed;
extern int mainPowerSwitchState;
void handlePlugOnOff(){
    DEFDPROMPT("Plug on/off")
    if ( !mainPowerSwitchState ){
        server->send(404, "text/plain", "Main power is off");
        return;
    }
    /////////////////////////////////////////////////////////////////////////////
    //      DISPLAY URI                                                        //
    /////////////////////////////////////////////////////////////////////////////
    String uriReceived = server->uri();
    DSPL( dPrompt + F(" Received uri = ") + uriReceived );
    DSPL( dPrompt + " nbr de parametres : "+(String)server->args() );
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server->args() ; i++ ){
        allArgs += server->argName( i ) + "=" + server->arg( i ) + "/";
    }
    DSPL( dPrompt + allArgs);
    /////////////////////////////////////////////////////////////////////////////
    restartTempoLed = true;
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
        if ( plugs[i].getPlugName() == plugColor ) break;
    }
    String returnVal;
    if (i == 4){
        returnVal = " couleur invalide";
        DSPL( dPrompt + returnVal);
    } else {
        plugs[i].handleHtmlReq( allArgs ); 
        returnVal = "OK";
    }
   
    String returnPage = allArgs + "\n" + returnVal ;
    server->send(200, "text/plain", returnPage );    
}


/** 
 @fn void handleSoftAPIndex()
 @brief A function to diplay SoftAP special Page
 @return no return value and no parameter

*/
void handleSoftAPIndex(){
    String page;

    page = "<html><head>";
    // page += "<meta http-equiv='refresh' content='5'/>";
    page += "<title>IoT EPS softAP index page</title>";
    page += "<style>";
    page += "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }";
    page += "</style></head><body><h1>IoT EPS Soft Access Point Index Page!</h1>";
    page += "<a href=\"index.html\">Accueil</a><p>";
    page += "<p> While there is not internet connection in soft Access Point mode we can not";
    page += " display a nice page with Bootsrap and others great features...</p>";
    page += "</br></br></br></br><h1>Enter new credentials</h1>";
    page += "<FORM action=\"/ChangeCred\" method=\"post\">";
    page += "<p>";
    page += "<label style=\"font-size:250%\">SSID";
    page += "<INPUT type=\"text\" name=\"ssid\" style=\"font-size:115%\"></label><BR>";
    page += "</br><label style=\"font-size:250%\">pasword";
    page += "<INPUT type=\"text\" name=\"pass\" style=\"font-size:115%\" ></label><BR>";
    page += "<INPUT type=\"submit\" value=\"Send\" style=\"font-size:250%\" >";
    page += "<INPUT type=\"reset\" style=\"font-size:250%\"   > ";
    page += "</p></form>";
    page += "</body></html>";
    server->send ( 200, "text/html", page );
    /** @todo add a link to the page to drive power strip without internet connection */
    /** @todo add a page to set the DS3231 time without NTP server of course */
}

/** 
 @fn void handleNewCred()
 @brief fun tha handle new credential in response to handleSoftAPIndex...
 @return no return value and no parameter

 This function write credentials.json file in the SPIFFS with received SSID and password.
 
*/
void handleNewCred(){
    //usage /ChangeCred?SSID=xxxx/pass="yyyy" or connect to Stripplug in softAP mode to change
    // credential.
    DEFDPROMPT( F("handel New Cred") );
    String uriReceived = server->uri();
    DSPL( dPrompt + F(" Received uri = ") + uriReceived );
        DSPL( dPrompt + " nbr de parametres : "+(String)server->args() );
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server->args() ; i++ ){
        allArgs += server->argName( i ) + "=" + server->arg( i ) + "/";
    }
    DSPL( dPrompt + allArgs);
    String ssid = server->arg( 0 );
    String pass = server->arg( 1 );
    DSPL( dPrompt + F("SSID = ") + ssid );
    DSPL( dPrompt + F("pass = ") + pass );
    //creat file : credentials.json
    //ArduinoJson lib with pdf serialization documentation
    /*
    {
    "ssid" : "VoLab",
    "pass" : "V0L@b42net"
    }
    */
    const int capacity = JSON_OBJECT_SIZE(4);
    StaticJsonBuffer<capacity> jb;
    JsonObject& obj = jb.createObject();
    obj["ssid"] = ssid;
    obj["pass"] = pass;
    // jb.prettyPrintTo(configFile);
    obj.prettyPrintTo(Serial);DSPL("");
    File credFile = SPIFFS.open( "/credentials.json" , "w");
    if (credFile){
        DSPL( dPrompt + F("File /credentials.json open for write") );
        obj.prettyPrintTo(credFile);
    } else {
        DSPL( dPrompt + F("File /credentials.json open for write fail !") );
    }
    credFile.close();
    String returnPage = allArgs ;
    server->send(200, "text/plain", returnPage );     
}

