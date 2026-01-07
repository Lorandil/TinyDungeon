#pragma once

#include <Arduino.h>

#define _USE_FAST_TINY_DRIVER_

#if defined( __AVR_ATtiny85__)
  // required for _delay_us()
  #include <util/delay.h>
#else
  #define _delay_ms    delay
  #define _delay_us    delayMicroseconds
#endif

////////////////////////////////////////////////////////////
// Uncomment the following line to enable serial screenshot
//#define _ENABLE_SERIAL_SCREENSHOT_
// perform a serial screenshot if this condition is true:
#define _SERIAL_SCREENSHOT_TRIGGER_CONDITION_ ( isFirePressed() )
// uncomment to disable automatic screenshot function
//#define _SERIAL_SCREENSHOT_NO_AUTO_SHOT_


////////////////////////////////////////////////////////////
// Pin definitions for the joystick and the fire button
#if defined(__AVR_ATtiny85__)
  // don't change these (or you won't support TinyJoypad anymore!)
  #define LEFT_RIGHT_BUTTON A0
  #define UP_DOWN_BUTTON    A3
  #define FIRE_BUTTON        1
  #define SOUND_PIN          4
  #define SOUND_PORT_DDR  DDRB
  #define SOUND_PORT     PORTB
  // disable extended features
  #undef USE_EXTENDED_CHECKS
  #undef USE_SERIAL_PRINT

  // Analog limits for joystick control (controller/voltage dependent)
  const uint16_t ANALOG_LOWER_LIMIT_MIN = 500;
  const uint16_t ANALOG_LOWER_LIMIT_MAX = 750;
  const uint16_t ANALOG_UPPER_LIMIT_MIN = 750;
  const uint16_t ANALOG_UPPER_LIMIT_MAX = 950;
#else
  #if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328P__) || defined(_VARIANT_ARDUINO_ZERO_) || defined(ARDUINO_UNOWIFIR4) || defined(ARDUINO_UNOR4_MINIMA)
    // Arduino Mega 2560 (and compatible)
    #define LEFT_RIGHT_BUTTON A0
    #define UP_DOWN_BUTTON    A3
    #define FIRE_BUTTON       A1
    #define SOUND_PIN         12
  #else
    // change these definitions as required
    #define LEFT_RIGHT_BUTTON A0
    #define UP_DOWN_BUTTON    A3
    #define FIRE_BUTTON       A1
    #define SOUND_PIN          4
    #define SOUND_PORT_DDR  DDRB
    #define SOUND_PORT     PORTB
  #endif

  // Analog limits for joystick control (controller/voltage dependent)
  #if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328P__)
    const uint16_t ANALOG_LOWER_LIMIT_MIN = 500;
    const uint16_t ANALOG_LOWER_LIMIT_MAX = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MIN = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MAX = 950;
  #elif defined(_VARIANT_ARDUINO_ZERO_)
    const uint16_t ANALOG_LOWER_LIMIT_MIN = 500;
    const uint16_t ANALOG_LOWER_LIMIT_MAX = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MIN = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MAX = 950;
  #elif defined(ARDUINO_UNOWIFIR4) || defined(ARDUINO_UNOR4_MINIMA)
    const uint16_t ANALOG_LOWER_LIMIT_MIN = 300;
    const uint16_t ANALOG_LOWER_LIMIT_MAX = 540;
    const uint16_t ANALOG_UPPER_LIMIT_MIN = 540;
    const uint16_t ANALOG_UPPER_LIMIT_MAX = 650;
  #else
    const uint16_t ANALOG_LOWER_LIMIT_MIN = 500;
    const uint16_t ANALOG_LOWER_LIMIT_MAX = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MIN = 750;
    const uint16_t ANALOG_UPPER_LIMIT_MAX = 950;
  #endif

  // use extensive checks (not memory restricted by ATtiny85...)
  #define USE_EXTENDED_CHECKS
  #define USE_SERIAL_PRINT
#endif


// funciton for initializing the TinyJoypad (ATtiny85) and other microcontrollers
void InitTinyJoypad();

// switch between vertical and horizontal addressing modes
void EnableVerticalAddressingMode();
void DisableVerticalAddressingMode();

// function for direct joystick readings
bool isLeftPressed();
bool isRightPressed();
bool isUpPressed();
bool isDownPressed();
bool isFirePressed();
void waitUntilButtonsReleased();
void waitUntilButtonsReleased( const uint8_t delayTime );

// read analog joystick inputs into internal variables
void readAnalogJoystick();
// functions for working on buffered joystick readings
bool wasLeftPressed();
bool wasRightPressed();
bool wasUpPressed();
bool wasDownPressed();
// returns the analog values
uint16_t getAnalogValueX();
uint16_t getAnalogValueY();

#if defined( __AVR_ATtiny85__)
  void __attribute__ ((noinline)) _variableDelay_us( uint8_t delayValue );
#endif
void Sound( const uint8_t freq, const uint8_t dur );

// functions to simplify display handling between ATtiny85 and Ardafruit_SSD1306
void InitDisplay();
void InitDisplayVertical();
void PrepareDisplayRow( uint8_t y );
void StartSendPixels();
void SendPixels( uint8_t pixels );
void StopSendPixels();
void FinishDisplayRow();
void DisplayBuffer();

// screenshot functions
void SerialScreenshot();
void CheckForSerialScreenshot();

// serial output without clustering the code with #if !defined(__AVR_ATtiny85__)...
void serialPrint( const char *text );
void serialPrintln( const char *text );
void serialPrint( const __FlashStringHelper *text );
void serialPrintln( const __FlashStringHelper *text );
//void serialPrint( const unsigned int number );
//void serialPrintln( const unsigned int number );
void serialPrint( const int number );
void serialPrintln( const int number );

#if !defined( __AVR_ATtiny85__)
class Logger
{
public:
  Logger(const char* text)
  {
    serialPrint(F("-> "));
  #if _MSC_VER
    strncpy_s(_text, text, sizeof(_text));
  #else
    strncpy(_text, text, sizeof(_text));
  #endif
    _text[sizeof(_text) - 1] = 0;
    serialPrintln(text);
    _startTime = millis();
  }
  ~Logger()
  {
    serialPrint(F("<- "));
    serialPrint(_text);
    serialPrint(F("[time = "));
    serialPrint( millis() - _startTime );
    serialPrintln(F("]"));
  }
private:
  char   _text[16];
  unsigned long _startTime;
};
#endif
