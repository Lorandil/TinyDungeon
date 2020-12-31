#ifndef _DUNGEON_TYPES_H_
#define _DUNGEON_TYPES_H_

const uint8_t MAX_LEVEL_BYTES = 128;

typedef struct 
{
  int8_t playerX;
  int8_t playerY;
  uint8_t dir;
  
  uint8_t levelHeight;
  uint8_t levelWidth;
  uint8_t currentLevel[MAX_LEVEL_BYTES];
  
} DUNGEON;

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

typedef struct 
{
  uint8_t itemType;
  uint8_t bitmapWidth;
  uint8_t maskOffset;
  uint8_t nextLineOffset;
  uint8_t maxViewDistance;
  uint8_t scalingThreshold[3];
  const uint8_t* itemBitmap;
  
} NON_WALL_OBJECT;

// information for single wall display
typedef struct
{
  // wall bitmap to use
  const uint8_t *wallBitmap;
  // screen start position for this bitmap
  int8_t   startPosX;
  // screen end position for this bitmap
  int8_t   endPosX;
  // view distance of this object
  int8_t   viewDistance;
  // offset to left or right
  int8_t   leftRightOffset;
  // object selector, e.g. WALL
  uint8_t  objectMask;
} SIMPLE_WALL_INFO;

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
  //DOOR                = 0x02,// | FLAG_SOLID,
  //BARS                = 0x03,// | FLAG_SOLID,
  STAIRS_UP           = 0x04 | FLAG_SOLID,
  STAIRS_DOWN         = 0x05 | FLAG_SOLID,

  GOBLIN              = 0x10,
  SKELETON            = 0x20,
  BEHOLDER            = 0x30,
  ITEM_KEY            = 0x40,
  ITEM_GOLD           = 0x50,
  ITEM_FOUNTAIN       = 0x60,
  DOOR                = 0x70 | FLAG_SOLID,
  BARS                = 0x80 | FLAG_SOLID,
};

#endif
