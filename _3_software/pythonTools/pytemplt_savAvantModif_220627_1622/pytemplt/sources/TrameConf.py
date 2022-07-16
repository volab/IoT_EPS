
    # :Nom de ficier: TrameConf.py
    # :Autheur: J.Soranzo
    # :version: 2020210
    # :Dépendences:
    # :Licence: c-2020 groupe SAFRAN
    # :Projet: AVOCETTE RDC Capteurs
    # :Société: SAFRAN Electronic & Defense
    # :Entité: PAD

# Ce module ne comporte qu'une seule classe TrameConf


from constantes import FREQ_EMISSION, FREQ_ECHATILLONAGE, FILTRAGE, MISE_A_L_ECHELLE

class TrameConf():
    """
    Trame de configuration telle que définie dans la spec.
    """

    def __init__(self):
        self.preambule = 0xEB9055AA
        self.version = 10
        self.adresseRDC = 0xFE #broadcast
        self.freqEchantillonage = FREQ_ECHATILLONAGE
        self.freqEmission = FREQ_EMISSION
        self.activationFiltrage = FILTRAGE
        self.miseAEchelle = MISE_A_L_ECHELLE
        self.reserve = 0x0
        self._checksum = 0

        #self.trameBytes = bytearray()

    @property
    def trameBytes(self):
        a = bytearray(self.preambule.to_bytes(4, byteorder="big") ) 
        a+= bytearray(self.version.to_bytes(1, byteorder="big") )
        a+= bytearray(self.adresseRDC.to_bytes(1, byteorder="big") )
        a+= bytearray(self.freqEchantillonage.to_bytes(1, byteorder="big") )
        a+= bytearray(self.freqEmission.to_bytes(1, byteorder="big") )
        a+= bytearray(self.activationFiltrage.to_bytes(1, byteorder="big") )
        a+= bytearray(self.miseAEchelle.to_bytes(1, byteorder="big") )
        a+= bytearray(self.reserve.to_bytes(4, byteorder="big") )
        cs = 0
        for i in a:
            cs += i
        self._checksum = cs
        a+=bytearray(cs.to_bytes(2, byteorder="big") )
        return a

    @property
    def trameListHexa(self):
        return ["{:02X}".format(i) for i in self.trameBytes]

    def _getcs(self):
        self.trameBytes
        return self._checksum
    
    def _setcs(self):
        pass

    checksum = property( _getcs, _setcs )



import os
from constantes import GEN_PADDING, FEN_HAUTEUR

def main():
    # from constantes import GEN_PADDING, FEN_HAUTEUR   
    import os
    print("*"*80)
    print('Test du programme :' + os.path.basename(__file__) )
    print("*"*80)
    
    trame = TrameConf()
    print(trame)
    print(trame.trameBytes.hex() )
    print( "Longueur de la trame {} octets".format(len(trame.trameBytes)) )
    print( trame.trameListHexa )
    print("Trame checksum : 0x{:04X} valeur attendue  0x03E7".format(trame.checksum))
    trame.freqEchantillonage = 1
    trame.freqEmission = 2
    trame.activationFiltrage = 3
    trame.miseAEchelle = 4
    trame.reserve = 0x05060708
    print('Trame modifiée:')
    print( trame.trameListHexa )
    print("Trame modifiée nouvelle checksum : 0x{:04X} valeur attendue  0x03A6".format(trame.checksum))

if __name__ == '__main__':
    main()
