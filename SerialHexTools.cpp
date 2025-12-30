#if !defined(__AVR_ATtiny85__)

#include <Arduino.h>
#if defined(__AVR__)
  #include <EEPROM.h>
#endif
#include "SerialHexTools.h"

/*--------------------------------------------------------------*/
void hexdumpResetPositionCount() 
{ 
  hexdumpPositionCount = 0; 
}

/*--------------------------------------------------------------*/
char getHexChar( const uint8_t value )
{
  return ( value < 10 ) ? '0' + value
                        : 'A' + value - 10;
}

/*--------------------------------------------------------------*/
// just print a byte to the serial console (with leading zero)
void printHexToSerial( uint8_t value, bool addComma /*= false*/, bool autoLineBreak /*= false*/ )
{
  static uint8_t count = 0;

  char hexString[5];
  memcpy_P( hexString, F("0x00"), 5 );
  hexString[2] = getHexChar( value >> 4 );
  hexString[3] = getHexChar( value & 0x0F );
  Serial.print( hexString );
  
  if ( addComma )
  {
    Serial.print( F(", ") );
  }

  if ( autoLineBreak )
  {
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
}

/*--------------------------------------------------------------*/
// simple hexdump from RAM
void hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( pData[n], ( n < byteCount - 1 ) || finalComma, true );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}

#if defined(__AVR__)
/*--------------------------------------------------------------*/
// simple hexdump from EEPROM
void EEPROM_hexdumpToSerial( uint16_t startAddress, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( EEPROM.read( startAddress + n ), ( n < byteCount - 1 ) || finalComma, true );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}
#endif

/*--------------------------------------------------------------*/
// simple hexdump from PROGMEM
void pgm_hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma, bool finalLinebreak )
{
  for ( uint16_t n = 0; n < byteCount; n++ )
  {
    printHexToSerial( pgm_read_byte( pData + n ), ( n < byteCount - 1 ) || finalComma, true );
  }
  
  // insert line break if necessary
  if ( finalLinebreak )
  {
    Serial.println();
  }
}

/*--------------------------------------------------------------*/
// print rotated 1 bit image buffer to serial as an 8 bit hexdump
void printScreenBufferToSerial( const uint8_t *buffer, const uint8_t widthInPixels, const uint8_t heightInBytes )
{
  for ( int x = 0; x < widthInPixels; x++ )
  {
    for ( int y = 0; y < heightInBytes; y++ )
    {
      uint8_t value = buffer[y * widthInPixels + x];
      // now convert to 8bpp
      for ( int n = 0; n < 8; n++ )
      {
        if ( value & ( 1 << n ) )
          { Serial.print( F("0xFF,") ); }
        else
          { Serial.print( F("0x00,") ); }
      }
    }
    Serial.println();
  }
}

#endif
