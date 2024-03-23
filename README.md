![KanaChord_glamor_off](https://github.com/maccody/KanaChord/assets/17059321/b76565f8-2dac-4850-b650-6bb7f1f815eb)
# KanaChord Keyboard (かな・コード・キーボード)
## Overview
KanaChord is an auxiliary keyboard that works in parallel with a standard English keyboard and generates Unicode keyboard macros to render Japanese Kana characters.

The Japanese writing system consists of three components: Kanji, Hiragana, and Katakana. Kanji consists of Chinese logography and conveys main ideas and names in sentences, e.g., 私, 東京, 何 (‘I’, ‘Tokyo’, ‘what’).  There are thousands of unique Kanji characters.  Hiragana consists of 48 syllabic characters that are used for some words of Japanese origin and grammatical sentence fragments, e.g., あなた, これ, の (‘you’, ‘this’, possessive particle).  Katakana also consists of 48 syllabic characters that are used for foreign loan words and names, e.g., テーブル, クッキー, マック (‘table’, ‘cookie’, ‘Mac’).  The table below shows the syllabary of Hiragana and Katakana, known collectively as the Kana.
![Kana Table](https://github.com/maccody/KanaChord/assets/17059321/9cd2e0d3-35b2-4e8d-afc0-48902b5663b5)

The layout of the Kana Table inspires a chording keyboard input method. Chording is where multiple keys are pressed simultaneously on the keyboard to obtain a desired character output.  The illustration below provides further explanation and demonstration of how chording is used on the KanaChord Keyboard.
![Kana Chording Example](https://github.com/maccody/KanaChord/assets/17059321/28a0261d-a850-44c0-8041-38e712184cdf)
## Features
KanaChord includes dynamic key coloring that provides indication of character type, Kana mode, and error feedback.  The three Shift keys on the left keypad are normally white:
- Voicing mark, a.k.a. dakuten or ten-ten (ﾞ),
- Plosive mark, a.k.a. handakuten or maru (ﾟ),
- Small characters, a.k.a. chiisai (小), also used to ‘shift’ to alternate punctuation characters.

Punctuation keys on the top two rows of the right keypad are also normally white:
- Vertical iteration mark (〳,〴,〵), continuation mark (ー), and separation (・) characters ,
- Sentence pausing (、) and ending characters (。, ! , ?),
- Space and ellipsis (…) characters,
- Commonly-used quotation (「, 」,『, 』), bracket (【, 】,〈, 〉), and special (〜,※) characters.

The Kana and horizontal iteration mark (ゝ,ゞ,ヽ,ヾ) keys are green for Hiragana mode or blue for Katakana mode, as selected by the mode key (ひカ) at upper right-hand corner of the right keypad.
![KanaChord_installed_grn](https://github.com/maccody/KanaChord/assets/17059321/16ad7761-8050-4fc2-88fc-f42ae1514f95)
![KanaChord_installed_blu](https://github.com/maccody/KanaChord/assets/17059321/82f53d75-e7da-4fb6-b7fc-707c0d0d8970)

Feedback is provided to the user for incorrect key combinations by changing those keys red.  Releasing the keys will cause the keys to revert to their original colors.  Some examples are provded below:

Keyboard error lighting with press of ! and あ key combination.
![KanaChord_error_1](https://github.com/maccody/KanaChord/assets/17059321/a320b713-3092-48ac-b89c-a8866d4bee1f)

Keyboard error lighting with press of ﾞ, な, and あ key combination.
![KanaChord_error_2](https://github.com/maccody/KanaChord/assets/17059321/92adddb6-386d-42b5-8858-f299eb6bf426)

A slide switch above the か key provides user-selectable mode of Unicode key sequences to support different computer platforms:
- Unicode hexidecimal value, followed by Alt-X: Supports Microsoft Word and Wordpad, and LibreOffice Writer.
- Ctrl-Shift-u, followed by four-character Unicode hexidecimal value: Supports Linux applications like LibreOffice Writer and Firefox.
- Option key, followed by Unicode hexidecimal value: Support MacOS applications (not yet tested).

## Implementation Overview
The primary electical componets of the KanaChord Keyboard are a Raspberry Pi Pico (RP2040) microcontroller, an Adfruit NeoKey 5x6 Ortho Snap-Apart keyboard PCB, and thirty Cherry MX mechanical key switches.  The keycaps and keyboard enclosure are 3D printed designs created with TinkerCAD.  Blank keycaps and an OpenSCAD tight-fit box generator were found on Thingiverse.  No special hardware, such as screws are needed to mount the electrical components and assemble the enclosure.  Details on the electronics, enclosure, and their assembly can be found in the hardware folder.

Kanachord's software was developed with the Arduino IDE (version 1.8.19) and Earle Philhower's RP2040 board support package.  The USB Keyboard library, Adafruit Neopixel library, and Mark Stanley's Key and Keypad libraries provided critical software functions.  Details on the software can be found in the software folder.

## Hardware and Software Licenses
![Cc_by-nc-nd_icon svg](https://github.com/maccody/KanaChord/assets/17059321/d487f84e-e2eb-4da8-92fb-27e1601b0ce2)
KanaChord's circuit design and the STL files for the keycaps, component mounting parts, and enclosure parts are placed under Creative Commons Attribution-NonCommercial-NoDerivatives license.

![GNU_GPL_V3](https://github.com/maccody/KanaChord/assets/17059321/118bcb5a-27bf-43ac-b6bc-08312a90a695)
KanaChord's source code that I wrote (KanaChord.ino, kana.h, kbd_mgt.cpp, and kbd_mgt.h) are placed under GNU General Public License, Version 3.0.

The slightly-modified versions of Mark Stanley's Key and Keypad libraries (Key2040.cpp, Key2040.h, Keypad2040.cpp, and Keypad2040.h) fall under the license of the original sources.
