# TinyDungeon
 Just a simple DungeonMaster "clone". let's see how far we can get!

# The Idea
When I discovered Daniel C's TinyJoypad project I was stunned by all the cool retro like
games Daniel had created. 

I started to play with the code of Tiny invaders and decided to try to make it even a little more fun (check the result here: https://github.com/Lorandil/Tiny-invaders-v4.2).
When I had finished most of my ideas on that project, I thought of a game project of my own.

I always loved games like The Bard's Tale or DungeonMaster in the 80s and early 90s.
Why not something like a 3D dungeon crawler on the TinyJoypad platform?

# Features
* 3D graphics (ok, pseudo 3D)
* Large dungeon size of 16x16 tiles
* Two different monster types
* Treasure chests
* Teleporters
* Spinners
* Compass
* Doors
* Bars
* Switches
* Sound effects

# Screenshots
![Picture](https://github.com/screenshots/meet Joey!.png)

# Open Points
* Still missing ideas for a combat system
* When does the player win?
* When does the player lose (HP <= 0?)
* Are there different weapons?
* Can the player heal?

# Technical Details
* game window resolution is 96x48 pixels
* on-the-fly bitmaps scaling (1x,2x,4x) with variable threshold and view distance
* view distance is up to 3 tiles from
* Bitmaps can have a mask to keep the background from shimmering through
* all interactions are scripted (not hardcoded)
* extensible design (levels, bitmaps, interactions, ...)
* highly optimized code ;)
* code compiles for ATtiny85 with xled1306 library
* code compiles Arduino Uno R3, Arduino Mega 2560 and many boards more using
  the Adafruit SSD1306 library (no sound support yet)
* Screenshot functionality: Dump screen content to serial port as a hexdump
  [only on MCUs with serial port, so not on ATtiny85 ;)]

# Current Size
Sketch uses 7478 bytes (91%) of program storage space. Maximum is 8192 bytes.
Global variables use 342 bytes (66%) of dynamic memory, leaving 170 bytes for local variables. Maximum is 512 bytes.

# License
