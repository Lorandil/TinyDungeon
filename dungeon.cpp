#include <Arduino.h>
#include "Dungeon.h"

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
