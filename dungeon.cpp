#include <Arduino.h>

#include "dungeon.h"
#include "dungeonTypes.h"
#include "soundFX.h"
#include "textUtils.h"
#include "tinyJoypadUtils.h"

/*--------------------------------------------------------*/
void clearDungeon( DUNGEON *dungeon )
{
  // zero dungeon structure
  memset( dungeon, 0x00, sizeof( *dungeon ) );
}

/*--------------------------------------------------------*/
// Returns a pointer to the cell which is 
// - 'distance' away 
// - in direction 'orientation'
// - from position 'x', 'y'
// This function supports a wrap-around, so endless corridors are possible :)
uint8_t *getCell( DUNGEON *dungeon, int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation )
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
    //case WEST:
    default:
    {
      x -= distance;
      y -= offsetLR;
      break;
    }
  }

  limitDungeonPosition( dungeon, x, y );

  return( dungeon->currentLevel + y * dungeon->getLevelWidth() + x );
}


/*--------------------------------------------------------*/
// Limits the position in the dungeon, but enables wrap-around :)
void limitDungeonPosition( const DUNGEON *dungeon, int8_t &x, int8_t &y )
{
  if ( x < 0 ) { x += dungeon->getLevelWidth(); }
  if ( x >= dungeon->getLevelWidth() ) { x -= dungeon->getLevelWidth(); }
  if ( y < 0 ) { y += dungeon->getLevelHeight(); }
  if ( y >= dungeon->getLevelHeight() ) { y -= dungeon->getLevelHeight(); }
}


/*--------------------------------------------------------*/
// updates the compass and the player stats
void updateStatusPane( const DUNGEON *dungeon )
{
  clearTextBuffer();

  // display viewing direction
  uint8_t *textBuffer = getTextBuffer();

  // display compass
  textBuffer[POS_COMPASS] = pgm_read_byte( directionLetter + dungeon->dir );

  // and the hitpoints
  convertValueToDigits( dungeon->playerHP, textBuffer + POS_HITPOINTS );

  // and the damage
  convertValueToDigits( dungeon->playerDAM, textBuffer + POS_DAMAGE );

  // and the number of keys
  convertValueToDigits( dungeon->playerKeys, textBuffer + POS_KEYS );
}

/*--------------------------------------------------------*/
// opens a chest
void openChest( DUNGEON *dungeon, INTERACTION_INFO &info )
{
  serialPrintln( F("openChest()") );

  switch( info.newItem )
  {
    case ITEM_COMPASS:
      {
        // a compass will be displayed
        dungeon->playerHasCompass = true;
        // hooray!
        serialPrintln( F("+ <Compass> found!") );
        break;
      }
    case ITEM_AMULET:
      {    
        // fake will be removed
        dungeon->playerHasAmulet = true;
        // remove all fake walls
        uint8_t *currentCell = dungeon->currentLevel;
        while ( currentCell < dungeon->currentLevel + dungeon->getLevelWidth() * dungeon->getLevelHeight() )
        {
          // fake? let's stay with the facts...
          if ( *currentCell == FAKE_WALL ) { *currentCell = EMPTY; }
          currentCell++;
        }
        // hooray!
        serialPrintln( F("+ <Amulet of True Sight> found!") );
        break;
      }
    case ITEM_RING:
      {    
        // spinning and teleporting revealed by flashing the screen
        dungeon->playerHasRing = 0xff;
        // hooray!
        serialPrintln( F("+ <Ring of Orientation> found!") );
        break;
      }
  }
}

/*--------------------------------------------------------*/
void updateDice( DUNGEON *dungeon )
{ 
  dungeon->dice++; 
  dungeon->dice &= DICE_MASK;
  //serialPrint( F("D8 = ")); serialPrintln( dungeon->dice + 1 );
}

/*--------------------------------------------------------*/
// Every single monster is mapped to an entry in the monsterStats table.
// The table size is only (sic!) restricted by the RAM size (change to EEPROM???).
// If no monster is found, everything goes directly to hell :)
MONSTER_STATS *findMonster( DUNGEON *dungeon, const uint8_t position )
{
  serialPrint(F("findMonster( position = (")); serialPrint( position % dungeon->getLevelWidth()); serialPrint(F(", ")); serialPrint( position / dungeon->getLevelWidth());serialPrintln(F(") )"));

  // no monster found
  MONSTER_STATS *monster = dungeon->monsterStats;

#ifdef USE_EXTENDED_CHECKS
  MONSTER_STATS *maxMonster = monster + sizeof( dungeon->monsterStats ) / sizeof( dungeon->monsterStats[0] );
#endif

  // find the monster
  while ( true  )
  {
    if ( monster->position == position )
    {
      // monster found!
      serialPrintln(F("+ Monster found!") );
      break;
    }
    serialPrintln(F("- nope") );
    // next monster
    monster++;

#ifdef USE_EXTENDED_CHECKS
    // check if we are leaving the table
    if ( monster >= maxMonster )
    {
      // print error message
      serialPrint(F("*** No entry found for monster at position (")); serialPrint( position % dungeon->getLevelWidth() ); serialPrint(F(", ")); serialPrint( position / dungeon->getLevelWidth() ); serialPrintln(F(")"));
      // leave function early
      return( nullptr );
    }
#endif
  }

#ifdef USE_SERIAL_PRINT
  monster->serialPrint();
#endif

  return( monster );
}

/*--------------------------------------------------------*/
void playerAttack( DUNGEON *dungeon, MONSTER_STATS *monster )
{
#ifdef USE_EXTENDED_CHECKS
  if ( !monster ) 
  { 
    serialPrintln(F("*** No monster - no fight!"));
    return;
  }
#endif

  // attack the monster (use D7 + player's damage bonus)
  monster->hitpoints -= dungeon->dice + dungeon->playerDAM;
  // there should be a sound
  swordSound();
  // invert monster!
  dungeon->invertMonsterEffect = 0xFF;

#ifdef USE_SERIAL_PRINT
  monster->serialPrint();
#endif
}

/*--------------------------------------------------------*/
void monsterAttack( DUNGEON *dungeon, MONSTER_STATS *monster )
{
  // monster retaliates
  int8_t damage = dungeon->dice + monster->damageBonus;
  if ( damage > 0 )
  {
    dungeon->playerHP -= damage;
    // ouch!
    swordSound();
    // invert screen
    dungeon->invertStatusEffect = 0xFF;
  }
}

/*--------------------------------------------------------*/
void playerInteraction( DUNGEON *dungeon, uint8_t *cell, const uint8_t cellValue )
{
  INTERACTION_INFO interactionInfo;
  for ( uint8_t n = 0; n < sizeof( interactionData ) / sizeof( INTERACTION_INFO ); n++ )
  {
    // get data from progmem
    memcpy_P( &interactionInfo, interactionData + n, sizeof( INTERACTION_INFO ) );

    // does this info cover the current position?
    if (    ( cell == dungeon->currentLevel + interactionInfo.currentPosition )
        //|| ( interactionInfo.currentPosition == ANY_POSITION )
      )
    {
      // is the status correct?
      if ( ( cellValue & interactionInfo.currentStatusMask ) == interactionInfo.currentStatus )
      {
      #ifdef USE_SERIAL_PRINT
        Serial.print(F("+ Matching entry found <"));Serial.print( n );Serial.println(F(">"));
        // print entry information
        interactionInfo.serialPrint();
      #endif

      bool modifyCurrentPosition = true;
      bool modifyTargetPosition = true;

        // special handling for special types
        switch ( cellValue )
        {
        case CLOSED_CHEST:
          {
            // plunder the chest!
            openChest( dungeon, interactionInfo );
            break;
          }
        }

        if ( modifyCurrentPosition )
        {
          // change current position
          *cell = ( cellValue - interactionInfo.currentStatus ) | interactionInfo.nextStatus;
        }

        if ( modifyTargetPosition )
        {
          // modify target position
          dungeon->currentLevel[interactionInfo.modifiedPosition] = interactionInfo.modifiedPositionCellValue;
        }

        swordSound();
        
        // perform only the first action, otherwise on/off actions might be immediately revoked ;)
        break;
      }
    }
  }
}

/*--------------------------------------------------------*/
void Tiny_Flip( DUNGEON *dungeon )
{
  // update the status pane
  updateStatusPane( dungeon );

  uint8_t statusPaneOffset = 0; 

  for ( uint8_t y = 0; y < 8; y++ )
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
    for ( uint8_t x = 0; x < 32; x++ )
    {
      uint8_t pixels = 0;
      if ( y | dungeon->playerHasCompass )
      {
        pixels = pgm_read_byte( statusPane + statusPaneOffset ) | displayText( x, y );
      }
      // invert the 4th line (hitpoints)
      if ( y == 4 )
      {
        pixels ^= dungeon->invertStatusEffect;
      }
#if 0
      // is the player dead?
      if ( dungeon->playerHP <= 0 )
      {
        uint8_t *offsetXY = joey + y * 28 + x - 2;
        if ( ( x >= 2 ) && ( x < 30 ) )
        {
          // use mask
          pixels &= pgm_read_byte( offsetXY + 28 );
          // or pixels in
          pixels |= pgm_read_byte( offsetXY );
        }
      }
#endif
      // send 8 vertical pixels to the display
      TinyFlip_SendPixels( pixels );

      statusPaneOffset++;
    }
    
    // this row has been finished
    TinyFlip_FinishDisplayRow();
  } // for y

  // display the whole screen
  TinyFlip_DisplayBuffer();

  // disable fight effects
  dungeon->invertMonsterEffect = 0;
  dungeon->invertStatusEffect = 0;
}
