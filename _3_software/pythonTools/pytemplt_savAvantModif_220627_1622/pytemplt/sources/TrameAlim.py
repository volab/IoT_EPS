# """
#     :Nom de fichier: TrameAlim.py
#     :Autheur: J.Soranzo
#     :version: 20210318
#     :Dépendences: TrameMag
#     :Licence: (c) 2020 groupe SAFRAN
#     :Projet: AVOCETTE RDC Capteurs
#     :Société: SAFRAN Electronic & Defense
#     :Entité: PAD
"""
Défini les classe Tension, Temperature, DataAlim qui permettent de décoder Les
informations de servitudes contenues dans les trames RDC Capteurs.
"""

import constantes as CST
from TrameMag import DataValue


class Tension(DataValue):
    def __init__(self):
        DataValue.__init__(self)

    @property
    def enVolt(self):
        return "{} V".format( self.v16bits / 1000 )

class Temperature(DataValue):
    def __init__(self):
        DataValue.__init__(self)

    @property
    def enDeg(self):
        return "{} °C".format( self.signed16 / 100 )

class DataAlim:
    def __init__(self , dataBaseAd ):
        self.baseAd = dataBaseAd
        self.numC = 0
        self.err = 0
        self.status = 0
        self.Vin = Tension()
        self.V5Vtlm = Tension()
        self.V3v = Tension()
        self.temp = Temperature()

    def populate(self, trameBrute):
        self.numC = trameBrute[ self.baseAd ]
        self.err = trameBrute[ self.baseAd + 9]
        self.stat = trameBrute[ self.baseAd + 10]
        self.Vin.v16bits = ( trameBrute[ self.baseAd + 1 ] << 8 ) \
                + trameBrute[ self.baseAd + 2 ]
        self.V5Vtlm.v16bits = ( trameBrute[ self.baseAd + 3 ] << 8 ) \
                + trameBrute[ self.baseAd + 4 ]
        self.V3v.v16bits = ( trameBrute[ self.baseAd + 5 ] << 8 ) \
                + trameBrute[ self.baseAd + 6 ]
        self.temp.v16bits = ( trameBrute[ self.baseAd + 7 ] << 8 ) \
                + trameBrute[ self.baseAd + 8 ]

    def pourEnregistrement( self, separateur = ',') :
        """
        :methode: pourEnregistrement( separateur )
        :parmam in: separateur, valeur par défaut "," de type chaine

        Cette méthode permet de préparer les données en format human readable en vue de les enregister.
        """

        chaine = ""
        chaine = "Capt_{}{}".format( self.numC, separateur)
        chaine = chaine + self.Vin.enVolt + separateur
        chaine = chaine + self.V5Vtlm.enVolt + separateur
        chaine = chaine + self.temp.enDeg + separateur        
        chaine = chaine + "0x{:02X}{}".format(self.err,separateur)
        chaine = chaine + "0x{:02X}".format(self.stat)
        return chaine

def fTest( trame ):
    import os
    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)

    print("Alimentations numéro de capteur : {}".\
        format( trame.trameDecoupee.dataAlim.numC ) )
    print("Alimentations Température hexa {}".\
        format( trame.trameDecoupee.dataAlim.temp.enHexa ) )
    print("Alimentations Température en degré : {}".\
        format(trame.trameDecoupee.dataAlim.temp.enDeg))
    print("Alimentations Vin en hexa : {}" \
        .format( trame.trameDecoupee.dataAlim.Vin.enHexa ))
    print("Alimentations Vin en Volt : {}" \
        .format( trame.trameDecoupee.dataAlim.Vin.enVolt  ))
    # print('Alimentations en Pascal : {}' \
    #     .format( trame.trameDecoupee.dataAlim.pression.enPascal ))
    # trame.trameDecoupee.dataAlim.pression.v16bits = 0XFFFF
    # print( "Pitot Pression différentielle à -1 : {} " \
    #     .format( trame.trameDecoupee.dataAlim.pression.signed16 ) )
    # print('Pression différentielle Pitot en Pascal avec -1 : {}' \
    #     .format( trame.trameDecoupee.dataAlim.pression.enPascal ))
    print("for Rec: "+\
        trame.trameDecoupee.dataAlim.pourEnregistrement() )

    print("Fin du test du module " + os.path.basename(__file__))

def main():

    import Trame as tr   
    trame = tr.Trame( 'COM1', CST.SIZE_OF_FRAME )
    # trame.trameBrute = [ 0X52,0X44,0X43,0X2,
    # 0X01,0X26,0X5A,0X34,0X58,0X00,0X00,0X07,0X8D,0X06,0X11,
    # 0X02,0X00,0X01,0X13,0XBF,0X00,0X3C,0X16,0X17,0X07,0X11,
    # 0X03,0X00,0X35,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    # 0X04,0XFF,0XD4,0X00,0XB7,0XFD,0X58,0XFF,0XE7,0X00,0X11,
    # 0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    # 0X01,0XCD,0X59,0X0D ]
    
    trame.trameBrute = [ 0X52,0X44,0X43,0X01,0X02,
    0X01,0XFF,0X02,0X19,0X06,0X00,0X00,0X08,0XAC,0X06,0X11,
    0X02,0X00,0X01,0X12,0X66,0X00,0X3C,0X16,0X17,0X07,0X11,
    0X03,0X00,0X24,0X1D,0X1E,0X1F,0X20,0X21,0X22,0X00,0X11,
    0X04,0XFF,0X6D,0X02,0X26,0XFC,0XF2,0XFF,0XD2,0X00,0X11,
    0X05,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X08,0X11,
    0X01,0X26,0X09,0X0C ]
    trame.trameDecoupee.populate( trame.trameBrute )
    fTest( trame )
    

if __name__ == '__main__':
    main()
    