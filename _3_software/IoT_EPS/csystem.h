/**
 @file csystem.h
 @author J.SORANZO
 @date 30/06/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Fichier d'entête de la classe CSystem
*/

#include "IoT_EPS.h"
#include "oledMessages.h"

#ifndef CSYSTEM_H
#define CSYSTEM_H

/**
* @class  CSystem csystem.h
* @brief Classe qui controle l'ensemble du system

Tentative de clarification du code
*/
class CSystem
{
	public:
		void init( WiFiUDP &ntpUDP, CSysStatus *psysStat, FS *pFileSyst, ConfigParam *pcParam,
					const String *necessaryFileList, int necessaryFileNbr, String buildInfo
					, ESP8266WiFiClass *wifi, CNanoI2CIOExpander *pNanoExp, Adafruit_SSD1306 *pdisplay  );
		NTPClient *_pTimeclient;
		void timeServerCheck();
	private:
		ConfigParam *_pcParam;
		Credential _wifiCred;
		CRtc _rtc;
		//ESP8266WebServer *_pServer;
		CSysStatus *_psysStat;
		FS *_pFileSystem;
		Adafruit_SSD1306 *_pDisplay;
		const String *_pNecessaryFiles; //no need to keep if only used in init()
		static const unsigned char logoLab[1024];
		void _oledStartMessagesManager();
		

};

#endif


