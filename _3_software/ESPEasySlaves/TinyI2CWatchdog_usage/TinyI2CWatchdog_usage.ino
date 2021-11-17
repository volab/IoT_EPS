#define RSSPEED 115200

#include <Arduino.h>
#include <Wire.h>
// write register
    // Wire.beginTransmission((uint8_t)NANOEXP_ADDRESS);
    // Wire.write((uint8_t)add);
    // Wire.write((uint8_t)val);
    // Wire.endTransmission();

#define TINY_I2C_ADD 0x26    
    
void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    Wire.begin();
    int val = readRegister( 5 );
    Serial.print( "Valeur lue = " );
    Serial.println( val, HEX );
    writeRegister( 6, 10 );
    delay( 1000 );
    writeRegister( 0xA5, 0 );
    // writeRegister( 0x80, 0 ); // store setting in EEPROM
    for ( int i = 0; i < 5 ; i++ ){
                delay( 6000 );
        writeRegister( 0xA5, 0 );
        Serial.println( "refresh" + String( i+1 ) );
    }    
    Serial.println( "No more refresh" );
    
}

void loop(){

    
}

void writeRegister( int add, int val){
    Wire.beginTransmission((uint8_t)TINY_I2C_ADD);
    Wire.write((uint8_t)add);
    Wire.write((uint8_t)val);
    Wire.endTransmission();
}

int readRegister( int add ){
    Wire.beginTransmission((uint8_t)TINY_I2C_ADD);
    Wire.write((uint8_t)add);
    Wire.endTransmission();
    Wire.requestFrom( (uint8_t)TINY_I2C_ADD, (uint8_t)1 );
    return (int)Wire.read();   
}