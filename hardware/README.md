# KanaChord Hardware

## Electronics Components
KanaChord Keyboard uses following electronics parts:
- 1 x Raspberry Pi Pico microcontroller
- 1 x [Adfruit](https://www.adafruit.com) [NeoKey 5x6 Ortho Snap-Apart Mechanical Key Switches w/ NeoPixel - For MX Compatible Switches](https://www.adafruit.com/product/5157)
- 30 x Cherry MX mechanical key switches, [e.g., Cherry MX Brown Switches](https://www.cherrymx.de/en/cherry-mx/mx-original/mx-brown.html) (does not count spares)
- 1 x BC547 (or equivalent) NPN transistor
- 1 x 2.2 Kohm 1/8 Watt resistor
- 1 x 6.8 Kohm 1/8 Watt resistor
- 1 x Three-position (NC-NO-NC) slide switch (e.g., E-Switch Slide Switches 500SSP3S2M1QEB, Mouser 612-500SSP3S2M1QEB)
- 27 x 0.1" Spacing Row Right Angle Headers (does not count spairs) [e.g., Schmartboard brand](https://schmartboard.com/qty-10-0-1-spacing-40-single-row-right-angle-headers-920-0076-01/)
- 2 x Seven-position ITT connector shell - Found in Adafruit [Large Single Row Housing Pack](https://www.adafruit.com/product/3146)
- 3 x Five-position ITT connector shell - Found in Adafruit [Small Single Row Wire Housing Pack](https://www.adafruit.com/product/3145)
- 1 x Four-position ITT connector shell - Found in Adafruit [Small Single Row Wire Housing Pack](https://www.adafruit.com/product/3145)
- 1 x Three-position ITT connector shell - Found in Adafruit [Small Single Row Wire Housing Pack](https://www.adafruit.com/product/3145)
- 27 x Female crimp contact pins (does not count spares)
- 5 x Male crimp contact pins (does not count spares)
- 1 x 12 inches of Forty-conductor ribbon cable 
- 1 x USB A to USB Micro B cable

## Keyboard Schematics
Below is a pictorial schematic of the keypad portion of the KanaChord keyboard.
![Keypad_Schematic](https://github.com/maccody/KanaChord/assets/17059321/e88566f6-8786-4128-a668-2d8d51245a2b)

While the Neopixels of the Ortho Snap-Apart board can opperate at 3.3 Volts, the 3.3-Volt regulator on the Pico cannot supply enough current.  Therefore, the Neopixels are powered by the Pico's 5-Volt VSYS output.  Consequently, a unidirectional level shifter is used to convert the low-voltage Neopixel signal, NP(LV), to a high-voltage Neopixel, NP(HV).  The BC547 and resistors are used to implement the unidirectional level shifter circuit.

Below is a pictorial schematic of the Raspberry Pi Pico portion of the KanaChord keyboard.
![Pico_Schematic](https://github.com/maccody/KanaChord/assets/17059321/c55b775b-cf49-4f5c-ba6d-753b1c51984f)

The right-angle header pins are soldered in 'gull-wing' fashion on pins 1 through 25 and 36 through 39 of the Pico.  The slide switch is not soldered directly to the Pico.  Rather, the wires soldered to the switch have female connector pins crimped on and placed within a three-position connector shell.  During final assembly, the connector will be placed on the header pins at positions 22 through 24.

Left keypad wiring
![left_keyboard_wiring](https://github.com/maccody/KanaChord/assets/17059321/9d1dbdbe-8107-420e-a732-3e044da0dc36)



Right keypad wiring
![right_keyboard_wiring](https://github.com/maccody/KanaChord/assets/17059321/4543c96b-0231-4bb2-8c08-8ce42945edf8)




## 3D-Printed Keycaps
The keycaps for the KanaChord Keyboard were created in TinkerCAD, as shown in the illustration below.  The STL files for the left-hand and right-hand keycap sets can be viewed with the Github STL viewer by clicking on the STL files listed above.
![KanaChord_Keycaps](https://github.com/maccody/KanaChord/assets/17059321/93afd88c-73b2-4089-8cf6-816c1f5a1629)

The blank keycap from makerhack's (Chris Garrett) [Custom Cherry MX Keycaps](https://www.thingiverse.com/thing:4702109) was used as the source keycap.  It is licensed under the [Creative Commons - Attribution license](https://creativecommons.org/licenses/by/4.0/).  The Kana and special charaters are text objects coverted to TinkerCAD 'holes' that were combined with each blank keycap to form insets.  The keycaps were sliced with Cura using Standard Quality (0.2mm), with 20% infill using the gyroid infill pattern.  The keycaps were printed with untinted PLA to allow the Neopixels to shine through.  After printing, the insets were filled with black acrylic paint, followed by a coat of flat, clear enamel paint.




## 3D-Printed Enclosure
Enclosure for the KanaChord Keyboard was also created in TinkerCAD, as shown in the illustrations below.  The STL files for the individual components of the enclosure can be viewed with the Github STL viewer by clicking on the STL files listed above.
![TinkerCAD_Keyboard_Case](https://github.com/maccody/KanaChord/assets/17059321/fc7e1685-39a2-46db-be0c-d81ea0488f06)

The left and right keycase enclosures were created using 0707070user's OpenSCAD program [Customizable snap-fit electronics project box enclosure](https://www.thingiverse.com/thing:2866563). It is licensed under the [Creative Commons - Attribution license](https://creativecommons.org/licenses/by/4.0/). The enclosure components are flipped so tha the lids now act as baseplates for the keyboard enclosure.  The enclosures were edited to crete the holes of the integral keyplates, the switch and Pico mounts, and hole for the USB cable.  



The enclosure was designed in halves to fit on the build plate of a Crealty Ender 3 Pro 3D printer.  Keyed mating components were included to ensure secure assembly.  Two feet, one shown on the lower left of the enclosure illustration, are printed and inserted into the holes in the baseplate during assembly.  These provide some ergonomic tilt to the KanaChord Keyboard in alignment with the main keyboard.  Note that the green rectangle on the baseplate indicates where the microcontroller is attached and is not part of the baseplate design.


## KanaChord Assembly

### Applying PCB Cushions
![foam_pads](https://github.com/maccody/KanaChord/assets/17059321/d07042ee-55a1-4edd-b80b-6a1c03b1eda2)



### Mounting the Raspberry Pi Pico
![pico_mounted_part_1](https://github.com/maccody/KanaChord/assets/17059321/215b43be-626e-4dd2-926f-f6f00e13c8eb)![pico_mounted_part_2](https://github.com/maccody/KanaChord/assets/17059321/30025973-4183-44a0-b6ef-df61fa7475e0)



### Mounting the Macro Mode Switch


### Pre-stressing the Key Switch Sockets


### Mounting Keyboard PCBs to Enclosures







