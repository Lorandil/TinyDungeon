/*
 * FastTinyDriver.h
 * Copyright (c) 2025 Électro L.I.B Daniel C. electro_l.i.b@tinyjoypad.com
 *  https://github.com/phoenixbozo/TinyJoypad/tree/main/TinyJoypad
 *                    https://WWW.TINYJOYPAD.COM
 *          https://sites.google.com/view/arduino-collection
 * Developed with the assistance of Grok, an AI developed by xAI
 *
 * Description:
 * FastTinyDriver is an optimized graphics driver designed to work with 
 * ATtiny85 microcontrollers, particularly for the Tinyjoypad game console. 
 * This file contains the OLED driver code used in games developed for 
 * the ATtiny85. Although it is an integral part of each game code, 
 * FastTinyDriver is also designed to be used in other projects 
 * that require an OLED display based on the SSD1306 controller.
 *
 * This code is based on general knowledge of I2C programming and 
 * standard SSD1306 commands, as specified in the datasheet.
 *
 * **IMPORTANT**: This program is licensed under the GNU General Public License version 3 (GPLv3).
 * You can redistribute and/or modify it under the terms of the GPLv3, 
 * as published by the Free Software Foundation.
 *
 * This license grants you the right to use, modify, and share this software. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. 
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * **IMPORTANT NOTE**: If this code is to be used for purposes other than the Tinyjoypad ATtiny85, 
 * it is imperative to remove the #define TINYJOYPAD_ASM_DRIVER to use the portable version 
 * of FastTinyDriver. Failing to do so may cause issues.
 *
 * for TINY JOYPAD rev2 (attiny85)
 * the code work at 16MHZ internal
 */

#ifndef FASTTINYDRIVER_H
#define FASTTINYDRIVER_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Adresse I2C du SSD1306
#define SSD1306_ADDRESS 0x3C

// Mode d'adressage mémoire (horizontal ou vertical)
//#define SSD1306_MEMORY_ADDRESSING_MODE  0x00  // horizontal
#define SSD1306_MEMORY_ADDRESSING_MODE   0x01  // vertical

// Fonction d’initialisation complète de l’écran OLED pour Tinyjoypad
void TinyOLED_init();

// Fonction de sélection de la page pour l’écran SSD1306
void ssd1306_selectPage(uint8_t Page);

// Fonction de démarrage de la communication I2C (exposée pour usage externe)
void i2c_start(void);

// Fonction d’écriture d’un octet sur le bus I2C (exposée pour usage externe)
void i2c_write(uint8_t data);

// Fonction d’arrêt de la communication I2C (exposée pour usage externe)
void i2c_stop(void);

#endif /* FASTTINYDRIVER_H */
