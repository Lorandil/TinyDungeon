#if !defined(__AVR_ATtiny85__)

#include <Arduino.h>
#include <EEPROM.h>
#include "SerialHexTools.h"

/*--------------------------------------------------------------*/
void hexdumpResetPositionCount() 
{ 
  hexdumpPositionCount = 0; 
}

/*--------------------------------------------------------------*/
// just print a byte to the serial console (with leading zero)
void printHexToSerial( uint8_t value, bool addComma )
{
  static uint8_t count = 0;

  Serial.print("0x"); 
  if ( value < 0x10 )
  {
    Serial.print("0");
  }
  Serial.print( value, HEX );
  if ( addComma )
  {
    Serial.print(", ");
  }

  // increase count
  hexdumpPositionCount++;
  // maximum reached?
  if ( hexdumpPositionCount >= hexdumpValuesPerLine )
  {
    // reset count
    hexdumpPositionCount = 0;
    // insert line break
    Serial.println();
  }
}

/*--------------------------------------------------------------*/
// simple hexdump from RAM
void hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( pData[n], ( n < byteCount - 1 ) || finalComma );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}

/*--------------------------------------------------------------*/
// simple hexdump from EEPROM
void EEPROM_hexdumpToSerial( uint16_t startAddress, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( EEPROM.read( startAddress + n ), ( n < byteCount - 1 ) || finalComma );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}

/*--------------------------------------------------------------*/
// simple hexdump from PROGMEM
void pgm_hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( pgm_read_byte( pData + n ), ( n < byteCount - 1 ) || finalComma );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}

#endif
