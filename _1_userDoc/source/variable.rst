++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Importants variables
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: Juin 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top

.. _refVariableList:

====================================================================================================
List before OOnew more orientation in 2020 Jully
====================================================================================================
Global main variables:

- FtpServer 	ftpSrv :only 2 instances in .ino
- ConfigParam 	cParam  to hold the configuration parameters More...
- Credential 	wifiCred
- CRtc 	rtc
- ESP8266WebServer * 	server
- CPowerPlug * 	plugs
- CRGB 	colorLeds [NUM_LEDS]
- bool 	simpleManualMode = false
- CFlasherNanoExp 	wifiLed
- int 	mainPowerSwitchState
- int 	mainPowerPrevState = 0
- CSwitchNano 	specialBp
- CNanoI2CIOExpander 	nanoioExp
- CTempo 	allLeds
- bool 	restartTempoLed = false
- WiFiUDP 	ntpUDP
- bool 	cycleState = false

Not directly listed in autogenerate doxygen documentation:

- dPrompt
- sysStatus

dprompt
====================================================================================================
dprompt is very usefull to display message prompt in debug serial monitor.
It is declared in macro DEFDPROMPT(X) in debugSerialPort.h file

It is a local variable in the bloc where DEFDPROMTP is used

sysStatus
====================================================================================================
Auto declared global Instance of the CSysStatus classe in csysstat.cpp file

Its usage:

.. image:: image/sysStatusReference.jpg
   :width: 300 px

As this instance is declared in its own cpp file, it doesn't appear in the doxygen documentation.

This clas store system status and managed them.

28 reference in 5 files

cParam
====================================================================================================
52 references in 3 files

- loT_EPS.ino 44
- SerialCommand.cpp loT_EPS 2
- serverFunction.cpp loT_EPS 6

This instance hold all configuration parameters

====================================================================================================
Weblinks
====================================================================================================

.. target-notes::