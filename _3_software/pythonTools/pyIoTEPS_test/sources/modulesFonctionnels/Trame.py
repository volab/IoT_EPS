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
    # cptCommut = 0

    def __init__( self, serialPort ):
        self.serialPort = serialPort
        self.trameBrute = b'0'      
        self.cptCommut = 0
        

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
            if self.trameBrute.decode().find('<Volab in the loop > It is time for :') != -1:
                # Trame.cptCommut += 1
                self.cptCommut += 1
                self.serialPort.write(b'<M>\n')
                # print("Cpt commutation : {}".format(Trame.cptCommut) )
                # print("Cpt commutation : {}".format(self.cptCommut) )

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
