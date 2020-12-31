#ifndef _BITMAP_DRAWING_H_
#define _BITMAP_DRAWING_H_

#include "dungeonTypes.h"

uint8_t __attribute__ ((always_inline)) getWallPixels( DUNGEON *dungeon, const int8_t x, const int8_t y );
uint8_t getDownScaledBitmapData( uint8_t x, uint8_t y, const uint8_t scaleFactor, 
                                 const uint8_t *bitmapData, const uint8_t bitmapWidth );
#endif
