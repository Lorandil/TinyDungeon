// Just a text file, but Ardiono IDE doesn't like "txt" to be added to the project

#ifdef _HISTORY_

Current size 7104 bytes - 1088 bytes remaining

History and open points list of TinyDungeon

already achieved:
* make walls solid
* copy level from flash to RAM
* store level dimensions in level structure,
  thus enabling arbitrary level sizes
  add information about stairs up and down to the level structure, too
* mirror walls between odd and even cells
* added skeleton and beholder bitmap
* very plain draw function (buggy!) for non-wall-objects
* use solid bit
* add bitmap scaling
* add scripted events (levers switching doors, ...)
* code works on Arduino UNO and MEGA2560 (without sound) too
* enhanced bitmap scaling to work with bitmap heights (in bytes) which are not a power of 2
* cropped the wall bitmaps to the required size saving 960 bytes
* added compass
* added open chest image

next steps:
* add a fountain to restore health
* extend object drawing to full field of view
* add stairs up/down
* add monster(s)
* add treasure

? add floor graphics
? use only one bitmap for all front walls using downscaling <- is this really still necessary, it's just 576 bytes?! 

* ...
* add fun!

goal
* 4 levels(?)
* combat system
* fun
* save to EEPROM?

#endif
