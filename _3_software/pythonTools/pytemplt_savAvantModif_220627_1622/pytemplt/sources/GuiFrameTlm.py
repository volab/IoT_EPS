import tkinter as tk


class GuiFrameTlm( tk.LabelFrame ):
    def __init__(self, masterFrame , posRow, posCol, padding ):
        """
        Block d'affichag des information du télémètre laser
        """
        tk.LabelFrame.__init__( self, masterFrame, text="Data Tlm", width=230, height=100
            , relief=tk.GROOVE)
        self.grid(row=posRow, column=posCol, padx = padding, pady=padding, sticky=tk.NW)
        self.grid_propagate(0) #sinon Hieght et width ne sont pas pris en compte

        self.etqDist=tk.Label(self,text='Distance: ')
        self.etqDist.grid(row=1,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.DistOctets=tk.Label(self, text="0x0102")
        self.DistOctets.grid(row=1,column=2, padx=padding, pady=padding)
        self.Distm=tk.Label(self, text="01 m", justify = tk.LEFT, bg = 'cyan')
        self.Distm.grid(row=1,column=3, padx=padding, pady=padding, sticky=tk.E)

    def displayDataCapteur_O( self, slicedFrame_O ):
        
        self.DistOctets.config(text=slicedFrame_O.dataTlm.dist.enHexa )
        self.Distm.config(text=slicedFrame_O.dataTlm.dist.enMetre )

def main():
    import os
    from constantes import GEN_PADDING, SIZE_OF_FRAME

    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameTlm(root, 1, 1, GEN_PADDING)
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