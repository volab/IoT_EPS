/**
* @file serverFunction.h

* @author J.Soranzo
* @date 27/10/2018
* @copyright 2018 CC0
* @version 1.0
* @brief fichier d'entête des fonction dédiées au serveur html pour essai


*/
#ifndef SERVEURFUNC_H
#define SERVEURFUNC_H
#include "IoT_EPS.h"
// #include <Arduino.h>

extern ESP8266WebServer server;

void handleRoot();
void handleNotFound();
#endif