#include <Arduino.h>

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
