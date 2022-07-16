"""
:Nom de fichier: TrameBaro.py
:Autheur: J.Soranzo
:version: 20210318
:Dépendences: 
:Licence: c-2020 groupe SAFRAN
:Project: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD
  
Défini les classe BaroDataValue, Pression, Temperature, DataBaro qui permettent de décoder Les
informations barométriques contenues dans les trames.
"""


import constantes as CST


class BaroDataValue:
    """
    Classe 
    """
    def __init__(self):
        self.v32bits = 0

    @property
    def signed32(self):
        valOctet = self.poidsFortHaut.to_bytes(1, 'little')\
            + self.poidsFortBas.to_bytes(1, 'little')\
            + self.poidsFaibleHaut.to_bytes(1, 'little')\
            + self.poidsFaibleBas.to_bytes(1, 'little')
        return int.from_bytes( valOctet, byteorder='big', signed=True)

    @property
    def poidsFortHaut(self):
        return ( self.v32bits & 0xFF000000 ) >> 24
    
    @property
    def poidsFortBas(self):
        return ( self.v32bits & 0xFF0000 ) >> 16

    @property
    def poidsFaibleHaut(self):
        return ( self.v32bits & 0xFF00 ) >> 8

    @property
    def poidsFaibleBas(self):
        return ( self.v32bits & 0xFF ) 

    @property
    def enHexa(self):
        return "0x{:08X}".format(self.v32bits )       

class Pression(BaroDataValue):
    def __init__(self):
        BaroDataValue.__init__(self)

    @property    
    def enMbar(self, fascii = True):
        '''Retourne la pression an ascii avec son unité'''
        return "{} mBar".format(self.signed32/100)


class Temperature(BaroDataValue):
    def __init__(self):
        BaroDataValue.__init__(self)

    @property
    def enDeg(self, ascii = True):
        '''Retourne la température an ascii avec son unité'''
        return "{}°C".format(self.signed32/100)


class DataBaro:
    """
        Pression : 4 octets, valeur conforme à la datasheet du MS5611 page 8 signed int32 100009 = 1000.09mbar
        Température : 4 octets, signed int 32 2007 = 20.07deg   
    """
    def __init__( self, dataBaseAd ):
        self.baseAd = dataBaseAd
        self.dataSize = CST.CAPT_STRUCT_FRAME_SIZE
        self.numC = 0
        self.err = 0
        self.status = 0
        self.pression = Pression()
        self.temp = Temperature()        

    def populate( self, trameBrute ):
        self.numC = trameBrute[ self.baseAd ]
        self.err = trameBrute[ self.baseAd + 9]
        self.stat = trameBrute[ self.baseAd + 10]
        self.pression.v32bits = ( trameBrute[ self.baseAd + 1 ] << 24 ) \
                        + ( trameBrute[ self.baseAd + 2 ] << 16 ) \
                        + ( trameBrute[ self.baseAd + 3 ] << 8 ) \
                        + ( trameBrute[ self.baseAd + 4 ] )  
        self.temp.v32bits = ( trameBrute[ self.baseAd + 5 ] << 24 ) \
                        + ( trameBrute[ self.baseAd + 6 ] << 16 ) \
                        + ( trameBrute[ self.baseAd + 7 ] << 8 ) \
                        + ( trameBrute[ self.baseAd + 8 ] ) 


    def pourEnregistrement( self, separateur = ',') :
        """
        :methode: pourEnregistrement( separateur )
        :parmam in: separateur, valeur par défaut "," de type chaine

        Cette méthode permet de préparer les données en format human readable en vue de les enregister.
        """

        chaine = ""
        chaine = "Capt_{}{}".format( self.numC, separateur)
        chaine = chaine + self.pression.enMbar + separateur
        chaine = chaine + self.temp.enDeg + separateur
        chaine = chaine + "0x{:02X}{}".format(self.err,separateur)
        chaine = chaine + "0x{:02X}".format(self.stat)
        return chaine

def main():
    print("*"*80)
    import os
    print('Test du programme :' + os.path.basename(__file__) )
    import Trame as tr
    trame = tr.Trame( 'COM1', CST.SIZE_OF_FRAME )
    # trame.trameBrute = [ 0X52,0X44,0X43,0X2,
    # 0X01,0X26,0X5A,0X34,0X58,0X00,0X00,0X07,0X8D,0X06,0X11,
    # 0X02,0X00,0X01,0X13,0XBF,0X00,0X3C,0X16,0X17,0X07,0X11,
    # 0X03,0X00,0X35,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    # 0X04,0XFF,0XD4,0X00,0XB7,0XFD,0X58,0XFF,0XE7,0X00,0X11,
    # 0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    # 0X01,0XCD,0X59,0X0D ]
    
    trame.trameBrute = [ 0X52,0X44,0X43,0X0A,0X02,
    0X01,0XFF,0X02,0X19,0X06,0X00,0X00,0X08,0XAC,0X06,0X11,
    0X02,0X00,0X01,0X12,0X66,0X00,0X3C,0X16,0X17,0X07,0X11,
    0X03,0X00,0X24,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    0X04,0XFF,0X6D,0X02,0X26,0XFC,0XF2,0XFF,0XD2,0X00,0X11,
    0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    0X01,0X26,0X09,0X0C ]
    trame.trameDecoupee.populate( trame.trameBrute )

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
    print("Pression Barométrique signed value modifiée attendue 1015.26 : {} mbar".\
        format(trame.trameDecoupee.dataBaro.pression.enMbar))
    print("Pour enreg: " + trame.trameDecoupee.dataBaro.pourEnregistrement() )


if __name__ == "__main__":
    main()