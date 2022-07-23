'''
Contante de l'application XXXX IHM de template

(c) VoRoBoTics
'''


IHM_TITLE = "IoTEPS Serial Test tool"
FEN_HAUTEUR = 510
GEN_PADDING = 2
SIZE_OF_FRAME = 64 #6/01/2021 ajout de la version
CAPT_STRUCT_FRAME_SIZE = 11 #Taille de la structure de donnée de chaque capteur
RS_HANDLER_PERIOD = 25 # ms
ZONE_DE_TEXTE_HAUTEUR = 15 #attention c'est en nombre de ligne
# BARO_FRAME_BASE_IDX = 5 #6/01/2021 ajout de la version

# LIS3MDL_SCALE = "16g"

#Trame de configuration
FREQ_EMISSION = 5 #100Hz de 10 à 100 tous les 10
# 15/01/2021 : F emission 100Hz le magnéto perd une mesure sur 2
FREQ_ECHATILLONAGE = 1 #val 1 à 5 pour 100 à 500 Hz cf. spec logiciel RDC RDC_SBL_022
FILTRAGE = 0
MISE_A_L_ECHELLE = 0

BAUD_RATE = 115200


