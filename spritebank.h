#pragma once

#include <Arduino.h>
#include "dungeonTypes.h"

// 'frontwall24x16_inv2_cropped', 96x16px
const unsigned char frontWalls_D3 [] PROGMEM = {
  0xee, 0x0e, 0xee, 0xee, 0xe0, 0xee, 0xee, 0x0e, 0xee, 0xee, 0xee, 0xe2, 0x2c, 0xce, 0xee, 0xee, 
  0xee, 0xee, 0x2e, 0xce, 0xe8, 0xe6, 0xee, 0xee, 0x4e, 0xae, 0xee, 0xee, 0xe8, 0xe6, 0xee, 0xee, 
  0xee, 0xee, 0xe2, 0x6c, 0x8e, 0xee, 0xee, 0xee, 0xee, 0xe2, 0xcc, 0x2e, 0xee, 0xee, 0xee, 0xee, 
  0xee, 0xee, 0x0e, 0xee, 0xec, 0xe2, 0xee, 0xee, 0xce, 0x2e, 0xee, 0xec, 0xe2, 0x2e, 0xce, 0xee, 
  0xee, 0xee, 0xee, 0x2e, 0xce, 0xe8, 0xe6, 0xee, 0xee, 0xce, 0x2e, 0xee, 0xee, 0xe8, 0xe6, 0xee, 
  0x2e, 0xce, 0xee, 0xe8, 0xe6, 0xee, 0xce, 0x2e, 0xee, 0xee, 0xe0, 0xce, 0x2e, 0xee, 0xee, 0xee, 
  0x6e, 0x6e, 0x6e, 0x62, 0x6c, 0x0e, 0x6e, 0x6e, 0x6e, 0x62, 0x6c, 0x0e, 0x6e, 0x6e, 0x6e, 0x60, 
  0x6e, 0x4e, 0x2e, 0x6e, 0x6e, 0x64, 0x6a, 0x6e, 0x6e, 0x6e, 0x6e, 0x26, 0x48, 0x6e, 0x6e, 0x6e, 
  0x6e, 0x66, 0x68, 0x0e, 0x6e, 0x6e, 0x6e, 0x6c, 0x62, 0x6e, 0x6e, 0x0e, 0x6e, 0x60, 0x6e, 0x6e, 
  0x6e, 0x6e, 0x6e, 0x6c, 0x62, 0x6e, 0x0e, 0x6e, 0x6e, 0x6e, 0x62, 0x2c, 0x4e, 0x6e, 0x6e, 0x6e, 
  0x60, 0x6e, 0x4e, 0x2e, 0x6e, 0x6e, 0x62, 0x6c, 0x6e, 0x6e, 0x6e, 0x4e, 0x2e, 0x68, 0x66, 0x6e, 
  0x6e, 0x6e, 0x62, 0x2c, 0x4e, 0x6e, 0x6e, 0x6e, 0x6e, 0x60, 0x6e, 0x2e, 0x4e, 0x6e, 0x60, 0x6e
};

// 'frontwall48x32_inv2_cropped', 96x32px
const unsigned char frontWalls_D2 [] PROGMEM = {
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x80, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xe0, 0x1e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x3c, 0xc2, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0xe2, 0x1e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xe0, 0x1e, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0x02, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0x7e, 0x7e, 0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x0e, 0x70, 0x7e, 
  0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x0e, 0x70, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 
  0x7e, 0x7e, 0x7e, 0x70, 0x0e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x0e, 
  0x70, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7c, 0x02, 0x7e, 
  0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x0e, 0x70, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 
  0x7e, 0x7e, 0x7e, 0x70, 0x0e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 0x41, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x0f, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x40, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 0x41, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x0f, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x0f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x03, 0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x07, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x07, 0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x07, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x47, 0x38, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f
};

// 'frontwall96x64_inv2', 96x64px
const unsigned char frontWalls_D1 [] PROGMEM = {
  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
  0xf8, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 
  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
  0x78, 0x08, 0x80, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x07, 0x02, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x00, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 
  0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf0, 0x00, 0x1c, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x40, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x41, 0x00, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x70, 0x03, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x00, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x02, 
  0x00, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x38, 0x00, 0x86, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x0f, 0x07, 0x27, 0x30, 
  0x30, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
  0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
  0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x3f, 0x3f, 
  0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
  0x3f, 0x3f, 0x03, 0x20, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x3f, 0x0f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x80, 0x1f, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
  0x1f, 0x1f, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x1f, 0x1f, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x01, 0x00, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
};

// 'leftrightwalls_inv2', 96x64px
const unsigned char leftRightWalls [] PROGMEM = {
  0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0x00, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 
  0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xe0, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 
  0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0xe0, 0xf0, 0xf0, 
  0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 0xe7, 0xff, 0xff, 0xff, 0x7f, 0x7f, 
  0xff, 0xff, 0xfe, 0xfe, 0xfe, 0x01, 0xfd, 0xfd, 0xfb, 0xf8, 0xf7, 0xf7, 0xf7, 0xef, 0xef, 0xef, 
  0x1f, 0xdf, 0xdf, 0xbf, 0xbf, 0xbf, 0x7f, 0x7f, 0x7e, 0xfc, 0xfc, 0xf8, 0x00, 0xf0, 0xe0, 0xc0, 
  0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
  0xc0, 0xe0, 0xf0, 0x00, 0xf8, 0xfc, 0xfc, 0x7e, 0x7f, 0x7f, 0xbf, 0x83, 0xb8, 0xdf, 0xdf, 0x1f, 
  0xcf, 0xef, 0xef, 0xf7, 0xf7, 0xf7, 0xfb, 0xfb, 0xfd, 0xfc, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x01, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x07, 
  0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xfe, 0xfe, 0xfd, 0xfc, 0xfd, 0xfb, 0x3b, 
  0xc3, 0xf7, 0xf0, 0xf7, 0xee, 0xec, 0xdc, 0xc0, 0xd0, 0xb0, 0xa0, 0xc0, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x80, 0xc0, 0xa0, 0xb0, 0xd0, 0x18, 0xec, 0xec, 0xee, 0xf1, 0xf6, 0xf7, 0xfb, 
  0xf3, 0x0b, 0xfd, 0xfc, 0xfd, 0xfe, 0xfe, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x78, 0x06, 0x7e, 0xbe, 0xbe, 0x9e, 0xde, 0xde, 
  0x1e, 0xe8, 0xe6, 0xee, 0x6e, 0x06, 0x36, 0x16, 0x08, 0x0a, 0x06, 0x02, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x02, 0x02, 0x06, 0x0a, 0x0a, 0x16, 0x36, 0x36, 0x6e, 0xee, 0xe0, 0xde, 0xde, 
  0xde, 0xbe, 0xbe, 0x3e, 0x7e, 0x7e, 0x0e, 0x70, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x3f, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x7f, 0x7f, 0xbf, 0xbf, 0x3f, 0xdf, 0xdf, 0xdf, 0xef, 0xe0, 0xef, 0xf7, 0xf7, 0xf7, 0xf7, 0xfb, 
  0xfb, 0xfb, 0xfd, 0x01, 0xfd, 0xfe, 0xfe, 0xfe, 0x7f, 0x3f, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
  0x03, 0x07, 0x03, 0x0c, 0x1f, 0x3f, 0x3f, 0x7f, 0xfe, 0xfe, 0xfe, 0xfd, 0x3d, 0xc5, 0xfb, 0xfb, 
  0xf3, 0xf7, 0xf7, 0xf7, 0xe0, 0xef, 0xef, 0xef, 0xdf, 0x1f, 0xdf, 0xbf, 0xbf, 0xbf, 0x7f, 0x7f, 
  0xff, 0xff, 0xff, 0x3f, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 
  0x0f, 0x0f, 0x07, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x07, 0x0f, 0x0f, 
  0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x7f, 0x3f, 0x3f, 0x00, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f
};

// 'Title32x64', 32x64px
const unsigned char statusPane [] PROGMEM = {
	0x00, 0x00, 0x08, 0x04, 0x04, 0x08, 0x10, 0x10, 0x08, 0x04, 0x04, 0x08, 0x14, 0x3e, 0x22, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x22, 0x3e, 0x14, 0x08, 0x04, 0x04, 0x08, 0x10, 0x10, 0x08, 0x04, 0x04, 
	0x00, 0x00, 0x01, 0x01, 0x7f, 0x01, 0x75, 0x01, 0x79, 0x08, 0x71, 0x01, 0x79, 0x40, 0xf9, 0x01, 
	0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 
	0x00, 0x00, 0x21, 0xa1, 0x3f, 0xa1, 0xa1, 0x1e, 0x80, 0x9c, 0x20, 0xbd, 0x81, 0xbd, 0x05, 0xb8, 
	0x80, 0x98, 0xa4, 0x7c, 0x00, 0x38, 0x54, 0x58, 0x00, 0x3c, 0x44, 0x78, 0x00, 0x7c, 0x04, 0x78, 
	0x00, 0xb8, 0x44, 0xa8, 0x14, 0x14, 0x14, 0x08, 0x14, 0x14, 0x14, 0x08, 0x14, 0x14, 0x14, 0x14, 
	0x08, 0x14, 0x14, 0x14, 0x14, 0x08, 0x14, 0x14, 0x14, 0x14, 0x08, 0x14, 0x14, 0xe4, 0x14, 0xe8, 
	0x00, 0xf7, 0x08, 0xf7, 0x00, 0x00, 0x3e, 0x08, 0x3e, 0x00, 0x3e, 0x0a, 0x0e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x42, 0xbd, 
	0x00, 0xde, 0x21, 0xde, 0x00, 0x00, 0x1e, 0x12, 0x0c, 0x00, 0x1c, 0x0a, 0x1c, 0x00, 0x1e, 0x04, 
	0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbb, 0x44, 0xbb, 
	0x00, 0xfb, 0x04, 0xfb, 0x00, 0x00, 0x0c, 0x12, 0x12, 0x0c, 0x0c, 0x1c, 0x0c, 0x1c, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x08, 0xf7, 
	0x00, 0x5e, 0xa1, 0x9e, 0xa0, 0xa0, 0x40, 0xa0, 0xa0, 0xa0, 0x40, 0xa0, 0xa0, 0xa0, 0x40, 0xa0, 
	0xa0, 0xa0, 0x40, 0xa0, 0xa0, 0xa0, 0xa0, 0x40, 0xa0, 0xa0, 0xa0, 0x40, 0xa0, 0x9e, 0xa1, 0x5e
};

// 'beholder32x56_w_mask', 64x56px
const unsigned char beholder [] PROGMEM = {
	0x38, 0x44, 0x82, 0x39, 0x29, 0x39, 0x82, 0x44, 0x38, 0x00, 0x00, 0x38, 0x44, 0x82, 0x39, 0x29, 
	0x39, 0x82, 0x44, 0x38, 0x70, 0x88, 0x04, 0x72, 0x52, 0x72, 0x04, 0x88, 0x70, 0x00, 0x00, 0x00, 
	0xff, 0xc7, 0x83, 0x01, 0x01, 0x01, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x83, 0x01, 0x01, 
	0x01, 0x83, 0xc7, 0xff, 0xff, 0x8f, 0x07, 0x03, 0x03, 0x03, 0x07, 0x8f, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x03, 0x04, 0x18, 0x60, 0x83, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x80, 
	0x7e, 0x01, 0x80, 0x60, 0x18, 0x04, 0xc3, 0x30, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xfc, 0xf8, 0xe0, 0x83, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x80, 
	0xfe, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0xc3, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x46, 0x48, 0x30, 0x33, 0x3c, 0x13, 0x1c, 0x10, 0x11, 
	0x1e, 0x1e, 0x11, 0x30, 0x2c, 0x23, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x78, 0x00, 0x03, 0x1f, 0x1f, 0x1c, 0x00, 0x01, 
	0x1f, 0x1f, 0x01, 0x00, 0x3c, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xc0, 0x30, 0x08, 0x04, 0x82, 0xe1, 0xe0, 0xe8, 0xe4, 0xd4, 0x96, 0x36, 0x73, 0xf3, 0xf3, 0xfb, 
	0x9b, 0xcb, 0xf3, 0xf2, 0xf6, 0xe4, 0xec, 0x68, 0x60, 0xe1, 0x82, 0x04, 0x08, 0x30, 0xc0, 0x00, 
	0xff, 0x3f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x3f, 0xff, 0xff, 
	0x45, 0x00, 0x00, 0xfe, 0xff, 0xef, 0xe7, 0xf7, 0xf3, 0xfb, 0xfb, 0xff, 0xe1, 0x40, 0xc0, 0xc0, 
	0x40, 0xe1, 0xff, 0xed, 0xed, 0xcd, 0xdc, 0x9e, 0xbf, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x45, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 
	0x07, 0x18, 0x20, 0x40, 0x83, 0x07, 0x07, 0x2f, 0x6f, 0x47, 0xd3, 0xd9, 0xdc, 0xde, 0xdf, 0xdf, 
	0xde, 0xd8, 0xd3, 0xdf, 0xdf, 0x4f, 0x6f, 0x2f, 0x07, 0x03, 0x83, 0x40, 0x20, 0x18, 0x07, 0x00, 
	0xff, 0xf8, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0x11, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'joey28x40_w_mask', 56x40px
const unsigned char joey [] PROGMEM = {
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x98, 0x9c, 
	0xfc, 0xfe, 0xfe, 0x9e, 0x9c, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x07, 0xff, 0xff, 0xff, 0xff, 0x0e, 0xf1, 0x00, 0x0f, 0x70, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x14, 0xd7, 0x14, 0x07, 0x07, 0x03, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xf1, 0x00, 0x00, 0x00, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x78, 0x70, 0x60, 0x00, 0x00, 0x00, 0x60, 0x70, 0x78, 0x78, 0xfc, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x07, 0x78, 0x80, 0x03, 0x7c, 0x80, 0x80, 0x00, 0x80, 0xf0, 0x3c, 0x07, 0x7d, 0xed, 
	0x45, 0x37, 0xf5, 0x25, 0xed, 0x27, 0xe9, 0x27, 0xe0, 0x20, 0xc0, 0x00, 0xff, 0xff, 0xf8, 0x80, 
	0x00, 0x00, 0x03, 0x7f, 0x7f, 0x7f, 0x07, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x1f, 0x00, 0x00, 0x00, 0x04, 0x0b, 0x0a, 0x08, 0x10, 
	0x10, 0x06, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x5d, 0x9f, 0x40, 0x3f, 0x60, 0x7f, 0x40, 0x7f, 0x40, 
	0x7f, 0x60, 0x3f, 0x00, 0xff, 0xff, 0xff, 0xfb, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xfc, 0xff, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x20, 0x2d, 
	0x00, 0x00, 0x00, 0x00, 0x2d, 0x20, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 
	0x80, 0x80, 0x0f, 0x1f, 0xbf, 0xff, 0xff, 0xff
};

// 'new_bars28x48_w_mask', 56x48px
const unsigned char newBars [] PROGMEM = {
	0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 
	0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x01, 0x00, 0x00, 0x01, 
	0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 
	0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x3f, 
	0x3f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x3f, 0x3f, 0x00, 0xc0, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 0x80, 0x80, 0xc0, 0xff, 0xff, 
	0xc0, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 0x80, 0x80, 0xc0
};

// 'door_32x64_w_mask', 64x64px
const unsigned char door [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
  0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 
  0x3f, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0xa0, 0x10, 0xe8, 0xf4, 0xf4, 0x42, 0xf8, 0xfa, 0xfd, 0x00, 0xfd, 0xfd, 0xfc, 
  0x21, 0xfd, 0xfd, 0xfd, 0x80, 0xfd, 0xfa, 0xf8, 0x02, 0xf4, 0xf4, 0xe8, 0x10, 0xe0, 0x00, 0x00, 
  0xff, 0xff, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0xff, 
  0x00, 0x00, 0x00, 0x31, 0x00, 0xb5, 0x31, 0x7b, 0x00, 0xff, 0xff, 0xff, 0x04, 0xff, 0xff, 0xff, 
  0x00, 0xff, 0xff, 0xff, 0x20, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xbd, 0x40, 0x00, 
  0xff, 0x31, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xff, 
  0x00, 0x00, 0x00, 0xee, 0x00, 0xfe, 0xfe, 0xff, 0x20, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
  0x04, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0x7f, 0x7f, 0x41, 0x7f, 0x7f, 0xff, 0x00, 0xf7, 0x00, 0x00, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0xde, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x02, 0xff, 0xff, 0xff, 
  0x00, 0xff, 0xff, 0xff, 0x03, 0xfe, 0xfe, 0xfe, 0x26, 0xf8, 0xf8, 0xff, 0x00, 0xde, 0x20, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xff, 
  0x00, 0x00, 0x00, 0x1b, 0x00, 0x5f, 0x1f, 0xbf, 0x02, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 
  0x01, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xbb, 0x40, 0x00, 
  0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xff, 
  0x00, 0x00, 0x00, 0x63, 0x00, 0xeb, 0xe3, 0xf7, 0x20, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
  0x08, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x04, 0xff, 0xff, 0xff, 0x00, 0xbb, 0x00, 0x00, 
  0xff, 0xe3, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0x00, 0x00, 0x00, 0x07, 0x08, 0x0d, 0x0d, 0x0d, 0x0c, 0x0d, 0x01, 0x0d, 0x0c, 0x0d, 0x0d, 0x0d, 
  0x00, 0x0d, 0x0d, 0x0d, 0x0e, 0x0d, 0x01, 0x0d, 0x0c, 0x0d, 0x0d, 0x0d, 0x08, 0x07, 0x00, 0x00, 
  0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff
};

// 'leverDown_32x24_w_mask', 32x24px
const unsigned char leverDown [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xfc, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0xfc, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x3f, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3f, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x7c, 0x44, 0x44, 0x40, 0x40, 0x40, 0x40, 0x44, 0x44, 0x7c, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0x83, 0x83, 0x83, 0x80, 0x80, 0x80, 0x80, 0x83, 0x83, 0x83, 0xff, 0xff, 0xff
};

// 'leverUp_32x24_w_mask', 32x24px
const unsigned char leverUp [] PROGMEM = {
  0x00, 0x00, 0x00, 0x3e, 0x22, 0x22, 0x02, 0x02, 0x02, 0x02, 0x22, 0x22, 0x3e, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0xc1, 0xc1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xc1, 0xc1, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0xfc, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xfc, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x3f, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x3f, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff
};

// 'chest24x24_closed_v3_w_mask', 48x24px
const unsigned char chestClosed [] PROGMEM = {
	0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
	0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 
	0x00, 0x77, 0x56, 0x76, 0x76, 0x76, 0x76, 0x76, 0x76, 0x86, 0x06, 0x66, 0x06, 0x86, 0x76, 0x76, 
	0x76, 0x76, 0x76, 0x76, 0x56, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0x77, 0x55, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x76, 0x76, 0x77, 0x77, 0x77, 
	0x77, 0x77, 0x77, 0x77, 0x55, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff
};

// 'chest24x24_open_w_mask', 48x24px
const unsigned char chestOpen [] PROGMEM = {
	0x00, 0x00, 0x00, 0xfe, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 
	0xb6, 0xb6, 0xb6, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0x00, 0x70, 0x50, 0x75, 0x71, 0x75, 0x71, 0x75, 0x71, 0x75, 0xf1, 0x35, 0x31, 0xf5, 0x71, 0x75, 
	0x71, 0x75, 0x71, 0x75, 0x50, 0x70, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0xff, 
	0x00, 0x77, 0x55, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x76, 0x77, 0x77, 0x77, 
	0x77, 0x77, 0x77, 0x77, 0x55, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff
};

// 'fountain_12x24_w_mask', 24x24px
const unsigned char fountain [] PROGMEM = {
	0x00, 0x00, 0x60, 0x10, 0x30, 0x24, 0xfc, 0x24, 0x30, 0x10, 0x60, 0x00, 0xff, 0x9f, 0x0f, 0x87, 
	0x83, 0x01, 0x01, 0x01, 0x83, 0x87, 0x0f, 0x9f, 0x00, 0x00, 0x0c, 0x34, 0x6a, 0xe8, 0x0f, 0xe8, 
	0x6a, 0x34, 0x0c, 0x00, 0xff, 0xf3, 0xc1, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xc1, 0xf3, 
	0x00, 0x00, 0x00, 0x10, 0x38, 0x2f, 0x20, 0x2f, 0x38, 0x10, 0x00, 0x00, 0xff, 0xff, 0xef, 0xc7, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0xc7, 0xef, 0xff
};

// 'rat_20x16_w_mask', 40x16px
const unsigned char rat [] PROGMEM = {
	0x00, 0x00, 0x18, 0x7e, 0xb0, 0xf0, 0xf0, 0xb8, 0xfc, 0xee, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
	0x28, 0x84, 0x00, 0x00, 0xff, 0xe7, 0x81, 0x00, 0x01, 0x07, 0x07, 0x03, 0x01, 0x00, 0x11, 0x1f, 
	0x1f, 0x3f, 0x7f, 0xc3, 0x01, 0x01, 0x7b, 0xff, 0x00, 0x0c, 0x06, 0x43, 0x43, 0x61, 0x31, 0x0e, 
	0x0f, 0x1f, 0x33, 0x4d, 0x5f, 0x7f, 0x5c, 0x08, 0x04, 0x0a, 0x00, 0x00, 0xe2, 0xe1, 0x30, 0x08, 
	0x18, 0x0c, 0x80, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa3, 0xe0, 0xe0, 0xf0, 0xff
};
