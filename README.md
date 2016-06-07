ZKeyboard
=========

This repo is the home of the ZKeyboard Arduino Micro firmware.

![alt text](https://github.com/jclopes/ZKeyboard/blob/master/img/ZKeyboard-TOP.jpg "ZKeyboard Top View")

ZKeyboard is a split keyboard inspired by the ErgoDox that it self was inspired by Key64@.
The main changes from ErgoDox concept is that the ZKeyboard has less keys to keep the fingers from moving too far from the home row.

The electronic components that are part of the ZKeyboard are the same as the ones in ergodox except for the main controller where the Teensy USB Board was replaced by a Arduino Micro.


Acknowledgements
----------------

@sansol for discussing the possible solutions and good suggestions for the design of the keyboard.
All involved in building the ergodox and making everything accessible to everyone (http://ergodox.org).
Key64@ (http://www.key64.org).


Firmware Features
-----------------

 - Key layout Layered system with 3 layers.
 - Key debounce.
 - 6-key rollover (limited by the USB Human Interface Device protocol).
 - Uses I2C communication with IO-Expander (mcp23018).


Keyboard Features
-----------------

 - Split keyboard with free angle positioning.
 - Only 50 keys (25 on each side).
 - Only three rows of keys to keep the fingers always close to the home row.
 - Only 6 columns of keys so that only the index and pinky fingers move between two columns.
 - Seven keys assigned to each of the thumbs to maximize the use of the strongest finger.
 - Key positioning to match finger length and avoid extra hand movement and wrist twisting.
 - N-Key rollover compatible.
 - Fully programable.


Future
------

 - Support for all media keys.
 - Control mouse pointer with keyboard.
 - World domination...
