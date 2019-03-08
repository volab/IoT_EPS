/**
 @file tempo.cpp
 @author J.SORANZO
 @date _date
 @copyright 2019 SAFRAN Group
 @version git versionning
 @brief Fichier d'implémentation de la classe CTempo
*/

#include "tempo.h"
#include "Arduino.h"
#include "debugSerialPort.h"

void CTempo::begin(){
    _enCours = false;
    _duree = 0;
    _millis =  millis();
    finie = false;
}

void CTempo::update(){
    DEFDPROMPT( F("Tempo::update") );
    //DSPL( dPrompt + (String)_millis );
    if ( _enCours && (millis() - _millis >= _duree) ){
        finie = true;
        _enCours = false;
        //DSPL( dPrompt + F("finie") );
    }
}

void CTempo::start( unsigned long duree ){
    finie = false;
    _enCours = true;
    _duree = duree ;
    _millis =  millis();
}

void CTempo::pause(){
    _enCours = false;
}

void CTempo::stop(){
    begin(); // ;-)
}

