"""
:Nom de fichier: Trame.py
:Autheur: J.Soranzo
:version: 20210318
:Dépendences: TrameBaro, TrameAlim, TrameMag, TramePitot, TrameTlm
:Licence: c-2020 VoRoBoTics
:Projet: AVOCETTE RDC Capteurs
:Société: VoRoBoTics
:Entité: VoLAB
  
Défini les classes TrameDecoupee et Trame
"""
import serial



import os
import sys
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0,os.path.dirname(SCRIPT_DIR))
import constantes as CST
import modulesFonctionnels.plugs as plugs

class Trame:
    """
    Classe qui englobe les données de la trame reçue
    """
    # cptCommut = 0

    def __init__( self, serialPort ):
        self.serialPort = serialPort
        self.trameBrute = b'0'      
        self.cptCommut = 0
        self.redPlug = plugs.Plug('redPlug')
        self.greenPlug = plugs.Plug('greenPlug')
        self.bluePlug = plugs.Plug('bluePlug')
        self.yellowPlug = plugs.Plug('yellowPlug')
        self.lastPlugSwitched = plugs.Plug('not yet seen')

    def recevoirTrame(self):
        if self.serialPort.in_waiting:
            line = self.serialPort.readline()
            self.trameBrute = line

    def checkCS( self ):
        pass

    def pourAffichage(self, prefixe = '', separateur = ' '):
        trameChaine=""
        if self.trameBrute != b'0':
            trameChaine = self.trameBrute.decode()
        return trameChaine

    def pourEnregistrement( self ):
        """
        Méthode de mise en forme des données au format ascci avec unité et tout
        """
        trameChaine = ""
        if self.trameBrute != b'0':
            trameChaine = self.trameBrute.decode().rstrip('\n')
        return trameChaine
        
    def analyzeTrame(self):
        if self.trameBrute != b'0':
            trameTxt = self.trameBrute.decode()

            if trameTxt.find('<Volab in the loop > It is time for :') != -1:
                # Trame.cptCommut += 1
                self.cptCommut += 1 
                switchedPlugColor = trameTxt[37:].strip()
                print('switched color : {}'.format(switchedPlugColor))
                if switchedPlugColor == 'redPlug':
                    self.lastPlugSwitched = self.redPlug
                if switchedPlugColor == 'greenPlug':
                    self.lastPlugSwitched = self.greenPlug
                if switchedPlugColor == 'bluePlug':
                    self.lastPlugSwitched = self.bluePlug
                if switchedPlugColor == 'yellowPlug':
                    self.lastPlugSwitched = self.yellowPlug               
                print('last switched plug color : {}'.format(self.lastPlugSwitched.color))

                try:
                    self.serialPort.write(b'<M>\n')
                    self.serialPort.write(b'<N>\n')
                except serial.SerialTimeoutException:
                    print("ecriture port serie impossible")
                except serial.SerialException:
                    print("Port non ouvert")
                # print("Cpt commutation : {}".format(Trame.cptCommut) )
                # print("Cpt commutation : {}".format(self.cptCommut) )

            if trameTxt.find('<Volab updateOutputs > Nouvelle valeur du compteur ON/OFF: ') != -1:
                #             012345678901234567890123456789012345678901234567890123456789
                after = trameTxt.find(' de : ')
                self.lastPlugSwitched.onOffCount = trameTxt[58:after].strip()              

            if trameTxt.find('<Volab CEpsStrTime::computeNextTime > future = ') != -1:
                #             012345678901234567890123456789012345678901234567890123456789
                dateFull = trameTxt[46:].strip()
                remover = dateFull.find(' ')
                dateFull = dateFull[remover:]
                self.lastPlugSwitched.nextSwitch = dateFull             


            # memory state capture
            if trameTxt.find('Red plug : ') != -1:
                self.redPlug.stateInMemory = trameTxt[11:].strip()
            if trameTxt.find('Green plug : ') != -1:
                self.greenPlug.stateInMemory = trameTxt[13:].strip()            
            if trameTxt.find('Bleue plug : ') != -1:
                self.bluePlug.stateInMemory = trameTxt[13:].strip()
            if trameTxt.find('Yellow plug : ') != -1:
                self.yellowPlug.stateInMemory = trameTxt[14:].strip()

            #Physical state capture
            if trameTxt.find('Analog Red value : ') != -1:
                self.redPlug.statePhysical = trameTxt[18:].strip()
            if trameTxt.find('Analog Green value : ') != -1:
                self.greenPlug.statePhysical = trameTxt[20:].strip()
            if trameTxt.find('Analog Bleue value : ') != -1:
                self.bluePlug.statePhysical = trameTxt[20:].strip()
            if trameTxt.find('Analog Yellow value : ') != -1:
                self.yellowPlug.statePhysical = trameTxt[21:].strip()

def main():
    import os

    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    # trame = Trame( 'COM1' )
    #Use com0com to test (on Windows)
    serialPort = serial.Serial( 'COM22', CST.BAUD_RATE )


    trame = Trame( serialPort )
    print( "Red plug color : {}".format( trame.redPlug.color))
    
    trame.trameBrute = b'<Volab in the loop > It is time for : redPlug'
    print("longeur trame brute : {}".format( len(trame.trameBrute ) ) )
    trame.analyzeTrame()
    print("Compteur de commutations : {}".format(trame.cptCommut))
    assert (trame.cptCommut == 1), "erreur"
    trame.analyzeTrame()
    print("Compteur de commutations : {}".format(trame.cptCommut))
    assert (trame.cptCommut == 2), "erreur"


    trame.trameBrute = b'Red plug : ON'
    trame.analyzeTrame()
    print('Commutation red plug mem state = {}'.format(trame.redPlug.stateInMemory))
    trame.trameBrute = b'Analog Red value : OFF'
    trame.analyzeTrame()
    print('Commutation red plug phys state = {}'.format(trame.redPlug.statePhysical))

    print( trame.pourAffichage() )
    print("Trame brute pour affichage avec 0X et ,:")




    print("*"*80)
    print("Fin du test du module " + os.path.basename(__file__))


if __name__ == "__main__":
    main()
