#include <Arduino.h>

#include "dungeon.h"
#include "dungeonTypes.h"
#include "textUtils.h"
#include "tinyJoypadUtils.h"

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

  return( dungeon->currentLevel + y * LEVEL_WIDTH + x );
}


/*--------------------------------------------------------*/
// Limits the position in the dungeon, but enables wrap-around :)
void limitDungeonPosition( DUNGEON *dungeon, int8_t &x, int8_t &y )
{
  if ( x < 0 ) { x += LEVEL_WIDTH; }
  if ( x >= LEVEL_WIDTH ) { x -= LEVEL_WIDTH; }
  if ( y < 0 ) { y += LEVEL_HEIGHT; }
  if ( y >= LEVEL_HEIGHT ) { y -= LEVEL_HEIGHT; }
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
  serialPrintln( F("openChest()") );

  switch( info.newItem )
  {
    case ITEM_COMPASS:
      // a compass will be displayed
      dungeon->playerHasCompass = true;
      // hooray!
      serialPrintln( F("+ <Compass> found!") );
      break;
    case ITEM_AMULET:
      // fake will be removed
      dungeon->playerHasAmulet = true;
      // remove all fake walls
      uint8_t *currentCell = dungeon->currentLevel;
      while ( currentCell < dungeon->currentLevel + LEVEL_WIDTH * LEVEL_HEIGHT )
      {
        // fake? let's stay with the facts...
        if ( *currentCell == FAKE_WALL ) { *currentCell = EMPTY; }
        currentCell++;
      }
      // hooray!
      serialPrintln( F("+ <Amulet of True Sight> found!") );
      break;
    case ITEM_RING:
      // spinning and teleporting revealed by flashing the screen
      dungeon->playerHasRing = 0xff;
      // hooray!
      serialPrintln( F("+ <Ring of Orientation> found!") );
      break;
  }
}

/*--------------------------------------------------------*/
void updateDice( DUNGEON *dungeon )
{ 
  dungeon->dice++; dungeon->dice &= MAX_DICE_VALUE;
  //serialPrint( F("D8 = ")); serialPrint( dungeon->dice + 1 );
  //readAnalogJoystick();
  //serialPrint( F(", analogX = ")); serialPrint( getAnalogValueX() );
  //serialPrint( F(", analogY = ")); serialPrintln( getAnalogValueY() );

}