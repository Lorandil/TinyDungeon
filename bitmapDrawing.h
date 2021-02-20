#ifndef _BITMAP_DRAWING_H_
#define _BITMAP_DRAWING_H_

#include "dungeonTypes.h"

uint8_t __attribute__ ((always_inline)) getWallPixels( DUNGEON *dungeon, const int8_t x, const int8_t y );

uint8_t getDownScaledBitmapData( int8_t x, int8_t y, 
                                 const uint8_t distance, const NON_WALL_OBJECT *object,
                                 bool useMask );
#endif
