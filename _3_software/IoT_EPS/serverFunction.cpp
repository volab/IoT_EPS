

#include "IoT_EPS.h"

extern RTC_DS3231 rtc;

//==================================================================================================
// integration FSBrowser example functions
// begin

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
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
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}


File fsUploadFile; // cette variable doit être globale
//la fonction l'utilise plusieurs fois
//eventuellement pourrait être static
void handleFileUpload(){
    
  if(server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
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
  if(server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  DEBUGPORT.println("handleFileDelete: " + path);
  if(path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if(!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate(){
  if(server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  DEBUGPORT.println("handleFileCreate: " + path);
  if(path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if(SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if(file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileList() {
    //usage ipaddr/list?dir=/
  if(!server.hasArg("dir")) {server.send(500, "text/plain", "BAD ARGS"); return;}
  
  String path = server.arg("dir");
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
  server.send(200, "text/json", output);
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
    server.send ( 200, "text/html", page );
    
}

void handlePlugConfig(){
    
    DEFDPROMPT("Plug config")
    DSPL( dPrompt + " nbr de parametres : "+(String)server.args() );
    DSPL( dPrompt + " plug = " + server.arg( "plug"));
    DSPL( dPrompt + " mode = " + server.arg( "mode"));
    server.send(200, "text/plain", "OK");
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
extern CPowerPlug plugs[4];
void handlePlugOnOff(){
    DEFDPROMPT("Plug on/off")
    /////////////////////////////////////////////////////////////////////////////
    //      DISPLAY URI                                                        //
    /////////////////////////////////////////////////////////////////////////////
    String uriReceived = server.uri();
    DSPL( dPrompt + F(" Received uri = ") + uriReceived );
    DSPL( dPrompt + " nbr de parametres : "+(String)server.args() );
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server.args() ; i++ ){
        allArgs += server.argName( i ) + "=" + server.arg( i ) + "/ ";
    }
    DSPL( dPrompt + allArgs);
    /////////////////////////////////////////////////////////////////////////////

    String plugColor = server.arg("COLOR");
    DSPL( dPrompt + " Plug color = " + plugColor );
    String plugVal = server.arg("State");
    DSPL( dPrompt + " State = " + plugVal);
    String duree = server.arg("DUREE");
    DSPL( dPrompt + " Duree val = " + duree);
    String mode = server.arg(JSON_PARAMNAME_MODE);
    DSPL( dPrompt + " Mode = " + mode);
    int i;
    
    for ( i = 0; i < 4 ; i++ ){
        // DSPL( dPrompt + "plugName : " + plugs[i].getPlugName() );
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
    server.send(200, "text/plain", returnPage );    
}