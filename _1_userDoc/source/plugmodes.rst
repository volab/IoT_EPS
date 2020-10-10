++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Plugs modes
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:Auteur: J.Soranzo
:Date: October 2020
:Societe: VoRoBoTics
:Entity: VoLAB

.. contents::
    :backlinks: top


.. index:: Modes

====================================
Plugs modes description
====================================

Manuel
======
- press on ON/OFF push button
- durée avant arrêt (durée limité à 300mn): pour s'offrir la possibilité de couper la prise en cas de départ prématurer...
- ou heure d'arrêt : dans le même état d'esprit mais pour fixer une heure absolue.

Timer / minuteur / mode cuit oeuf
==================================
- 1 seul paramètre la durée ON à partir de maintenant (durée limité à 300mn00s)
- 1 appui court lance ou relance la minuterie
- 1 appui sur BP (long) met OFF et repasse en manuelle
- la minuterie peut être avec des secondes exmple 2mn30s (2:30 dans la requête)

La minuterie est-elle uniquement lancée par BP ? Sinon comment on fait la diff
If state == On immediat start 

Périodique/cyclique
=====================
- duré on
- durée off 
- avec reprise de On après off indéfiniment jusqu'au repassage en commande manuelle.
- avec champ heure de début (et 'Entrez une heure de début (facultatif)' par défaut)
- un appui court sur BP met à OFF mais reste en mode cyclique pour le cycle suivant
- un deuxième appui court reprend le cycle (attention ne met pas forcément à ON)
- le mode pause de l'interface web effectue les mêmes actions que ci-dessus

- 1 appui sur BP (long) met OFF et repasse en manuelle

Hebdomadaire
==============
- heure de mise on
- heure de mise off
- choix des jours de la semaine
- un appui court sur BP met à OFF mais reste en mode Hebdomadaire pour le cycle suivant
- un deuxième appui court reprend le cycle (attention ne met pas forcément à ON)
- le mode pause de l'interface web effectue les mêmes actions que ci-dessus
- 1 appui sur BP (long) met OFF et repasse en manuelle

Clone
========
Clone le fonctionnement d'une des 3 autres prises. Il s'agit d'une copie des paramètres.
Ce n'est pas un clone dynamique. Ce qui signifie que l'information de la prise source et de
son état au moment du clonage ne sont pas historisés.

Evolutions possibles
=====================
- un mixte entre cyclique et hebo: clyclique mais seulement pendant un certaines 
  période de la journée.
- Sur le mode hebdo, prévoir la possibilité d'avoir plusieurs plage de fonctionnement par jours
  et différentes chaque jour
- connexion MQTT, IFTTT, Flic, openHAB


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


====================================================================================================
Weblinks
====================================================================================================

.. target-notes::