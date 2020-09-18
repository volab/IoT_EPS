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
void CWifiLink::begin( ESP8266WiFiClass &wifiRef, const bool simpleManualMode ){
    // _pWiFi = pWiFi;
    _wifiRef = wifiRef;
    _wifiCred.begin( );
    DEFDPROMPT("setUp, Wifilink begin");


    sysStatus.credFileErr.err( !_wifiCred.ready );
	wifiLed.begin( WIFILED, WIFILED_FLASH_FAST, WIFILED_FLASH_FAST );
	if ( !simpleManualMode ){
		int tryCount = 0;
        DSPL( dPrompt + F("Wifi mode in json = ") + cParam.getWifiMode() );
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

            
            displayWifiMode();
            DSPL( dPrompt + F("Try softAccess") );
            
            IPAddress apIP = cParam.getIPAdd();
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
		DSPL( dPrompt + F("Host name which does not work with Android is : ") + cParam.getHostName() );
		// MDNS.begin( cParam.getHostName().c_str() ); //ne fonctionne pas sous Android
        /** @todo [OPTION] mDNS.begin issue on github #4417 https://github.com/esp8266/Arduino/issues/4417
        try : LEAmDNS - Multicast DNS Responder #5442 -for now leav commented*/
        
        /////////////////////////////////////////////////////////////////////////////
        //  Station mode                                                           //
        /////////////////////////////////////////////////////////////////////////////
        if ( cParam.getWifiMode() == "client" && !sysStatus.credFileErr.isErr()
                || cParam.getWifiMode() == "Station" ){ // Station WIFI mode    

            if ( !cParam.getDHCPMode() ){
                IPAddress staIP = cParam.getStaIP();
                IPAddress staGateway = cParam.getStaGatewayIP();
                IPAddress DNS1;
                DNS1.fromString( "8.8.8.8");
                /** NO we decide to leave in the code as it is. change DNS as a config param */
                _wifiRef.config( staIP, staGateway, IPAddress(255, 255, 255, 0), DNS1 );
                DSPL( dPrompt + F("No DHCP mode, static IP add") );
            } 
            _wifiRef.begin( _wifiCred.getSsid(), _wifiCred.getPass() );
            DSPL(  dPrompt + F("Try to join : ") + _wifiCred.getSsid() );
            wifiLedFlash( wifiLed, WIFILED_FLASH_COUNT );
            wifiLed.begin( WIFILED, WIFILED_FLASH_SLOW, WIFILED_FLASH_SLOW );
            while (_wifiRef.status() != WL_CONNECTED) {
                delay(500);
                wifiLed.update();
                DSP(".");
                //a normal acces should came in 18 try
                tryCount++;
                if ( watchdog.isItTimeTo() ) watchdog.refresh();
                if (tryCount == cParam.getSTAMaxRetries() ) break;  
            }
            wifiLed.stop();
            wifiLed.high();
            DSP( "\n" + dPrompt + F("Number of Station wifi try : ") + (String)tryCount );
            DSPL( ", max was : " + String( cParam.getSTAMaxRetries() ) );
            if ( _wifiRef.status() == WL_CONNECTED){
                sysStatus.ntpEnabled = true;
                String staIP =  WiFi.localIP().toString();
                DSPL(  dPrompt + F("Adresse Wifi.localIP Station mode : ") \
                    + staIP );
                    ConfigParam::write2Json( "staIP", staIP );
                if ( cParam.getFirstBoot() == ConfigParam::TRY ){
                    ConfigParam::write2Json( "firstBoot", "OFF" );
                    cParam.setFirstBoot( ConfigParam::NO );
                }                    
            } else { 
                _wifiRef.disconnect();
                sysStatus.ntpEnabled = false;
                wifiLed.low();
            }    
        }
	} else {
		DSPL(  dPrompt + F("Enter in simple manual mode") );
		cParam.setWifiMode( "No wifi" );
		simpleManualModeChaser();
    }

}

