# KanaChord Hardware

## Electronics Components
KanaChord Keyboard uses following electronics parts:
- 1 - Raspberry Pi Pico microcontroller
- 1 - [Adfruit](https://www.adafruit.com) [NeoKey 5x6 Ortho Snap-Apart Mechanical Key Switches w/ NeoPixel - For MX Compatible Switches](https://www.adafruit.com/product/5157)
- 30 - Cherry MX mechanical key switches, [e.g., Cherry MX Brown Switches](https://www.cherrymx.de/en/cherry-mx/mx-original/mx-brown.html) (does not count spares)
- 1 - BC547 (or equivalent) NPN transistor
- 1 - 2.2 Kohm 1/8 Watt resistor
- 1 - 6.8 Kohm 1/8 Watt resistor
- 1 - Three-position (NC-NO-NC) slide switch (e.g., E-Switch Slide Switches 500SSP3S2M1QEB, Mouser 612-500SSP3S2M1QEB)
- 27 - 0.1" Spacing Row Right Angle Headers (does not count spairs) [e.g., Schmartboard brand](https://schmartboard.com/qty-10-0-1-spacing-40-single-row-right-angle-headers-920-0076-01/)
- 2 - Seven-position ITT connector shell
- 3 - Five-position ITT connector shell
- 1 - Four-position ITT connector shell
- 1 - Three-position ITT connector shell
- 27 - Female crimp contact pins (does not count spares)
- 5 - Male crimp contact pins (does not count spares)
- 1 - USB A to USB Micro B cable

## Keyboard Schematics
Below is a pictorial schematic of the keypad portion of the KanaChord keyboard.
![Keypad_Schematic](https://github.com/maccody/KanaChord/assets/17059321/c248bed6-f632-452f-8a74-8115157004ea)
While the Neopixels of the Ortho Snap-Apart board can opperate at 3.3 Volts, the 3.3-Volt regulator on the Pico cannot supply enough current.  Therefore, the Neopixels are powered by the Pico's 5-Volt VSYS output.  Consequently, a unidirectional level shifter is used to convert the low-voltage Neopixel signal, NP(LV), to a high-voltage Neopixel, NP(HV).  The BC547 and resistors are used to implement the unidirectional level shifter circuit.

Below is a pictorial schematic of the Raspberry Pi Pico portion of the KanaChord keyboard.
![Pico_Schematic](https://github.com/maccody/KanaChord/assets/17059321/dfdb0b1d-8bab-49b1-8f25-17d24acd65c2)
The right-angle header pins are soldered in 'gull-wing' fashion on pins 1 through 25 and 36 through 39 of the Pico.  The slide switch is not soldered directly to the Pico.  Rather, the wires soldered to the switch have female connector pins crimped on and placed within a three-position connector shell.  During final assembly, the connector will be placed on the header pins at positions 22 through 24.


## 3D-Printed Enclosure
The keycaps and enclosure for the KanaChord Keyboard were created in TinkerCAD, as shown in the illustrations below.  The enclosure was designed in halves to fit on the build plate of a Crealty Ender 3 Pro 3D printer.  Keyed mating components were included to ensure secure assembly.  Two feet, one shown on the lower left of the enclosure illustration, are printed and inserted into the holes in the baseplate during assembly.  These provide some ergonomic tilt to the KanaChord Keyboard in alignment with the main keyboard.  Note that the green rectangle on the baseplate indicates where the microcontroller is attached and is not part of the baseplate design.
![KanaChord_Keycaps](https://github.com/maccody/KanaChord/assets/17059321/93afd88c-73b2-4089-8cf6-816c1f5a1629)
