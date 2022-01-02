#pragma once

#include <Arduino.h>

// Video text memory:
// - one line (of 32 characters) in standard mode,
// - four lines (of 16 characters) in zoomed mode
static uint8_t textBuffer[64];

// convert value to decimal numbers
void     convertValueToDigits( uint8_t value, uint8_t *digits );

// display functions (and helpers)
uint8_t  displayText( uint8_t x,uint8_t y );
uint8_t  displayZoomedText( uint8_t x, uint8_t y );
void     clearTextBuffer();
void     printText( uint8_t x, uint8_t *text, uint8_t textLength );
void     pgm_printText( uint8_t x, uint8_t *text, uint8_t textLength );
uint8_t *getTextBuffer();
