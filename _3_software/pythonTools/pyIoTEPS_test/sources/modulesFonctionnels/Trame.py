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
        #self.LIS3MDL_SCALE = "16g" # ne devait pas être ici à revoir 19/11/2020
        self.serialPort = serialPort
        # self.trameBrute = list()
        self.trameBrute = b'0'
        
        self.frameSize = frameSize
        # self.CAPT_STRUCT_FRAME_SIZE = CST.CAPT_STRUCT_FRAME_SIZE
        # self.BARO_FRAME_BASE_IDX = CST.BARO_FRAME_BASE_IDX
        # self.ALIM_FRAME_BASE_IDX = self.MAG_FRAME_BASE_IDX  + self.CAPT_STRUCT_FRAME_SIZE
        # self.trameDecoupee = TrameDecoupee( self.BARO_FRAME_BASE_IDX \
        #                                 , self.ALIM_FRAME_BASE_IDX \
        #                                 , self.frameSize )
        self.timeout=False
        self.lastFrameOnError = False

    def recevoirTrame(self):
        if self.serialPort.in_waiting:
            line = self.serialPort.readline()
            self.trameBrute = line
            # print(line.decode().rstrip('\n'))
            # self.trameBrute.append( line )
            # print(line.decode('utf').rstrip('\n'))

        # oneChar=0x00
        # # timeout=False

        # while (oneChar != b'R' and not self.timeout): #preambule
        #     oneChar=self.serialPort.read(size=1)
        #     if len(oneChar)==0:
        #         self.timeout=True

        # if self.timeout:
        #     return

 
        # cpt=0
        # if not self.timeout:
            # octet = ord( oneChar )
            # self.trameBrute.append(octet)
            # while( cpt < self.frameSize-3): 
            #     nbCar=self.serialPort.inWaiting()
            #     if nbCar!=0:
            #         octet=ord( self.serialPort.read(size=1) )
            #         self.trameBrute.append(octet)
            #         cpt +=1
            # self.lastFrameOnError = self.checkCS()
            # if not self.lastFrameOnError:
                
            #     self.trameDecoupee.populate( self.trameBrute  )

    def checkCS( self ):
        pass

    def pourAffichage(self, prefixe = '', separateur = ' '):
        trameChaine=""
        # for i in self.trameBrute:
        #     trameChaine += "{}{:02X}{}".format(prefixe,i,separateur)
        # trameChaine = trameChaine[:-len(separateur)]
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
