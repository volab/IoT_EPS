/**
* @file serverFunction.h

* @author J.Soranzo
* @date 27/10/2018
* @copyright 2018 CC0
* @version 1.0
* @brief fichier d'entête des fonction dédiées au serveur html
*/
#ifndef SERVEURFUNC_H
#define SERVEURFUNC_H
#include "IoT_EPS.h"
// #include <Arduino.h>

extern ESP8266WebServer *server;

// void handleRoot();
void handleNotFound(); /**< @brief to handle page not found in SPIFFS and with other functions*/
void displayTime();     /**< @brief A simple page in the c code -for exemple*/

String getContentType(String filename);
bool handleFileRead(String path); /**< @brief very important function*/
void handleFileUpload();
void handleFileDelete();
void handleFileCreate();
void handleFileList();
void handleSoftAPIndex();
void handleNewCred();
void firstBootHtmlForm();
void handleFirstBoot();
String buildMacAddName( String prefix);
String extractParamFromHtmlReq( String allRecParam, String param );


// void handlePlugConfig();
void handlePlugOnOff();
void handleIOTESPConfiguration();
void handelIOTESPConfPage();
void handleIndex();
#endif