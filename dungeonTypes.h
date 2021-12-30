#pragma once

#include <Arduino.h>

#if !defined(__AVR_ATtiny85__)
  #include "SerialHexTools.h"
#endif

const uint8_t LEVEL_WIDTH = 16;
const uint8_t LEVEL_HEIGHT = 16;
const uint16_t MAX_LEVEL_BYTES = LEVEL_WIDTH * LEVEL_HEIGHT;

const uint8_t MAX_MONSTERS = 8;
const uint8_t MONSTER_INDEX_MASK = ( MAX_MONSTERS - 1 );

const uint8_t WINDOW_SIZE_X   = 96;
const uint8_t WINDOW_CENTER_X = WINDOW_SIZE_X / 2; /* = 48 */
const uint8_t WINDOW_SIZE_Y   = 64;
const uint8_t WINDOW_CENTER_Y = WINDOW_SIZE_Y / 2; /* = 32 */

// this position is true for every cell
const uint8_t ANY_POSITION = 0xff;

// text positions
const uint8_t POS_COMPASS     = 0 * 8 + 4;
const uint8_t POS_HITPOINTS   = 4 * 8 + 5;
const uint8_t POS_DAMAGE      = 5 * 8 + 5;
const uint8_t POS_KEYS        = 6 * 8 + 5;

// we will be using an old fashioned D8 (counting from 0 to 7)
const uint8_t MAX_DICE_VALUE  = 0x07;

// possible item types
enum
{
  // bit 7 is reserved for marking objects as "SOLID", making them impassable
  FLAG_SOLID          = 0x08,

  WALL_MASK           = 0x10,
  OBJECT_MASK         = 0xF0 | FLAG_SOLID,
  // mask for retreiving the index from the cell data (used for managing monsters)
  INDEX_MASK          = 0x07,

  EMPTY               = 0x00,

  // Caution! The following objects are always rendered *on* a wall,
  // so the wall bit (0) is always set!
  FAKE_WALL           = 0x10,
  WALL                = FAKE_WALL | FLAG_SOLID,
  DOOR                = 0x30	| FLAG_SOLID,
  LVR_UP              = 0x50	| FLAG_SOLID,
  LVR_DWN             = 0x70	| FLAG_SOLID,

  // Caution! The following objects are *never* rendered on a wall,
  // so the wall bit (0) must be '0'
  RAT                 = 0x20, // | FLAG_SOLID,
  SKELETON            = 0x40, // | FLAG_SOLID,
  BEHOLDER            = 0x60, // | FLAG_SOLID,
  CLOSED_CHEST        = 0x80, // | FLAG_SOLID,
  OPEN_CHEST          = 0xA0, // | FLAG_SOLID,
  FOUNTAIN            = 0xC0 | FLAG_SOLID,
  BARS                = 0xE0 | FLAG_SOLID,
};

// special FX types
enum 
{
  TELEPORTER          = 0x01,
  SPINNER             = 0x02,
};

// list of items in chests or monster treasure
enum
{
  ITEM_NONE    = 0x00,
  ITEM_COMPASS = 0x01,
  ITEM_AMULET  = 0x02,
  ITEM_RING    = 0x04,
  ITEM_KEY     = 0x08,
  ITEM_POTION  = 0x10,
  ITEM_VICTORY = 0x80,
};


// monster stats
class MONSTER_STATS
{
  public:
  // monster position (byte offset from level start)
  uint8_t position;
  // hit points
  int8_t  hitpoints;
  // damage (additional to 1D8)
  int8_t  damageBonus;
  // monster attacks first?
  uint8_t attacksFirst;
  // treasure (bit mask)
  uint8_t treasureMask;
#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.print( F("  position     = ( ") ); Serial.print( position % LEVEL_WIDTH ); Serial.print(F(",")); Serial.print( position / LEVEL_WIDTH ); Serial.println(F(")"));
    Serial.print( F("  hitpoints    = ") ); Serial.println( hitpoints );
    Serial.print( F("  damageBonus  = (") ); Serial.println( damageBonus );
    Serial.print( F("  attacksFirst = (") ); Serial.println( ( attacksFirst != 0 ) ? "yes" : "no" );
    Serial.print( F("  treasureMask = (") ); Serial.println( treasureMask );
    Serial.println();
  }
#endif
};


// DUNGEON
class DUNGEON
{
public:
  int8_t  playerX;
  int8_t  playerY;
  uint8_t dir;
  int8_t  playerHP;
  int8_t  playerDAM;
  int8_t  playerKeys;
  bool    playerHasCompass;
  bool    playerHasAmulet; 
  uint8_t playerHasRing;    /* 0x00 if player has no ring, 0xFF if he/she has the ring */
  int8_t  dice;
  uint8_t displayXorEffect;
  uint8_t currentLevel[MAX_LEVEL_BYTES];
  MONSTER_STATS monsterStats[MAX_MONSTERS];

  static constexpr uint8_t getLevelWidth() { return( LEVEL_WIDTH ); }
  static constexpr uint8_t getLevelHeight() { return( LEVEL_HEIGHT ); }

#if !defined(__AVR_ATtiny85__)
  void serialPrint()
  {
    Serial.println(F("DUNGEON") );
    Serial.print(F("  playerX = ") );Serial.print( playerX );
    Serial.print(F(", playerY = ") );Serial.print( playerY );
    Serial.print(F(", dir = ") );Serial.print( dir );
    Serial.print(F(", HP = ") );Serial.print( playerHP );
    Serial.print(F(", DAM = ") );Serial.print( playerDAM );
    Serial.print(F(", Keys = ") );Serial.print( playerKeys );
    Serial.print(F(", Compass = ") );Serial.print( playerHasCompass );
    Serial.print(F(", displayXorEffect = ") );Serial.print( displayXorEffect );
    Serial.println(F(" )") );

    for ( uint8_t y = 0; y < LEVEL_HEIGHT; y++ )
    {
      for( uint8_t x = 0; x < LEVEL_WIDTH; x++ )
      {
        uint8_t cellValue = currentLevel[y * LEVEL_WIDTH + x];
        Serial.print( ( cellValue & FLAG_SOLID )                              ? F("s")  : F("-") );
        Serial.print( ( cellValue & WALL_MASK ) == FAKE_WALL                  ? F("W")  : F("-") );
        Serial.print( ( cellValue & ( SKELETON | FLAG_SOLID ) ) == SKELETON   ? F("S")  : F("-") );
        Serial.print( ( cellValue & ( BEHOLDER | FLAG_SOLID ) ) == BEHOLDER   ? F("B")  : F("-") );
        Serial.print( ( cellValue & OBJECT_MASK ) == DOOR                     ? F("D")  : F("-") );
        Serial.print( ( cellValue & OBJECT_MASK ) == BARS                     ? F("#")  : F("-") );
        Serial.print( ( cellValue & OBJECT_MASK ) == LVR_UP                   ? F("u")
                                                                              : ( cellValue & OBJECT_MASK ) == LVR_DWN ? F("d")
                                                                                                                       : F("-") );
        Serial.print( F("   ") );
      }
    Serial.println();
    }
    Serial.println();
    //hexdumpResetPositionCount();
    //hexdumpToSerial( currentLevel, LEVEL_WIDTH * LEVEL_HEIGHT );
  }
#endif
};

/*
// LEVEL_HEADER
typedef struct
{
  // width x height
  int8_t width;
  int8_t height;
  // stairs up
  int8_t upX;
  int8_t upY;
  // stairs down
  int8_t downX;
  int8_t downY;
  // level number
  int8_t levelNumber;
  
} LEVEL_HEADER;
*/

// NON_WALL_OBJECT
class NON_WALL_OBJECT
{
  public:
  
  uint8_t itemType;
  uint8_t bitmapWidth;
  uint8_t bitmapVerticalOffsetInBits;
  uint8_t bitmapHeightInBits;
  uint8_t nextLineOffset;
  uint8_t maxViewDistance;
  uint8_t scalingThreshold[3];
  const uint8_t *bitmapData;

#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.println( F("NON_WALL_OBJECT") );
    Serial.print( F("  itemType                     = ") );Serial.println( itemType );
    Serial.print( F("  bitmapWidth                  = ") );Serial.print( bitmapWidth );Serial.println();
    Serial.print( F("  bitmapVerticalOffsetInBytes  = ") );Serial.print( bitmapVerticalOffsetInBits );Serial.println();
    Serial.print( F("  bitmapHeightInBytes          = ") );Serial.print( bitmapHeightInBits );Serial.println();
    Serial.print( F("  nextLineOffset               = ") );Serial.println( nextLineOffset );
    Serial.print( F("  maxViewDistance              = ") );Serial.println( maxViewDistance );
    Serial.print( F("  scalingThreshold[0]          = ") );Serial.print( scalingThreshold[1] );Serial.println();
    Serial.print( F("  scalingThreshold[1]          = ") );Serial.print( scalingThreshold[2] );Serial.println();
    Serial.print( F("  scalingThreshold[2]          = ") );Serial.print( scalingThreshold[3] );Serial.println();
    Serial.println();
  }
#endif  
};


// information for single wall display
// SIMPLE_WALL_INFO
class SIMPLE_WALL_INFO
{
  public:
	
  // wall bitmap to use
  const uint8_t *wallBitmap;
  // screen start position for this bitmap
  int8_t   startPosX;
  // screen end position for this bitmap
  int8_t   endPosX;
  // vertical start position in bytes
  int8_t   startPosY;
  // vertical end position in bytes
  int8_t   endPosY;
  // view distance of this object
  int8_t   viewDistance;
  // offset to left or right
  int8_t   leftRightOffset;
  // object selector, e.g. WALL
  uint8_t  objectMask;
};

// interaction information
class INTERACTION_INFO
{
public:
  // position in which the dungeon is interacted with
  uint8_t currentPosition;
  // required status of this position
  uint8_t currentStatus;
  // required mask
  uint8_t currentStatusMask;
  // new status if true
  uint8_t nextStatus;
  // bit coded item number for gained items, i.e. keys
  uint8_t newItem;
  // an amount (of coins or healing)
  uint8_t itemValue;
  // position in which the dungeon will be modified
  uint8_t modifiedPosition;
  // new status on modified position
  uint8_t modifiedPositionCellValue;

#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.println( F("INTERACTION_INFO") );
    Serial.print( F("  currentPosition    = ") );if ( currentPosition == ANY_POSITION ) { Serial.println( F("ANY_POSITION") ); } else { Serial.println( currentPosition ); }
    Serial.print( F("  currentStatus      = ") );printHexToSerial( currentStatus );Serial.println();
    Serial.print( F("  currentStatusMask  = ") );printHexToSerial( currentStatusMask );Serial.println();
    Serial.print( F("  nextStatus         = ") );printHexToSerial( nextStatus );Serial.println();
    Serial.print( F("  newItem            = ") );printHexToSerial( newItem );Serial.println();
    Serial.print( F("  itemValue          = ") );Serial.println( itemValue );
    Serial.print( F("  modifiedPosition   = ") );if ( modifiedPosition == ANY_POSITION ) { Serial.println( F("ANY_POSITION") ); } else { Serial.println( modifiedPosition ); }
    Serial.print( F("  modifiedPosValue   = ") );printHexToSerial( modifiedPositionCellValue );Serial.println();
    Serial.println();
  }
#endif
};

// interaction information
class SPECIAL_CELL_INFO
{
public:
  // cell type
  uint8_t specialFX;
  // combined xy-position of the effect (as byte offset from level start)
  uint8_t position;
  // additional parameter 1 (target position x, ...)
  uint8_t value_1;
  // additional parameter 2 (target position y, ...)
  uint8_t value_2;

#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.print( F("  specialFX    = ") );if ( specialFX == TELEPORTER ) { Serial.println( F("TELEPORTER") ); } else { Serial.println( F("SPINNER") ); }
    //Serial.print( F("  position     = (") );Serial.print( position % LEVEL_WIDTH ); Serial.print( F(", ") );Serial.print( position / LEVEL_WIDTH );Serial.println( F(")"));
    Serial.print( F("  value        = (") );Serial.print( value_1 ); Serial.print( F(", ") );Serial.print( value_2 );Serial.println( F(")"));
    Serial.println();
  }
#endif
};

// orientations
enum 
{
  NORTH = 0,
  UP    = NORTH,
  EAST  = 1,
  RIGHT = EAST,
  SOUTH = 2,
  DOWN  = SOUTH,
  WEST  = 3,
  LEFT  = WEST,
  MAX_ORIENTATION = 4,
};
