#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H

#include <Adafruit_MCP23017.h>
#include <Arduino.h>

enum {
    MANUEL,
    TIMER,
    CYCLE
};

#define ON true
#define OFF false

typedef enum plugColor_t{
        ROUGE, VERT, BLEU, JAUNE
};



class CPowerPlug{
    public:
        CPowerPlug(){}
        CPowerPlug( plugColor_t couleur ){ _couleur = couleur;}
        void begin( int pin , int onOffLedPin, int mode = MANUEL );
        static void init();
    private:
        static bool _initDone;
        int _pin;
        bool _state;
        int _mode = MANUEL;
        int _onOffLedPin;
        plugColor_t _couleur = ROUGE;
        static Adafruit_MCP23017 _mcp;
        
};




#endif
