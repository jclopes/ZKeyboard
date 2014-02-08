ZKeyboard
=========

This repo contains the ZKeyboard firmware for the Arduino Micro.

ZKeyboard is a split keyboard inspired by the ErgoDox that it self was inspired by Key64@.
The main changes from ErgoDox concept is to have less keys to keep the fingers from moving too far from the home row.

The components that are part of the ZKeyboard are the same as the ones in ergodox except for the main controller. ZKeyboard uses a Arduino Micro.


Acknowledgements
----------------

All involved in building the ergodox and making everything accessible to everyone (http://ergodox.org).
Key64@ (http://www.key64.org)


Firmware Features
-----------------

 - Key layout Layered system with 3 layers.
 - Key debounce.
 - 6-key rollover (limited by the USB Human Interface Device protocol).
 - Uses I2C communication with IO-Expander (mcp23018).


Keyboard Features
-----------------

 - Split keyboard with free angle positioning.
 - Three rows only to keep fingers from moving away from home row.
 - Multiple keys assigned to the thumbs.
 - Key positioning to match finger length and avoid extra hand movement.
 - N-Key rollover compatible.
 - Multi-layered key layout.
 - Fully programable.
