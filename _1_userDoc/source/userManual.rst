++++++++++++++++++++++++++++++++
IoT_EPS User Manual
++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: Décembre 2019
:Societe: VoLAB
:Entity: VoRoBoTics

.. toctree::
   :maxdepth: 2
   :caption: Contents
   :titlesonly:
   
   userManualAnex.rst

.. contents::
    :backlinks: top

================================
First connection
================================
When connecting the power Strip for the first time, user should connect a WiFi Device in AP mode and
search IoT_ESP_HHHH SSID (where HHHH is 4 hexadecimal digits) 
and connect to it with password : 123456789

User should change this password and configure ip and password for WIFI station mode and restart.

================================
WIFI connections
================================
**AP mode** : is always available and default SSID name is IoT_ESP_HHHH.

**Station mode** : is available after first configuration and credential settings. In this mode, 
human interface is mode responsive due to boostrap CDN usage.

In station mode user can address all ist iot plug from its internet browser of its Mac, PC 
or Android device.


================================
Boutons
================================
In manuel mode, short press switch on/off the plug

Long press : return to manuel mode

At power up (wall plug - not by main power switch):
 - red push button : switch to very simple mode (without web interface)
 - green push button : restaure json file.

================================
Advanced user
================================
Serial com speed : 115200 (dans debugSerialPort.h DEBUGSPEED)

File upload : use web interface (need to be connected to internet) PowerStip01/edit
If your plug's name is PowerStrip01 or 192.168.1.xx/edit (access with it's IP addresse)

File delete : use seial commande <d _filename>

FTP server dosen't work very well

In csysstat.cpp et csysstat.h files, variable _forceSystemStartOnFatalError allow to desable the
sabordage behavior.

=========================================
Obtaine IP addresse of the Power strip 
=========================================
Use serial connexion <a> command if possible or an IP scanner like `AngryIP scanner`_

.. _`AngryIP scanner` : https://angryip.org/

=========
Weblinks
=========

.. target-notes::
