ZKeyboard
=========

This is the firmware for the ZKeyboard Arduino Micro.

![alt ZKeyboard](https://github.com/jclopes/ZKeyboard/blob/master/img/ZKeyboard-TOP.jpg)

ZKeyboard is a split keyboard inspired by the ErgoDox that it self was inspired by Key64@.
The main changes from ErgoDox concept is to have less keys to keep the fingers from moving too far from the home row.

The electronic components that are part of the ZKeyboard are the same as the ones in ergodox except for the main controller where the Teensy USB Board was replaced by a Arduino Micro.


Acknowledgements
----------------

@sansol For discussing the possible solutions and good suggestions.
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
 - Only three rows of keys to keep the fingers always close to the home row.
 - Seven keys assigned to each of the thumbs.
 - Key positioning to match finger length and avoid extra hand movement and twisting.
 - N-Key rollover compatible.
 - Fully programable.
