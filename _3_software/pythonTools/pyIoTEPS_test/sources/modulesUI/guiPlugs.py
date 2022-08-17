import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import os
from time import strftime, localtime


class GuiPlugs(tk.Frame):

    def __init__(self, master, genPad, color, **kwargs):
        self.GEN_PADDING = genPad
        tk.Frame.__init__(self, master ,  width=800 , relief=tk.GROOVE, bg=color, height=41, bd=5, class_='CframeOfContrl', **kwargs)
        self.grid(row=0, column=0, padx=self.GEN_PADDING, pady=self.GEN_PADDING)

        self.plugColor = tk.Label(self, width=10, anchor=tk.W, text="plug color")
        self.plugColor.grid(row=0, column=0, sticky=tk.E+tk.W+tk.N+tk.S, padx = 5, pady = 5)

        self.plugPhyState = tk.Label(self, width=15, anchor=tk.W, text="Physical state : ?")
        self.plugPhyState.grid(row=0, column=1, sticky=tk.E+tk.W+tk.N+tk.S, padx = 5, pady=5)

        self.plugMemState = tk.Label(self, width=15, anchor=tk.W, text="Memory state : ?")
        self.plugMemState.grid(row=0, column=2, sticky=tk.E+tk.W+tk.N+tk.S, padx = 5, pady=5)

        self.plugOnOffCount = tk.Label(self, width=17, anchor=tk.W, text="On Off Count : ?")
        self.plugOnOffCount.grid(row=0, column=3, sticky=tk.E+tk.W+tk.N+tk.S, padx = 5, pady=5)

        self.nextSwitch = tk.Label(self, width=26, anchor=tk.W, text="Next Switch : ?")
        self.nextSwitch.grid(row=0, column=4, sticky=tk.E+tk.W+tk.N+tk.S, padx = 5, pady=5)
    
    def updateDisplay( self, plug ):
        self.plugColor.config( text = plug.color )
        self.plugPhyState.config( text = "Physical state : {}".format( plug.statePhysical)  )
        self.plugMemState.config( text = "Memory state : {}".format( plug.stateInMemory)  )
        self.plugOnOffCount.config( text = "On Off Count : {}".format( plug.onOffCount)  )
        self.nextSwitch.config( text = "Next Switch : {}".format( plug.nextSwitch)  )
        

        if plug.stateCheckAllowed == 2:
            if (plug.stateInMemory != plug.statePhysical):
                date = strftime("%d/%m/%y %H:%M:%S" , localtime() )
                message ="Warning : wrong state of {}\n".format(plug.color)
                message += date
                messagebox.showerror(title = "Alerte", message = message)
            plug.stateCheckAllowed = 0
        if plug.color == "greenPlug" or plug.color == "yellowPlug":
            if plug.statePhysical== "ON" or plug.stateInMemory == "ON":
                date = strftime("%d/%m/%y %H:%M:%S" , localtime() )
                message ="Warning the {} should never be ON\n".format(plug.color)
                message += date
                messagebox.showerror(title = "Alerte", message = message)



import os
import sys
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0,os.path.dirname(SCRIPT_DIR))
from constantes import GEN_PADDING, FEN_HAUTEUR, ZONE_DE_TEXTE_HAUTEUR
import modulesFonctionnels.plugs as plugs



def fonctionPeriodique():
    global tours
    print("Alerte")
    print( "Tours dans la fonction : {}".format( tours ) )
    if tours == 1:
        tours += 1
    elif tours == 2:
        onePlug.onOffCount = 1258
        onePlug.color ="bluePlug"
        framePlug.config(background="blue")
        onePlug.stateInMemory = "ON"
        onePlug.statePhysical = "ON"
        tours +=1
    elif tours == 3:
        onePlug.onOffCount = 1259
        onePlug.color ="redPlug"
        framePlug.config(background="red")
        onePlug.stateInMemory = "OFF"
        onePlug.stateCheckAllowed = 1
        onePlug.statePhysical = "NR"  
        tours +=1 
    elif tours == 4:
        onePlug.onOffCount = 1260
        onePlug.color ="redPlug"
        onePlug.stateCheckAllowed = 2
        framePlug.config(background="red")
        onePlug.stateInMemory = "OFF"
        onePlug.statePhysical = "ON"  
        tours +=1
    elif tours == 5:   
        onePlug.onOffCount = 1261
        onePlug.color ="redPlug"

        framePlug.config(background="red")
        onePlug.stateInMemory = "OFF"
        onePlug.statePhysical = "ON"  
        tours +=1                  
    elif tours == 6:    
        onePlug.onOffCount = 0
        onePlug.color ="yellowPlug"
        framePlug.config(background="yellow")
        onePlug.stateInMemory = "OFF"
        onePlug.statePhysical = "OFF"  
        tours +=1
    elif tours == 7:
        onePlug.onOffCount = 36
        onePlug.color ="greenPlug"
        onePlug.stateInMemory = "ON"
        framePlug.config(background="green")
        onePlug.statePhysical = "ON"  
        tours +=1                     
    framePlug.updateDisplay( onePlug )
    
    if tours < 8 :
        root.after(2000, fonctionPeriodique)

def main():
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("ouvre un fenêtre TK inter")
    
    
    
    framePlug.grid_propagate(0)
    root.after(2000, fonctionPeriodique)
    root.mainloop()



if __name__ == '__main__':
    root = tk.Tk()
    onePlug = plugs.Plug("redPlug")
    framePlug = GuiPlugs(root, GEN_PADDING, "red")
    tours = 1
    main()