/**
 @file csystem.cpp
 @author J.SORANZO
 @date 30/06/2020
 @copyright 2020 CC0
 @version git versionning
 @brief Fichier d'implémentation de la classe system pour englober tout le system
*/

#include "csystem.h"

// VoLAB Logo (1kB size : 128*64 /8 - 8 bytes/line)
//generated with http://en.radzio.dxp.pl/bitmap_converter/
//parameters : Horizontal little endianess

const unsigned char CSystem::logoLab [1024] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xCF, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x9F, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xE0,
0x00, 0x00, 0x01, 0xB9, 0xC8, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF8,
0x00, 0x00, 0x01, 0x70, 0xE8, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00, 0x1C,
0x00, 0x00, 0x01, 0x66, 0x68, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x60, 0x00, 0x0E,
0x00, 0x00, 0x01, 0x66, 0x68, 0x00, 0x00, 0x00, 0x23, 0x10, 0x00, 0x00, 0x00, 0x60, 0x00, 0x06,
0x00, 0x00, 0x01, 0x70, 0xE8, 0x00, 0x00, 0x00, 0x27, 0x90, 0x00, 0x00, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x79, 0xE8, 0x00, 0x00, 0x00, 0x27, 0x90, 0x00, 0x00, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x7F, 0xE8, 0x00, 0x0C, 0x00, 0x67, 0x88, 0x00, 0xE0, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x79, 0xE8, 0x00, 0x13, 0x00, 0x4F, 0xC8, 0x03, 0xB0, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x70, 0xE8, 0x00, 0x21, 0x80, 0xCF, 0xC8, 0x06, 0x08, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x66, 0x68, 0x00, 0x4C, 0xE1, 0x8F, 0xC7, 0x0C, 0x04, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x66, 0x68, 0x00, 0x9E, 0x3F, 0x1F, 0xE1, 0xF8, 0xE3, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x70, 0xE8, 0x01, 0x3F, 0x00, 0x3F, 0xF8, 0x01, 0xF1, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x7F, 0xE8, 0x01, 0x3F, 0xC1, 0xFF, 0xFE, 0x03, 0xF1, 0x00, 0x60, 0x60, 0x06,
0x00, 0x00, 0x01, 0x79, 0xE8, 0x01, 0x9F, 0xF7, 0xFF, 0xFF, 0xFF, 0xF3, 0x00, 0x60, 0x7E, 0x06,
0x00, 0x00, 0x01, 0x70, 0xE8, 0x00, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE6, 0x00, 0x60, 0x7E, 0x06,
0x00, 0x00, 0x01, 0x66, 0x68, 0x00, 0x67, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0x00, 0x20, 0x00, 0x0E,
0x07, 0xE0, 0x01, 0x66, 0x68, 0x00, 0x23, 0xFF, 0xFF, 0xFF, 0xFF, 0x98, 0x00, 0x30, 0x00, 0x0C,
0x18, 0x18, 0x01, 0x70, 0xE8, 0x00, 0x31, 0xFF, 0xFF, 0xFF, 0xFF, 0x90, 0x00, 0x1F, 0xFF, 0xF8,
0x33, 0xC4, 0x01, 0x79, 0xE8, 0x00, 0x11, 0xFF, 0xF0, 0x3F, 0xFF, 0x10, 0x00, 0x0F, 0xFF, 0xF0,
0x67, 0xE2, 0x01, 0x7F, 0xE8, 0x00, 0x33, 0xFF, 0xC0, 0x07, 0xFF, 0x90, 0x00, 0x18, 0x00, 0x18,
0x4E, 0x71, 0x01, 0x79, 0xE8, 0x00, 0x67, 0xFF, 0x07, 0xC3, 0xFF, 0x98, 0x00, 0x30, 0x00, 0x0C,
0x5C, 0x38, 0x81, 0x70, 0xE8, 0x00, 0x47, 0xFE, 0x3C, 0x78, 0xFF, 0x8C, 0x00, 0x20, 0x00, 0x0E,
0x5D, 0xBC, 0xC1, 0x66, 0x68, 0x00, 0x47, 0xFC, 0x60, 0x0C, 0x7F, 0xC4, 0x00, 0x60, 0x00, 0x0E,
0x5C, 0x3E, 0x41, 0x66, 0x68, 0x03, 0xCF, 0xF8, 0xC0, 0x04, 0x7F, 0xC6, 0x00, 0x60, 0x18, 0x06,
0x4E, 0x7F, 0x21, 0x70, 0xE8, 0x7E, 0x0F, 0xF9, 0x80, 0x06, 0x3F, 0xC1, 0xFC, 0x60, 0x18, 0x06,
0x6F, 0xE7, 0x21, 0x79, 0xE8, 0xC0, 0x1F, 0xF1, 0x00, 0x02, 0x3F, 0xF0, 0x04, 0x60, 0x3C, 0x06,
0x27, 0xC3, 0x99, 0x7F, 0xE8, 0x8F, 0xFF, 0xF3, 0x00, 0x03, 0x1F, 0xFF, 0x04, 0x60, 0x24, 0x06,
0x13, 0x99, 0xC9, 0x79, 0xE8, 0x9F, 0xFF, 0xF2, 0x00, 0x01, 0x9F, 0xFF, 0xC4, 0x60, 0x66, 0x06,
0x19, 0x99, 0xE5, 0x70, 0xE8, 0x9F, 0xFF, 0xF2, 0x00, 0x00, 0x9F, 0xFF, 0xE4, 0x60, 0x66, 0x06,
0x06, 0xC3, 0xF3, 0x66, 0x68, 0x9F, 0xFF, 0xF2, 0x00, 0x01, 0x9F, 0xFF, 0xE4, 0x60, 0x7E, 0x06,
0x02, 0xE7, 0x31, 0x66, 0x68, 0x9F, 0xFF, 0xF2, 0x00, 0x01, 0x1F, 0xFF, 0xC4, 0x60, 0xC3, 0x06,
0x03, 0x7E, 0x18, 0x70, 0xE8, 0x8F, 0xFF, 0xF3, 0x00, 0x03, 0x1F, 0xFE, 0x04, 0x60, 0xC3, 0x06,
0x01, 0x3C, 0xCC, 0x7F, 0xE8, 0xC0, 0x1F, 0xF9, 0x00, 0x06, 0x3F, 0xF0, 0x04, 0x60, 0x81, 0x06,
0x00, 0x9C, 0xCE, 0x79, 0xE8, 0x7F, 0x8F, 0xF9, 0x80, 0x0C, 0x3F, 0xE1, 0xF8, 0x60, 0x00, 0x06,
0x00, 0xCE, 0x1F, 0x70, 0xE8, 0x00, 0x8F, 0xFC, 0xC0, 0x18, 0x7F, 0xC3, 0x00, 0x20, 0x00, 0x06,
0x00, 0x67, 0x3F, 0xB6, 0x68, 0x00, 0x87, 0xFE, 0x70, 0x30, 0xFF, 0xC6, 0x00, 0x38, 0x00, 0x0C,
0x00, 0x37, 0xF3, 0x96, 0x68, 0x00, 0xC7, 0xFF, 0x10, 0x21, 0xFF, 0xCC, 0x00, 0x0F, 0xFF, 0xF8,
0x00, 0x13, 0xE1, 0xD0, 0xE8, 0x00, 0x63, 0xFF, 0x10, 0x21, 0xFF, 0x88, 0x00, 0x0F, 0xFF, 0xF0,
0x00, 0x08, 0xCC, 0xE9, 0xE8, 0x00, 0x23, 0xFF, 0x10, 0x33, 0xFF, 0x98, 0x00, 0x18, 0x00, 0x18,
0x00, 0x04, 0xCC, 0xF7, 0xE8, 0x00, 0x33, 0xFE, 0x30, 0x13, 0xFF, 0x10, 0x00, 0x30, 0x00, 0x0C,
0x00, 0x03, 0x61, 0xFB, 0xE8, 0x00, 0x33, 0xFE, 0x20, 0x19, 0xFF, 0x10, 0x00, 0x60, 0x00, 0x06,
0x00, 0x01, 0x33, 0x9D, 0xE8, 0x00, 0xE3, 0xFC, 0x60, 0x09, 0xFF, 0x8C, 0x00, 0x60, 0x00, 0x06,
0x00, 0x01, 0x9F, 0x0C, 0xE8, 0x00, 0x87, 0xFC, 0xC0, 0x08, 0xFF, 0xC4, 0x00, 0x60, 0xF8, 0x06,
0x00, 0x00, 0x9E, 0x66, 0x68, 0x00, 0x8F, 0xFC, 0x80, 0x0C, 0x7F, 0xC6, 0x00, 0x60, 0xC4, 0x06,
0x00, 0x00, 0x4E, 0x67, 0x68, 0x01, 0x0F, 0xF8, 0x80, 0x04, 0x3F, 0xE3, 0x00, 0x60, 0xC2, 0x06,
0x00, 0x00, 0x67, 0x0F, 0xA8, 0x01, 0x1F, 0x80, 0x80, 0x06, 0x03, 0xF1, 0x00, 0x60, 0xC4, 0x06,
0x00, 0x00, 0x33, 0x9F, 0x88, 0x01, 0x1E, 0x01, 0x80, 0x03, 0x00, 0xE1, 0x00, 0x60, 0xF8, 0x06,
0x00, 0x00, 0x19, 0xF9, 0xC8, 0x01, 0x8C, 0x73, 0x00, 0x01, 0x30, 0x06, 0x00, 0x60, 0xCE, 0x06,
0x00, 0x00, 0x08, 0xF0, 0xE8, 0x00, 0xC0, 0xCE, 0x00, 0x01, 0xDC, 0x0C, 0x00, 0x60, 0xC3, 0x06,
0x00, 0x00, 0x0C, 0xE6, 0x68, 0x00, 0x71, 0x80, 0x00, 0x00, 0x07, 0x98, 0x00, 0x60, 0xC3, 0x06,
0x00, 0x00, 0x06, 0x66, 0x68, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x60, 0xC6, 0x06,
0x00, 0x00, 0x03, 0x30, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0xFC, 0x06,
0x00, 0x00, 0x01, 0x99, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x06,
0x00, 0x00, 0x00, 0x8F, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x0C,
0x00, 0x00, 0x00, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18,
0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char CSystem::loopBackScreen [1024] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0xEF, 0x88, 0xF8, 0x07, 0x3E, 0x8B, 0xEF, 0x08, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x02, 0x02, 0x1C, 0x20, 0x08, 0x20, 0xCA, 0x08, 0x9C, 0x80, 0x00, 0x00, 0x00,
0x3F, 0xFF, 0xFF, 0xFA, 0x02, 0x22, 0x20, 0x08, 0x20, 0xAA, 0x08, 0xA2, 0x81, 0xFF, 0xFF, 0xFE,
0x3F, 0xFF, 0xFF, 0xFB, 0x82, 0x22, 0x20, 0x08, 0x38, 0x9B, 0x8F, 0x22, 0x81, 0xFF, 0xFF, 0xFE,
0x20, 0x00, 0x00, 0x02, 0x02, 0x3E, 0x20, 0x09, 0xA0, 0x8A, 0x0A, 0x3E, 0x80, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x02, 0x02, 0x22, 0x20, 0x08, 0xA0, 0x8A, 0x09, 0x22, 0x80, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x03, 0xE2, 0x22, 0x20, 0x07, 0x3E, 0x8B, 0xE8, 0xA2, 0xF8, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xF9, 0xCF, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x22, 0x82, 0x08, 0x1C, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xA2, 0x82, 0x08, 0x22, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xBC, 0xE1, 0xCE, 0x22, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x20, 0x00, 0x00, 0x00, 0x00, 0x28, 0x80, 0x28, 0x3E, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x24, 0x80, 0x28, 0x22, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x22, 0xF9, 0xCF, 0xA2, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



void CSystem::oledLoopBackScreen(){
    _pDisplay->setCursor(0,0);
    _pDisplay->drawBitmap(0,0, loopBackScreen, 128,64,1);
    // _pDisplay->display();   
}


void CSystem::oledDisplayDate(){
    
    //String date;
    char date[21];
    _pDisplay->setCursor( OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_DATE);
    DateTime now = _rtc.now();
    
    // date = (String)now.day()+"/"+(String)now.month()+"/";
    // date += (String)now.year()+"   ";
    // date += (String)now.hour()+":"+ (String)now.minute()+":";
    // date += (String)now.second();  
    // _oledBlankLine(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_DATE);
    sprintf( date, "%02d/%02d/%04d  %02d:%02d:%02d", now.day(), now.month(), now.year(), now.hour(), 
    now.minute(), now.second());
  
    _pDisplay->println(date);
    // _pDisplay->display(); 
}
void CSystem::oledDisplaySate(){
    // _oledBlankLine(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_STATE); 
    _pDisplay->setCursor(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_STATE);
    String message;
    if ( _psysStat->isSystemok() ){
        // display one plug state
        message = _pPlugs[_oledCptPlugToDisplay].getPlugName();
        message += " mode ";
        message += (String)_pPlugs[_oledCptPlugToDisplay++].getMode();
        _pDisplay->println(message);
        //cpt++
        //if cpt >= plug Number => cpt =0
        if ( _oledCptPlugToDisplay >= _pcParam->getNumberOfPlugs() ){
            _oledCptPlugToDisplay =0;
        }
    } else {
        // how to display many errors
        // cpt = _psysStat->howManyError
        // display oneError and cpt--
        //if cpt = 0 reload
        if ( _oledCptErrToDisplay = 0 ) _oledCptErrToDisplay = _psysStat->howManyError();
        if ( _psysStat->fsErr.isErr() ){
            message = _psysStat->fsErr.getMsg();
        }
    }
    // _pDisplay->println("STATE: XYZW");

    
}
void CSystem::oledDisplayIps(){
    // _oledBlankLine(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_LAN_IPADD);
    _pDisplay->setCursor(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_LAN_IPADD);
    _pDisplay->println("LAN:" + WiFi.localIP().toString() );
    // _oledBlankLine(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_AP_IPADD);
    _pDisplay->setCursor(OLED_XPOS_STARTLIGN, OLED_YPOS_FOR_AP_IPADD);
    _pDisplay->println(" AP:" + WiFi.softAPIP().toString() );
     
}

void CSystem::oledLoopChangeDispayIf(){
    DEFDPROMPT( "CSystem::oledLoopChangeDispayIf" )
    if ( millis() - _oledPrevMillis > _oledRefreshPeriod*1000 ){
        _oledPrevMillis = millis();
        _pDisplay->clearDisplay();

        oledLoopBackScreen();  
        
        oledDisplayDate();
        oledDisplayIps();
        //do the job here

        oledDisplaySate();
        

        _pDisplay->display();
    
        
    }   
}



/**
 @fn void CSystem::init( WiFiUDP &ntpUDP, CSysStatus *psysStat, FS *pFileSyst, ConfigParam *pcParam,
                    const String *necessaryFlLst, int necessaryFileNbr, String buildinfo
                    , ESP8266WiFiClass *pWifi, CNanoI2CIOExpander *pNanoioExp
                    , Adafruit_SSD1306 *pdisplay )
 @brief IoT_EPS system init method
 @param ntpUDP just for NTPClient init, this parameter is not kept
 @param psysStat a pointer on global variable sysStatus
 @param pFileSyst a pointer on the file system
 @param pcParam a pointer on the cParm class instance
 @param necessaryFlLst a pointer on the necessary list files
 @param necessaryFileNbr a many necessary files
 @param buildinfo as ti says
 @param pWifi a pointer on the wifi class connection
 @param pNanoioExp a pointer on the instance of nano io expension
 @param pdisplay a pointer on the oled display
 @return no return val

Start RTc DS3231 and nothing else @25/09/2020. With all this pointers Csysteminstance can inteeract
with almost all components in the system.
*/
void CSystem::init( WiFiUDP &ntpUDP, CSysStatus *psysStat, FS *pFileSyst, ConfigParam *pcParam,
                    const String *necessaryFlLst, int necessaryFileNbr, String buildinfo
                    , ESP8266WiFiClass *pWifi, CNanoI2CIOExpander *pNanoioExp
                    , Adafruit_SSD1306 *pdisplay
                     ){

    DEFDPROMPT( "CSystem::init" )

    String message;
    String date;

    _psysStat = psysStat;
    _pFileSystem = pFileSyst;
    _pcParam = pcParam;
    _pNecessaryFiles = necessaryFileList;
    _pDisplay = pdisplay;
    
    delay(1000);//a try to correct the powerup pb
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite( LED_BUILTIN, LOW ); //warning D4 BP bleue plug
    delay(1000);
    digitalWrite( LED_BUILTIN, HIGH ); //warning D4 BP bleue plug
    pinMode(LED_BUILTIN, INPUT);

    DSPL();
    DSPL( dPrompt + F("Sketch start..."));
    pinMode( BP1, INPUT_PULLUP );

    /////////////////////////////////////////////////////////////////////////////
    //     file system check                                                   //
    /////////////////////////////////////////////////////////////////////////////
    DSPL( dPrompt + " Build : " + buildinfo );
    _psysStat->fsErr.err( !_pFileSystem->begin() ); 
    DSPL( dPrompt + F("File system correctly Open @ setup level") );

    /////////////////////////////////////////////////////////////////////////////
    //     Special Actions                                                     //
    /////////////////////////////////////////////////////////////////////////////
    if ( !(digitalRead(BP1) ) ){ // green PB
        DSPL( dPrompt + F("Special action take place..." ) );
        // place special actions here
        // example sysStatus._forceSystemStartOnFatalError = true;
        _pcParam->creatDefaultJson();
    }

    /////////////////////////////////////////////////////////////////////////////
    //  Start of the check necessary files  presence                           //
    /////////////////////////////////////////////////////////////////////////////
    DSPL(dPrompt + F("File check !") );
    bool fileExist = true;
    for ( int i = 0; i < necessaryFileNbr; i++){
        String s = necessaryFlLst[i];
        bool b = _pFileSystem->exists(s);
        fileExist &= b;
        DSPL( dPrompt + F("file : ") + s + F(" is ") + (b?F("present"):F("not found")) );
    }
    DSPL( dPrompt + F("Result all files are present ? ") + (fileExist?"OK":"ERROR") );
    _psysStat->filesErr.err( !fileExist );

    /////////////////////////////////////////////////////////////////////////////
    //     Config param check                                                  //
    /////////////////////////////////////////////////////////////////////////////
    _pcParam->begin();
    _psysStat->confFileErr.err( !_pcParam->ready );
    DSPL( dPrompt + F("json mac add : ") + _pcParam->getMacAdd() );
    DSPL( dPrompt + F("Board Sation MAC add = ") + pWifi->macAddress() );
    if ( _pcParam->getMacAdd() == pWifi->macAddress() ) DSPL( dPrompt + "Station equal add");
    else {
        DSPL( dPrompt + "diff add, write to json");
        _pcParam->write2Json( "macAdd", pWifi->macAddress() );
    }
    DSPL( dPrompt + F("json Soft AP mac add : ") + _pcParam->getSoftAPMacAdd() );
    DSPL( dPrompt + F("Board Soft AP MAC add = ") + pWifi->softAPmacAddress() );
    if ( _pcParam->getSoftAPMacAdd() == pWifi->softAPmacAddress() ) DSPL( dPrompt + "AP equal add");
    else {
        DSPL( dPrompt + "diff add, write to json");
        _pcParam->write2Json( "softAP_macAdd", pWifi->softAPmacAddress() );
    }
    /////////////////////////////////////////////////////////////////////////////
    //     I2C bus check                                                       //
    ///////////////////////////////////////////////////////////////////////////// 
    CNano::init();
    DSPL( dPrompt+ F("I2C test start") );
    int cpt = 1;
    do{
        if ( !pNanoioExp->test() ){
            DSPL( dPrompt + "i2cRecov" + " number " + cpt);
            SerialCommand::i2c_recovery();
        } else cpt = 9;
        
        cpt++;
    } while (cpt < I2C_RETRIES );
    if (cpt != 10) _psysStat->nanoErr.err( true );
    DSPL(dPrompt + F("Nano test ok"));

    /////////////////////////////////////////////////////////////////////////////
    //     OLED Start message                                                    //
    /////////////////////////////////////////////////////////////////////////////
    DSPL(dPrompt + F("Display oled Logo"));
    _oledStartMessagesManager();



    /////////////////////////////////////////////////////////////////////////////
    //     rtc DS3231 start                                                    //
    /////////////////////////////////////////////////////////////////////////////
    
    _pTimeclient = new NTPClient(ntpUDP, NTPSERVER);
    _pTimeclient->setTimeOffset( OFFSET_HEURE * SECPERHOURS );
    _rtc.begin( _pTimeclient );
    _psysStat->rtcErr.err( _rtc.initErr );
    if (_rtc.lostPower()){
        DSPL( dPrompt + F("une remise a l'heure est necessaire") );
    }
    DateTime now = _rtc.now();
    message = dPrompt + F("DS3231 Start date : ");
    date = (String)now.day()+"/"+(String)now.month()+"/";
    date += (String)now.year()+" ";
    date += (String)now.hour()+":"+ (String)now.minute()+":";
    date += (String)now.second();  
    message += date;    
    DSPL( message);

    /////////////////////////////////////////////////////////////////////////////
    //     OLED check messages                                                 //
    /////////////////////////////////////////////////////////////////////////////    
    _pDisplay->setCursor(0,0);
    _pDisplay->println(DS3231_START_DATE);
    _pDisplay->println(date);
    _pDisplay->println();
    _pDisplay->println(AT_THIS_POINT);
    _pDisplay->println("* I2C ok"); //L5
    _pDisplay->println(OLED_FILE_SYSTEM_OK);
    _pDisplay->println(OLED_CONFIG_PARAM_OK );

    _pDisplay->display();
    delay(5000);
    _pDisplay->clearDisplay();
    _pDisplay->setCursor(0,0);
    _pDisplay->display();
    _oledRefreshPeriod = OLED_REFRESH_PERIOD;
    _oledPrevMillis = millis();                    

    _oledCptPlugToDisplay = 0;
    
        
}


/**
 @fn void CSystem::timeServerCheck()
 @brief IoT_EPS Check time server access
 @return not param and no return value

Need to be called after Wifi init cause _psysStat->ntpEnabled set by Wifi link
*/
void CSystem::timeServerCheck(){
    /////////////////////////////////////////////////////////////////////////////
    //  Time server check                                                     //
    /////////////////////////////////////////////////////////////////////////////
    // if ((wifi is on station mode connected))
    int timeZone = OFFSET_HEURE;
    DateTime NTPTime;
    DEFDPROMPT( "CSystem::timeServerCheck" )

    if( _psysStat->ntpEnabled){
        DSPL(dPrompt + F("check started") );
        _pTimeclient->begin();

        _psysStat->ntpErr.err( !_pTimeclient->forceUpdate() ) ;
        if ( !_psysStat->ntpErr.isErr() ){
            _pTimeclient->setTimeOffset( timeZone * SECPERHOURS );
            // setTime(  timeClient.getEpochTime() );
            NTPTime = DateTime( _pTimeclient->getEpochTime() );
            String sDate = "";
            sDate += (String)NTPTime.day() +"/"+(String)NTPTime.month()+"/"+(String)NTPTime.year()+" ";
            sDate += (String)NTPTime.hour()+":"+(String)NTPTime.minute()+":";
            sDate += (String)NTPTime.second();
            DSPL( dPrompt + "NTP Time : " + sDate );
            _pDisplay->println("NTP Time");
            _pDisplay->println(sDate);
            _pDisplay->display();
            
            if (_rtc.lostPower()){
                RTC_DS3231::adjust( NTPTime );
                DSPL( dPrompt + F("DS3231 set to NTP time due to power lost.") );
                // CRtc::displayTime();
            }
            _pcParam->write2Json( "ntpError", "OFF" );
        } else { 
            DSPL( dPrompt +"NTP ERROR");
            _pcParam->write2Json( "ntpError", "ON" ); }
    }    
}

void CSystem::_oledStartMessagesManager(){
    DEFDPROMPT( "CSystem::init:Stratup Messages" )
    _pDisplay->drawBitmap(0,0, CSystem::logoLab, 128, 64, 1 );
    _pDisplay->display();
    DSPL( dPrompt + F("OLED Logo pause") );
    delay(OLED_LOGO_DISPLAY_TEMPO);
    _pDisplay->clearDisplay();
    _pDisplay->setTextSize(1);
    _pDisplay->setTextColor(WHITE);
    _pDisplay->setCursor(0,0);
    _pDisplay->println(PROVIDER_NAME);
    _pDisplay->println();
    _pDisplay->println(EPS_NAME1);
    _pDisplay->println(EPS_NAME2);
    _pDisplay->println(EPS_NAME3);
    _pDisplay->display();
    DSPL( dPrompt +F("OLED startup message pause") );
    delay(OLED_STARTUP_MESSAGE_TEMPO);
    _pDisplay->clearDisplay();
    _pDisplay->display();

}



