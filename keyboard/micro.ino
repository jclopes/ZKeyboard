/* This file implements the functionality of arduino keyboard side */

// The keyboard is a matrix of buttons.
// The matrix is composed by row pins set as input and
// column pins set as output.
#define NUM_RROWS 5
#define NUM_RCOLS 6

/* Map key position to key ID.
    This is needed because there is no direct transformation from position to
  key id.
 */
// TODO: fix the mapping according to the circuit schema.
const byte rmap_pos2id[] = {
   25,  31,  37, 255, 255,
   26,  32,  38, 255, 255,
   27,  33,  39,  48,  49,
   28,  34,  40,  45,  47,
   29,  35,  41,  44,  46,
   30,  36,  42,  43, 255
};

/* Which pins will be rows and which will be columns */
int rowPins[NUM_RROWS] = {A0, A1, A2, A3, A4};
int colPins[NUM_RCOLS] = {6, 7, 8, 9, 10, 11};


void micro_setup() {
  setup_rowPins();
  setup_colPins();
}


/* Set row pins as input_pullup (HIGH) */
void setup_rowPins() {
  for(int i=0; i < NUM_RROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
}


/* Set column pins as input (floating) */
void setup_colPins() {
  for(int i=0; i < NUM_RCOLS; i++) {
    pinMode(colPins[i], INPUT);
  }
}


/* Updates the global keyboard state.
 Calls update_state for each key of the right side with the current reading of
 the key state.
 */
void read_right() {
  byte key_pos = 0;
  for (byte j = 0; j < NUM_RCOLS; j++){
    // Drain power from column pin
    pinMode(colPins[j], OUTPUT);
    digitalWrite(colPins[j], LOW);

    // Read row pins
    for (byte i = 0; i < NUM_RROWS; i++){
      bool is_pressed = (digitalRead(rowPins[i]) == LOW);
      update_state(rmap_pos2id[key_pos], is_pressed);
      key_pos++;
    }

    // Reset column pin
    pinMode(colPins[j], INPUT);
  }
}
