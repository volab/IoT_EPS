=============
Interface WEB
=============

Prestation des différents comportement de l'interface WEB

.. contents:: Table des matières
.. section-numbering::

####

------------
Comportement
------------

Comportement par défaut
=======================

Deux type de présentation par défaut sont envisager :

    * Résumer par prise

    * Résumer globale

Résumer par prise
-----------------

Lors de l'accès à la page, en cas de rafraichissement ou lors d'une action sur un bouton 'Envoyer',
chaque prise présente un résumé de son état et du mode dans lequel elle est configurée. Ces
informations sont directement lue depuis le fichiers 'config3.json'.

    **N.B: Ce mode ne sera pas retenu**

Résumer global
--------------

Lors de l'accès à la page, en cas de rafraichissement ou lors d'une action sur un bouton 'Envoyer',
seul un résumer global de l'état et de la configuration de chaque prise est présenté à 
l'utilisateur. Les éléments "PRISE" seront masqués. Pour accéder à la configuration d'une prise, il 
faut cliquer sur nom dans la barre (ou le menu) de navigation.

    **N.B: Ce mode sera utilisé**

Comportement responcive
=======================

Sur les petites résolution d'écran (tablette et mobile):

    * l'entête comprenant le nom du bloc multi-prise et le logo sont masqués.

    * La barre de navigation (en haut du document) est remplacé par un bouton qui ouvre une fenêtre
      latérale (sidebar), reprenant tous les éléments (et tous les liens) de la barre de navigation.

    * Le menu 'Sélection du mode' de chaque prise est remplacer par un menu déroulant.

####

-----------------------
Sélection et navigation
-----------------------

Accès à une prise spécifique
============================

L'accès à une prise spécifique se fait soit depuis la barre de navigation, soit en navigant (avec la
barre de navigation verticale ou avec le bouton centrale de la souris).

Sélection d'un mode
===================

La sélection des mode se fait au niveau de chaque prise par un menu spécifique

####

---------------------------------------------
Action et validation des formulaires par mode
---------------------------------------------

Mode Manuel
===========

[TODO] A renseigner [TODO]
Mode Minuterie
==============

[TODO] A renseigner [TODO]

Mode Cyclique
=============

[TODO] A renseigner [TODO]

Mode Hebdomadaire
=================

    * La case à cocher "Sélectionner tous les jours" permet de sélectionner tous les jours d'un
      seule coup. Cet élément n'est pas obligatoire.

    * Les cases à cocher "jour de la semaine" servent à définir les jours sur lesquels appliquer la
      plage de fonctionnement. Au moins un élément doit être sélectionner.

    * Le champ de saisie "Heure de début" permet de définir l'heure à partir de laquelle la prise 
      s'allume. Cet élément est obligatoire.

    * Le champ de saisie "Heure de fin" permet de définir à partir de laquelle la prise s'éteint.
      Cet élément est obligatoire.

    **N.B:** Les champs "Heure de début" et "Heure de fin" ne peuvent pas avoir la même valeur.

    * Le sélecteur "Arrêt provisoire" Arrête la prise mais ne change pas la configuration de la
      prise. Lorsque cet élément est sélectionné, tous les éléments associés au mode en cours sont
      désactiver (grisés et inactif).

        - Si le sélecteur est actif, la prise est OFF

        - Si le sélecteur est inactif, la prise est ON

        - Si le sélecteur est actif et sans action de la part de l'utilisateur, la prise reste OFF
          jusqu'au prochain cycle de fonctionnement.

Mode Clone
==========

[TODO] A renseigner [TODO]

####

-----------
Webographie
-----------

.. target-notes::

