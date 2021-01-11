//   >>>>>  T-I-N-Y  D-U-N-G-E-O-N v0.1 for ATTINY85  GPLv3 <<<<
//						Tinyjoypad rev2 compatible
//                   Programmer: Sven B 2021
//              Contact EMAIL: 

//the code works at 16MHZ internal
//and use ssd1306xled Library for SSD1306 oled display 128x64

#if defined(__AVR_ATtiny85__)
  #include <ssd1306xled.h>
#else
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display( 128, 64, &Wire, -1 );
#endif
#include "Dungeon.h"
#include "spritebank.h"
#include "bitmapDrawing.h"
#include "bitTables.h"
#include "smallFont.h"
#include "TinyJoypadUtils.h"

DUNGEON _dungeon;

/*--------------------------------------------------------*/
void setup()
{
#if defined(__AVR_ATtiny85__)
  SSD1306.ssd1306_init();
  // not using 'pinMode()' here saves ~100 bytes of flash!
  // configure A0, A3 and D1 as input
  DDRB &= ~( ( 1 << PB5) | ( 1 << PB3 ) | ( 1 << PB1 ) );
  // configure A2 as output
  DDRB |= ( 1 << PB4 );
#else
  // DEBUG version on Controller with serial ports
  Serial.begin( 115200 );
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // use 'pinMode()' for simplicity's sake... any other micro controller has enough flash :)
  pinMode( LEFT_RIGHT_BUTTON, INPUT );
  pinMode( UP_DOWN_BUTTON, INPUT );
  pinMode( FIRE_BUTTON, INPUT );
#endif
}

/*--------------------------------------------------------*/
void loop()
{
  // Prepare the dungeon
  _dungeon.playerX = 6;
  _dungeon.playerY = 2;
  _dungeon.dir  = NORTH;
  // Prepare first level
  LEVEL_HEADER *header = (LEVEL_HEADER *)Level_1;
  _dungeon.levelWidth = header->width;
  _dungeon.levelHeight = header->height;
  // copy the level data to RAM
  memcpy_P( _dungeon.currentLevel, Level_1 + sizeof( LEVEL_HEADER ), _dungeon.levelWidth * _dungeon.levelHeight );

  while( 1 )
  {
    Tiny_Flip( &_dungeon );
  #if !defined(__AVR_ATtiny85__)
    HexDumpDungeon( &_dungeon );
  #endif
  
    // update player's position and orientation
    checkPlayerMovement( &_dungeon );
  }
}

/*--------------------------------------------------------*/
void Tiny_Flip( DUNGEON *dungeon)
{
  for ( uint8_t y = 0; y < 8; y++)
  {
#if defined(__AVR_ATtiny85__)
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
#else
  uint8_t *buffer = display.getBuffer() + y * 128;
#endif
    
    for ( uint8_t x = 0; x < 96; x++ )
    {
      uint8_t pixels = getWallPixels( dungeon, x, y );
      #if defined(__AVR_ATtiny85__)
        SSD1306.ssd1306_send_byte( pixels );
      #else
        *buffer++ = pixels;
      #endif
    } // for x

    // display the dashboard here (later)
    for ( uint8_t x = 96; x < 128; x++)
    {
      #if defined(__AVR_ATtiny85__)
        SSD1306.ssd1306_send_byte( 0 );
      #else
        *buffer++ = 0;
      #endif
    }
    
#if defined(__AVR_ATtiny85__)
    // this line appears to be optional, as it was never called during the intro screen...
    // but hey, we still have some bytes left ;)
    SSD1306.ssd1306_send_data_stop();
#endif
  } // for y

#if !defined(__AVR_ATtiny85__)
  display.display();
#endif
}

/*--------------------------------------------------------*/
void checkPlayerMovement( DUNGEON *dungeon )
{
  // get pointer to cell in front of player
  uint8_t *cell = getCell( dungeon, dungeon->playerX, dungeon->playerY, +1, 0, dungeon->dir );

  if ( isLeftPressed() ) 
  {
    // turn left
    dungeon->dir = ( dungeon->dir - 1 ) & 0x03;
    stepSound();
  }
  if ( isRightPressed() )
  {
    // turn right
    dungeon->dir = ( dungeon->dir + 1 ) & 0x03;
    stepSound();
  }

  if ( isUpPressed() )
  {
    if ( ( ( *cell ) & FLAG_SOLID ) != FLAG_SOLID )
    {
      stepSound();
      stepSound();
      
      switch( dungeon->dir )
      {
        case NORTH:
          dungeon->playerY--; break;
        case EAST:
          dungeon->playerX++; break;
        case SOUTH:
          dungeon->playerY++; break;
        case WEST:
          dungeon->playerX--; break;
      }
    }
    else
    {
      wallSound();
    }
  }
  
  if ( isDownPressed() )
  {
    if ( ( *( getCell( dungeon, dungeon->playerX, dungeon->playerY, -1, 0, dungeon->dir ) ) & FLAG_SOLID ) != FLAG_SOLID )
    {
      stepSound();
      stepSound();
  
      switch( dungeon->dir )
      {
        case NORTH:
          dungeon->playerY++; break;
        case EAST:
          dungeon->playerX--; break;
        case SOUTH:
          dungeon->playerY--; break;
        case WEST:
          dungeon->playerX++; break;
      }
    }
    else
    {
      wallSound();
    }
  }

  // ... and ACTION!
  if ( isFirePressed() )
  {
    #if 0
    if ( ( ( *cell ) & OBJECT_MASK ) == LVR_UP )
    {
      *cell &= ~( LVR_UP );
      *cell |= LVR_DWN;
      swordSound();
    } 
    else if ( ( ( *cell ) & OBJECT_MASK ) == LVR_DWN )
    {
      *cell &= ~( LVR_DWN );
      *cell |= LVR_UP;
      swordSound();
    }
    #else

    INTERACTION_INFO interactionInfo;
    for ( uint8_t n = 0; n < sizeof( interactionData ) / sizeof( INTERACTION_INFO ); n++ )
    {
      // get data from progmem
      memcpy_P( &interactionInfo, interactionData + n, sizeof( INTERACTION_INFO ) );
      
      // does this info cover the current position?
      if ( cell == dungeon->currentLevel + interactionInfo.currentPosition )
      {
        // is the status correct?
        if ( ( *cell & interactionInfo.currentStatusMask ) == interactionInfo.currentStatus )
        {
          // yay!
          *cell = interactionInfo.nextStatus;
          dungeon->currentLevel[interactionInfo.modifiedPosition] = interactionInfo.modifiedPositionCellValue;
          swordSound();
        }
      }


#if 0
// interaction information
typedef struct 
{
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
 
} INTERACTION_INFO;
#endif
    }
    #endif
  }
  
  // limit the positions
  limitDungeonPosition( dungeon, dungeon->playerX, dungeon->playerY );
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
  Sound( 50,10 );
}

#if !defined(__AVR_ATtiny85__)
/*--------------------------------------------------------*/
void HexDumpDungeon( DUNGEON *dungeon )
{
  for ( uint8_t y = 0; y < dungeon->levelHeight; y++ )
  {
    for( uint8_t x = 0; x < dungeon->levelWidth; x++ )
    {
      uint8_t cellValue = dungeon->currentLevel[y * dungeon->levelWidth + x];
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
  Serial.println( F("\n-----------------------------\n") );
}
#endif
