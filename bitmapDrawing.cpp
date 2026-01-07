#include "bitTables.h"
#include "dungeon.h"
#include "monsterBitmaps.h"
#include "objectBitmaps.h"
#include "wallBitmaps.h"
#include "TinyJoypadUtils.h"

/*--------------------------------------------------------*/
uint8_t Dungeon::getLightingMask( const uint8_t &viewDistance )
{
  return( pgm_read_byte( lightingTable + _dungeon.lightingOffset + viewDistance ) );
}

/*--------------------------------------------------------*/
// Processes a complete vertical column at position x
void Dungeon::renderDungeonColumn( const uint8_t x )
{
  memset( _dungeon.lineBuffer, 0, sizeof( _dungeon.lineBuffer ) / sizeof(_dungeon.lineBuffer[0] ) );

  // here is what we're gonna do:
  // - find the frontmost wall in this column and determine the max. view distance
  // start a y-loop
  //   - get the wall pixels and apply shading (if enabled)
  //   - place all visible NWOs (Non Wall Objects) over the wall pixels from back to front and apply shading

  SIMPLE_WALL_INFO wallInfo;
  const SIMPLE_WALL_INFO* wallInfoPtr = arrayOfWallInfo;

  // all objects are visible
  int8_t maxObjectDistance = MAX_VIEW_DISTANCE;

  // iterate through the whole list (at least as long as it's necessary)
  while( true )
  {
    // the structure resides in PROGMEM, so we need to copy it to RAM first...
    memcpy_P( &wallInfo, wallInfoPtr, sizeof( wallInfo ) );

    // end of list reached?
    if ( wallInfo.wallBitmap == nullptr ) { break; }

    // check conditions
    if ( ( x >= wallInfo.startPosX ) && ( x <= wallInfo.endPosX ) )
    {
      // use mirror effect depending on position and orientation to create walking illusion (this works quite well!)
      bool mirror = ( ( _dungeon.playerX + _dungeon.playerY +_dungeon.dir ) & 0x01 );

      // is there a wall object?
      if ( ( *( getCellRaw( _dungeon.playerX, _dungeon.playerY, wallInfo.viewDistance, wallInfo.leftRightOffset, _dungeon.dir ) ) & WALL_MASK ) == ( WALL & ~FLAG_SOLID ) )
      {
        // split combined positions into start and end
        int8_t startPosY = wallInfo.posStartEndY >> 4;
        int8_t endPosY = wallInfo.posStartEndY & 0x0f;
        int8_t sizeY = endPosY - startPosY + 1;

        // positions are to be considered relative to the bitmap
        int8_t posX = x - wallInfo.startPosX;

        // calculate the x offset depending on the mirror flag
        uint8_t offsetX = mirror ? wallInfo.width - 1 - posX - wallInfo.relPos
                                 : posX + wallInfo.relPos;
        
        // copy wall data to the right position
        const uint8_t *bitmapData = wallInfo.wallBitmap + offsetX * sizeY;
        uint8_t *buffer = _dungeon.lineBuffer + startPosY;
        while ( sizeY-- )
        {
          uint8_t pixels = pgm_read_byte( bitmapData++ );
        #ifdef _ENABLE_WALL_SHADING_
          // TODO: this could be optimized further:
          // - integrate shading into wall bitmaps
          // - or use simple 'if ( wallInfo.viewDistance > 2 )...' instead of switch statement
          // - OR use lookup table for dynamic lighting!
          //uint8_t lightMask = pgm_read_byte( lightingTable + _dungeon.lightingOffset + wallInfo.viewDistance * 2 + ( x & 0x01 ) );
          *buffer++ = pixels & getLightingMask( wallInfo.viewDistance * 2 + ( x & 0x01 ) );
        #else
          *buffer++ = pixels;
        #endif
        }

        // objects behind walls are not visible, but doors or switches might be placed *on* walls
        maxObjectDistance = wallInfo.viewDistance;
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }

  NON_WALL_OBJECT object;

  uint8_t cellValue;

  // draw NWOs (Non Wall Objects) over the background pixels (with mask!)
  for ( uint8_t distance = maxObjectDistance; distance > 0; distance-- )
  {
    for ( uint8_t n = 0; n < sizeof( objectList ) / sizeof( objectList[0] ); n++ )
    {
      memcpy_P( &object, &objectList[n], sizeof(object) );
      uint8_t objectWidth = object.bitmapWidth >> distance;

      // offset table for center positions at the corresponding distance
      const int8_t* offsets = objectCenterPositions + distance * objCenterPosPerLine;

      // start at the leftmost position
      int8_t leftRightOffset = objCenterPosStartOffset;

      // try to find the correct column
      while ( leftRightOffset <= objCenterPosEndOffset )
      {
        int8_t offset = pgm_read_byte( offsets );
        // is this a valid place for the object?
        if ( ( x >= offset - objectWidth ) && ( x < offset + objectWidth ) )
        {
          // is there such an object at the target position?
          cellValue = *( getCellRaw( _dungeon.playerX, _dungeon.playerY, distance, leftRightOffset, _dungeon.dir ) );
          if ( ( cellValue & OBJECT_MASK ) == object.itemType )
          {
            // some objects must not be visibile from orthogonal directions
            if ( cellValue & FLAG_LIMITED_VISIBILITY )
            {
              // forbidden direction?
              if ( ( cellValue & LIMITED_VISIBILITY_MASK ) == ( _dungeon.dir & LIMITED_VISIBILITY_MASK ) )
              {
                // not visible
                break;
              }
            }

            // if the object is in the same distance as a wall object and not placed on a wall,
            // it must not be rendered
            if ((wallInfo.viewDistance == distance)
              && !(cellValue & WALL_MASK))
            {
              if ( !leftRightOffset )
              {
                return;
              }
            }

            uint8_t* buffer = _dungeon.lineBuffer;
            // walk over all vertical pixels in the current column
            for ( uint8_t y = 0; y < DUNGEON_WINDOW_SIZE_Y / 8; y++ )
            {
              uint8_t posX = x - offset + objectWidth;
              // free background
              uint8_t mask = getDownScaledBitmapData(posX, y, distance, &object, true);
              *buffer &= mask;
              // and overlay scaled bitmap
              uint8_t scaledBitmap = getDownScaledBitmapData(posX, y, distance, &object, false);

            #ifdef _ENABLE_OBJECT_SHADING_
              // use shading effect to pronounce the distance of an object (at the cost of clarity)
              //uint8_t lightMask = pgm_read_byte( lightingTable + _dungeon.lightingOffset + wallInfo.viewDistance );
              scaledBitmap &= getLightingMask(wallInfo.viewDistance);
            #endif

              // is it the object right in front of the player (must be, if distance is 1)
              if (distance == 1)
              {
                // apply inversion effect if the monster was hit...
                scaledBitmap ^= (_dungeon.invertMonsterEffect & ~mask);
              }
              *buffer++ |= scaledBitmap;
            } // for y
            break;
          }
        }
      
        // next column
        offsets++;
        leftRightOffset++;
      } // while

    } // for n

  } // for distance
}

/*--------------------------------------------------------*/
// Returns the downscaled bitmap data at position x,y.
// Supported distance values are 1, 2, 3.
// Note that x is scaled by the scale factor for
// the current distance, while y remains unscaled!
uint8_t Dungeon::getDownScaledBitmapData( uint8_t x,                     // already downscaled by 1 << ( distance - 1 )
                                          uint8_t y,                     // unscaled vertical position
                                          const uint8_t distance,        // supported values are 1..3
                                          const NON_WALL_OBJECT *object, // current non wall object
                                          bool useMask                   // if true returns the down scaled mask instead of the bitmap
                                        )
{
  uint8_t pixels = 0;

  // get start address
  const uint8_t *bitmapData = object->bitmapData;
  // (add optional offset for mask if required)
  if ( useMask ) { bitmapData += object->bitmapHeightInBytes * object->bitmapWidth; }

  // Get scaling factor from LUT (efficient and still flexible).
  const uint8_t scaleFactor = pgm_read_byte( scalingFactorFromDistance + distance );
  const uint8_t squaredScaleFactor = scaleFactor * scaleFactor;

  // get threshold (distance is 1..3, so subtract 1 (at no cost!))
  const uint8_t threshold = object->scalingThreshold[distance - 1];

  // is there anything to be done?
  uint8_t startOffsetY = pgm_read_byte( verticalStartOffset + distance );
  uint8_t endOffsetY = pgm_read_byte( verticalEndOffset + distance );

  if ( ( y >= startOffsetY ) && ( y <= endOffsetY ) )
  {
    // modify positions in source bitmap by scaling factor
    //x = x * scaleFactor * object->bitmapHeightInBytes;
    // correct y position by start offset
    y -= startOffsetY;
    
    // get associated bit mask
    uint8_t bitMask = pgm_read_byte( bitMaskFromScalingFactor + scaleFactor );

    // calculate the first and last bit to be processed
    uint8_t startBitNo = object->bitmapVerticalOffsetInBits;
    uint8_t endBitNo = startBitNo + object->bitmapHeightInBytes * 8;
    
    // but we are starting with bit 0 (and its friends)
    uint8_t bitNo = y * 8 * scaleFactor;

    // We need to calculate 8 vertical output bits...
    // NOTE: Because the Tiny85 only supports shifting by 1 bit, it is
    //       more efficient to do the shifting in the 'for' loop instead
    //       of using a ( 1 << n ) construct.
    for ( uint8_t bitValue = 1; bitValue != 0; bitValue <<= 1 )
    {
      uint8_t bitSum = 0;
  
      if ( ( bitNo >= startBitNo ) && ( bitNo < endBitNo ) )
      {
        // calculate start address
        uint8_t row = ( bitNo - startBitNo ) / 8;
        const uint8_t *data = bitmapData + x * scaleFactor * object->bitmapHeightInBytes + row;
        
        // go over the columns - all required bits always are in one row
        for ( uint8_t col = 0; col < scaleFactor; col++ )
        {
          // to get the output value, we will sum all the bits up (using a lookup table saves time and flash space)
          bitSum += pgm_read_byte( nibbleBitCount + ( ( pgm_read_byte( data ) >> ( bitNo & 0x07 ) ) & bitMask ) );
          data += object->bitmapHeightInBytes;
        }
      }
      else if ( useMask )
      {
        // make bitsum count - otherwise we will erase the backgound ;)
        //bitSum += pgm_read_byte( scalingFactorFromDistance2 + distance );
        bitSum += squaredScaleFactor;
      }
  
      // next bit position
      bitNo += scaleFactor;

      // calculate output pixel
      if ( bitSum >= threshold )
      {
        pixels |= bitValue;
      }
    } // for
  }
  // no bits here, set mask to 0xff
  else if ( useMask )
  { 
    // 0x00-- -> 0xff
    pixels--;
  }
                                     
  return( pixels );  
}
