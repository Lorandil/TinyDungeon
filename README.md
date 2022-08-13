# TinyDungeon

Just a simple DungeonMaster "clone" for the ATtiny85 with an 128x64 OLED display (especially for the TinyJoypad platform).<br>
Let's see how far we can get!

## The Idea
When I discovered Daniel C's TinyJoypad project I was stunned by all the cool retro like
games Daniel had created. 

I started to play with the code of Tiny invaders and decided to try to make it even a little more fun (check the result here: https://github.com/Lorandil/Tiny-invaders-v4.2).
When I had finished most of my ideas on that project, I thought of a game project of my own.

I always loved games like The Bard's Tale or DungeonMaster in the 80s and early 90s.
Why not something like a 3D dungeon crawler on the TinyJoypad platform?

## Game Features
* 3D graphics (ok, pseudo 3D)
* Large dungeon size of 16x16 tiles
* Three different monster types
* Treasure chests
* Teleporters
* Spinners
* Compass
* Doors
* Bars
* Switches
* Sound effects

## First Screenshots
#### The player has found the compass!
![Oh, I see!](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/compass_found!.png)

#### No trespassing here...
![Tunnel is blocked](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/the_tunnel_is_blocked.png)

#### Hi folks!
![Meet Joey!](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/meet_Joey!.png)

#### Die Scum!
![The Boss](https://github.com/Lorandil/TinyDungeon/blob/main/screenshots/the_boss.png)

## Magic Objects
* The Compass (visible as a compass)
* Amulet of True Sight (visible as an eye, removes fake walls)
* Ring of Orientation (lets the screen flash when teleporting or spinning)
* Healing Potions (granting additional hitpoints)
* The Armor of Faith (massively reducing damage taken)
* The Glass Sword (killing every enemy with the first blow, then breaking)

## Combat System

#### Initiative
A special D8 is thrown (ranging from 0..7). If the result is even, the player attacks first, if odd the monster attacks first.
Might use free running timer as a random source instead...

#### Attack or Run
If it's the player's turn, the player can chose to attack by pressing the fire button or run away by moving back.
If the monster survives the attack it will retaliate immediately.
The monster might also hit the player when the player choses to retreat (0 and 1 on D8).

#### Damage
The damage is determined by a roll of a D8 plus/minus some monster specific value. 
Obviously the damage value is always positive.
The damage is shown in the top center of the screen (enlarged by 2?)

### Rewards on Dead Monsters
Some monsters could leave a chest.

### Monster Management
The state of the monsters should be persistent, so damaged monsters should stay damaged (if possible).
* How is the mapping between the dungeon cells and the monster data?
* Perhaps an index is stored with the monster type in the dungeon
* The monster states need to be held in RAM at all times (perhaps EEPROM if code is not too expensive - 'EEPROM.write()' costs 36 bytes, 'EEPROM.update()' consts 62 bytes)

### Losing the game
The player loses the game, if the hit points fall to 0 or below (use 'int8_t' for hit points!).<br>
If the game is lost, the game will restart after a short delay.
If flash permits, there might be a sound or a flash effect.

### Winning the Game
The player wins the game when... well yes - when does the player win?<br>
What happens when the player wins?

## Other Open Points
* Are there different weapons? - nope!
* Can the player heal? - perhaps ;)

## Engine Features
* realtime rendering in 96x64 pixels
* realtime bitmap scaling in up to three sizes (full, half, quarter) with a variable threshold for each view distance to optimize the visuals
* all bitmaps have a mask to keep the background from shimmering through
* view distance is up to three tiles (depending on the object)
* believable movement illusion when walking through tunnels (done by mirroring left and right wall bitmap on every step)
* different sound effects
* some magic items
* easily expandle scripted interactions (monsters, switches, chests, teleporters, spinners)
* extensible design (levels, bitmaps, interactions, ...)
* highly opimized for size (target system is an ATtiny85 with 512 bytes of RAM and 8kB of flash)
* code compiles for ATtiny85 with xled1306 library
* code compiles for Arduino Uno R3, Arduino Mega 2560 and many boards more using the Adafruit SSD1306 library (encapsuled in `"tinyJoypadUtils.h"`)
* Screenshot functionality: Dump screen content to serial port as a hexdump
  [only on MCUs with serial port, so not on ATtiny85 ;)]

## Engine Limitations
* some objects don't look good when scaled (even with the variable threshold)
* on-wall objects (switches, doors) aren't rendered correctly when seen from the side -> architectual measures required (e.g. doors need to be set back by at least one field)
* at the moment non-wall objects like monsters, chests or doors are only rendered in front of the player.
* no floor or ceiling for now (mostly because of lack of memory)
* max. dungeon size is 256 tiles

## Current Size
Sketch uses 7868 bytes (96%) of program storage space. Maximum is 8192 bytes (324 bytes left).
Global variables use 302 bytes (58%) of dynamic memory, leaving 210 bytes for local variables. Maximum is 512 bytes.

## License
GNU General Public License v3.0
