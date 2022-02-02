++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
First boot informations
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: Octobre 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top


.. index::
    single: First boot

====================================
First boot configuration
====================================

@first boot :
 - mode AP connection and display config page to set SSID password and server name
 - softAP ssid <32
 - WARNING pass in AP mode >8 <63
 - propose a unic ID for server name to the user
 - explain that it will possible to change after
 

Restaure factory parameters 
----------------------------------------------------------------------------------------------------
firstBoot after check box in config page.

Restaure defConfig.json
 
 
What are hypothesis, when boot for the first time ?
----------------------------------------------------------------------------------------------------
Is a config json exist ? What is inside it ? Yes and it contain FirstBoot ON and other stuff.

Same questions with credentials ? No, we generate it

We consider that the user upload sketch and data directory.

When consider the first boot is OFF (end of first boot procedure) ? 
When we receive the following form:

 - station mode or AP choice
 - SSID et pass du mode AP (WARNING provide diff SSID if you own more then one PowerStrip)
 - SSID and pass of station mode [ optional if user wish stay always in AP mode ]
 - propose default same hostname and default SSID AP build with mac add:
   IOT_EPS_HHHH

First boot process
----------------------------------------------------------------------------------------------------
#. check firstBoot param in config.json if ON
#. start in AP mode with page firstboot.html only if main power is on
#. if firstboot param is ON or TRY, we start the server with a special index page (firstboot.htm)
#. server.on( /firstBoot, firstBootHandler) - who send /firstboot
#. in firstBootHandler check param, write credential, set firstBoot param to "trySation" if needed
#. restart ESP
#. if Station is ok firstBoot is ended, set firstBoot param = off
#. if station ko reload firstboot page with alert

/fisrtboot page is send by firstboot.html page witch is register in place off index.html normale
page when we received /

Behavior when user move EPS from one physical site to another
----------------------------------------------------------------------------------------------------
It is not a first boot

EPS will search its WiFi station and will not find it so it restart in AP mode then user can acces
to the config special page change SSID and password.


.. index::
    single: Startup

=====================================
Start up behavior
=====================================

Question:what should be the behavior when power is switched to ON ?

2 cases are possibles when power is On: the button is switched to ON or the system restart after a
genaral power cut

Soit l'interrupteur général est actif (cas de la coupure EDF) et on reprend où on en était.

Soit l'interrupteur général est  inactif et on reprend en mode manuel.

L'interrupteur général coupe le 220V des prise mais pas de l'ESP8266.

Bien expliquer les 2 modes de fonctionnement dans l'interface WEB et donner le choix à l'utilisateur.

Expliquer le coup de la coupure de courant.

Evol : après coupure EDF : donner le choix à l'utilisateur de configurer le comportement de
chaque prise.

Possible behaviors:

 #. on repart d'où on en était (avec éventuellement alerte instantanée à l'utilisateur)
 #. on met tout la prise à OFF en manuel(avec éventuellement alerte instantanée à l'utilisateur)
 #. on informe l'utilisateur (canal à définir, MQTT ou autre...) qui décide mais on met en
    pause en attendant

When main power switch is off : html server post no reply.

Problem : when in AP mode WiFi start even if main power is OFF and in Station ESP connect to acces
point. It is not a logically expected behavior. When power switch is in OFF position no Wifi 
activity should be detected.

Solution wait for power on in ARDUINO setup function.
Restart ESP in ARDUINO loop when power is switch to OFF.

.. index:: Special push buttons

Special push button behaviors @startup
----------------------------------------------------------------------------------------------------
PB0 : @power on (not by power switch but by wall plug) start in simple manual mode see 
:ref:`WIFI Modes<refWifiModes>`


PB1 : in same conditions as above, start specials action only for expert and debug mode
(today create default json) with main power switch on on state (to be checked 21/10/2019) 


====================================================================================================
Weblinks
====================================================================================================

.. target-notes::