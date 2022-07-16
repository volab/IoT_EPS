import tkinter as tk


class GuiFrameMag(tk.LabelFrame):
    def __init__(self, masterFrame, posRow, posCol, padding):
        # super(FrameMag, self).__init__(masterFrame, text="Data MAGNETO", width=230, height=150)
        tk.LabelFrame.__init__(self, masterFrame, text="Data MAGNETO", width=230, height=150)
        self.grid( row=posRow, column=posCol, padx = padding, pady=padding, sticky=tk.NW)
        self.grid_propagate(0) #sinon Hieght et width ne sont pas pris en compte

        lignMagFrame=1
        self.etqX=tk.Label(self,text='Out X : ')
        self.etqX.grid(row=1,column=lignMagFrame, padx=padding, pady=padding, sticky=tk.W)
        self.xOctet1=tk.Label(self, text="08")
        self.xOctet1.grid(row=lignMagFrame,column=2, padx=padding, pady=padding)
        self.xOctet2=tk.Label(self, text="09")
        self.xOctet2.grid(row=lignMagFrame,column=3, padx=padding, pady=padding)
        self.etqXDec=tk.Label(self,text=' : gauss')
        self.etqXDec.grid(row=lignMagFrame,column=4, padx=padding, pady=padding, sticky=tk.W)

        lignMagFrame+=1
        self.etqY=tk.Label(self,text='Out Y : ')
        self.etqY.grid(row=lignMagFrame,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.yOctet1=tk.Label(self, text="0A")
        self.yOctet1.grid(row=lignMagFrame,column=2, padx=padding, pady=padding)
        self.yOctet2=tk.Label(self, text="0B")
        self.yOctet2.grid(row=lignMagFrame,column=3, padx=padding, pady=padding)
        self.etqYDec=tk.Label(self,text=' : gauss')
        self.etqYDec.grid(row=lignMagFrame,column=4, padx=padding, pady=padding, sticky=tk.W)

        lignMagFrame+=1
        self.etqZ=tk.Label(self,text='Out Z : ')
        self.etqZ.grid(row=lignMagFrame,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.zOctet1=tk.Label(self, text="0C")
        self.zOctet1.grid(row=lignMagFrame,column=2, padx=padding, pady=padding)
        self.zOctet2=tk.Label(self, text="0D")
        self.zOctet2.grid(row=lignMagFrame,column=3, padx=padding, pady=padding)
        self.etqZDec=tk.Label(self,text=' : gauss')
        self.etqZDec.grid(row=lignMagFrame,column=4, padx=padding, pady=padding, sticky=tk.W)

        lignMagFrame+=1
        self.etqTemp=tk.Label(self,text='Temp  : ')
        self.etqTemp.grid(row=lignMagFrame,column=1, padx=padding, pady=padding, sticky=tk.W)
        self.tempOctet1=tk.Label(self, text="0C")
        self.tempOctet1.grid(row=lignMagFrame,column=2, padx=padding, pady=padding)
        self.tempOctet2=tk.Label(self, text="0D")
        self.tempOctet2.grid(row=lignMagFrame,column=3, padx=padding, pady=padding)
        self.etqTempDec=tk.Label(self,text=' : Temp(deg)')
        self.etqTempDec.grid(row=lignMagFrame,column=4, padx=padding, pady=padding, sticky=tk.W)

        lignMagFrame+=1
        self.etqDir=tk.Label(self,text='Dir  : ')
        self.etqDir.grid(row=lignMagFrame,column=1, padx=padding, pady=padding, sticky=tk.W)

        self.etqDirDec=tk.Label(self,text=' : dir(°)')
        self.etqDirDec.grid(row=lignMagFrame,column=4, padx=padding, pady=padding, sticky=tk.W)

    def displayDataCapteur_O( self, slicedFrame_O ):
        self.xOctet1.config(text=format(slicedFrame_O.dataMag.x.poidsFort,"02X"))
        self.xOctet2.config(text=format(slicedFrame_O.dataMag.x.poidsFaible,"02X"))
        self.yOctet1.config(text=format(slicedFrame_O.dataMag.y.poidsFort,"02X"))
        self.yOctet2.config(text=format(slicedFrame_O.dataMag.y.poidsFaible,"02X"))
        self.zOctet1.config(text=format(slicedFrame_O.dataMag.z.poidsFort,"02X"))
        self.zOctet2.config(text=format(slicedFrame_O.dataMag.z.poidsFaible,"02X"))
        self.tempOctet1.config(text=format(slicedFrame_O.dataMag.temp.poidsFort,"02X"))
        self.tempOctet2.config(text=format(slicedFrame_O.dataMag.temp.poidsFaible,"02X"))
        self.etqTempDec.config(text= " : {} degres".format(slicedFrame_O.dataMag.temp.enDeg))
        self.etqXDec.config(text=" : {:.3f} mG".format(1000*slicedFrame_O.dataMag.x.enGauss) )
        self.etqYDec.config(text=" : {:.3f} mG".format(1000*slicedFrame_O.dataMag.y.enGauss) )
        self.etqZDec.config(text=" : {:.3f} mG".format(1000*slicedFrame_O.dataMag.z.enGauss) )
        self.etqDirDec.config(text= " : {}".format(slicedFrame_O.dataMag.direction ) )

def main():
    import os
    from constantes import GEN_PADDING, SIZE_OF_FRAME

    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    testedFrame= GuiFrameMag(root, 1, 1, GEN_PADDING)
    testedFrame.grid_propagate(0)
    import Trame as tr
    trame = tr.Trame( 'COM1', SIZE_OF_FRAME)
    trame.trameBrute =[ 0X52,0X44,0X43,0X0A,0X01,
    0X01,0X00,0X01,0X87,0XD7,0X00,0X00,0X0C,0X5A,0X00,0X01,
    0X02,0X00,0X06,0X18,0XD4,0X00,0X14,0X17,0X18,0X00,0X01,
    0X03,0X00,0X69,0X1E,0X1F,0X20,0X21,0X22,0X23,0X00,0X01,
    0X04,0XFE,0X23,0X00,0X3D,0X02,0X5F,0X00,0X21,0X00,0X01,
    0X05,0X2C,0X1C,0X13,0X74,0X00,0X00,0X02,0XF3,0X00,0X01,
    0X00,0X9C,0X58,0X09 ]
    trame.trameDecoupee.populate( trame.trameBrute )
    testedFrame.displayDataCapteur_O( trame.trameDecoupee )
    root.mainloop()


if __name__ == '__main__':
    main()