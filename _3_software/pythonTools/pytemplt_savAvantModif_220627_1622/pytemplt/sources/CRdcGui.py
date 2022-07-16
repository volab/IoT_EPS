"""
    :Nom de ficier: CRdcGui.py
    :Autheur: J.Soranzo
    :version: 2020210
    :Dépendences: tkinter, time, datetime, os et pySerial
    :Licence: c-2020 groupe SAFRAN
    :Projet: AVOCETTE RDC Capteurs
    :Société: SAFRAN Electronic & Defense
    :Entité: PAD
"""

# from tkinter import Label, Button, Frame
import tkinter as tk
from tkinter import ttk
import serial.tools.list_ports
from tkinter import messagebox
import serial
import os
from time import strftime, localtime
from datetime import datetime #juste pour les milisecondes :-(

import GuiFrameControles as FrameControles
import GuiFrameDisplay as FrameDisplay
import Trame as Tr
import constantes as CST
from TrameMag import XYZ


       

class CRdcGUI:
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

        self.magMin = XYZ( 32767, 32767, 32767 )
        """Calibration magnétomètre"""
        self.magMax = XYZ( -32768, -32768, -32768 )
        self.magOffset = XYZ(0,0,0)

        self.master = master
        master.title("RDC Capteur IHM de Test")

        self.frameCtrl = FrameControles.CFrameControles(master, self.GEN_PADDING, self.FEN_HAUTEUR)
        self.frameCtrl.grid_propagate(0)

        self.frameDisplay = FrameDisplay.GuiFrameDisplay(master, self.GEN_PADDING, self.FEN_HAUTEUR)
        self.frameDisplay.grid_propagate(0)
        
        
        self.statBar=tk.Label(master, width=20, anchor=tk.W, text="etat")
        self.statBar.grid(row=2, column=1, columnspan= 2, sticky=tk.E+tk.W+tk.N+tk.S)


    def rsHandler(self):
        """
        :fonction: rsHandler(self)

        Routine de traitement de réception des trames série
        Cette routine est appelée périodiquement. En fait elle relance elle-même sont propre timer.
        C'est une fonctionnalité apportée par tkinter.

        Nouveauté 2021 : c'est routine gère également les démarrage et enregistrement des trames.
        Mais le bouton, ainsi que les déclenchment et arrêt de l'enregistrement est fait dans
        la classe CFrameControles
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
            if trame.lastFrameOnError:
                self.tramesErrorCpt += 1
            if len(trame.trameBrute) != 0:
                #Trame reçue
                self.frameDisplay.msgZone.delete('1.0',tk.END)
                self.frameDisplay.msgZone.insert('1.0',\
                    trame.pourAffichage())
                trame.trameDecoupee.dataMag.offset.x = self.magOffset.x
                trame.trameDecoupee.dataMag.offset.y = self.magOffset.y
                trame.trameDecoupee.dataMag.offset.z = self.magOffset.z                
                self.frameDisplay.updateDataCapteur( trame.trameDecoupee )
                #Enregistrement
                if self.frameCtrl.frameRecord.recordOn:
                    if not(self.enregistrementEncours):
                        print("ouverture fichier")
                        baseChemin = os.path.dirname(__file__)
                        prefixe = strftime("%y%m%d_%H%M_" , localtime() )
                        print("Prefixe des fichiers d'enregistrement : " + prefixe)
                        try:
                            
                            fileName = prefixe + "raw.log"
                            chemin =  os.path.join( baseChemin, "dataRaw")
                            chemin =  os.path.join( chemin, fileName)
                            self.f = open(chemin, 'w')
                            fileName = prefixe + "lisibles.log"
                            chemin =  os.path.join( baseChemin, "data")
                            chemin =  os.path.join( chemin, fileName)
                            self.fHumRead = open(chemin, 'w', encoding="utf-8")                            
                          
                            self.enregistrementEncours = True
                        except IOError as e:
                            print("I/O error({0}): {1}".format(e.errno, e.strerror) )
                            
                    else:
                        #enregistrementEncours
                        if not(self.f.closed) or not(self.fHumRead.closed):                        
                            separateur = ","
                            ms = "{:03d}".format(int(datetime.now().microsecond/1000) )
                            recordPrefix = strftime("%H:%M:%S,", localtime()) + ms + separateur
                        if not(self.f.closed):
                            record = recordPrefix + trame.pourAffichage(separateur=',') + "\n"
                            self.f.write(record)
                        if not(self.fHumRead.closed):
                            record = recordPrefix + trame.pourEnregistrement() + "\n"
                            self.fHumRead.write(record)
                            # print(record)

                else:
                    if self.enregistrementEncours:
                        print("fermeture fichier")
                        if not(self.f.closed):
                            self.f.close()
                        if not(self.fHumRead.closed):   
                            self.fHumRead.close()
                        self.enregistrementEncours = False
                #Calibration
                if self.frameCtrl.frameCalMag.calOn:
                    magX = trame.trameDecoupee.dataMag.x.signed16
                    magY = trame.trameDecoupee.dataMag.y.signed16
                    magZ = trame.trameDecoupee.dataMag.z.signed16
                    self.magMin.x = min( self.magMin.x, magX )
                    self.magMin.y = min( self.magMin.y, magY )
                    self.magMin.z = min( self.magMin.z, magZ )

                    self.magMax.x = max( self.magMax.x, magX )
                    self.magMax.y = max( self.magMax.y, magY )
                    self.magMax.z = max( self.magMax.z, magZ )

                    self.magOffset.x = ( self.magMax.x +self.magMin.x ) /2
                    self.magOffset.y = ( self.magMax.y +self.magMin.y ) /2
                    self.magOffset.z = ( self.magMax.z +self.magMin.z ) /2

                    self.frameCtrl.frameCalMag.displayData( self.magMin, self.magMax, self.magOffset )

                    # print("calibration enCours")

            #self.frameCtrl.etqPortOpen.config(text=self.frameCtrl.portCom)
            
        self.statBar.config(text="Erreurs de trame : {}".format(self.tramesErrorCpt))
        self.master.after(self.RS_HANDLER_PERIOD, self.rsHandler)

import os
from constantes import GEN_PADDING, FEN_HAUTEUR


def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )

    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    frame = CRdcGUI(root)
    # frame.grid_propagate(0)
    root.mainloop()

if __name__ == '__main__':
    main()