Sven's collected ATTINY85 C(++) code optimization tips for Arduino IDE

* The AVR only supports shifting left and right by one bit, so
  constructs like ( 1 << n ) are quite expensive because they require
  a loop.

* Don't use pinMode() command, better write directly to the control registers.
  This easily saves 100 bytes of flash!
