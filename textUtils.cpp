#include <Arduino.h>
#include <avr/pgmspace.h>
#include "textUtils.h"
#include "bitTables.h"
#include "smallFont.h"

/*--------------------------------------------------------------*/
// Converts 'value' to 5 decimal digits
// Not the most elegant version, but the shortest for uint16_t
void convertValueToDigits( uint16_t value, uint8_t *digits )
{
  static uint16_t dividerList[] = { 10000, 1000, 100, 10, 1, 0 };

  uint16_t *divider = dividerList;

  // wait for the first divider which is smaller than the value
  while ( *divider > value ) { divider++; }
  // if we reach zero, the divider pointer has to be reset to '1'
  if ( value == 0 ) { divider = &dividerList[4]; }
  
  do
  {
    uint8_t digit = '0';
    while( value >= *divider )
    {
      digit++;
      value -= *divider;
    }
    // store digit
    *digits++ = digit;
    // next divider
    divider++;
  }
  while ( *divider != 0 );
}

/*--------------------------------------------------------------*/
// Displays a line of ASCII character from the smallFont in the 
// top line of the screen. To save flash memory, the font ranges
// only from '0' to 'Z'.
uint8_t displayText( uint8_t x, uint8_t y )
{
  // find appropriate character in text array (font width is 4 px)
  uint8_t value = textBuffer[y * 8 + ( x >> 2 )];
  // is it a valid character?
  if ( value != 0 )
  {
    // get the column value
    return( pgm_read_byte( characterFont3x5 + ( ( value - '0' ) << 2 ) + ( x & 0x03) ) );
  }
}

/*--------------------------------------------------------------*/
// Display zoomed ASCII character from the smallFont in four
// lines of 16 characters. The zoom factor is fixed to '2'.
// If bit 7 is set, the character will be displayed inverted.
// To save flash memory, the font ranges only from '0' to 'Z'.
uint8_t displayZoomedText( uint8_t x, uint8_t y )
{
  // Find appropriate character in text array:
  // Font width is 4 px, zoom is 2x, so fetch a new character every 8 pixels
  uint8_t value = textBuffer[((y >> 1) << 4) + ( x >> 3)];
  // is it a valid character?
  if ( value != 0 )
  {
    // MSB set? -> inverse video
    uint8_t reverse = value & 0x80;
    // remove MSB from value
    value -= reverse;
    // return the column value (move the font 1 pixel down, lowest pixel returns at the top)
    value = ( pgm_read_byte( characterFont3x5 + ( ( value - '0' ) << 2 ) + ( ( x >> 1 ) & 0x03 ) ) );
    if ( ( y & 0x01 ) == 0 )
    {
      // upper line
      value = ( pgm_read_byte( nibbleZoom + ( value & 0x0f ) ) );
    }
    else
    {
      // lower line
      value = ( pgm_read_byte( nibbleZoom + ( value >> 4 ) ) );
    }
    // invert?
    if ( reverse )
    {
      // invert pixels
      value = value ^ 0xff;
    }
    return( value );
  }

  // Please move along, there is nothing to be seen here...
  return( 0x00 );
}

/*--------------------------------------------------------------*/
void clearTextBuffer()
{
  memset( textBuffer, 0x00, sizeof( textBuffer ) );
#if !defined(__AVR_ATtiny85__)
  for ( auto n = 0; n < sizeof( textBuffer ); n++ )
  {
    auto value = textBuffer[n];
    Serial.write( value == 0 ? '_' : value );
  }
  Serial.println();
#endif
}

/*--------------------------------------------------------------*/
void printText( uint8_t x, uint8_t *text, uint8_t textLength )
{
  memcpy( textBuffer + x, text, textLength );
}

/*--------------------------------------------------------------*/
void pgm_printText( uint8_t x, uint8_t *text, uint8_t textLength )
{
  memcpy_P( textBuffer + x, text, textLength );

#if !defined(__AVR_ATtiny85__)
  for ( auto n = 0; n < sizeof( textBuffer ); n++ )
  {
    auto value = textBuffer[n];
    Serial.write( value == 0 ? '_' : value );
  }
  Serial.println();
#endif
}

/*--------------------------------------------------------------*/
uint8_t *getTextBuffer()
{
  return( textBuffer );
}
