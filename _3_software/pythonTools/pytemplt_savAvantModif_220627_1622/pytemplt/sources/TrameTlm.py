"""
:Nom de ficier: TrameTlm.py
:Autheur: J.Soranzo
:version: 20210318
:Dépendences: TrameMag
:Licence: (c) 2020 groupe SAFRAN
:Projet: AVOCETTE RDC Capteurs
:Société: SAFRAN Electronic & Defense
:Entité: PAD

Défini les classe Distance, DataTlm qui permettent de décoder les
informations télémétriques contenues dans les trames RDC Capteurs.
"""

import constantes as CST
from TrameMag import DataValue


class Distance(DataValue):
    def __init__(self):
        DataValue.__init__(self)

    @property
    def enMetre(self):
        """Méthode, vue comme une propriété, qui retourne la distence directement en centimètre
        Et au format ASCII"""
        return "{} cm".format( self.v16bits)
        
class DataTlm:
    def __init__(self , dataBaseAd ):
        self.baseAd = dataBaseAd
        self.numC = 0
        self.err = 0
        self.status = 0
        self.dist = Distance()

    def populate(self, trameBrute):
        self.numC = trameBrute[ self.baseAd ]
        self.err = trameBrute[ self.baseAd + 9]
        self.stat = trameBrute[ self.baseAd + 10]
        self.dist.v16bits = ( trameBrute[ self.baseAd + 1 ] << 8 ) \
                + trameBrute[ self.baseAd + 2 ]

    def pourEnregistrement( self, separateur = ',') :
        """
        :methode: pourEnregistrement( separateur )
        :parmam in: separateur, valeur par défaut "," de type chaine

        Cette méthode permet de préparer les données en format human readable en vue de les enregister.
        """

        chaine = ""
        chaine = "Capt_{}{}".format( self.numC, separateur)
        chaine += self.dist.enMetre + separateur
        chaine = chaine + "0x{:02X}{}".format(self.err,separateur)
        chaine = chaine + "0x{:02X}".format(self.stat)
        return chaine

def fTest( trame ):
    print("Télémètre numéro de capteur : {}".\
        format( trame.trameDecoupee.dataTlm.numC ) )
    print("Télémètre distance en hexa {}".\
        format( trame.trameDecoupee.dataTlm.dist.enHexa ) )
    print("Télémètre distance en mètre {}".\
        format( trame.trameDecoupee.dataTlm.dist.enMetre ) )
    print("for rec : " +\
        trame.trameDecoupee.dataTlm.pourEnregistrement() )

def main():
    import os
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
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
    fTest( trame )

if __name__ == '__main__':
    main()