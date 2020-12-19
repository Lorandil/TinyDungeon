//   >>>>>  T-I-N-Y  D-U-N-G-E-O-N v0.1 for ATTINY85  GPLv3 <<<<
//						Tinyjoypad rev2 compatible
//                   Programmer: Sven B 2020
//              Contact EMAIL: 

//the code works at 16MHZ internal
//and use ssd1306xled Library for SSD1306 oled display 128x64

#include <ssd1306xled.h>
#include "Dungeon.h"
#include "smallFont.h"
#include "TinyJoystickControls.h"

int8_t playerX = 6;
int8_t playerY = 2;
uint8_t dir  = NORTH;

uint8_t levelHeight;
uint8_t levelWidth;
const uint8_t MAX_LEVEL_BYTES = 128;
const uint8_t currentLevel[MAX_LEVEL_BYTES];

/*--------------------------------------------------------*/
void setup()
{
  SSD1306.ssd1306_init();
  // not using 'pinMode()' here saves ~100 bytes of flash!
  // configure A0, A3 and D1 as input
  DDRB &= ~( ( 1 << PB5) | ( 1 << PB3 ) | ( 1 << PB1 ) );
  // configure A2 as output
  DDRB |= ( 1 << PB4 );
}

/*--------------------------------------------------------*/
void loop()
{
  // Prepare first level
  LEVEL_HEADER *header = (LEVEL_HEADER *)Level_1;
  levelWidth = header->width;
  levelHeight = header->height;
  // copy the level data to RAM
  memcpy_P( currentLevel, Level_1 + sizeof( LEVEL_HEADER ), levelWidth * levelHeight );

  while( 1 )
  {
    Tiny_Flip();
  
    // update player's position and orientation
    checkPlayerMovement();
  }
}

/*--------------------------------------------------------*/
void Tiny_Flip()
{
  for ( uint8_t y = 0; y < 8; y++)
  {
    // initialize image transfer to segment 'y'
    SSD1306.ssd1306_send_command(0xb0 + y);
    SSD1306.ssd1306_send_command(0x00); 
    SSD1306.ssd1306_send_command(0x10);  
    SSD1306.ssd1306_send_data_start();
    
    for ( uint8_t x = 0; x < 96; x++ )
    {
      uint8_t pixels = getWallPixels( x, y );
      SSD1306.ssd1306_send_byte( pixels );
    } // for x

    // display the dashboard here (later)
    for ( uint8_t x = 96; x < 128; x++)
    {
      SSD1306.ssd1306_send_byte( 0 );
    }
    
    // this line appears to be optional, as it was never called during the intro screen...
    // but hey, we still have some bytes left ;)
    SSD1306.ssd1306_send_data_stop();
  } // for y
}

/*--------------------------------------------------------*/
uint8_t getWallPixels( const int8_t x, const int8_t y )
{
  uint8_t pixel = 0;

  SIMPLE_WALL_INFO wallInfo;
  
  SIMPLE_WALL_INFO *wallInfoPtr = arrayOfWallInfo;

  // iterate through the whole list (at least as long as it's necessary)
  while( true )
  {
    // the structure resides in PROGMEM, so we need to copy it to RAM first...
    memcpy_P( &wallInfo, wallInfoPtr, sizeof( wallInfo ) );

    // end of list reached?
    if ( wallInfo.wallBitmap == NULL ) { break; }

    // check conditions
    if ( ( x >= wallInfo.startPosX ) && ( x <= wallInfo.endPosX ) )
    {
      if ( ( *( getCell( playerX, playerY, wallInfo.viewDistance, wallInfo.leftRightOffset, dir ) ) & WALL_MASK ) == wallInfo.objectMask )
      {
        if ( ( playerX + playerY ) & 0x01 )
        {
          pixel = pgm_read_byte( wallInfo.wallBitmap + y * 96 + x );
        }
        else
        {
          pixel = pgm_read_byte( wallInfo.wallBitmap + y * 96 + 95 - x );
        }
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }
  
  return( pixel );
}

/*--------------------------------------------------------*/
// Returns a pointer to the cell which is 
// - 'distance' away 
// - in direction 'orientation'
// - from position 'x', 'y'
// This function supports a wrap-around, so endless corridors are possible :)
uint8_t *getCell( int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation )
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

  limitDungeonPosition( x, y );

  return( currentLevel + y * levelWidth + x );
}

/*--------------------------------------------------------*/
void checkPlayerMovement()
{
  if ( isLeftPressed() ) 
  {
    // turn left
    dir = ( dir - 1 ) & 0x03;
    stepSound();
  }
  if ( isRightPressed() )
  {
    // turn right
    dir = ( dir + 1 ) & 0x03;
    stepSound();
  }

  if ( isUpPressed() )
  {
    if ( ( *( getCell( playerX, playerY, 1, 0, dir ) ) & WALL_MASK ) != WALL )
    {
      stepSound();
      stepSound();
      
      switch( dir )
      {
        case NORTH:
          playerY--;
          break;
        case EAST:
          playerX++;
          break;
        case SOUTH:
          playerY++;
          break;
        case WEST:
          playerX--;
          break;
      }
    }
    else
    {
      wallSound();
    }
  }
  if ( isDownPressed() )
  {
    if ( ( *( getCell( playerX, playerY, -1, 0, dir ) ) & WALL_MASK ) != WALL )
    {
      stepSound();
      stepSound();
  
      switch( dir )
      {
        case NORTH:
          playerY++;
          break;
        case EAST:
          playerX--;
          break;
        case SOUTH:
          playerY--;
          break;
        case WEST:
          playerX++;
          break;
      }
    }
    else
    {
      wallSound();
    }
  }
  
  // limit the positions
  limitDungeonPosition( playerX, playerY );
}

/*--------------------------------------------------------*/
// Limits the position in the dungeon, but enables wrap-around :)
void limitDungeonPosition( int8_t &x, int8_t &y )
{
  if ( x < 0 ) { x += levelWidth; }
  if ( x >= levelWidth ) { x -= levelWidth; }
  if ( y < 0 ) { y += levelHeight; }
  if ( y >= levelHeight ) { y -= levelHeight; }
}

/*--------------------------------------------------------*/
void stepSound()
{
  Sound( 100,1 );
  Sound( 200,1 );
  _delay_ms( 100 );
}

/*--------------------------------------------------------*/
void wallSound()
{
  Sound( 50,1 );
  _delay_ms( 100 );
}

/*--------------------------------------------------------*/
void swordSound()
{
  Sound( 50,100 );
}
