# KanaChord Software
KanaChord's software was developed with open-source tools and libraries:
- Arduino Integrated Development Environment (Version 1.8.19),
- Wiring programming language (C++-ish),
- [Earle Philhower's RP2040 Arduino board support package](https://github.com/earlephilhower/arduino-pico),
- Libraries used:
   - [Arduino USB Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/),
   - [Mark Stanley's Arduino Keypad](https://github.com/Chris--A/Keypad),
   - [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel).

Note that the source code for the Keypad library has been slightly modified for the RP2040 and the file names have been renamed accordingly.  The output drive current for the keyboard polling lines has been set to 12 milliamps, which is the maximum for the RP2040.  It was found that the default drive current of 4 milliamps provided insufficient for the keyboard.

A high-level flowchart of the Arduino setup() and loop() functions is presented below:
![Software_Flowchart](https://github.com/maccody/KanaChord/assets/17059321/38649ea0-ec65-4ddd-a641-76963ef7813d)

A lot of the keyboard processing involves determine whether a pressed key combination is valid or not.  If the combination is invalid, the Neopixels of the pressed key combination are turned red.  If the combination is valid, a Unicode key value is converted to ASCII and sent as part of a macro sequence to the USB device interface for transmission to the computer.  The macro sequence sent is determined by a three-position switch.  The macro sequence are for Microsoft Windows applications (e.g., MS Word, Wordpad, LibreOffice), Linux applications (e.g., LibreOffice, Firefox), and MacOS applications (functionality not tested yet).  For additional details, consult the commented source code.
## Unicode Data
The file kana.h contains C++ arrays containing the 16-bit Unicode values for Kana (Hiragana and Katakana) characters, and some Chinese/Japanese/Korean punctuation and special characters.  Details on these Unicode blocks can be found in the following PDFs:
- [Official Unicode Consortium Hiragana code chart](https://www.unicode.org/charts/PDF/U3040.pdf)
- [Official Unicode Consortium Katakana code chart](https://www.unicode.org/charts/PDF/U30A0.pdf)
- [Official Unicode Consortium CJK Symbols and Special characters code chart](https://www.unicode.org/charts/PDF/U3000.pdf)
- [Official Unicode Consortium General Punctuation characters code chart](https://www.unicode.org/charts/PDF/U2000.pdf)

The arrays containing the Kana are grouped according Hiragana and Katakana character sets. Individual arrays represent unaugmented (base) characters and augmented characters, i.e., ten-ten, maru, and small (chiisai) characters. Each array is organized by ten 'consonants' (rows) and six 'vowels' (columns).  Special characters are also grouped according to Hiragana and Katakana character sets, although this results in most characters being duplicates in these sets. This was done to simplify the code used to access the arrays.  

The function getKanaUnicode(), defined in kbd_mgt.cpp, takes inputs of kana mode, special character mode, shift mode, and index row and column to select a Unicode character value. If the selected Unicode value is 0x0000, then an illegal key has been selected.
