"""
:Nom de fichier: GuiFrameCalMag.py
:Autheur: J.Soranzo
:version: 20210319
:Dépendences: 
:Licence: (c) 2020 groupe SAFRAN
:Projet: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD

Partie de l'interface graphique dédiée à la gestion de la calibration du magnétomètre.

.. image:: images/guiCalMag.jpg
   :width: 300 px
"""


import tkinter as tk
from constantes import GEN_PADDING
from TrameMag import XYZ


class GuiFrameCalMag(tk.LabelFrame ):
    def __init__(self, masterFrame , posRow, posCol, padding,colspan, largeur ):
        """
        Block d'affichage des controles de calibration du magnétomètre
        """
        self.master = masterFrame
        self.calOn = False
        tk.LabelFrame.__init__( self, masterFrame, text="Calibration magnétomètre", width=(largeur-10)
            , height=130, relief=tk.GROOVE)
        self.grid(row=posRow, column=posCol, padx = padding, pady=padding, \
            columnspan=colspan, sticky=tk.NW)
        self.grid_propagate(0) #sinon Height et width ne sont pas pris en compte
        self.etiquetteBouton = tk.StringVar() #Obligation de passer par une variable pour pouvoir modifier le texte dynamiquement
        self.etiquetteBouton.set("Calibrer")
        widgetsVertPos = 0
        
        self.btnCal = tk.Button(self,
                                textvariable = self.etiquetteBouton,
                                state=tk.DISABLED,
                                command=self.toggleCalibration)
        self.btnCal.grid(row=widgetsVertPos, column=0, padx=GEN_PADDING,
                            pady=GEN_PADDING, sticky=tk.W)

        widgetsVertPos += 1
        self.etqMin=tk.Label(self,text='Min : ')
        self.etqMin.grid(row=widgetsVertPos,column=0, padx=padding, pady=padding, sticky=tk.W)
        self.valsMin=tk.Label(self, text="minx,miny,minz")
        self.valsMin.grid(row=widgetsVertPos,column=1, padx=padding, pady=padding,sticky=tk.W)

        widgetsVertPos += 1
        self.etqMax=tk.Label(self,text='Max : ')
        self.etqMax.grid(row=widgetsVertPos,column=0, padx=padding, pady=padding, sticky=tk.W)
        self.valsMax=tk.Label(self, text="maxx, maxy, maxz")
        self.valsMax.grid(row=widgetsVertPos,column=1, padx=padding, pady=padding,sticky=tk.W)

        widgetsVertPos += 1
        self.etqOff=tk.Label(self,text='Off : ')
        self.etqOff.grid(row=widgetsVertPos,column=0, padx=padding, pady=padding, sticky=tk.W)
        self.valsOff=tk.Label(self, text="offsetx, offsety, offsetz")
        self.valsOff.grid(row=widgetsVertPos,column=1, padx=padding, pady=padding,sticky=tk.W)        

    def toggleCalibration(self):
        '''
            callback associé au bouton Calibrer
        '''
        if not(self.calOn):
            self.calOn = True
            self.etiquetteBouton.set("Arrêter")
            print('Calibration démarré')
            
        else:
            self.calOn = False
            self.etiquetteBouton.set("Calibrer")
            print('Calibration arrêté')

    def displayData(self, min, max, offset):
        afficher = "{:04X}, {:04X}, {:04X}".format(min.x, min.y, min.z)
        self.valsMin.config(text=afficher)
        afficher = "{:04X}, {:04X}, {:04X}".format(max.x, max.y, max.z)
        self.valsMax.config(text=afficher)
        afficher = "{:3}, {:3}, {:3}".format(offset.x, offset.y, offset.z)
        self.valsOff.config(text=afficher)
        # print("affichage des données")

def main():
    import os
    # import serial
    from constantes import GEN_PADDING, SIZE_OF_FRAME
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameCalMag(root, 1, 1, GEN_PADDING, 1, 230)
    testedFrame.grid_propagate(0)
    testedFrame.btnCal.config( state=tk.NORMAL )
    # testedFrame.master.serialPort = serial.Serial() # juste pour pouvoir activer le bouton envoi !!!
    # import Trame as tr
    # trame = tr.Trame( 'COM1', SIZE_OF_FRAME)
    # trame.trameBrute = [ 0X52,0X44,0X43,0X02,
    # 0X01,0XFF,0X02,0X19,0X06,0X00,0X00,0X08,0XAC,0X06,0X11,
    # 0X02,0X00,0X01,0X12,0X66,0X00,0X3C,0X16,0X17,0X07,0X11,
    # 0X03,0X00,0X24,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    # 0X04,0XFF,0X6D,0X02,0X26,0XFC,0XF2,0XFF,0XD2,0X00,0X11,
    # 0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    # 0X01,0X26,0X09,0X0C ]
    # trame.trameDecoupee.populate( trame.trameBrute )
    # testedFrame.displayDataCapteur_O( trame.trameDecoupee )
    root.mainloop()

if __name__ == '__main__':
    main()