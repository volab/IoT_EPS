// le 13/2/2018
// changement de nom des methodes
// hasBeenClicked...

#include "bouton.h"

void bouton::begin( int boutonPin ){
    _boutonPin = boutonPin;
    _debutDernierAppui = millis();
    _finDernierAppui = _debutDernierAppui + 1;
    pinMode(boutonPin, INPUT_PULLUP);  
    _etat=0;
    _doubleClicked=false;
    _clicked=false;
    _longClicked=false;
    _lastUpdate = millis();
    _updateSpeed = BUTONSPEED ; // see in config.h    
    //_simpleClicCount = 0;
}
    
bool bouton::longClic(){ return _longClicked;  }
bool bouton::clic(){ return _clicked; }
bool bouton::doubleClic(){ return _doubleClicked; }  
  
void bouton::acquit(){
    _doubleClicked=false;
    _clicked=false;
    _longClicked=false;
}
    
// void bouton::refreshBouton()
void bouton::update(){
        #ifdef BUTONCLASS_LOOPMODE
#warning la classe Bouton est en mode loop
    if ( millis() - _lastUpdate < _updateSpeed ) return;
    _lastUpdate = millis();
    #else 
#warning la classe Bouton est en mode timer
    #endif
    // int bpState = _nano.digitalRead(_boutonPin)
    switch (_etat){
        case 0:
            if (digitalRead(_boutonPin) == LOW){ //active low buton due to INPUT_PULLUP
                _etat=1;
                _debutDernierAppui=millis();
            }
            break;
        case 1:
            //detection simple clique ou double clique
            // il serait bon que le 800 et le 200 soit des MACROCONSTANTES
            // multiple de la periode d'echantillonnage du bouton
            // ex : Te = 50ms, BTNLONGTIME = 16*Te, BTNSHORTTIME = 4*Te
            if (digitalRead(_boutonPin)==HIGH && \
                millis()<_debutDernierAppui + LONGCLICKTIME){
              _etat=2;
              _finDernierAppui=millis();
              // la variable _finDernierAppui n'est pas utile
              // elle pourait etre concatenee avec _debutDernierAppui
              // on l'appelerait alors _boutonEventTime par exemple
            }
            //detection clique long
            if (digitalRead(_boutonPin)==HIGH \
                    && millis()>=_debutDernierAppui + LONGCLICKTIME){ 
                _etat=0;
                _longClicked=true; //clic long detected
            }
            //les 2 conditions ci-dessus pourraient etre remaniees
            // if ( digitalRead( _boutonPin)){
                // if ( millis() >= _boutonEventTime + BTNLONGTIME ){
                    // _etat=0;
                    // _longClicked=true; //clic long detected
                // } else {
                    // _etat = 2 ; //peut etre un double clic ?
                    // _boutonEventTime = millis();
                // }
            // }
            break;
              
        case 2:
            //check if there is a second push in less than 200ms
            if (digitalRead(_boutonPin)==HIGH \
                    && millis()>_finDernierAppui + DOUBLECLICKSAMPLETIME ){
                _etat=0;
                _clicked=true;
                //_simpleClicCount++;
            }
            if (digitalRead(_boutonPin)==LOW && millis()<_finDernierAppui + DOUBLECLICKSAMPLETIME ){
            // A tester mais si le bouton est vu low a cet instant c'est forcement
            // un clic double quelque soit le temps non.
            // si on arrive dans la situation low apres 200ms c'est qu'on est
            // forcement repasse par l'etat 0
                _etat=5;
            }
            break;

        case 5: 
            //waiting for release buton before returning to state 0
            if (digitalRead(_boutonPin)==HIGH ){
                _etat=0;
                _doubleClicked=true;
            }
            break;
         
        }

}
    
bool bouton::directRead(){
	return !digitalRead( _boutonPin ); // ! cause input PULLUP
}  
