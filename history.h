// Just a text file, but Ardiono IDE doesn't like "txt" to be added to the project

#ifdef _HISTORY_

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


next steps:
* enhance bitmap scaling to work with bitmap heights (in bytes) which are not a power of 2
* extend object drawing to full field of view
* add compass
* add stairs up/down
* add monster(s)
* add treasure
* add floor graphics

* ...
* have fun!

goal
* 4 levels(?)
* combat system
* fun
* save to EEPROM?

#endif
