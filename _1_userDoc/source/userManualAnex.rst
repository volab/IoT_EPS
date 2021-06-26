++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
User manual annexe
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: August 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top

.. index::
    pair: Exmple; Serial output example

====================================================================================================
Serial monitor output example
====================================================================================================
.. code::
    
    <Volab CSystem::init > Sketch start...
    <Volab CSystem::init >  Build : Oct 13 2020 @ 23:26:33
    <Volab CSystem::init > File system correctly Open @ setup level
    <Volab CSystem::init > File check !
    <Volab CSystem::init > file : /index.html is present
    <Volab CSystem::init > file : /config4.json is present
    <Volab CSystem::init > file : /firstboot.html is present
    <Volab CSystem::init > file : /js/main.js is present
    <Volab CSystem::init > file : /js/plug.js is present
    <Volab CSystem::init > file : /js/regExPatern.js is present
    <Volab CSystem::init > file : /js/table.js is present
    <Volab CSystem::init > file : /css/sidebar.css is present
    <Volab CSystem::init > file : /css/style.css is present
    <Volab CSystem::init > Result all files are present ? OK
    <Volab reading config param. > Mounting FS...
    <Volab reading config param. > File system mounted 
    <Volab reading config param. > reading config file
    	config file opened 
    <Volab reading config param. > Config file size : 1394
    <Volab CSystem::init > json mac add : A0:20:A6:17:3F:B1
    <Volab CSystem::init > Board Sation MAC add = A0:20:A6:17:3F:B1
    <Volab CSystem::init > Station equal add
    <Volab CSystem::init > json Soft AP mac add : A2:20:A6:17:3F:B1
    <Volab CSystem::init > Board Soft AP MAC add = A2:20:A6:17:3F:B1
    <Volab CSystem::init > AP equal add
    <Volab CSystem::init > I2C test start
    Write 0x10 to 1
    Write 0x12 to 2
    Read of reg 1 = 10
    Read of reg 2 = 12
    <Volab CSystem::init > Nano test ok
    <Volab CSystem::init > Display oled Logo
    <Volab CSystem::init:Stratup Messages > OLED Logo pause
    <Volab CSystem::init:Stratup Messages > OLED startup message pause
    <Volab CSystem::init > DS3231 Start date : 14/10/2020 22:15:51
    <Volab setUp > watchdog test 
    watchdog OK
    <Volab setUp > watchdog set to 30s.
    <Volab setUp > Main power state : ON
    <Volab setUp > number of plugs : 4
    <Volab write to jSon > redPlug : State = OFF
    <Volab reading config values for redPlug > Mode = Cyclique
    <Volab reading config values for redPlug > Etat = OFF
    <Volab reading config values for redPlug > Start time = 
    <Volab reading config values for redPlug > End time = 
    <Volab reading config values for redPlug > on duration = 1
    <Volab reading config values for redPlug > off duration = 2
    <Volab reading config values for redPlug > Cloned plug = 
    <Volab reading config values for redPlug > Relay on off count = 62
    <Volab reading config values for redPlug > Next time to switch : Mercredi 14/10/2020 22:17:27
    <Volab reading config values for redPlug > Jours : 
    <Volab write to jSon > greenPlug : State = ON
    <Volab reading config values for greenPlug > Mode = Manuel
    <Volab reading config values for greenPlug > Etat = ON
    <Volab reading config values for greenPlug > Start time = 
    <Volab reading config values for greenPlug > End time = 
    <Volab reading config values for greenPlug > on duration = 
    <Volab reading config values for greenPlug > off duration = 
    <Volab reading config values for greenPlug > Cloned plug = 
    <Volab reading config values for greenPlug > Relay on off count = 173
    <Volab reading config values for greenPlug > Jours : 
    <Volab write to jSon > bluePlug : State = ON
    <Volab reading config values for bluePlug > Mode = Manuel
    <Volab reading config values for bluePlug > Etat = ON
    <Volab reading config values for bluePlug > Start time = 
    <Volab reading config values for bluePlug > End time = 
    <Volab reading config values for bluePlug > on duration = 
    <Volab reading config values for bluePlug > off duration = 
    <Volab reading config values for bluePlug > Cloned plug = 
    <Volab reading config values for bluePlug > Relay on off count = 5
    <Volab reading config values for bluePlug > Jours : 
    <Volab write to jSon > yellowPlug : State = OFF
    <Volab reading config values for yellowPlug > Mode = Manuel
    <Volab reading config values for yellowPlug > Etat = OFF
    <Volab reading config values for yellowPlug > Start time = 
    <Volab reading config values for yellowPlug > End time = 
    <Volab reading config values for yellowPlug > on duration = 
    <Volab reading config values for yellowPlug > off duration = 
    <Volab reading config values for yellowPlug > Cloned plug = 
    <Volab reading config values for yellowPlug > Relay on off count = 2
    <Volab reading config values for yellowPlug > Jours : 
    <Volab setUp > Main power ON
    <Volab reading credentials > mounting FS...
    <Volab reading credentials > File system mounted
    <Volab reading credentials > Reading credit. file
    	Credit. file is opened
    <Volab setUp, Wifilink begin > Wifi mode in json = Station
    <Volab setUp, Wifilink begin > try to set autoconnect to off
    <Volab setUp, Wifilink begin > Mode autoconnect read from ESP : disabled
    <Volab setUp, Wifilink begin > Wifi is connected ? No
    <Volab setUp, Wifilink begin > Wifi def mode in FLASH : 3
    <Volab setUp, Wifilink begin > Stored Wifi default soft AP param : 
    <Volab setUp, Wifilink begin >     SSID len : 14
    <Volab setUp, Wifilink begin >     Stored SSID :PowerStrip_mac.
    <Volab WiFi mode > WIFI_STA and AP
    <Volab setUp, Wifilink begin > Try softAccess
    <Volab setUp, Wifilink begin > Try soft AP with : IoT_ESP_3FB1 and 123456789
    <Volab setUp, Wifilink begin > softAP : Ready
    <Volab setUp, Wifilink begin > SoftAP returned IP address = 192.168.95.42
    <Volab setUp, Wifilink begin > Host name which does not work with Android is : PowerStrip01
    <Volab setUp, Wifilink begin > Try to join : VoLab
    .....
    <Volab setUp, Wifilink begin > Number of Station wifi try : 5, max was : 30
    <Volab setUp, Wifilink begin > NTP enabled
    <Volab setUp, Wifilink begin > Adresse Wifi.localIP Station mode : 192.168.1.20
    <Volab write  param to jSon file > /config4.json
    <Volab write  param to jSon file >  general : staIP = 192.168.1.20
    <Volab setUp > NTP enable ? TRUE
    <Volab CSystem::timeServerCheck > check started
    <Volab CSystem::timeServerCheck > NTP Time : 14/10/2020 22:16:0
    <Volab write  param to jSon file > /config4.json
    <Volab write  param to jSon file >  general : ntpError = OFF
    Serial Command list :
    <h> ou <H> display this list
    <E> display status
    <C> Check DS3231 date
    <S JJ/MM/AAAA HH:MM:SS> returns code <O>
    <T HH:MM:SS> returns code <O>
    <s> set DS3231 by NTP server
    <J> for display config.json
    <W> display WIFI mode
    <P key value> write config parameter in json WARNING
    <I _newSSID> write SSID in credentials WARNING
    <i _wifiPass> write password in credentials WARNING
    <t various_param> for code test
    <N> nano IO expander test
    <O> nano out test HIGH
    <o> nano out test low
    <F> Find I2C device I2C scan
    <R> I2C recovery
    <c> I2C crash
    <a> for Ip address
    <w> for WiFi.printDig function
    <z> display credetial file
    <L> _newSoftAP_SSID> write SoftAP SSID in credentials WARNING
    <l> _wifiPass> write soft AP password in credentials WARNING
    <D> SPIFFS dir
    <j> display general part of config json file
    <d _filename> erase a file WARNING
    <e> display system status
    <p> display main power state
    <Volab setUp > Leds On config : -1
    <Volab setUp > Leds On lumi : 5
    <Volab setUp > [HTTP] begin...
    <Volab setUp > [HTTP] GET... http://www.google.fr/
    <Volab setUp > [HTTP] GET... code: 200
    <Volab setUp > Watchdog set to 10s with a refresh period to 5s
    <Volab setUp > Loop start

.. index::
    pair: Help; Commands


====================================================================================================
Serial command help
====================================================================================================
.. code::

    Serial Command list :
    <h> ou <H> display this list
    <E> display status
    <C> Check DS3231 date
    <S JJ/MM/AAAA HH:MM:SS> returns code <O>
    <T HH:MM:SS> returns code <O>
    <s> set DS3231 by NTP server
    <J> for display config.json
    <W> display WIFI mode
    <P key value> write config parameter in json WARNING
    <I _newSSID> write SSID in credentials WARNING
    <i _wifiPass> write password in credentials WARNING
    <t various_param> for code test
    <N> nano IO expander test
    <O> nano out test HIGH
    <o> nano out test low
    <F> Find I2C device I2C scan
    <R> I2C recovery
    <c> I2C crash
    <a> for Ip address
    <w> for WiFi.printDig function
    <z> display credetial file
    <L> _newSoftAP_SSID> write SoftAP SSID in credentials WARNING
    <l> _wifiPass> write soft AP password in credentials WARNING
    <D> SPIFFS dir
    <j> display general part of config json file
    <d _filename> erase a file WARNING
    <e> display system status
    <p> display main power state

====================================================================================================
Weblinks
====================================================================================================

.. target-notes::