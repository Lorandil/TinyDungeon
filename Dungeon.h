#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"
#include "externBitmaps.h"

// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
  // plain level data
/*             0            1            2            3            4            5            6            7            8            9           10           11           12           13           14           15              */
/*  0 */     WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,WALL|LVR_UP ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     , /*  0 */
/*  1 */       0      ,/*START*/ 0 ,   BARS     ,     0      ,CLOSED_CHEST, WALL|LVR_UP,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     , /*  1 */
/*  2 */       0      ,     0      ,   WALL     ,     0      ,   WALL     ,   WALL     ,   WALL     ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,   WALL     ,   WALL     ,     0      ,   WALL     , /*  2 */
/*  3 */      RAT     ,   WALL     ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,  BEHOLDER  ,   WALL     ,     0      ,   WALL     , /*  3 */
/*  4 */  WALL|LVR_UP ,   WALL     ,     0      ,   WALL     ,  FOUNTAIN  ,/*TELEP.*/0 ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      ,     0      ,   WALL     , /*  4 */
/*  5 */     WALL     ,     0      ,/*SPINNER*/0,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     , /*  5 */
/*  6 */       0	  ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     , /*  6 */
/*  7 */     WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,CLOSED_CHEST,   WALL     ,   WALL     ,   WALL     ,WALL|LVR_UP ,   WALL     ,   WALL     ,   WALL     ,     0      ,   WALL     ,   WALL     , /*  7 */
/*  8 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      , /*  8 */
/*  9 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,   WALL     , /*  9 */
/* 10 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      ,   WALL     , /* 10 */
/* 11 */     WALL     ,   WALL     ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,   WALL     ,     0      ,   WALL     , /* 11 */
/* 12 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      , WALL|DOOR  ,     0      ,   WALL     , /* 12 */
/* 13 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,   WALL     ,   WALL     ,   WALL     , /* 13 */
/* 14 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,   WALL     ,     0      ,     0      ,     0      , /* 14 */
/* 15 */       0      ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      ,     0      ,     0      ,   WALL     ,     0      ,     0      ,     0      , /* 15 */
/*             0            1            2            3            4            5            6            7            8            9           10           11           12           13           14           15              */
};

// interaction data (8 bytes per event)
const INTERACTION_INFO interactionData[] PROGMEM =
{
  // currentPos currentStatus    currentStatus    currentStatusMask  nextStatus     newItem              modifiedPos        modifiedPosCellValue
  { 0 +  4 * LEVEL_WIDTH        ,    LVR_UP       , OBJECT_MASK     , LVR_DWN     ,     0           , 2 + 1 * LEVEL_WIDTH  ,      0        },
  { 0 +  4 * LEVEL_WIDTH        ,    LVR_DWN      , OBJECT_MASK     , LVR_UP      ,     0           , 2 + 1 * LEVEL_WIDTH  ,     BARS      },
  { 5 +  1 * LEVEL_WIDTH        ,    LVR_UP       , OBJECT_MASK     ,    0        ,     0           , 5 + 1 * LEVEL_WIDTH  ,      0        },
  { 3 +  4 * LEVEL_WIDTH        ,    DOOR         , OBJECT_MASK     ,    0        ,     0           , 3 + 4 * LEVEL_WIDTH  ,      0        },
  { 4 +  1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_COMPASS    , 4 + 1 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  { 5 +  7 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_RING       , 5 + 7 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  { 6 +  1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OBJECT_MASK     , OPEN_CHEST  , ITEM_AMULET     , 6 + 1 * LEVEL_WIDTH  ,  OPEN_CHEST   },
};

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM =
{
  // position                monsterType  hp  bonusDamage   attacksFirst  treasureItemMask
  {   0 +  3 * LEVEL_WIDTH,  RAT        ,  3 ,     -6      ,      1       ,     0                     }, // rat
  {   6 +  1 * LEVEL_WIDTH,  MIMIC      , 20 ,     -5      ,      1       ,    ITEM_SHIELD            }, // mimic
  //{   3 +  1 * LEVEL_WIDTH,  SKELETON   ,  6 ,      0      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
  //{   6 +  2 * LEVEL_WIDTH,  BEHOLDER   , 50 ,     +7      ,      1       ,  ITEM_VICTORY             }, // beholder (end boss)
  //{   6 +  2 * LEVEL_WIDTH,  BEHOLDER   , 20 ,     +2      ,      1       ,  ITEM_VICTORY             }, // beholder (end boss)
  //{   1 +  0 * LEVEL_WIDTH,  SKELETON   , 10 ,     -2      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
  //{   0 +  7 * LEVEL_WIDTH,  SKELETON   , 10 ,     -2      ,      0       ,  ITEM_SWORD | ITEM_SHIELD }, // skeleton
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 },
};

// special cell effects (4 bytes per FX)
const SPECIAL_CELL_INFO specialCellFX[] PROGMEM =
{
  // cell type ,     position       , value_1, value_2
  { TELEPORTER , 5 + 4 * LEVEL_WIDTH,     6  ,    4    },
  { SPINNER    , 2 + 5 * LEVEL_WIDTH,    +1  ,    0    },
};

// list of possible non wall objects (i.e. monsters, doors, ...) (10 bytes per object)
const NON_WALL_OBJECT objectList [11] PROGMEM = {
//  itemType    , width, verticalOffsetBits, heightBits, lineOffset, scalingThreshold, bitmapData
  { SKELETON    ,  28,         2 * 8,          5 * 8,         56,      { 1, 2, 99 },   joey        },  //  0
  { BEHOLDER    ,  32,         0 * 8,          7 * 8,         64,      { 1, 2,  5 },   beholder    },  //  1
  { BARS        ,  28,         1 * 8,          6 * 8,         56,      { 1, 2,  5 },   newBars     },  //  2
  { DOOR        ,  32,         1 * 8,          7 * 8,         64,      { 1, 3, 12 },   door        },  //  3
  { LVR_UP      ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverLeft   },  //  4
  { LVR_DWN     ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverRight  },  //  5
  { CLOSED_CHEST,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestClosed },  //  6
  { MIMIC       ,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestClosed },  //  7
  { OPEN_CHEST  ,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestOpen   },  //  8
  { FOUNTAIN    ,  12,         4 * 8,          3 * 8,         24,      { 1, 2, 99 },   fountain    },  //  9
  { RAT         ,  20,         5 * 8,          2 * 8,         40,      { 1, 2, 99 },   rat         },  // 10
};

// array of conditions for wall display (9 bytes per row)
// 'WALL & ~FLAG_SOLID' means all walls, fake or not...
// CAUTION: The entries must be ordered from min. distance(0) to max. distance (3)
// Otherwise display errors will occur
const SIMPLE_WALL_INFO arrayOfWallInfo[] PROGMEM = {
#if 0
  // *wallBitmap         , startX, endX, posStartEndY, distance, l/r offset,relPos, width /*, objectMask */
  // distance 0
  { leftRightWalls_D0    ,   0   ,   4 ,   0x07      ,     0   ,     -1    ,   0  ,  10   /*, WALL & ~FLAG_SOLID */ }, //  0
  { leftRightWalls_D0    ,  91   ,  95 ,   0x07      ,     0   ,     +1    ,   5  ,  10   /*, WALL & ~FLAG_SOLID */ }, //  1
																						  /*                     */ 
  // distance 1	                                                                          /*                     */ 
  { frontWalls_D1        ,   0   ,   4 ,   0x07      ,     1   ,     -1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  2
  { frontWalls_D1        ,   5   ,  90 ,   0x07      ,     1   ,      0    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  3
  { frontWalls_D1        ,  91   ,  95 ,   0x07      ,     1   ,     +1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  4
  { leftRightWalls_D1    ,   5   ,  24 ,   0x07      ,     1   ,     -1    ,   0  ,  40   /*, WALL & ~FLAG_SOLID */ }, //  5
  { leftRightWalls_D1    ,  71   ,  90 ,   0x07      ,     1   ,     +1    ,  20  ,  40   /*, WALL & ~FLAG_SOLID */ }, //  6
																						  /*                     */ 
  // distance 2	                                                                          /*                     */ 
  { smallFrontWalls_D2   ,   0   ,  24 ,   0x25      ,     2   ,     -1    ,  21  ,  46   /*, WALL & ~FLAG_SOLID */ }, //  7
  { smallFrontWalls_D2   ,  25   ,  70 ,   0x25      ,     2   ,      0    ,   0  ,  46   /*, WALL & ~FLAG_SOLID */ }, //  8
  { smallFrontWalls_D2   ,  71   ,  95 ,   0x25      ,     2   ,     +1    ,   0  ,  46   /*, WALL & ~FLAG_SOLID */ }, //  9
  { leftRightWalls_D2    ,  25   ,  34 ,   0x25      ,     2   ,     -1    ,   0  ,  20   /*, WALL & ~FLAG_SOLID */ }, // 10
  { leftRightWalls_D2    ,  61   ,  70 ,   0x25      ,     2   ,     +1    ,  10  ,  20   /*, WALL & ~FLAG_SOLID */ }, // 11
  { distLeftRightWalls_D2,   0   ,  23 ,   0x25      ,     2   ,     -2    ,   0  ,  48   /*, WALL & ~FLAG_SOLID */ }, // 12
  { distLeftRightWalls_D2,  72   ,  95 ,   0x25      ,     2   ,     +2    ,  24  ,  48   /*, WALL & ~FLAG_SOLID */ }, // 13
																						  /*                     */ 
  // distance 3                                                                           /*                     */ 
  { smallFrontWalls_D3   ,   0   ,  11 ,   0x34      ,     3   ,     -2    ,  12  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 14
  { smallFrontWalls_D3   ,  12   ,  35 ,   0x34      ,     3   ,     -1    ,   0  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 15
  { smallFrontWalls_D3   ,  36   ,  59 ,   0x34      ,     3   ,      0    ,   0  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 16
  { smallFrontWalls_D3   ,  60   ,  83 ,   0x34      ,     3   ,     +1    ,   0  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 17
  { smallFrontWalls_D3   ,  84   ,  95 ,   0x34      ,     3   ,     +2    ,   0  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 18
  { leftRightWalls_D3    ,  35   ,  44 ,   0x34      ,     3   ,     -1    ,   0  ,  20   /*, WALL & ~FLAG_SOLID */ }, // 19
  { leftRightWalls_D3    ,  51   ,  60 ,   0x34      ,     3   ,     +1    ,  10  ,  20   /*, WALL & ~FLAG_SOLID */ }, // 20
  { distLeftRightWalls_D3,  24   ,  35 ,   0x34      ,     3   ,     -2    ,   0  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 21
  { distLeftRightWalls_D3,  60   ,  71 ,   0x34      ,     3   ,     +2    ,  12  ,  24   /*, WALL & ~FLAG_SOLID */ }, // 22
#else
  // distance 0
  { leftRightWalls_D0    ,   0   ,   3 ,   0x07      ,     0   ,     -1    ,   0  ,   8   /*, WALL & ~FLAG_SOLID */ }, //  5
  { leftRightWalls_D0    ,  92   ,  95 ,   0x07      ,     0   ,     +1    ,   4  ,   8   /*, WALL & ~FLAG_SOLID */ }, //  5

  // distance 1	                                                                          /*                     */ 
  { smallFrontWall_D1    ,   0   ,   3 ,   0x07      ,     1   ,      0    ,  84  ,  88   /*, WALL & ~FLAG_SOLID */ }, //  3
  { smallFrontWall_D1    ,   4   ,  91 ,   0x07      ,     1   ,      0    ,   0  ,  88   /*, WALL & ~FLAG_SOLID */ }, //  3
  { smallFrontWall_D1    ,  92   ,  95 ,   0x07      ,     1   ,      0    ,   0  ,  88   /*, WALL & ~FLAG_SOLID */ }, //  3
  
  { leftRightWalls_D0_v2 ,   0   ,  23 ,   0x07      ,     1   ,     -1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  5
  { leftRightWalls_D0_v2 ,  72   ,  95 ,   0x07      ,     1   ,     +1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  5

  // distance 2	                                                                          /*                     */ 
  { smallFrontWall_D2    ,   0   ,  25 ,   0x25      ,     2   ,     -1    ,  18  ,  44   /*, WALL & ~FLAG_SOLID */ }, //  7
  { smallFrontWall_D2    ,  26   ,  69 ,   0x25      ,     2   ,      0    ,   0  ,  44   /*, WALL & ~FLAG_SOLID */ }, //  7
  { smallFrontWall_D2    ,  70   ,  95 ,   0x25      ,     2   ,     -1    ,   0  ,  44   /*, WALL & ~FLAG_SOLID */ }, //  7

  { leftRightWalls_D0_v2 ,  24   ,  35 ,   0x07      ,     2   ,     -1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  5
  { leftRightWalls_D0_v2 ,  60   ,  71 ,   0x07      ,     2   ,     +1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, //  5

  { leftRightWalls_D1_v2,    0   ,  12 ,   0x07      ,     2   ,     -2    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 12
  { leftRightWalls_D1_v2,   84   ,  95 ,   0x07      ,     2   ,     +2    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 13
																						  /*                     */ 
  // distance 3                                                                           /*                     */ 
  { smallFrontWall_D3    ,   0   ,  14 ,   0x34      ,     3   ,     -2    ,   7  ,  22   /*, WALL & ~FLAG_SOLID */ }, // 14
  { smallFrontWall_D3    ,  15   ,  36 ,   0x34      ,     3   ,     -1    ,   0  ,  22   /*, WALL & ~FLAG_SOLID */ }, // 15
  { smallFrontWall_D3    ,  37   ,  58 ,   0x34      ,     3   ,      0    ,   0  ,  22   /*, WALL & ~FLAG_SOLID */ }, // 16
  { smallFrontWall_D3    ,  59   ,  80 ,   0x34      ,     3   ,     +1    ,   0  ,  22   /*, WALL & ~FLAG_SOLID */ }, // 17
  { smallFrontWall_D3    ,  81   ,  95 ,   0x34      ,     3   ,     +2    ,   0  ,  22   /*, WALL & ~FLAG_SOLID */ }, // 18

  { leftRightWalls_D0_v2 ,  36   ,  41 ,   0x07      ,     3   ,     -1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 19
  { leftRightWalls_D0_v2 ,  54   ,  59 ,   0x07      ,     3   ,     +1    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 20

  { leftRightWalls_D1_v2 ,  13   ,  29 ,   0x07      ,     3   ,     -2    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 21
  { leftRightWalls_D1_v2 ,  66   ,  83 ,   0x07      ,     3   ,     +2    ,   0  ,  96   /*, WALL & ~FLAG_SOLID */ }, // 22
#endif
																						  /*                     */ 
  { NULL                 ,   0   ,   0 ,   0x00      ,     0   ,      0    ,   0  ,   0   /*, 0                  */ }, // 7 unused bytes.. how can I save those?
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

#ifdef _USE_FIELD_OF_VIEW_
  void updateFieldOfView();
  uint8_t getCell( const int8_t distance, const int8_t offsetLR );
#endif
  uint8_t *getCellRaw( int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation );
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
