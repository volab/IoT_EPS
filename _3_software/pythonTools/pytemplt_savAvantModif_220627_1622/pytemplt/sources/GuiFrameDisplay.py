import tkinter as tk
from tkinter import ttk

import GuiFrameMag as FMag
import GuiFrameBaro as FBaro
import GuiFramePitot as FPit
import GuiFrameTlm as FTlm
import GuiFrameAlim as FAlim




     

class GuiFrameDisplay(tk.Frame):

    def __init__(self, master, genPad, fenHeight, **kwargs):
        self.GEN_PADDING = genPad
        self.FEN_HAUTEUR = fenHeight
    
        tk.Frame.__init__(self, master, height=self.FEN_HAUTEUR ,  width=500 , relief=tk.GROOVE, bg="blue", bd=5, class_='CframeOfContrl', **kwargs)
        self.grid(row=1, column=2, padx=self.GEN_PADDING, pady=self.GEN_PADDING)


        self.msgZone=tk.Text(self, bd=5, padx=genPad , pady=genPad , 
            relief=tk.GROOVE, width=57, height= 6)
        self.msgZone.grid(row=1, column=1, padx=genPad , pady=genPad, sticky=tk.NW, columnspan=2)

        self.msgZone.insert(tk.END, "Texte initial")
        s=tk.Scrollbar(self)
        s.grid(row=1, column=3, sticky=tk.N+tk.S)
        s.config(command=self.msgZone.yview)
        self.msgZone.config(yscrollcommand=s.set)

        self.dataBaroFrame = FBaro.GuiFrameBaro( self, 2, 1, self.GEN_PADDING)
        self.dataMagFrame  = FMag.GuiFrameMag(self, 2, 2, self.GEN_PADDING)
        self.dataPitoFrame = FPit.GuiFramePitot(self, 3, 1, self.GEN_PADDING)
        self.dataTlmFrame  = FTlm.GuiFrameTlm(self, 3, 2, self.GEN_PADDING)
        self.dataAlimFrame = FAlim.GuiFrameAlim(self, 4, 2, self.GEN_PADDING)
    
    def updateDataCapteur(self, trameDecoupee ):
        self.dataBaroFrame.displayDataCapteur_O( trameDecoupee )
        self.dataMagFrame.displayDataCapteur_O( trameDecoupee ) 
        self.dataPitoFrame.displayDataCapteur_O( trameDecoupee )
        self.dataTlmFrame.displayDataCapteur_O( trameDecoupee )
        self.dataAlimFrame.displayDataCapteur_O( trameDecoupee )


import os
from constantes import GEN_PADDING, FEN_HAUTEUR

def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    frameDisplay = GuiFrameDisplay(root, GEN_PADDING, FEN_HAUTEUR)
    frameDisplay.grid_propagate(0)
    root.mainloop()

if __name__ == '__main__':
    main()
    