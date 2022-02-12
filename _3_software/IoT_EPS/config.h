/**
* @file config.h
* @author J.SORANZO
* @date 08/12/2021
* @copyright 2021 CC0
* @brief all application parameters
*/

#ifndef _CONFIG_H
#define _CONFIG_H

/** @todo [NECESSARY]Passage heure d'hiver/été : soit automatique soit configurable via l'interface */
#define DEFAULT_PREFIX_NAME "ESP_IOT"


#define JSON_TAG "IoTEps"
#define JSON_VERSION "v5.1"

#define NTPSERVER "fr.pool.ntp.org"
//#define OFFSET_HEURE 2 //ETE
#define OFFSET_HEURE 1 //Hiver

#define DEFAULT_LED_LUMINOSITY 15
#define FLASH_ERROR_PERIODE 500 //ms

#define INTERNET_HEALTH_TARGET "http://www.google.fr/"

#define OLED_I2C_ADD 0x3C
/*
    Scanning (SDA : SCL) - GPIO4 : GPIO5 - 
    I2C device found at address 0x26  !
    I2C device found at address 0x3C  !
    I2C device found at address 0x53  !
    I2C device found at address 0x58  !
    I2C device found at address 0x68  !
    

- watchdog : 0x26 (defined in cattiny_i2C_watchdog.h)
- ioexpender : 0x58 (ored with D13) - defined in the ARDUINO NANO code
- DS3231 : 0x68 defined in RTClib.h
- +EEPROM on DS3231 1010011 normaly 0x53 base add is 0x50 and I have solder A2 slot
there is 3 pull-up on the board.
*/

#define OLED_REFRESH_PERIOD 1 //in seconds
#define OLED_SYSTEM_STATE_DISPLAY_DIV 2 //example 2*1s


#define RTC_UPDATE_PERIOD 15 //every 15mn
// #define RTC_UPDATE_PERIOD 1 //every 1

#define RTC_ALLOWED_TIME_ERROR 20//seconds
#define I2C_CBIT_TEST_PERIOD 60 * 1000 //ms it smells millis() ;-)
#define I2C_RETRIES 5
#define CBIT_TIME 60000 // period of CBIt in ms

#define DEFAULTIPADD "192.168.95.42"
#define NBRPLUGS 4
#define NUM_LEDS NBRPLUGS /**< for fastLED class */

#define COLOR_LED_ERROR_PERIOD 300 //ms

#define OLED_SHUTDOWN_MESSAGE "Shutdown Started !"

#endif