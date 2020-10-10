

#ifndef H_OLED_MESSAGES_H
#define H_OLED_MESSAGES_H

#define FRENCH_OLED_TXT

//#define ENGLISH_OLED_TXT


/** @todo [OPTION] Put messages tempo in a json config file and access with html config form */
#define OLED_LOGO_DISPLAY_TEMPO 4000 //4s
#define OLED_STARTUP_MESSAGE_TEMPO 2000

//Common Messages
#define PROVIDER_NAME F("VoLAB")
#define EPS_NAME1 F("   Electrical")
#define EPS_NAME2 F("   Power")
#define EPS_NAME3 F("   Strip")


#ifdef FRENCH_OLED_TXT
//                               123456789+123456789+1
#define DS3231_START_DATE     F("DS3231 demarre a:")
#define AT_THIS_POINT         F("A partir d'ici:")
#define OLED_FILE_SYSTEM_OK   F("* Fichiers ok")
#define OLED_CONFIG_PARAM_OK  F("* Parametres ok")

#else //ENGLISH Text are default texts
#define DS3231_START_DATE    F("DS3231 start date:")
#define AT_THIS_POINT        F("At This point:")
#define OLED_FILE_SYSTEM_OK  F("* File system ok")
#define OLED_CONFIG_PARAM_OK F("* Config. param ok")

#endif





#endif //guard

