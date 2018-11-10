++++++++++++++++++++++++++++++++++++++++++++++
Document de conception hardware de IOT_ESP
++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: Octobre 2018
:version: 1


.. contents:: Table of Contents
.. section-numbering::

.. include:: ../../README.rst
   :encoding: UTF-8

============
Avancement
============
#. alimentation ESP
#. choix curent sensor: 
#. horloge temps réelle : ok
#. LED
#. bouton poussoirs
#. Affectation des io
#. module relais : ok
#. définition des modes de fonctionnement : ok

####

==================   
Alimentation ESP
==================
Premier écueil: l'ESP peut-il s'alimenter en 5V ?

Réponse : oui


.. figure:: image/alimWemosD1Mini.jpg
    :align: center
    
    Circuit d'alimentation WEMOS D1 mini

####

====================
Horloge temps réelle
====================

Ajout d'un DS3231 comme dans le projet  `ESP_NTP_DS3231 <https://github.com/volab/ESP_NTP_DS3231>`_

.. important::

  D1 : SCL
  D2   SDA

####

====================
Choix current sensor
====================

INA219 et INA220
================
- impossible "bus voltage 0-26V"

ACS712
======

- "Output voltage proportional to AC or DC currents"

- "2.1 kVRMS minimum isolation voltage from pins 1-4 to pins 5-8"

- "5V power supply"

pb c'est pas de l'I2C et en plus x4

ACS764
======
Je n'arrive pas à voir la tension de rail max

- I2C
- courant max programmable
- Unidirectional DC current sensing and reporting : KO

Recherche internet
==================

"AC isolated current sensor I2C"

le vainqueur est `Si8901B-GS`_

.. _`Si8901B-GS` : https://www.silabs.com/products/isolation/current-sensors/si890x-isolated-adc-ac-mains-monitor

dispo chez `Mouser`_ à 3.44€/10pcs

.. _`Mouser` : https://www.mouser.fr/Search/Refine.aspx?Keyword=SI8901 

`Un exemple de mise en oeuvre`_

.. _`Un exemple de mise en oeuvre` : http://tinkerman.cat/the-espurna-board-a-smart-wall-switch-with-power-monitoring/#lightbox-gallery-oY6vOUw7/3/

Exemple open source

####

=======================
Choix du module relais
=======================

Coupure des 2 voies en même temps (phase et neutre) donc soit des relais 2 voies soit 8 relais.

Nous avons retenu l'option 8 relais car plus disponible dans l'écosphére ARDUINO.

Disponible entre autres chez `Banggood 8 Channel Module Module Relais`_ 

.. _`Banggood 8 Channel Module Module Relais` : https://www.banggood.com/fr/5Pcs-5V-8-Channel-Relay-Module-Board-For-Arduino-PIC-AVR-DSP-ARM-p-968931.html?rmmds=detail-left-hotproducts__2&cur_warehouse=CN

.. figure:: image/moduleRelais8Chan.jpg
    :align: center
    
    Photo module relais 8 voies de chez Banggod
    
####

=====================
Affectation des io
=====================

.. figure:: image/wemos-d1-mini-pinout_avecI2C.png
    :width: 600 px
    :align: center
    
    Wemos D1 Mini pinout

.. table:: Affectation des broches
    :align: center
    
    ===== =============
    pins  affectation
    ===== =============
    D0
    D1    I2C SCL
    D2    I2C data
    D3    Out1
    D4    Out2
    D5    Out3
    D6    Out3
    D7
    D8
    ===== =============

On va pas aller loin avec ça !

Nécessite l'utilisation d'un IO expander

MCP23017 I2C 16 bits IO expander

.. figure:: image/mpc2307_pinout.jpg
    :width: 400 px
    :align: center
    
    MPC23017 pinout

####

====================
Useful Documentation
====================

Exemples 

=============
Weblinks
=============

.. target-notes::