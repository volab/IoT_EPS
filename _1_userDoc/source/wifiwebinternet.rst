++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Wifi, Web and internet
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: Ocotbre 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top


.. index:: 
   single: Wifi modes

.. _refWifiModes:

==================
WIFI Modes
==================

In Json config file, it is configured with: "startInAPMode" value,

No WiFi
==========
Also called simpleManualMode

When power on (by the wall plug not by the power switch) the powerStrip, maintain Push button plug 1

Power strip start in this mode independently of Json configured mode.

4 Big color LED flasf 20 times in purple.

In this very simple poor mode, powerstrip works only in manual mode with BP actions ON/OFF.

SoftAP
=========
EPS starts in this mode when value of "startInAPMode" parameter is "ON".

No acces to NTP server but all other functions work.

After 20 false tries of station mode, power Strip automaticly switch in this mode

Station
=========
EPS starts in this mode when value of "startInAPMode" parameter is "OFF".

The best functionnal mode ! With full web interface and others functions.

both mode STA and AP
=======================
July 2019 : reflexion when we start in DHCP station mode we don't know IP address of the IoT EPS.
One way to know it is to use a tool to scan the local network !
So why do not connect systematically in both mode !!!
Do it in new dev branch  !!!!!!!!!!!!!!!!!! 10 months of development to achieve this !!!!

====================================
IP address
====================================
AP and non DHCP IP address are class C address (subnet mask is 255.255.255.0 hardcoded )

.. index::
    single: Wifi LEDs

==================
WIFI LED behavior
==================
In Station mode, fast flashing (20 times 100ms, 100ms) before to try connection
and after slow flashing while waiting for connection.
(500ms with a 20 times time out - new in 24/12/2018). If no connection detected afte 20 tries
Automatically switch in SoftAP mode.

In Access Point LED FLash quickly (20 times 100ms-500ms) and 
led flash slowly (50ms-2s) while waiting for connection.

Cause WiFi.softAPConfig function is a blocking function. This is wrong : 
test on 24/12/2018 softAP is non blocking !

So - in summary - if power led is on and WIFI Led flash (50ms-2s) WIFI wait for connection in AP mode. 

It rises a new problem : in this state it is not possible to use plugs even in simple  manual mode 
with push button. 

Possible solution : check push button at startup if a particular combination is pressed,
plugs do not try to connect to wifi and work in simple manual mode.
In Dec 2018, push button
added pressing plug 0 while power on the strip cause no WIFI mode (color LED FLASH in RED to confirm)
This is : simpleManualMode (see above). To return to normal mode power off the strip 
(not by the power on/off button but by removing the strip from the wall plug)

===========================================
ESP8266 and its wifi managment !
===========================================
ESP8266 store credentials information in FLASH but how to access to them ???
And how to control them

Question how to erase wifi flash param ?

Memory mapping is not provided. Some peace of informations
like in SPIFFS description that provide the order of memory big blocks but not their respective add

Second question : how to directly access to flash memory ?

Perhaps with SPI lib 

https://github.com/esp8266/Arduino/blob/master/doc/libraries.rst#spi

Answer :

- ESP.flashRead(...)https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Esp.h
- ESP.flashWrite(..)
- ESP.flashEraseSector(...)
- ESP.eraseConfig() Erase all from start of the flash till -0x4000 about 16k
- no-documented function !


ESP-SDK ? nothing fond about erase

persistant(false) <=> do not write in flash but do not clear informations

Question 3: How to read  flash info  ?

Answer : call Espressif SDK functions::

    #include <user_interface.h> in
    Arduino\Croquis\hardware\esp8266com\esp8266\tools\sdk\include
    page 62/179 pdf ESP8266 Non-OS SDK API Reference 
    3.5.33. wifi_softap_get_config_default

.. code::

    struct softap_config {
        uint8 ssid[32];
        uint8 password[64];
        uint8 ssid_len;	// Note: Recommend to set it according to your ssid
        uint8 channel;	// Note: support 1 ~ 13
        AUTH_MODE authmode;	// Note: Don't support AUTH_WEP in softAP mode.
        uint8 ssid_hidden;	// Note: default 0
        uint8 max_connection;	// Note: default 4, max 4
        uint16 beacon_interval;	// Note: support 100 ~ 60000 ms, default 100
    };

ESP12E module Flash size : W25Q32 32Mbits/4Mo 256octets /pages 16384 pages

Could be erase by 16 ou 128 ou 256 -4(sectors)- or 32kB or even 64kB groups.

====================================================================================================
ESP8266Webserver
====================================================================================================
Documentation very hard to find

`In github readme`_

.. _`In github readme` : https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

Don't forget to `check the provided examples`_

.. _`check the provided examples` : https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/examples

`ESP8266Webserver Doxygen documentation`_  do not wast your time !

.. _`ESP8266Webserver Doxygen documentation` : https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html

We can `find this on Arduino`_  forum::

    As for the ESP8266WiFi documentation, it is here::
    The on() function is actually part of the ESP8266WebServer library. Most of the library 
    documentation for the ESP8266 core for Arduino is found here:
    https://arduino-esp8266.readthedocs.io/en/latest/index.html
    but for some reason the ESP8266WebServer library documentation is missing from those pages. 
    You can find it here:
    https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/README.rst

    https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
    Generally the ESP8266 libraries attempt to follow the API of the standard Arduino libraries 
    and only document the differences. You may find it useful to refer to the Arduino WiFi library 
    reference pages in addition to the ESP8266WiFi documentation:
    https://www.arduino.cc/en/Reference/WiFi


.. _`find this on Arduino` : https://forum.arduino.cc/index.php?topic=588866.0


`Arduino ESP8266 example readthedoc`_

.. _`Arduino ESP8266 example readthedoc` : https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/server-examples.html

Bind to a method 
====================================

`Explication sur Stackoverflow`_

.. _`Explication sur Stackoverflow` : https://stackoverflow.com/questions/32900314/esp8266webserver-setting-a-value-inside-a-class


===========================
WEB page development
===========================

HTML5 et css and bootstrap
jquery, jquery ui, ajax and popper

bootstrap from its CDN
https://www.bootstrapcdn.com/


.. index::
    single: Html Request

html requests
=====================

ipaddr/plugonoff?plug=redPlug...


192.168.1.42/plugonoff?COLOR=redPlug&Mode=Manuel&State=ON

Possible plugonoff requests:

- Mode=Manuel&State=ON&dureeOff=299 : dureeOff on minutes only
- Mode=Manuel&State=ON&dureeOff=299:59 : dureeOff on minutes and seconds
- Mode=Manuel&State=ON&hFin=23:59 : hFin only one format HH:MM
- Mode=Manuel&State=OFF
- Mode=Manuel&State=ON

Other request:

- /time
- /list
- /edit
- /cfgpage
- /cfgsen?lots of parameter...
- /ChangeCred?ssid=xxxx&pass=yyyy&softApSsid=ssidOfSoftApMode&softApPass=123456789



NTP server name
=================
The name reside in the IoT_EPS.h file and is not a config param through web config page

====================
Serveur html ESP8266
====================
Copy from example provided in ARDUINO IDE : ESP8266WebServer/FSBrowser

This example provide a lot of functions that managed file sending as css, jpg and so on

edit page
==============
Strange behavior with html extension

Le bouton parcourir tronc en htm et le visualisateur ne montre que les fichier htm

Edit.htm source code ? not provided in the .ino file

One possible source (but not really the same) :

https://github.com/gmag11/FSBrowser/blob/master/data/edit.html


================================
HTML IHM integration
================================
Start on March 2019

Used technologies:

- HTML5/css
- Javascipt
- JQuery
- Boostrap

Test list:

For all plugs

- manual ON/OFF :  OK on RED
- manual ON with OFF time : ok on RED
- manual ON with delay : ok on RED 1 minutes
- timer : RED plug ko, state no transmit: corrected ok
- timer red switched by bp : OK
- clone from green cyclic to bleu : ok

... see testAndErrorHandling.xlsx file for the rest of the tests

bugs found :

- manual hfin and dureeOff without parameter should be KO
- manual cleanup buton dont remove hfin and others param
- no default state in manual mode : corrected
- minuterie (timer mode) no default value for the ratio immediat start or differed start - corrected
- bug in ESP source side effect of main power switch  ?

improvments:
- add tips on main page : To refresh this page press F5

====================================================================================================
Weblinks
====================================================================================================

.. target-notes::