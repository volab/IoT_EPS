++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
User manual annexe
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: August 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top

====================================================================================================
Serial monitor output example
====================================================================================================
.. code::
    
    <Volab setUp > Sketch start...
    <Volab setUp > DS3231 Start date : 6/2/2106 6:36:58
    <Volab setUp >  Build : Aug 14 2020 @ 21:41:12
    <Volab setUp > File system corectly Open @ setup level
    <Volab setUp > File check !
    <Volab setUp > file : /index.html is present
    <Volab setUp > file : /config4.json is present
    <Volab setUp > file : /firstboot.html is present
    <Volab setUp > file : /js/main.js is present
    <Volab setUp > file : /js/plug.js is present
    <Volab setUp > file : /js/regExPatern.js is present
    <Volab setUp > file : /js/table.js is present
    <Volab setUp > file : /css/sidebar.css is present
    <Volab setUp > file : /css/style.css is present
    <Volab setUp > Result all files are present ? OK
    <Volab reading config param. > Mounting FS...
    <Volab reading config param. > File system mounted 
    <Volab reading config param. > reading config file
        config file opened 
    <Volab reading config param. > Config file size : 1373
    <Volab setUp > json mac add : 38:2B:78:04:B9:F9
    <Volab setUp > Board Sation MAC add = 38:2B:78:04:B9:F9
    <Volab setUp > equal add
    <Volab setUp > json Soft AP mac add : 3A:2B:78:04:B9:F9
    <Volab setUp > Board Soft AP MAC add = 3A:2B:78:04:B9:F9
    <Volab setUp > equal add
    Write 0x10 to 1
    Write 0x12 to 2
    Read of reg 1 = 10
    Read of reg 2 = 12
    <Volab setUp > Nano test ok
    <Volab setUp > watchdog test OK
    <Volab setUp > watchdog set to 30s.
    <Volab setUp > Main power state : ON
    <Volab setUp > number of plugs : 4
    <Volab write to jSon > redPlug : State = OFF
    <Volab reading config values for redPlug > Mode = Manuel
    <Volab reading config values for redPlug > Etat = OFF
    <Volab reading config values for redPlug > Start time = 
    <Volab reading config values for redPlug > End time = 
    <Volab reading config values for redPlug > on duration = 
    <Volab reading config values for redPlug > off duration = 
    <Volab reading config values for redPlug > Cloned plug = 
    <Volab reading config values for redPlug > Relay on off count = 94
    <Volab reading config values for redPlug > Jours : 
    <Volab write to jSon > greenPlug : State = OFF
    <Volab reading config values for greenPlug > Mode = Manuel
    <Volab reading config values for greenPlug > Etat = OFF
    <Volab reading config values for greenPlug > Start time = 
    <Volab reading config values for greenPlug > End time = 
    <Volab reading config values for greenPlug > on duration = 
    <Volab reading config values for greenPlug > off duration = 
    <Volab reading config values for greenPlug > Cloned plug = 
    <Volab reading config values for greenPlug > Relay on off count = 123
    <Volab reading config values for greenPlug > Jours : 
    <Volab write to jSon > bluePlug : State = OFF
    <Volab reading config values for bluePlug > Mode = Manuel
    <Volab reading config values for bluePlug > Etat = OFF
    <Volab reading config values for bluePlug > Start time = 
    <Volab reading config values for bluePlug > End time = 
    <Volab reading config values for bluePlug > on duration = 
    <Volab reading config values for bluePlug > off duration = 
    <Volab reading config values for bluePlug > Cloned plug = 
    <Volab reading config values for bluePlug > Relay on off count = 22
    <Volab reading config values for bluePlug > Jours : 
    <Volab write to jSon > yellowPlug : State = OFF
    <Volab reading config values for yellowPlug > Mode = Manuel
    <Volab reading config values for yellowPlug > Etat = OFF
    <Volab reading config values for yellowPlug > Start time = 
    <Volab reading config values for yellowPlug > End time = 
    <Volab reading config values for yellowPlug > on duration = 
    <Volab reading config values for yellowPlug > off duration = 
    <Volab reading config values for yellowPlug > Cloned plug = 
    <Volab reading config values for yellowPlug > Relay on off count = 9
    <Volab reading config values for yellowPlug > Jours : 
    <Volab setUp > Main power ON
    <Volab reading credentials > mounting FS...
    <Volab reading credentials > File system mounted
    <Volab reading credentials > Reading credit. file
        Credit. file is opened
    <Volab setUp > Wifi mode in json = Station
    <Volab setUp > try to set autoconnect to off
    <Volab setUp > Mode autoconnect read from ESP : enabled
    <Volab setUp > Wifi is connected ? No
    <Volab setUp > Wifi def mode in FLASH : 2
    <Volab setUp > Stored Wifi default soft AP param :   ,Stored SSID :ESP-04B9F9.
    <Volab WiFi mode > WIFI_STA and AP
    <Volab WiFi mode > WIFI_STA and AP
    <Volab setUp > Try softAccess
    <Volab setUp > Try soft AP with : powerStrip01_mac and plusDe8c
    <Volab setUp > softAP : Ready
    <Volab setUp > SoftAP returned IP address = 192.168.95.42
    <Volab setUp > Host name that not work with Android is : PowerStrip01
    <Volab setUp > Try to join : VoLab
    ...................
    <Volab setUp > Number of Station wifi try : 19, max was : 30
    <Volab setUp > Adresse Wifi.localIP Station mode : 192.168.1.22
    <Volab write  param to jSon file > /config4.json
    <Volab write  param to jSon file >  general : staIP = 192.168.1.22

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