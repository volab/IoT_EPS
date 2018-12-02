#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H


#include <Arduino.h>
#include <RTClib.h>
#include <ESP8266WebServer.h>
#include "Cmcp.h"

/**
a no named enumeration for plug mode
*/
enum {
    MANUEL, /**< Manuel mode of the plug */
    TIMER, /*!< Timer mode of the plug */
    CYCLE, /*!< Cyclic mode of the plug */
    HEBDO, /*!< Weekly mode of the plug */
    CLONE /**< @brief  clone an other plug mode*/
};


/**
* @def ON alias of true
*/
#define ON true
#define OFF false /*!< OFF alias for false*/

/**
* @typedef plugColor_t
* @brief un enum for color of the plugs
*/
typedef enum plugColor_t{
        ROUGE, VERTE, BLEUE, JAUNE
};

static inline String stringFromColor(plugColor_t c){
    static const String strings[] = { "ROUGE", "VERTE", "BLEUE", "JAUNE" };

    return strings[c];
}

/**
* @class CPowerPlug CpowerPlug.h
* @brief a class to oparate power plugs
*/
class CPowerPlug : public Cmcp {
    public:
        CPowerPlug(){}
        CPowerPlug( plugColor_t couleur ){ _couleur = couleur;}
        void begin( int pin , int onOffLedPin, int mode = MANUEL );

        void setColor( plugColor_t color ){ _couleur = color; }
        bool getstate(){ return _state; }
        plugColor_t getColor(){ return _couleur; }
        
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
        

        
        
    private:

        int _pin = 0; /**< @brief The relay command plug pin*/
        bool _state;
        int _mode = MANUEL;
        int _onOffLedPin;/**< a pin to display plug state diff of the cmd plug pin*/
        plugColor_t _couleur = ROUGE;

        uint8_t daysOnWeek;
        // heure de début
        DateTime _startDate;
        // heure de fin
        DateTime _endDate;
        // duréeOn
        unsigned long _onDelay;
        unsigned long _offDelay;
        // duréeOff
        void updateOutputs();
        // #ifdef DEBUG
        // String dPrompt = F("<VOLAB CPowerPlug >");
        // #else
        // String dPrompt = "";
        // #endif
        
};




#endif
