"""
:Nom de fichier: TramePitot.py
:Autheur: J.Soranzo
:version: 20210318
:Dépendences: TrameMag
:Licence: c-2020 groupe SAFRAN
:Projet: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD

Défini les classe PressionDiff, Temperature, DataPitot qui permettent de décoder Les
informations de pression différentielles contenues dans les trames RDC Capteurs.
"""

import constantes as CST
from TrameMag import DataValue


class PressionDiff(DataValue):
    def __init__(self):
        DataValue.__init__(self)
        self.scale = DataValue()

    @property
    def enPascal(self):
        return "{:.3f} Pa".format( float(self.signed16)/float(self.scale.signed16) )

    @property
    def enms(self):
        Dp = abs( float(self.signed16)/float(self.scale.signed16) )
        vitesse = pow( ((2.0*Dp)/1.225), 0.5 )
        return "{:.3f} m/s".format( vitesse )

class Temperature(DataValue):
    def __init__(self):
        DataValue.__init__(self)

    @property
    def enDeg( self ):
        '''Retourne la températue directement en ascii avec l'unité'''
        return "{}°C".format( self.signed16/200.0 )



class DataPitot:
    def __init__(self , dataBaseAd ):
        self.baseAd = dataBaseAd
        self.numC = 0
        self.err = 0
        self.status = 0
        self.pression = PressionDiff()
        self.temp = Temperature()
        

    def populate(self, trameBrute):
        self.numC = trameBrute[ self.baseAd ]
        self.err = trameBrute[ self.baseAd + 9]
        self.stat = trameBrute[ self.baseAd + 10]
        self.pression.v16bits = ( trameBrute[ self.baseAd + 1 ] << 8 ) \
                + trameBrute[ self.baseAd + 2 ]
        self.temp.v16bits = ( trameBrute[ self.baseAd + 3 ] << 8 ) \
                + trameBrute[ self.baseAd + 4 ]
        self.pression.scale.v16bits = ( trameBrute[ self.baseAd + 5 ] << 8 ) \
                + trameBrute[ self.baseAd + 6 ]

    def pourEnregistrement( self, separateur = ',') :
        """
        :methode: pourEnregistrement( separateur )
        :parmam in: separateur, valeur par défaut "," de type chaine

        Cette méthode permet de préparer les données en format human readable en vue de les enregister.
        """

        chaine = ""
        chaine = "Capt_{}{}".format( self.numC, separateur)
        chaine = chaine + self.pression.enPascal + separateur
        chaine = chaine + self.temp.enDeg + separateur
        chaine = chaine + self.pression.enms + separateur        
        chaine = chaine + "0x{:02X}{}".format(self.err,separateur)
        chaine = chaine + "0x{:02X}".format(self.stat)
        return chaine

def fTest( trame ):
    import os
    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    print("Pitot numéro de capteur : {}".\
        format( trame.trameDecoupee.dataPitot.numC ) )
    print("Température Pitot hexa {}".\
        format( trame.trameDecoupee.dataPitot.temp.enHexa ) )
    print("Température Pitot signed value : {}".\
        format(trame.trameDecoupee.dataPitot.temp.enDeg))
    print("Pression différentielle Pitot en hexa : 0x{:04X}" \
        .format( trame.trameDecoupee.dataPitot.pression.v16bits ))
    print("Pitot scale factor en hexa : 0x{:04X}" \
        .format( trame.trameDecoupee.dataPitot.pression.scale.v16bits  ))
    print('Pression différentielle Pitot en Pascal : {}' \
        .format( trame.trameDecoupee.dataPitot.pression.enPascal ))
    print('Vitesse calculée : {}' \
        .format( trame.trameDecoupee.dataPitot.pression.enms ))
    trame.trameDecoupee.dataPitot.pression.v16bits = 0XFF00
    print( "Pitot Pression différentielle à -1 : {} " \
        .format( trame.trameDecoupee.dataPitot.pression.signed16 ) )
    print('Pression différentielle Pitot en Pascal avec -1 : {}' \
        .format( trame.trameDecoupee.dataPitot.pression.enPascal ))
    print('Vitesse calculée : {}' \
        .format( trame.trameDecoupee.dataPitot.pression.enms ))
    print("Pour enreg: " + trame.trameDecoupee.dataPitot.pourEnregistrement() )    
    print("Fin du test du module " + os.path.basename(__file__))
    print("*"*80)

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
    
    trame.trameBrute =[ 0X52,0X44,0X43,0X0A,0X01,
    0X01,0X00,0X01,0X87,0XD7,0X00,0X00,0X0C,0X5A,0X00,0X01,
    0X02,0X00,0X06,0X18,0XD4,0X00,0X14,0X17,0X18,0X00,0X01,
    0X03,0X00,0X69,0X1E,0X1F,0X20,0X21,0X22,0X23,0X00,0X01,
    0X04,0XFE,0X23,0X00,0X3D,0X02,0X5F,0X00,0X21,0X00,0X01,
    0X05,0X2C,0X1C,0X13,0X74,0X00,0X00,0X02,0XF3,0X00,0X01,
    0X00,0X9C,0X58,0X09 ]


    trame.trameDecoupee.populate( trame.trameBrute )
    fTest( trame )

if __name__ == '__main__':
    main()
    