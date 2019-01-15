/**
* @file bouton.h
* @author Gilles Debussy and J.SORANZO
* @date oct 2015
* @copyright 2018 CC0
* @version 1.0
* @brief a class to manage psuh bouton
*/

/*
 gilles
 repris par JSO dans le cadre du projet temp datalogger
 26/06/2017
 Un appui de + de 800ms est un clic long
 Un deuxième appui en moins de 200ms après le premier est un double clic
 // Pour le moment ces 2 constante sont en dur dans le code (cf. fichier .cpp)
 // possibilite d'en faire des macro (cf. fichier .cpp encore)
 Sinon c'est un clic simple
 Fonctionne avec des active low bouton (INPUT_PULLUP)
*/ 
 


#ifndef bouton_h
#define bouton_h

#include <Arduino.h>

//commenter pour passer en mode timer
#define BUTONCLASS_LOOPMODE //versus timer mode
// dans la ISR appeler update()
// compilation conditionnelle
// Si on est pas en mode timer alors on est en mode LOOP
// En mode loop, il faut appeler la fonction update a chaque tour de la boucle
// loop (au debut ou a la fin) avant d'appeler les methode clic, doubleClic
// longClic, acquit

#ifndef BUTONSPEED //normaly defined in config.h
#define BUTONSPEED 70 //ms
#endif

class bouton{
    public:
        void begin( int boutonPin );
        void update();
        //void refreshBouton();
        bool clic();
        bool doubleClic();
        bool longClic();
        void acquit(); //remet les état à zéro (clique et double clique)
		bool directRead();

    private:
        int _boutonPin; //numéro de Pin pour le bouton
        unsigned long _finDernierAppui; // heure de la dernière fois que qq1 a relaché le bouton
        unsigned long _debutDernierAppui; // heure de la dernière fois que qq1 a appuyé le bouton
        byte _etat; // etat interne du bouton pour déterminer clique et double clique
        bool _clicked; // si a été cliqué
        bool _doubleClicked; // si a été doublecliqué (dans les 200ms en dur)
        bool _longClicked; //si subit clique long ( 800ms en dur dans le code)
        unsigned long _lastUpdate; 
        unsigned long _updateSpeed; // vitesse de rafraichissement en mode loop

};

#endif
