#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"
#include "externBitmaps.h"

// use nice shading effect, giving more depth
#define _ENABLE_WALL_SHADING_
// use object shading, reduces clarity (not recommended)
#define _ENABLE_OBJECT_SHADING_

// uncomment this line to make the player invincible
//#define _GODMODE_

// uncomment this to slowly kill the player (required for testing)
//#define _SLOW_DEATH

// used for vertical addressing mode - this is still experimental but should be able to
// speed up the whole drawing a lot... let's see...
#define _VERTICAL_RENDERING

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
  void /*__attribute__ ((noinline))*/ renderImage();
  // bitmap drawing functions
  void renderDungeonColumn( const uint8_t x );
#if defined(__AVR_ATtiny85__)
  uint8_t __attribute__ ((noinline)) getDownScaledBitmapData( uint8_t x, uint8_t y, 
                                   const uint8_t distance, const NON_WALL_OBJECT *object,
                                   bool useMask );
#else
  uint8_t getDownScaledBitmapData( uint8_t x, uint8_t y,
                                   const uint8_t distance, const NON_WALL_OBJECT* object,
                                   bool useMask);
#endif
  uint8_t lightingMask( const uint8_t &viewDistance );
};

// TODO: find a more apropriate place for this table
// lighting mask inclusive fade in and out
const uint8_t lightingTable[] PROGMEM = { 0b11111111, 0b11111111, // distance 0
                                          0b11111111, 0b11111111, // distance 1
                                          0b01010101, 0b10101010, // distance 2
                                          0b10001000, 0b00100100, // distance 3
                                          0b00000000, 0b00000000, // distance 4
                                          0b00000000, 0b00000000, // distance 5
                                          0b00000000, 0b00000000, // distance 6
                                          0b00000000, 0b00000000  // distance 7
                                        };
