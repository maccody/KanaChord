/* kbd_mgt.cpp */

#include <Arduino.h>

#include "Keypad2040.h"

#include <Adafruit_NeoPixel.h>
#include "kana.h"
#include "kbd_mgt.h"

/*
 * The Adafruit Neokey board, which has five rows and six columns,
 * is broken between the third and fourth rows and set up as a
 * keyboard with three rows and twelve columns.  Note that the
 * left-most six columns only has two rows.
*/
#define ROWS 3
#define COLS 12
// Key groupings are differentiated by the value of the
// most-significant nybble.
#define CONSO_KEY 0
#define SHIFT_KEY 1
#define VOWEL_KEY 2
#define SPECL_KEY 3
/*
 * Rather than containing ASCII characters, the key array contains
 * codes for each key group.  The most significant nybble contains
 * the key group:
 * 0x0 - Consonant keys
 * 0x1 - Shift keys
 * 0x2 - Vowel keys
 * 0x3 - Special keys
 * 
 * The least sigificant nybble contains the indexing for the key group:
 * Consonant keys - Index is row of table.  Note: index of 0 implies vowels.
 * Shift keys - Index values: 0 = none, 1 = ten-ten, 2 = maru, 4 = chiisai.
 * Vowel keys - Index is column of table.
 * Special keys - Bits 0 - 3 for column index, bit 4 is row index.
  */
char keys[ROWS][COLS] = {
  {0x14,0x11,0x08,0x06,0x04,0x02,0x20,0x21,0x22,0x23,0x24,0x25},
  {0x12,0x09,0x07,0x05,0x03,0x01,0x30,0x31,0x32,0x33,0x34,0x35},
  {0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x39,0x3a,0x3b,0x3c,0x3d},
};

// Arduino pins for the rows of the keypad.  RP Pico GPIO pin numbers.
byte rowPins[ROWS] = {12, 13, 14};
// Arduino pins for the columns of the keypad.  RP Pico GPIO pin numbers.
byte colPins[COLS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// Uncomment lines below to debug neopixels once keyboard is debugged.
// Pico GPIO pin number
#define NEOPIXEL_PIN 15 // RP Pico GPIO pin number
#define NUM_PIXELS 30 // Only 30 pixels in original neokey ordering.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
#define GREENPIXEL 0x00006400
#define BLUEPIXEL 0x000000FF
#define REDPIXEL 0x00640000
#define WHITEPIXEL 0x00646464
#define KANAMODEKEY 5
#define KANAITERATE 11

/*
 * An approach to associating key values to neopixels is to use the index formed 
 * for each group to map to a specific neopixel.  Note that indexes that do not
 * map to a specific neopixel is set to -1.
 */
const int8_t consoColorKeys[] = {-1, 18, 29, 19, 28, 20, 27, 21, 26, 22};
const int8_t shiftColorKeys[] = {-1, 25, 23, -1, 24};
const int8_t vowelColorKeys[] = {12, 13, 14, 15, 16, 17};
const int8_t speclColorKeys[] = {11, 10, 9, 8, 7, 6, -1, -1, 0, 1, 2, 3, 4, -1};

// Note that press key indexes corresponding to color
// keys with value of -1 will never be set to true.
bool consoPressKeys[] = {false, false, false, false, false, false, false, false, false, false};
bool shiftPressKeys[] = {false, false, false, false, false};
bool vowelPressKeys[] = {false, false, false, false, false, false};
bool speclPressKeys[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

uint16_t getKanaUnicode(bool kana, bool special, uint8_t shift, uint8_t row, uint8_t col);

// Count of number of keys currently pressed for each key group.
byte consoCount;
byte shiftCount;
byte vowelCount;
byte speclCount;
byte indexRow, indexCol, shiftType;
bool kana, emit, speclKey; // Hirigana = false, Katakana = true.

/**
 * Function: kbd_setup - Initialze keyboard functionality,
 * e.g., keypad driver, keypad debounce, Neopixel driver.
 * Input: None.
 * Output: None.
 */
void kbd_setup(void) {
  consoCount = 0;
  shiftCount = 0;
  vowelCount = 0;
  speclCount = 0;
  kana = false;
  speclKey = false;
  indexRow = 0;
  indexCol = 0;
  shiftType = 0;
  
  /**
   * Initialize the Neopixels at start up.  Consonant, vowel, and
   * Kana mode, and iteration mark keys are green.  The remaining
   * special keys and shift keys are white.
   */
  strip.setPixelColor(KANAMODEKEY, GREENPIXEL);
  for (int i = 0; i < sizeof(consoColorKeys); i++) {
    if (consoColorKeys[i] != -1)
      strip.setPixelColor(consoColorKeys[i], GREENPIXEL);
  }
  for (int i = 0; i < sizeof(vowelColorKeys); i++) {
    if (vowelColorKeys[i] != -1)
      strip.setPixelColor(vowelColorKeys[i], GREENPIXEL);
  }

  strip.setPixelColor(speclColorKeys[0], GREENPIXEL);

  for (int i = 1; i < sizeof(speclColorKeys); i++) {
    if (speclColorKeys[i] != -1)
      strip.setPixelColor(speclColorKeys[i], WHITEPIXEL);
  }
  for (int i = 0; i < sizeof(shiftColorKeys); i++) {
    if (shiftColorKeys[i] != -1)
      strip.setPixelColor(shiftColorKeys[i], WHITEPIXEL);
  }
  strip.show();
  
  kpd.setDebounceTime(40); // 40 ms debounce works better that default 20 ms.
}

/**
 * Function: kbd_process - Keyboard functionality processing,
 * Input: None.
 * Output: Kana Unicode character.
 */
uint16_t kbd_process(void) {
  byte keyGroup, keyIndex;
  bool kanaChange, badCombo; // Indicator of bad key combination.
  unsigned long keyColor;
  uint16_t kanaValue = 0x0000;

  kanaChange = false;
  emit = false;
 
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        keyGroup = kpd.key[i].kchar >> 4;   // Most-significant four bits hold key group.
        keyIndex = kpd.key[i].kchar & 0x0f; // Least-significant four bits hold index value.
        switch (kpd.key[i].kstate) {  // Report active key states : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            // Increment count for key type.
            switch (keyGroup) {
              case CONSO_KEY:
                consoCount += 1; // Increment count of consonant keys pressed.
                indexRow = keyIndex;
                consoPressKeys[keyIndex] = true;
              break;
              case SHIFT_KEY:
                shiftCount += 1; // Increment count of shift keys pressed.
                shiftType = keyIndex;
                shiftPressKeys[keyIndex] = true;
              break;
              case VOWEL_KEY:
                vowelCount += 1; // Increment count of vowel keys pressed.
                indexCol = keyIndex;
                vowelPressKeys[keyIndex] = true;
                speclKey = false;
                emit = true;
              break;
              case SPECL_KEY:
                if (keyIndex != 0x0d) {
                  speclCount += 1;  // Increment count of special keys pressed.
                  speclPressKeys[keyIndex] = true;
                  // Most-significant bit of nybble forms column index.
                  indexRow = (keyIndex & 0x08) >> 3;
                  // Least-significant three bits of nybble form column index.
                  indexCol = keyIndex & 0x07;
                  speclKey = true;
                  emit = true;
                } else {
                  kanaChange = true;
                }
              break;
            }
          break;
          case HOLD:
            // Preserving the HOLD case if needed in the future.
          break;
          case RELEASED:
            keyColor = kana ? BLUEPIXEL : GREENPIXEL;
            // Decrement count for key type.
            switch (keyGroup) {
              case CONSO_KEY:
                consoCount -= 1;
                indexRow = 0;
                consoPressKeys[keyIndex] = false;
                strip.setPixelColor(consoColorKeys[keyIndex], keyColor);
              break;
              case SHIFT_KEY:
                shiftCount -= 1;
                shiftType = 0;
                shiftPressKeys[keyIndex] = false;
                strip.setPixelColor(shiftColorKeys[keyIndex], WHITEPIXEL);
              break;
              case VOWEL_KEY:
                vowelCount -= 1;
                indexCol = 0;
                vowelPressKeys[keyIndex] = false;
                strip.setPixelColor(vowelColorKeys[keyIndex], keyColor);
              break;
              case SPECL_KEY:
                if (keyIndex != 0x0d) {
                  speclCount -= 1;
                  indexRow = 0;
                  indexCol = 0;
                  speclPressKeys[keyIndex] = false;
                  if (keyIndex >= 0x01)
                    keyColor = WHITEPIXEL;
                  strip.setPixelColor(speclColorKeys[keyIndex], keyColor);
                }
              break;
            }
            strip.show();
          break;
          case IDLE:
            // Preserving the IDLE case if needed in the future.
          break;
        }
      }
    }

    if (kanaChange) {
      kana ^= true; // Switch between hiragana and katakana.
      keyColor = kana ? BLUEPIXEL : GREENPIXEL;
      strip.setPixelColor(KANAMODEKEY, keyColor);
      strip.setPixelColor(KANAITERATE, keyColor);
      for (int i = 0; i < sizeof(consoColorKeys); i++) {
        if (consoColorKeys[i] != -1)
          strip.setPixelColor(consoColorKeys[i], keyColor);
      }
      for (int i = 0; i < sizeof(vowelColorKeys); i++) {
        if (vowelColorKeys[i] != -1)
          strip.setPixelColor(vowelColorKeys[i], keyColor);
      }
      strip.show();
    }

    badCombo = false;
    // Bad combo if any key group has more than one key pressed at the same time.
    if ((consoCount > 1) || (shiftCount > 1) || (vowelCount > 1) || (speclCount > 1))
      badCombo = true;

    // Bad combo if either consonant key(s) or vowel key(s) and special key(s) are
    // pressed at the same time.
    if (((consoCount > 0) || (vowelCount > 0)) && (speclCount > 0))
      badCombo = true;

    // Bad combo
    if (badCombo) {
      // This is a point where the tone is turned on, if buzzer is used?
      emit = false;
    }

    if (emit) {
      kanaValue = getKanaUnicode(kana, speclKey, shiftType, indexRow, indexCol);
      if (kanaValue == 0x0000) {
        badCombo = true;
        // This is a point where the tone is turned on, if buzzer is used?
      }
    }

    if (badCombo) {
      // A bad key combination makes those keys red.
      keyColor = REDPIXEL;
    } else {
      // When key combination is not bad, the Kana mode sets the color.
      keyColor = kana ? BLUEPIXEL : GREENPIXEL;
    }
    // Set the pressed Consonant keys to the selected color.
    for (int i = 0; i < sizeof(consoPressKeys); i++) {
      if (consoPressKeys[i])
        strip.setPixelColor(consoColorKeys[i], keyColor);
    }
    
    // Set the pressed Vowel keys to the selected color.
    for (int i = 0; i < sizeof(vowelPressKeys); i++) {
      if (vowelPressKeys[i])
        strip.setPixelColor(vowelColorKeys[i], keyColor);
    }

    // If Special key 0 (iteration marks key) is pressed, set to selected color.
    if (speclPressKeys[0])
      strip.setPixelColor(speclColorKeys[0], keyColor);

    // All other pressed keys will be either red or white.
    keyColor = badCombo ? REDPIXEL : WHITEPIXEL;
    // Set the pressed Special keys to the selected color.
    for (int i = 1; i < sizeof(speclPressKeys); i++) {
      if (speclPressKeys[i])
        strip.setPixelColor(speclColorKeys[i], keyColor);
    }

    // Set the pressed Shift keys to the selected color.
    for (int i = 0; i < sizeof(shiftPressKeys); i++) {
      if (shiftPressKeys[i])
        strip.setPixelColor(shiftColorKeys[i], keyColor);
    }
    strip.show();
  }
  
  return(kanaValue);
}

#define HIRAGANA false
#define KATAKANA true
#define NOMOD 0
#define TENTEN 1
#define MARU 2
#define CHIISAI 4

/**
 * Function: getKanaUnicode - Get Unicode value for Kana or special character
 * Input:
 *   kana: false - Hiragana character mode, true - Katakana character mode.
 *   special: false - Kana syllabary character, true - CJK symbol character.
 *   shift: 0 - No modification, 1 - Ten ten, 2 - Maru, 3 - Chiisai.
 *   row: Row index of table.
 *   col: Column index of table.
 * Output:
 */
uint16_t getKanaUnicode(bool kana, bool special, uint8_t shift, uint8_t row, uint8_t col) {
  uint16_t unicode;
  
  if (kana == HIRAGANA) {
    if (special) {
      switch (shift) {
        case NOMOD:
          // Hirigana base special characters.
          unicode = specialHiraBase[row][col];
        break;
        case TENTEN:
          // Hiragana ten-ten special characters.
          unicode = specialHiraTen[row][col];
        break;
        case MARU:
          // There are no Hiragana Maru special characters.
          unicode = 0x0000;
        break;
        case CHIISAI:
          // Hirigana chiisai special characters.
          unicode = specialHiraChi[row][col];
        break;
      }
    } else {
      switch (shift) {
        case NOMOD:
          // Hiragana base characters.
          unicode = hiraBase[row][col];
        break;
        case TENTEN:
          // Hiragana ten-ten characters.
          unicode = hiraTenTen[row][col];
        break;
        case MARU:
          // Hiragana maru characters.
          unicode = hiraMaru[row][col];
        break;
        case CHIISAI:
          // Hirigana chiisai characters.
          unicode = hiraChiisai[row][col];
        break;
      }
    }
  } else { // KATAKANA
    if (special) {
      switch (shift) {
        case NOMOD:
          // Katakana base special characters.
          unicode = specialKataBase[row][col];
        break;
        case TENTEN:
          // Katakana ten-ten special characters.
          unicode = specialKataTen[row][col];
        break;
        case MARU:
          // There are no Katakana maru special characters.
          unicode = 0x0000;
        break;
        case CHIISAI:
          // Katakana chiisai special characters.
          unicode = specialKataChi[row][col];
        break;
      }
    } else {
      switch (shift) {
        case NOMOD:
          // Katakana base characters.
          unicode = kataBase[row][col];
        break;
        case TENTEN:
          // Katakana ten-ten characters.
          unicode = kataTenTen[row][col];
        break;
        case MARU:
          // Katakana maru characters.
          unicode = kataMaru[row][col];
        break;
        case CHIISAI:
          // Katakana chiisai characters.
          unicode = kataChiisai[row][col];
        break;
      }
    }
  }
  
  return(unicode);
}
