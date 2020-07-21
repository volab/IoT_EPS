/**
 @file serverFunction.cpp
 @author J.SORANZO
 @date 20 Oct 2018
 @copyright 2018 CC0
 @version git versionning
 @brief a collection of simple C functions to handler server request
 
 The first group of this functions are copy from ARDUINO FSBBrowse?ino example
 
 The rest at the end of this file are our work
*/

#include "IoT_EPS.h"

// extern RTC_DS3231 rtc; //where is it creat warning it is not CRtc instance
// RTC_DS3231 rtc; //where is it creat warning it is not CRtc instance
extern ConfigParam cParam;



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
  else if(filename.endsWith(".json")) return "application/json";
  return "text/plain";
}


//extern cParam
bool handleFileRead(String path){
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
 @brief To display the current time from DS3231...
 @return no return value and no parameter
HTML text is in the c code as String page var

This is the handler of the /time action (see the setup function of IoT_ESP.ino)
*/
void displayTime(){
    String page;
    DateTime now;
    // now = rtc.now();
    now = RTC_DS3231::now();
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
@fn void handlePlugOnOff()
@brief this the handler for html request...
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
    IPAddress modeAPIP = cParam.getIPAdd();
    
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
   
    // String returnPage = allArgs + "\n" + returnVal ;
    // server->send(200, "text/plain", returnPage ); 
    // if ( cParam.getWifiMode() == "softAP" )
    if ( requestAP )
        handleSoftAPIndex();
    else
        handleFileRead("/");
    /** DONE see above 13/07/2019 in APmode this return to Station page */
}


/** 
 @fn void handleSoftAPIndex()
 @brief A function to diplay SoftAP special Page
 @return no return value and no parameter

*/
void handleSoftAPIndex(){
    /*
    String page;
// send the page file directly - see handelFileRead function
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
    */
    handleFileRead( APMODEINDEXPAGENAME );
    /** DONE add a link to the page to drive power strip without internet connection */
    /** DONE see config .html page 
    add a page to set the DS3231 time without NTP server of course */
}

/** 
 @fn void handleNewCred()
 @brief fun tha handle new credential in response to handleSoftAPIndex...
 @return no return value and no parameter

 This function write credentials.json file in the SPIFFS with received SSID and password.
 
*/
void handleNewCred(){
    //usage /ChangeCred?ssid=xxxx/pass="yyyy" or connect to EPS in softAP mode to change
    // credential.
    DEFDPROMPT( F("handel New Cred") );
    String uriReceived = server->uri();
    DSPL( dPrompt + F(" Received uri = ") + uriReceived );
        DSPL( dPrompt + " nbr de parametres : "+(String)server->args() );
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server->args() ; i++ ){
        allArgs += server->argName( i ) + "=" + server->arg( i ) + HTML_ALLARGS_SEPARATOR;
    }
    DSPL( dPrompt + allArgs);
    String ssid = extractParamFromHtmlReq( allArgs, JSON_SSID_NAME );
    String pass = extractParamFromHtmlReq( allArgs, JSON_PPASS_NAME );
    String softAPssid =  extractParamFromHtmlReq( allArgs, JSON_APSSID_NAME );
    String sofATPpass =  extractParamFromHtmlReq( allArgs, JSON_APPASS_NAME );
    DSPL( dPrompt + F("new SSID = ") + ssid );
    DSPL( dPrompt + F("new pass = ") + pass );
    DSPL( dPrompt + F("Soft AP new ssid = ") + softAPssid );
    DSPL( dPrompt + F("Soft AP new pass = ") + sofATPpass );

    /** DONE - 13/07/2019 change this function to adapt to new credentials file */
    //this page is necessary to enter new credential in AP mode
    // const int capacity = JSON_OBJECT_SIZE(4);
    // StaticJsonBuffer<capacity> jb;
    // JsonObject& obj = jb.createObject();
    // obj["ssid"] = ssid;
    // obj["pass"] = pass;
    // // jb.prettyPrintTo(configFile);
    // obj.prettyPrintTo(Serial);DSPL("");
    // File credFile = SPIFFS.open( "/credentials.json" , "w");
    // if (credFile){
        // DSPL( dPrompt + F("File /credentials.json open for write") );
        // obj.prettyPrintTo(credFile);
    // } else {
        // DSPL( dPrompt + F("File /credentials.json open for write fail !") );
    // }
    // credFile.close();
    // String returnPage = allArgs ;
    File creFile = SPIFFS.open( CREDENTIALFILENAME , "r");
    // DSPL( dPrompt + file);
    if (creFile) {
        size_t size = creFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        creFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (json.success()) {
            JsonObject& general = json["general"]; // main level
            // DSPL( dPrompt + " general : " + param + " = " + value);
            if ( ssid != "" ) general[JSON_SSID_NAME] = ssid; 
            if ( pass != "" ) general[ JSON_PPASS_NAME ] = pass ;
            if ( softAPssid != "" ) general[ JSON_APSSID_NAME ] = softAPssid ;
            if ( sofATPpass != "" ) general[ JSON_APPASS_NAME ] = sofATPpass ;
            creFile.close();
            creFile = SPIFFS.open( CREDENTIALFILENAME , "w");
            json.printTo(creFile);
            DSPL( dPrompt + F("new credentials written") );
        } else {
            DSPL( dPrompt + F("Failed to load json credentials file") );
            sysStatus.fsErr.err( true );
        }
        creFile.close();
    }
    if ( cParam.getWifiMode() == "softAP" )
        handleSoftAPIndex();
    else
        handleFileRead("/");
    /** @todo [NECESSARY] Send an html page to confir that credentials was written */
    // server->send(200, "text/plain", returnPage );     
}


/** 
 @fn void firstBootHtmlForm()
 @brief Special firsboot page handler...
 @return no return value and no parameter
 
 Firstboot special page provide a way to the user to set SSID and pass for AP or Station mode.
*/
void firstBootHtmlForm(){
    /** DONE here 13/07/2019 if (firstBoot == tryStattion ){ add warnig to the page} */ 
    DEFDPROMPT("Handle First boot html form");
    DSPL( dPrompt );
    String page;
    File firstBFormFile = SPIFFS.open(FIRSTBOOTFORMFILENAME, "r");
    if (firstBFormFile){
        page = firstBFormFile.readString();
        if (cParam.getFirstBoot() == ConfigParam::TRY ){
            page.replace( FBTAG_WARNIG_STAACCES_IMPOSSIBLE ,
                FB_WARNING_STAACCES_IMPOSSIBLE_MESS );
                DSPL(dPrompt + F("Warning HTML insertion !") );
                page.replace( FBTAG_APSSID , buildMacAddName( "IoT_ESP_2" ) );
        // }
        } else page.replace( FBTAG_APSSID , buildMacAddName( "IoT_ESP" ) );
        // page.replace( FBTAG_APSSID , buildMacAddName( "IoT_ESP" ) );
        //page.replace("__APPASS__"), getAPPass() );
        server->send ( 200, "text/html", page );
    } else {
        DSPL( dPrompt + F("form first boot not found") );
        server->send(404, "text/plain", "FileNotFound");
    }
}

/** 
 @fn void firstBootHtmlForm()
 @brief Special firsboot reponse handler...
 @return no return value and no parameter
 
 Firstboot special page provide a way to the user to set SSID and pass for AP or Station mode.
 
 Here we process the answer of the user to write credential file and switch to normal mode.
*/
void handleFirstBoot(){
    // check parameters
    // if (mode == Station)  set firstBoot to tryStation and restart ESP
    // if (mode == AP) set firstBoot to OFF
    DEFDPROMPT( "handle First Boot "); 
    cParam.creatDefaultJson();
    ConfigParam::write2Json( "firstBoot", "ON" ); //not very usefull
    //1) when we came from a real firstBoot this value change in this function
    //2) when we came from config page config handler has previously write this value and it is 
    //    the next reset who trigger this method and this value change in this method
    //piece of code generate by
    //https://arduinojson.org/v5/assistant/
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4);
    DynamicJsonBuffer jsonBuffer(capacity);
    JsonObject& root = jsonBuffer.createObject();
    JsonObject& general = root.createNestedObject("general");
    general["ssid"] = "yourSSID";
    general["pass"] = "yourPass";
    general["softApSsid"] = buildMacAddName( "IoT_ESP" );
    general["softApPass"] = "123456789";
    // root.prettyPrintTo(DEBUGPORT);DSPL("");
       
    
    String allArgs = F(" Received args : ") ;
    for ( int i = 0; i < server->args() ; i++ ){
        allArgs += server->argName( i ) + "=" + server->arg( i ) + HTML_ALLARGS_SEPARATOR;
    }
    DSPL( dPrompt + allArgs );
    String mode = extractParamFromHtmlReq( allArgs, FB_PARAMNAME_MODE );
    
    if (mode == FB_PARAMVAL_MODEAP){
    //**********************************************************************************************
    //   Access Point Mode
    //**********************************************************************************************
        String apSsid = extractParamFromHtmlReq( allArgs, FB_PARAMNAME_APSSID );
        String apPass = extractParamFromHtmlReq( allArgs, FB_PARAMNAME_APPASS );
        DSPL( dPrompt + F("credentials.json file creation.") );
        
        //creat credential.json
        general["softApSsid"] = apSsid;
        general["softApPass"] = apPass;
        root.prettyPrintTo(DEBUGPORT);DSPL("");
        File credFile = SPIFFS.open( CREDENTIALFILENAME , "w");
        if (credFile){
            DSPL( dPrompt + F("File ") + CREDENTIALFILENAME + F(" open for write") );
            root.prettyPrintTo(credFile);
        } else {
            DSPL( dPrompt + F("File") + CREDENTIALFILENAME + F(" for write fail !") );
        }
        credFile.close();
        //write to config.json
        ConfigParam::write2Json( "firstBoot", "OFF" );
        ConfigParam::write2Json( "startInAPMode", "ON" );
        //Empty STA_SSId and pass
        //AP_SSID and PASS
        /** @todo [NECESSARY] replace reset by watchdog not refresh 2 times */
        ESP.reset();
    } else { //mode Station
    //**********************************************************************************************
    //   Station Mode
    //**********************************************************************************************
        String stationSsid = extractParamFromHtmlReq( allArgs, FB_PARAMNAME_STASSID );
        String stationPass = extractParamFromHtmlReq( allArgs, FB_PARAMNAME_STAPASS );
        if ( stationSsid.length() == 0 ){
            /** Removed manage error about ssid in first boot - normaly done in HTML form*/
        }
        general["ssid"] = stationSsid;
        general["pass"] = stationPass;
        root.prettyPrintTo(DEBUGPORT);DSPL("");
        File credFile = SPIFFS.open( "/credentials.json" , "w");
        if (credFile){
            DSPL( dPrompt + F("File /credentials.json open for write") );
            root.prettyPrintTo(credFile);
        } else {
            DSPL( dPrompt + F("File /credentials.json open for write fail !") );
        }
        credFile.close();
        ConfigParam::write2Json( "startInAPMode", "OFF" );
        ConfigParam::write2Json( "firstBoot", "TRYSTA" );
        /** @todo [NECESSARY] replace reset by watchdog not refresh */
        ESP.reset();        
    }
    String returnPage = allArgs ;
    server->send(200, "text/plain", returnPage ); 
}


/** 
 @fn String buildMacAddName( String prefix)
 @brief return a string from mac add...
 @param prefix the prefix of the wanted name example IoT_ESP
 @return a tring with the prefix followed by _MMNN

 Build a string by concatenate prefix provided with the 2 last octets of the mac address.
*/
String buildMacAddName( String prefix){
    uint8_t mac[6];
    char macStr[18] = { 0 };
    WiFi.macAddress( mac );
    sprintf(macStr, "_%02X%02X", mac[4], mac[5]);
    return prefix+String(macStr);
    
}

/** 
@fn String extractParamFromHtmlReq( String allRecParam, String param )
@brief to extract a parameter from all parameter
@param allRecParam a concatened String containing all received parameters build in handlePlugOnOff()
@param param the parameter to extract
@return the value of the parameter or "nf" for not found or "" empty
*/
String extractParamFromHtmlReq( String allRecParam, String param ){
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
 @fn void handleIOTESPConfiguration()
 @brief function that handle configuration.html page returns
 @return no return value and no parameter

*/
void handleIOTESPConfiguration(){
    DEFDPROMPT("handle configuration")
    if ( !mainPowerSwitchState ){
        server->send(404, "text/plain", "Page not found");
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
        allArgs += server->argName( i ) + "=" + server->arg( i ) + HTML_ALLARGS_SEPARATOR ;
    }
    DSPL( dPrompt + allArgs);
    /////////////////////////////////////////////////////////////////////////////
    restartTempoLed = true;
    
    struct configItem {
        String name;
        String val;
    };
    
    configItem confParam[] ={
        { HTML_EMPLACEMENT_NAME, "" },
        { HTML_ALLLEDSONTIME_NAME, ""},
        { HTML_LEDLUM_NAME, ""},
        { HTML_HOSTNAME_NAME, ""},
        { HTML_SOFTAPIP_NAME, ""},
        { HTML_SOFTAPPORT_NAME, ""},
        { HTML_STATIONIP_NAME, ""},
        { HTML_STAGATEWAY_NAME, ""},
        { HTML_MAXRETRY_NAME, ""},
 
    };
    
    configItem plugsNickNames[] ={
        { HTML_REDPLUGNICK_NAME, ""},
        { HTML_GREENPLUGNICK_NAME, ""},
        { HTML_BLUEPLUGNICK_NAME, ""},
        { HTML_YELLOWPLUGNICK_NAME, ""},        
    };    
    //17 parameters
    
    //check box special process
    configItem checkBoxes[] ={
        { HTML_POWERLEDECO_NAME, ""},
        { HTML_FIRSTBOOT_NAME, ""},
        { HTML_STARTINAP_NAME, ""},
        { HTML_DHCPMODE_NAME, ""},        
    };
    
    //2 for loop for better debug display ;-)
    int cpt = 0;
    for ( configItem i : confParam )
        confParam[cpt++].val = extractParamFromHtmlReq( allArgs, i.name );   
    for ( configItem i : confParam ){
        if ( i.val != "" ){
            // DSPL( dPrompt + "Write to json for " + i.name + " value : " + i.val );
            ConfigParam::write2Json( i.name, i.val, CONFIGFILENAME);
        }
    }
    cpt=0;
    for ( configItem i : checkBoxes){
        i.val = extractParamFromHtmlReq( allArgs, i.name );
        checkBoxes[cpt++].val = ( i.val == NOT_FOUND?"OFF":"ON");
    }
    for ( configItem i : checkBoxes){
        // DSPL( dPrompt + "Write to json for " + i.name + " value : " + i.val);
        ConfigParam::write2Json( i.name, i.val, CONFIGFILENAME);
    }
    cpt=0;
    for ( configItem i : plugsNickNames)
        plugsNickNames[cpt++].val = extractParamFromHtmlReq( allArgs, i.name );
    for ( configItem i : plugsNickNames){
        if ( i.val != "" ){
            String color = i.name.substring(0, i.name.indexOf('_') );
            // DSPL(dPrompt + "plug name = " + color );
            for ( int j = 0; j < 4 ; j++ ){
                // DSPL( dPrompt + "plugName : " + plugs[j].getPlugName() );
                if ( plugs[j].getPlugName() == color ){
                    // DSPL(dPrompt + "Write to json for " + color + " nickname = " + i.val );
                    plugs[j].writeToJson( "nickName", i.val );
                }
            } 
            
        }
       
    }
    String date =  extractParamFromHtmlReq( allArgs, "setDate" );
    String time = extractParamFromHtmlReq( allArgs, "setTime" );
    DSPL( dPrompt + date +" " + time );
    if ( date != "" || time != "" ){
        DateTime now =  RTC_DS3231::now();
        if ( time == "" ) time = String( now.hour() ) + ":" + String( now.minute() ) 
                    + ":" + String( now.second() );
        if ( date == "" ) date = String( now.day() ) + "/" + String( now.month() )
                    + "/" + String( now.year() );        
        date = date + " " + time;
        DSPL( dPrompt + " date/time to set : " + date );
        char * cstr = new char [date.length()+1];
        strcpy (cstr, date.c_str());
        CRtc::adjust( cstr );
    }


    // String returnPage = allArgs + "\n" ;
    // server->send(200, "text/plain", returnPage );
/** @todo [NECESSARY]return to config page to confirm that values are taken into account */    
    // if ( cParam.getWifiMode() == "softAP" )
        // handleSoftAPIndex();
    // else
        // handleFileRead("/");
    // handleFileRead("/");
    handelIOTESPConfPage();    
}


/** 
 @fn void handelIOTESPConfPage()
 @brief /cfgpage action handler
 @return no return value and no parameter
 
Replace the place holder of the conf_tag.htm file by the config.json content
*/
void handelIOTESPConfPage(){
    String confParam[] ={
          HTML_EMPLACEMENT_NAME
        , HTML_ALLLEDSONTIME_NAME
        , HTML_LEDLUM_NAME
        , HTML_HOSTNAME_NAME
        , HTML_SOFTAPIP_NAME
        , HTML_SOFTAPPORT_NAME
        , HTML_STATIONIP_NAME
        , HTML_STAGATEWAY_NAME
        , HTML_MAXRETRY_NAME
    };
    String plugNames[] = {
          HTML_JSON_REDPLUGNAME
        , HTML_JSON_GREENPLUGNAME
        , HTML_JSON_BLUEPLUGNAME 
        , HTML_JSON_YELLOWPLUGNAME
    };
    String checkBox[] = {
          HTML_STARTINAP_NAME
        , HTML_DHCPMODE_NAME
        , HTML_FIRSTBOOT_NAME
        , HTML_POWERLEDECO_NAME     
    };
    String phParamTag;
    String param;
    DEFDPROMPT("Handle config html form");
    DSPL( dPrompt );
    String page;
    File confFormFile = SPIFFS.open(CONFIGFORMFILENAME, "r");
    if (confFormFile){
        page = confFormFile.readString();
        for (String p : confParam ){
            phParamTag = PALCEHOLDERTAG+p;
            param = ConfigParam::readFromJsonParam( p, "general");
            page.replace( phParamTag , param );          
        }
        for (String p : plugNames ){
            phParamTag = PALCEHOLDERTAG+p;
            param = ConfigParam::readFromJsonParam( "nickName", p );
            page.replace( phParamTag , param );          
        }
        for (String p : checkBox ){
            phParamTag = PALCEHOLDERTAG+p;
            param = ConfigParam::readFromJsonParam( p, "general" );
            DSPL( dPrompt + "p = " + param );
            param = (param == "ON"?"checked":"");
            page.replace( phParamTag , param );          
        }
        
        server->send ( 200, "text/html", page );
    } else{
        DSPL( dPrompt + F("form configuration not found") );
        server->send(404, "text/plain", "FileNotFound");
    } 
}

/** 
 @fn void handleIndex()
 @brief A new handler for index page to choose different index page between AP and station...
 @return no return value and no parameter

Now we can be connected in both mode AP and station so it is necessary to separate request from AP 
and station mode to serve the right page
*/
void handleIndex(){
    DEFDPROMPT("handleIndex");
    DSPL( dPrompt );
    bool requestAP;
    IPAddress clientIP = server->client().remoteIP();
    IPAddress modeAPIP = cParam.getIPAdd();   
    modeAPIP[3] = 0;
    clientIP[3] = 0;
    if ( clientIP == modeAPIP ){
       handleSoftAPIndex();
    } else {
       handleFileRead("/");
    }

}   



