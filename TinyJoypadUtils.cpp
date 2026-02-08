//
// This file works for TinyJoypad compatible devices.
//
// If not compiled for ATTiny85 (meaning __AVR_ATtiny85__ is not defined),
// generic functions are used instead of direct port access, which 
// makes it possible to use an Arduino or Mega2560 (or many others)
// for debugging with serial output or even hardware breakpoints.
//

#include <Arduino.h>
#include "TinyJoypadUtils.h"

#if defined(__AVR_ATtiny85__)
  #if defined( _USE_FAST_TINY_DRIVER_ )
    #include "FastTinyDriver.h"
  #else
    #include <ssd1306xled.h>
  #endif
#else
  // Arduboy2?
  #ifdef _USE_ARDUBOY2_
    Arduboy2 arduboy;
    BeepPin1 beep;
  #else
    // include Adafruit library and immediately create an object
    #include <Adafruit_SSD1306.h>
    Adafruit_SSD1306 display( 128, 64, &Wire, -1 );
  #endif

  // frame buffer handling and addressing
  uint8_t *_frameBuffer;
  uint8_t _column{0};
  uint8_t _row{0};
  // flag if vertical addressing mode is enabled
  bool _verticalAddressingModeEnabled{false};

  // these functions are only required if a screenshot should be printed as a hexdump to the serial port
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    // include serial output functions
    #include "SerialHexTools.h"
  #endif
#endif

// buffered analog joystick inputs
uint16_t _analogJoystickX;
uint16_t _analogJoystickY;


/*-------------------------------------------------------*/
// function for initializing the TinyJoypad (ATtiny85) and other microcontrollers
void InitTinyJoypad()
{
#if defined(__AVR_ATtiny85__)
  // not using 'pinMode()' here saves ~100 bytes of flash!
  // configure A0, A3 and D1 as input
  SOUND_PORT_DDR &= ~( ( 1 << PB5) | ( 1 << PB3 ) | ( 1 << PB1 ) );
  // configure A2 (aka SOUND_PIN) as output
  SOUND_PORT_DDR |= ( 1 << SOUND_PIN );
#elif !defined( USE_KEYBOARD_INPUT )
  #ifdef _USE_ARDUBOY2_
    // initialize Arduboy2
    arduboy.begin();
    beep.begin();
    // prepare serial port for debugging output
    Serial.begin( 115200 );
  #else
    // use 'pinMode()' for simplicity's sake... any other micro controller has enough flash :)
    pinMode( LEFT_RIGHT_BUTTON, INPUT );
    pinMode( UP_DOWN_BUTTON, INPUT );
    pinMode( FIRE_BUTTON, INPUT );
    // configure SOUND_PIN as output (Pin D12 on Arduino UNO R3 and Pin D10 on Arduino Mega 2560 )
    pinMode( SOUND_PIN, OUTPUT );
    // prepare serial port for debugging output
    Serial.begin( 115200 );
  #endif
#endif
}

#ifdef USE_KEYBOARD_INPUT
bool leftKeyPressed{ false };
bool rightKeyPressed{ false };
bool upKeyPressed{ false };
bool downKeyPressed{ false };
bool actionKeyPressed{ false };

/*-------------------------------------------------------*/
void handleKeys()
{
  if (_kbhit())
  {
    auto key = _getch();
    switch( key )
    {
      case 'a':
      case 'A':
        leftKeyPressed = true;
        break;
      case 'd':
      case 'D':
        rightKeyPressed = true;
        break;
      case 'w':
      case 'W':
        upKeyPressed = true;
        break;
      case 's':
      case 'S':
        downKeyPressed = true;
        break;
      case ' ':
        actionKeyPressed = true;
        break;
      default:
        break;
      // cursor keys
      case 224:
        key = _getch();
        switch (key)
        {
        case 75:
          leftKeyPressed = true;
          break;
        case 77:
          rightKeyPressed = true;
          break;
        case 72:
          upKeyPressed = true;
          break;
        case 80:
          downKeyPressed = true;
          break;
        default:
          break;
        }
    }
  }
}
#endif

/*-------------------------------------------------------*/
bool isLeftPressed()
{
#ifdef USE_KEYBOARD_INPUT
  handleKeys();
  auto key = leftKeyPressed;
  leftKeyPressed = false;
  return( key );
#else
  #ifdef _USE_ARDUBOY2_
    return( arduboy.pressed( LEFT_BUTTON ) );
  #else
    uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
    return( ( inputX >= ANALOG_UPPER_LIMIT_MIN ) && ( inputX < ANALOG_UPPER_LIMIT_MAX ) );
  #endif
#endif
}

/*-------------------------------------------------------*/
bool isRightPressed()
{
#ifdef USE_KEYBOARD_INPUT
  handleKeys();
  auto key = rightKeyPressed;
  rightKeyPressed = false;
  return( key );
#else
  #ifdef _USE_ARDUBOY2_
    return( arduboy.pressed( RIGHT_BUTTON ) );
  #else
    uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
    return( ( inputX > ANALOG_LOWER_LIMIT_MIN ) && ( inputX < ANALOG_LOWER_LIMIT_MAX ) );
  #endif
#endif
}

/*-------------------------------------------------------*/
bool isUpPressed()
{
#ifdef USE_KEYBOARD_INPUT
  handleKeys();
  auto key = upKeyPressed;
  upKeyPressed = false;
  return(key);
#else
  #ifdef _USE_ARDUBOY2_
    return( arduboy.pressed( UP_BUTTON ) );
  #else
    uint16_t inputY = analogRead( UP_DOWN_BUTTON );
    return( ( inputY > ANALOG_LOWER_LIMIT_MIN ) && ( inputY < ANALOG_LOWER_LIMIT_MAX ) );
  #endif
#endif
}

/*-------------------------------------------------------*/
bool isDownPressed()
{
#ifdef USE_KEYBOARD_INPUT
  handleKeys();
  auto key = downKeyPressed;
  downKeyPressed = false;
  return(key);
#else
  #ifdef _USE_ARDUBOY2_
    return( arduboy.pressed( DOWN_BUTTON ) );
  #else
    uint16_t inputY = analogRead( UP_DOWN_BUTTON );
    return( ( inputY >= ANALOG_UPPER_LIMIT_MIN ) && ( inputY < ANALOG_UPPER_LIMIT_MAX ) );
  #endif
#endif
}

/*-------------------------------------------------------*/
bool isFirePressed()
{
#ifdef USE_KEYBOARD_INPUT
  handleKeys();
  auto key = actionKeyPressed;
  actionKeyPressed = false;
  return( key );
#else
  #ifdef _USE_ARDUBOY2_
    return( arduboy.pressed( A_BUTTON ) );
  #else
    return( digitalRead( FIRE_BUTTON ) == 0 );
  #endif
#endif
}

/*-------------------------------------------------------*/
// wait until all buttons are released
void waitUntilButtonsReleased()
{
  while( isLeftPressed() || isRightPressed() || isUpPressed() || isDownPressed() || isFirePressed() );
}

/*-------------------------------------------------------*/
// wait until all buttons are released and wait a little delay
void waitUntilButtonsReleased( const uint8_t delayTime )
{
  waitUntilButtonsReleased();
  _delay_ms( delayTime );
}

/*-------------------------------------------------------*/
// read analog joystick inputs into internal variables
void readAnalogJoystick()
{
  _analogJoystickX = analogRead( LEFT_RIGHT_BUTTON );
  _analogJoystickY = analogRead( UP_DOWN_BUTTON );
}

/*-------------------------------------------------------*/
bool wasLeftPressed()
{
  return( ( _analogJoystickX >= ANALOG_UPPER_LIMIT_MIN ) && ( _analogJoystickX < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasRightPressed()
{
  return( ( _analogJoystickX > ANALOG_LOWER_LIMIT_MIN ) && ( _analogJoystickX < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasUpPressed()
{
  return( ( _analogJoystickY > ANALOG_LOWER_LIMIT_MIN ) && ( _analogJoystickY < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasDownPressed()
{
  return( ( _analogJoystickY >= ANALOG_UPPER_LIMIT_MIN ) && ( _analogJoystickY < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
uint16_t getAnalogValueX()
{
  return( _analogJoystickX );
}

/*-------------------------------------------------------*/
uint16_t getAnalogValueY()
{
  return( _analogJoystickY );
}

/*-------------------------------------------------------*/
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
void __attribute__ ((noinline)) _variableDelay_us( uint8_t delayValue )
#else
void _variableDelay_us(uint8_t delayValue)
#endif
{
  while ( delayValue-- != 0 )
  {
    _delay_us( 1 );
  }
}

/*-------------------------------------------------------*/
#if defined( NO_SOUND )
  void Sound(const uint8_t, const uint8_t) {}
#else
  // This code was originaly borrowed from Daniel C's Tiny-invaders :)
  // Code optimization by sbr
  void Sound( const uint8_t freq, const uint8_t dur )
  {
    for ( uint8_t t = 0; t < dur; t++ )
    {
  #if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
      if ( freq != 0 ){ SOUND_PORT = SOUND_PORT | ( 1 << SOUND_PIN); }
      _variableDelay_us( 255 - freq );
      SOUND_PORT = SOUND_PORT & ~( 1 << SOUND_PIN );
      _variableDelay_us( 255 - freq );
  #else
    #ifdef _USE_ARDUBOY2_
      // yeah, figure that out later...
    #else
      if ( freq != 0 ){ digitalWrite( SOUND_PIN, 1 ); }
      _variableDelay_us( 255 - freq );
      digitalWrite( SOUND_PIN, 0 );
      _variableDelay_us( 255 - freq );
    #endif
  #endif
    }
  }
#endif

/*-------------------------------------------------------*/
void InitDisplay()
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    TinyOLED_init();
  #else
    #if defined( _SSD1306XLED_TINY_INIT_SUPPORTED_ )
      // library supports shorter init method
      SSD1306.ssd1306_tiny_init();
    #else
      // use standard init method
      SSD1306.ssd1306_init();
    #endif
  #endif
#else
  #ifdef _USE_ARDUBOY2_
    _frameBuffer = arduboy.getBuffer();
  #else
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // Address 0x3D for 128x64
    if( !display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { 
      // extended the error message
      Serial.println(F("SSD1306 allocation failed - 1024 bytes for frame buffer required!")); for(;;);
    }

    // get raw image buffer
    _frameBuffer = display.getBuffer();
  #endif

  // enable horizontal addressing mode
  _verticalAddressingModeEnabled = false;
  // reset display coordinates
  _column = 0;
  _row = 0;
#endif
}

/*-------------------------------------------------------*/
void InitDisplayVertical()
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    TinyOLED_init();
  #elif defined( _SSD1306XLED_TINY_INIT_SUPPORTED_ )
    #if defined( _SSD1306XLED_INIT_VERTICAL_SUPPORTED_ )
      // library supports shorter init method
      SSD1306.ssd1306_tiny_init_vertical();
    #else    
      // library supports shorter init method
      SSD1306.ssd1306_tiny_init();
      // enable vertical addressing mode
      EnableVerticalAddressingMode();
    #endif
  #else
    // use standard init method
    SSD1306.ssd1306_init();
    // enable vertical addressing mode
    EnableVerticalAddressingMode();
  #endif
#else
  #ifdef _USE_ARDUBOY2_
    _frameBuffer = arduboy.getBuffer();
  #else
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // Address 0x3C for 128x64
    if( !display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { 
      // extended the error message
      Serial.println(F("SSD1306 allocation failed - 1024 bytes for frame buffer required!")); for(;;);
    }
    // get raw image buffer
    _frameBuffer = display.getBuffer();
  #endif

  // enable vertical addressing mode
  _verticalAddressingModeEnabled = true;
  // reset display coordinates
  _column = 0;
  _row = 0;
#endif
}

/*-------------------------------------------------------*/
void EnableVerticalAddressingMode()
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    i2c_start();
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    i2c_write(SSD1306_ADDRESS << 1);
    // Envoie l’octet de contrôle pour indiquer des données
    i2c_write(0x40);
    i2c_write(0x20); i2c_write(0x01);
    i2c_stop();
  #else
    SSD1306.ssd1306_send_command_start();
    SSD1306.ssd1306_send_byte( 0x20 ); SSD1306.ssd1306_send_byte( 0x01 );
    SSD1306.ssd1306_send_byte( 0x21 ); SSD1306.ssd1306_send_byte( 0x00 ); SSD1306.ssd1306_send_byte( 0x7f );
    SSD1306.ssd1306_send_byte( 0x22 ); SSD1306.ssd1306_send_byte( 0x00 ); SSD1306.ssd1306_send_byte( 0x07 );
    SSD1306.ssd1306_send_command_stop();
  #endif
#else
  // enable vertical addressing mode
  _verticalAddressingModeEnabled = true;
  // reset display coordinates
  _column = 0;
  _row = 0;
#endif
}

/*-------------------------------------------------------*/
void DisableVerticalAddressingMode()
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    i2c_start();
    i2c_write(0x20); i2c_write(0x00);
    i2c_stop();
  #else
    SSD1306.ssd1306_send_command_start();
    SSD1306.ssd1306_send_byte( 0x20 ); SSD1306.ssd1306_send_byte( 0x00 );
    SSD1306.ssd1306_send_byte( 0x21 ); SSD1306.ssd1306_send_byte( 0x00 ); SSD1306.ssd1306_send_byte( 0x7f );
    SSD1306.ssd1306_send_byte( 0x22 ); SSD1306.ssd1306_send_byte( 0x00 ); SSD1306.ssd1306_send_byte( 0x07 );
    SSD1306.ssd1306_send_command_stop();
  #endif
#else
  // enable horizontal addressing mode
  _verticalAddressingModeEnabled = false;
  // reset display coordinates
  _column = 0;
  _row = 0;
#endif
}

/*-------------------------------------------------------*/
// This code will init the display for row <y>
void PrepareDisplayRow( uint8_t y )
{
#if defined(__AVR_ATtiny85__)  /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    ssd1306_selectPage( y );
  #else
      // initialize image transfer to segment 'y'
      SSD1306.ssd1306_send_command(0xb0 + y);
      SSD1306.ssd1306_send_command(0x00);
      SSD1306.ssd1306_send_command(0x10);  
      SSD1306.ssd1306_send_data_start();
  #endif

#else  /* codepath for any Adafruit_SSD1306 supported MCU */
  // address the display buffer
  _row = y;
#endif
}

/*-------------------------------------------------------*/
void StartSendPixels()
{
#if defined(__AVR_ATtiny85__)  /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    i2c_start();
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    i2c_write(SSD1306_ADDRESS << 1);
    // Envoie l’octet de contrôle pour indiquer des données
    i2c_write(0x40);
  #else
    SSD1306.ssd1306_send_data_start();
  #endif
#endif
}

#if !defined(__AVR_ATtiny85__)  /* codepath for ATtiny85 */
/*-------------------------------------------------------*/
// writes the pixles and handles the addressing of columns and rows
void writePixelsToFrameBuffer( uint8_t pixels )
{
  _frameBuffer[_column + _row * 128] = pixels;
  if ( _verticalAddressingModeEnabled )
  {
    _row++;
    if ( _row > 7 )
    {
      _row = 0;
      _column++;
      if ( _column > 127 )
      {
        _column = 0;
      }
    }
  }
  else
  {
    _column++;
    if ( _column > 127 )
    {
      _column = 0;
      _row++;
      if ( _row > 7 )
      {
        _row = 0;
      }
    }
  }
}
#endif

/*-------------------------------------------------------*/
void SendPixels( uint8_t pixels )
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined(_USE_FAST_TINY_DRIVER_)
    i2c_write( pixels );
  #else
    // send a byte directly to the SSD1306
    SSD1306.ssd1306_send_byte( pixels );
  #endif
#else  /* codepath for any Adafruit_SSD1306 supported MCU */
  // write pixels directly into the buffer
  writePixelsToFrameBuffer( pixels );
#endif
}

/*-------------------------------------------------------*/
void StopSendPixels()
{
#if defined(__AVR_ATtiny85__)  /* codepath for ATtiny85 */
  #if defined (_USE_FAST_TINY_DRIVER_)
    i2c_stop();
  #else
    SSD1306.ssd1306_send_data_stop();
  #endif
#endif
}

/*-------------------------------------------------------*/
// This code will finish a row (only on Tiny85)
void FinishDisplayRow()
{
#if defined(__AVR_ATtiny85__)
  // this line appears to be optional, as it was never called during the intro screen...
  // but hey, we still have some bytes left ;)
  StopSendPixels();
#endif
}

/*-------------------------------------------------------*/
void DisplayBuffer()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  #ifdef _USE_ARDUBOY2_
    arduboy.display();
  #else
    // display buffer (not necessary)
    display.display();

    // slow down fast microcontrollers (maybe obsolete)
    #if defined(_VARIANT_ARDUINO_ZERO_)
      // wait 100ms to compensate for extremely fast hardware i2c
      delay( 100 );
    #endif
  #endif

  #ifndef _SERIAL_SCREENSHOT_NO_AUTO_SHOT_
    // check for screenshot request
    CheckForSerialScreenshot();
  #endif
#endif
}

/*-------------------------------------------------------*/
// Output is one hex byte per pixel. To get the actual image perform the following steps:
// (1) The output can be converted to binary with 'https://tomeko.net/online_tools/hex_to_file.php?lang=en' online.
// (2) Then import the file with IrfanView (https://www.irfanview.com/): Open as -> RAW file...
// (3) Set Image width to 64 and Image height to 128, 8 BPP -> OK
// (4) Rotate and mirror the result as needed :)
void SerialScreenshot()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    // print a short header
    Serial.println( F("\r\nThis is a TinyJoypad screenshot. Output is one hex byte per pixel. To get the actual image perform the following steps:") );
    Serial.println( F("(1) The output can be converted to binary with 'https://tomeko.net/online_tools/hex_to_file.php?lang=en' online.") );
    Serial.println( F("(2) Then import the file with IrfanView (https://www.irfanview.com/): Open as -> RAW file...") );
    Serial.println( F("(3) Set Image width to 64 and Image height to 128, 8 BPP -> OK") );
    Serial.println( F("(4) Rotate and mirror the result as needed :)\r\n") );
    Serial.println( F("Hint: If you only get partial screenshots, try using a terminal program to capture the serial output.") );
    // output the full buffer as a hexdump to the serial port
    printScreenBufferToSerial( display.getBuffer(), 128, 8 );
  #endif
#endif
}

/*-------------------------------------------------------*/
// Perform a screenshot if 
//  [x] enabled and 
//  [x] trigger condition met
void CheckForSerialScreenshot()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    if ( _SERIAL_SCREENSHOT_TRIGGER_CONDITION_ )
    {
      // perform the screenshot
      SerialScreenshot();
    }
  #endif
#endif
}

///////////////////////////////////////////////////////////////////////////////////
// serial output without clustering the code with #if !defined(__AVR_ATtiny85__)...

/*-------------------------------------------------------*/
void serialPrint( const char *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const char *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrint( const __FlashStringHelper *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const __FlashStringHelper *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrint( const int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( number );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( number );
#endif
}
