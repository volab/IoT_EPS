import tkinter as tk


class GuiFrameAlim( tk.LabelFrame ):
    def __init__(self, masterFrame , posRow, posCol, padding ):
        """
        Block d'affichage des information d'alimentation
        """
        tk.LabelFrame.__init__( self, masterFrame, text="Data alim", width=230, height=120
            , relief=tk.GROOVE)
        self.grid(row=posRow, column=posCol, padx = padding, pady=padding, sticky=tk.NW)
        self.grid_propagate(0) #sinon Hieght et width ne sont pas pris en compte

        ligne=1
        self.etqVin=tk.Label(self,text='Vin:    ')
        self.etqVin.grid(row=ligne,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.VinOctets=tk.Label(self, text="0x0102")
        self.VinOctets.grid(row=ligne,column=2, padx=padding, pady=padding)
        self.VinVolt=tk.Label(self, text="01.00 V", justify = tk.LEFT, bg = 'cyan')
        self.VinVolt.grid(row=ligne,column=3, padx=padding, pady=padding, sticky=tk.E)

        ligne +=1
        self.etqV5Vtlm=tk.Label(self,text='V5Vtlm: ')
        self.etqV5Vtlm.grid(row=ligne,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.V5VtlmOctets=tk.Label(self, text="0x0102")
        self.V5VtlmOctets.grid(row=ligne,column=2, padx=padding, pady=padding)
        self.V5VtlmVolt=tk.Label(self, text="01.00 °C", justify = tk.LEFT, bg = 'cyan')
        self.V5VtlmVolt.grid(row=ligne,column=3, padx=padding, pady=padding, sticky=tk.E)

        ligne +=1
        self.etqV3v=tk.Label(self,text='V3v: ')
        self.etqV3v.grid(row=ligne,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.V3vOctets=tk.Label(self, text="0x0102")
        self.V3vOctets.grid(row=ligne,column=2, padx=padding, pady=padding)
        self.V3vVolt=tk.Label(self, text="01.00 V", justify = tk.LEFT, bg = 'cyan')
        self.V3vVolt.grid(row=ligne,column=3, padx=padding, pady=padding, sticky=tk.E)

        ligne +=1
        self.etqTemp=tk.Label(self,text='Temp: ')
        self.etqTemp.grid(row=ligne,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.TempOctets=tk.Label(self, text="0x0102")
        self.TempOctets.grid(row=ligne,column=2, padx=padding, pady=padding)
        self.TempDeg=tk.Label(self, text="01.00 V", justify = tk.LEFT, bg = 'cyan')
        self.TempDeg.grid(row=ligne,column=3, padx=padding, pady=padding, sticky=tk.E)


    def displayDataCapteur_O( self, slicedFrame_O ):
        self.VinOctets.config(text=slicedFrame_O.dataAlim.Vin.enHexa)
        self.VinVolt.config(text=slicedFrame_O.dataAlim.Vin.enVolt)
        self.V5VtlmOctets.config(text=slicedFrame_O.dataAlim.V5Vtlm.enHexa)
        self.V5VtlmVolt.config(text=slicedFrame_O.dataAlim.V5Vtlm.enVolt)
        self.V3vOctets.config(text=slicedFrame_O.dataAlim.V3v.enHexa)
        self.V3vVolt.config(text=slicedFrame_O.dataAlim.V3v.enVolt)
        self.TempOctets.config(text=slicedFrame_O.dataAlim.temp.enHexa)
        self.TempDeg.config(text=slicedFrame_O.dataAlim.temp.enDeg)

def main():
    import os
    from constantes import GEN_PADDING, SIZE_OF_FRAME

    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameAlim(root, 1, 1, GEN_PADDING)
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
    print("Fin du test du module " + os.path.basename(__file__))

if __name__ == '__main__':
    main()