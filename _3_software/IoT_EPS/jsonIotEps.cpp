/**
* @file cpowerplug.cpp
* @author J.Soranzo
* @date 10/11/2018
* @copyright see project readme 
* @version 1.0
* @brief This class is the plug class for Electrical Power Strip project
*/

#include "jsonIotEps.h"

bool CJsonIotEps::init(){
    return true;
}


void CJsonIotEps::storeJson(){
    return;
}

bool CJsonIotEps::loadJson(){
    bool fileLoaded = false;

    //compute HO hash of config4.json


    // compute H1 of config4copy1.json

    if ( H0 == H1 ){
        // master ok
        //load config4.json
    }
    return true;
}