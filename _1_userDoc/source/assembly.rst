+++++++++++++++++++++++++++++++++++++++++++
IoT Electrical Power Strip Assembly manual
+++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: December 2019
:Societe: VoLAB
:Entity: VoRoBoTics

.. contents::
    :backlinks: top


====================================================================================================
First: program ESP8266
====================================================================================================

Use Arduino IDE
Install ESP8266 from:
https://arduino.esp8266.com/stable/package_esp8266com_index.json

.. image:: image/arduino_esptoolsversion.jpg
   :width: 300 px

You need also esptools to program SPIFFS

.. DANGER::
    ARDUINO IDE 1.8.12, ESP8266 2.4.7 doesn't work for me when i try to program SPIFFS.
	Error : esptool not found

====================================================================================================
Second Program Arduino nano
====================================================================================================


====================================================================================================
Third : program Atiny85 watchdog
====================================================================================================

================================
Solder components onto the board
================================
Progressive assembly and test

====================================================================================================
Notes de mise au point du PCB (A SUPRIMER)
====================================================================================================
Alimentation ? Quid de l'alim 5V et de l'alimentation USB

Donc avec le PCB 2664013A_Y7

Par où on commence ? 

- Par souder les composants passifs
- On vérifie l'absence de CC

Relay 1 : référence ? SRD-05VDC-SL-C. Est-ce que j'en ai ? `Lien Banggood SRD-05`_

.. _`Lien Banggood SRD-05` :   https://www.banggood.com/fr/Mini-5V-DC-Power-Relay-SRD5VDCSLC-5-Pin-PCB-Type-p-930170.html?rmmds=detail-left-hotproducts__4&cur_warehouse=CN

Des `relais 30A ! chez Banggood:`_

.. _`relais 30A ! chez Banggood:` : https://www.banggood.com/fr/5Pcs-SLA-05V-12V-24VDC-SL-A-SL-C-5V-12V-24V-DC-30A-4Pin-Relay-Module-p-1555743.html?rmmds=detail-left-hotproducts__7&ID=519957&cur_warehouse=CN


Données de mise au point:

- ajouter une diode sur le 5V de l'ESP pour éviter que l'USB ne réalimente la carte?
- de la même manière l'USB du UNO pourrait réalimenter la carte, ajouter une diode pin 27

================================
Connect wires to the plugs
================================

=========
Weblinks
=========

.. target-notes::
