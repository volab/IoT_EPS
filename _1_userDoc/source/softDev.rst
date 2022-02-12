+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Software development documentation
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
   testToBeConducted
   jsonImprovment

.. contents:: Table of Contents
    :backlinks: top

.. |clearer|  raw:: html

    <div class="clearer"></div>


=============================
Source code documentation
=============================

Source code documentation provide a lot of informations
 
 `<codeDoc\\html\\index.html>`_


===========================
Progress of development
===========================

Terminated
----------------------------------------------------------------------------------------------------

::

    #. Display single static html page:                                                      ok
    #. Affichage page html fichier SPIFFS :                                                  ok
    #. Affichage de l'heure à partir d'une page en dur dans le code :                        ok
    #. Affichage page avec CSS :                                                             ok
    #. Gestion des mode wifi SoftAP vs client :                                              ok
    #. reception d'une action via un bouton :                                                ok
    #. lecture du fichier de configuration :                                                 ok
    #. intégration MCP23017 :                                                                ok
    #. lecture du fichier de configuration config3.json :                                    ok
    #. gestion bouton poussoir mécanique :                                                   ok
    #. Write json file :                                                                     ok
    #. Traitement de la requête html avec analyze, exécution et écriture json:               ok
    #. manage wif led :                                                                      ok
    #. integrate nano expander with analog inputs :                                          ok
    #. scan I2C response 57 and 58 nano IoExpander !!!! not a bug simply DS3231 board has 2 component DS3231 an EEPROM ! OK
    #. Time managment strategy :                                                             ok
    #. review work without rtc component strategy                                            ok
    #. review work without NTP access strategy                                               ok
    #. define rtc component versus NTP update strategy                                       ok
    #. suppress html replies if main power is off                                            ok
    #. generate a unique server name                                                         ok
    #. rewrite main program setup and loop function with more object oriented structure      ok
    #. add OLED display managment in accordance of its hardware implementation of course     ok
    #. creation of config.h and config-advenced.h (see :ref:`see project todo list<todocreateconfigfile>`) **OK**
    #. new bug in 2022 : json writes incorrect : ex : cycle hdebut and hfin ="" !!! **OK**
       detect 05/1/2022 correcte 8/01/2022
    #. Correct watchdog bug  **OK**
    #. Correct corrupted on/off compt bug see bug and todo list
    #. Correct internet error bug see bug and todo list

In progress
----------------------------------------------------------------------------------------------------

Transferred :ref:`here<mainTodoList>`

====================================================================================================
Software architecture or how does it work
====================================================================================================
Some words on software architecture @13/07/2020

see also :ref:`Json file improvements : analyze<jsonFileImprovementsAnalyze>`


Major points
----------------------------------------------------------------------------------------------------

One main .ino file with its .h : IoT_EPS.
In the header file we can find include and config informations. (to changed - 
:ref:`see project todo list<todocreateconfigfile>` ) Now we have the IoT_EPS.h with includes and 
config.h for parameters and config_advanced.h for advanced parameters.

A lot of usage of global variables and objects (not very optimal). :ref:`See variables list<refVariableList>`

Usage of one big json file (except for credentials) to store plugs information and 
application parameters. Not optimal (a better choice would be one file for general informations and
one file for plugs parameters and perhaps one file by plug).

Usage of static functions in some classes like *Crtc* due to usage of external library.

Usage of a pseudo object in **SerialCommand** (just a struct) due to reuse of code from an other project.

The embedded html server is based on **ESP8266webserver** class 

Global File system SPIFFS is based on **ESP8266 core**

Operations
----------------------------------------------------------------------------------------------------
An array of 4 plug objects manage the behavior of the plugs. Events from wifi trigs 
web server functions. The main part of the jobs is to write data in the json file that it is resend
to the user's web browser.

Timing are managed by CRtc a derived class from rtc from RTClib.

The wifi : after a long expectation where I navigate between station mode or softAP mode. Finally,
I activate the 2 modes simultaneously.

====================================================================================================
How does it work
====================================================================================================
There is 2 worlds

The Plugs world and the Web world.

The Plug world
----------------------------------------------------------------------------------------------------
It is although the hardware or physical world

**Setup sequence**

- serial, time, ftp, debug oled screen init
- Watchdog check
- Main power first check (already on ? Return from electrical power down, hot restart)
- Plugs config
- Main power wait ON (the purpose is to maintain Wifi off) loop
- WIFI start
- Server configurations
- Time server check 
- Setup last operations (displayCommandsList, initCBITTimer, check internet access and setup wd)

**Loop sequence**

- CBIT : Continus Built In Test Start : periodicly check file system, internet access
- watchdog refresh
- Some little jobs : specialBp, ftp, SerialProcess...
- manage leds
- manage bps + plugs time to switch  
- main power switch actions

The Web world
----------------------------------------------------------------------------------------------------
Server event (HTTP GET requests). They are mapped to callback C functions (CServerWeb methods)

  ============== ===================================================================================
  Event          Binded functions
  ============== ===================================================================================
   /             firstBootHtmlForm, handleSoftAPIndex or handleIndex
   /time         displayTime
   /list         handleFileList
   /plugonoff    handlePlugOnOff
   /help         handleHelp
   /edit         handleEdit, handleFileCreate, htmlOkResponse, handleFileUpload, handleFileDelete
   /cfgpage      handelIOTESPConfPage
   /cfgsend      handleIOTESPConfiguration
   /changeCred   handleNewCred
   /firstBoot    handleFirstBoot
  ============== ===================================================================================

Theses events are triggered by HTTP requests from user's Web browser. Some of these above request are
not implemented in http pages and are only for debug and should be send directly in the uri like 
``/time``

Html pages are stored in the data folder of the SPIFFS in the ESP8266 flash.

Links between the 2 worlds
----------------------------------------------------------------------------------------------------
These 2 worlds live their lives almost independent of each other.

There are 2 links between them:

- the json file
- the time

Events write data in json file and physical part of the system check periodicaly the data in the 
json file and do the jobs.


.. _devProgress:



Differed to next version
----------------------------------------------------------------------------------------------------

::

    #. power measurement - not in this vesion




====================================================================================================
Config.h and config_advenced.h
====================================================================================================
config.h include all user define macro.

config_advenced.h group all others interesting parameters

.. _webBrowserCaching:

====================================================================================================
web caching
====================================================================================================
see to do list.
Perhaps use following method but i don't find how to use it

server->serveStatic("/", SPIFFS, "/index.html");

function prototype::

    void serveStatic(const char* uri, fs::FS& fs, const char* path, const char* cache_header = NULL );

Another example::

    // Serve a file with no cache so every tile It's downloaded
    httpServer.serveStatic("/configuration.json", SPIFFS, "/configuration.json","no-cache, no-store, must-revalidate");
    // Server all other page with long cache so browser chaching they
     httpServer.serveStatic("/", SPIFFS, "/","max-age=31536000");

`Web server with esp8266 and esp32`_

.. _`Web server with esp8266 and esp32` : https://www.mischianti.org/2020/11/02/web-server-with-esp8266-and-esp32-multi-purpose-generic-web-server-3/



====================================================================================================
Watchdog bug 
====================================================================================================
There is no  watchdog component in the system and system always displays watchdog ok !!!

Detection date : 5/12/2021

Start of traitement : 08/12/2021

Dev branch : watch_dog_bug :

Code analyze::

    Method : void CSysStatus::display() do not display wd error ! Why ! An oversight ?
    This method display **9 errors**

    But the class CSysStatus() is declared with **11 error** !

    CSysStatus::isSystemok()

    CSysStatus::howManyError()

    String CSysStatus::getMsg( int8_t n)

In the setup sequence::

    <Volab setUp > watchdog test 
    <Volab System error handler > watchdog error
    <Volab setUp > watchdog set to 30s.

Creation of ``config.h`` et de ``config_advenced.h`` **OK**

define : ``#define NBR_OF_SYSTEM_ERROR 11`` in ``config_advenced.h``

The purpose of this is to create a table of system error in the class. **OK**

<e> command that displays system error display ``<Volab System status > watchdog error : no error``
but some line above at boot time system displays ::

    <Volab setUp > watchdog test 
    <Volab wd test > -1
    <Volab wd test > -1
    <Volab System error handler > watchdog error


.. code:: cpp

    watchdog.begin();
    DSPL( dPrompt + F("watchdog test ") );
    sysStatus.watchdogErr.err( !watchdog.test() );
    if ( !sysStatus.watchdogErr.isErr() ) DSPL( "watchdog OK"); //normaly if error we did not reach
    //this point unless _forceSystemStartOnFatalError is true for debug
    watchdog.setTimeout( cParam.getSTAMaxRetries() );
    watchdog.setRefreshPeriod( cParam.getSTAMaxRetries()/3 );  
    DSPL( dPrompt + F("watchdog set to ") + String( cParam.getSTAMaxRetries() ) + F("s.") );
    //oled message


.. _newErrorHandling2022:

====================================================================================================
New error handling 01/2022
====================================================================================================

Analyze
----------------------------------------------------------------------------------------------------
sysError::err method that sabord system

each time a fatal error rise, sysError class sabord the system just when the error is raise.

But with the boolean _forceSystemStartOnFatalError sysError::err can't sabord the system but all 
functions continues to try to work.

if only one fatal error rise, all functions should not  try to work

Question: how errors are they clean ? at this time, there is no way to clean errors.

Due to the new paradigm flash colors for errors are no longer useful.

As almost all errors are fatal, is there a way to consider a commun behavior when a fatal error rise ?

To day (on 22/01/2022), Error list::

    fsErr( sysError::fatal, CRGB::Red, CRGB::Black, "File system error" )
    , nanoErr( sysError::fatal, CRGB::Red, CRGB::Blue, "Nano error" )
    , rtcErr( sysError::fatal, CRGB::Brown, CRGB::Black, "DS3231 error" ) 
    , confFileErr( sysError::fatal, CRGB::Red, CRGB::Yellow, "Config file error" )
    , credFileErr( sysError::medium, "Credential error" )
    , filesErr( sysError::fatal, CRGB::OrangeRed, CRGB::Black, "Needed files error" )
    , plugParamErr( sysError::fatal, CRGB::Red, CRGB::Snow,    "Plug's file error"  )
    , ntpErr( sysError::low, "NTP error")
    , internetErr( sysError::fatal, CRGB::RoyalBlue, CRGB::OrangeRed, "Internet error" )
    , watchdogErr( sysError::fatal, CRGB::Snow, CRGB::Black, "watchdog error")
    , wifiSoftApErr(sysError::medium, CRGB::Snow, CRGB::Black, "SoftAp error")
    /** @todo [NECESSARY] creat wifiErr and wifiStaModeErr (choose a color) */

And where these errors are raised ?::

- fsErr : at setup only in CSystem::init
- nanoErr : at setup and in **loop** @ ic2_time 1mn 
- rtcErr : at setup in CSystem::init (equivalent to a i2c test)
- confFileErr : setup in CSystem::init
- credFileErr : wifi begin 
- filesErr : setup + in the **loop** @ cbit time 1mn
- plugParamErr : setup by CJsonIotEps::loadJsonPlugParam
- ntpErr : in the **loop** @ cbit time
- internetErr : in the **loop** @ cbit time
- watchdogErr : only in setup
- wifiSoftApErr :  wifi begin

.. NOTE:: **About rtc and ntp errors** 
   :class: without-title

   The time is important to switch plugs. It is **rtc** that is used to check time

   Ntp is only use to adjust RTC when it is necessary in one method and is not a fatal error

.. NOTE:: **fs, nano, confFile,other files, plugs param**
   :class: without-title

   reals fatal errors

.. NOTE:: **Watchdog**
   :class: without-title

   Perhaps not a fatal error : if wd doesn't work only one function is break : main switch off

.. NOTE:: **Credentials and wifi station mode errors**
   :class: without-title

   Only prevent ntp clock update and Bootstrap cdn access. Plugs continue to work in AP mode

.. CAUTION:: Most of this error are hardware failures
   :class: without-title

   Only ntp and AP mode are auto-repaired errors. During normal operations for ntp and generally 
   a restart is necessary for AP mode error.

.. SEEALSO:: The only feature to maintain when fatal error is risen, is the manual push button switching
   :class: without-title

   To simplify dev, we decide to lock all features except above one. 

Implementation
----------------------------------------------------------------------------------------------------
When fatal error is risen, potentially there is no web (no user browser to display error) nor oled.

Only bp and color led are direct connected to ESP8266. Relay commands are through nanoI2CIoExpander and 
I2C bus

Only the Serial line can work.

.. WARNING:: **DECISION** 
   :class: without-title

   - Display first fatal error on color LED blinking between their normal color and error color.
   - Keep push button active to try to drive relay (not guaranteed)
   - watchdog changed to medium error

For ntp, wd and ap mode error display them on OLED cycling with normal display of plugs

- create new help commande to force and clear error **OK**
    - Choose letter for commands B and b ( there are few letters left ) **OK**
    - add letters to the help system **OK**
    - decide number of each errors (see below) to give as parameter of the command **OK**
    - create help force commande **OK**
- create a new help cmd to stop WD set WD to 4mn and 15s (maximum) **OK**
    - merge it on devFirmware **OK**
    - pb with git and devfirmware with a lower case f !!! **CORRECTED**
- rearrange help commande list in alphabetic order **OK**
    - merge it on devFirmware **OK**

Stop wD ? set timeout to 255seconds ie 4mn and 15s is enough to upload firmware ?

Number of the error, as in the code::

        sysError* sysErrorTable[NBR_OF_SYSTEM_ERROR] = { 
                    &fsErr, &nanoErr, &rtcErr, &confFileErr, &credFileErr, &filesErr, &plugParamErr, 
                    &ntpErr, &internetErr, &watchdogErr, &wifiSoftApErr };

        in csysstat.h

    0 : file system
    1 : nano
    2 : rtc
    3 : config file
    4 : credential file
    5 : Needed files
    6 : plugs params
    7 : ntp
    8 : internet
    9 : Watchdog
    10 : soft app

.. NOTE:: To Remember
   :class: without-title

    - int8_t CSysStatus::howManyError()
    - bool CSysStatus::isSystemok()
    - int8_t isThereFatalError()




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


Référence : config4.json (this is the only file name that is mandatory to ensure interface between 
plugs and wed worlds).

In the code I use lower Camel Case.

============================
Software development choice
============================
wifi access point

Html pages are in the file system SPIFFS

Why do not use wifi manager ?
----------------------------------------------------------------------------------------------------
A good question and i have no answers today !

======================================
Displaying plugs mode only with LEDs
======================================


Problem : how to displays functional mode of a plug without the web interface

Solution1: Use the little plug red LED. When the LED is OFF flash shortly one time for mode 1 "manual" to five
time for mode 5 "Clone". When ON is on invert ton and toff of the flasher

Solution2: use color LED with flash capability one time for mode manual to 5 times to mode Clone
with a long time between group of flash 3 seconds for example.

Implemented : solution n°1 with the little specialPB pushed in the same time as the plug Push Button

**An advice for users** : retain special BP pressed some seconds before pushing plug's PB to avoid to swith the plug.

==============
IOExpander
==============

The following text is for history only and is **obsolete**:

When we define hardware pin usage, we decide to use IOEpander MPC23017.
Due to this choice, we need to use a new lib Adafruit_MCP23017.h

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
  
Default address: 0x20 (with the 3 address pins at ground)

En premier mouture, essai avec la librairie directement mais en deuxième monte, faire une classe
qui prennent en charge la gestion du temps (classe Flasher dédiée au MCP)

Deuxième mouture création de la class CPowerPlug avec utilisation de variable static

_initDone et _mpc (mpc étant la ressource commune à toutes les instances de la classe)

.. important::

    J'ai choisi d'utiliser une broche dédiée pour la LED d'état des plugs.
    On aurait pu utiliser la broche de commande du relais mais au cas où les 2
    seraient inversées l'une par rapport à l'autre, cela apporte plus de liberté.

During development, to get more digital IO and 4 analog inputs, we decide to add an ARDUINO Nano as 
an I2C IO expander (see :ref:`Hardware dev doc<nanoI2CIoExpander>` ) 


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
#. I2C access
#. rtc
#. only in Station mode and after WIFI connection, check NTP access


CBIT : Continus BIT every loop cycle, check :
 - I2C access (only one retry)
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
- OLED 0x3C
- EEPROM on DS3231 1010011 normaly 0x53 base add is 0x50 and I have solder A2 slot
- ioexpender : 0x58 (ored with D13) - defined in the ARDUINO NANO code
- DS3231 : 0x68 defined in RTClib.h

There is 3 pull-up on the board.

<F> command result (22/06/2021)::

    I2C device found at address 0x26  !
    I2C device found at address 0x3C  !
    I2C device found at address 0x53  !
    I2C device found at address 0x58  !
    I2C device found at address 0x68  !
    

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






====================================================================================================
OLED Screen integration
====================================================================================================
0.96" `128X64 I2C SSD1306 on Aliexpress`_

.. _`128X64 I2C SSD1306 on Aliexpress` : https://fr.aliexpress.com/item/33008480580.html?spm=a2g0o.cart.0.0.5d273c007sJ7KR&mp=1

`Adafruit GFX library`_  used 

.. _`Adafruit GFX library` : https://learn.adafruit.com/adafruit-gfx-graphics-library

Add I2C 0x78 on the board (7 or 8 bits add ?)

The right add is 0x3C

There is a pdf documentation for the GFX lib but no doc for special method in SSD1306.

setTextSize : ???

1 is default 6x8, 2 is 12x16, 3 is 18x24, etc (in adafruit source code)

Size 1 : 8 lign of 21 char
Size 2 : 4 lign of 10 char
Size 3 : 2 lign of 5 char

Screen definitions
----------------------------------------------------------------------------------------------------
Screen are created with GIMP and converted with `LCD Assistant from radzio.dxp.pl`_

.. _`LCD Assistant from radzio.dxp.pl` : http://en.radzio.dxp.pl/bitmap_converter/

Screen color shall be inverted in GIMP text shall be in black and screen in white.
 
Bitmap exported file from GIMP shall be in 2 bits indexed color maode
(In gimp: Image/Mode/Couleur indexée... menu and dialog box)

How many and what screen do we need ?

First screen VoLAB logo

.. image:: image/ecranlogo_210612_1940.png


Second screen : The project name : 

.. image:: image/firstScreen.png 


First and second screen are display by CSystem::_oledStartMessagesManager

In the septup sequence::

  - DS3231 demarre a: ( CSystem.init() )    [on line 1]
  - A partir d'ici:                         [on line 3]
  - * I2C ok                                [on line 4]
  - * Fichiers ok
  - * Parametres ok

In the loop sequence:

.. image:: image/ecran1_201019_1402.png
   :width: 128 px

To display IPs, states and errors. Exemple: time server and Wifi accessibility... 

On the above screen, only Date, time and state can change. Ip adress stay the same to the next reboot !

So the right place to put it it at the end of setup loop.

I place methods in the CSystem class not very logic. The right way to do it should be to creat a new
dedicate displayMessageClass.



====================================================================================================
Free memory analyze
====================================================================================================
Special git branch analyseFreeMem.

Due to a bug when I want to test the write function, I am forced to conduct this analyze.

Commands used::

    #include <ESP.h>
    //...
    DSPL( dPrompt + "Free mem : " + String( ESP.getFreeHeap() ));


Memory analysis::


	SDK:2.2.1(cfd48f3)/Core:2.4.1/lwIP:2.0.3(STABLE-2_0_3_RELEASE/glue:arduino-2.4.1)
	<Volab setUp > >>>>>>   Free mem at start: 15976
	<Volab setUp > >>>>>>   Free mem before build info: 15960
	<Volab setUp > >>>>>>   Free mem after build info: 15912
	<Volab CSystem::init > DS3231 Start date : 15/9/2021 21:41:7
	<Volab setUp > >>>>>>   Free mem after system init: 13568
	<Volab setUp > >>>>>>   Free mem after serial init: 13456
	<Volab setUp > >>>>>>   Free mem before new plugs: 13472
	<Volab setUp > >>>>>>   Free mem after  new plugs: 11464
	<Volab setUp > >>>>>>   Free mem after plugs init: 11464
	<Volab setUp > >>>>>>   Free mem before wifi init: 11464
	<Volab setUp, Wifilink begin > >>>>>>   Free mem before _wifiRef init: 11400
	<Volab setUp, Wifilink begin > >>>>>>   Free mem after alls init: 11384
	<Volab setUp, Wifilink begin > >>>>>>   Free mem before displya wifi mode : 11384
	<Volab setUp, Wifilink begin > >>>>>>   Free mem before wifiRef.begin : 10920
	<Volab setUp, Wifilink begin > >>>>>>   Free mem after  wifiRef.begin : 10688
	<Volab setUp, Wifilink begin > >>>>>>   Free mem before station connect loop : 10656
	<Volab setUp, Wifilink begin > >>>>>>   Free mem after station connect loop : 10568
	<Volab setUp, Wifilink begin > >>>>>>   Free mem after station mode start : 10568
	<Volab setUp > >>>>>>   Free mem after wifi init: 10632
	<Volab setUp > >>>>>>   Free mem before webserver init: 10632
	<Volab WEbServer init > >>>>>>   Free mem before new ESP8266WebServer : 10568
	<Volab WEbServer init > >>>>>>   Free mem before new ESP8266WebServer : 10136
	<Volab WEbServer init > >>>>>>   Free mem before server begin : 9152
	<Volab WEbServer init > >>>>>>   Free mem after server begin : 9008 (some unsued pages commented sot save memory)
	<Volab setUp > >>>>>>   Free mem after webserver init: 9056
	<Volab setUp > >>>>>>   Free mem after timeserver check: 8808
	<Volab setUp > >>>>>>   Free mem after initCBITTimer: 8808
	<Volab setUp > >>>>>>   Free mem at setup end: 8072
	<Volab CJsonIotEps store json method > *********JSON WRITE REQUESTED***************

	<Volab Handle config html form > >>>>>>   Free mem at handleConfPage start: 7640
	<Volab Handle config html form > >>>>>>   Free mem after page read: 3280
	<Volab reading one parameter from config > >>>>>>   Free mem at funct begin: 3088
	<Volab reading one parameter from config > Config file size : 1413
	<Volab reading one parameter from config > >>>>>>   Free mem after file read: 1536
	<Volab reading one parameter from config > >>>>>>   Free mem after json dynamic alloc: 688
	<Volab reading one parameter from config > Failed to load json config
	<Volab reading one parameter from config > Free mem after close: 824

	...

	<Volab handleFileRead > >>>>>>   Free mem at handle file read start: 8248
	handleFileRead _path : /css/style.css
	handleFileRead _contenttype : text/css
	<Volab handleFileRead > >>>>>>   Free mem at handle file read juste before file close: 6640
	<Volab handleFileRead > >>>>>>   Free mem at handle file read end: 6776
	<Volab handleFileRead > /img/logo_alpha.png
	<Volab handleFileRead > >>>>>>   Free mem at handle file read start: 8216
	handleFileRead _path : /img/logo_alpha.png
	handleFileRead _contenttype : image/png
	<Volab handleFileRead > >>>>>>   Free mem at handle file read juste before file close: 6608
	<Volab handleFileRead > >>>>>>   Free mem at handle file read end: 6744

	#Serial command <J0>

	<Volab Display json > Json file: /config4.json
	<Volab Display json > >>>>>>   Free mem after file is opened: 8128
	<Volab Display json > Config file size : 1413
	<Volab Display json > >>>>>>   Free mem after json dynamic alloc: 6680
	<Volab Display json > >>>>>>   Free mem after json parse: 4808
	<Volab in the loop > >>>>>>   Free mem at CBIT time: 8552

	#Serial command <J1>

	<Volab Display json > >>>>>>   Free mem after file is opened: 8032
	<Volab Display json > Config file size : 2170
	<Volab Display json > >>>>>>   Free mem after json dynamic alloc: 5824
	<Volab Display json > >>>>>>   Free mem after json parse: 3952

**Conclusions**:
The bug is due to a lack of memory when in the method that compute the html page that load json, 
for a 1k file it takes more than 2K in memory, one for the txt buffer that receive raw data and 
one for the json object.
 
Corrections:

- remove unused web path from server to win 910 bytes
- remove asscoiated function like : ``void CServerWeb::displayTime()``
- minifier html page config_tag.htm to win 714 bytes. befor 4214bytes afert 3279 delta 935bytes !
- rewrite method : void CServerWeb::handelIOTESPConfPage()
- add : ``friend class CServerWeb;`` to class ConfigParam and to CPowerPlug



===============================
Usefull Tools
===============================

On Android : `Network IP Scanner`_ from homework.

On PC : `Angry IP Scanner`_


.. _`Network IP Scanner` : https://play.google.com/store/apps/details?id=com.network.networkip&hl=fr
.. _`Angry IP Scanner` : https://angryip.org/
    


.. index::
    pair: Used; Library

.. _usedLirary:

========================
Used library
========================
last update : 05/05/2021

13 libs:

- ESP8266WiFi version 1.0
- ESP8266WebServer version 1.0
- ArduinoJson version 5.13.2
- Wire version 1.0
- RTClib version 1.2.0
- ESP8266mDNS
- FastLED version 3.3.3
- nanoI2CIOExpLib version 3.2
- NTPClient version 3.1.0
- Adafruit_GFX_Library version 1.1.8
- Adafruit_SSD1306 version 1.1.2
- SPI version 1.0
- ESP8266HTTPClient version 1.1


12 libs are official Arduino libs and one lib is a special one: `nanoI2CIOExpLib`_
 
.. _`nanoI2CIOExpLib` : https://www.hackster.io/MajorLeeDuVoLAB/nano-i2c-io-expander-3e76fc

===============================
Usefull Documentation
===============================

Espressif
----------------------------------------------------------------------------------------------------
:download:`ESP8266 Non-OS SDK<fichiersJoints/2c-esp8266_non_os_sdk_api_reference_en.pdf>` pdf file

Containt function and class and struct like::

    wifi_softap_get_config_default

    struct softap_config {
        uint8 ssid[32];
        uint8 password[64];
        uint8 ssid_len;     
        uint8 channel;           // support 1 ~ 13     
        uint8 authmode;          // Don’t support AUTH_WEP in  SoftAP mode     
        uint8 ssid_hidden;       // default 0     
        uint8 max_connection;    // default 4, max 4     
        uint16 beacon_interval;  // 100 ~ 60000 ms, default 100 };

Which is very usefull to debug !

ESP8266WebServer
----------------------------------------------------------------------------------------------------
only `github documentation for ESP8266Webserver`_

.. _`github documentation for ESP8266Webserver` : https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer



Html server
----------------------------------------------------------------------------------------------------

Exemples ESP html serveurs::

    C:\MountWD\Donnees\OneDrive\Donnees\008_iao_wrk\Arduino\Croquis\ESP01\HelloServer

Documentation `arduino-esp8266`_

.. _`arduino-esp8266` : https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#class-description

Gros gros tuto sur  `Web serveur`_ 

.. _`Web serveur` : https://github.com/projetsdiy/ESP8266-Webserver-Tutorials

Demonstrate using an http server and an HTML form to `control an LED`_. The http server runs on the ESP8266. 

.. _`control an LED` : https://gist.github.com/bbx10/5a2885a700f30af75fc5

jQery slim : 70ko

fastLed
----------------------------------------------------------------------------------------------------

`FastLed lib`_

.. _`FastLed lib` : https://gi thub.com/FastLED/FastLED

json (lectures / écritures)
----------------------------------------------------------------------------------------------------

La librairie utilisée: `ArduinoJson`_ version 5.13.2 

.. _`ArduinoJson` : https://github.com/bblanchon/ArduinoJson

Assistant plutôt efficace: `ArduinoJson Assistant`_

.. _`ArduinoJson Assistant` : https://arduinojson.org/v5/assistant/

Json genrator sur `ObjGen.com`_

.. _`ObjGen.com` : http://www.objgen.com/json

.. index::
    single: SPIFFS; Documentation

SPIFFS 
----------------------------------------------------------------------------------------------------

`Official documentation for SPIFFS on Espressif`_

.. _`Official documentation for SPIFFS on Espressif` : https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html


===============================
Eccueils et autres difficultés
===============================

Limite des longueurs de nom de fichier SPIFFS
----------------------------------------------------------------------------------------------------

Les noms de fichiers dans SPIFFS sont limités par défaut à 32 caractères chemin compris.

C'est court! voir `github issue #34 mkspiffs`_



.. _`github issue #34 mkspiffs` : https://github.com/igrr/mkspiffs/issues/34

Prise en main de la librairie JSON
----------------------------------------------------------------------------------------------------

Nécessite un investissement personnel important.

DS3231 stuck I2C bus
----------------------------------------------------------------------------------------------------

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

