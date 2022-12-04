#include "soundFX.h"

#if defined(__AVR_ATtiny85__)
  // required for _delay_us()
  #include <util/delay.h>
#endif

/*--------------------------------------------------------*/
void stepSound()
{
  Sound( 100,1 );
  Sound( 200,1 );
  _delay_ms( 100 );
}

/*--------------------------------------------------------*/
void wallSound()
{
  Sound( 50,1 );
  _delay_ms( 100 );
}

/*--------------------------------------------------------*/
void swordSound()
{
  Sound( 50,10 );
}
