/**
 @file CWifiLink.cpp
 @author J.SORANZO
 @date 05/09/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Implementation file of the class CWifiLink
*/ 


#include "CWifiLink.h"

// void CWifiLink::begin( ESP8266WiFiClass * pWiFi, ESP8266WiFiClass &wifiRef ){
void CWifiLink::begin( ESP8266WiFiClass &wifiRef, const bool simpleManualMode
                        ,ConfigParam *pcparam, CSysStatus *pcSysStatus, CFlasherNanoExp *pwifiled ){
    // _pWiFi = pWiFi;
    _wifiRef = wifiRef;
    _wifiCred.begin( );
    _cParam = pcparam;
    _pcSysStatus = pcSysStatus;
    _pwifiled = pwifiled;
    DEFDPROMPT("setUp, Wifilink begin");


    _pcSysStatus->credFileErr.err( !_wifiCred.ready );
	_pwifiled->begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_FAST );
	if ( !simpleManualMode ){
		int tryCount = 0;
        DSPL( dPrompt + F("Wifi mode in json = ") + _cParam->getWifiMode() );
        DSPL( dPrompt + F("try to set autoconnect to off"));
		_wifiRef.setAutoConnect(false); //to allways control wifi connection
		// WiFi.setAutoConnect(true); //to allways control wifi connection
		DSP( dPrompt + F("Mode autoconnect read from ESP : "));
		DSPL( _wifiRef.getAutoConnect()?"enabled":"disabled");
		DSPL( dPrompt + F("Wifi is connected ? ") +  String(_wifiRef.isConnected()?"Yes":"No") );
        _wifiRef.persistent(false);
        _wifiRef.mode(WIFI_AP_STA);
        /*******************************************************************************************
        
        *******************************************************************************************/
        DSPL( dPrompt + F("Wifi def mode in FLASH : ") + String(wifi_get_opmode_default	() ) );
        softap_config	config;
        wifi_softap_get_config_default(&config);
        DSPL( dPrompt + "Stored Wifi default soft AP param : " );
        DSPL( dPrompt + F("    SSID len : ") + config.ssid_len );
        DSP( dPrompt + F("    Stored SSID :") );
        for ( int i = 0; i < config.ssid_len ; i++ ){
            DSP( char(config.ssid[i]) );
        }
        DSPL( "." );

        if( 1 ){

            //displayWifiMode();           

            
            _displayWifiMode();
            DSPL( dPrompt + F("Try softAccess") );
            
            IPAddress apIP = _cParam->getIPAdd();
            _wifiRef.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            // cParam.setWifiMode( "softAP" ); // not in the config file just for temorary mode
            /** DONE review the interest of keeping code below! */
            //As it is only debug informations leave it. When debug define will be turn off
            //this peace of code should desapear at the coompilation time.
            if ( _wifiCred.ready ){
                DSPL( dPrompt + "Try soft AP with : " + _wifiCred.getSoftApSsid() 
                        + " and " + _wifiCred.getSoftApPass() );
                DSP( dPrompt + F("softAP : "));
                DSPL(_wifiRef.softAP(_wifiCred.getSoftApSsid(),
                    _wifiCred.getSoftApPass() )?F("Ready"):F("Failed!"));
                IPAddress myIP = _wifiRef.softAPIP();
                DSPL( dPrompt + "SoftAP returned IP address = " + myIP.toString()  );
            }
        }
		DSPL( dPrompt + F("Host name which does not work with Android is : ") + _cParam->getHostName() );
		// MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
        /** @todo [OPTION] mDNS.begin issue on github #4417 https://github.com/esp8266/Arduino/issues/4417
        try : LEAmDNS - Multicast DNS Responder #5442 -for now leav commented*/
        
        /////////////////////////////////////////////////////////////////////////////
        //  Station mode                                                           //
        /////////////////////////////////////////////////////////////////////////////
        if ( _cParam->getWifiMode() == "client" && !_pcSysStatus->credFileErr.isErr()
                || _cParam->getWifiMode() == "Station" ){ // Station WIFI mode    

            if ( !_cParam->getDHCPMode() ){
                IPAddress staIP = _cParam->getStaIP();
                IPAddress staGateway = _cParam->getStaGatewayIP();
                IPAddress DNS1;
                DNS1.fromString( "8.8.8.8");
                /** NO we decide to leave in the code as it is. change DNS as a config param */
                _wifiRef.config( staIP, staGateway, IPAddress(255, 255, 255, 0), DNS1 );
                DSPL( dPrompt + F("No DHCP mode, static IP add") );
            } 
            _wifiRef.begin( _wifiCred.getSsid(), _wifiCred.getPass() );
            DSPL(  dPrompt + F("Try to join : ") + _wifiCred.getSsid() );
            _wifiLedFlash( _pwifiled, WIFILED_FLASH_COUNT );
            _pwifiled->begin( WIFILED, WIFILED_FLASH_SLOW, WIFILED_FLASH_SLOW );
            while (_wifiRef.status() != WL_CONNECTED) {
                delay(500);
                _pwifiled->update();
                DSP(".");
                //a normal acces should came in 18 try
                tryCount++;
                if ( watchdog.isItTimeTo() ) watchdog.refresh();
                if (tryCount == _cParam->getSTAMaxRetries() ) break;  
            }
            _pwifiled->stop();
            _pwifiled->high();
            DSP( "\n" + dPrompt + F("Number of Station wifi try : ") + (String)tryCount );
            DSPL( ", max was : " + String( _cParam->getSTAMaxRetries() ) );
            if ( _wifiRef.status() == WL_CONNECTED){
                _pcSysStatus->ntpEnabled = true;
                String staIP =  WiFi.localIP().toString();
                DSPL(  dPrompt + F("Adresse Wifi.localIP Station mode : ") \
                    + staIP );
                    ConfigParam::write2Json( "staIP", staIP );
                if ( _cParam->getFirstBoot() == ConfigParam::TRY ){
                    ConfigParam::write2Json( "firstBoot", "OFF" );
                    _cParam->setFirstBoot( ConfigParam::NO );
                }                    
            } else { 
                _wifiRef.disconnect();
                _pcSysStatus->ntpEnabled = false;
                _pwifiled->low();
            }    
        }
	} else {
		DSPL(  dPrompt + F("Enter in simple manual mode") );
		_cParam->setWifiMode( "No wifi" );
		simpleManualModeChaser();
    }

}



void CWifiLink::_displayWifiMode(){
    DEFDPROMPT("WiFi mode")
    DSP( dPrompt ) ;
    String s_wifiMode;
    //WIFI_OFF = 0, WIFI_STA = 1, WIFI_AP = 2, WIFI_AP_STA = 3
    switch ( _wifiRef.getMode() ){
        case 0: s_wifiMode = F("WIFI_OFF"); break;
        case 1: s_wifiMode = F("WIFI_STA"); break;
        case 2: s_wifiMode = F("WIFI_AP"); break;
        case 3: s_wifiMode = F("WIFI_STA and AP"); break;
        default : s_wifiMode = F("???");
    }
    DSPL( s_wifiMode );
}


void CWifiLink::_wifiLedFlash( CFlasherNanoExp *pled, int count ){
    
	while ( pled->getChangeStateCpt() < count ){
		pled->update();
		yield();
	}
    pled->stop();
}