+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
IOT Electrical Power Strip Software development documentation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. toctree::
   :maxdepth: 2
   :caption: Others related pages
   :titlesonly:

   firstboot
   plugmodes
   configAndParam
   wifiwebinternet   
   curentSensing
   variable

.. contents:: Table of Contents
    :backlinks: top



=============================
Source code documentation
=============================

Source code documentation provide a lot of informations
 
 `<codeDoc\\html\\index.html>`_

====================================================================================================
Software architecture
====================================================================================================
Some words on software architecture @13/07/2020

Major points
====================================================================================================

one main ino file with its .h : IoT_EPS
in the header file we can find includes and config informations. (to be changed - see project
todo list)

A lot of usage of global variables and objects (not very optimal).

:ref:`See variables list<refVariableList>`

Usage of one big json file (except for credentials) to store plugs information and 
application parameters. Not optimal.

Usage of static functions in some object like Crtc.

Usage of a pseudo object in SerialCommand (just a struct)

The embedded html server is based on ESP8266webserver class 

file system globale SPIFFS is based on ESP8266 core

Operations
====================================================================================================
An array of 4 plugs object manage the behavior of the plug. Events from wifi trigs 
web server functions. The main part of the jobs is to write data in the json file that it is resend
to the user's navigator.

Timing are managed by CRtc a derived class from rtc from RTClib.

The wifi : after a long expectation where I navigate between station mode or softAP mode. Finally,
i activate the 2 modes simultaneously.


===========================
Progress of development
===========================
#. Display single static html page: ok
#. Affichage page html fichier SPIFFS : ok
#. Affichage de l'heure à partir d'une page en dur dans le code : ok
#. Affichage page avec CSS : ok
#. Gestion des mode wifi SoftAP vs client : ok
#. reception d'une action via un bouton :  ok
#. lecture du fichier de configuration : ok
#. intégration MCP23017 : ok
#. lecture du fichier de configuration config3.json : ok
#. gestion bouton poussoir mécanique : ok
#. Write json file : ok
#. Traitement de la requete html avec analyze, exécution et écriture json: ok
#. manage wif led : ok
#. integrate nano expander with analog inputs : ok
#. scan I2C response 57 and 58 nano IoExpander !!!! not a bug simply DS3231 board has 2 component
   DS3231 an EEPROM ! OK
#. Time managment strategy : ok
#. review work without rtc component strategy ok
#. review work without NTP access strategy ok
#. define rtc component versus NTP update strategy ok
#. suppress html replies if main power is off ok
#. generate a unique server name  ok

#. Error handling improvement 95% (todo display low error with LED ? Which one : power led ?)
#. configuration page (see softdev.rst)

#. power measurement

#. exhaustive test of hebdo mode : 95%
#. write index special page for softAP Mode with local boostrap or other light js.framework 5%
#. prepare an infographie résumant fonctionnalité et besoin : 
#. Write user manual : 1%
#. Write builder manual
#. rewrite main program setup and loop function with more object oriented structure 15%
#. add OLED display managment in accordance of its hardware implementation of course

Don't forget the todo list of the doxygen documentation

====================================================================================================
More object oriented rewriting (August 2020)
====================================================================================================

see in :ref:`variable list<refVariableList>`




.. index::
    single: Naming

====================================
Naming convention
====================================

Référence : config4.json


====================================
Remember
====================================

#. see javascript http request to perform DELETE: obsolete



============================
Software development choice
============================
wifi access point

Html pages are in the file system SPIFFS

Why do not use wifi manager ?
=========================================

====================================
Displaying plugs mode only with LED
====================================

Problem : how to displays functional mode of a plug without the web interface

Problem2 : is it really necessary ?

Solution1: Use the little plug red LED. When OFF flash 1 shortly one time for mode 1 manual to five
 time for mode 5 Clone. When ON invert ton and toff of the flasher

Solution2: use color LED with flash capability one time for mode manual to 5 times to mode Clone
with a long time between group of flash 3 seconds for example.

Implemented solution : n°1 with the little specialPB pushed in the same time as the plug Push Button

Advice : retain special BP some seconds before pushing plug's PB to avoid to swith the plug.

==============
IOExpander
==============

The following text is for history only and it is obsolète:

When we define hardware pin usage, we decide to use IOEpander MPC23017.
Due to this choice=, we need to use a new lib Adafruit_MCP23017.h

Available method:

.. code::

    void begin(uint8_t addr);
    void begin(void);

    void pinMode(uint8_t p, uint8_t d); // 0<= p < 16
    void digitalWrite(uint8_t p, uint8_t d);
    void pullUp(uint8_t p, uint8_t d);
    uint8_t digitalRead(uint8_t p);

    void writeGPIOAB(uint16_t); /: A priori on peut écrire sur un  port en entrée sans risque
    uint16_t readGPIOAB();
    uint8_t readGPIO(uint8_t b); // b=0 => PORTA, else PORTB

    void setupInterrupts(uint8_t mirroring, uint8_t open, uint8_t polarity);
    void setupInterruptPin(uint8_t p, uint8_t mode);
    uint8_t getLastInterruptPin();
    uint8_t getLastInterruptPinValue();
  
Adresse par défaut: 0x20 (avec les 3 broches d'adresse à 0)

En premier mouture, essai avec la librairie directement mais en deuxième monte, faire une classe
qui prennent en charge la gestion du temps (classe Flasher dédiée au MCP)

Deuxième mouture clréation de la class CPowerPlug avec utilisation de variable static

_initDone et _mpc (mpc étant la ressource commune à toutes les instances de la classe)

.. important::

    J'ai choisi d'utiliser une broche dédiée pour la LED d'état des plugs.
    On aurait pu utiliser la broche de commande du relais mais au cas où les 2
    seraient inversées l'une par rapport à l'autre, cela apporte plus de liberté.

During development, to get more digital IO and 4 analog input, we decide to add a ARDUINO Nano as 
an I2C IO expander (see Hardware dev doc)

.. index::
    single: Error handling
    
==================================
Error handling
==================================

.. figure:: image/ressourcesIot_ESP.svg
   :alt: IoT_ESP res
   :align: center
   
   IoT_EPS ressources tree

**All below informations are obsoletes.** See dedicated Excel file ``testAndErrorHandling.xlsx`` under
``_1-1_tests`` subdirectory.

Buildin test error BIT

PBIT : preliminary BIT

#. File system
#. Config param (JSON config file)
#. Credentials file (not in firstboot mode) - check its structure
#. I2C acces
#. rtc
#. only in Station mode and after WIFI connection, check NTP access


CBIT : Continus BIT every loop cycle, check :
 - I2C acces (only one retry)
 - RTC access
 - JSON config file
 - File system 
 - NTP access
 
...

 - current monitoring for ON plugs and if it is possible with the choosen sensor when currents will 
   be very low

Not in CBIT
 - WIFI state if in Station mode and/or AP mode ???
 
Because when wifi is down ( if our wifi box shutdown, for example, EPS should continue to work)

Can we work without File system or Json error ? No, fatal error => RED LED FLash 
 The system won't be started so no special web page index

Can we work without credential file ? Yes start in AP mode : OK

Check credentials.json structure

Can we work without I2C and/or nanoI2CIOExpander ? No, fatal error : OK

Can we work without RTC ? No, in the first release of IoT_EPS we consider that when one component
is ko the entire EPS is ko (no degraded mode). 

Perhaps in future version of the EPS, we can imagine that we work without DS3231 and only with
NTP server and the ARDUINO Time.h. This version of the EPS could only work in Station mode.

Can we work without internet connection or Wifi in station mode ?
 yes in softAP mode Refine softAP mode behavior
 
 Can we work without NTP server ? Yes (it could be temporary down)
 
.. important::
 
    How to display no fatal error ? the only one is NTP error all other error are FATAL
    We decide to only display on index html page


.. index::
    single: Time managment


================================
Time managment strategy
================================

Normal

No NTP server (no Wifi)

First of all, what is the time usage in the EPS ? bool CPowerPlug::isItTimeToSwitch() =>
CRtc::now().unixtime() <=>  DS3231::now().unixtime()

if NTP is reachable ie in Station mode and all is ok update DS3231 time every 15mn.
else do not update ds3231 and work with its time !

if NTP not reachable or in AP Mode the time can be updated by configuration page.

NTP server configuration ? not configurable for now only in IoT_EPS.h

RTC on error strategy, No RTC component

====================================================================================================
I2C address
====================================================================================================
- watchdog : 0x26 (defined in cattiny_i2C_watchdog.h)
- ioexpender : 0x58 (ored with D13) - defined in the ARDUINO NANO code
- DS3231 : 0x68 defined in RTClib.h
- +EEPROM on DS3231 1010011 normaly 0x53 base add is 0x50 and I have solder A2 slot
- OLED 0x3C

There is 3 pull-up on the board.


================================
RTC DS3231 EEPROM access
================================
nano ADD is 58

I2C add of EEPROM AT24C32 is 57
Changed to 0x53

Ok but why access to this EEPROM ? 
Perhaps to store a copy of config3.json

Live time2 ? 10^6 write cycle

8 bytes/page 4ko

.. index::
    single: Lives times

===================================
Livetime of ESP8266 flash SPIFFS
===================================
hypothesis :
- 4 plugs that work in clycle mode 1 minutes on and 1 minutes off
- 4 plugs not synchronyzed
With this hyp. the 4write/minutes 

WEMOS D1 Flash is Ai ESP12-F module W25Q32 pour 32Mbits soit 4Mo
100k erase/write cycle

25k minutes = 416 hours = 17 days

But it is a very hard hypothesis

A great question : what is the realistic usage ?

- one On/off cycle by hour on each plug every days only 12 hours by days
  25k hours /12 <=> 2083 days <=> more than 5 years
 
====================================
 Livetime of the relays
====================================
 10^7 time 


===============================
Usefull Tools
===============================

On Android : `Network IP Scanner`_ from homework.

On PC : `Angry IP Scanner`_


.. _`Network IP Scanner` : https://play.google.com/store/apps/details?id=com.network.networkip&hl=fr
.. _`Angry IP Scanner` : https://angryip.org/
    
===============================
Usefull Documentation
===============================

Html server
=====================

Exemples ESP html serveurs:

C:\MountWD\Donnees\OneDrive\Donnees\008_iao_wrk\Arduino\Croquis\ESP01\HelloServer

Documentation `arduino-esp8266`_

.. _`arduino-esp8266` : https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#class-description

Gros gros tuto sur  `Web serveur`_ 

.. _`Web serveur` : https://github.com/projetsdiy/ESP8266-Webserver-Tutorials

Demonstrate using an http server and an HTML form to `control an LED`_. The http server runs on the ESP8266. 

.. _`control an LED` : https://gist.github.com/bbx10/5a2885a700f30af75fc5

jQery slim : 70ko

fastLed
=============

`FastLed lib`_

.. _`FastLed lib` : https://gi thub.com/FastLED/FastLED

json (lectures / écritures)
==============================

La librairie utilisée: `ArduinoJson`_ version 5.13.2 

.. _`ArduinoJson` : https://github.com/bblanchon/ArduinoJson

Assistant plutôt efficace: `ArduinoJson Assistant`_

.. _`ArduinoJson Assistant` : https://arduinojson.org/v5/assistant/

Json genrator sur `ObjGen.com`_

.. _`ObjGen.com` : http://www.objgen.com/json

.. index::
    single: SPIFFS; Documentation

SPIFFS 
========================

`Official documentation for SPIFFS on Espressif`_

.. _`Official documentation for SPIFFS on Espressif` : https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html


========================
Used library
========================
last update : 02/12/2018

13 libs:

- ESP8266WiFi version 1.0
- ESP8266WebServer version 1.0
- ArduinoJson version 5.13.2
- Wire version 1.0
- RTClib version 1.2.0
- ESP8266mDNS prise
- FastLED version 3.3.3
- nanoI2CIOExpLib version 3.2
- NTPClient version 3.1.0
- Adafruit_GFX_Library version 1.1.8
- Adafruit_SSD1306 version 1.1.2
- SPI version 1.0
- ESP8266HTTPClient version 1.1

12 libs are official Arduino libs and one lib is a special one: `nanoI2CIOExpLib`_
 
.. _`nanoI2CIOExpLib` : https://www.hackster.io/MajorLeeDuVoLAB/nano-i2c-io-expander-3e76fc

====================================================================================================
OLED Screen integration
====================================================================================================
0.96" `128X64 I2C SSD1306 on Aliexpress`_

.. _`128X64 I2C SSD1306 on Aliexpress` : https://fr.aliexpress.com/item/33008480580.html?spm=a2g0o.cart.0.0.5d273c007sJ7KR&mp=1

`Adafruit GFX library`_

.. _`Adafruit GFX library` : https://learn.adafruit.com/adafruit-gfx-graphics-library/overview used 

Add I2C 0x78 on the board (7 or 8 bits add ?)

The right add is 0x3C

There is a pdf documentation for the GFX lib but no doc for special method in SSD13206.

setTextSize : ???

1 is default 6x8, 2 is 12x16, 3 is 18x24, etc (in adafruit source code)

Size 1 : 8 lign of 21 char
Size 2 : 4 lign of 10 char
Size 3 : 2 lign of 5 char

===============================
Eccueils et autres difficultés
===============================

Limite des longueurs de nom de fichier SPIFFS
===============================================

Les noms de fichiers dans SPIFFS sont limités par défaut à 32 caractères chemin compris.

C'est court! voir `github issue #34 mkspiffs`_



.. _`github issue #34 mkspiffs` : https://github.com/igrr/mkspiffs/issues/34

Prise en main de la librairie JSON
======================================

Nécessite un investissement personnel important.

DS3231 stuck I2C bus
======================

It is a known problem with DS3231 see `method for recovering I2C bus #1025`_

.. _`method for recovering I2C bus #1025` : https://github.com/esp8266/Arduino/issues/1025

and `Reliable Startup for I2C Battery Backed RTC`_

.. _`Reliable Startup for I2C Battery Backed RTC` : http://www.forward.com.au/pfod/ArduinoProgramming/I2C_ClearBus/index.html


===========================
Vocabulary
===========================

.. _refCdn:

Un réseau de diffusion de contenu (RDC) ou en anglais `content delivery network (CDN)`_

.. _`content delivery network (CDN)` : https://en.wikipedia.org/wiki/Content_delivery_network

=============
Webography
=============

.. target-notes::

