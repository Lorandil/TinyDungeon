#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"
#include "spritebank.h"

uint8_t *getCell( DUNGEON *dungeon, int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation );
void limitDungeonPosition( DUNGEON *dungeon, int8_t &x, int8_t &y );
void updateStatusPane( DUNGEON *dungeon );
void openChest( DUNGEON *dungeon, INTERACTION_INFO &info );

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
//    0       1          2        3           4        5           6        7
  WALL  , WALL|LVR_UP, WALL,   WALL      ,   WALL ,   WALL     ,FAKE_WALL, WALL  , // 0
    0   ,     0  ,     BARS , SKELETON   ,   WALL ,   WALL     ,   0     , WALL  , // 1
    0   ,     0  ,     WALL ,CLOSED_CHEST,   WALL ,  FOUNTAIN  ,BEHOLDER , WALL  , // 2
    0   ,     0  ,     WALL ,   WALL     ,   WALL ,     0      ,   0     , WALL  , // 3
    0   ,     0  ,       0  ,WALL|DOOR   ,   0    , TELEPORTER ,   0     , WALL  , // 4
  WALL  ,   WALL ,       0  ,   WALL     ,   WALL ,     0      ,   0     , WALL  , // 5
  SKELETON,   0  , SPINNER  ,     0      ,     0  ,     0      ,   0     ,   0   , // 6
  WALL  ,   WALL ,     WALL ,   WALL     ,   WALL ,CLOSED_CHEST,   0     , WALL  , // 7
//    0       1          2        3           4        5           6        7
};

// interaction data for level 1
const INTERACTION_INFO interactionData[] PROGMEM =
{
  // currentPos currentStatus  currentStatusMask nextStatus   newItem itemValue modifiedPos   modifiedPosCellValue;
  { 1 + 0 * 8,    LVR_UP       , OBJECT_MASK    , LVR_DWN     ,     0    ,  0      , 2 + 1 * 8   ,       0      },
  { 1 + 0 * 8,    LVR_DWN      , OBJECT_MASK    , LVR_UP      ,     0    ,  0      , 2 + 1 * 8   , BARS         },
  //{ ANY_POSITION, CLOSED_CHEST , OBJECT_MASK    , OPEN_CHEST  ,     0    ,  0      , ANY_POSITION, OPEN_CHEST   },
  //{ ANY_POSITION, OPEN_CHEST   , OBJECT_MASK    , CLOSED_CHEST,     0    ,  0      , ANY_POSITION, CLOSED_CHEST },
  { 3 + 4 * 8,    DOOR         , OBJECT_MASK    ,    0        ,     0    ,  0      , 3 + 4 * 8   ,       0      },
  { 3 + 2 * 8,    CLOSED_CHEST , OBJECT_MASK    , OPEN_CHEST  , ITEM_COMPASS,  0      , 3 + 2 * 8  , OPEN_CHEST   },
  //{ 3 + 2 * 8,    OPEN_CHEST   , OBJECT_MASK    , CLOSED_CHEST,     0    ,  0      , 3 + 2 * 8  , CLOSED_CHEST },
  { 5 + 7 * 8,    CLOSED_CHEST , OBJECT_MASK    , OPEN_CHEST  ,     0    ,  0      , 5 + 7 * 8  , OPEN_CHEST   },
  //{ 5 + 7 * 8,    OPEN_CHEST   , OBJECT_MASK    , CLOSED_CHEST,     0    ,  0      , 5 + 7 * 8  , CLOSED_CHEST },
};

// special cell effects
const SPECIAL_CELL_INFO specialCellFX[] PROGMEM =
{
  // cell type ,  posX , posY , value_1, value_2
  { TELEPORTER ,   5   ,   4  ,     6  ,    4    },
  { SPINNER    ,   2   ,   6  ,    +1  ,    0    },
};


// array of conditions for wall display
const SIMPLE_WALL_INFO arrayOfWallInfo[] PROGMEM = {
  // distance 0
  { leftRightWalls,  0,  4, 0, 7, 0, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 91, 95, 0, 7, 0, +1, WALL & ~FLAG_SOLID },
  // distance 1
  { frontWalls_D1,   0,  4, 0, 7, 1, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D1,   5, 90, 0, 7, 1,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D1,  91, 95, 0, 7, 1, +1, WALL & ~FLAG_SOLID },
  { leftRightWalls,  5, 24, 0, 7, 1, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 71, 90, 0, 7, 1, +1, WALL & ~FLAG_SOLID },
  // distance 2
  { frontWalls_D2,   0, 24, 2, 5, 2, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D2,  25, 70, 2, 5, 2,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D2,  71, 95, 2, 5, 2, +1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 25, 34, 0, 7, 2, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 61, 70, 0, 7, 2, +1, WALL & ~FLAG_SOLID },
  // distance 3
  { frontWalls_D3,   0, 11, 3, 4, 3, -2, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  12, 35, 3, 4, 3, -1, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  36, 58, 3, 4, 3,  0, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  59, 83, 3, 4, 3, +1, WALL & ~FLAG_SOLID },
  { frontWalls_D3,  84, 95, 3, 4, 3, +2, WALL & ~FLAG_SOLID },
  { leftRightWalls, 35, 47, 0, 7, 3, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 48, 60, 0, 7, 3, +1, WALL & ~FLAG_SOLID },
  
  { NULL,            0,  0, 0, 0, 0,  0,    0 },
};


// list of possible non wall objects (i.e. monsters, doors, ...)
const NON_WALL_OBJECT objectList [] PROGMEM = {
//  itemType, width, verticalOffset, heightBytes, maskOffset, lineOffset, maxView, scalingThreshold, bitmap
  { SKELETON    ,  32,         2,             5,          32,         64,         3,  { 0, 1, 2, 99 },  joey        },
  { BEHOLDER    ,  32,         0,             8,          32,         64,         3,  { 0, 1, 2,  5 },  beholder    },
  { BARS        ,  32,         1,             6,          32,         64,         3,  { 0, 1, 2,  5 },  newBars     },
  { DOOR        ,  32,         0,             8,          32,         64,         3,  { 0, 1, 3, 13 },  door        },
  { LVR_UP      ,  16,         2,             3,          16,         32,         3,  { 0, 1, 2,  8 },  leverUp     },
  { LVR_DWN     ,  16,         3,             3,          16,         32,         3,  { 0, 1, 2,  8 },  leverDown   },
  { CLOSED_CHEST,  24,         4,             3,          24,         48,         3,  { 0, 1, 3, 99 },  chestClosed },
  { OPEN_CHEST  ,  24,         4,             3,          24,         48,         3,  { 0, 1, 3, 99 },  chestOpen   },
  { FOUNTAIN    ,  12,         4,             3,          12,         24,         3,  { 0, 1, 2, 99 },  fountain    },
};

// direction letters for the compass ('0' + dir [0..3])
//                                       N   E   S   W
const char directionLetter[] PROGMEM = {';',':','<','='};
