#include <Arduino.h>
#include <ssd1306xled.h>

/*-------------------------------------------------------*/
bool isLeftPressed()
{
  uint16_t inputX = analogRead( A0 );
  return( ( inputX >= 750 ) && ( inputX < 950 ) );
}

/*-------------------------------------------------------*/
bool isRightPressed()
{
  uint16_t inputX = analogRead( A0 );
  return( ( inputX > 500 ) && ( inputX < 750 ) );
}

/*-------------------------------------------------------*/
bool isUpPressed()
{
  uint16_t inputY = analogRead( A3 );
  return( ( inputY > 500 ) && ( inputY < 750 ) );
}

/*-------------------------------------------------------*/
bool isDownPressed()
{
  uint16_t inputY = analogRead( A3 );
  return( ( inputY >= 750 ) && ( inputY < 950 ) );
}

/*-------------------------------------------------------*/
bool isFirePressed()
{
  return( digitalRead( 1 ) == 0 );
}

/*-------------------------------------------------------*/
// This code was borrowed from Daniel C's Tiny-invaders :)
void Sound( uint8_t freq, uint8_t dur ){
  for ( uint8_t t = 0; t < dur; t++ ){
    if ( freq!=0 ){ PORTB = PORTB|0b00010000; }
    for ( uint8_t t = 0; t < ( 255 - freq ); t++ ){
      _delay_us(1);
    }
    PORTB = PORTB&0b11101111;
    for ( uint8_t t = 0; t < ( 255 - freq ); t++ ){
      _delay_us(1);
    }
  }
}
