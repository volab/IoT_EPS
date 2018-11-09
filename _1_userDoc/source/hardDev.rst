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
#. horloge temps réelle
#. LED
#. bouton poussoirs
#. Affectation des io

####

==================   
Alimentation ESP
==================
Premier écueil: l'ESP peut-il s'alimenter en 5V ?

Réponse : oui


.. image:: ./image/alimWemosD1Mini.jpg

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

=====================
Affectation des io
=====================

Suite...

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