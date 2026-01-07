/*
 * FastTinyDriver.cpp
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

#include "FastTinyDriver.h"

#define TINYJOYPAD_ASM_DRIVER // it is imperative to remove the #define TINYJOYPAD_ASM_DRIVER to use the portable version of FastTinyDriver. Failing to do so may cause issues.

// Définition des broches I2C utilisées sur l’ATtiny85
#define SCL_PIN 2 // Broche PB2 pour SCL (horloge I2C)
#define SDA_PIN 0 // Broche PB0 pour SDA (données I2C)

// Choix entre version ASM ou C via une macro de compilation
// Définir TINYJOYPAD_ASM_DRIVER pour utiliser l’implémentation en assembleur
#ifdef TINYJOYPAD_ASM_DRIVER
// Version en assembleur pour une exécution optimisée

// Initialisation des broches I2C
static void i2c_init(void) {
    asm volatile (
        // Configure PB2 (SCL) comme sortie
        "sbi %0, %1\n\t"
        // Configure PB0 (SDA) comme sortie
        "sbi %0, %2\n\t"
        // Active la résistance pull-up sur PB2 (SCL)
        "sbi %3, %1\n\t"
        // Active la résistance pull-up sur PB0 (SDA)
        "sbi %3, %2"
        :
        : "I" (_SFR_IO_ADDR(DDRB)), // Adresse du registre DDRB
          "I" (SCL_PIN),           // Numéro de la broche SCL
          "I" (SDA_PIN),           // Numéro de la broche SDA
          "I" (_SFR_IO_ADDR(PORTB)) // Adresse du registre PORTB
    );
}

// Démarrage de la communication I2C
static void i2c_start(void) {
    asm volatile (
        // Met SDA à l’état haut
        "sbi %0, %1\n\t"
        // Met SCL à l’état haut
        "sbi %0, %2\n\t"
        // Bascule SDA à l’état bas pendant que SCL est haut (condition de démarrage)
        "cbi %0, %1\n\t"
        // Bascule SCL à l’état bas pour commencer la transmission
        "cbi %0, %2"
        :
        : "I" (_SFR_IO_ADDR(PORTB)), // Adresse du registre PORTB
          "I" (SDA_PIN),            // Numéro de la broche SDA
          "I" (SCL_PIN)             // Numéro de la broche SCL
    );
}

// Arrêt de la communication I2C
void i2c_stop(void) {
    asm volatile (
        // Met SDA à l’état bas
        "cbi %0, %1\n\t"
        // Met SCL à l’état haut
        "sbi %0, %2\n\t"
        // Bascule SDA à l’état haut pendant que SCL est haut (condition d’arrêt)
        "sbi %0, %1"
        :
        : "I" (_SFR_IO_ADDR(PORTB)), // Adresse du registre PORTB
          "I" (SDA_PIN),            // Numéro de la broche SDA
          "I" (SCL_PIN)             // Numéro de la broche SCL
    );
}

// Écriture d’un octet sur le bus I2C
void i2c_write(uint8_t data) {
    asm volatile (
        // Initialise un compteur à 8 pour les 8 bits de l’octet
        "ldi r18, 8\n\t"
        // Début de la boucle pour envoyer chaque bit
        "1:\n\t"
        // Met SCL à l’état bas pour préparer l’envoi du bit
        "cbi %1, %2\n\t"
        // Teste si le bit le plus significatif (bit 7) est à 1
        "sbrc %0, 7\n\t"
        // Si oui, met SDA à l’état haut
        "sbi %1, %3\n\t"
        // Teste si le bit 7 est à 0
        "sbrs %0, 7\n\t"
        // Si oui, met SDA à l’état bas
        "cbi %1, %3\n\t"
        // Met SCL à l’état haut pour valider le bit
        "sbi %1, %2\n\t"
        // Décale les bits de data vers la gauche pour le prochain bit
        "lsl %0\n\t"
        // Décrémente le compteur
        "dec r18\n\t"
        // Retourne au début de la boucle si tous les bits ne sont pas envoyés
        "brne 1b\n\t"
        // Gestion de l’acquittement (ACK)
        // Met SCL à l’état bas
        "cbi %1, %2\n\t"
        // Met SDA à l’état haut pour libérer la ligne
        "sbi %1, %3\n\t"
        // Configure SDA comme entrée pour lire l’ACK
        "cbi %4, %3\n\t"
        // Met SCL à l’état haut pour que l’esclave envoie l’ACK
        "sbi %1, %2\n\t"
        // Remet SCL à l’état bas après l’ACK
        "cbi %1, %2\n\t"
        // Reconfigure SDA comme sortie
        "sbi %4, %3\n\t"
        // Force SDA à l’état bas pour la prochaine opération
        "cbi %1, %3"
        : "+r" (data)                // Entrée/sortie : octet à envoyer
        : "I" (_SFR_IO_ADDR(PORTB)), // Adresse du registre PORTB
          "I" (SCL_PIN),            // Numéro de la broche SCL
          "I" (SDA_PIN),            // Numéro de la broche SDA
          "I" (_SFR_IO_ADDR(DDRB))  // Adresse du registre DDRB
        : "r18"                     // Registre temporaire utilisé
    );
}

#else
// Version en C pour une meilleure lisibilité

// Initialisation des broches I2C
static void i2c_init(void) {
    // Configure PB2 (SCL) et PB0 (SDA) comme sorties
    DDRB |= (1 << SCL_PIN) | (1 << SDA_PIN);
    // Active les résistances pull-up sur PB2 et PB0
    PORTB |= (1 << SCL_PIN) | (1 << SDA_PIN);
}

// Démarrage de la communication I2C
static void i2c_start(void) {
    // Met SDA à l’état haut
    PORTB |= (1 << SDA_PIN);
    // Met SCL à l’état haut
    PORTB |= (1 << SCL_PIN);
    // Bascule SDA à l’état bas pour signaler le début
    PORTB &= ~(1 << SDA_PIN);
    // Bascule SCL à l’état bas pour commencer la transmission
    PORTB &= ~(1 << SCL_PIN);
}

// Arrêt de la communication I2C
void i2c_stop(void) {
    // Met SDA à l’état bas
    PORTB &= ~(1 << SDA_PIN);
    // Met SCL à l’état haut
    PORTB |= (1 << SCL_PIN);
    // Bascule SDA à l’état haut pour signaler la fin
    PORTB |= (1 << SDA_PIN);
}

// Écriture d’un octet sur le bus I2C
void i2c_write(uint8_t data) {
    // Boucle pour envoyer les 8 bits de l’octet
    for (uint8_t i = 0; i < 8; i++) {
        // Met SCL à l’état bas pour préparer l’envoi
        PORTB &= ~(1 << SCL_PIN);
        // Vérifie le bit le plus significatif de l’octet
        if (data & 0x80) {
            // Si bit est 1, met SDA à l’état haut
            PORTB |= (1 << SDA_PIN);
        } else {
            // Si bit est 0, met SDA à l’état bas
            PORTB &= ~(1 << SDA_PIN);
        }
        // Met SCL à l’état haut pour valider le bit
        PORTB |= (1 << SCL_PIN);
        // Décale l’octet pour préparer le prochain bit
        data <<= 1;
    }
    // Gestion de l’acquittement (ACK)
    // Met SCL à l’état bas
    PORTB &= ~(1 << SCL_PIN);
    // Met SDA à l’état haut pour libérer la ligne
    PORTB |= (1 << SDA_PIN);
    // Configure SDA comme entrée pour lire l’ACK
    DDRB &= ~(1 << SDA_PIN);
    // Met SCL à l’état haut pour recevoir l’ACK
    PORTB |= (1 << SCL_PIN);
    // Remet SCL à l’état bas après l’ACK
    PORTB &= ~(1 << SCL_PIN);
    // Reconfigure SDA comme sortie
    DDRB |= (1 << SDA_PIN);
    // Force SDA à l’état bas pour la prochaine opération
    PORTB &= ~(1 << SDA_PIN);
}

#endif

// Fonctions communes aux deux versions (ASM et C)

// Sélection de la page pour l’écran SSD1306
void ssd1306_selectPage(uint8_t Page) {
    // Démarre une transmission I2C
    i2c_start();
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    i2c_write(SSD1306_ADDRESS << 1);
    // Envoie l’octet de contrôle pour indiquer une commande
    i2c_write(0x00);
    // Envoie la commande pour sélectionner la page (0 à 7)
    i2c_write(0xB0 | (Page & 0x07));
    // Définit la colonne basse à 0
    i2c_write(0x00);
    // Définit la colonne haute à 0
    i2c_write(0x10);
    // Termine la transmission des commandes
    i2c_stop();

    // Démarre une nouvelle transmission pour les données
    i2c_start();
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    i2c_write(SSD1306_ADDRESS << 1);
    // Envoie l’octet de contrôle pour indiquer des données
    i2c_write(0x40);
}

#if 0
// Initialisation de l’écran SSD1306
static void ssd1306_init(const uint8_t mode) {
    // Démarre une transmission I2C
    i2c_start();
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    i2c_write(SSD1306_ADDRESS << 1);
    // Envoie l’octet de contrôle pour indiquer des commandes
    i2c_write(0x00);
    // Éteint l’écran
    i2c_write(0xAE);
    // Définit le rapport de division d’horloge (fréquence)
    i2c_write(0xD5); i2c_write(0x80);
    // Définit le multiplexage à 64 lignes (pour 128x64)
    i2c_write(0xA8); i2c_write(0x3F);
    // Définit le décalage d’affichage à 0
    i2c_write(0xD3); i2c_write(0x00);
    // Définit la ligne de départ à 0
    i2c_write(0x40);
    // Active la pompe de charge interne
    i2c_write(0x8D); i2c_write(0x14);
    // Inverse le mappage des segments (orientation)
    i2c_write(0xA1);
    // Inverse la direction de balayage des lignes COM
    i2c_write(0xC8);
    // Configure les broches COM pour un écran 128x64
    i2c_write(0xDA); i2c_write(0x12);
    // Définit le contraste de l’écran
    i2c_write(0x81); i2c_write(0xCF);
    // Définit la période de précharge
    i2c_write(0xD9); i2c_write(0xF1);
    // Définit la tension VCOMH
    i2c_write(0xDB); i2c_write(0x40);
    // Définit le mode de mémoire
    i2c_write(0x20); i2c_write(SSD1306_MEMORY_ADDRESSING_MODE);
    // Définit les colonnes utilisées.
    i2c_write(0x21); i2c_write(0x00); i2c_write(0x7f);
    // Allume l’écran
    i2c_write(0xAF);
    // Termine la transmission
    i2c_stop();
}
#endif

const unsigned char ssd1306_init_sequence_commands[] PROGMEM =
{
    // Envoie l’adresse de l’esclave SSD1306 avec bit d’écriture (0)
    SSD1306_ADDRESS << 1,
    // Envoie l’octet de contrôle pour indiquer des commandes
    0x00,
    // Éteint l’écran
    0xAE,
    // Définit le rapport de division d’horloge (fréquence)
    0xD5, 0x80,
    // Définit le multiplexage à 64 lignes (pour 128x64)
    0xA8, 0x3F,
    // Définit le décalage d’affichage à 0
    0xD3, 0x00,
    // Définit la ligne de départ à 0
    0x40,
    // Active la pompe de charge interne
    0x8D, 0x14,
    // Inverse le mappage des segments (orientation)
    0xA1,
    // Inverse la direction de balayage des lignes COM
    0xC8,
    // Configure les broches COM pour un écran 128x64
    0xDA, 0x12,
    // Définit le contraste de l’écran
    0x81, 0xCF,
    // Définit la période de précharge
    0xD9, 0xF1,
    // Définit la tension VCOMH
    0xDB, 0x40,
    // Définit le mode de mémoire (horizontal ou vertical)
    0x20, SSD1306_MEMORY_ADDRESSING_MODE,
    // Définit les colonnes utilisées.
    0x21, 0x00, 0x7f,
    // Allume l’écran
    0xAF,
};

// Initialisation de l’écran SSD1306
static void ssd1306_init() {
    // Démarre une transmission I2C
    i2c_start();

    for ( uint8_t n = 0; n < sizeof(ssd1306_init_sequence_commands); n++ )
    {
        // Envoie chaque octet de la séquence d’initialisation
        i2c_write( pgm_read_byte( ssd1306_init_sequence_commands + n ) );
    }

    // Termine la transmission
    i2c_stop();
}

// Initialisation complète pour TinyOLED
void TinyOLED_init() {
    // Configure les broches I2C
    i2c_init();
    // Attend 10 ms pour stabiliser l’alimentation
    _delay_ms(10);
    // Initialise les paramètres de l’écran SSD1306
    ssd1306_init();
    // Attend 10 ms supplémentaires pour garantir l’initialisation
    _delay_ms(10);
}
