"""
:Nom de ficier: GuiFrameControles.py
:Autheur: J.Soranzo
:version: 2020210
:Dépendences: tkinter et pySerial
:Licence: c-2020 VoRoBoTics
:Projet: AVOCETTE RDC Capteurs
:Société: VoRoBoTics
:Entité: VoLAB
"""
import tkinter as tk
from tkinter import ttk
import serial
import serial.tools.list_ports
from tkinter import messagebox

# import GuiFrameConfig as FConfig
# import GuiFrameRecord as Frec
# import GuiFrameCalMag as FCalMag


import os
import sys
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0,os.path.dirname(SCRIPT_DIR))

from constantes import BAUD_RATE
# import constantes
import modulesUI.guiRecBtn as RecBtn

class CFrameControles(tk.Frame):
    '''
    Classe qui porte la partie des contrôles de l'application de test RDC capteurs.

    Classe hérité de tkinter (donc dont le fonctionnement est directement lié à tk inter)

    Elle instancie GUIFrameConfig et GuiFrameRecord

    :param: master handler de la fenêtre parent
    :param: genPad padding général entre les éléments graphiques
    '''
    def __init__(self, master, genPad, fenHeight,**kwargs):
    
        FEN_HAUTEUR = fenHeight #pour pas tout ré-écrire
        GEN_PADDING = genPad #pour pas tout ré-écrire
        
        
        

        self.serialPort=serial.Serial()
        self.serialPort.baudrate = BAUD_RATE
        self.serialPort.timeout=0.2
        self.serialPortIsOpen = False #serialPort.is_open
        self.portCom = '' 
        
        FrameLargeur = 300
        tk.Frame.__init__(self, master, width=FrameLargeur, height=FEN_HAUTEUR, relief=tk.RIDGE, \
                            bg="white", bd=5, class_='CFrameContrles' ,**kwargs) 
        self.grid(row=1, column=1, padx=GEN_PADDING, pady=GEN_PADDING, sticky = tk.N+tk.S)
        self.master = master
        
        widgetsVertPos = 0
        #********************************************************************************
        # Premiere ligne de controle
        self.etqPortChoisi=tk.Label(self,text='Port COM:')
        self.etqPortChoisi.grid(row=widgetsVertPos, padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.W)
        self.etqPortChoisi.config( bg='yellow') 

        self.etqPortOpen=tk.Label(self,text="compteur", bg='blue', anchor=tk.E)
                                           # 123456789_123456789_123456789_
        self.etqPortOpen.grid(row=widgetsVertPos,column=3, padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.E)

        widgetsVertPos += 1
        #********************************************************************************
        # Premier separateur
        self.separateur( widgetsVertPos )


        widgetsVertPos += 1
        #********************************************************************************
        # Deuxième ligne de controle: liste port com et btns OPEN...        
        comListCol=0
        self.comList=ttk.Combobox(self, width=7)
        self.comList.grid(row=widgetsVertPos, column=comListCol, padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.W)

        #********************************************************************************
        # Btn all Port COMs info
        self.comInfoBtn = tk.Button(self, text="all COMs Info", state=tk.DISABLED, command=self.comInfo)
        self.comInfoBtn.grid(row=widgetsVertPos, column=comListCol+1, padx=GEN_PADDING,
                                pady=GEN_PADDING, sticky=tk.E)

        #********************************************************************************
        # Btn Port COM open
        self.comOpenBtn= tk.Button(self, text="OPEN", state=tk.DISABLED, command=self.openPortCom)
        self.comOpenBtn.grid(row=widgetsVertPos, column=comListCol+2, padx=GEN_PADDING,
                                pady=GEN_PADDING, sticky=tk.E)
        self.comOpenBtn.config(state=tk.DISABLED)

        widgetsVertPos += 1
        #********************************************************************************
        # Deuxieme separateur        
        self.separateur( widgetsVertPos )

        widgetsVertPos += 1
        #********************************************************************************
        # Btn quit
        self.quitButton = tk.Button(self, text="Quit", command=self.master.quit)
        self.quitButton.grid(row=widgetsVertPos,column=1, 
                    padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.N)


        #********************************************************************************
        # Btn Port COM Close
        self.comCloseBtn = tk.Button(self, text="Close com", command=self.comClose)
        self.comCloseBtn.grid(row=widgetsVertPos,column=0, 
                    padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.N)

        # self.btnCalMag = tk.Button(self, text="Cal MAG", state=tk.DISABLED, command=self.calMagneto)
        # self.btnCalMag.grid(row=widgetsVertPos, column=2, padx=GEN_PADDING,
        #                     pady=GEN_PADDING, sticky=tk.W)           

        widgetsVertPos += 1
        #********************************************************************************
        # Troisième separateur        
        self.separateur( widgetsVertPos )

        widgetsVertPos += 1
        #********************************************************************************
        self.helpBtn = tk.Button( self, text='Help', command=self.sendHelpCmd, state = tk.DISABLED )
        self.helpBtn.grid(row=widgetsVertPos,column=0, 
                    padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.N)
        self.ds3231dateBtn = tk.Button( self, text='CHECK CLK', command=self.sendCheckClkCmd, state = tk.DISABLED )
        self.ds3231dateBtn.grid(row=widgetsVertPos,column=1, 
                    padx=GEN_PADDING, pady=GEN_PADDING, sticky=tk.N)
        # self.logBtn = RecBtn( self, text='CHECK CLK', command=self.logCmd, state = tk.DISABLED )
        self.logBtn = RecBtn.RecBtn( self,  widgetsVertPos, 2, GEN_PADDING)
               

        widgetsVertPos += 1
        #********************************************************************************
        # Quatrième separateur        
        # self.separateur( widgetsVertPos )
        # widgetsVertPos += 1
        #********************************************************************************


        # widgetsVertPos += 1
        #********************************************************************************
        # Cinquième separateur : Calibration magnétomètre       
        # self.separateur( widgetsVertPos )
        # widgetsVertPos += 1
        #********************************************************************************


        # self.listeDesPortsSerie=serial_ports()
        listeDesPortsSerie=serial.tools.list_ports.comports()
        listeDesPortsSerie=[i.device for i in listeDesPortsSerie]
        print(listeDesPortsSerie)
        #listeDesPortsSerie=[] # for debug
        if len(listeDesPortsSerie) == 0:
            msg = "Pas de port serie trouve ! (t'aurais pas oublie de brancher le cable !)"
            messagebox.showerror(title='Pb Serie', message=msg)
        else:
            self.comList.config(values=listeDesPortsSerie)
            self.comOpenBtn.config(state=tk.NORMAL) 
            self.comInfoBtn.config(state=tk.NORMAL)  

    def separateur(self, vertPos):
        from constantes import GEN_PADDING
        ttk.Separator(self, orient=tk.HORIZONTAL).grid(row=vertPos, column=0, 
                    columnspan= 5, sticky=tk.E+tk.W, pady=GEN_PADDING)   

    #********************************************************************************
    # Méthodes handler de boutons   
    #********************************************************************************

    def comInfo(self):
        '''Fonction associee au bouton COM INFO'''	
        msg=""
        # serial.tools.list_ports.comports
        # The function returns an iterable that yields tuples of three strings:
        # 
        # port name as it can be passed to serial.Serial or serial.serial_for_url()
        # description in human readable form
        # sort of hardware ID. E.g. may contain VID:PID of USB-serial adapters.
        for port in serial.tools.list_ports.comports():
            msg += "".join(str(port)) # transforme le tuple en chaine
            msg +="\n"
        messagebox.showinfo(title='Liste port(s) serie', message=msg)

    def openPortCom(self):
        print("Open port com")

        ''' Ouverture du canal de communication
        Fonction associee au bouton OPEN'''
        # global serialPort,serialPortIsOpen, portCom
        if self.comList.current()==-1:
            msg="Choisir un port"
            print("Etat du port serie : {}".format(self.serialPort.is_open) )
            messagebox.showinfo(title='Attention', message=msg)
        else:
            self.portCom = self.comList['values'][self.comList.current()]
            self.serialPort.port=self.comList['values'][self.comList.current()]
            # msgZone.delete('1.0',tk.END)
            # msgZone.insert('1.0', "Port choisi : "+ portCom)

            try:	
                self.serialPort.open()
            except serial.SerialException:
                print("Erreur port serie (t'aurais pas oublie de brancher le cable !)")
                # sys.exit()
            else:
                self.serialPortIsOpen=True
                self.etqPortOpen.config(text=self.portCom)
                self.comCloseBtn.config( state = tk.ACTIVE )
                self.helpBtn.config( state = tk.ACTIVE )
                self.ds3231dateBtn.config( state = tk.ACTIVE )
                self.logBtn.config( state = tk.ACTIVE )
                self.comOpenBtn.config( state = tk.DISABLED)


    def comClose(self):
        if self.serialPort.is_open:
            self.serialPort.close()
            self.serialPortIsOpen = False
            self.comOpenBtn.config( state = tk.ACTIVE)
            self.comCloseBtn.config( state = tk.DISABLED ) 
            self.helpBtn.config( state = tk.DISABLED )
            self.logBtn.config( state = tk.DISABLED )
            self.ds3231dateBtn.config( state = tk.DISABLED )
            print("COM close")

    def sendHelpCmd(self):
        self.serialPort.write(b'<H>\n')

    def sendCheckClkCmd(self):
        self.serialPort.write(b'<C>\n')

    def logCmd(self):
        pass




import os
from constantes import GEN_PADDING, FEN_HAUTEUR


def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )

    print("ouvre un fenêtre TK inter")
    root = tk.Tk()
    frame = CFrameControles(root, GEN_PADDING, FEN_HAUTEUR)
    frame.grid_propagate(0)
    root.mainloop()

if __name__ == '__main__':
    main()