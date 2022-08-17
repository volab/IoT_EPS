
import tkinter as tk
from tkinter import ttk
import os
from time import strftime, localtime


class RecBtn( tk.Button ):

    def __init__( self, master, posRow, posCol, padding, recBasePath ):

        self.etiquetteBouton = tk.StringVar()
        self.etiquetteBouton.set("Enregistrer")

        
        # tk.Button.__init__( self, master,  text='LOG', command=self.logToggle, state = tk.DISABLED)
        tk.Button.__init__( self, master, textvariable = self.etiquetteBouton, 
            command=self.logToggle, state = tk.DISABLED, width = 11)
        self.grid( row=posRow,column=posCol, padx=padding, pady=padding)  #, sticky=tk.N
        self.grid_propagate(0)
       
        self.recordOn = False
        self.enregistrementEncours = False
        self.f = 0 # handler fichier de log
        self.recBasePath = recBasePath


    def logToggle( self ):
        if not(self.recordOn):
            self.recordOn = True
            self.etiquetteBouton.set("Arrêter")
            print('Enregistrement démarré')
            
        else:
            self.recordOn = False
            self.etiquetteBouton.set("Enregistrer")
            print('enregistrement arrêté')

    def logManager( self, trameStr ):
        if self.recordOn:
            if not(self.enregistrementEncours):
                print("ouverture fichier")
                # baseChemin = os.path.dirname(__file__)
                baseChemin = self.recBasePath
                prefixe = strftime("%y%m%d_%H%M" , localtime() )
                # print("Prefixe du fichier de log : " + prefixe)
                try:
                    
                    # fileName = prefixe + "raw.log"
                    # chemin =  os.path.join( baseChemin, "dataRaw")
                    # chemin =  os.path.join( chemin, fileName)
                    # self.f = open(chemin, 'w')
                    fileName = prefixe + ".log"
                    chemin =  os.path.join( baseChemin, "datum")
                    chemin =  os.path.join( chemin, fileName)
                    # print("===> Chemin : {}".format( chemin ) )
                    self.f = open(chemin, 'w', encoding="utf-8")                            
                    
                    self.enregistrementEncours = True
                except IOError as e:
                    print("I/O error({0}): {1}".format(e.errno, e.strerror) )
                    
            else:
                #enregistrementEncours
                if not(self.f.closed):
                    if trameStr != "":                        
                        self.f.write(trameStr)
                        # print("Ecriture fichier")
                    

        else:
            if self.enregistrementEncours:
                print("fermeture fichier")
                if not(self.f.closed):
                    self.f.close()
                    # print("fichier de log fermé")
                self.enregistrementEncours = False