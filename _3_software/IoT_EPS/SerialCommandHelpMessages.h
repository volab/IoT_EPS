#ifndef SERIALCMDHLPMSG_H
#define SERIALCMDHLPMSG_H

    //There is 29 cmds on 2/2/2022

    #define HH_HLP_MSG "<H> display this list in alphabetic order\n"
    #define H_HLP_MSG "<h> display this list in thematic order\n"

    //A
    #define BB_HLP_MSG "<B0 to 10> B as bind un error to the system (11 errors)\n"
    #define CC_HLP_MSG "<C> Check DS3231 date\n"
    #define DD_HLP_MSG "<D> SPIFFS dir\n"   
    #define EE_HLP_MSG "<E> display code status\n"
    #define FF_HLP_MSG "<F> Find I2C device I2C scan\n"
    //G
    //H
    #define II_HLP_MSG "<I _newSSID> write SSID in credentials WARNING\n"
    #define JJ_HLP_MSG "<J _jsonFileNumber 0..2> for display config.json or one of its copy\n"
    //K
    #define LL_HLP_MSG "<L> _newSoftAP_SSID> write SoftAP SSID in credentials WARNING\n"
    //M
    #define NN_HLP_MSG "<N> nano IO expander test\n"
    #define OO_HLP_MSG "<O> nano out test HIGH\n"   
    #define PP_HLP_MSG "<P key value> write config parameter in json WARNING\n"
    //Q
    #define RR_HLP_MSG "<R> I2C recovery\n"
    #define SS_HLP_MSG "<S JJ/MM/AAAA HH:MM:SS> returns code <O>\n"
    #define TT_HLP_MSG "<T HH:MM:SS> returns code <O>\n"
    //U
    //V
    #define WW_HLP_MSG "<W> display WIFI mode\n"
    //X
    //Y
    #define ZZ_HLP_MSG "<Z> set WD to 4mn and 15s to upload a new firmware\n"
    
    
    #define A_HLP_MSG "<a> for Ip address\n"  
    #define B_HLP_MSG "<b0 to x unbind error to the system\n x : see B command\n"
    #define C_HLP_MSG "<c> I2C crash\n"    
    #define D_HLP_MSG "<d _filename> erase a file WARNING\n"
    #define E_HLP_MSG "<e> display system status\n"
    //f
    //g
    //h
    #define I_HLP_MSG "<i _wifiPass> write password in credentials WARNING\n"
    #define J_HLP_MSG "<j> display general part of main config json file\n"
    //k
    #define L_HLP_MSG "<l _wifiPass> write soft AP password in credentials WARNING\n"
    //m
    //n
    #define O_HLP_MSG "<o> nano out test low\n"
    #define P_HLP_MSG "<p> display main power state\n"
    //q
    #define S_HLP_MSG "<s> set DS3231 by NTP server\n"
    #define T_HLP_MSG "<t various_param> for code test\n"
    //u
    //v
    #define W_HLP_MSG "<w> for WiFi.printDig function\n"
    //x
    //y
    #define Z_HLP_MSG "<z> display credetial file\n"

#endif