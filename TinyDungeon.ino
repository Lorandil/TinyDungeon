//   >>>>>  T-I-N-Y  D-U-N-G-E-O-N v0.5 for ATTINY85  GPLv3 <<<<
//						Tinyjoypad rev2 compatible
//                   Programmer: Sven B 2021
//              Contact EMAIL: Lorandil@gmx.de

//  Tiny Dungeon is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

// The code works at 16MHZ internal PLL
// and uses the ssd1306xled library for SSD1306 oled display 128x64 (on ATtiny85)
// or the Adafruit_SSD1306 library on any other micro controller.

// To stuff all code and data into the 8192 bytes of the ATtiny85
// the ATTinyCore (v1.5.2) by Spence Konde is recommended.
// The core is available at github: [https://github.com/SpenceKonde/ATTinyCore], just add the
// following board manager to the Arduino IDE: [http://drazzy.com/package_drazzy.com_index.json]
// Please enable LTO (link time optimization) and disable 'millis()' and
// 'micros()'.

// show an 8x8 grid overlay
//#define _SHOW_GRID_OVERLAY

#include "dungeon.h"
#include "spritebank.h"
#include "bitmapDrawing.h"
#include "bitTables.h"
#include "smallFont.h"
#include "tinyJoypadUtils.h"
#include "textUtils.h"
#include "soundFX.h"

DUNGEON _dungeon;

/*--------------------------------------------------------*/
void setup()
{
  // initialize the pins (and serial port if present)
  InitTinyJoypad();
  // perform display initialization
  InitDisplay();
}

/*--------------------------------------------------------*/
void loop()
{
  // zero dungeon structure
  memset( &_dungeon, 0x00, sizeof( _dungeon ) );

  // Prepare the dungeon
  _dungeon.playerX = 5; // could save 4 bytes here, if the whole level is shifted, so that the starting point is at (0,0)
  _dungeon.playerY = 3;
  //_dungeon.dir  = NORTH; // NORTH = 0!
  // prepare player stats
  _dungeon.playerHP = 30;
  _dungeon.playerDAM = 10;
  //_dungeon.playerKeys = 0;  
  //_dungeon.playerHasCompass = false;
  //_dungeon.playerHasAmulett = false;
  //_dungeon.displayXorEffect = 0;

  // Prepare first level
  //LEVEL_HEADER *header = (LEVEL_HEADER *)Level_1;
  //_dungeon.levelWidth = LEVEL_WIDTH;
  //_dungeon.levelHeight = LEVEL_HEIGHT;
  // copy the level data to RAM
  memcpy_P( _dungeon.currentLevel, Level_1 /*+ sizeof( LEVEL_HEADER )*/, _dungeon.getLevelWidth() * _dungeon.getLevelHeight() );

  // populate dungeon with monsters
  memcpy_P( _dungeon.monsterStats, monsterStats, sizeof( monsterStats ) );

  // clear text buffer
  clearTextBuffer();

  while( 1 )
  {
    // update the status pane
    updateStatusPane( &_dungeon );

    // display the dungeon
    Tiny_Flip( &_dungeon );

    // update player's position and orientation
    checkPlayerMovement( &_dungeon );
  }
}

/*--------------------------------------------------------*/
void Tiny_Flip( DUNGEON *dungeon)
{
  uint8_t statusPaneOffset = 0; 

  for ( uint8_t y = 0; y < 8; y++)
  {
    // prepare display of row <y>
    TinyFlip_PrepareDisplayRow( y );
    
    // the first 96 columns are used to display the dungeon
    for ( uint8_t x = 0; x < 96; x++ )
    {
      uint8_t pixels = getWallPixels( dungeon, x, y );
      pixels ^= dungeon->displayXorEffect;
    #ifdef _SHOW_GRID_OVERLAY
      if ( ( x & 0x01 ) && ( y < 7 ) ) { pixels |= 0x80; }
      //if ( ( x & 0x07 ) == 0x07 ) { pixels |= 0x55; }
    #endif      
      // send 8 vertical pixels to the display
      TinyFlip_SendPixels( pixels );
    } // for x

    // display the dashboard here
    for ( uint8_t x = 0; x < 32; x++)
    {
      uint8_t pixels;
      if ( y | dungeon->playerHasCompass )
      {
        pixels = pgm_read_byte( statusPane + statusPaneOffset ) | displayText( x, y );
      }
      else
      {
        pixels = 0;
      }
      // send 8 vertical pixels to the display
      TinyFlip_SendPixels( pixels );

      statusPaneOffset++;
    }
    
    // this row has been finished
    TinyFlip_FinishDisplayRow();
  } // for y

  // display the whole screen
  TinyFlip_DisplayBuffer();
}

/*--------------------------------------------------------*/
void checkPlayerMovement( DUNGEON *dungeon )
{
  // get pointer to cell in front of player
  uint8_t *cell = getCell( dungeon, dungeon->playerX, dungeon->playerY, +1, 0, dungeon->dir );

  // no movement yet
  bool playerHasReachedNewCell = false;
  bool playerAction = false;

  // remember to disable the flashing effect
  bool disableFlashEffect = dungeon->displayXorEffect;
  dungeon->displayXorEffect = 0;

  // stay in this loop until the player does anything (just increase the random counter)
  while ( !playerAction && !disableFlashEffect )
  {
    playerAction = dungeon->displayXorEffect;

    // prepare the dice
    updateDice( dungeon );

    if ( isLeftPressed() ) 
    {
      // turn left
      dungeon->dir = ( dungeon->dir - 1 ) & 0x03;
      stepSound();
      playerAction = true;
    }
    
    if ( isRightPressed() )
    {
      // turn right
      dungeon->dir = ( dungeon->dir + 1 ) & 0x03;
      stepSound();
      playerAction = true;
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
          //case WEST:
          default:  // this saves 4 bytes
            dungeon->playerX--; break;
        }

        // just a small step for a player
        playerHasReachedNewCell = true;
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
          //case WEST:
          default:
            dungeon->playerX++; break;
        }
      
        // just a small step for a player
        playerHasReachedNewCell = true;
      }
      else
      {
        wallSound();
      }
    }

    // always limit the positions
    limitDungeonPosition( dungeon, dungeon->playerX, dungeon->playerY );

    // check for special cell effects like teleporter or spinner
    if ( playerHasReachedNewCell )
    {
      // obviously that's a player action, too
      playerAction = true;
      // log player coordinates
      serialPrint( F("player position = (") ); serialPrint( dungeon->playerX ); serialPrint( F(", ") ); serialPrint( dungeon->playerY ); serialPrintln( F(")") );

      SPECIAL_CELL_INFO specialCellInfo;
      
      for ( int n = 0; n < sizeof( specialCellFX ) / sizeof( specialCellFX[0] ); n++ )
      {
        // copy cell info object from flash to RAM
        memcpy_P( &specialCellInfo, &specialCellFX[n], sizeof( specialCellInfo ) );

        // does this entry refer to the current position?
        if ( specialCellInfo.position == dungeon->playerX + dungeon->playerY * dungeon->getLevelWidth() )
        {
        #if !defined(__AVR_ATtiny85__)
          // print the special effect...
          specialCellInfo.serialPrint();
        #endif

          // teleporter?
          if ( specialCellInfo.specialFX == TELEPORTER )
          {
            dungeon->playerX = specialCellInfo.value_1;
            dungeon->playerY = specialCellInfo.value_2;
          }
          else // it's a spinner
          {
            // modify player's orientation
            dungeon->dir += specialCellInfo.value_1;
            dungeon->dir &= 0x03;
          }
          // *** BAZINGA! ***
          dungeon->displayXorEffect = dungeon->playerHasRing; /* visualize by flashing if player has the <Ring of Orientation>*/
        }
      }
    }
    else
    {
      // ... and ACTION!
      if ( isFirePressed() )
      {
        playerAction = true;

        uint8_t cellValue = *cell;

        #ifdef USE_SERIAL_PRINT
          dungeon->serialPrint();
          Serial.print(F("*cell = "));printHexToSerial( cellValue );Serial.println();
        #endif

        if ( cellValue & FLAG_MONSTER )
        {
          fightMonster( dungeon, cell - dungeon->currentLevel );

        #ifdef USE_SERIAL_PRINT
          dungeon->serialPrint();
          Serial.print(F("*cell = ")); printHexToSerial( cellValue ); Serial.println();
        #endif
        }
        else
        {
          // let's see if there is some scripted interaction...
          playerInteraction( dungeon, cell, cellValue );
        }
      }
    }
  }
}
