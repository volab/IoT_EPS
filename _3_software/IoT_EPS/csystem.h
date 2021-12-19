/**
 @file csystem.h
 @author J.SORANZO
 @date 30/06/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Fichier d'entête de la classe CSystem
*/

#include "IoT_EPS.h"
// #include "oledMessages.h"

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
					, ESP8266WiFiClass *wifi, CNanoI2CIOExpander *pNanoExp, Adafruit_SSD1306 *pdisplay
                    , CJsonIotEps *pjsonData
                      );
		NTPClient *_pTimeclient;
		void timeServerCheck();
        void oledLoopBackScreen();
    
        /**
        @fn void oledDisplayDate()
        @brief Display date on oled display delay corresponding line befor
        @return not param and no return value
        
        This method call CSystem::_oledBlankLine before displaying anything
        */
        void oledDisplayDate();



        void oledDisplaySate();
        void oledDisplayIps();
        void oledDsiplayShutDown();

        /**
         @fn void CSystem::oledLoopChangeDispayIf()
         @brief Change display information if it is time in the loop
         @return not param and no return value
        
        Change display evry seconds. it concerne the date and status ligns only.
        */
        void oledLoopChangeDispayIf();

        void setPlugsAdd( CPowerPlug *plugs );

	private:

        /**
         @fn void _oledBlankLine(int16_t x, int16_t y)
         @brief This very dedicat method clear a line of oled display from x,y coordinate.
         @param x start pixel
         @param y start pixel (not line number)
         @return return value description's
        
        This method remove 19c(hard coded) fom x,y 
        */
        void _oledBlankLine(int16_t x, int16_t y);



        static const unsigned char logoLab[1024];
        static const unsigned char loopBackScreen[1024];
		void _oledStartMessagesManager();
		ConfigParam *_pcParam;
		Credential _wifiCred;
		CRtc _rtc;
		//ESP8266WebServer *_pServer;
		CSysStatus *_psysStat;
		FS *_pFileSystem;
		Adafruit_SSD1306 *_pDisplay;
        CPowerPlug *_pPlugs;
		const String *_pNecessaryFiles; //no need to keep if only used in init()

        unsigned long _oledPrevMillis;
        unsigned long _oledRefreshPeriod; //in seconds
        uint8_t _oledCptPlugToDisplay;
        uint8_t _oledCptErrToDisplay=0;
        uint8_t _oledDivSysState = (uint8_t)OLED_SYSTEM_STATE_DISPLAY_DIV;
        CJsonIotEps* _pJsonData;

		

};

#endif


