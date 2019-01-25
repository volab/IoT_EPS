/**
 @file cnano.cpp
 @author J.SORANZO
 @date 25/01/2019
 @copyright 2018 CC0
 @version git versionning
 @brief Implémentation file of CNano class
*/

#include "cnano.h"

bool CNano::_initDone = false;
CNanoI2CIOExpander CNano::_nano;

void CNano::init(){
    _initDone = true;
    _nano.begin();
}