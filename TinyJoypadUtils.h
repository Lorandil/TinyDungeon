#pragma once

#include <Arduino.h>

#if defined(__AVR_ATtiny85__)
  #define LEFT_RIGHT_BUTTON A0
  #define UP_DOWN_BUTTON    A3
  #define FIRE_BUTTON        1
#else
  #define LEFT_RIGHT_BUTTON A0
  #define UP_DOWN_BUTTON    A3
  #define FIRE_BUTTON       A1
#endif

bool isLeftPressed();
bool isRightPressed();
bool isUpPressed();
bool isDownPressed();
bool isFirePressed();
void _variableDelay_us( uint8_t delayValue );
void Sound( const uint8_t freq, const uint8_t dur );
