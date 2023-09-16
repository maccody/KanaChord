# KanaChord Keyboard (かな・コード・キーボード)
## Overview
KanaChord Keyboard is an auxiliary keyboard that works in parallel with a standard English keyboard and generates Unicode keyboard macros to render Japanese Kana characters.  The Japanese writing system consists of three components: Kanji, Hiragana, and Katakana. Kanji consists of Chinese logography and conveys main ideas and names in sentences, e.g., 私, 東京, 何 (‘I’, ‘Tokyo’, ‘what’).  There are thousands of unique Kanji characters.  Hiragana consists of 48 syllabic characters that are used for some words of Japanese origin and grammatical sentence fragments, e.g., あなた, これ, の (‘you’, ‘this’, possessive particle).  Katakana also consists of 48 syllabic characters that are used for foreign loan words and names, e.g., テーブル, クッキー, マック (‘table’, ‘cookie’, ‘Mac’).  The table below shows the syllabary of Hiragana and Katakana, known collectively as the Kana.
![Kana Table](https://github.com/maccody/KanaChord/assets/17059321/9cd2e0d3-35b2-4e8d-afc0-48902b5663b5)

The layout of the Kana Table inspires a chording keyboard input method. Chording is where multiple keys are pressed simultaneously on the keyboard to obtain a desired character output.  The illustration below provides further explanation and demonstration of how chording is used on the Kana Chord Keyboard.
![Kana Chording Example](https://github.com/maccody/KanaChord/assets/17059321/28a0261d-a850-44c0-8041-38e712184cdf)

## Software Development
The software was developed with open-source tools and libraries:
- Arduino Integrated Development Environment,
- Wiring programming language (C++-ish),
- Libraries used: Arduino USB Keyboard, Arduino Keypad, Adafruit Neopixel.

The KanaChord Keyboard software includes dynamic key coloring that provides indication of character type, Kana mode, and error feedback.  The three Shift keys on the left keypad are normally white:
- Voicing mark, a.k.a. dakuten or ten-ten (ﾞ),
- Plosive mark, a.k.a. handakuten or maru (ﾟ),
- Small characters, a.k.a. chiisai (小), also used to ‘shift’ to alternate punctuation characters.

Punctuation keys on the top two rows of the right keypad are also normally white:
- Continuation and separation characters (ー, ・ ),
- Sentence pausing and ending characters (、,。, ! , ?),
- Space and ellipsis (…) characters,
- Commonly-used quotation, bracket, and special characters.

The Kana and iteration mark (ゝ,〳,ゞ,〴,ヽ,ヾ) keys are green for Hiragana mode or blue for Katakana mode, as selected by the mode key (ひカ) at upper right-hand corner of the right keypad.
![20230318_205640](https://github.com/maccody/KanaChord/assets/17059321/ff97c014-84e4-4272-921e-25d34306a08e)
![20230318_205708](https://github.com/maccody/KanaChord/assets/17059321/13aefc38-7ce3-475f-89a3-238944a63125)

Illustration of keyboard error with press of ! and 'o' keys
![20230322_200831](https://github.com/maccody/KanaChord/assets/17059321/178542a7-6032-462a-81f3-f55750371a6d)

Illustration of keyboard error with press of ﾞ, な, and あ keys
![20230322_205141](https://github.com/maccody/KanaChord/assets/17059321/4bdc44d7-9c5f-4fe7-92b0-0d6acc72a206)

## Keyboard Electronics
KanaChord Keyboard uses following electronics parts:
- [Adfruit](https://www.adafruit.com) [Itsy Bitsy 32u4 5V](https://www.adafruit.com/product/3677) microcontroller
- [Adfruit](https://www.adafruit.com) [NeoKey 5x6 Ortho Snap-Apart Mechanical Key Switches w/ NeoPixel - For MX Compatible Switches](https://www.adafruit.com/product/5157)
- Cherry MX mechanical key switches [e.g., Cherry MX Brown Switches](https://www.cherrymx.de/en/cherry-mx/mx-original/mx-brown.html)
- 0.1" Spacing Row Right Angle Headers (15 pins required, not counting spairs) [e.g., Schmartboard brand](https://schmartboard.com/qty-10-0-1-spacing-40-single-row-right-angle-headers-920-0076-01/)
- Nine-position ITT connector shell (1 required) 
- Six-position ITT connector shell (1 required)
- Five-position ITT connector shell (2 required)
- Three-position ITT connector shell (1 required)
- Female crimp contact pins (23 required, not counting spares)
- Male crimp contact pins (5 required, not counting spares)
- USB A to USB Micro B cable

Below is an (admittedly crude) schematic of the wiring of the keyboard and the connectors:
![KanaChord_keyboard_circuit](https://github.com/maccody/KanaChord/assets/17059321/051a43f7-1a26-48e3-bedd-93266b0b7eaa)

The numbering on the connectors corresponds to the digital pin (green) numbers on the Itsy Bitsy 32u4 5V board.  The right-angle headers are soldered into these positions on the Itsy Bitsy board.
![ItsyBitsy32u4-5V_Pinout](https://github.com/maccody/KanaChord/assets/17059321/368507ac-0de2-422d-badb-0200d922d985)

Here is a photo of the prototype assembly used durring initial KanaChord keyboard code development.
![20230315_104338](https://github.com/maccody/KanaChord/assets/17059321/d0d42a97-7489-4146-944f-17b9951dcf35)

## 3D Printed Components
The keycaps and enclosure for the KanaChord Keyboard were created in TinkerCAD, as shown in the illustrations below.  The enclosure was designed in halves to fit on the build plate of a Crealty Ender 3 Pro 3D printer.  Keyed mating components were included to ensure secure assembly.  Two feet, one shown on the lower left of the enclosure illustration, are printed and inserted into the holes in the baseplate during assembly.  These provide some ergonomic tilt to the KanaChord Keyboard in alignment with the main keyboard.  Note that the green rectangle on the baseplate indicates where the microcontroller is attached and is not part of the baseplate design.

![KanaChord_Keycaps](https://github.com/maccody/KanaChord/assets/17059321/93afd88c-73b2-4089-8cf6-816c1f5a1629)
![KanaChord_enclosure](https://github.com/maccody/KanaChord/assets/17059321/e6565c8f-9f96-4970-b865-d092f926ca26)

The keycaps and enclosure components were exported as STL files that were sliced using Cura.  The keycaps were printed in untinted PLA and black acrylic paint was used to infill the characters.  The enclosure components were printed in black PLA and assembled.

