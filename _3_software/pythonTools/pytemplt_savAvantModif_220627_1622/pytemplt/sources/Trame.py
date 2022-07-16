"""
:Nom de fichier: Trame.py
:Autheur: J.Soranzo
:version: 20210318
:Dépendences: TrameBaro, TrameAlim, TrameMag, TramePitot, TrameTlm
:Licence: c-2020 groupe SAFRAN
:Projet: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD
  
Défini les classes TrameDecoupee et Trame
"""
import serial

import constantes as CST
import TrameMag as trMag
import TrameBaro as trBaro
import TramePitot as trPitot
import TrameTlm as trTlm
import TrameAlim as trAlim


class TrameDecoupee:
    """
    Classe qui contient le contenu de la trame séparée dans les différentes intances des capteurs
    Une instance par capteur.
    """
    def __init__(self, dataBaroBaseAd, dataMagBaseAd, dataPitotBaseAd, dataTlmBaseAd, \
                    dataAlimBaseAd, size ):
        self.frameSize = size

        self.dataBaro = trBaro.DataBaro( dataBaroBaseAd )
        self.dataMag = trMag.DataMag( dataMagBaseAd )
        self.dataPitot = trPitot.DataPitot ( dataPitotBaseAd )
        self.dataTlm = trTlm.DataTlm( dataTlmBaseAd )
        self.dataAlim = trAlim.DataAlim( dataAlimBaseAd )

    def populate( self, trame ):
        """
        Cette méthode permet à partir de la trame brute de renseigner les différents contenu de 
        chaque capteur et pour cela elle fait appelle à son homologue dans chaque classe de 
        chaque capteur.
        """
        self.dataBaro.populate( trame )
        self.dataMag.populate( trame )
        self.dataPitot.populate( trame )
        self.dataTlm.populate( trame )
        self.dataAlim.populate( trame )


class Trame:
    """
    Classe qui englobe les données de la trame reçue
    """

    def __init__( self, serialPort, frameSize ):
        self.LIS3MDL_SCALE = "16g" # ne devait pas être ici à revoir 19/11/2020
        self.serialPort = serialPort
        self.trameBrute = list()
        
        
        self.frameSize = frameSize
        self.CAPT_STRUCT_FRAME_SIZE = CST.CAPT_STRUCT_FRAME_SIZE
        self.BARO_FRAME_BASE_IDX = CST.BARO_FRAME_BASE_IDX
        self.PITOT_FRAME_BASE_IDX = self.BARO_FRAME_BASE_IDX + self.CAPT_STRUCT_FRAME_SIZE
        self.TLM_FRAME_BASE_IDX =  self.PITOT_FRAME_BASE_IDX + self.CAPT_STRUCT_FRAME_SIZE
        self.MAG_FRAME_BASE_IDX =  self.TLM_FRAME_BASE_IDX  + self.CAPT_STRUCT_FRAME_SIZE
        self.ALIM_FRAME_BASE_IDX = self.MAG_FRAME_BASE_IDX  + self.CAPT_STRUCT_FRAME_SIZE
        self.trameDecoupee = TrameDecoupee( self.BARO_FRAME_BASE_IDX \
                                        , self.MAG_FRAME_BASE_IDX \
                                        , self.PITOT_FRAME_BASE_IDX \
                                        , self.TLM_FRAME_BASE_IDX \
                                        , self.ALIM_FRAME_BASE_IDX \
                                        , self.frameSize )
        self.timeout=False
        self.lastFrameOnError = False

    def recevoirTrame(self):

        oneChar=0x00
        # timeout=False

        while (oneChar != b'R' and not self.timeout): #preambule RDC
            oneChar=self.serialPort.read(size=1)
            if len(oneChar)==0:
                self.timeout=True

        if self.timeout:
            return

        if self.serialPort.read(size=1) != b'D':
            self.lastFrameOnError = True
            return 
        if self.serialPort.read(size=1) != b'C':
            self.lastFrameOnError = True
            return
        self.trameBrute.extend([0x52,0x44,0x43])
        #frame detected, read the frame
        cpt=0
        if not self.timeout:
            # octet = ord( oneChar )
            # self.trameBrute.append(octet)
            while( cpt < self.frameSize-3): #RDC déjà passés
                nbCar=self.serialPort.inWaiting()
                if nbCar!=0:
                    octet=ord( self.serialPort.read(size=1) )
                    self.trameBrute.append(octet)
                    cpt +=1
            self.lastFrameOnError = self.checkCS()
            if not self.lastFrameOnError:
                
                self.trameDecoupee.populate( self.trameBrute  )

    def checkCS( self ):
        trameCsLow = self.trameBrute[ self.frameSize - 2 ]
        trameCsHigh = self.trameBrute[ self.frameSize - 1 ]
        trameCs =  ( trameCsHigh << 8 ) + trameCsLow   
        calculatedCs = 0
        trameSansCs = self.trameBrute[ : self.frameSize - 2 ]
        for i in trameSansCs:
            calculatedCs += i
        return ( calculatedCs != trameCs )

    def pourAffichage(self, prefixe = '', separateur = ' '):
        trameChaine=""
        for i in self.trameBrute:
            trameChaine += "{}{:02X}{}".format(prefixe,i,separateur)
        trameChaine = trameChaine[:-len(separateur)]
        return trameChaine

    def pourEnregistrement( self, separateur = ',' ):
        """
        Méthode de mise en forme des données au format ascci avec unité et tout
        """
        trameChaine = ""
        trameChaine = self.trameDecoupee.dataBaro.pourEnregistrement(separateur)
        trameChaine += separateur + self.trameDecoupee.dataPitot.pourEnregistrement(separateur)
        trameChaine += separateur + self.trameDecoupee.dataTlm.pourEnregistrement(separateur)
        trameChaine += separateur + self.trameDecoupee.dataMag.pourEnregistrement(separateur)
        trameChaine += separateur + self.trameDecoupee.dataAlim.pourEnregistrement(separateur)
        return trameChaine
        


def main():
    import os
    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    trame = Trame( 'COM1', CST.SIZE_OF_FRAME )
    # trame.trameBrute = [ 0X52,0X44,0X43,0X2,
    # 0X01,0X26,0X5A,0X34,0X58,0X00,0X00,0X07,0X8D,0X06,0X11,
    # 0X02,0X00,0X01,0X13,0XBF,0X00,0X3C,0X16,0X17,0X07,0X11,
    # 0X03,0X00,0X35,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    # 0X04,0XFF,0XD4,0X00,0XB7,0XFD,0X58,0XFF,0XE7,0X00,0X11,
    # 0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    # 0X01,0XCD,0X59,0X0D ]
    
    trame.trameBrute = [ 0X52,0X44,0X43,0X02,0X0A,
    0X01,0XFF,0X02,0X19,0X06,0X00,0X00,0X08,0XAC,0X06,0X11,
    0X02,0X00,0X01,0X12,0X66,0X00,0X3C,0X16,0X17,0X07,0X11,
    0X03,0X00,0X24,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    0X04,0XFF,0X6D,0X02,0X26,0XFC,0XF2,0XFF,0XD2,0X00,0X11,
    0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    0X01,0X26,0X09,0X0C ]
    print("longeur trame brute : {}".format( len(trame.trameBrute ) ) )
    trame.trameDecoupee.populate( trame.trameBrute )
    print ("Verification checksum : {}".format( not(trame.checkCS()) ) )
    print("Trame brute pour affichage:")
    print( trame.pourAffichage() )
    print("Trame brute pour affichage avec 0X et ,:")
    print( trame.pourAffichage( prefixe="0X", separateur=",") )
    print("Corruption de la cs")
    trame.trameBrute[ CST.SIZE_OF_FRAME -1 ] = 0X0E
    print ("Verification checksum corrompue: {}".format( not(trame.checkCS()) ) )
    print("*"*80)
    print("Magnéto numéro de capteur : {}".\
        format( trame.trameDecoupee.dataMag.numC ) )
    print("Température magnéto hexa {:04X}".\
        format( trame.trameDecoupee.dataMag.temp.v16bits ) )
    print("Température magnétomètre en degré : {}°C".\
        format( trame.trameDecoupee.dataMag.temp.enDeg ) )
    print("*"*80)
    print("Baromètre numéro de capteur : {}".\
        format( trame.trameDecoupee.dataBaro.numC ) )
    print("Température Barométrique hexa {:08X}".\
        format( trame.trameDecoupee.dataBaro.temp.v32bits ) )
    print("Température Barométrique en Hexa octet par octet 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}".\
        format(trame.trameDecoupee.dataBaro.temp.poidsFortHaut \
              ,trame.trameDecoupee.dataBaro.temp.poidsFortBas \
              ,trame.trameDecoupee.dataBaro.temp.poidsFaibleHaut \
              ,trame.trameDecoupee.dataBaro.temp.poidsFaibleBas    ))
    print("Température Barométrique signed value : {}".\
        format(trame.trameDecoupee.dataBaro.temp.enDeg))
    trame.trameDecoupee.dataBaro.temp.v32bits = 0XFFFFFA00
    print("Température Barométrique signed value modifiée attendue -1536 : {}".\
        format(trame.trameDecoupee.dataBaro.temp.signed32))
    print("Pression Barométrique hexa {:08X}".\
        format( trame.trameDecoupee.dataBaro.pression.v32bits ) )
    print("Pression Barométrique signed value : {}".\
        format(trame.trameDecoupee.dataBaro.pression.signed32/100))
    print("Pression Barométrique : {}".\
        format(trame.trameDecoupee.dataBaro.pression.enMbar ))
    trame.trameDecoupee.dataBaro.pression.v32bits = 0X18C96
    #1015.26 hPa = 1015.26 mbar en hexa = 018C96        
    print("Pression Barométrique signed value modifiée attendue 1015.26 : {}".\
        format(trame.trameDecoupee.dataBaro.pression.enMbar))
    print("*"*80)
    trPitot.fTest( trame )
    print("*"*80)
    trTlm.fTest( trame )
    print("*"*80)
    trAlim.fTest( trame )
    print("forRecord : " +\
        trame.pourEnregistrement() )

    print("*"*80)
    print("Fin du test du module " + os.path.basename(__file__))


if __name__ == "__main__":
    main()
