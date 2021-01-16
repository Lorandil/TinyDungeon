#ifndef _SERIAL_HEX_TOOLS_H_
#define _SERIAL_HEX_TOOLS_H_

#if !defined(__AVR_ATtiny85__)
  static uint8_t hexdumpPositionCount = 0;
  static uint8_t hexdumpValuesPerLine = 8;

  void hexdumpResetPositionCount();
  void hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  void EEPROM_hexdumpToSerial( uint16_t startAddress, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  void pgm_hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  void printHexToSerial( uint8_t value, bool addComma = false );
#endif

#endif
