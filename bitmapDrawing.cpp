#include <Arduino.h>
#include "Dungeon.h"
#include "dungeonTypes.h"
#include "spritebank.h"
#include "bitmapDrawing.h"
#include "bitTables.h"

/*--------------------------------------------------------*/
uint8_t getWallPixels( DUNGEON *dungeon, const int8_t x, const int8_t y )
{
  uint8_t pixels = 0;

  SIMPLE_WALL_INFO wallInfo;
  
  const SIMPLE_WALL_INFO *wallInfoPtr = arrayOfWallInfo;

  // all objects are visible
  int8_t maxObjectDistance = 4;

  // iterate through the whole list (at least as long as it's necessary)
  while( true )
  {
    // the structure resides in PROGMEM, so we need to copy it to RAM first...
    memcpy_P( &wallInfo, wallInfoPtr, sizeof( wallInfo ) );

    // end of list reached?
    if ( wallInfo.wallBitmap == NULL ) { break; }

    // check conditions
    if ( ( x >= wallInfo.startPosX ) && ( x <= wallInfo.endPosX ) )
    {
      // is there a wall object?
      if ( ( *( getCell( dungeon, dungeon->playerX, dungeon->playerY, wallInfo.viewDistance, wallInfo.leftRightOffset, dungeon->dir ) ) & WALL_MASK ) == wallInfo.objectMask )
      {
        // mirror walls on odd fields
        uint8_t offsetX = ( ( dungeon->playerX + dungeon->playerY ) & 0x01 ) ? 95 - x : x;
        // get wall pixels
        pixels = pgm_read_byte( wallInfo.wallBitmap + y * 96 + offsetX );
        // objects behind walls not invisible, but doors or switched might be placed *on* walls
        maxObjectDistance = wallInfo.viewDistance;
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }

  NON_WALL_OBJECT object;

  // draw NWOs (Non Wall Objects) over the wall pixls (with mask!)
  for ( uint8_t d = maxObjectDistance; d > 0; d-- )
  {
    uint8_t objectSize = 32 >> d;
   
    for ( uint8_t n = 0; n < sizeof( objectList ) / sizeof( objectList[0] ); n++ )
    {
      // centered?
      if ( ( x >= 48 - objectSize ) && ( x < 48 + objectSize ) )
      {
        memcpy_P( &object, &objectList[n], sizeof( object ) );
        
        if ( ( *( getCell( dungeon, dungeon->playerX, dungeon->playerY, d, 0, dungeon->dir ) ) & OBJECT_MASK ) == object.itemType )
        {
          if ( d == 3 )
          {
            d++;
          }
          objectSize = 48 - objectSize;
          pixels &= getDownScaledBitmapData( x - objectSize, y, d, object.itemBitmap + object.maskOffset, object.nextLineOffset );
          pixels |= getDownScaledBitmapData( x - objectSize, y, d, object.itemBitmap, object.nextLineOffset );
        }
      }
    }
  }
  
  return( pixels );
}

/*--------------------------------------------------------*/
// Returns the downscaled bitmap data at position x,y.
// Supported scaling values are 1, 2, 4
uint8_t getDownScaledBitmapData( uint8_t x, uint8_t y, const uint8_t scaleFactor, 
                                 const uint8_t *bitmapData, const uint8_t bitmapWidth )
{
  uint8_t pixels = 0;

  // modify positions in source bitmap by scaling factor
  x = x * scaleFactor;
  y = y * scaleFactor;

  // create appropriate bit mask
  uint8_t bitMask = ( scaleFactor << 1 ) - 1;

  // calculate start address
  const uint8_t *data = bitmapData + y * bitmapWidth + x;

  // first bit to be processed
  uint8_t bitNo = 0;

  // We need to calculate 8 vertical output bits...
  // NOTE: Because the Tiny85 only supports shifting by 1 bit, it is
  //       more efficient to do the shifting in the 'for' loop instead
  //       of using a ( 1 << n ) construct.
  for ( uint8_t bitValue = 1; bitValue != 0; bitValue <<= 1 )
  {
    uint8_t bitSum = 0;

    // go over the rows...
    for ( uint8_t row = 0; row < scaleFactor; row++ )
    {
      // but first the columns
      for ( uint8_t col = 0; col < scaleFactor; col++ )
      {
        // to get the output value, we will sum all the bits up (using a lookup table saves time and flash space)
        bitSum += pgm_read_byte( nibbleBitCount + ( ( pgm_read_byte( data++ ) >> bitNo ) & bitMask ) );
      }
      // correct the post increments from before
      data -= scaleFactor;
    }

    // next bit position
    bitNo += scaleFactor;

    if ( bitNo >= 8 )
    {
      // a new byte will begin...
      bitNo = 0;
      // address next 8-pixel row
      data += bitmapWidth;
    }

    // calculate output pixel
    if ( bitSum >= bitMask )
    {
      pixels |= bitValue;
    }
  }

  return( pixels );  
}
