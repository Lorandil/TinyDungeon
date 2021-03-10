#ifndef _DUNGEON_TYPES_H_
#define _DUNGEON_TYPES_H_

#if !defined(__AVR_ATtiny85__)
  #include "SerialHexTools.h"
#endif

const uint8_t MAX_LEVEL_BYTES = 128;
const uint8_t WINDOW_SIZE_X   = 96;
const uint8_t WINDOW_CENTER_X = WINDOW_SIZE_X / 2;
const uint8_t WINDOW_SIZE_Y   = 64;
const uint8_t WINDOW_CENTER_Y = WINDOW_SIZE_Y / 2;

// possible item types
enum
{
  // bit 3 is reserved for "SOLID" objects, making them unpassable
  FLAG_SOLID          = 0x08,

  WALL_MASK           = 0x07,
  OBJECT_MASK         = 0xF0 | FLAG_SOLID,

  EMPTY               = 0x00,
  // fake wall
  FAKE_WALL           = 0x01,
  // solid wall
  WALL                = 0x01 | FLAG_SOLID,
  //STAIRS_UP           = 0x04 | FLAG_SOLID,
  //STAIRS_DWN          = 0x05 | FLAG_SOLID,

  //GOBLIN              = 0x10,
  SKELETON            = 0x20,
  BEHOLDER            = 0x30,
  //ITEM_KEY            = 0x40,
  //ITEM_GOLD           = 0x50,
  //ITEM_FOUNTAIN       = 0x60,
  DOOR                = 0x70 | FLAG_SOLID,
  BARS                = 0x80 | FLAG_SOLID,
  LVR_UP              = 0x90 | FLAG_SOLID,
  LVR_DWN             = 0xA0 | FLAG_SOLID,
};

// DUNGEON
#if !defined(__AVR_ATtiny85__)
  class DUNGEON
#else
  typedef struct
#endif
{
public:
  int8_t playerX;
  int8_t playerY;
  uint8_t dir;
  
  uint8_t levelHeight;
  uint8_t levelWidth;
  uint8_t currentLevel[MAX_LEVEL_BYTES];

#if !defined(__AVR_ATtiny85__)
  void serialPrint()
  {
    Serial.println(F("DUNGEON") );
    Serial.print(F("  playerX = ") );Serial.print( playerX );
    Serial.print(F(", playerY = ") );Serial.print( playerY );
    Serial.print(F(", dir = ") );Serial.print( dir );
    Serial.print(F("   ( levelHeight = ") );Serial.print( levelHeight );
    Serial.print(F(", levelWidth  = ") );Serial.print( levelWidth );
    Serial.println(F(" )") );

    for ( uint8_t y = 0; y < levelHeight; y++ )
    {
      for( uint8_t x = 0; x < levelWidth; x++ )
      {
        uint8_t cellValue = currentLevel[y * levelWidth + x];
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
    hexdumpResetPositionCount();
    hexdumpToSerial( currentLevel, levelWidth * levelHeight );
  }
#endif
#if !defined(__AVR_ATtiny85__)
};
#else
} DUNGEON;
#endif


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


// NON_WALL_OBJECT

#if !defined(__AVR_ATtiny85__)
  class NON_WALL_OBJECT
#else
  typedef struct
#endif
{
  public:
  
  uint8_t itemType;
  uint8_t bitmapWidth;
  uint8_t bitmapVerticalOffsetInBytes;
  uint8_t bitmapHeightInBytes;
  uint8_t maskOffset;
  uint8_t nextLineOffset;
  uint8_t maxViewDistance;
  uint8_t scalingThreshold[4];
  const uint8_t *bitmapData;

#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.println( F("NON_WALL_OBJECT") );
    Serial.print( F("  itemType                     = ") );Serial.println( itemType );
    Serial.print( F("  bitmapWidth                  = ") );Serial.print( bitmapWidth );Serial.println();
    Serial.print( F("  bitmapVerticalOffsetInBytes  = ") );Serial.print( bitmapVerticalOffsetInBytes );Serial.println();
    Serial.print( F("  bitmapHeightInBytes          = ") );Serial.print( bitmapHeightInBytes );Serial.println();
    Serial.print( F("  maskOffset                   = ") );Serial.print( maskOffset );Serial.println();
    Serial.print( F("  nextLineOffset               = ") );Serial.println( nextLineOffset );
    Serial.print( F("  maxViewDistance              = ") );Serial.println( maxViewDistance );
    Serial.print( F("  scalingThreshold[1]          = ") );Serial.print( scalingThreshold[1] );Serial.println();
    Serial.print( F("  scalingThreshold[2]          = ") );Serial.print( scalingThreshold[2] );Serial.println();
    Serial.print( F("  scalingThreshold[3]          = ") );Serial.print( scalingThreshold[3] );Serial.println();
    Serial.println();
  }
#endif  

#if defined(__AVR_ATtiny85__)
} NON_WALL_OBJECT;
#else
};
#endif


// information for single wall display
// SIMPLE_WALL_INFO
typedef struct
{
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
  
} SIMPLE_WALL_INFO;

// interaction information
#if !defined(__AVR_ATtiny85__)
  class INTERACTION_INFO
#else
  typedef struct
#endif
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
    Serial.print( F("  currentPosition    = ") );Serial.println( currentPosition );
    Serial.print( F("  currentStatus      = ") );printHexToSerial( currentStatus );Serial.println();
    Serial.print( F("  currentStatusMask  = ") );printHexToSerial( currentStatusMask );Serial.println();
    Serial.print( F("  nextStatus         = ") );printHexToSerial( nextStatus );Serial.println();
    Serial.print( F("  newItem            = ") );printHexToSerial( newItem );Serial.println();
    Serial.print( F("  itemValue          = ") );Serial.println( itemValue );
    Serial.print( F("  modifiedPosition   = ") );Serial.println( modifiedPosition );
    Serial.print( F("  modifiedPosValue   = ") );printHexToSerial( modifiedPositionCellValue );Serial.println();
    Serial.println();
  }
#endif
#if defined(__AVR_ATtiny85__)
} INTERACTION_INFO;
#else
};
#endif

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

#endif
