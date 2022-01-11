#include <Arduino.h>
#include <avr/pgmspace.h>

#include "bitTables.h"
#include "dungeon.h"
#include "dungeonTypes.h"
#include "soundFX.h"
#include "textUtils.h"
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
  memcpy_P( _dungeon.currentLevel, Level_1 /*+ sizeof( LEVEL_HEADER )*/, getLevelWidth() * getLevelHeight() );

  // populate dungeon with monsters
  memcpy_P( _dungeon.monsterStats, monsterStats, sizeof( monsterStats ) );
}


/*--------------------------------------------------------*/
 void Dungeon::gameLoop()
 {
  // prepare a new..
  init();

  while( isPlayerAlive() )
  {
    // update the status pane and render the screen
    Tiny_Flip();

    // update player's position and orientation
    checkPlayerMovement();
  }

  // player is dead... turn dungeon to black
  clear();

  // update the status pane and render the screen
  Tiny_Flip();

  // let the player fell the darkness...
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

  // stay in this loop until the player does anything (just increase the random counter)
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
          _dungeon.displayXorEffect = _dungeon.playerHasRing; /* visualize by flashing if player has the <Ring of Orientation>*/
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
          // player attacks monster
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


          /////////////////////////////////////////////
          // is the monster still alive?
          if ( monster->hitpoints > 0 )
          {
            // just wait a moment (for the display effect to be visible)
            _delay_ms( 250 );
            
            // now let the monster attack the player            
            monsterAttack( monster );

            // update the status pane and render the screen
            Tiny_Flip();

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
// updates the compass and the player stats
void Dungeon::updateStatusPane()
{
  clearTextBuffer();

  // display viewing direction
  uint8_t *textBuffer = getTextBuffer();

  // display compass
  textBuffer[POS_COMPASS] = pgm_read_byte( directionLetter + _dungeon.dir );

  // and the hitpoints
  convertValueToDigits( _dungeon.playerHP, textBuffer + POS_HITPOINTS );

  // and the damage
  convertValueToDigits( _dungeon.playerDAM, textBuffer + POS_DAMAGE );

  // and the number of keys
  convertValueToDigits( _dungeon.playerKeys, textBuffer + POS_KEYS );
}

/*--------------------------------------------------------*/
// opens a chest
void Dungeon::openChest( INTERACTION_INFO &info )
{
  serialPrintln( F("openChest()") );

  switch( info.newItem )
  {
    case ITEM_COMPASS:
      {
        // a compass will be displayed
        _dungeon.playerHasCompass = true;
        // hooray!
        serialPrintln( F("+ <Compass> found!") );
        break;
      }
    case ITEM_AMULET:
      {    
        // fake will be removed
        _dungeon.playerHasAmulet = true;
        // remove all fake walls
        uint8_t *currentCell = _dungeon.currentLevel;
        while ( currentCell < _dungeon.currentLevel + getLevelWidth() * getLevelHeight() )
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
        _dungeon.playerHasRing = 0xff;
        // hooray!
        serialPrintln( F("+ <Ring of Orientation> found!") );
        break;
      }
  }
}

/*--------------------------------------------------------*/
void Dungeon::updateDice()
{ 
  _dungeon.dice++; 
  _dungeon.dice &= DICE_MASK;
  //serialPrint( F("D8 = ")); serialPrintln( _dungeon.dice + 1 );
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
    serialPrintln(F("- nope") );
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
#ifdef USE_EXTENDED_CHECKS
  if ( !monster ) 
  { 
    serialPrintln(F("*** No monster - no fight!"));
    return;
  }
#endif

  // attack the monster (use D7 + player's damage bonus)
  monster->hitpoints -= _dungeon.dice + _dungeon.playerDAM;
  // there should be a sound
  swordSound();
  // invert monster!
  _dungeon.invertMonsterEffect = 0xFF;

#ifdef USE_SERIAL_PRINT
  monster->serialPrint();
#endif
}

/*--------------------------------------------------------*/
void Dungeon::monsterAttack( MONSTER_STATS *monster )
{
  // monster retaliates
  int8_t damage = _dungeon.dice + monster->damageBonus;
  if ( damage > 0 )
  {
    _dungeon.playerHP -= damage;
    // ouch!
    swordSound();
    // invert screen
    _dungeon.invertStatusEffect = 0xFF;
  }
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
    if (    ( cell == _dungeon.currentLevel + interactionInfo.currentPosition )
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
  // update the status pane
  updateStatusPane();

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
      if ( y | _dungeon.playerHasCompass )
      {
        pixels = pgm_read_byte( statusPane + statusPaneOffset ) | displayText( x, y );
      }
      // invert the 4th line (hitpoints)
      if ( y == 4 )
      {
        pixels ^= _dungeon.invertStatusEffect;
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

/*--------------------------------------------------------*/
uint8_t Dungeon::getWallPixels( const int8_t x, const int8_t y )
{
  uint8_t pixels = 0;

  SIMPLE_WALL_INFO wallInfo;
  
  const SIMPLE_WALL_INFO *wallInfoPtr = arrayOfWallInfo;

  // all objects are visible
  int8_t maxObjectDistance = 3;

  // iterate through the whole list (at least as long as it's necessary)
  while( true )
  {
    // the structure resides in PROGMEM, so we need to copy it to RAM first...
    memcpy_P( &wallInfo, wallInfoPtr, sizeof( wallInfo ) );

    // end of list reached?
    if ( wallInfo.wallBitmap == nullptr ) { break; }

    // check conditions
    if ( ( x >= wallInfo.startPosX ) && ( x <= wallInfo.endPosX ) )
    {
      // is there a wall object?
      if ( ( *( getCell( _dungeon.playerX, _dungeon.playerY, wallInfo.viewDistance, wallInfo.leftRightOffset, _dungeon.dir ) ) & WALL_MASK ) == wallInfo.objectMask )
      {
        // is there wall information for this vertical position
        if ( ( y >= wallInfo.startPosY ) && ( y <= wallInfo.endPosY ) )
        {
          // mirror walls on odd fields
          uint8_t offsetX = ( ( _dungeon.playerX + _dungeon.playerY ) & 0x01 ) ? ( WINDOW_SIZE_X - 1 ) - x : x;
          // get wall pixels (shave off the empty rows)
          pixels = pgm_read_byte( wallInfo.wallBitmap + ( y - wallInfo.startPosY ) * WINDOW_SIZE_X + offsetX );
        }
        else
        {
          // nope, just nothing
          pixels = 0;
        }
        // objects behind walls are not visible, but doors or switches might be placed *on* walls
        maxObjectDistance = wallInfo.viewDistance;
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }

  NON_WALL_OBJECT object;

  // draw NWOs (Non Wall Objects) over the background pixels (with mask!)
  for ( uint8_t distance = maxObjectDistance; distance > 0; distance-- )
  {
    for ( uint8_t n = 0; n < sizeof( objectList ) / sizeof( objectList[0] ); n++ )
    {
      memcpy_P( &object, &objectList[n], sizeof( object ) );
      uint8_t objectWidth = object.bitmapWidth >> distance;

      // non wall objects will only be rendered if directly in front of the player (for now!)
      if ( ( x >= WINDOW_CENTER_X - objectWidth ) && ( x < WINDOW_CENTER_X + objectWidth ) )
      {
        if ( ( *( getCell( _dungeon.playerX, _dungeon.playerY, distance, 0, _dungeon.dir ) ) & OBJECT_MASK ) == object.itemType )
        {
          objectWidth = WINDOW_CENTER_X - objectWidth;
          uint8_t posX = x - objectWidth;
          // free background
          uint8_t mask = getDownScaledBitmapData( posX, y, distance, &object, true );
          pixels &= mask;
          // and overlay scaled bitmap
          uint8_t scaledBitmap = getDownScaledBitmapData( posX, y, distance, &object, false );
          if ( distance == 1 )
          {
            // invert monster?!
            scaledBitmap ^= ( _dungeon.invertMonsterEffect & ~mask );
          }
          pixels |= scaledBitmap;
        }
      }
    }
  }
  
  return( pixels );
}

/*--------------------------------------------------------*/
// Returns the downscaled bitmap data at position x,y.
// Supported distance values are 1, 2, 3.
// Note that x is scaled by the scale factor for
// the current distance, while y remains unscaled!
uint8_t Dungeon::getDownScaledBitmapData( int8_t x,                      // already downscaled by 1 << ( distance - 1 )
                                          int8_t y,                      // unscaled vertical position
                                          const uint8_t distance,        // supported values are 1..3
                                          const NON_WALL_OBJECT *object, // current non wall object
                                          bool useMask                   // if true returns the down scaled mask instead of the bitmap
                                        )
{
  uint8_t pixels = 0;

  // get start address (and add optional offset for mask)
  const uint8_t *bitmapData = object->bitmapData;
  if ( useMask ) { bitmapData += object->bitmapWidth; }

  // Get scaling factor from LUT (efficient and still flexible).
  uint8_t scaleFactor = pgm_read_byte( scalingFactorFromDistance + distance );
  // get threshold (distance is 1..3, so subtract 1 (at no cost!))
  const uint8_t threshold = object->scalingThreshold[distance - 1];

  // is there anything to be done?
  uint8_t startOffsetY = pgm_read_byte( verticalStartOffset + distance );
  uint8_t endOffsetY = pgm_read_byte( verticalEndOffset + distance );

  if ( ( y >= startOffsetY ) && ( y <= endOffsetY ) )
  {
    // modify positions in source bitmap by scaling factor
    x = x * scaleFactor;
    // correct y position by start offset
    y -= startOffsetY;
    
  #if 0
    if ( ( x == 0 ) && !useMask )
    {
      Serial.print(F("x = "));Serial.print( x );Serial.print(F(", y = "));Serial.print( y );
      Serial.print(F(", distance = "));Serial.print( distance );
      //Serial.print(F(", scaleFactor = "));Serial.print( scaleFactor ); Serial.print(F(", threshold = "));Serial.print( threshold );
      //Serial.print(F(", startOffsetY = "));Serial.print( startOffsetY ); Serial.print(F(", endOffsetY = "));Serial.print( endOffsetY );
      Serial.print(F(", bitmapVerticalOffsetInBits = "));Serial.print( object->bitmapVerticalOffsetInBits );
      Serial.println();
    }
  #endif

    // get associated bit mask
    uint8_t bitMask = pgm_read_byte( bitMaskFromScalingFactor + scaleFactor );

    // calculate the first and last bit to be processed
    uint8_t startBitNo = object->bitmapVerticalOffsetInBits;
    uint8_t endBitNo = startBitNo + object->bitmapHeightInBits;
    
    // but we are starting with bit 0 (and its friends)
    uint8_t bitNo = y * 8 * scaleFactor;
  
    // We need to calculate 8 vertical output bits...
    // NOTE: Because the Tiny85 only supports shifting by 1 bit, it is
    //       more efficient to do the shifting in the 'for' loop instead
    //       of using a ( 1 << n ) construct.
    for ( uint8_t bitValue = 1; bitValue != 0; bitValue <<= 1 )
    {
      uint8_t bitSum = 0;
  
      if ( ( bitNo >= startBitNo ) && ( bitNo <  endBitNo ) )
      {
        // calculate start address
        uint8_t row = ( bitNo - startBitNo ) / 8;
        const uint8_t *data = bitmapData + row * object->nextLineOffset + x;
    #if 0
      if ( ( x == 0 ) && !useMask )
      {
        Serial.print(F("y = "));Serial.print( y ); Serial.print(F(", bitNo = "));Serial.print( bitNo );
        Serial.print(F(", startBitNo = "));Serial.print( startBitNo ); Serial.print(F(", endBitNo = "));Serial.print( endBitNo );
        Serial.print(F(", row = "));Serial.print( row );
        Serial.println();
      }
    #endif
        
        // go over the columns - all required bits always are in one row
        for ( uint8_t col = 0; col < scaleFactor; col++ )
        {
          // to get the output value, we will sum all the bits up (using a lookup table saves time and flash space)
          bitSum += pgm_read_byte( nibbleBitCount + ( ( pgm_read_byte( data++ ) >> ( bitNo & 0x07 ) ) & bitMask ) );
        }
      }
      else if ( useMask )
      {
        // make bitsum count - otherwise we will erase the backgound
        bitSum += scaleFactor * scaleFactor;
      }
  
      // next bit position
      bitNo += scaleFactor;

      // calculate output pixel
      if ( bitSum >= threshold )
      {
        pixels |= bitValue;
      }
    } // for
  }
  // no bits here, set mask to 0xff
  else if ( useMask )
  { 
    pixels--;
  }
                                     
  return( pixels );  
}
