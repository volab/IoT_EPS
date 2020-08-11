
#include "IoT_EPS.h"

#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H



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
News from feb2019 mcp2371 was replaced by nanoI2Cexpander a new mother clas was used : Cnano
So CPowerPlug class inherit from Cnano who instancite a _nano object from CNanoI2CIOExpander
It's a bit tricky !
*/
class CPowerPlug : public CNano {
    public:
 
        CPowerPlug(){}
        CPowerPlug( plugColor_t couleur ){ _couleur = couleur;}
        void begin( int pin , int onOffLedPin, int bpPin, int mode = 0 );
/** @todo [OPTION] rewrite a new begin methode to add plugName and _color*/
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
              
        // bool readFromJson();
        bool readFromJson( bool restaurePhyState );
        String readFromJson( String param );
        void writeToJson( String param, String val );
        void writeDaysToJson();
        void handleHtmlReq( String allRecParam );
        
        static int modeId( String mode );
        bouton bp;
        uint32_t getNextT2Switch(){ return _nextTimeToSwitch; }
        String getStringMode(){ return modes[ _mode ]; }
        void handleBpClic();
        void handleBpLongClic();
        void handleBpDoubleClic();
        uint8_t getDays(){ return _daysOnWeek; }
        bool getPause(){ return _pause; }
        
        CFlasherNanoExp onOffFlasher;
        bool flashLedReq(){ return _flashLed; }
        void manageLeds( bool ledState );
        void setMainPow( bool mainP ){ _mainPower = mainP; }
        
    private:
        bool _flashLed = false;
        static const String modes[5];
        int _pin = 0; /**< @brief The relay command plug pin*/
        bool _state; /**< @brief on off state of the physical plug*/
        String _plugName ; /**< @brief redPlug, greenPlug... as it is named in the html page*/
        int _mode = 0; /**< @brief MANUAL, CYCLIC... in int form see modeId method*/
        int _onOffLedPin;/**< a pin to display plug state diff of the cmd plug pin*/

        plugColor_t _couleur = CRGB::Red;
        //String extractParamFromHtmlReq( String allRecParam, String Param );
        void updateOutputs( bool writeToJsonCount = true );
        uint32_t _nextTimeToSwitch;        
        
        uint8_t _daysOnWeek; 
        bool _pause = false;
        bool _ledOn = true;
        bool _mainPower;
};


#endif
