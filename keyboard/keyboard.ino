/*
 * ZKeyboard
 * Firmeware for a arduino micro and mcp23018 to work as a keyboard controller.
 */


/*
  How do the two parts of the keyboard connect?
  =============================================
    On the left side there is a mcp23018 controller and on the right side
  there is a arduino micro.
    The arduino communicates with the mcp23018 using the I2C protocol (Wire).
    The mcp23018 address is set to 0x20 by connecting all address pins
  (A0, A1, A2) to the ground.

  How does the controler detect a key pressed?
  ============================================
    Each key switch is connected to a row pin and a column pin in a matrix
  (see key matrix).
    On the arduino the 'row_pins' are set as INPUT_PULLUP, this makes them
  report HIGH state when not connected to the ground.
    The 'column_pins' are set as INPUT, this makes them not interfer with the
  circuit.
    To check if a key is pressed we set the column pin to OUTPUT and
  LOW. If a key is pressed, it will create a connection between a row pin and
  the column pin. Since the column pin is now set to OUTPUT LOW it will drain
  the power from the row pin making it read LOW.
 */

// Number of consecutive reads before we consider a key as changed state
#define MAX_BOUNCE 3

// The "Key" struct keeps the current status of a key.
typedef struct {
  byte id;           // identifies the key
  boolean changed;   // did the key change state?
  boolean pressed;   // key state is pressed or not pressed
  byte bounce;       // count how many times the key is bouncing
} Key;

// There are 50 keys on the keyboard.
#define NUM_KEYS 50
// keyboard is an array of keys
Key keyboard[NUM_KEYS];

// A layer maps a Key->id to a scan code.
byte activeLayer = 0;
// TODO: Add two more layers. For now there will be only one layer available.
byte layers[1][NUM_KEYS];


// the setup routine
void setup() {

  Serial.begin(9600);
  while (!Serial) {
    delay(10); // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Testing Keyboard");

  // Initialize the mcp23018. Start the wire system.
  mcp_setup();  // join the i2c bus

  // Initialize the arduino micro. Setup the pins.
  micro_setup();

  // initialize the keyboard global
  reset_keyboard();

  // initialize the layers
  // TODO: Move all layer related code to a layers.ino file
  layers[0][0] = 47;    // [
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
  layers[0][18] = 0;    // LAYER 1 (doesn't send a scan code)
  layers[0][19] = 41;   // ESC
  layers[0][20] = 57;   // CAPSLOCK
  layers[0][21] = 42;   // BSPACE
  layers[0][22] = 76;   // DEL
  layers[0][23] = 226;  // LALT
  layers[0][24] = 227;  // LGUI

  layers[0][25] = 28;   // Y
  layers[0][26] = 24;   // U
  layers[0][27] = 11;   // H
  layers[0][28] = 13;   // J
  layers[0][29] = 4;
  layers[0][30] = 8;
  layers[0][31] = 12;
  layers[0][32] = 18;
  layers[0][33] = 4;
  layers[0][34] = 8;
  layers[0][35] = 12;
  layers[0][36] = 18;
  layers[0][37] = 4;
  layers[0][38] = 8;
  layers[0][39] = 12;
  layers[0][40] = 18;
  layers[0][41] = 4;
  layers[0][42] = 8;
  layers[0][43] = 12;
  layers[0][44] = 18;
  layers[0][45] = 18;
  layers[0][46] = 4;
  layers[0][47] = 8;
  layers[0][48] = 12;
  layers[0][49] = 18;

  // initialize the keyboard lib.
  Keyboard.end();         // Disable keyboard emulation
  Keyboard.begin();       // Enable keyboard emulation
  Keyboard.releaseAll();  // reset all keys
}


/* Reset keyboard state */
void reset_keyboard() {
  Key *k;
  for (byte i = 0; i < NUM_KEYS; ++i) {
    k = &keyboard[i];
    k->changed = false;
    k->pressed = false;
    k->bounce = 0;
  }
}


// updates the state of a key
void update_state(byte key_id, boolean is_pressed) {
  if (key_id >= NUM_KEYS) {
    return;
  }
  Key *key = &keyboard[key_id];
  if (key->pressed != is_pressed) {
    key->bounce += 1;
    Serial.print("Bouncing ");
    Serial.print(key->bounce);
    Serial.print(" key ");
    Serial.println(key_id);
  }
  else {
    key->bounce = 0;
  }

  if (key->bounce > MAX_BOUNCE) {
    Serial.print("Changed ");
    Serial.println(key_id);
    key->changed = true;
    key->pressed = is_pressed;
  }
}


// The Main loop that will keep reading the keys
void loop() {
  // read state of the pins and update the 'keyboard' global
  read_left();
  read_right();

  // go through all keys and send the proper event
  for (int k_id = 0; k_id < NUM_KEYS; k_id++) {
    Key *k = &keyboard[k_id];
    if (k->changed) {
      byte scancode = layers[activeLayer][k_id];
      if (k->pressed) {
        // TODO: Layer check
        // if (it's a layer key) update layers
        // else {
          Keyboard.press_sc(scancode);
      }
      else {
        // TODO: Layer check
        // if (it's a layer key) update layers
        // else {
          Keyboard.release_sc(scancode);
      }
      k->changed = false;
    }
  }
  // TODO: find an adequate value for the delay
  // We want to read at least 20 key presses per second (20Hz)
  delay(10);
}
