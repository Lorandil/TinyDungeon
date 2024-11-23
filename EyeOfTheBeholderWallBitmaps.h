#pragma once

// Dungeon walls inspired by Eye of the Beholder
// The walls are made from small, irregular rocks - I prefer this look ;)

// 'EOB_frontwall88x64_D1_inv', 88x64px (704 bytes)
const unsigned char smallFrontWall_D1 [] PROGMEM = {
	0x00, 0x80, 0xe0, 0xf0, 0xf0, 0x70, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 
	0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x80, 0xe0, 0xe0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 
	0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
	0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x78, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x07, 0x00, 0x78, 0xf3, 0xf7, 
	0xef, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x7c, 0x00, 0x03, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x78, 0x00, 0x07, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0xfe, 0xfd, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x03, 0x00, 
	0xfc, 0xfc, 0xf8, 0xf1, 0x01, 0x01, 0xf1, 0xf9, 0xfd, 0xfd, 0xfd, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 
	0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xdc, 0xdc, 0xfd, 0xfd, 0xf9, 0xf1, 0x01, 0x01, 0xe1, 0xf1, 
	0xf9, 0xf9, 0xf9, 0xfd, 0xfd, 0x3d, 0xfd, 0xfd, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf9, 
	0xf9, 0xf1, 0xe1, 0x01, 0x01, 0xe1, 0xf1, 0xf9, 0xf9, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xbc, 
	0xc8, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf9, 0xf1, 0x01, 0x01, 0xf1, 0xf9, 0xf9, 0xfd, 0x7d, 0x7d, 
	0xfd, 0xfd, 0xfd, 0xfc, 0xf8, 0xf8, 0xf8, 0xfc, 0x3f, 0x3f, 0x3f, 0x9f, 0x80, 0x80, 0x8f, 0x1f, 
	0x3f, 0x3f, 0x77, 0x6f, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
	0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7d, 
	0x7f, 0x7b, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x01, 0x00, 0x0e, 0x3f, 0x7f, 0x7f, 
	0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 
	0x3e, 0x30, 0x03, 0x0f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xee, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 
	0xc0, 0xe0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xef, 0xdf, 0xdf, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0x00, 0x00, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0x1c, 0x00, 0xc0, 0xf8, 
	0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xbe, 0xde, 0xdf, 0xef, 0xef, 0xef, 0xff, 0xff, 0xff, 0xfe, 
	0xfe, 0xfe, 0xfc, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0x9f, 0x9e, 0x9e, 0x9d, 0x9f, 0x9f, 0x9f, 0x1f, 
	0x1f, 0x0f, 0x0f, 0x87, 0xc3, 0xc1, 0xe0, 0xe0, 0xc3, 0x87, 0x8f, 0x1f, 0x1f, 0x1f, 0x9f, 0x9f, 
	0x9f, 0xbf, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x8f, 0x87, 0x80, 
	0x80, 0x87, 0x8f, 0x8f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x8f, 0x97, 0x17, 0x1b, 0x1f, 0x1f, 0x1f, 
	0x1f, 0x1f, 0x8f, 0x87, 0x80, 0x80, 0x87, 0x8f, 0x8f, 0x9f, 0x9f, 0x9f, 0x9f, 0xbf, 0xbf, 0x3f, 
	0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x80, 0x80, 0x8e, 0x9f, 0xbf, 0xbf, 
	0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x0e, 0xc0, 0xff, 0xff, 0xff, 0xfb, 0xf7, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xe0, 
	0xc0, 0x0e, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x7f, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xce, 0x00, 0x00, 0x78, 0xfe, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 
	0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0x38, 0x00, 0xc0, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 
	0x0c, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x1f, 
	0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0e, 0x07, 0x07, 0x03, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 
	0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 
	0x01, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
	0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f
};

// 'EOB_frontwall44x32_D2_inv', 44x32px (176 bytes)
const unsigned char smallFrontWall_D2 [] PROGMEM = {
	0xfe, 0xfe, 0xbe, 0xfe, 0x7e, 0x7c, 0x00, 0x7c, 0x7c, 0xfe, 0xfe, 0xf6, 0xfe, 0xfe, 0xde, 0x7e, 
	0x7c, 0x00, 0x78, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x7c, 0x18, 0x80, 0xfc, 0xfe, 
	0xfe, 0xde, 0xee, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7c, 0x00, 0x1c, 0xfe, 0x3c, 0x7c, 0x7c, 0x7e, 
	0x7e, 0x7f, 0x7f, 0x7e, 0x7c, 0x30, 0x08, 0x3c, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x6e, 0x7e, 0x7e, 
	0x3e, 0x0c, 0x30, 0x7c, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7c, 0x7d, 0x39, 0x00, 0x3c, 0x7c, 0x7e, 
	0x7e, 0x7e, 0x7e, 0x6c, 0x6e, 0x76, 0x3e, 0x00, 0x7f, 0x7f, 0x7f, 0x3e, 0x00, 0x1e, 0x7f, 0x7f, 
	0x7f, 0x7f, 0x7f, 0x77, 0x7f, 0x7e, 0x3e, 0x00, 0x3c, 0x7f, 0x7f, 0x7f, 0x7f, 0x77, 0x7f, 0x7f, 
	0x7f, 0x7f, 0x3c, 0x00, 0x3c, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x1e, 0x00, 0x3e, 
	0x6e, 0x7f, 0x7f, 0x7f, 0x00, 0x7e, 0x7b, 0x77, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3c, 0x00, 0x3e, 
	0x7e, 0x7f, 0x7b, 0x7f, 0x7f, 0x3f, 0x3f, 0x7f, 0x7e, 0x00, 0x3c, 0x7f, 0x7f, 0x7f, 0x77, 0x7f, 
	0x7f, 0x7f, 0x7f, 0x3e, 0x00, 0x3e, 0x7f, 0x7f, 0x7f, 0x5f, 0x7f, 0x77, 0x7f, 0x7f, 0x7e, 0x3c
};

// 'EOB_frontwall22x16_D3_inv', 22x16px (44 bytes)
const unsigned char smallFrontWall_D3 [] PROGMEM = {
	0x6e, 0xe4, 0xe2, 0xee, 0x0e, 0x6e, 0xec, 0xe0, 0xe6, 0xee, 0x0e, 0x4e, 0xe6, 0xe0, 0xe6, 0xee, 
	0x0e, 0x6e, 0xec, 0xe0, 0xee, 0x8e, 0x4e, 0x0d, 0x62, 0xec, 0xee, 0xee, 0x0e, 0x60, 0xee, 0xee, 
	0xee, 0x66, 0x0e, 0xe0, 0xec, 0xee, 0xce, 0x0e, 0x6c, 0xe0, 0xee, 0xee
};

// 'EOB_leftrightwalls_8x64_D0_inv', 8x64px (64 bytes)
const unsigned char leftRightWalls_D0 [] PROGMEM = {
	0xff, 0xfe, 0xfc, 0xf8, 0xf8, 0xfc, 0xfe, 0xff, 0x3f, 0x7f, 0xff, 0xfd, 0xff, 0xfd, 0x7f, 0x3f, 
	0xfe, 0x7f, 0xbe, 0xfe, 0x7e, 0xfe, 0xff, 0xfe, 0x7f, 0x7f, 0x7f, 0x3f, 0x7f, 0x7c, 0x7f, 0x3f, 
	0xfe, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xfe, 0xfc, 0x3f, 0x7f, 0xbf, 0x3e, 0xbf, 0xbf, 0x3f, 0x0f, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x7e, 0x3f, 0x0f, 0x1e, 0x3e, 0x7f, 0x7f
};

// 'EOB_leftrightwalls_44x64_D1_inv', 44x64px (352 bytes)
const unsigned char leftRightWalls_D1 [] PROGMEM = {
	0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0xe0, 0xfd, 0xf7, 0xff, 0xff, 
	0x1f, 0xc0, 0xfc, 0xfe, 0x9e, 0xfc, 0xfc, 0xf8, 0x00, 0xc0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0x00, 0xf8, 0xfe, 
	0xff, 0xd7, 0xff, 0xff, 0xff, 0x18, 0x67, 0xff, 0xfc, 0x01, 0xf9, 0xfd, 0xf8, 0xf9, 0xf3, 0xf7, 
	0xf7, 0xef, 0xef, 0xe3, 0x18, 0x9f, 0xdd, 0xbb, 0xbf, 0x9f, 0x00, 0x3f, 0x7e, 0xfc, 0xfc, 0x00, 
	0x7e, 0x77, 0xbf, 0x80, 0x8f, 0xdf, 0xdd, 0x1f, 0x8f, 0xc0, 0xe1, 0xf3, 0xf7, 0xf7, 0xf3, 0x03, 
	0xf1, 0xf8, 0xfc, 0xfe, 0x01, 0x3e, 0x7f, 0x7f, 0x7f, 0x7d, 0x7b, 0x7f, 0x7f, 0x7f, 0x3f, 0x07, 
	0x38, 0x7f, 0x7f, 0x77, 0x7d, 0x7f, 0x7f, 0x7f, 0xff, 0x3e, 0xfe, 0x7f, 0x00, 0x3f, 0x7f, 0x7f, 
	0x7f, 0x77, 0x3f, 0x00, 0x3f, 0x7f, 0x7f, 0x7d, 0x7e, 0x7f, 0x3f, 0x30, 0x03, 0x3f, 0x7f, 0x7f, 
	0x3f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xfc, 0xfe, 0xef, 0xdf, 0xff, 0xff, 0xfe, 0x00, 0xfe, 0xff, 
	0xff, 0xfd, 0xdf, 0x7e, 0x38, 0x06, 0x0e, 0x70, 0xfe, 0xff, 0xef, 0xff, 0xfe, 0x00, 0xfc, 0xfe, 
	0xbf, 0xff, 0xff, 0xff, 0x3e, 0xc0, 0xfe, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x9f, 0xcf, 
	0xe7, 0xe0, 0xe3, 0xf7, 0xf7, 0x07, 0xe7, 0xf3, 0xb9, 0xf8, 0xf0, 0x01, 0xfd, 0xfe, 0xfe, 0xde, 
	0x7f, 0x3f, 0x3f, 0x7e, 0x00, 0x70, 0xfe, 0xbd, 0xfc, 0xfc, 0xf0, 0x03, 0xc3, 0xe7, 0xf7, 0xf7, 
	0xe0, 0xe3, 0xe7, 0xcf, 0x9f, 0x1f, 0x1d, 0xbf, 0x00, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xf7, 0xff, 
	0x7f, 0x00, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x00, 0x0f, 0x3f, 0x3e, 0x7f, 0xff, 0xe7, 0xff, 0xff, 
	0x7f, 0x00, 0xff, 0xff, 0x00, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x0f
};

// 'EOB_leftrightwalls_22x32_D2_inv', 22x32px (88 bytes)
const unsigned char leftRightWalls_D2 [] PROGMEM = {
	0xfc, 0xf8, 0x00, 0xf0, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
	0xc0, 0xe0, 0xe0, 0x00, 0xf8, 0xfc, 0x00, 0xf9, 0xfc, 0xdd, 0xfb, 0x33, 0xc3, 0xf7, 0xd0, 0x77, 
	0x0e, 0xae, 0xf1, 0x96, 0xf7, 0xf8, 0xf3, 0x0b, 0xfc, 0xfd, 0xed, 0xfe, 0x7e, 0x3e, 0xbe, 0x9e, 
	0xd6, 0xde, 0x1c, 0xe8, 0xe6, 0xee, 0x6e, 0x4e, 0xee, 0xe0, 0x5e, 0x9e, 0xde, 0xa6, 0xb0, 0x2e, 
	0x7f, 0x7e, 0x00, 0x1f, 0x0f, 0x0f, 0x06, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x03, 0x07, 0x03, 0x0c, 0x1f, 0x37
};

// 'EOB_leftrightwalls_10x16_D3_inv', 10x16px (20 bytes)
const unsigned char leftRightWalls_D3 [] PROGMEM = {
	0xe4, 0xdc, 0x80, 0xd0, 0xb0, 0xb0, 0xc0, 0x18, 0xec, 0x68, 0x00, 0x36, 0x16, 0x08, 0x0a, 0x0a, 
	0x0a, 0x16, 0x34, 0x36
};

// 'EOB_outerleftrightwalls_D2_30x32_inv', 30x32px (120 bytes)
const unsigned char outerLeftRightWalls_D2 [] PROGMEM = {
	0xe0, 0x80, 0x40, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0x7b, 0x7f, 
	0x7a, 0x7b, 0x3b, 0x47, 0x77, 0x7f, 0x71, 0x74, 0x77, 0x7f, 0x7d, 0x7f, 0x7f, 0x60, 0x76, 0x77, 
	0x5f, 0x7d, 0x77, 0x47, 0x37, 0x70, 0x7b, 0x7b, 0x7b, 0x5b, 0x7f, 0x7b, 0xdf, 0xff, 0xef, 0xef, 
	0x0b, 0xef, 0xef, 0xef, 0xfe, 0xf0, 0xf6, 0xfe, 0xe5, 0x0f, 0x7f, 0xf7, 0xdf, 0xff, 0xf2, 0xf4, 
	0xfe, 0xeb, 0xeb, 0x0f, 0xef, 0xfe, 0xf1, 0xff, 0xfe, 0xce, 0x03, 0x02, 0x03, 0x01, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03
};

// 'EOB_outerleftrightwalls_D3_30x16_inv', 30x16px (60 bytes)
const unsigned char outerLeftRightWalls_D3 [] PROGMEM = {
	0x36, 0x40, 0x6c, 0x6e, 0x74, 0x7c, 0x2c, 0x60, 0x6c, 0xd8, 0x58, 0x18, 0xf0, 0xc0, 0xf0, 0xd0, 
	0xe0, 0xb0, 0xd8, 0xd8, 0x60, 0x18, 0x5c, 0x7c, 0x60, 0x6c, 0x6e, 0x6e, 0x0e, 0x6e, 0x77, 0x76, 
	0x70, 0x36, 0x07, 0x3f, 0x3f, 0x1f, 0x0a, 0x1a, 0x18, 0x02, 0x0a, 0x0e, 0x0e, 0x06, 0x08, 0x0b, 
	0x1a, 0x18, 0x1a, 0x06, 0x17, 0x3d, 0x3f, 0x3e, 0x78, 0x76, 0x06, 0x67
};

