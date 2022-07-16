"""
    :Nom de ficier: CGui.py
    :Autheur: J.Soranzo
    :version: 20220703
    :Dépendences: tkinter, time, datetime, os et pySerial
    :Licence: c-2020 VoRoBoTics
    :Projet: IOT Eps
    :Société: VoRoBoTics
    :Entité: VoLAB
"""

# from tkinter import Label, Button, Frame
# import os
# import sys
# SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
# sys.path.insert(0,os.path.dirname(SCRIPT_DIR))

import tkinter as tk
from tkinter import ttk
import serial.tools.list_ports
from tkinter import messagebox
import serial
import os
from time import strftime, localtime
from datetime import datetime #juste pour les milisecondes :-(

import modulesUI.GuiFrameControles as FrameControles
import modulesUI.GuiFrameDisplay as FrameDisplay
import modulesFonctionnels.Trame as Tr
import constantes as CST
# from TrameMag import XYZ


       

class mainUi:
    """
    Classe qui fait le regrouppement des 2 classes d'interface graphique principale du logiciel.

    Elle instancie la partie de gauche : les controles, et la partie de droite : les affichages

    Via les classes CFrameControles et GuiFrameDisplay

    Cette classe contient également la méthode de réception des trames série !

    A noter que cette classe ne contient pas d'autotest.
    
    """
    def __init__(self, master):
        self.FEN_HAUTEUR = CST.FEN_HAUTEUR
        self.GEN_PADDING = CST.GEN_PADDING
        self.RS_HANDLER_PERIOD = CST.RS_HANDLER_PERIOD
        self.SIZE_OF_FRAME = CST.SIZE_OF_FRAME
        # self.BTN_QUIT_ROW = 6
        # self.LABEL_VERT_POS = 2
        self.tramesErrorCpt = 0
    
        self.cpt = 0
        """ Compteur qui s'affiche dans la zone du port série lorsqu'on est pas connecté"""
        self.enregistrementEncours = False
        self.f = 0
        """ handler du fichier d'enregistrement des trames"""
        self.fHumRead = 0
        """ handler du fichier d'enregistrement des trames au format lisible"""

        # self.magMin = XYZ( 32767, 32767, 32767 )
        """Calibration magnétomètre"""
        # self.magMax = XYZ( -32768, -32768, -32768 )
        # self.magOffset = XYZ(0,0,0)

        self.master = master
        self.master.title( CST.IHM_TITLE )

        self.frameCtrl = FrameControles.CFrameControles(master, self.GEN_PADDING, self.FEN_HAUTEUR)
        self.frameCtrl.grid_propagate(0)

        self.frameDisplay = FrameDisplay.GuiFrameDisplay(master, self.GEN_PADDING, self.FEN_HAUTEUR, CST.ZONE_DE_TEXTE_HAUTEUR)
        self.frameDisplay.grid_propagate(0)
        
        
        self.statBar=tk.Label(master, width=20, anchor=tk.W, text="etat")
        self.statBar.grid(row=2, column=1, columnspan= 2, sticky=tk.E+tk.W+tk.N+tk.S)


    def rsHandler(self):
        """
        :fonction: rsHandler(self)

        Routine de traitement de réception des trames série
        Cette routine est appelée périodiquement. En fait elle relance elle-même sont propre timer.
        C'est une fonctionnalité apportée par tkinter.
        """
        comPortState = self.frameCtrl.serialPortIsOpen
        if not comPortState:
            self.cpt +=1
            self.frameCtrl.etqPortOpen.config(text=self.cpt)
            self.tramesErrorCpt = 0
        else:
            #Port serie ouvert
            trame = Tr.Trame( self.frameCtrl.serialPort, self.SIZE_OF_FRAME )
            trame.recevoirTrame()
            # if trame.lastFrameOnError:
            #     self.tramesErrorCpt += 1
            # if len(trame.trameBrute) != 0:
            #     #Trame reçue
            self.frameDisplay.msgZone.delete('1.0',tk.END)
            # self.frameDisplay.msgZone.insert('1.0',\
            #         trame.pourAffichage())
            #     trame.trameDecoupee.dataMag.offset.x = self.magOffset.x
            #     trame.trameDecoupee.dataMag.offset.y = self.magOffset.y
            #     trame.trameDecoupee.dataMag.offset.z = self.magOffset.z                
            #     self.frameDisplay.updateDataCapteur( trame.trameDecoupee )

        
            
        self.statBar.config(text="Erreurs de trame : {}".format(self.tramesErrorCpt ) )
        self.master.after(self.RS_HANDLER_PERIOD, self.rsHandler)

import os
from constantes import GEN_PADDING, FEN_HAUTEUR


def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )

    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    frame = mainUi(root)
    # frame.grid_propagate(0)
    root.mainloop()

if __name__ == '__main__':
    main()