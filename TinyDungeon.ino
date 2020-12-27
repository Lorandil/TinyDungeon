//   >>>>>  T-I-N-Y  D-U-N-G-E-O-N v0.1 for ATTINY85  GPLv3 <<<<
//						Tinyjoypad rev2 compatible
//                   Programmer: Sven B 2020
//              Contact EMAIL: 

//the code works at 16MHZ internal
//and use ssd1306xled Library for SSD1306 oled display 128x64

#include <ssd1306xled.h>
#include "Dungeon.h"
#include "spritebank.h"
#include "bitTables.h"
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
  #ifdef _USE_SH1106_
    // SH1106 internally uses 132 pixels/line,
    // output is (mostly?) centered, so we need to start at position 2
    SSD1306.ssd1306_send_command(0x02);
    SSD1306.ssd1306_send_command(0x10);  
  #else
    // classic SSD1306 supports only 128 pixels/line, so we start at 0
    SSD1306.ssd1306_send_command(0x00);
    SSD1306.ssd1306_send_command(0x10);  
  #endif    
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
  uint8_t pixels = 0;

  SIMPLE_WALL_INFO wallInfo;
  
  SIMPLE_WALL_INFO *wallInfoPtr = arrayOfWallInfo;

  // all objects are visible
  int8_t maxObjectDistance = 4;

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
          pixels = pgm_read_byte( wallInfo.wallBitmap + y * 96 + x );
        }
        else
        {
          pixels = pgm_read_byte( wallInfo.wallBitmap + y * 96 + 95 - x );
        }
        // objects behind walls not invisible
        maxObjectDistance = wallInfo.viewDistance - 1;
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }

  // display NWOs (Non Wall Objects)
  for ( uint8_t d = maxObjectDistance; d > 0; d-- )
  {
    for ( uint8_t n = 0; n < sizeof( objectList ) / sizeof( objectList[0] ); n++ )
    {
      // center?
      if ( ( x >= 32 ) && ( x < 64 ) )
      {
        NON_WALL_OBJECT object;
        memcpy_P( &object, &objectList[n], sizeof( object ) );
        
        if ( ( *( getCell( playerX, playerY, d, 0, dir ) ) & OBJECT_MASK ) == object.itemType )
        {
          if ( d == 3 )
          {
            d++;
          }
          pixels &= getDownScaledBitmapData( x - 32, y, d, object.itemBitmap + object.maskOffset, object.nextLineOffset );
          pixels |= getDownScaledBitmapData( x - 32, y, d, object.itemBitmap, object.nextLineOffset );
          
          //pixels &= pgm_read_byte( object.itemBitmap + y * object.nextLineOffset + ( x - 32 ) + object.maskOffset );
          //pixels |= pgm_read_byte( object.itemBitmap + y * object.nextLineOffset + ( x - 32 ) );
        }
      }
    }
  }
  
  return( pixels );
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
    if ( ( *( getCell( playerX, playerY, 1, 0, dir ) ) & FLAG_SOLID ) != FLAG_SOLID )
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
    if ( ( *( getCell( playerX, playerY, -1, 0, dir ) ) & FLAG_SOLID ) != FLAG_SOLID )
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

/*--------------------------------------------------------*/
// Returns the downscaled bitmap data at position x,y.
// Supported scaling values are 1, 2, 4
uint8_t getDownScaledBitmapData( uint8_t x, uint8_t y, const uint8_t scaleFactor, 
                                 const uint8_t *bitmapData, const uint8_t bitmapWidth )
{
  uint8_t pixels = 0;

  // correct x position
  x = x * scaleFactor;
  y = y * scaleFactor;

  // calculate start address
  uint8_t *data = bitmapData + y * bitmapWidth + x;
  
  uint8_t bitNo = 0;

  switch( scaleFactor )
  {
    case 2:

      for ( uint8_t n = 0; n < 8; n++ )
      {
        uint8_t bitSum = 0;
        
        for ( uint8_t row = 0; row < scaleFactor; row++ )
        {
          for ( uint8_t col = 0; col < scaleFactor; col++ )
          {
            bitSum += pgm_read_byte( nibbleBitCount + ( ( pgm_read_byte( data++ ) >> ( bitNo << 1 ) ) & 0x03 ) );
          }
          data -= scaleFactor;
        }

        if ( bitSum >= 2 )
        {
          pixels |= ( 1 << n );
        }

        // next output bit
        bitNo++;
        
        if ( bitNo == 4 )
        {
          // a new byte will begin...
          bitNo = 0;
          // address next 8-pixel row
          data += bitmapWidth;
        }
      }
      break;
      
    case 4:
      break;  
      
    // simple... no down scaling
    case 1:
    default:
      pixels = pgm_read_byte( data );
      break;
  }

  return( pixels );  
}
