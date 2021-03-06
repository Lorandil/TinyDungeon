#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "dungeonTypes.h"
#include "spritebank.h"

uint8_t *getCell( DUNGEON *dungeon, int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation );
void limitDungeonPosition( DUNGEON *dungeon, int8_t &x, int8_t &y );

// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
  // width x height
   8,  8,
  // stairs up
  0xFF, 0xFF,
  // stairs down
  0xFF, 0xFF,
  // level number
   1,

  // plain level data
//    0       1          2       3        4        5         6         7
  WALL  ,WALL|LVR_DWN, WALL,   WALL ,   WALL ,   WALL    ,FAKE_WALL, WALL  , // 0
    0   ,     0  ,     BARS ,     0  ,   WALL ,   WALL    ,   0     , WALL  , // 1
    0   ,     0  ,     WALL ,     0  ,   WALL ,  SKELETON ,BEHOLDER , WALL  , // 2
    0   ,     0  ,     WALL ,   WALL ,   WALL ,     0     ,   0     , WALL  , // 3
    0   ,     0  ,       0  ,WALL|DOOR ,   0  ,     0     ,   0     , WALL  , // 4
  WALL  ,   WALL ,       0  ,   WALL ,   WALL ,     0     ,   0     , WALL  , // 5
  SKELETON,   0  ,       0  ,     0  ,     0  ,     0     ,   0     ,   0   , // 6
  WALL  ,   WALL ,     WALL ,   WALL ,   WALL ,     0     ,   0     , WALL  , // 7
};

// interaction data for level 1
const INTERACTION_INFO interactionData[] PROGMEM =
{
  { 1 + 8 * 0, LVR_DWN, OBJECT_MASK, LVR_UP ,  0,  0, 2 + 1 * 8, SKELETON },
  { 1 + 8 * 0, LVR_UP , OBJECT_MASK, LVR_DWN,  0,  0, 2 + 1 * 8, BARS     },
};


// array of conditions for wall display
const SIMPLE_WALL_INFO arrayOfWallInfo[] PROGMEM = {
  // distance 0
  { leftRightWalls,  0,  4, 0, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 91, 95, 0, +1, WALL & ~FLAG_SOLID },
  // distance 1
  { frontWalls_D1,   0,  4, 1, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D1,   5, 90, 1,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D1,  91, 95, 1, +1, WALL & ~FLAG_SOLID },
  { leftRightWalls,  5, 24, 1, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 71, 90, 1, +1, WALL & ~FLAG_SOLID },
  // distance 2
  { frontWalls_D2,   0, 24, 2, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D2,  25, 70, 2,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D2,  71, 95, 2, +1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 25, 34, 2, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 61, 70, 2, +1, WALL & ~FLAG_SOLID },
  // distance 3
  { frontWalls_D3,   0, 11, 3, -2, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  12, 35, 3, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  36, 58, 3,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  59, 83, 3, +1, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  84, 95, 3, +2, WALL & ~FLAG_SOLID },
  { leftRightWalls, 35, 47, 3, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 48, 60, 3, +1, WALL & ~FLAG_SOLID },
  
  { NULL,            0,  0, 0,  0,    0 },
};


// list of possible non wall objects (i.e. monsters, doors, ...)
const NON_WALL_OBJECT objectList [] PROGMEM = {
//  itemType, width, verticalOffset, heightBytes, maskOffset, lineOffset, maxView, scalingThreshold, bitmap
  { SKELETON,  32,         1,             6,          32,         64,         3,  { 0, 1, 2,  5 },  skeleton },
  { BEHOLDER,  32,         0,             8,          32,         64,         3,  { 0, 1, 2,  5 },  beholder },
  { BARS    ,  32,         1,             6,          32,         64,         3,  { 0, 1, 2,  5 },  newBars  },
  { DOOR    ,  32,         0,             8,          32,         64,         3,  { 0, 1, 3, 13 },  door     },
  { LVR_UP  ,  16,         2,             3,          16,         32,         3,  { 0, 1, 2,  8 },  leverUp  },
  { LVR_DWN ,  16,         3,             3,          16,         32,         3,  { 0, 1, 2,  8 },  leverDown},
};

#endif
