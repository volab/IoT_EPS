Document de conception soft de IOT_ESP
======================================


.. include:: ../../README.rst
   :encoding: UTF-8

Avancement
==========
#. Affichage d'un page html static: ok
#. Affichage page html fichier SPIFFS : ok
#. Affichage de l'heure à partir d'une page en dur dans le code : ok
#. Affichage page avec CSS :
#. Gestion des mode wifi SoftAP vs client : 
#. reception d'une action via un bouton :
#. lecture du fichier de configuration : 

   
Un peu de hardware
==================
Premier écueil: l'ESP peut-il s'alimenter en 5V ?

Réponse : oui


.. image:: ./image/alimWemosD1Mini.jpg

Ajout d'un DS3231 comme dans le projet  `ESP_NTP_DS3231 <https://github.com/volab/ESP_NTP_DS3231>`_

.. important::

  D1 : SCL
  D2   SDA

####

Choix dev soft
==============
wifi access point

Les pages html sont dans le file système SPIFFS

WEMOS D1 MIN ARDUINO configurattion:

.. image:: ./image/wemosD1Mini_configArduino.jpg


Useful Documentation
===============================

Exemples ESP html serveurs:

C:\MountWD\Donnees\OneDrive\Donnees\008_iao_wrk\Arduino\Croquis\ESP01\HelloServer

Documentation `arduino-esp8266 <https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#class-description>`_

Gros gros tuto sur  `Web serveur <https://github.com/projetsdiy/ESP8266-Webserver-Tutorials>`_
