/**
 @file CServerWeb.cpp
 @author J.SORANZO
 @date 15/08/2020
 @copyright 2020 CC0
 @version git versioning
 @brief Implementation file of CServerWeb class
*/
#include "CServerWeb.h"

//Warning global : SPIFFS used !!

// CServerWeb::CServerWeb(/* args */)
// {
// }

// CServerWeb::~CServerWeb()
// {
// }

/**
 @fn CServerWeb::init(CRtc* prtc, ConfigParam* pcParam, CPowerPlug* pPlugs
        , bool* restartTempoLed, ESP8266WiFiClass *pWifiCon)
 @brief Iot_EPS web server initialisation method
 @param prtc a class RTC pointer
 @param pcParam a CParm pointer
 @param pPlugs Plugs array class pointer
 @param restartTempoLed restart booleen pointer
 @param pWifiCon a pointer to acces wifi param
 @return no return value
*/
void CServerWeb::init(CRtc* prtc, ConfigParam* pcParam, CPowerPlug* pPlugs
        , bool* restartTempoLed, ESP8266WiFiClass *pWifiCon){
    //big warning if _rtc is initialised with a local variable !!!!
    DEFDPROMPT( "WEbServer init")
    
    _pRtc = prtc;
    _pcParam = pcParam;
    _pPlugs = pPlugs;
    mainPowerSwitchState = 0;
    _pRestartTempoLed = restartTempoLed;
    _pWifiConnection = pWifiCon;
    server = new ESP8266WebServer(_pcParam->getServerPort());

    //Register handlers in the web server

    /** @todo [OPTION] test FSBBrowserNG from https://github.com/gmag11/FSBrowserNG */
    //Register pages for first boot and Acces Point mode
    if ( _pcParam->getFirstBoot() == ConfigParam::YES
            || _pcParam->getFirstBoot() == ConfigParam::TRY ){
        server->on("/", HTTP_GET, std::bind(&CServerWeb::firstBootHtmlForm, this) );
        DSPL( dPrompt + "First boot procedure");
    } else if ( _pcParam->getWifiMode() == "softAP" ) {
        server->on("/", HTTP_GET, std::bind(&CServerWeb::handleSoftAPIndex, this) );
        DSPL( dPrompt + F("******************reg page") );
    }
    server->on("/", HTTP_GET, std::bind(&CServerWeb::handleIndex, this));
    // server->on("/time", std::bind(&CServerWeb::displayTime, this));
    // server->on("/list", HTTP_GET, std::bind(&CServerWeb::handleFileList, this));
    server->on("/plugonoff", HTTP_POST, std::bind(&CServerWeb::handlePlugOnOff, this));
    server->on("/help", HTTP_GET, std::bind(&CServerWeb::handleHelp, this));
    // server->on("/edit", HTTP_GET, std::bind(&CServerWeb::handleEdit, this));
    // server->on("/edit", HTTP_PUT, std::bind(&CServerWeb::handleFileCreate, this));

    //server.on with 4 parameters - 2 callbacks
    //first callback is called after the request has ended with all parsed arguments
    //second callback handles file uploads at that location
    // server->on("/edit", HTTP_POST, std::bind(&CServerWeb::htmlOkResponse, this)
    //                              , std::bind(&CServerWeb::handleFileUpload, this));

    // server->on("/edit", HTTP_DELETE, std::bind(&CServerWeb::handleFileDelete, this));
    server->on("/cfgpage", HTTP_GET, std::bind(&CServerWeb::handelIOTESPConfPage, this));
    server->on("/cfgsend", HTTP_POST, std::bind(&CServerWeb::handleIOTESPConfiguration, this));
    server->on("/ChangeCred", HTTP_POST, std::bind(&CServerWeb::handleNewCred, this) );
    server->onNotFound(std::bind(&CServerWeb::notFoundHandler, this));
    server->on("/firstBoot", HTTP_POST, std::bind(&CServerWeb::handleFirstBoot, this) );

    server->begin();
}




/**
@fn CServerWeb::notFoundHandler()
@brief Web server page not found handler function
@return no param and return value
*/
void CServerWeb::notFoundHandler(){
    if (!handleFileRead(server->uri()))
        server->send(404, "text/plain", "IoTEPS : FileNotFound");
}

void CServerWeb::htmlOkResponse(){
    server->send(200, "text/plain", "");
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
// void CServerWeb::displayTime(){
//     String page;
//     DateTime now;
//     // now = rtc.now();
//     if (_pRtc == NULL)
//         return;

//     now = _pRtc->now();
//     page = "<html><head>";
//     page += "<meta http-equiv='refresh' content='5'/>";
//     page += "<title>IoT EPS display Time</title>";
//     page += "<style>";
//     page += "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }";
//     page += "</style></head><body><h1>IoT EPS time!</h1>";
//     page += "<a href=\"index.html\">Accueil</a><p>";
//     page += (String)now.day() + "/" + (String)now.month() + "/" + (String)now.year() + " ";
//     page += (String)now.hour() + ":" + (String)now.minute() + ":";
//     page += (String)now.second();
//     page += "</p></body></html>";

//     server->send(200, "text/html", page);
// }

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
    if (!mainPowerSwitchState) {
        server->send(404, "text/plain", "Page not found");
        return;
    }
    /////////////////////////////////////////////////////////////////////////////
    //      DISPLAY URI                                                        //
    /////////////////////////////////////////////////////////////////////////////
    String uriReceived = server->uri();
    DSPL(dPrompt + F(" Received uri = ") + uriReceived);
    IPAddress clientIP = server->client().remoteIP();
    IPAddress modeAPIP = _pcParam->getIPAdd();

    DSPL(dPrompt + F("client IP = ") + clientIP.toString());
    DSPL(dPrompt + F("Soft AP IP : ") + modeAPIP.toString());
    modeAPIP[3] = 0;
    clientIP[3] = 0;
    DSPL(dPrompt + F("new IP = ") + clientIP.toString());
    if (clientIP == modeAPIP) {
        DSPL(dPrompt + F("soft AP request"));
        requestAP = true;
    } else {
        DSPL(dPrompt + F("Station network request"));
        requestAP = false;
    }
    DSPL(dPrompt + " nbr de parametres : " + (String)server->args());
    String allArgs = F(" Received args : ");
    for (int i = 0; i < server->args(); i++) {
        allArgs += server->argName(i) + "=" + server->arg(i) + HTML_ALLARGS_SEPARATOR;
    }
    DSPL(dPrompt + allArgs);

    /////////////////////////////////////////////////////////////////////////////
    *_pRestartTempoLed = true;
    String plugColor = server->arg("COLOR");
    DSPL(dPrompt + " Plug color = " + plugColor);
    String plugVal = server->arg("State");
    DSPL(dPrompt + " State = " + plugVal);
    String duree = server->arg("DUREE");
    DSPL(dPrompt + " Duree val = " + duree);
    String mode = server->arg(JSON_PARAMNAME_MODE);
    DSPL(dPrompt + " Mode = " + mode);
    int i;

    for (i = 0; i < 4; i++) {
        //DSPL( dPrompt + "plugName : " + plugs[i].getPlugName() );
        if (_pPlugs[i].getPlugName() == plugColor)
            break;
    }
    String returnVal;
    if (i == 4) {
        returnVal = " couleur invalide";
        DSPL(dPrompt + returnVal);
    } else {
        _pPlugs[i].handleHtmlReq(allArgs);
        returnVal = "OK";
    }

    if (requestAP)
        handleSoftAPIndex();
    else
        handleFileRead("/");
    /** DONE see above 13/07/2019 in APmode this return to Station page */
}

/**
 @fn CServerWeb::handleFileRead(String path)
 @brief IoT_EPS a web server private method to handle file read request from others methods
 @param path a string that represent the path of the file to bo served
 @return

*/
bool CServerWeb::handleFileRead(String path){
    DEBUGPORT.println("handleFileRead: " + path);

    //if ( cParam.getFirstBoot() or firstBoot == tryStation ){ firstBootHtmlForm() }
    if (path.endsWith("/"))
        path += "index.html";
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
        if (SPIFFS.exists(pathWithGz))
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
    if (server->hasArg("download"))
        return "application/octet-stream";
    else if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    else if (filename.endsWith(".json"))
        return "application/json";
    return "text/plain";
}

/**
 @fn void CServerWeb::handleSoftAPIndex()
 @brief IoT_EPS Web server method to handle soft app index.html page
*/
void CServerWeb::handleSoftAPIndex(){
    handleFileRead(APMODEINDEXPAGENAME);
}

/** 
@fn String CServerWeb::extractParamFromHtmlReq( String allRecParam, String param )
@brief to extract a parameter from all parameter
@param allRecParam a concatened String containing all received parameters build in handlePlugOnOff()
@param param the parameter to extract
@return the value of the parameter or "nf" for not found or "" empty
*/
String CServerWeb::extractParamFromHtmlReq(String allRecParam, String param){
    DEFDPROMPT("extract param");
    DSPL(dPrompt + F("Search for : ") + param);
    param += "=";
    int pos = allRecParam.indexOf(param);
    //DSPL( dPrompt + "Pos brut = " + (String)pos);
    if (pos == -1)
        return RETURN_NOT_FOUND_VALUE;
    pos += param.length();
    int fin = allRecParam.indexOf(HTML_ALLARGS_SEPARATOR, pos);
    //DSPL( dPrompt + "fin = " +(String)fin );
    return allRecParam.substring(pos, fin);
}

/**
 @fn void CServerWeb::handleFileList()
 @brief IoT_EPS web server method to handle /list?dir html reques
 @return not param and no return value
 
 This function is provided by core spiffs example
*/
void CServerWeb::handleFileList(){
    //usage exemple ipaddr/list?dir=/
    if (!server->hasArg("dir")) {
        server->send(500, "text/plain", "BAD ARGS");
        return;
    }

    String path = server->arg("dir");
    DEBUGPORT.println("handleFileList: " + path);
    Dir dir = SPIFFS.openDir(path);
    path = String();

    String output = "[";
    while (dir.next()) {
        File entry = dir.openFile("r");
        if (output != "[")
            output += ",\n";
        bool isDir = false;
        output += "{\"type\":\"";
        output += (isDir) ? "dir" : "file";
        output += "\",\"name\":\"";
        output += String(entry.name()).substring(1);
        output += "\"}";
        entry.close();
    }

    output += "]";
    server->send(200, "text/json", output);
}

/**
 * @brief Juste to send help.html file
 * 
 */
void CServerWeb::handleHelp(){
    if (!handleFileRead("/help.htm"))
        server->send(404, "text/plain", "FileNotFound");
}

/**
 * @brief Handler that open edit.htm
 * 
 */
void CServerWeb::handleEdit(){
    DEFDPROMPT("Handle edit");
    DSPL(dPrompt);
    if (!handleFileRead("/edit.htm"))
        server->send(404, "text/plain", "FileNotFound");
}

void CServerWeb::handleFileCreate(){
    DEFDPROMPT("Handle file creat");
    DSPL(dPrompt);
    if (server->args() == 0)
        return server->send(500, "text/plain", "BAD ARGS");
    String path = server->arg(0);
    DEBUGPORT.println("handleFileCreate: " + path);
    if (path == "/")
        return server->send(500, "text/plain", "BAD PATH");
    if (SPIFFS.exists(path))
        return server->send(500, "text/plain", "FILE EXISTS");
    File file = SPIFFS.open(path, "w");
    if (file)
        file.close();
    else
        return server->send(500, "text/plain", "CREATE FAILED");
    server->send(200, "text/plain", "");
    path = String();
}

void CServerWeb::handleFileUpload(){
    if (server->uri() != "/edit")
        return;
    HTTPUpload& upload = server->upload();
    if (upload.status == UPLOAD_FILE_START) {
        String filename = upload.filename;
        if (!filename.startsWith("/"))
            filename = "/" + filename;
        DEBUGPORT.print("handleFileUpload Name: ");
        DEBUGPORT.println(filename);
        _fsUploadFile = SPIFFS.open(filename, "w");
        filename = String();
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        //DEBUGPORT.print("handleFileUpload Data: "); DEBUGPORT.println(upload.currentSize);
        if (_fsUploadFile)
            _fsUploadFile.write(upload.buf, upload.currentSize);
    } else if (upload.status == UPLOAD_FILE_END) {
        if (_fsUploadFile)
            _fsUploadFile.close();
        DEBUGPORT.print("handleFileUpload Size: ");
        DEBUGPORT.println(upload.totalSize);
    }
}

void CServerWeb::handleFileDelete(){
    if (server->args() == 0)
        return server->send(500, "text/plain", "BAD ARGS");
    String path = server->arg(0);
    DEBUGPORT.println("handleFileDelete: " + path);
    if (path == "/")
        return server->send(500, "text/plain", "BAD PATH");
    if (!SPIFFS.exists(path))
        return server->send(404, "text/plain", "FileNotFound");
    SPIFFS.remove(path);
    server->send(200, "text/plain", "");
    path = String();
}

/** 
 @fn void CServerWeb::handleIndex()
 @brief A new handler for index page to choose different index page between AP and station...
 @return no return value and no parameter

Now we can be connected in both mode AP and station so it is necessary to separate request from AP 
and station mode to serve the right page
*/
void CServerWeb::handleIndex(){
    DEFDPROMPT("handleIndex");
    // DSPL(dPrompt);
    // bool requestAP;
    IPAddress clientIP = server->client().remoteIP();
    IPAddress modeAPIP = _pcParam->getIPAdd();
    modeAPIP[3] = 0;
    clientIP[3] = 0;
    if (clientIP == modeAPIP) {
        DSPL(dPrompt + F("Mode AP index page"));
        handleSoftAPIndex();
    } else {
        DSPL(dPrompt + F("Mode Station index page"));
        handleFileRead("/");
    }
}

/** 
 @fn void CServerWeb::handelIOTESPConfPage()
 @brief /cfgpage action handler
 @return no return value and no parameter
 
Replace the place holder of the conf_tag.htm file by the config.json content
This handler is trigerred by apmodeindex.htm from simple href link
There is 2 step in this process display the conf page and compute the conf data.
This is the purpose of the next method : CServerWeb::handleIOTESPConfiguration to compute the data
*/
void CServerWeb::handelIOTESPConfPage(){
    // String confParam[] = {
    //       HTML_EMPLACEMENT_NAME
    //     , HTML_ALLLEDSONTIME_NAME
    //     , HTML_LEDLUM_NAME, HTML_HOSTNAME_NAME
    //     , HTML_SOFTAPIP_NAME, HTML_SOFTAPPORT_NAME
    //     , HTML_STATIONIP_NAME, HTML_STAGATEWAY_NAME
    //     , HTML_MAXRETRY_NAME
    // };
    String plugNames[] = {
          HTML_JSON_REDPLUGNAME
        , HTML_JSON_GREENPLUGNAME
        , HTML_JSON_BLUEPLUGNAME
        , HTML_JSON_YELLOWPLUGNAME
    };
    // String checkBox[] = {
    //       HTML_STARTINAP_NAME
    //     , HTML_DHCPMODE_NAME
    //     , HTML_FIRSTBOOT_NAME
    //     , HTML_POWERLEDECO_NAME
    // };
    String phParamTag;
    String param;
    DEFDPROMPT("Handle config html form");
    DSPL(dPrompt);
    String page;
    File confFormFile = SPIFFS.open(CONFIGFORMFILENAME, "r");
    if (confFormFile) {
        page = confFormFile.readString();
        // for (String p : confParam) {
        //     phParamTag = PALCEHOLDERTAG + p;
        //     param = ConfigParam::readFromJsonParam(p, "general");
        //     page.replace(phParamTag, param);
        // }
        String ph = String(PALCEHOLDERTAG);
        page.replace( ph + String(HTML_EMPLACEMENT_NAME), _pcParam->_emplacement);
        page.replace( ph + String(HTML_ALLLEDSONTIME_NAME), String(_pcParam->_allLedsOnTime));  
        page.replace( ph + String(HTML_LEDLUM_NAME), String(_pcParam->_ledsGlobalLuminosity));     
        page.replace( ph + String(HTML_HOSTNAME_NAME) , String(_pcParam->_host) );
        page.replace( ph + String(HTML_SOFTAPIP_NAME) , _pcParam->_addIP.toString() );
        page.replace( ph + String(HTML_SOFTAPPORT_NAME) , String(_pcParam->_serverPort) );
        page.replace( ph + String(HTML_STATIONIP_NAME) , _pcParam->_staIP.toString() );
        page.replace( ph + String(HTML_STAGATEWAY_NAME) ,_pcParam->_staGateway.toString() );
        page.replace( ph + String(HTML_MAXRETRY_NAME) , String(_pcParam->_STAmaxWifiConnectionRetries) );    
        int i = 0;    
        for (String p : plugNames) {
            phParamTag = PALCEHOLDERTAG + p;
            // param = ConfigParam::readFromJsonParam("nickName", p);
            param = _pPlugs[i]._nickName;   
            i++;      
            page.replace(phParamTag, param);
        }
        // for (String p : checkBox) {
        //     phParamTag = PALCEHOLDERTAG + p;
        //     //param = ConfigParam::readFromJsonParam(p, "general");
        //     DSPL(dPrompt + "p = " + param);
        //     param = (param == "ON" ? "checked" : "");
        //     page.replace(phParamTag, param);
        // }
        ph = String(PALCEHOLDERTAG);
        page.replace( ph + String(HTML_STARTINAP_NAME), String(_pcParam->_startInApMode?"checked":"") );
        page.replace( ph + String(HTML_DHCPMODE_NAME), String(_pcParam->_DHCPMode?"checked":"") );
        page.replace( ph + String(HTML_FIRSTBOOT_NAME), String(_pcParam->_firstBoot==ConfigParam::YES?"checked":"") );
        page.replace( ph + String(HTML_POWERLEDECO_NAME), String(_pcParam->_powerLedEconomyMode?"checked":"") );

        server->send(200, "text/html", page);
    } else {
        DSPL(dPrompt + F("form configuration not found"));
        server->send(404, "text/plain", "FileNotFound");
    }
}

void CServerWeb::handleIOTESPConfiguration(){
    DEFDPROMPT("handle configuration")
    if (!mainPowerSwitchState) { //We consider that the plug not respond :-(
        server->send(404, "text/plain", "Page not found");
        return;
    }
    /////////////////////////////////////////////////////////////////////////////
    //      DISPLAY URI                                                        //
    /////////////////////////////////////////////////////////////////////////////
    String uriReceived = server->uri();
    DSPL(dPrompt + F(" Received uri = ") + uriReceived);
    DSPL(dPrompt + " nbr de parametres : " + (String)server->args());
    String allArgs = F(" Received args : ");
    for (int i = 0; i < server->args(); i++) {
        allArgs += server->argName(i) + "=" + server->arg(i) + HTML_ALLARGS_SEPARATOR;
    }
    DSPL(dPrompt + allArgs);
    /////////////////////////////////////////////////////////////////////////////
    *_pRestartTempoLed = true;

    struct configItem {
        String name;
        String val;
    };

    // configItem confParam[] = {
    //     { HTML_EMPLACEMENT_NAME, "" },
    //     { HTML_ALLLEDSONTIME_NAME, "" },
    //     { HTML_LEDLUM_NAME, "" },
    //     { HTML_HOSTNAME_NAME, "" },
    //     { HTML_SOFTAPIP_NAME, "" },
    //     { HTML_SOFTAPPORT_NAME, "" },
    //     { HTML_STATIONIP_NAME, "" },
    //     { HTML_STAGATEWAY_NAME, "" },
    //     { HTML_MAXRETRY_NAME, "" },

    // };

    configItem plugsNickNames[] = {
        { HTML_REDPLUGNICK_NAME, "" },
        { HTML_GREENPLUGNICK_NAME, "" },
        { HTML_BLUEPLUGNICK_NAME, "" },
        { HTML_YELLOWPLUGNICK_NAME, "" },
    };
    //17 parameters

    //check box special process
    // configItem checkBoxes[] = {
    //     { HTML_POWERLEDECO_NAME, "" },
    //     { HTML_FIRSTBOOT_NAME, "" },
    //     { HTML_STARTINAP_NAME, "" },
    //     { HTML_DHCPMODE_NAME, "" },
    // };
    String parameter;

    parameter = extractParamFromHtmlReq(allArgs, HTML_EMPLACEMENT_NAME);
    if ( parameter != "" )  _pcParam->_emplacement = parameter;
    parameter = extractParamFromHtmlReq(allArgs, HTML_ALLLEDSONTIME_NAME );
    if ( parameter != "" )  _pcParam->_allLedsOnTime =  parameter.toInt();
    parameter = extractParamFromHtmlReq(allArgs, HTML_LEDLUM_NAME );
    if ( parameter != "" )  _pcParam->_ledsGlobalLuminosity = parameter.toInt();
    parameter = extractParamFromHtmlReq(allArgs, HTML_HOSTNAME_NAME );
    if ( parameter != "" )  _pcParam->_host = parameter;
    parameter = extractParamFromHtmlReq(allArgs, HTML_SOFTAPIP_NAME );
    if ( parameter != "" ) _pcParam->_addIP.fromString( parameter );
    parameter = extractParamFromHtmlReq(allArgs, HTML_SOFTAPPORT_NAME );
    if ( parameter != "" ) _pcParam->_serverPort = parameter.toInt();
    parameter= extractParamFromHtmlReq(allArgs, HTML_STATIONIP_NAME );
    if ( parameter != "" ) _pcParam->_staIP.fromString( parameter );
    parameter= extractParamFromHtmlReq(allArgs, HTML_STAGATEWAY_NAME );
    if ( parameter != "" ) _pcParam->_staGateway.fromString( parameter );
    parameter= extractParamFromHtmlReq(allArgs, HTML_MAXRETRY_NAME );
    if ( parameter != "" ) _pcParam->_STAmaxWifiConnectionRetries = parameter.toInt();
  
    

    //2 for loop for better debug display ;-)
    // int cpt = 0;
    // for (configItem i : confParam)
    //     confParam[cpt++].val = 
    // for (configItem i : confParam) {
    //     if (i.val != "") {
    //         // DSPL( dPrompt + "Write to json for " + i.name + " value : " + i.val );
    //         //ConfigParam::write2Json(i.name, i.val, CONFIGFILENAME);
    //         _pcParam->write2Json(i.name, i.val, CONFIGFILENAME);
    //     }
    // }

    _pcParam->_startInApMode = !( extractParamFromHtmlReq(allArgs, HTML_STARTINAP_NAME) == NOT_FOUND );
    _pcParam->_DHCPMode = !( extractParamFromHtmlReq(allArgs, HTML_DHCPMODE_NAME) == NOT_FOUND );
    _pcParam->_firstBoot = ( (extractParamFromHtmlReq(allArgs, HTML_FIRSTBOOT_NAME) == NOT_FOUND) ? (ConfigParam::NO):(ConfigParam::YES) );
    _pcParam->_powerLedEconomyMode = !( extractParamFromHtmlReq(allArgs, HTML_POWERLEDECO_NAME) == NOT_FOUND );

    DSPL( dPrompt + F("Start in AP mode : ") + String(_pcParam->_startInApMode) );
    DSPL( dPrompt + F("DHCP mode : ") + String(_pcParam->_DHCPMode) );
    DSPL( dPrompt + "first boot mode : " + ( (_pcParam->_firstBoot==ConfigParam::YES)?"YES":"NO") );
    DSPL( dPrompt + F("Power Led Economy mode mode : ") + String( _pcParam->_powerLedEconomyMode) );

    // cpt = 0;
    // for (configItem i : checkBoxes) {
    //     i.val = extractParamFromHtmlReq(allArgs, i.name);
    //     checkBoxes[cpt++].val = (i.val == NOT_FOUND ? "OFF" : "ON");
    // }
    // for (configItem i : checkBoxes) {
    //     // DSPL( dPrompt + "Write to json for " + i.name + " value : " + i.val);
    //     //ConfigParam::write2Json(i.name, i.val, CONFIGFILENAME);
    //     _pcParam->write2Json(i.name, i.val, CONFIGFILENAME);
    // }

    int cpt = 0;
    for (configItem i : plugsNickNames)
        plugsNickNames[cpt++].val = extractParamFromHtmlReq(allArgs, i.name);
    for (configItem i : plugsNickNames) {
        if (i.val != "") {
            String color = i.name.substring(0, i.name.indexOf('_'));
            DSPL(dPrompt + "plug name = " + color );
            for (int j = 0; j < 4; j++) {
                // DSPL( dPrompt + "plugName : " + plugs[j].getPlugName() );
                if (_pPlugs[j].getPlugName() == color) {
                    //DSPL(dPrompt + "set nickName " + color + " nickname = " + i.val );
                    //_pPlugs[j].writeToJson("nickName", i.val);
                    _pPlugs[j]._nickName = i.val;
                    DSPL(dPrompt + "get nickName " + color + " nickname = " + _pPlugs[j]._nickName );
                }
            }
        }
    }


    String date = extractParamFromHtmlReq(allArgs, "setDate");
    String time = extractParamFromHtmlReq(allArgs, "setTime");
    DSPL(dPrompt + date + " " + time);
    if (date != "" || time != "") {
        DateTime now = RTC_DS3231::now();
        if (time == "")
            time = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
        if (date == "")
            date = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
        date = date + " " + time;
        DSPL(dPrompt + " date/time to set : " + date);
        char* cstr = new char[date.length() + 1];
        strcpy(cstr, date.c_str());
        // CRtc::adjust(cstr);
        _pRtc->adjust(cstr);
    }

    _pcParam->_jsonWriteRequest = true; //only one flag is necessary to write all (config and plugs)

    /** @todo [NECESSARY]return to config page to confirm that values are taken into account */
    handelIOTESPConfPage();
}



/** 
 @fn void CServerWeb::handleNewCred()
 @brief fun tha handle new credential in response to handleSoftAPIndex...
 @return no return value and no parameter

 This function write credentials.json file in the SPIFFS with received SSID and password.
 
*/
void CServerWeb::handleNewCred(){
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
            if ( (ssid != "") & (ssid != NOT_FOUND) ) general[JSON_SSID_NAME] = ssid; 
            if ( (pass != "") & (pass != NOT_FOUND) ) general[ JSON_PPASS_NAME ] = pass ;
            if ( (softAPssid != "") & (softAPssid != NOT_FOUND) ) general[ JSON_APSSID_NAME ] = softAPssid ;
            if ( (sofATPpass != "") & (sofATPpass != NOT_FOUND) ) general[ JSON_APPASS_NAME ] = sofATPpass ;
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
    if ( _pcParam->getWifiMode() == "softAP" )
        handleSoftAPIndex();
    else
        handleFileRead("/");
    /** @todo [NECESSARY] Send an html page to confir that credentials was written */
    // server->send(200, "text/plain", returnPage );     
}

/** 
 @fn void CServerWeb::firstBootHtmlForm()
 @brief Special firsboot page handler...
 @return no return value and no parameter
 
 Firstboot special page provide a way to the user to set SSID and pass for AP or Station mode.
*/
void CServerWeb::firstBootHtmlForm(){
    /** DONE here 13/07/2019 if (firstBoot == tryStattion ){ add warning to the page} */ 
    DEFDPROMPT("Handle First boot html form");
    DSPL( dPrompt );
    String page;
    File firstBFormFile = SPIFFS.open(FIRSTBOOTFORMFILENAME, "r");
    if (firstBFormFile){
        page = firstBFormFile.readString();
        if (_pcParam->getFirstBoot() == ConfigParam::TRY ){
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
 @fn void CServerWeb::handleFirstBoot()
 @brief Special firsboot reponse handler...
 @return no return value and no parameter
 
 Firstboot special page provide a way to the user to set SSID and pass for AP or Station mode.
 
 Here we process the answer of the user to write credential file and switch to normal mode.
*/
void CServerWeb::handleFirstBoot(){
    // check parameters
    // if (mode == Station)  set firstBoot to tryStation and restart ESP
    // if (mode == AP) set firstBoot to OFF
    DEFDPROMPT( "handle First Boot "); 
    _pcParam->creatDefaultJson();
    //ConfigParam::write2Json( "firstBoot", "ON" ); //not very usefull
    _pcParam->write2Json( "firstBoot", "ON" );
    
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
        //ConfigParam::write2Json( "firstBoot", "OFF" );
        _pcParam->write2Json( "firstBoot", "OFF" );
        //ConfigParam::write2Json( "startInAPMode", "ON" );
        _pcParam->write2Json( "startInAPMode", "ON" );
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
        //ConfigParam::write2Json( "startInAPMode", "OFF" );
        _pcParam->write2Json( "startInAPMode", "OFF" );
        //ConfigParam::write2Json( "firstBoot", "TRYSTA" );
        _pcParam->write2Json( "firstBoot", "TRYSTA" );
        /** @todo [NECESSARY] replace reset by watchdog not refresh */
        ESP.reset();        
    }
    String returnPage = allArgs ;
    server->send(200, "text/plain", returnPage ); 
}

/** 
 @fn String CServerWeb::buildMacAddName( String prefix)
 @brief return a string from mac add...
 @param prefix the prefix of the wanted name example IoT_ESP
 @return a tring with the prefix followed by _MMNN

 Build a string by concatenate prefix provided with the 2 last octets of the mac address.
*/
String CServerWeb::buildMacAddName( String prefix){
    uint8_t mac[6];
    char macStr[18] = { 0 };
    // WiFi.macAddress( mac );
    _pWifiConnection->macAddress( mac );
    sprintf(macStr, "_%02X%02X", mac[4], mac[5]);
    return prefix+String(macStr);
    
}