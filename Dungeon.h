#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"
#include "externBitmaps.h"

// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
  // plain level data
/*             0            1            2            3            4            5            6            7            8            9           10           11           12           13           14           15              */
/*  0 */     WALL     ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,  FAKE_WALL ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /*  0 */ 
/*  1 */       0      ,     0      ,   BARS     ,     0      ,   WALL     ,     0      ,CLOSED_CHEST,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /*  1 */
/*  2 */       0      ,     0      ,   WALL     ,CLOSED_CHEST,   WALL     ,  FOUNTAIN  ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /*  2 */
/*  3 */       0      ,     0      ,   WALL     ,   WALL     ,   WALL     ,     0      ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,     0      ,     0      , /*  3 */
/*  4 */       0      ,     0      ,     0      , WALL|DOOR  ,     0      ,/*TELEP.*/0 ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      , /*  4 */
/*  5 */     WALL     ,   WALL     ,     0      ,   WALL     ,   WALL     ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      , /*  5 */
/*  6 */       0      ,     0      ,/*SPINNER*/0,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      , /*  6 */
/*  7 */     WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,CLOSED_CHEST,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      , /*  7 */
/*  8 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      , /*  8 */ 
/*  9 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,     0      ,     0      , /*  9 */
/* 10 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 10 */
/* 11 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 11 */
/* 12 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 12 */
/* 13 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 13 */
/* 14 */       0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 14 */
/* 15 */     WALL     ,WALL|LVR_UP ,    WALL    ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      , /* 15 */
/*             0            1            2            3            4            5            6            7            8            9           10           11           12           13           14           15              */
};

// interaction data (8 bytes per event)
const INTERACTION_INFO interactionData[] PROGMEM =
{
  // currentPos currentStatus    currentStatus    currentStatusMask  nextStatus     newItem              modifiedPos        modifiedPosCellValue
  { 1 + 15 * LEVEL_WIDTH        ,    LVR_UP       , OBJECT_MASK     , LVR_DWN     ,     0           , 2 + 1 * LEVEL_WIDTH  ,      0        },
  { 1 + 15 * LEVEL_WIDTH        ,    LVR_DWN      , OBJECT_MASK     , LVR_UP      ,     0           , 2 + 1 * LEVEL_WIDTH  ,     BARS      },
  { 3 +  4 * LEVEL_WIDTH        ,    DOOR         , OBJECT_MASK     ,    0        ,     0           , 3 + 4 * LEVEL_WIDTH  ,      0        },
  { 3 +  2 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_COMPASS    , 3 + 2 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  { 5 +  7 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_RING       , 5 + 7 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  { 6 +  1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_AMULET     , 6 + 1 * LEVEL_WIDTH  ,  OPEN_CHEST   },
};

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM =
{
  // position                monsterType  hp  bonusDamage   attacksFirst  treasureItemMask
  {   0 +  1 * LEVEL_WIDTH,  RAT        ,  3 ,     -6      ,      1       ,     0                     }, // rat
  {   3 +  1 * LEVEL_WIDTH,  SKELETON   ,  6 ,      0      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
  //{   6 +  2 * LEVEL_WIDTH,  BEHOLDER   , 50 ,     +7      ,      1       ,  ITEM_VICTORY             }, // beholder (end boss)
  {   6 +  2 * LEVEL_WIDTH,  BEHOLDER   , 20 ,     +2      ,      1       ,  ITEM_VICTORY             }, // beholder (end boss)
  {   1 +  0 * LEVEL_WIDTH,  SKELETON   , 10 ,     -2      ,      0       ,     0                     }, // mimic
  {   0 +  7 * LEVEL_WIDTH,  SKELETON   , 10 ,     -2      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
  {   6 +  6 * LEVEL_WIDTH,  SKELETON   , 10 ,     -2      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
};

const SPECIAL_CELL_INFO specialCellFX[] PROGMEM =
{
  // cell type ,     position       , value_1, value_2
  { TELEPORTER , 5 + 4 * LEVEL_WIDTH,     6  ,    4    },
  { SPINNER    , 2 + 6 * LEVEL_WIDTH,    +1  ,    0    },
};

// list of possible non wall objects (i.e. monsters, doors, ...) (10 bytes per object)
const NON_WALL_OBJECT objectList [10] PROGMEM = {
//  itemType    , width, verticalOffsetBits, heightBits, lineOffset, scalingThreshold, bitmapData
  { SKELETON    ,  28,         2 * 8,          5 * 8,         56,      { 1, 2, 99 },   joey        },  //  0
  { BEHOLDER    ,  32,         0 * 8,          7 * 8,         64,      { 1, 2,  5 },   beholder    },  //  1
  { BARS        ,  28,         1 * 8,          6 * 8,         56,      { 1, 2,  5 },   newBars     },  //  2
  { DOOR        ,  32,         1 * 8,          7 * 8,         64,      { 1, 3, 12 },   door        },  //  3
  { LVR_UP      ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverLeft   },  //  4
  { LVR_DWN     ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverRight  },  //  5
  { CLOSED_CHEST,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestClosed },  //  6
  { OPEN_CHEST  ,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestOpen   },  //  7
  { FOUNTAIN    ,  12,         4 * 8,          3 * 8,         24,      { 1, 2, 99 },   fountain    },  //  8
  { RAT         ,  20,         5 * 8,          2 * 8,         40,      { 1, 2, 99 },   rat         },  //  9
};// special cell effects (4 bytes per FX)

// array of conditions for wall display (9 bytes per row)
// 'WALL & ~ FLAG_SOLID' means all walls, fake or not...
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
  { leftRightWalls, 35, 44, 0, 7, 3, -1, WALL & ~FLAG_SOLID },
  { leftRightWalls, 51, 60, 0, 7, 3, +1, WALL & ~FLAG_SOLID },
  
  { NULL,            0,  0, 0, 0, 0,  0,    0 }, // 7 unused bytes.. how can I save those?
};


// Dungeon
class Dungeon
{
public:
  DUNGEON _dungeon;

  static constexpr uint8_t getLevelWidth() { return( LEVEL_WIDTH ); }
  static constexpr uint8_t getLevelHeight() { return( LEVEL_HEIGHT ); }

  void clear();
  void init();

  bool isPlayerAlive() { return( _dungeon.playerHP > 0 ); }

  void gameLoop();
  void checkPlayerMovement();

  uint8_t *getCell( int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation );
  void limitDungeonPosition( int8_t &x, int8_t &y );
  void updateStatusPane();
  void openChest( INTERACTION_INFO &info );
  void initDice();
  void updateDice();
  uint8_t getDice( uint8_t maxValue );
  MONSTER_STATS *findMonster( const uint8_t position );
  void playerAttack( MONSTER_STATS *monster );
  void monsterAttack( MONSTER_STATS *monster );
  void playerInteraction( uint8_t *cell, const uint8_t cellValue );
  void /*__attribute__ ((noinline))*/ Tiny_Flip();
  // bitmap drawing functions
  uint8_t /*__attribute__ ((always_inline))*/ getWallPixels( const int8_t x, const int8_t y );
  uint8_t getDownScaledBitmapData( int8_t x, int8_t y, 
                                   const uint8_t distance, const NON_WALL_OBJECT *object,
                                   bool useMask );
};
