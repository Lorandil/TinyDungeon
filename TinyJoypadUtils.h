#ifndef _TINY_JOYSTICK_
#define _TINY_JOYSTICK_

bool isLeftPressed();
bool isRightPressed();
bool isUpPressed();
bool isDownPressed();
bool isFirePressed();
void _variableDelay_us( uint8_t delayValue );
void Sound( const uint8_t freq, const uint8_t dur );

#endif
