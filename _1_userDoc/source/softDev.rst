Document de conception soft de IOT_ESP
======================================


.. include:: ../../README.rst
   :encoding: UTF-8

Avancement
==========
#. Affichage d'un page html static: ok
#. Affichage page html fichier SPIFFS : ok
#. Affichage de l'heure à partir d'une page en dur dans le code : ok
#. Affichage page avec CSS : ok
#. Gestion des mode wifi SoftAP vs client : ok
#. reception d'une action via un bouton : 
#. lecture du fichier de configuration : ok

   

Choix dev soft
==============
wifi access point

Les pages html sont dans le file système SPIFFS

WEMOS D1 MIN ARDUINO configurattion:

.. image:: ./image/wemosD1Mini_configArduino.jpg

Développement des page Web
==========================
HTML5 et css

Serveur html ESP8266
====================
Repris de l'exemple fourni avec l'IDE ARDUINO : FSBrowser

Cette exemple apporte un lot de fonction qui gérent l'envoie de fichier css, jpg et autres...



Useful Documentation
===============================

Exemples ESP html serveurs:

C:\MountWD\Donnees\OneDrive\Donnees\008_iao_wrk\Arduino\Croquis\ESP01\HelloServer

Documentation `arduino-esp8266 <https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html#class-description>`_

Gros gros tuto sur  `Web serveur <https://github.com/projetsdiy/ESP8266-Webserver-Tutorials>`_
