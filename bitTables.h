#ifndef _BIT_TABLES_H_
#define _BIT_TABLES_H_

// some simple tables to save time and code

#include <Arduino.h>

// Table of '1' bits in a nibble.
const uint8_t nibbleBitCount[16] PROGMEM =
{
  0, // 0b0000
  1, // 0b0001
  1, // 0b0010
  2, // 0b0011
  1, // 0b0100
  2, // 0b0101
  2, // 0b0110
  3, // 0b0111
  1, // 0b1000
  2, // 0b1001
  2, // 0b1010
  3, // 0b1011
  2, // 0b1100
  3, // 0b1101
  3, // 0b1110
  4, // 0b1111
};

// Conversion table from view distance to scaling factor.
// A distance of '0' is undefined but simplies adressing.
const uint8_t scalingFactorFromDistance[] PROGMEM =
{
  0, 1, 2, 4,
};

// Conversion table from scaling factor to bit mask.
// A factor of '0' is undefined but simplies adressing.
const uint8_t bitMaskFromScalingFactor[] PROGMEM =
{
//    -     1     2     -       4 
    0x00, 0x01, 0x03, 0x00  , 0x0F,
};

#endif
