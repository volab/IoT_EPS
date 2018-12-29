#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H

#include "IoT_EPS.h"

 /**
* @def RETURN_NOT_FOUND_VALUE
When a function need to return or test a not found value 
*/
#define RETURN_NOT_FOUND_VALUE NOT_FOUND //alias definition

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

typedef CRGB::HTMLColorCode plugColor_t; /**< @brief see FastLed lib pixelstype.h for colors*/


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
        void begin( int pin , int onOffLedPin, int bpPin, int mode = 0 );
/** @todo rewrite a new begin methode to add plugName and _color*/
        void setColor( plugColor_t color ){ _couleur = color; }
        bool getState(){ return _state; }
        plugColor_t getColor(){ return _couleur; }
        String getPlugName(){return _plugName ; }
        void setPlugName( String name ){ _plugName = name ; }
        
        void on();
        void off();
        void toggle();
        bool isItTimeToSwitch(); /**< For the loop of ARDUINO check millis()*/
        void switchAtTime();
        
        void setMode( int mode ){ _mode = mode; }
        int getMode(){ return _mode; }
        
        // void setOnOffTime( unsigned long onDelay, unsigned long offDelay ){
            // _onDelay = onDelay; 
            // _offDelay = offDelay;
        // }
        // void setOnOffTime( unsigned long onDelay, unsigned long offDelay, DateTime startDate ){
            // _startDate = startDate;
            // setOnOffTime( onDelay, offDelay );          
        // }
        
        bool readFromJson();
        String readFromJson( String param );
        void writeToJson( String param, String val );
        void handleHtmlReq( String allRecParam );
        
        static int modeId( String mode );
        bouton bp;
        uint32_t getNextT2Switch(){ return _nextTimeToSwitch; }
        String getStringMode(){ return modes[ _mode ]; }
        void handleBpClic();
        
    private:
        static const String modes[5];
        int _pin = 0; /**< @brief The relay command plug pin*/
        bool _state; /**< @brief on off state of the physical plug*/
        String _plugName ; /**< @brief redPlug, greenPlug... as it is named in the html page*/
        int _mode = 0; /**< @brief MANUAL, CYCLIC... in int form see modeId method*/
        int _onOffLedPin;/**< a pin to display plug state diff of the cmd plug pin*/
        // plugColor_t _couleur = ROUGE;
        plugColor_t _couleur = CRGB::Red;
        String extractParamFromHtmlReq( String allRecParam, String Param );
        void updateOutputs( bool writeToJsonCount = true );
        uint32_t _nextTimeToSwitch;        
        
        uint8_t daysOnWeek; 
        /**
        * @var DateTime _startDate
        @brief date to turn on for Hebdo and Cycle mode
        * @var DateTime _endDate;
        @brief date to turn off for Manual and Hebdo mode
        
        See softDef.rst for detail
        * @var unsigned int _onDelay
        @brief For cyclic mode. Max value 300mn possibly not used
         * @var unsigned int _offDelay;
        @brief For cyclic and manual mode. Max value 300mn 
        * @var uint8_t daysOnWeek;
        @brief For HebdoMode each bit represent one day. bit0 represente Monday        
        */
        
        // DateTime _startDate;
        // DateTime _endDate;
        //DateTime _nextTimeToSwitch; //for reflexion
        // unsigned int _onDelay;
        // unsigned int _offDelay;



        
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
