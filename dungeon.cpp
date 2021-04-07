#include <Arduino.h>

#include "dungeon.h"
#include "dungeonTypes.h"
#include "textUtils.h"

/*--------------------------------------------------------*/
// Returns a pointer to the cell which is 
// - 'distance' away 
// - in direction 'orientation'
// - from position 'x', 'y'
// This function supports a wrap-around, so endless corridors are possible :)
uint8_t *getCell( DUNGEON *dungeon, int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation )
{
  switch( orientation )
  {
    case NORTH:
    {
      y -= distance;
      x += offsetLR;
      break;
    }
    case SOUTH:
    {
      y += distance;
      x -= offsetLR;
      break;
    }
    case EAST:
    {
      x += distance;
      y += offsetLR;
      break;
    }
    case WEST:
    {
      x -= distance;
      y -= offsetLR;
      break;
    }
  }

  limitDungeonPosition( dungeon, x, y );

  return( dungeon->currentLevel + y * dungeon->levelWidth + x );
}


/*--------------------------------------------------------*/
// Limits the position in the dungeon, but enables wrap-around :)
void limitDungeonPosition( DUNGEON *dungeon, int8_t &x, int8_t &y )
{
  if ( x < 0 ) { x += dungeon->levelWidth; }
  if ( x >= dungeon->levelWidth ) { x -= dungeon->levelWidth; }
  if ( y < 0 ) { y += dungeon->levelHeight; }
  if ( y >= dungeon->levelHeight ) { y -= dungeon->levelHeight; }
}


/*--------------------------------------------------------*/
// updates the compass and the player stats
void updateStatusPane( DUNGEON *dungeon )
{
  // display viewing direction
  uint8_t *textBuffer = getTextBuffer();

  // display compass
  //if ( dungeon->playerHasCompass ) 
  { textBuffer[POS_COMPASS] = pgm_read_byte( directionLetter + dungeon->dir ); }
  //else // show '?'
  //{ textBuffer[POS_COMPASS] = '>'; }

  // and the hitpoints
  convertValueToDigits( dungeon->playerHP, textBuffer + POS_HITPOINTS );

  // and the damage
  convertValueToDigits( dungeon->playerDAM, textBuffer + POS_DAMAGE );

  // and the number of keys
  convertValueToDigits( dungeon->playerKeys, textBuffer + POS_KEYS );
}

/*--------------------------------------------------------*/
// opens a chest
void openChest( DUNGEON *dungeon, INTERACTION_INFO &info )
{
#if !defined(__AVR_ATtiny85__)
  Serial.println(F("openChest()") );
#endif

  // is there a compass in this chest?
  if ( info.newItem == ITEM_COMPASS )
  {
    dungeon->playerHasCompass = true;
    // hooray!
  #if !defined(__AVR_ATtiny85__)
    Serial.println(F("+ Compass found!"));
  #endif

  }
}
