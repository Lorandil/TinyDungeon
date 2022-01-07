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
#include "bitTables.h"
#include "smallFont.h"
#include "tinyJoypadUtils.h"
//#include "textUtils.h"
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
  clearDungeon( &_dungeon );

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

  while( _dungeon.playerHP > 0 )
  {
    // update the status pane and render the screen
    Tiny_Flip( &_dungeon );

    // update player's position and orientation
    checkPlayerMovement( &_dungeon );
  }

  // player is dead... turn dungeon to black
  clearDungeon( &_dungeon );

  // update the status pane and render the screen
  Tiny_Flip( &_dungeon );

  while ( !isFirePressed() );
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
  bool disableFlashEffect = dungeon->displayXorEffect | dungeon->invertMonsterEffect | dungeon->invertStatusEffect;;
  dungeon->displayXorEffect = 0;
  /*
  dungeon->invertMonsterEffect = 0;
  dungeon->invertStatusEffect = 0;
  */

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
      
      for ( int n = 0; n < int( sizeof( specialCellFX ) / sizeof( specialCellFX[0] ) ); n++ )
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
          /////////////////////////////////////////////
          // find the monster...
          MONSTER_STATS *monster = findMonster( dungeon, cell - dungeon->currentLevel );


          /////////////////////////////////////////////
          // player attacks monster
          playerAttack( dungeon, monster );

          // wait for fire button to be released (random number generation!)
          while ( isFirePressed() )
          {
            updateDice( dungeon );
          }

          // update the status pane and render the screen (monster will be inverted)
          Tiny_Flip( dungeon );
          // redraw with normal monster (so that the monster appears to have flashed)
          Tiny_Flip( dungeon );


          /////////////////////////////////////////////
          // is the monster still alive?
          if ( monster->hitpoints > 0 )
          {
            // just wait a moment (for the display effect to be visible)
            _delay_ms( 250 );
            
            // now let the monster attack the player            
            monsterAttack( dungeon, monster );

            // update the status pane and render the screen
            Tiny_Flip( dungeon );

            // just wait a moment (for the display effect to be visible)
            //_delay_ms( 100 );
          }
          else
          {
            // the monster has been defeated!
            serialPrintln(F("Monster defeated!"));
            // remove the monster from the dungeon
            *cell = EMPTY;
            // remove line from monster list?
            // maybe later... just unnecessary code!
          }

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
