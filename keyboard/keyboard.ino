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
// The keyboard layout consists of 3 layers.
#define NUM_LAYERS 3

// keyboard is an array of keys
Key keyboard[NUM_KEYS];

// Which layer is currently in use.
byte activeLayer = 0;
// Lock layout to the active layer
bool lockLayer = false;
// Layer mapping. A layer maps a Key->id to a scan code.
byte layers[NUM_LAYERS][NUM_KEYS];

// the setup routine
void setup() {

  // Serial.begin(9600);
  // while (!Serial) {
  //   delay(10); // wait for serial port to connect. Needed for Leonardo only
  // }
  // Serial.println("Testing Keyboard");

  // Initialize the mcp23018. Start the wire system.
  mcp_setup();  // join the i2c bus

  // Initialize the arduino micro. Setup the pins.
  micro_setup();

  // initialize the layers
  layers_setup();

  // initialize the keyboard global
  reset_keyboard();

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
        if (is_layerkey(scancode)) {
          layer_press(scancode);
        }
        else {
          Keyboard.press_sc(scancode);
          Serial.print("pressed -> ");
          Serial.println(k_id);
        }
      }
      else {
        if (is_layerkey(scancode)) {
          layer_release(scancode);
        }
        else {
          Keyboard.release_sc(scancode);
          Serial.print("relessed -> ");
          Serial.println(k_id);
        }
      }
      k->changed = false;
    }
  }
  // TODO: find an adequate value for the delay
  // We want to read at least 20 key presses per second (20Hz)
  delay(10);
}
