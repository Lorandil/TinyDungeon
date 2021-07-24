# TinyDungeon
***
 Just a simple DungeonMaster "clone". let's see how far we can get!

## The Idea
When I discovered Daniel C's TinyJoypad project I was stunned by all the cool retro like
games Daniel had created. 

I started to play with the code of Tiny invaders and decided to try to make it even a little more fun (check the result here: https://github.com/Lorandil/Tiny-invaders-v4.2).
When I had finished most of my ideas on that project, I thought of a game project of my own.

I always loved games like The Bard's Tale or DungeonMaster in the 80s and early 90s.
Why not something like a 3D dungeon crawler on the TinyJoypad platform?

## Features
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

## Combat System

#### Initiative
A die is thrown. If the result is even, the player attacks first, if odd the monster attacks first.

#### Attack or Run
If it's the player's turn, the player can chose to attack by pressing <fire> or run away by moving back.
If the monster survives the attack it will retaliate immediately.
The monster might also hit the player when the player choses to retreat (1 and 2 on D8).

#### Damage
The damage is determined by a roll of a D8 plus/minus some monster specific value. 
Obviously the damage value is always positive.
The damage is shown in the top center of the screen (enlarged by 2?)

## Open Points
* When does the player win?
* When does the player lose (HP <= 0?)
* Are there different weapons?
* Can the player heal?

## Technical Details
* game window resolution is 96x48 pixels
* on-the-fly bitmaps scaling (1x,2x,4x) with variable threshold and view distance
* view distance is up to 3 tiles
* Bitmaps can have a mask to keep the background from shimmering through
* all interactions are scripted (not hardcoded)
* extensible design (levels, bitmaps, interactions, ...)
* highly optimized code ;)
* code compiles for ATtiny85 with xled1306 library
* code compiles Arduino Uno R3, Arduino Mega 2560 and many boards more using
  the Adafruit SSD1306 library (no sound support yet)
* Screenshot functionality: Dump screen content to serial port as a hexdump
  [only on MCUs with serial port, so not on ATtiny85 ;)]

## Current Size
Sketch uses 7720 bytes (94%) of program storage space. Maximum is 8192 bytes.
Global variables use 344 bytes (67%) of dynamic memory, leaving 168 bytes for local variables. Maximum is 512 bytes.

## License
GNU General Public License v3.0
