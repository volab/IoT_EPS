'''
Contante de l'application RDC capteurs IHM de test

(c) groupe SAFRAN
'''

FEN_HAUTEUR = 510
GEN_PADDING = 2
SIZE_OF_FRAME = 64 #6/01/2021 ajout de la version
CAPT_STRUCT_FRAME_SIZE = 11 #Taille de la structre de donnée de chaque capteur
RS_HANDLER_PERIOD = 9 # ms
BARO_FRAME_BASE_IDX = 5 #6/01/2021 ajout de la version

LIS3MDL_SCALE = "16g"

#Trame de configuration
FREQ_EMISSION = 5 #100Hz de 10 à 100 tous les 10
# 15/01/2021 : F emission 100Hz le magnéto perd une mesure sur 2
FREQ_ECHATILLONAGE = 1 #val 1 à 5 pour 100 à 500 Hz cf. spec logiciel RDC RDC_SBL_022
FILTRAGE = 0
MISE_A_L_ECHELLE = 0

BAUD_RATE = 460800


