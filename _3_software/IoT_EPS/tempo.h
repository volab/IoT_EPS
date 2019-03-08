/**
 @file tempo.h
 @author J.SORANZO
 @date 08/03/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'entête de la classe tempo
*/


#ifndef _TEMPO_H
#define _TEMPO_H

class CTempo {
    public:
        void begin();
        void start( unsigned long duree );
        void update();
        bool finie = false;
        void stop();
        void pause();
        bool enCours(){ return _enCours; }
        //void releasePause();
        //void restart();
    private:
        bool _enCours;
        unsigned long _millis;
        unsigned long _duree;
        
};
#endif

