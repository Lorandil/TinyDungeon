# TinyDungeon

Just a simple DungeonMaster "clone" for the ATtiny85 with an 128x64 OLED display (especially for the TinyJoypad platform).<br>
Let's see how far we can get!

## The Idea
When I discovered Daniel C's TinyJoypad project I was stunned by all the cool retro like
games Daniel had created. 

I started to play with the code of Tiny invaders and decided to try to make it even a little more fun (check the result here: https://github.com/Lorandil/Tiny-invaders-v4.2).
When I had finished most of my ideas on that project, I thought of a game project of my own.

I always loved games like The Bard's Tale or DungeonMaster in the 80s and early 90s.
Why don't develop something like a 3D dungeon crawler on the TinyJoypad platform?

## Game Features
* 3D graphics (ok - it's pseudo 3D)
* Large dungeon size of 16x16 tiles
* Four different monster types
* Treasure chests
* Teleporters
* Spinners
* Compass
* Doors
* Bars
* Switches
* Sound effects

## Technical Details
It soon became clear, that regarding the limited flash capacity (8kB) of the ATtiny85, a data driven approach was required. All walls, monsters and encounters/events are organized in tables which makes the game easy to extend, yet saving a lot of space.

### Flash Memory Requirements for the Graphics Data
* all walls require ~1600 bytes
* monsters require ~900 bytes
* the status window requires 256 bytes
* the compass requires 20 bytes
* other objects require ~1200 bytes
This sums up to nearly 4000 bytes - meaning half the flash memory is used to store the game's graphics!



## First Screenshots
#### The player has found the compass!
![Oh, I see!](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/compass_found!.png)

#### No trespassing here...
![Tunnel is blocked](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/the_tunnel_is_blocked.png)

#### Hi folks!
![Meet Joey!](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/meet_Joey!.png)

#### Die Scum!
![The Boss](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/the_boss.png)

## List of Objects
* Compass - always points north
* Wooden shield - massively reducing damage taken
* Sword  - increases damage of attacks substantially
* Amulet of True Sight - displayed as an eye, lets the player see through fake walls
* Ring of Orientation - displayed as a ring, lets the screen flash when teleporting or spinning
* Healing Potions - granting additional hit points

## Combat System
The health state of the player and the monsters is persistent, so damaged monsters will stay damaged. <br>

#### Initiative
Some monsters are faster than the player and will attack first.
Others like undead are slower but deadly nonetheless.<br>

#### Attack or Run
If it's the player's turn, the player can chose to attack by pressing the button or run away by moving back.<br>
If the monster survives the attack, it will retaliate immediately.

#### Damage
The damage is determined by a roll of a D8 plus/minus some monster specific value. 
Obviously the damage value is always positive.
The damage is shown in the top center of the screen (enlarged by 2?)

### Rewards on Dead Monsters
Some monsters may leave items...

### Losing the game
The player loses the game, if the hit points drop to 0.<br>
When the game is lost, the game will restart after pressing the button.

### Winning the Game
The player wins the game when reaching the Fountain of Life, gaining the desperately needed remedy for the player's lover.

## Engine Features
* real-time rendering in 96x64 pixels
* real-time bitmap scaling in up to three sizes (full, half, quarter) with a variable threshold for each view distance to optimize the visuals
* all bitmaps have a mask to keep the background from shimmering through
* view distance is up to three tiles (depending on the object)
* convincing movement illusion when walking through tunnels (done by mirroring left and right wall bitmap on every step)
* different sound effects
* some magic items
* easily expandle scripted interactions (monsters, switches, chests, teleporters, spinners)
* extensible design (levels, bitmaps, interactions, ...)
* highly opimized for size (target system is an ATtiny85 with 512 bytes of RAM and 8kB of flash)
* code compiles for ATtiny85 with xled1306 library
* code compiles for Arduino Uno R3, Leonardo, Mega 2560, Zero and many boards more using the Adafruit SSD1306 library (encapsuled in `"tinyJoypadUtils.h"`)
* Screenshot functionality: Dump screen content to serial port as a hexdump
  [only on MCUs with serial port, so not on ATtiny85 ;)]

## Engine Limitations
* some objects don't look good when scaled (even with the variable threshold)
* on-wall objects (switches, doors) aren't rendered correctly when seen from the side -> architectural measures required (e.g. doors need to be set back by at least one field)
* at the moment non-wall objects like monsters, chests or doors are only rendered in front of the player.
* no floor or ceiling for now (mostly because of lack of memory)
* max. dungeon size is 256 tiles

## Current Size
Sketch uses 7762 bytes (94%) of program storage space. Maximum is 8192 bytes (430 bytes left).
Global variables use 326 bytes (63%) of dynamic memory, leaving 186 bytes for local variables. Maximum is 512 bytes.

## License
MIT License
