"""
:Nom de fichier: GuiFrameBaro.py
:Autheur: J.Soranzo
:version: 20201002
:Dépendences: tkinter
:Licence: (c) 2020 groupe SAFRAN
:Projet: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD

Partie de l'interface graphique dédiée à l'affichage des données du baromètre.

"""
import tkinter as tk


class GuiFrameBaro( tk.LabelFrame ):
    """
    Cette classe hérite de la classe tkinter LabelFrame
    """
    def __init__(self, masterFrame , posRow, posCol, padding ):
        """
        Block d'affichags des information baromètre
        """
        tk.LabelFrame.__init__( self, masterFrame, text="Data BARO", width=230, height=100
            , relief=tk.GROOVE)
        self.grid(row=posRow, column=posCol, padx = padding, pady=padding, sticky=tk.NW)
        self.grid_propagate(0) #sinon Height et width ne sont pas pris en compte

        self.etqPression=tk.Label(self,text='Pression : ')
        self.etqPression.grid(row=1,column=1, padx=padding, pady=padding, sticky=tk.W)
        #Poids fort en premier donc octet 1
        self.pressionOctets=tk.Label(self, text="01020304")
        self.pressionOctets.grid(row=1,column=2, padx=padding, pady=padding)
        self.pressionMbar=tk.Label(self, text="01 mbar", justify = tk.LEFT, bg = 'cyan')
        self.pressionMbar.grid(row=1,column=3, padx=padding, pady=padding)
        # self.pressionOctet3=tk.Label(self, text="02")
        # self.pressionOctet3.grid(row=1,column=4, padx=padding, pady=padding)
        # self.pressionOctet4=tk.Label(self, text="03")
        # self.pressionOctet4.grid(row=1,column=5, padx=padding, pady=padding)
    
        self.etqTemp=tk.Label(self,text='Temperat : ')
        self.etqTemp.grid(row=2,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.tempOctets=tk.Label(self, text="06070809")
        self.tempOctets.grid(row=2,column=2, padx=padding, pady=padding)
        self.tempDeg=tk.Label(self, text="05 °C", justify = tk.LEFT, bg = 'cyan')
        self.tempDeg.grid(row=2,column=3, padx=padding, pady=padding, sticky = tk.NW)
        # self.tempOctet3=tk.Label(self, text="06")
        # self.tempOctet3.grid(row=2,column=4, padx=padding, pady=padding)
        # self.tempOctet4=tk.Label(self, text="07")
        # self.tempOctet4.grid(row=2,column=5, padx=padding, pady=padding)

    def displayDataCapteur_O( self, slicedFrame_O ):
        """
        Méthode qui prend en charge l'affichage des données capteur dans les différents contrôles
        """
        self.pressionOctets.config(text=slicedFrame_O.dataBaro.pression.enHexa )
        self.tempOctets.config(text=slicedFrame_O.dataBaro.temp.enHexa )
        self.pressionMbar.config(text=slicedFrame_O.dataBaro.pression.enMbar)
        self.tempDeg.config(text=slicedFrame_O.dataBaro.temp.enDeg )

import os
from constantes import GEN_PADDING, SIZE_OF_FRAME

def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameBaro(root, 1, 1, GEN_PADDING)
    testedFrame.grid_propagate(0)
    import Trame as tr
    trame = tr.Trame( 'COM1', SIZE_OF_FRAME)
    trame.trameBrute = [ 0X52,0X44,0X43,0X02,
    0X01,0XFF,0X02,0X19,0X06,0X00,0X00,0X08,0XAC,0X06,0X11,
    0X02,0X00,0X01,0X12,0X66,0X00,0X3C,0X16,0X17,0X07,0X11,
    0X03,0X00,0X24,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    0X04,0XFF,0X6D,0X02,0X26,0XFC,0XF2,0XFF,0XD2,0X00,0X11,
    0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    0X01,0X26,0X09,0X0C ]
    trame.trameDecoupee.populate( trame.trameBrute )
    testedFrame.displayDataCapteur_O( trame.trameDecoupee )
    root.mainloop()

if __name__ == '__main__':
    main()