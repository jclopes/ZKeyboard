/**
 * Assigns a scancode to each key for each layer.
 *   The special layer keys won't emit scancodes, instead they will be used to
 * modify the global variable 'active_layer'.
 *   Scancodes from '1' to '3' are reserved for layerkeys.
 */

#define LAYER_BT_1  1
#define LAYER_BT_2  2
#define LAYER_BT_LK 3

bool is_layerkey(byte keycode) {
  return keycode < 4 && keycode > 0;
}

void layer_press(byte keycode) {
  switch (keycode) {
    case LAYER_BT_LK:
      if (lockLayer) {
        lockLayer = false;
        activeLayer = 0;
      } else {
          lockLayer = true;
      }
      break;
    case LAYER_BT_1:
      lockLayer = false;
      activeLayer = 1;
      break;
    case LAYER_BT_2:
      lockLayer = false;
      activeLayer = 2;
      break;
  }
}

void layer_release(byte keycode) {
  switch (keycode) {
    case LAYER_BT_LK:
      break;
    case LAYER_BT_1:
      if(!lockLayer) {
        activeLayer = 0;
      }
      break;
    case LAYER_BT_2:
      if(!lockLayer) {
        activeLayer = 0;
      }
      break;
  }
}

// initialize the layers
void layers_setup() {
  // Layer 0 (base layer)
  layers[0][0] = 47;    // [{
  layers[0][1] = 20;    // Q
  layers[0][2] = 26;    // W
  layers[0][3] = 8;     // E
  layers[0][4] = 21;    // R
  layers[0][5] = 23;    // T
  layers[0][6] = 225;   // LSHIFT
  layers[0][7] = 4;     // A
  layers[0][8] = 22;    // S
  layers[0][9] = 7;     // D
  layers[0][10] = 9;    // F
  layers[0][11] = 10;   // G
  layers[0][12] = 224;  // LCTRL
  layers[0][13] = 29;   // Z
  layers[0][14] = 27;   // X
  layers[0][15] = 6;    // C
  layers[0][16] = 25;   // V
  layers[0][17] = 5;    // B
  layers[0][18] = 40;   // ENTER
  layers[0][19] = 76;   // DEL
  layers[0][20] = 57;   // CAPSLOCK
  layers[0][21] = 1;    // LAYER 1 (doesn't send a scan code)
  layers[0][22] = 43;   // TAB
  layers[0][23] = 226;  // LALT
  layers[0][24] = 227;  // LGUI

  layers[0][25] = 28;   // Y
  layers[0][26] = 24;   // U
  layers[0][27] = 12;   // I
  layers[0][28] = 18;   // O
  layers[0][29] = 19;   // P
  layers[0][30] = 48;   // ]}
  layers[0][31] = 11;   // H
  layers[0][32] = 13;   // J
  layers[0][33] = 14;   // K
  layers[0][34] = 15;   // L
  layers[0][35] = 52;   // '"
  layers[0][36] = 229;  // RSHIFT
  layers[0][37] = 17;   // N
  layers[0][38] = 16;   // M
  layers[0][39] = 51;   // ;:
  layers[0][40] = 54;   // ,<
  layers[0][41] = 55;   // .>
  layers[0][42] = 228;  // RCTRL
  layers[0][43] = 41;   // ESC
  layers[0][44] = 42;   // BSPACE
  layers[0][45] = 40;   // ENTER
  layers[0][46] = 230;  // RALT
  layers[0][47] = 44;   // SPACE
  layers[0][48] = 2;    // LAYER 2 (doesn't send a scan code)
  layers[0][49] = 231;  // RGUI

  // Layer 1
  layers[1][0] = 47;    // [{
  layers[1][1] = 0;     //
  layers[1][2] = 0;     //
  layers[1][3] = 82;    // UP
  layers[1][4] = 75;    // PGUP
  layers[1][5] = 0;     //
  layers[1][6] = 225;   // LSHIFT
  layers[1][7] = 74;    // HOME
  layers[1][8] = 80;    // LEFT
  layers[1][9] = 81;    // DOWN
  layers[1][10] = 79;   // RIGHT
  layers[1][11] = 77;   // END
  layers[1][12] = 224;  // LCTRL
  layers[1][13] = 53;   // `~
  layers[1][14] = 45;   // -_
  layers[1][15] = 0;    //
  layers[1][16] = 78;   // PGDOWN
  layers[1][17] = 0;    //
  layers[1][18] = 40;   // ENTER
  layers[1][19] = 76;   // DEL
  layers[1][20] = 57;   // CAPSLOCK
  layers[1][21] = 1;    // LAYER 1 (doesn't send a scan code)
  layers[1][22] = 43;   // TAB
  layers[1][23] = 226;  // LALT
  layers[1][24] = 227;  // LGUI

  layers[1][25] = 46;   // =+
  layers[1][26] = 30;   // 1
  layers[1][27] = 31;   // 2
  layers[1][28] = 32;   // 3
  layers[1][29] = 33;   // 4
  layers[1][30] = 48;   // ]
  layers[1][31] = 56;   // /?
  layers[1][32] = 34;   // 5
  layers[1][33] = 35;   // 6
  layers[1][34] = 36;   // 7
  layers[1][35] = 37;   // 8
  layers[1][36] = 229;  // RSHIFT
  layers[1][37] = 49;   // \|
  layers[1][38] = 38;   // 9
  layers[1][39] = 39;   // 0
  layers[1][40] = 54;   // ,
  layers[1][41] = 55;   // .
  layers[1][42] = 228;  // RCTRL
  layers[1][43] = 41;   // ESC
  layers[1][44] = 42;   // BSPACE
  layers[1][45] = 40;   // ENTER
  layers[1][46] = 230;  // RALT
  layers[1][47] = 44;   // SPACE
  layers[1][48] = 3;    // LAYER LOCK (doesn't send a scan code)
  layers[1][49] = 231;  // RGUI

  // Layer 2
  layers[2][0] = 47;    // [{
  layers[2][1] = 102;   // POWER
  layers[2][2] = 0;     //
  layers[2][3] = 0;     //
  layers[2][4] = 0;     //
  layers[2][5] = 128;   // VOL+
  layers[2][6] = 225;   // LSHIFT
  layers[2][7] = 0;     //
  layers[2][8] = 105;   // BRIGHT-
  layers[2][9] = 106;   // BRIGHT+
  layers[2][10] = 0;    //
  layers[2][11] = 129;  // VOL-
  layers[2][12] = 224;  // LCTRL
  layers[2][13] = 0;    //
  layers[2][14] = 0;    //
  layers[2][15] = 0;    //
  layers[2][16] = 0;    //
  layers[2][17] = 127;  // MUTE
  layers[2][18] = 40;   // ENTER
  layers[2][19] = 76;   // DEL
  layers[2][20] = 57;   // CAPSLOCK
  layers[2][21] = 3;    // LAYER LOCK (doesn't send a scan code)
  layers[2][22] = 43;   // TAB
  layers[2][23] = 226;  // LALT
  layers[2][24] = 227;  // LGUI

  layers[2][25] = 0;    //
  layers[2][26] = 58;   // F1
  layers[2][27] = 59;   // F2
  layers[2][28] = 60;   // F3
  layers[2][29] = 61;   // F4
  layers[2][30] = 48;   // ]
  layers[2][31] = 0;    //
  layers[2][32] = 62;   // F5
  layers[2][33] = 63;   // F6
  layers[2][34] = 64;   // F7
  layers[2][35] = 65;   // F8
  layers[2][36] = 229;  // RSHIFT
  layers[2][37] = 0;    //
  layers[2][38] = 66;   // F9
  layers[2][39] = 67;   // F10
  layers[2][40] = 68;   // F11
  layers[2][41] = 69;   // F12
  layers[2][42] = 228;  // RCTRL
  layers[2][43] = 41;   // ESC
  layers[2][44] = 42;   // BSPACE
  layers[2][45] = 40;   // ENTER
  layers[2][46] = 230;  // RALT
  layers[2][47] = 44;   // SPACE
  layers[2][48] = 2;    // LAYER 2 (doesn't send a scan code)
  layers[2][49] = 231;  // RGUI
}
