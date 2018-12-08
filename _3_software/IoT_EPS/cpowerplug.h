#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H

#include "IoT_EPS.h"
// #include <Arduino.h>
// #include <RTClib.h>
// #include <ESP8266WebServer.h>
// #include "Cmcp.h"
// #include <FastLED.h>

// enum {
    // MANUEL, /**< Manuel mode of the plug */
    // TIMER, /*!< Timer mode of the plug */
    // CYCLE, /*!< Cyclic mode of the plug */
    // HEBDO, /*!< Weekly mode of the plug */
    // CLONE /**< @brief  clone an other plug mode*/
// };


/**
* @def ON alias of true
*/
#define ON true
#define OFF false /*!< OFF alias for false*/



/**
* @typedef plugColor_t
* @brief un enum for color of the plugs
*/
// typedef enum plugColor_t{
        // ROUGE, VERTE, BLEUE, JAUNE
// };

typedef CRGB::HTMLColorCode plugColor_t;


// static inline String stringFromColor(plugColor_t c){
    // static const String strings[] = { "ROUGE", "VERTE", "BLEUE", "JAUNE" };
    // return strings[c];
// }

/**
* @class CPowerPlug CpowerPlug.h
* @brief a class to oparate power plugs

Inherit of the Cmcp class that initialize mcp23711 I2C Io expander component
*/
class CPowerPlug : public Cmcp {
    public:
 
        CPowerPlug(){}
        CPowerPlug( plugColor_t couleur ){ _couleur = couleur;}
        void begin( int pin , int onOffLedPin, int mode = 0 );
/** @todo rewrite a new begin methode to add plugName and _color*/
        void setColor( plugColor_t color ){ _couleur = color; }
        bool getstate(){ return _state; }
        plugColor_t getColor(){ return _couleur; }
        String getPlugName(){return _plugName ; }
        void setPlugName( String name ){ _plugName = name ; }
        
        void on();
        void off();
        void toggle();
        bool isItTimeToSwitch(); /**< For the loop of ARDUINO check millis()*/
        void setMode( int mode ){ _mode = mode; }
        int getMode(){ return _mode; }
        
        void setOnOffTime( unsigned long onDelay, unsigned long offDelay ){
            _onDelay = onDelay; 
            _offDelay = offDelay;
        }
        void setOnOffTime( unsigned long onDelay, unsigned long offDelay, DateTime startDate ){
            _startDate = startDate;
            setOnOffTime( onDelay, offDelay );          
        }
        
        bool readFromJson();
        void handleHtmlReq( String allRecParam );
        
        static int modeId( String mode );
        
        
    private:
        static const String modes[5];
        int _pin = 0; /**< @brief The relay command plug pin*/
        bool _state;
        String _plugName ;
        int _mode = 0;
        int _onOffLedPin;/**< a pin to display plug state diff of the cmd plug pin*/
        // plugColor_t _couleur = ROUGE;
        plugColor_t _couleur = CRGB::Red;
        String extractParamFromHtmlReq( String allRecParam, String Param );
        

        /**
        * @var DateTime _startDate
        @brief date to turn on for Hebdo and Cycle mode
        * @var DateTime _endDate;
        @brief date to turn off for Manual and Hebdo mode
        
        See softDef.rst for detail
        * @var unsigned int _onDelay
        @brief For cyclic mode. Max value 300mn
         * @var unsigned int _offDelay;
        @brief For cyclic and manual mode. Max value 300mn 
        * @var uint8_t daysOnWeek;
        @brief For HebdoMode each bit represent one day. bit0 represente Monday        
        */
        uint8_t daysOnWeek;        
        DateTime _startDate;
        DateTime _endDate;
        unsigned int _onDelay;
        unsigned int _offDelay;

        void updateOutputs();

        
};

/*
  "redPlug": {
    "State": "ON",
    "Manuel": {
        "Status": "OFF"
    },
    "Minuterie": {
      "Status": "ON",
      "Duree": "60"
    },
    "Cyclique": {
      "Status": "OFF",
      "hDebut": "",
      "dureeOn": "",
      "dureeOff": ""
    },
    "Hebdomadaire": {
      "Status": "OFF",
      "hDebut": "",
      "hFin": "",
      "Jours": {
        "LU": "",
        "MA": "",
        "ME": "",
        "JE": "",
        "VE": "",
        "SA": "",
        "DI": ""
      }
    },
    "Clone" : {
        "Status": "OFF",
        "ClonedPlug" : ""
    },
    "OnOffCount" : "0"
  },*/


#endif
