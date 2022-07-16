
#     :Nom de ficier: TrameMag.py
#     :Autheur: J.Soranzo
#     :version: 20210318
#     :Dépendences: math
#     :Licence: (c) 2020 groupe SAFRAN
#     :Projet: AVOCETTE RDC Capteurs
#     :Société: SAFRAN Electronic & Defense
#     :Entité: PAD

# Défini les classe DataValue, MagDataValue, DataMag qui permettent de décoder les
# informations magnétométriques contenues dans les trames RDC Capteurs.

import constantes as CST
from math import atan2, pi

class DataValue:
    def __init__(self):
        self.v16bits = 0
        # print("tag DataValue")

    def __str__(self):
        return( "Value in hexa {:04X}".format(self.v16bits) )
    
    @property
    def signed16( self ):
        valOctet = self.poidsFort.to_bytes(1, 'little')\
            + self.poidsFaible.to_bytes(1, 'little')
        return int.from_bytes( valOctet, byteorder='big', signed=True)

    @property
    def poidsFort(self):
        return ( self.v16bits & 0xFF00 ) >> 8

    @property
    def poidsFaible(self):
        return ( self.v16bits & 0xFF )

    @property
    def enHexa(self):
        return '0x{:04X}'.format(self.v16bits)

class MagDataValue(DataValue):
    def __init__(self, echelle):
        DataValue.__init__(self)
        self.echelle = echelle

    @property
    def enDeg( self ):
        tempFloat = 25.0+self.signed16/8.0
        return tempFloat

    @property
    def enGauss( self ):
        ''' echelle: "16g", "12g", "8g", "4g"'''
        scaleFactors = { "16g": 1711.0, "12g":2281.0, "8g":3421.0, "4g":6842.0}
        scaleFactor=scaleFactors[self.echelle]
        valGauss = self.signed16/scaleFactor
        return valGauss

    @property
    def scaleFactor( self ):
        ''' 
        Propriété crée spécialement pour intégrer la calibration
        echelle: "16g", "12g", "8g", "4g"'''
        scaleFactors = { "16g": 1711.0, "12g":2281.0, "8g":3421.0, "4g":6842.0}
        scaleFactor=scaleFactors[self.echelle]
        return scaleFactor

class DataMag:
    """ Data structure:
        numC
        OUTXPF
        OUTXpf
        OUTYPF
        OUTYpf
        OUTZPF
        OUTZpf
        TPFort
        TPFaible
        Err
        Stat
    """

    def __init__(self , dataBaseAd ):
        self.baseAd = dataBaseAd
        self.dataSize = CST.CAPT_STRUCT_FRAME_SIZE
        self.numC = 0
        self.x = MagDataValue( CST.LIS3MDL_SCALE )
        self.y = MagDataValue( CST.LIS3MDL_SCALE )
        self.z = MagDataValue( CST.LIS3MDL_SCALE )
        self.temp = MagDataValue( 0 )
        self.err = 0
        self.status = 0
        self.offset = XYZ(0,0,0)

    def populate(self, trameBrute):
        self.numC = trameBrute[ self.baseAd ]
        self.x.v16bits = ( trameBrute[ self.baseAd + 1 ] << 8 ) \
                        + trameBrute[ self.baseAd + 2 ]
        self.y.v16bits = ( trameBrute[ self.baseAd + 3 ] << 8 ) \
                        + trameBrute[ self.baseAd + 4 ]
        self.z.v16bits = ( trameBrute[ self.baseAd + 5 ] << 8 ) \
                        + trameBrute[ self.baseAd + 6 ]
        self.temp.v16bits = ( trameBrute[ self.baseAd + 7 ] << 8 ) \
                        + trameBrute[ self.baseAd + 8 ]               
        self.err = trameBrute[ self.baseAd + 9]
        self.stat = trameBrute[ self.baseAd + 10]

    @property
    def direction( self ):
        xfloatEnGauss = ( float(self.x.signed16) - self.offset.x) / self.x.scaleFactor
        yfloatEnGauss = ( float(self.y.signed16) - self.offset.y)/self.y.scaleFactor
        # xenmG = self.x.enGauss*1000
        xenmG = xfloatEnGauss*1000
        # yenmG = self.y.enGauss*1000
        yenmG = yfloatEnGauss*1000
        if ( xenmG == 0 ):
            if ( yenmG < 0 ):
                direction = 90
            else:
                direction = 0
        else:
            direction = 180*atan2( yenmG,xenmG )/pi
            if direction < -180:
                direction += 360
            # if direction > 360:
            #     direction -= 360
        return "{:.1f}°".format( direction )

    def pourEnregistrement( self, separateur = ',') :
        """
        :methode: pourEnregistrement( separateur )
        :parmam in: separateur, valeur par défaut "," de type chaine

        Cette méthode permet de préparer les données en format human readable en vue de les enregister.
        """

        chaine = ""
        chaine = "Capt_{}{}".format( self.numC, separateur)
        chaine += self.direction + separateur
        chaine += "{:.3f}mG{}".format( 1000*self.x.enGauss, separateur)
        chaine += "{:.3f}mG{}".format( 1000*self.y.enGauss, separateur)
        chaine += "{:.3f}mG{}".format( 1000*self.z.enGauss, separateur)
        chaine += "{}°C{}".format( self.temp.enDeg, separateur)
        chaine += "0x{:02X}{}".format(self.err,separateur)
        chaine += "0x{:02X}".format(self.stat)
        return chaine

class XYZ() :
    """
    # source : https://raw.githubusercontent.com/National-Control-Devices/Raspberry_Pi-Python_Codes/master/PRODRUN5/LIS3MDL/LIS3MDL.py

    """
    def __init__(self, x=None, y=None, z=None) :
        self.x = x
        self.y = y
        self.z = z
        
    def __repr__(self) :
        return str( '{:6} {:6} {:6}'.format(self.x, self.y, self.z) )
    
    def total(self) :
        mtotal = (((self.x**2)+(self.y**2)+(self.z**2))**0.5)
        mtotal = (mtotal * 4 * 6.842)/32768
        return mtotal



def fTest( trame ):
    import os
    print("*"*80)
    print('Test du module :' + os.path.basename(__file__) )
    print("*"*80)
    print("Mag numéro de capteur : {}".\
        format( trame.trameDecoupee.dataMag.numC ) )
    # print("Température Pitot hexa {}".\
    #     format( trame.trameDecoupee.dataPitot.temp.enHexa ) )
    print("Mag outX : {:.3f} mG".\
        format( trame.trameDecoupee.dataMag.x.enGauss*1000))
    print("Mag outY : {:.3f} mG".\
        format( trame.trameDecoupee.dataMag.y.enGauss*1000))
    print("Mag outZ : {:.3f} mG".\
        format( trame.trameDecoupee.dataMag.z.enGauss*1000))
    print("Mag temp : {:.2f} °C".\
        format( trame.trameDecoupee.dataMag.temp.enDeg)) 
    print("Direction : {}".\
        format( trame.trameDecoupee.dataMag.direction ))  
    print("Pour Enregistrement : " + \
        trame.trameDecoupee.dataMag.pourEnregistrement() )
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