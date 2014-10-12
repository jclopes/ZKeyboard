/*
  This file implements the functionality to interact with the mcp23018 part of
the keyboard.
*/

#include <Wire.h>

/* Port A are columns and port B are rows */
// Set bitrate of the I2C to 400KHz
// Some say to set this value before calling Wire.begin others say after
// Need to check what is the value of
// TWBR = (some places say to set it to 12 others to 400000L)

/*
Pins reserved for I2C (wire) communication: 2 (SDA), 3 (SCL) on arduino micro
Pins reserved for I2C (wire) communication: A4 (SDA), A5 (SCL) on arduino 2009
*/
#define SDA_PIN 2
#define SCL_PIN 3


#define IODIRA_ADDR 0x00
#define IODIRB_ADDR 0x01
#define GPIOA_ADDR 0x12
#define GPIOB_ADDR 0x13
#define IOCON_ADDR 0x0A
#define GPPUA_ADDR 0x0C
#define GPPUB_ADDR 0x0D

// Left keyboard matrix size
#define NUM_LROWS 5
#define NUM_LCOLS 6

/* Map key position to key ID.
    This is needed because there is no direct transformation from position to
  key id.
 */
const byte lmap_pos2id[] = {
    0,   6,  12, 255, 255,
    1,   7,  13, 255, 255,
    2,   8,  14,  23,  24,
    3,   9,  15,  20,  22,
    4,  10,  16,  19,  21,
    5,  11,  17,  18, 255
};

// Address of the mcp23018
const byte mcp_address = 0x20;


/* Setup the mcp23018 controler and the Wire library */
int mcp_setup() {
  int res = 0;

  // Set I2C communication pins
  pinMode(SDA_PIN, INPUT_PULLUP);
  pinMode(SCL_PIN, INPUT_PULLUP);

  Wire.begin();
  // HACK To set Wire to use 400-kHz Fast-mode (default is 72)
  TWBR = 12;

  // Set port A to outputs floating
  Wire.beginTransmission(mcp_address);
  Wire.write(IODIRA_ADDR);
  Wire.write(0x00); // set all to outputs (open-drain)
  res = Wire.endTransmission();
  if (res != 0) {
    // failed to setup port A
    return res;
  }

  // Set port B to inputs
  Wire.beginTransmission(mcp_address);
  Wire.write(IODIRB_ADDR);
  Wire.write(0xFF); // set all of port B to inputs
  res = Wire.endTransmission();
  if (res != 0) {
    // failed to setup port B
    return res;
  }

  // Set port B to pull-up
  Wire.beginTransmission(mcp_address);
  Wire.write(GPPUB_ADDR);
  Wire.write(0xFF); // set all of port B to pull-up
  res = Wire.endTransmission();
  if (res != 0) {
    // failed to setup port B
    return res;
  }

  // Set BYTE_MODE
  Wire.beginTransmission(mcp_address);
  Wire.write(IOCON_ADDR);
  Wire.write(0x20); // Set byte_mode
  res = Wire.endTransmission();
  if (res != 0) {
    // failed to setup IOCON BYTE_MODE
    return res;
  }

  return 0;
}


/* Reads a column from mcp side of the keyboard.
 Activates col pin on Port A and reads Port B.
 returns the rows that are active.
 */
byte mcp_read_col(byte column) {
  byte row_state = 0;
  byte bitmask = 1 << column;

  // Activate Column
  Wire.beginTransmission(mcp_address);
  Wire.write(GPIOA_ADDR);
  Wire.write(~bitmask);
  Wire.endTransmission();

  // Read one byte from the mcp with the state of the rows.
  Wire.requestFrom((int)mcp_address, 1);
  row_state = Wire.read();
  return row_state;
}


/* Updates the global keyboard state.
 Calls update_state for each key of the left side with the current reading of
 the key state.
 */
void read_left() {
  byte active_rows = 0;
  byte key_pos = 0;
  for (byte i = 0; i < NUM_LCOLS; i++) {
    active_rows = mcp_read_col(i);
    for (byte j = 0; j < NUM_LROWS; j++) {
      bool is_pressed = (1 << j) & (byte)~active_rows;
      update_state(lmap_pos2id[key_pos], is_pressed);
      key_pos++;
    }
  }
}
