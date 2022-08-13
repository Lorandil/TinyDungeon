#include <Arduino.h>
#include <avr/pgmspace.h>

#include "bitTables.h"
#include "dungeon.h"
#include "dungeonTypes.h"
#include "externBitmaps.h"
#include "soundFX.h"
#include "tinyJoypadUtils.h"

/*--------------------------------------------------------*/
void Dungeon::clear()
{
  // zero dungeon structure
  memset( &_dungeon, 0x00, sizeof( _dungeon ) );
}

/*--------------------------------------------------------*/
// initialize all variables
void Dungeon::init()
{
  // zero dungeon structure
  clear();

  // Prepare the dungeon
  _dungeon.playerX = 5; // could save 4 bytes here, if the whole level is shifted, so that the starting point is at (0,0)
  _dungeon.playerY = 3;
  //_dungeon.dir  = NORTH; // NORTH = 0!
  // prepare player stats
  _dungeon.playerHP = 10;
  _dungeon.playerDamage = 3;
  //_dungeon.displayXorEffect = 0;

  // copy the level data to RAM
  memcpy_P( _dungeon.currentLevel, Level_1, getLevelWidth() * getLevelHeight() );

  // populate dungeon with monsters
  memcpy_P( _dungeon.monsterStats, monsterStats, sizeof( monsterStats ) );

  serialPrint("sizeof( MONSTER_STATS ) = ");
  serialPrintln( sizeof( MONSTER_STATS ) );
  serialPrint("sizeof( _dungeon.monsterStats ) = ");
  serialPrintln( sizeof( _dungeon.monsterStats ) );
  serialPrint("sizeof( monsterStats ) = ");
  serialPrintln( sizeof( monsterStats ) );

  MONSTER_STATS *pMonsterStats = _dungeon.monsterStats;

  for ( uint8_t n = 0; n < MAX_MONSTERS; n++ )
  {
    _dungeon.currentLevel[pMonsterStats->position] = pMonsterStats->monsterType;
  #if !defined( __AVR_ATtiny85__ )
    serialPrint("+ placing monster ");  printHexToSerial( pMonsterStats->monsterType, false );
    serialPrint(" at position ");  serialPrintln( pMonsterStats->position ); 
  #endif
    pMonsterStats++;
  }  
  //while( pMonsterStats->monsterType != 0 );
  #if !defined( __AVR_ATtiny85__ )
    _dungeon.serialPrint();
  #endif

  // initialize timer/counter
  initDice();
}

/*--------------------------------------------------------*/
// This is very hardware dependend, so we restrict the timer 
// programming to ATTiny85
void Dungeon::initDice()
{
#if defined( __AVR_ATtiny85__ )
  // initialize timer 0 to run at full cpu clock (no prescaler)
  TCCR0A = 0x00;        // normal mode
  TCCR0B = ( 1<<CS00 ); // prescaling with 1
#endif
}

/*--------------------------------------------------------*/
 void Dungeon::gameLoop()
 {
  // prepare a new dungeon...
  init();

// it ain't over, till it's over...  
  while( isPlayerAlive() )
  {
  // sword found? -> adjust damage
  if ( _dungeon.playerItems & ITEM_SWORD ) { _dungeon.playerDamage = 10; }

  // shield found? adjust protection
  if ( _dungeon.playerItems & ITEM_SHIELD ) { _dungeon.playerArmour = 3; }

    // update the status pane and render the screen
    Tiny_Flip();

    // update player's position and orientation
    checkPlayerMovement();
  }

  // player is dead... turn dungeon to black
  clear();

  // update the status pane and render the screen
  Tiny_Flip();

  // let the player feel the darkness...
  while ( !isFirePressed() );
 }


/*--------------------------------------------------------*/
void Dungeon::checkPlayerMovement()
{
  // get pointer to cell in front of player
  uint8_t *cell = getCell( _dungeon.playerX, _dungeon.playerY, +1, 0, _dungeon.dir );

  // no movement yet
  bool playerHasReachedNewCell = false;
  bool playerAction = false;

  // remember to disable the flashing effect
  bool disableFlashEffect = _dungeon.displayXorEffect | _dungeon.invertMonsterEffect | _dungeon.invertStatusEffect;;
  _dungeon.displayXorEffect = 0;
  /*
  _dungeon.invertMonsterEffect = 0;
  _dungeon.invertStatusEffect = 0;
  */

  // stay in this loop until the player does anything
  while ( !playerAction && !disableFlashEffect )
  {
    playerAction = _dungeon.displayXorEffect;

    // prepare the dice
    updateDice();

    if ( isLeftPressed() ) 
    {
      // turn left
      _dungeon.dir = ( _dungeon.dir - 1 ) & 0x03;
      stepSound();
      playerAction = true;
    }
    
    if ( isRightPressed() )
    {
      // turn right
      _dungeon.dir = ( _dungeon.dir + 1 ) & 0x03;
      stepSound();
      playerAction = true;
    }

    if ( isUpPressed() )
    {
      if ( ( ( *cell ) & FLAG_SOLID ) != FLAG_SOLID )
      {
        stepSound();
        stepSound();
        
        switch( _dungeon.dir )
        {
          case NORTH:
            _dungeon.playerY--; break;
          case EAST:
            _dungeon.playerX++; break;
          case SOUTH:
            _dungeon.playerY++; break;
          //case WEST:
          default:  // this saves 4 bytes
            _dungeon.playerX--; break;
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
      if ( ( *( getCell( _dungeon.playerX, _dungeon.playerY, -1, 0, _dungeon.dir ) ) & FLAG_SOLID ) != FLAG_SOLID )
      {
        stepSound();
        stepSound();
    
        switch( _dungeon.dir )
        {
          case NORTH:
            _dungeon.playerY++; break;
          case EAST:
            _dungeon.playerX--; break;
          case SOUTH:
            _dungeon.playerY--; break;
          //case WEST:
          default:
            _dungeon.playerX++; break;
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
    limitDungeonPosition( _dungeon.playerX, _dungeon.playerY );

    // check for special cell effects like teleporter or spinner
    if ( playerHasReachedNewCell )
    {
      // obviously that's a player action, too
      playerAction = true;
      // log player coordinates
      serialPrint( F("player position = (") ); serialPrint( _dungeon.playerX ); serialPrint( F(", ") ); serialPrint( _dungeon.playerY ); serialPrintln( F(")") );

      SPECIAL_CELL_INFO specialCellInfo;
      
      for ( int n = 0; n < int( sizeof( specialCellFX ) / sizeof( specialCellFX[0] ) ); n++ )
      {
        // copy cell info object from flash to RAM
        memcpy_P( &specialCellInfo, &specialCellFX[n], sizeof( specialCellInfo ) );

        // does this entry refer to the current position?
        if ( specialCellInfo.position == _dungeon.playerX + _dungeon.playerY * getLevelWidth() )
        {
        #if !defined(__AVR_ATtiny85__)
          // print the special effect...
          specialCellInfo.serialPrint();
        #endif

          // teleporter?
          if ( specialCellInfo.specialFX == TELEPORTER )
          {
            _dungeon.playerX = specialCellInfo.value_1;
            _dungeon.playerY = specialCellInfo.value_2;
          }
          else // it's a spinner
          {
            // modify player's orientation
            _dungeon.dir += specialCellInfo.value_1;
            _dungeon.dir &= 0x03;
          }
          // *** BAZINGA! ***
          if ( _dungeon.playerItems & ITEM_RING )
          {
            _dungeon.displayXorEffect = 0xff; /* visualize by flashing if player has the <Ring of Orientation>*/
          }
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
          _dungeon.serialPrint();
          Serial.print(F("*cell = "));printHexToSerial( cellValue );Serial.println();
        #endif

        if ( cellValue & FLAG_MONSTER )
        {
          /////////////////////////////////////////////
          // find the monster...
          MONSTER_STATS *monster = findMonster( cell - _dungeon.currentLevel );


          /////////////////////////////////////////////
          // does the monster attack first?
          if ( monster->attacksFirst )
          {
            // now let the monster attack the player
            monsterAttack( monster );
          }          

          /////////////////////////////////////////////
          // player attacks monster (if he/she is still alive)
          if ( _dungeon.playerHP > 0 )
          {
            playerAttack( monster );

            // wait for fire button to be released (random number generation!)
            while ( isFirePressed() )
            {
              updateDice();
            }

            // update the status pane and render the screen (monster will be inverted)
            Tiny_Flip();
            // redraw with normal monster (so that the monster appears to have flashed)
            Tiny_Flip();
          }

          /////////////////////////////////////////////
          // is the monster still alive?
          if ( monster->hitpoints > 0 )
          {
            if ( !monster->attacksFirst )
            {
              // just wait a moment (for the display effect to be visible)
              _variableDelay_us( 250 );
              
              // now let the monster attack the player
              monsterAttack( monster );
            }
          }
          else
          {
            // the monster has been defeated!
            serialPrintln(F("Monster defeated!"));
            // remove the monster from the dungeon
            *cell = EMPTY;
            // collect the treasure!
            _dungeon.playerItems |= monster->treasureItemMask;
          }

        #ifdef USE_SERIAL_PRINT
          _dungeon.serialPrint();
          Serial.print(F("*cell = ")); printHexToSerial( cellValue ); Serial.println();
        #endif
        }
        else
        {
          // let's see if there is some scripted interaction...
          playerInteraction( cell, cellValue );
        }
      }
    }
  }
}


/*--------------------------------------------------------*/
// Returns a pointer to the cell which is 
// - 'distance' away 
// - in direction 'orientation'
// - from position 'x', 'y'
// This function supports a wrap-around, so endless corridors are possible :)
uint8_t *Dungeon::getCell( int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation )
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

  limitDungeonPosition( x, y );

  return( _dungeon.currentLevel + y * getLevelWidth() + x );
}


/*--------------------------------------------------------*/
// Limits the position in the dungeon, but enables wrap-around :)
void Dungeon::limitDungeonPosition( int8_t &x, int8_t &y )
{
  if ( x < 0 ) { x += getLevelWidth(); }
  if ( x >= getLevelWidth() ) { x -= getLevelWidth(); }
  if ( y < 0 ) { y += getLevelHeight(); }
  if ( y >= getLevelHeight() ) { y -= getLevelHeight(); }
}


/*--------------------------------------------------------*/
// opens a chest
void Dungeon::openChest( INTERACTION_INFO &info )
{
  serialPrintln( F("openChest()") );

  // update player items
  _dungeon.playerItems |= info.newItem;

  // remove fake walls?
  if ( info.newItem == ITEM_AMULET )
  {
    // remove all fake walls
    uint8_t *currentCell = _dungeon.currentLevel;
    while ( currentCell < _dungeon.currentLevel + getLevelWidth() * getLevelHeight() )
    {
      // fake? let's stay with the facts...
      if ( *currentCell == FAKE_WALL ) { *currentCell = EMPTY; }
      currentCell++;
    }
  }
  
#if !defined(__AVR_ATtiny85__)
  switch( info.newItem )
  {
    case ITEM_COMPASS:
      {
        // hooray!
        serialPrintln( F("+ <Compass> found!") );
        break;
      }
    case ITEM_AMULET:
      {    
        // hooray!
        serialPrintln( F("+ <Amulet of True Sight> found!") );
        break;
      }
    case ITEM_RING:
      {    
        // hooray!
        serialPrintln( F("+ <Ring of Orientation> found!") );
        break;
      }
    case ITEM_KEY:
    {    
      // hooray!
      serialPrintln( F("+ <Key> found!") );
      break;
    }
    case ITEM_SWORD:
    {    
      // hooray!
      serialPrintln( F("+ <Rusty Sword found> found!") );
      break;
    }
    case ITEM_SHIELD:
    {    
      // hooray!
      serialPrintln( F("+ <Wooden Shield> found!") );
      break;
    }
    case ITEM_VICTORY:
    {    
      // hooray!
      serialPrintln( F("+ <Victory condition> found!") );
      break;
    }
}
#endif
}


/*--------------------------------------------------------*/
void Dungeon::updateDice()
{ 
#if !defined( __AVR_ATtiny85__ )
  _dungeon.dice++; 
#endif
}


/*--------------------------------------------------------*/
uint8_t Dungeon::getDice( uint8_t maxValue )
{
#if !defined( __AVR_ATtiny85__ )
  uint8_t value =_dungeon.dice; 
#else
  uint8_t value = TCNT0;
#endif
  // limit value
  while ( value > maxValue )
  {
    value -= maxValue;    
  }  
  return( value );
}


/*--------------------------------------------------------*/
// Every single monster is mapped to an entry in the monsterStats table.
// The table size is only (sic!) restricted by the RAM size (change to EEPROM???).
// If no monster is found, everything goes directly to hell :)
MONSTER_STATS *Dungeon::findMonster( const uint8_t position )
{
  serialPrint(F("findMonster( position = (")); serialPrint( position % getLevelWidth()); serialPrint(F(", ")); serialPrint( position / getLevelWidth());serialPrintln(F(") )"));

  // no monster found
  MONSTER_STATS *monster = _dungeon.monsterStats;

#ifdef USE_EXTENDED_CHECKS
  MONSTER_STATS *maxMonster = monster + sizeof( _dungeon.monsterStats ) / sizeof( _dungeon.monsterStats[0] );
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
    // next monster
    monster++;

#ifdef USE_EXTENDED_CHECKS
    // check if we are leaving the table
    if ( monster >= maxMonster )
    {
      // print error message
      serialPrint(F("*** No entry found for monster at position (")); serialPrint( position % getLevelWidth() ); serialPrint(F(", ")); serialPrint( position / getLevelWidth() ); serialPrintln(F(")"));
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
void Dungeon::playerAttack( MONSTER_STATS *monster )
{
  // just some logging
  serialPrintln(F("-> playerAttack"));

#ifdef USE_EXTENDED_CHECKS
  if ( !monster ) 
  { 
    serialPrintln(F("*** No monster - no fight!"));
    return;
  }
#endif

  // attack the monster (use D7 + player's damage bonus)
  monster->hitpoints -= getDice( 0x07 ) + _dungeon.playerDamage;
  // there should be a sound
  swordSound();
  // invert monster!
  _dungeon.invertMonsterEffect = 0xFF;

#ifdef USE_SERIAL_PRINT
  monster->serialPrint();
#endif

  // just some logging
  serialPrintln(F("<- playerAttack"));
}

/*--------------------------------------------------------*/
void Dungeon::monsterAttack( MONSTER_STATS *monster )
{
  // just some logging
  serialPrintln(F("-> monsterAttack()"));

  // monster retaliates
  int8_t damage = getDice( 0x07 ) + monster->damageBonus - _dungeon.playerArmour;
  if ( damage > 0 )
  {
    _dungeon.playerHP -= damage;
    // ouch!
    swordSound();
    // invert screen
    _dungeon.invertStatusEffect = 0xFF;
  }

#ifdef USE_SERIAL_PRINT
  Serial.print(F("  Player's hitpoints : ")); Serial.println( _dungeon.playerHP );
#endif

    // update the status pane and render the screen
    Tiny_Flip();

  // just some logging
  serialPrintln(F("<- monsterAttack()"));
}

/*--------------------------------------------------------*/
void Dungeon::playerInteraction( uint8_t *cell, const uint8_t cellValue )
{
  INTERACTION_INFO interactionInfo;
  for ( uint8_t n = 0; n < sizeof( interactionData ) / sizeof( INTERACTION_INFO ); n++ )
  {
    // get data from progmem
    memcpy_P( &interactionInfo, interactionData + n, sizeof( INTERACTION_INFO ) );

    // does this info cover the current position?
    if ( cell == _dungeon.currentLevel + interactionInfo.currentPosition )
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
            openChest( interactionInfo );
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
          _dungeon.currentLevel[interactionInfo.modifiedPosition] = interactionInfo.modifiedPositionCellValue;
        }

        swordSound();
        
        // perform only the first action, otherwise on/off actions might be immediately revoked ;)
        break;
      }
    }
  }
}

/*--------------------------------------------------------*/
void Dungeon::Tiny_Flip()
{
  uint8_t statusPaneOffset = 0; 

  for ( uint8_t y = 0; y < 8; y++ )
  {
    // prepare display of row <y>
    TinyFlip_PrepareDisplayRow( y );
    
    uint8_t pixels;

    // the first 96 columns are used to display the dungeon
    for ( uint8_t x = 0; x < 96; x++ )
    {
      pixels = getWallPixels( x, y );
      pixels ^= _dungeon.displayXorEffect;
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
      pixels = 0;
      if ( y | ( _dungeon.playerItems & ITEM_COMPASS ) )
      {
        pixels = pgm_read_byte( statusPane + statusPaneOffset );
        // compass present?
        if ( !y )
        {
          if ( ( x >= 15 ) && ( x < 20 ) )
          { 
            pixels |= pgm_read_byte( compass + x - 15 + 5 * _dungeon.dir );
          }
        }
      }

      // special status rows
      if ( ( x >= 1 ) && ( x <= 30 ) )
      {
        // hitpoints
        if ( y == 4 )
        {
          // display HP as am unscaled bar, so max HP is 28 ;)
            if ( x > _dungeon.playerHP + 2 ) { pixels = 0; }
            // invert the row if the player was hurt
            pixels ^= _dungeon.invertStatusEffect;
        }
        // items: display the appropriate icons
        if ( y == 5 )
        {
          if ( x >= 3 )
          {
            if ( x <= 8 )
            {
              if ( !( _dungeon.playerItems & ITEM_SWORD ) ) { pixels = 0; }
            }
            else if ( x <= 14 )
            {
              if ( !( _dungeon.playerItems & ITEM_SHIELD ) ) { pixels = 0; }
            }
            else if ( x <= 20 )
            {
              if ( !( _dungeon.playerItems & ITEM_AMULET ) ) { pixels = 0; }
            }
            else if ( x <= 26 )
            {
              if ( !( _dungeon.playerItems & ITEM_RING ) ) { pixels = 0; }
            }
            else if ( x <= 31 )
            {
              if ( !( _dungeon.playerItems & ITEM_KEY ) ) { pixels = 0; }
            }
          }
        }
        // did the player win?
        if ( y == 6 )
        {
          if ( !(_dungeon.playerItems & ITEM_VICTORY ) ) { pixels = 0; }
        }
      }

      // is the player dead?
      if ( !isPlayerAlive() )
      {
        if ( y >= 3 )
        {
          constexpr uint8_t joeyBitmapWidth = 28;
          constexpr uint8_t joeyMaskWidth = 28;
          // the y position needs correction, because we are already in row 3
          const uint8_t *offsetXY = joey - 3 * ( joeyBitmapWidth + joeyMaskWidth ) + y * ( joeyBitmapWidth + joeyMaskWidth ) + joeyBitmapWidth + 2  - x;
          if ( ( x >= 2 ) && ( x < 30 ) )
          {
            // use mask
            pixels &= pgm_read_byte( offsetXY + joeyMaskWidth );
            // or pixels in
            pixels |= pgm_read_byte( offsetXY );
          }
        }
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

  // disable fight effects
  _dungeon.invertMonsterEffect = 0;
  _dungeon.invertStatusEffect = 0;

  return;  
}
