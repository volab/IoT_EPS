#ifndef _CPOWERPLUG_H
#define _CPOWERPLUG_H


#include <Arduino.h>
#include <RTClib.h>
#include "Cmcp.h"

enum {
    MANUEL,
    TIMER,
    CYCLE,
    HEBDO
};



#define ON true
#define OFF false

typedef enum plugColor_t{
        ROUGE, VERT, BLEU, JAUNE
};



class CPowerPlug : public Cmcp {
    public:
        CPowerPlug(){}
        CPowerPlug( plugColor_t couleur ){ _couleur = couleur;}
        void begin( int pin , int onOffLedPin, int mode = MANUEL );

        
        bool getstate(){ return _state; }
        plugColor_t getColor(){ return _couleur; }
        
        void on();
        void off();
        void toggle();
        bool isItTimeToSwitch();
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

        int _pin = 0;
        bool _state;
        int _mode = MANUEL;
        int _onOffLedPin;
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
        #ifdef DEBUG
        String dPrompt = F("<VOLAB CPowerPlug >");
        #else
        String dPrompt = "";
        #endif
        
};




#endif
