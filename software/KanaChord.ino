/* KanaChord.ino */

#include <Keyboard.h>
#include "kbd_mgt.h"
#define MODE_PIN_1 17
#define MODE_PIN_2 18

void setup() {
  // Set up inputs pins with internal pullups for USB keyboard macro
  // mode selection.  Switch has one end tied to ground to pull low.
  pinMode(MODE_PIN_1, INPUT_PULLUP);
  pinMode(MODE_PIN_2, INPUT_PULLUP);
  // Initialize the USB keyboard emulation.
  Keyboard.begin();
  kbd_setup();
}

void loop() {
  uint16_t kanaValue = kbd_process();

  if (kanaValue != 0x0000) {
    // Convert Unicode value to ASCII by first isolating each nybble.
    // Add ACSII '0' (48) if nybble less than 10, otherwise add ten
    // less than ASCII 'a' (97).
    uint8_t n0 = uint8_t (kanaValue >> 12);
    n0 = n0 < 10 ? 48 + n0 : 87 + n0;
    uint8_t n1 = uint8_t ((kanaValue >> 8) & 0x000f);
    n1 = n1 < 10 ? 48 + n1 : 87 + n1;
    uint8_t n2 = uint8_t ((kanaValue >> 4) & 0x000f);
    n2 = n2 < 10 ? 48 + n2 : 87 + n2;
    uint8_t n3 = uint8_t (kanaValue & 0x000f);
    n3 = n3 < 10 ? 48 + n3 : 87 + n3;

    int pin1 = digitalRead(MODE_PIN_1);
    int pin2 = digitalRead(MODE_PIN_2);
    if (pin1 == HIGH && pin2 == HIGH) {
      // Linux Unicode entry sequence.
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(20);
      Keyboard.press(KEY_LEFT_CTRL);
      delay(20);
      Keyboard.write('u');
      Keyboard.write(n0);
      Keyboard.write(n1);
      Keyboard.write(n2);
      Keyboard.write(n3);
      Keyboard.releaseAll();
      delay(20);
    } else if (pin1 == HIGH && pin2 == LOW) {
      // Microsoft Windows Unicode entry sequence.
      Keyboard.write(n0);
      Keyboard.write(n1);
      Keyboard.write(n2);
      Keyboard.write(n3);
      Keyboard.press(KEY_LEFT_ALT);
      delay(20);
      Keyboard.press('x');
      delay(20);
      Keyboard.releaseAll();
      delay(20);
    } else if (pin1 == LOW && pin2 == HIGH) {
      // MacOS Unicode entry sequence.
      Keyboard.press(KEY_LEFT_ALT);
      delay(20);
      Keyboard.write(n0);
      Keyboard.write(n1);
      Keyboard.write(n2);
      Keyboard.write(n3);
      Keyboard.releaseAll();
      delay(20);
    }
  }
}
