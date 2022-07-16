#! /usr/bin/env python3
# -*- coding: utf8 -*-

"""
Programme principal
====================

    :Nom de ficier: main.py
    :Autheur: J.Soranzo
    :version: 20210316
    :Dépendences: tkinter et pySerial (au niveau de la classe CRdcGui)
    :Licence: (c) 2020 groupe SAFRAN
    :Projet: AVOCETTE RDC Capteurs
    :Société: SAFRAN Electronic & Defense
    :Entité: PAD

Installation
====================================================================================================
    Ce programme Python ne dispose pas d'un installer dédié.

    Pour pouvoir l'utiliser, il convient d'intaller Python 3.x puis pySerial
    Puis de lancer main.py via la commande python main.py

Vue d'ensemble
====================================================================================================
Ce programme est destiné à afficher les trames issues de la carte RDC capteur.

Ce programme est une simple interface graphique basée sur TK inter (un gestionnaire d'interface 
graphique intégré à Python donc ne nécessite pas d'intaller un package complexe supplémentaire comme 
pyQt).

Cette interface graphique est séparée en 2 parties, à gauche les controles et à droite l'affichage
de la trame décodée.

**Mise en garde** frames et trames. Dans la littérature gui et tkinter on parle de frame pour
désigner les boîtes contenant les éléments de l'interface graphique. On parle égalment de frames
dans le cas des les liaisons série. J'emploie donc le terme de trames dans ce dernier cas.

Les scripts Python préfixés par Gui sont les classes de l'interface graphique souvent associé à 
un fichier sans le préfixe qui réalise les traitements comme GuiFrameAlim et TrameAlim.

La trame reçue l'est par l'intermédiaire de l'intance trame de la classe Trame. 
C'est intance n'est pas persistante. Elle est crée et détruite à chaque exécution du handler RS.
Les seules données persistantes sont au niveau de l'interface graphique.

Petit mode d'emploi
====================================================================================================
Réaliser les branchements, notamment le doungle USB/RS connecté au PC avant de lancer l'IHM.
En effet, pour le moment il n'y a pas de scan dynamique des ports.

Pour identifier le port COM à utiliser, on peut utiliser soit le bouton "all COMs info" soit
le gestionnaire de périphérique Windows.

Au lancement, rien ne se passe (la carte RDC capteurs attends de recevoir sa trame de configuration)
Cliquer sur le bouton ENVOI de la zone configuration


.. image:: images/ihm.jpg 


Description du script
====================================================================================================    
"""

from tkinter import Tk  
from CRdcGui import CRdcGUI
from constantes import FEN_HAUTEUR

def main():
    """Programme principal de l'IHM de test du projet RDC Capteurs.

    Ce script Python lance l'interface graphique basée sur tkinter via la classe CRdcGui.CRdcGUI
    CRdcGui.

    Ce module lance également le timer de réception de la liaisons série.
    La période de ce timer est RS_HANDLER_PERIOD dans constantes.py

    """
    root = Tk()
    rdc_gui = CRdcGUI(root)
    print("Hauteur de la fenetre {}".format(FEN_HAUTEUR) )
    root.after(rdc_gui.RS_HANDLER_PERIOD, rdc_gui.rsHandler)
    root.mainloop()

if __name__ == "__main__":
    main()