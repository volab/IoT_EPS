++++++++++++++++++++++++++++++++++++++++
Document de conception soft de IOT_ESP
++++++++++++++++++++++++++++++++++++++++

.. contents:: Table of Contents
.. section-numbering::

.. include:: ../../README.rst
   :encoding: UTF-8

==============
Avancement
==============
#. Affichage d'un page html static: ok
#. Affichage page html fichier SPIFFS : ok
#. Affichage de l'heure à partir d'une page en dur dans le code : ok
#. Affichage page avec CSS : ok
#. Gestion des mode wifi SoftAP vs client : ok
#. reception d'une action via un bouton :  
#. lecture du fichier de configuration : ok
#. intégration MCP23017 : ok
#. lecture du fichier de configuration façon Pierre (config2.json) :
#. gestion bouton poussoir mécanique : 
#. Ecriture fichier json : 

====================================
Convention de nommage
====================================

Référence : config3.json


====================================
Penser à:
====================================

#. terminer l'implémentation des méthodes de CPowerPlug ( isItTimeToSwitch )
#. regarder javascript http request pour faire du DELETE

====================================
Modes de fonctionnement des prises
====================================

Manuel
======
- appui sur BP ON/OFF
- durée avant arrêt : pour s'offrir la possibilité de couper la prise en cas de départ prématurer...
- ou heure d'arrêt : dans le même état d'esprit mais pour fixer une heure absolue.

Timer / minuteur / mode cuit oeuf
==================================
- 1 seul paramètre la durée ON à partir de maintenant (durée limité à 300mn)
- 1 appui court lance ou relance la minuterie
- 1 appui sur BP (long) met OFF et repasse en manuelle

Périodique/cyclique
=====================
- duré on
- durée off 
- avec reprise de On après off indéfiniment jusqu'au repassage en commande manuelle.
- avec champ heure de début (et 'Entrez une heure de début (facultatif)' par défaut)
- un appui court sur BP met à OFF mais reste en mode calendaire pour le cycle suivant
- 1 appui sur BP (long) met OFF et repasse en manuelle

Hebdomadaire
==============
- heure de mise on
- heure de mise off
- choix des jours de la semaine
- un appui court sur BP met à OFF mais reste en mode calendaire pour le cycle suivant
- 1 appui sur BP (long) met OFF et repasse en manuelle

Clone
========
Clone le fonctionnement d'une des 3 autres prises

Evolutions possibles
=====================
- un mixte entre cyclique et hebo: clyclique mais seulement pendant un certaines 
  période de la journée.
- Sur le mode hebdo, prévoir la possibilité d'avoir plusieurs plage de fonctionnement par jours
  et différentes chaque jour
- Mode compte à rebour : le système est en mode manuel ON et on souhait qu'il s'éteigne
  tout seul dans 2 heures

Factorisation des varibales de mode
=========================================

::

    redPlug
      State = ON
      Mode = Manuel | Minuterie | Cyclique | Hebdomadaire | Clone
      hDebut =
      hFin = 
      dureeOn = 60 en minutes
      dureeOff =  en minutes
      Jours[] s = OFF,OFF,OFF,OFF,OFF,OFF,OFF
      clonedPlug =
      onOffCount = 10  
  
=====================================
Comportement à la mise sous tension
=====================================

Soit l'interrupteur général est actif et on reprend où on en était.

Soit l'interrupteur général est  inactif et on reprend en mode manuel.

L'interrupteur général coupe le 220V des prise mais pas de l'ESP8266.

Bien expliquer les 2 mode de fonctionnement dans l'interface WEB et donner le choix à l'utilisateur.

Expliquer le coup de la coupure de courant.

==============
Choix dev soft
==============
wifi access point

Les pages html sont dans le file système SPIFFS

WEMOS D1 MIN ARDUINO configurattion:

.. image:: ./image/wemosD1Mini_configArduino.jpg

==========================
Développement des page Web
==========================
HTML5 et css

Les requetes html
=====================

ipaddr/config?plug=redPlug

/PlugConfig?plug=red&mode=manuel
/modeManuel?plug=redPlug

Utilisation de formulaire

====================
Serveur html ESP8266
====================
Repris de l'exemple fourni avec l'IDE ARDUINO : FSBrowser

Cette exemple apporte un lot de fonction qui gérent l'envoie de fichier css, jpg et autres...

==============
IOExpander
==============

Au cours de la définition hardware pin, on a décider d'utiliser un IOEpander MPC23017 d'où nouvelle
dépendance à la librairie Adafruit_MCP23017.h

Métodes disponibles:

.. code:: cpp

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

===============================
Useful Documentation
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

fastLed
=============

`FastLed lib`_

.. _`FastLed lib` : https://gi thub.com/FastLED/FastLED

json (lectures / écritures)
==============================

La librairie utilisée: `ArduinoJson`_ version 5.13.2 

.. _`ArduinoJson` : https://github.com/bblanchon/ArduinoJson

Assistant plutôt efficace: `ArduinoJson Assistant`_

.._`ArduinoJson Assistant`  : https://arduinojson.org/v5/assistant/

========================
Librairies utilisées
========================
last update : 02/12/2018

8 libs:

- Utilisation de la bibliothèque ESP8266WiFi version 1.0
- Utilisation de la bibliothèque ESP8266WebServer version 1.0 
- Utilisation de la bibliothèque ArduinoJson version 5.13.2 
- Utilisation de la bibliothèque Wire version 1.0
- Utilisation de la bibliothèque RTClib version 1.2.0
- Utilisation de la bibliothèque ESP8266mDNS
- Utilisation de la bibliothèque Adafruit_MCP23017_Arduino_Library version 1.0.3
- Utilisation de la bibliothèque FastLED version 3.2.1

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


=============
Webographie
=============

.. target-notes::

