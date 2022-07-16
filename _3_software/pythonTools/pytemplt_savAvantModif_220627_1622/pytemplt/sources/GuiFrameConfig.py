"""
    :Nom de fichier: CGuiFrameConfig.py
    :Autheur: J.Soranzo
    :version: 2020210
    :Dépendences: pySerial
    :Licence: c-2020 groupe SAFRAN
    :Projet: AVOCETTE RDC Capteurs
    :Société: SAFRAN Electronic & Defense
    :Entité: PAD
"""
import tkinter as tk


import serial
from constantes import GEN_PADDING, FREQ_EMISSION

import TrameConf as trConf

class GuiFrameConfig(tk.LabelFrame ):
    def __init__(self, masterFrame , posRow, posCol, padding,colspan, largeur ):
        """
        Block d'affichag des controles de configutation
        """
        self.master = masterFrame
        tk.LabelFrame.__init__( self, masterFrame, text="Configuration", width=(largeur-10)
            , height=100, relief=tk.GROOVE)
        self.grid(row=posRow, column=posCol, padx = padding, pady=padding, \
            columnspan=colspan, sticky=tk.NW)
        self.grid_propagate(0) #sinon Height et width ne sont pas pris en compte


        widgetsVertPos = 0
        self.btnEnvoi = tk.Button(self, text="ENVOI", state=tk.DISABLED, command=self.envoiConfig)
        self.btnEnvoi.grid(row=widgetsVertPos, column=0, padx=GEN_PADDING,
                            pady=GEN_PADDING, sticky=tk.W)



        widgetsVertPos +=1
        self.etqFreqTrame = tk.Label(self, text="Frequence Trame FMAP : ")
        self.etqFreqTrame.grid(row=widgetsVertPos,column=0, padx=padding, pady=padding, sticky=tk.W ,columnspan=2)

        widgetsVertPos +=1
        self.fTrameFmapVal = tk.StringVar()
        self.fTrameFmapVal.set( FREQ_EMISSION )
        self.fTRameFmapCtrl = tk.Entry(self, text="5", width=5, textvariable = self.fTrameFmapVal, justify= tk.RIGHT )
        self.fTRameFmapCtrl.grid( row=widgetsVertPos,column=0, padx=padding, pady=padding, sticky=tk.E )
        self.etqFreqTrame = tk.Label(self, text="Hz (5 à 100)")
        self.etqFreqTrame.grid(row=widgetsVertPos,column=1, padx=padding, pady=padding, sticky=tk.W)

    def envoiConfig(self):
        '''
            callback associé au bouton ENVOI
        '''
        
        #normalement toujours vrai puisque le bouton n'est autorisé que si le port est ouvert
        print( "Fréquence de trame FMAP transmise : {}".format(self.fTrameFmapVal.get()))
        tc = trConf.TrameConf()
        tc.freqEmission = int(self.fTrameFmapVal.get( ))
        if self.master.serialPort.is_open:  
            
            print('envoi trame config')
            self.master.serialPort.write( tc.trameBytes )




def main():
    import os
    import serial
    from constantes import GEN_PADDING, SIZE_OF_FRAME
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameConfig(root, 1, 1, GEN_PADDING, 1, 230)
    testedFrame.grid_propagate(0)
    testedFrame.btnEnvoi.config( state=tk.NORMAL )
    testedFrame.master.serialPort = serial.Serial() # juste pour pouvoir activer le bouton envoi !!!
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