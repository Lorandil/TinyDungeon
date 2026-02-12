#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"
//#include "externBitmaps.h"

#if 0
// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
/*             0       ,     1       ,     2      ,     3        ,     4       ,      5       ,     6       ,     7       ,     8       ,     9      ,     10     ,     11      ,     12     ,     13     ,     14     ,     15     ,         */
/*  0 */     WALL      ,   WALL      ,   WALL     ,   WALL       ,WALL|SWITCH_L|N_S, WALL     ,    WALL     ,     0       ,   WALL      ,   WALL     ,     0      ,     0       ,     0      ,     0      ,     0      ,   WALL     , /*  0 */
/*  1 */       0       ,/*START*/ 0  ,  BARS|E_W  ,     0        ,CLOSED_CHEST|E_W,  WALL     , CLOSED_CHEST,   WALL      ,     0       ,   WALL     ,     0      ,    WALL     ,   WALL     ,   WALL     ,     0      ,   WALL     , /*  1 */
/*  2 */       0       ,     0       ,   WALL     ,     0        ,    WALL     ,     WALL     ,    WALL     ,     0       ,     0       ,   WALL     ,     0      ,    WALL     ,  FOUNTAIN  ,   WALL     ,     0      ,   WALL     , /*  2 */
/*  3 */   /*RAT*/ 0   ,   WALL      ,     0      ,     0        ,    WALL     ,      0       ,      0      ,     0       ,   WALL      ,   WALL     ,     0      ,    WALL     ,/*BEHOLDR*/0,   WALL     ,     0      ,   WALL     , /*  3 */
/*  4 */  WALL|SWITCH_L,   WALL      ,     0      ,   WALL       ,      0      ,      0       ,    WALL     ,     0       ,     0       ,   WALL     ,     0      ,    WALL     ,     0      ,  BARS|E_W  ,     0      ,   WALL     , /*  4 */
/*  5 */     WALL      ,     0       ,/*SPINNER*/0,  /*RAT*/ 0   ,    WALL     ,      0       ,    WALL     ,     0       ,     0       ,   WALL     ,     0      ,    WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL     , /*  5 */
/*  6 */       0       ,     0       ,   WALL     ,     0        ,      0      ,      0       ,    WALL     ,   WALL      ,CLOSED_CHEST|N_S, WALL    ,     0      ,     0       ,     0      ,/*SKELETON*/0,CLOSED_CHEST|E_W,BARS|E_W , /*  6 */ 
/*  7 */     WALL      ,   WALL	     ,     0      ,     0        ,    WALL     ,     WALL     ,    WALL     ,   WALL      ,   WALL      ,   WALL     ,    WALL    ,    WALL     ,   WALL     ,  BARS|N_S  ,   WALL     ,   WALL     , /*  7 */
/*  8 */     WALL      ,     0       ,     0      ,     0        ,    WALL     ,      0       ,    WALL     ,/*SPINNER*/0 ,   WALL      ,     0      ,    WALL    ,     0       ,     0      ,     0      ,     0      ,     0      , /*  8 */
/*  9 */     WALL      ,     0       ,   WALL     , FAKE_WALL    ,    WALL     ,      0       ,      0      ,     0       ,     0       ,     0      ,    WALL    ,   BARS|N_S  ,   WALL     ,     0      ,   WALL     ,     0      , /*  9 */
/* 10 */     WALL      ,     0       ,   WALL     ,CLOSED_CHEST  ,    WALL     ,      0       ,    WALL     ,     0       ,   WALL      ,     0      ,    WALL    , /*MIMIC*/ 0 ,   WALL     ,     0      ,     0      ,     0      , /* 10 */
/* 11 */     WALL      ,     0       ,     0      ,   WALL       ,    WALL     ,      0       ,      0      ,/*TELEP.*/ 0 ,     0       ,     0      ,    WALL    ,    WALL     ,     0      ,     0      ,   WALL     ,     0      , /* 11 */
/* 12 */WALL|SWITCH_L|N_S,   WALL    , FAKE_WALL  ,   BARS|E_W   ,   BARS|E_W  ,      0       ,    WALL     ,CLOSED_CHEST ,WALL|SWITCH_L|E_W, 0      ,     0      ,WALL|DOOR|E_W,     0      ,   WALL     ,     0      ,     0      , /* 12 */
/* 13 */       0       ,     0       ,     0      ,   WALL       ,    WALL     ,      0       ,      0      ,/*TELEP.*/ 0 ,     0       ,     0      ,    WALL    ,     0       ,     0      ,   WALL     ,     0      ,   WALL     , /* 13 */
/* 14 */     WALL      ,   WALL      ,     0      , /*SKELETON*/0,    WALL     ,      0       ,    WALL     ,     0       ,   WALL      ,     0      ,    WALL    ,/*SKELETON*/0,   WALL     ,     0      ,     0      ,     0      , /* 14 */
/* 15 */       0       ,WALL|SWITCH_L|N_S, WALL   ,WALL|SWITCH_L|N_S, WALL     ,      0       ,      0      ,     0       ,     0       ,     0      ,    WALL    ,    WALL     ,   WALL     ,WALL|SWITCH_L|N_S,   WALL    ,     0      , /* 15 */
/*             0       ,     1       ,     2      ,     3        ,     4       ,      5       ,     6       ,     7       ,     8       ,     9      ,     10     ,     11      ,     12     ,     13     ,     14     ,     15     ,         */
};

// interaction data (6 bytes per event)
const INTERACTION_INFO interactionData[] PROGMEM =
{
  // currentPos                    currentStatus     nextStatus         newItem              modifiedPos         modifiedPosCellValue
  {  4 + 0 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  5 + 1 * LEVEL_WIDTH  ,      0        },

  {  7 + 0 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },
  {  7 + 0 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },

  {  4 + 1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,    ITEM_COMPASS     ,  4 + 1 * LEVEL_WIDTH  , OPEN_CHEST | E_W},
  {  6 + 1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,    ITEM_SHIELD      ,  6 + 1 * LEVEL_WIDTH  ,  OPEN_CHEST   },

  { 12 + 2 * LEVEL_WIDTH        ,    FOUNTAIN     , FOUNTAIN   ,     ITEM_VICTORY    , 12 + 2 * LEVEL_WIDTH  ,    FOUNTAIN   },

  {  0 + 4 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,     0         },
  {  0 + 4 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,    BARS | E_W   },

  {  8 + 6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,     ITEM_AMULET     ,  8 + 6 * LEVEL_WIDTH  , OPEN_CHEST | N_S},
  { 14 + 6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,ITEM_RING | ITEM_POTION, 14 + 6 * LEVEL_WIDTH  , OPEN_CHEST | E_W},

  {  0 + 12 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,      0        },
  {  0 + 12 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  4 + 12 * LEVEL_WIDTH  ,    BARS | E_W   },

  {  7 + 12 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST , ITEM_KEY | ITEM_COMPASS,  7 + 12 * LEVEL_WIDTH ,  OPEN_CHEST   },
  {  8 + 12 * LEVEL_WIDTH        ,    SWITCH_L     ,    0       ,         0           , 10 + 12 * LEVEL_WIDTH  ,      0        },
  { 11 + 12 * LEVEL_WIDTH        ,    DOOR         ,    0       ,         0           , 11 + 12 * LEVEL_WIDTH  ,      0        },

  {  1 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  1 + 9 * LEVEL_WIDTH  ,    BARS | N_S   },
  {  1 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  1 + 9 * LEVEL_WIDTH  ,      0        },
  {  3 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,    BARS | E_W   },
  {  3 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  4 + 12 * LEVEL_WIDTH  ,      0        },

  { 13 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           , 13 + 7 * LEVEL_WIDTH  ,      0        },
  { 13 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           , 13 + 4 * LEVEL_WIDTH  ,      0        },
};

// special cell effects (4 bytes per FX)
// Note: If there would be a lot more spinners/teleporters/... it would make sense to combine value_1 and value_2 into a single byte.
//       But as it is, saving 5 bytes of data here would increase decoding costs by ~16 bytes, so no deal ;)
const SPECIAL_CELL_INFO specialCellFX[] PROGMEM =
{
  // cell type ,       position       , value_1, value_2
  { TELEPORTER ,  7 + 11 * LEVEL_WIDTH,     5  ,   13    },
  { TELEPORTER ,  7 + 13 * LEVEL_WIDTH,     5  ,   11    },
  { SPINNER    , 10 +  2 * LEVEL_WIDTH,    +2  ,    0    },
  { SPINNER    ,  2 +  5 * LEVEL_WIDTH,    +1  ,    0    },
  { SPINNER    ,  7 +  9 * LEVEL_WIDTH,    +3  ,    0    },
};

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM =
{
  // position                monsterType  hp  bonusDamage   attacksFirst  treasureItemMask
  {   0 +  3 * LEVEL_WIDTH,  RAT        ,  3 ,     -6      ,      1       ,           0                               }, // rat
  {   8 +  1 * LEVEL_WIDTH,  RAT        ,  3 ,     -4      ,      1       ,           0                               }, // rat
  {  12 +  3 * LEVEL_WIDTH,  BEHOLDER   , 40 ,     +7      ,      1       ,           0                               }, // beholder (end boss)
  {   3 +  5 * LEVEL_WIDTH,  RAT        ,  5 ,     -4      ,      1       ,           0                               }, // rat
  {  13 +  6 * LEVEL_WIDTH,  SKELETON   , 15 ,     +4      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   7 +  8 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   3 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     -1      ,      1       ,     ITEM_POTION | ITEM_SWORD              }, // mimic
  {  11 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     +1      ,      0       ,  ITEM_SWORD | ITEM_SHIELD | ITEM_POTION   }, // mimic
  {   3 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {  13 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
};

#else
// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
/*             0       ,     1       ,     2      ,     3        ,     4       ,      5       ,     6       ,     7       ,     8       ,     9      ,     10     ,     11      ,     12     ,     13      ,      14     ,     15     ,       */
/*  0 */     WALL      ,   WALL      ,   WALL     ,    WALL      , WALL        ,    WALL      ,    WALL     ,     0       ,   WALL      ,   WALL     ,     0      ,     0       ,     0      ,      0      ,      0      ,   WALL     , /*  0 */
/*  1 */       0       ,/*START*/ 0  ,  BARS|E_W  ,      0       ,CLOSED_CHEST|E_W ,WALL      ,     0       ,    WALL     ,CLOSED_CHEST|N_S,WALL     ,     0      ,   WALL      ,   WALL     ,    WALL     ,      0      ,   WALL     , /*  1 */
/*  2 */       0       ,     0       ,   WALL     ,      0       ,    WALL     ,      0       ,     0       ,     0       ,     0       ,   WALL     ,/*SPINNER*/0,   WALL      ,  FOUNTAIN  ,    WALL     ,      0      ,   WALL     , /*  2 */
/*  3 */  /* RAT*/ 0   ,   WALL      ,     0      ,      0       ,    WALL     ,      0       ,    WALL     ,     0       ,     0       ,   WALL     ,     0      ,   WALL      ,/*BEHOLDR*/0,    WALL     ,      0      ,   WALL     , /*  3 */
/*  4 */WALL | SWITCH_L,   WALL      ,     0      ,    WALL      ,WALL|SWITCH_L|E_W,  0       ,    WALL     ,     0       ,     0       ,   WALL     ,     0      ,   WALL      ,     0      ,   BARS|E_W  ,      0      ,   WALL     , /*  4 */
/*  5 */     WALL      ,     0       ,     0      , /* RAT*/ 0   ,    WALL     ,    WALL      ,     0       ,     0       ,    WALL     ,   WALL     ,     0      ,   WALL      ,   WALL     ,    WALL     ,    WALL     ,   WALL     , /*  5 */
/*  6 */       0       ,     0       ,   WALL     ,      0       ,      0      ,      0       ,     0       ,    WALL     , CLOSED_CHEST,   WALL     ,     0      ,     0       ,     0      ,/*SKELETON*/0,CLOSED_CHEST|E_W, BARS|E_W, /*  6 */
/*  7 */     WALL      ,   WALL	     ,     0      ,      0       ,    WALL     ,    WALL      ,     WALL     ,    WALL     ,   WALL     ,   WALL     ,   WALL     ,   WALL      ,   WALL     ,   BARS|N_S  ,    WALL     ,   WALL     , /*  7 */
/*  8 */     WALL      , FAKE_WALL   ,     0      ,     0        ,    WALL     ,      0       ,    WALL     ,     0       ,   WALL      ,     0      ,   WALL     ,     0       ,     0      ,      0      ,      0      ,     0      , /*  8 */
/*  9 */     WALL      ,     0       ,   WALL     , FAKE_WALL    ,    WALL     ,      0       ,      0      ,/*SPINNER*/0 ,     0       ,     0      ,   WALL     , BARS | N_S  ,   WALL     ,      0      ,    WALL     ,     0      , /*  9 */
/* 10 */     WALL      ,     0       ,   WALL     ,CLOSED_CHEST  ,    WALL     ,      0       ,    WALL     ,     0       ,   WALL      ,     0      ,   WALL     , /*MIMIC*/ 0 ,   WALL     ,      0      ,      0      ,     0      , /* 10 */
/* 11 */     WALL      ,     0       ,     0      ,   WALL       ,    WALL     ,      0       ,      0      ,/*TELEP.*/ 0 ,     0       ,     0      ,   WALL     ,   WALL      ,     0      ,      0      ,    WALL     ,     0      , /* 11 */
/* 12 */WALL|SWITCH_L|N_S,   WALL    , FAKE_WALL  ,   BARS | E_W ,  BARS | E_W ,      0       ,    WALL     ,CLOSED_CHEST ,WALL|SWITCH_L|E_W, 0      ,     0      ,WALL|DOOR|E_W,     0      ,    WALL     ,      0      ,     0      , /* 12 */
/* 13 */       0       ,     0       ,     0      ,   WALL       ,    WALL     ,      0       ,      0      ,/*TELEP.*/ 0 ,     0       ,     0      ,   WALL     ,     0       ,     0      ,    WALL     ,      0      ,   WALL     , /* 13 */
/* 14 */     WALL      ,   WALL      ,     0      ,/*SKELETON*/0 ,    WALL     ,      0       ,    WALL     ,     0       ,   WALL      ,     0      ,   WALL     ,/*SKELETON*/0,   WALL     ,      0      ,      0      ,     0      , /* 14 */
/* 15 */       0       ,WALL|SWITCH_L|N_S, WALL   ,WALL|SWITCH_L|N_S, WALL     ,      0       ,      0      ,     0       ,     0       ,     0      ,   WALL     ,    WALL     ,   WALL     ,WALL|SWITCH_L|N_S,WALL     ,     0      , /* 15 */
/*             0       ,     1       ,     2      ,     3        ,     4       ,      5       ,     6       ,     7       ,     8       ,     9      ,     10     ,     11      ,     12     ,      13     ,     14      ,     15     ,       */
};

// interaction data (6 bytes per event)
const INTERACTION_INFO interactionData[] PROGMEM =
{
  // currentPos                    currentStatus     nextStatus         newItem              modifiedPos         modifiedPosCellValue
  {  4 + 4 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  8 + 5 * LEVEL_WIDTH  ,      0        },

  {  7 + 0 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },
  {  7 + 0 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },

  {  4 + 1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,    ITEM_COMPASS     ,  4 + 1 * LEVEL_WIDTH  , OPEN_CHEST | E_W},
  {  8 + 1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,    ITEM_SHIELD      ,  8 + 1 * LEVEL_WIDTH  ,  OPEN_CHEST   },

  { 12 + 2 * LEVEL_WIDTH        ,    FOUNTAIN     , FOUNTAIN   ,     ITEM_VICTORY    , 12 + 2 * LEVEL_WIDTH  ,    FOUNTAIN   },

  {  0 + 4 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,     0         },
  {  0 + 4 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  2 + 1 * LEVEL_WIDTH  ,    BARS | E_W   },

  {  8 + 6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,     ITEM_AMULET     ,  8 + 6 * LEVEL_WIDTH  , OPEN_CHEST | N_S},
  { 14 + 6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST ,ITEM_RING | ITEM_POTION, 14 + 6 * LEVEL_WIDTH  , OPEN_CHEST | E_W},

  {  0 + 12 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,      0        },
  {  0 + 12 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  4 + 12 * LEVEL_WIDTH  ,    BARS | E_W   },

  {  7 + 12 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST , ITEM_KEY | ITEM_COMPASS,  7 + 12 * LEVEL_WIDTH ,  OPEN_CHEST   },
  {  8 + 12 * LEVEL_WIDTH        ,    SWITCH_L     ,    0       ,         0           , 10 + 12 * LEVEL_WIDTH  ,      0        },
  { 11 + 12 * LEVEL_WIDTH        ,    DOOR         ,    0       ,         0           , 11 + 12 * LEVEL_WIDTH  ,      0        },

  {  1 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  1 + 9 * LEVEL_WIDTH  ,    BARS | N_S   },
  {  1 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  1 + 9 * LEVEL_WIDTH  ,      0        },
  {  3 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,    BARS | E_W   },
  {  3 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           ,  4 + 12 * LEVEL_WIDTH  ,      0        },

  { 13 + 15 * LEVEL_WIDTH        ,    SWITCH_L     , SWITCH_R   ,         0           , 13 + 7 * LEVEL_WIDTH  ,      0        },
  { 13 + 15 * LEVEL_WIDTH        ,    SWITCH_R     , SWITCH_L   ,         0           , 13 + 4 * LEVEL_WIDTH  ,      0        },
};

// special cell effects (4 bytes per FX)
// Note: If there would be a lot more spinners/teleporters/... it would make sense to combine value_1 and value_2 into a single byte.
//       But as it is, saving 5 bytes of data here would increase decoding costs by ~16 bytes, so no deal ;)
const SPECIAL_CELL_INFO specialCellFX[] PROGMEM =
{
  // cell type ,       position       , value_1, value_2
  { TELEPORTER ,  7 + 11 * LEVEL_WIDTH,     5  ,   13    },
  { TELEPORTER ,  7 + 13 * LEVEL_WIDTH,     5  ,   11    },
  { SPINNER    , 10 +  2 * LEVEL_WIDTH,    +2  ,    0    },
  //{ SPINNER    ,  2 +  5 * LEVEL_WIDTH,    +1  ,    0    },
  { SPINNER    ,  7 +  9 * LEVEL_WIDTH,    +3  ,    0    },
};

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM =
{
  // position                monsterType  hp  bonusDamage   attacksFirst  treasureItemMask
  {   0 +  3 * LEVEL_WIDTH,  RAT        ,  3 ,     -6      ,      1       ,           0                               }, // rat
  {   8 +  2 * LEVEL_WIDTH,  RAT        ,  3 ,     -4      ,      1       ,           0                               }, // rat
  {  12 +  3 * LEVEL_WIDTH,  BEHOLDER   , 40 ,     +7      ,      1       ,           0                               }, // beholder (end boss)
  {   3 +  5 * LEVEL_WIDTH,  RAT        ,  5 ,     -4      ,      1       ,           0                               }, // rat
  {  13 +  6 * LEVEL_WIDTH,  SKELETON   , 15 ,     +4      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   7 +  8 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   3 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     -1      ,      1       ,     ITEM_POTION | ITEM_SWORD              }, // mimic
  {  11 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     +1      ,      0       ,  ITEM_SWORD | ITEM_SHIELD | ITEM_POTION   }, // mimic
  {   3 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {  13 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
};

#endif