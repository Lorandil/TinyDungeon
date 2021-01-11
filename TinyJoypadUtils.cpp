//
// This file works for TinyJoypad compatible devices.
//
// If not compiled for ATTiny85 (meaning __AVR_ATtiny85__ is not defined),
// generic functions are used instead of direct port access, which 
// makes it possible to use an Arduino or Mega2560 (or many others)
// for debugging with serial output or even hardware breakpoints.
//

#include <Arduino.h>
#include "tinyJoypadUtils.h"

// required for _delay_us()
#include <ssd1306xled.h>

/*-------------------------------------------------------*/
bool isLeftPressed()
{
  uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
  return( ( inputX >= 750 ) && ( inputX < 950 ) );
}

/*-------------------------------------------------------*/
bool isRightPressed()
{
  uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
  return( ( inputX > 500 ) && ( inputX < 750 ) );
}

/*-------------------------------------------------------*/
bool isUpPressed()
{
  uint16_t inputY = analogRead( UP_DOWN_BUTTON );
  return( ( inputY > 500 ) && ( inputY < 750 ) );
}

/*-------------------------------------------------------*/
bool isDownPressed()
{
  uint16_t inputY = analogRead( UP_DOWN_BUTTON );
  return( ( inputY >= 750 ) && ( inputY < 950 ) );
}

/*-------------------------------------------------------*/
bool isFirePressed()
{
  return( digitalRead( FIRE_BUTTON ) == 0 );
}

/*-------------------------------------------------------*/
void _variableDelay_us( uint8_t delayValue )
{
  while ( delayValue-- != 0 )
  {
    _delay_us( 1 );
  }
}

/*-------------------------------------------------------*/
// This code was originaly borrowed from Daniel C's Tiny-invaders :)
// Code optimization by sbr
void Sound( const uint8_t freq, const uint8_t dur )
{
  for ( uint8_t t = 0; t < dur; t++ )
  {
    if ( freq!=0 ){ PORTB = PORTB|0b00010000; }
    _variableDelay_us( 255 - freq );
    PORTB = PORTB&0b11101111;
    _variableDelay_us( 255 - freq );
  }
}
