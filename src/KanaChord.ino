#include <Keypad.h>
#include <Key.h>
#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>
#include "kana.h"

//#define DEBUG 1
/*
 * The Adafruit Neokey board, which has five rows and six columns,
 * is broken between the third and fourth rows and set up as a
 * keyboard with three rows and twelve columns.  Note that the
 * left-most six columns only has two rows.
*/
#define ROWS 3
#define COLS 12
// Different key groupings are differentiated by the value of the
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

// Arduino pins for the rows of the keypad.
byte rowPins[ROWS] = {8, 6, 4};
// Arduino pins for the columns of the keypad.
byte colPins[COLS] = {18, 19, 20, 21, 22, 23, 13, 12, 11, 10, 9, 7};

// Uncomment lines below to debug neopixels once keyboard is debugged.
#define NEOPIXEL_PIN 5
#define NUM_PIXELS 30 // Only 30 pixels in original neokey ordering.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
#define GREENPIXEL 0x00006400
#define BLUEPIXEL 0x000000FF
#define REDPIXEL 0x00640000
#define WHITEPIXEL 0x00646464
#define KANAMODEKEY 5
#define KANAITERATE 11
#define KANAREPEAT 10

/*
 * An approach to associating key values to neopixels is to use the index formed 
 * for each group to map to a specific neopixel.  Note that indexes that do not
 * map to a specific neopixel is set to -1.
 */
const byte consoColorKeys[] = {-1, 18, 29, 19, 28, 20, 27, 21, 26, 22};
const byte shiftColorKeys[] = {-1, 25, 23, -1, 24};
const byte vowelColorKeys[] = {12, 13, 14, 15, 16, 17};
const byte speclColorKeys[] = {11, 10, 9, 8, 7, 6, -1, -1, 0, 1, 2, 3, 4, -1};

// Note that press key indexes corresponding to color
// keys with value of -1 will never be set to true.
bool consoPressKeys[] = {false, false, false, false, false, false, false, false, false, false};
bool shiftPressKeys[] = {false, false, false, false, false};
bool vowelPressKeys[] = {false, false, false, false, false, false};
bool speclPressKeys[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false};

// Uncomment lines above to debug neopixels once keyboard is debugged.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void getUnicodeChars(char *unicode, bool kana, bool special, byte shift, byte row, char col);

#ifdef DEBUG
unsigned long loopCount;
unsigned long startTime;
String msg;
#endif

// Count of number of keys currently pressed for each key group.
byte consoCount;
byte shiftCount;
byte vowelCount;
byte speclCount;
byte indexRow, indexCol, shiftType;
bool kana, emit, speclKey; // Hirigana = false, Katakana = true.
char unicodeChars[4];

void setup() {
  #ifdef DEBUG
  // Serial port to support debugging of keyboard hardware.
  Serial.begin(115200);
  Serial.println("KanaChord keyboard demo");
  #endif
  
  // Uncomment lines below to debug neopixels once keyboard is debugged.
  strip.begin();
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'
  // Uncomment lines above to debug neopixels once keyboard is debugged.

  #ifdef DEBUG
  // Initialize variables to support debugging of keyboard.
  loopCount = 0;
  startTime = millis();
  msg = "";
  #endif
  consoCount = 0;
  shiftCount = 0;
  vowelCount = 0;
  speclCount = 0;
  kana = false;
  speclKey = false;
  indexRow = 0;
  indexCol = 0;
  shiftType = 0;

  strip.setPixelColor(KANAMODEKEY, GREENPIXEL);
  for (int i = 0; i < sizeof(consoColorKeys); i++) {
    if (consoColorKeys[i] != -1)
      strip.setPixelColor(consoColorKeys[i], GREENPIXEL);
  }
  for (int i = 0; i < sizeof(vowelColorKeys); i++) {
    if (vowelColorKeys[i] != -1)
      strip.setPixelColor(vowelColorKeys[i], GREENPIXEL);
  }
  for (int i = 0; i < 2; i++) {
      strip.setPixelColor(speclColorKeys[i], GREENPIXEL);
  }
  for (int i = 2; i < sizeof(speclColorKeys); i++) {
    if (speclColorKeys[i] != -1)
      strip.setPixelColor(speclColorKeys[i], WHITEPIXEL);
  }
  for (int i = 0; i < sizeof(shiftColorKeys); i++) {
    if (shiftColorKeys[i] != -1)
      strip.setPixelColor(shiftColorKeys[i], WHITEPIXEL);
  }
  strip.show();
  
  #ifndef DEBUG
  // Initialize the USB keyboard emulation.
  Keyboard.begin();
  #endif
  kpd.setDebounceTime(40); // 40 ms debounce works better that default 20 ms.
}


void loop() {
  byte keyGroup, keyIndex;
  bool kanaChange, badCombo; // Indicator of bad key combination.
  unsigned long keyColor;

  kanaChange = false;
  emit = false;

  #ifdef DEBUG
  loopCount++;
  if ( (millis()-startTime)>5000 ) {
    Serial.print("Average loops per second = ");
    Serial.println(loopCount/5);
    startTime = millis();
    loopCount = 0;
  }
  #endif
  
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        keyGroup = kpd.key[i].kchar >> 4;
        keyIndex = kpd.key[i].kchar & 0x0f;
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
          case PRESSED:
            #ifdef DEBUG
            msg = " PRESSED.";
            #endif
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
            #ifdef DEBUG
            msg = " HOLD.";
            #endif
          break;
          case RELEASED:
            #ifdef DEBUG
            msg = " RELEASED.";
            #endif
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
                  if (keyIndex >= 0x02)
                    keyColor = WHITEPIXEL;
                    
                  strip.setPixelColor(speclColorKeys[keyIndex], keyColor);
                }
              break;
            }
            
            strip.show();
          break;
          case IDLE:
            #ifdef DEBUG
            msg = " IDLE.";
            #endif
          break;
        }
        #ifdef DEBUG
        Serial.print("Key ");
        Serial.print(String(kpd.key[i].kchar, HEX));
        Serial.println(msg);
        #endif
      }
    }

    if (kanaChange) {
      kana ^= true; // Switch between hiragana and katakana.
      keyColor = kana ? BLUEPIXEL : GREENPIXEL;
      strip.setPixelColor(KANAMODEKEY, keyColor);
      strip.setPixelColor(KANAITERATE, keyColor);
      strip.setPixelColor(KANAREPEAT, keyColor);
      for (int i = 0; i < sizeof(consoColorKeys); i++) {
        if (consoColorKeys[i] != -1)
          strip.setPixelColor(consoColorKeys[i], keyColor);
      }
      for (int i = 0; i < sizeof(vowelColorKeys); i++) {
        if (vowelColorKeys[i] != -1)
          strip.setPixelColor(vowelColorKeys[i], keyColor);
      }
      strip.show();
      #ifdef DEBUG
      Serial.print("Kana state: ");
      if (kana) {
        Serial.println("true");
      } else {
        Serial.println("false");
      }
      #endif
    }

    badCombo = false;
    // Bad combo if any key group has more than one key pressed at the same time.
    if ((consoCount > 1) || (shiftCount > 1) || (vowelCount > 1) || (speclCount > 1))
      badCombo = true;

    // Bad combo if a vowel key and a special key are pressed at the same time.
    if ((vowelCount > 0) && (speclCount > 0))
      badCombo = true;

    // Bad combo
    if (badCombo) {
      // This is a point where the tone is turned on?
      #ifdef DEBUG
      Serial.println("Bad key combination!");
      #endif
      emit = false;
    }

    if (emit) {
      #ifdef DEBUG
      Serial.print("Emit: ");
      Serial.print(kana);
      Serial.print("  ");
      Serial.print(speclKey);
      Serial.print("  ");
      Serial.print(shiftType);
      Serial.print("  ");
      Serial.print(indexRow);
      Serial.print("  ");
      Serial.println(indexCol);
      #endif
      getUnicodeChars(unicodeChars, kana, speclKey, shiftType, indexRow, indexCol);
      if (unicodeChars[3] != ' ') {
        #ifdef DEBUG
        Serial.print("Unicode: ");
        Serial.println(unicodeChars);
        #endif
        #ifndef DEBUG
        /* Linux Unicode entry sequence */
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('u');
        Keyboard.write(unicodeChars[0]);
        Keyboard.write(unicodeChars[1]);
        Keyboard.write(unicodeChars[2]);
        Keyboard.write(unicodeChars[3]);
        Keyboard.releaseAll();
        /**/
        /* Windows Unicode entry sequence *
        Keyboard.write(unicodeChars[0]);
        Keyboard.write(unicodeChars[1]);
        Keyboard.write(unicodeChars[2]);
        Keyboard.write(unicodeChars[3]);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('x');
        Keyboard.releaseAll();
        /**/
        #endif
      } else {
        badCombo = true;
        // This is a point where the tone is turned on?
        #ifdef DEBUG
        Serial.println("Invalid key combination");
        #endif
      }
    }

    if (badCombo) {
      keyColor = REDPIXEL;
    } else {
      keyColor = kana ? BLUEPIXEL : GREENPIXEL;
    }
    
    for (int i = 0; i < sizeof(consoPressKeys); i++) {
      if (consoPressKeys[i])
        strip.setPixelColor(consoColorKeys[i], keyColor);
    }
    for (int i = 0; i < sizeof(vowelPressKeys); i++) {
      if (vowelPressKeys[i])
        strip.setPixelColor(vowelColorKeys[i], keyColor);
    }
    for (int i = 0; i < 2; i++) {
      if (speclPressKeys[i])
        strip.setPixelColor(speclColorKeys[i], keyColor);
    }
    keyColor = badCombo ? REDPIXEL : WHITEPIXEL;
    for (int i = 2; i < sizeof(speclPressKeys); i++) {
      if (speclPressKeys[i])
        strip.setPixelColor(speclColorKeys[i], keyColor);
    }
    for (int i = 0; i < sizeof(shiftPressKeys); i++) {
     if (shiftPressKeys[i])
        strip.setPixelColor(shiftColorKeys[i], keyColor);
    }
    strip.show();
  }
}


#define HIRAGANA false
#define KATAKANA true
#define NOMOD 0
#define TENTEN 1
#define MARU 2
#define CHIISAI 4

void getUnicodeChars(char *unicode, bool kana, bool special, byte shift, byte row, char col) {
  if (kana == HIRAGANA) {
    if (special) {
      switch (shift) {
        case NOMOD:
          // Hirigana base special characters.
          unicode[0] = specialHiraBase[row][col][0];
          unicode[1] = specialHiraBase[row][col][1];
          unicode[2] = specialHiraBase[row][col][2];
          unicode[3] = specialHiraBase[row][col][3];
        break;
        case TENTEN:
          // Hiragana ten-ten special characters.
          unicode[0] = specialHiraTen[row][col][0];
          unicode[1] = specialHiraTen[row][col][1];
          unicode[2] = specialHiraTen[row][col][2];
          unicode[3] = specialHiraTen[row][col][3];
        break;
        case MARU:
          // There are no Hiragana Maru special characters.
          unicode[0] = ' ';
          unicode[1] = ' ';
          unicode[2] = ' ';
          unicode[3] = ' ';
        break;
        case CHIISAI:
          // Hirigana chiisai special characters.
          unicode[0] = specialHiraChi[row][col][0];
          unicode[1] = specialHiraChi[row][col][1];
          unicode[2] = specialHiraChi[row][col][2];
          unicode[3] = specialHiraChi[row][col][3];
        break;
      }
    } else {
      unicode[0] = '3';
      unicode[1] = '0';
      switch (shift) {
        case NOMOD:
          // Hiragana base characters.
          unicode[2] = hiraBase[row][col][0];
          unicode[3] = hiraBase[row][col][1];
        break;
        case TENTEN:
          // Hiragana ten-ten characters.
          unicode[2] = hiraTenTen[row][col][0];
          unicode[3] = hiraTenTen[row][col][1];
        break;
        case MARU:
          // Hiragana maru characters.
          unicode[2] = hiraMaru[row][col][0];
          unicode[3] = hiraMaru[row][col][1];
        break;
        case CHIISAI:
          // Hirigana chiisai characters.
          unicode[2] = hiraChiisai[row][col][0];
          unicode[3] = hiraChiisai[row][col][1];
        break;
      }
    }
  } else { // KATAKANA
    if (special) {
      switch (shift) {
        case NOMOD:
          // Katakana base special characters.
          unicode[0] = specialKataBase[row][col][0];
          unicode[1] = specialKataBase[row][col][1];
          unicode[2] = specialKataBase[row][col][2];
          unicode[3] = specialKataBase[row][col][3];
        break;
        case TENTEN:
          // Katakana ten-ten special characters.
          unicode[0] = specialKataTen[row][col][0];
          unicode[1] = specialKataTen[row][col][1];
          unicode[2] = specialKataTen[row][col][2];
          unicode[3] = specialKataTen[row][col][3];
        break;
        case MARU:
          // There are no Katakana maru special characters.
          unicode[0] = ' ';
          unicode[1] = ' ';
          unicode[2] = ' ';
          unicode[3] = ' ';
        break;
        case CHIISAI:
          // Katakana chiisai special characters.
          unicode[0] = specialKataChi[row][col][0];
          unicode[1] = specialKataChi[row][col][1];
          unicode[2] = specialKataChi[row][col][2];
          unicode[3] = specialKataChi[row][col][3];
        break;
      }
    } else {
      unicode[0] = '3';
      unicode[1] = '0';
      switch (shift) {
        case NOMOD:
          // Katakana base characters.
          unicode[2] = kataBase[row][col][0];
          unicode[3] = kataBase[row][col][1];
        break;
        case TENTEN:
          // Katakana ten-ten characters.
          unicode[2] = kataTenTen[row][col][0];
          unicode[3] = kataTenTen[row][col][1];
        break;
        case MARU:
          // Katakana maru characters.
          unicode[2] = kataMaru[row][col][0];
          unicode[3] = kataMaru[row][col][1];
        break;
        case CHIISAI:
          // Katakana chiisai characters.
          unicode[2] = kataChiisai[row][col][0];
          unicode[3] = kataChiisai[row][col][1];
        break;
      }
    }
  }
}
