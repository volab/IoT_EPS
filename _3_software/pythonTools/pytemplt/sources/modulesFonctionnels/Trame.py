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

import constantes as CST

class Trame:
    """
    Classe qui englobe les données de la trame reçue
    """

    def __init__( self, serialPort, frameSize ):
        self.serialPort = serialPort
        # self.trameBrute = list()
        self.trameBrute = b'0'
        
        
        self.frameSize = frameSize
        self.timeout=False
        self.lastFrameOnError = False

    def recevoirTrame(self):
        if self.serialPort.in_waiting:
            line = self.serialPort.readline()
            self.trameBrute = line
            # print(line)

 
    def checkCS( self ):
        pass

    def pourAffichage(self, prefixe = '', separateur = ' '):
        trameChaine=""
        if self.trameBrute != b'0':
            # trameChaine = self.trameBrute.decode().rstrip('\n')
            trameChaine = self.trameBrute.decode()
        return trameChaine

    def pourEnregistrement( self, separateur = ',' ):
        """
        Méthode de mise en forme des données au format ascci avec unité et tout
        """
        trameChaine = ""
        # trameChaine = self.trameDecoupee.dataBaro.pourEnregistrement(separateur)
        # trameChaine += separateur + self.trameDecoupee.dataAlim.pourEnregistrement(separateur)
        return trameChaine
        


def main():
    import os
    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    trame = Trame( 'COM1', CST.SIZE_OF_FRAME )

    
    trame.trameBrute = [ ]
    print("longeur trame brute : {}".format( len(trame.trameBrute ) ) )
   


    print( trame.pourAffichage() )
    print("Trame brute pour affichage avec 0X et ,:")




    print("*"*80)
    print("Fin du test du module " + os.path.basename(__file__))


if __name__ == "__main__":
    main()
