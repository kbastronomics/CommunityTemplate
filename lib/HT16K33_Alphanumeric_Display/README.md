# HT16K33 Alphanumeric Display

Arduino library for HT16K33-based 14-segment alphanumeric displays.

This library is derived from the HT16K33 Alphanumeric  Display Arduino Library and has been expanded to support multiple display hardware mappings, custom character maps, formatted output, and additional microcontroller platforms.

## Features

- Supports the original HT16K33 Alphanumeric  Display
- Supports ECBUY / VK16K33-based 4-digit alphanumeric modules
- Supports custom SparkFun-compatible display hardware
- Supports up to four displays on a single I2C bus
- Standard Arduino `Print` support
- `printf()`-style formatted output
- Integer, hexadecimal, string, and floating-point formatting
- AVR-compatible floating-point formatting without special linker flags
- Custom 96-character font maps
- Individual character overrides with `defineChar()`
- Per-digit decimal-point support on ECBUY displays
- Colon support
- Adjustable brightness
- Blink-rate control
- Display enable / disable
- Character shifting
- Multiple I2C addresses
- Compatible with AVR, RP2040, ESP32, and other Arduino-compatible platforms

## Supported Display Types

The library supports three display modes.

### SparkFun

```cpp
display.setDisplayType(ALPHA_DISPLAY_SPARKFUN);
```

Uses:

- Original SparkFun segment wiring
- Original SparkFun character map
- SparkFun dedicated decimal and colon hardware

This is the default display type.

### ECBUY

```cpp
display.setDisplayType(ALPHA_DISPLAY_ECBUY);
```

Uses:

- ECBUY / VK16K33 segment wiring
- ECBUY-specific character map
- One decimal point per digit
- Colon rendered using display segments

### Custom

```cpp
display.setDisplayType(ALPHA_DISPLAY_CUSTOM);
```

Uses:

- SparkFun-compatible physical wiring
- A user-defined character map when one is installed
- The built-in SparkFun character map when no custom map is installed

Custom hardware must follow the SparkFun segment wiring arrangement.

## Installation

### Arduino Library Manager

If this library is published through the Arduino Library Manager, search for:

```text
HT16K33 Alphanumeric Display
```

### ZIP Installation

Download the repository as a ZIP file, then in the Arduino IDE select:

```text
Sketch
  -> Include Library
  -> Add .ZIP Library
```

## Basic Example

```cpp
#include <Wire.h>
#include <HT16K33_Alphanumeric_Display.h>

HT16K33 display;

void setup()
{
    Wire.begin();

    display.setDisplayType(ALPHA_DISPLAY_ECBUY);

    if (!display.begin(0x70))
    {
        while (1);
    }

    display.print("1234");
}

void loop()
{
}
```

For an original SparkFun display, the display type does not need to be explicitly selected:

```cpp
#include <Wire.h>
#include <HT16K33_Alphanumeric_Display.h>

HT16K33 display;

void setup()
{
    Wire.begin();

    display.begin(0x70);
    display.print("TEST");
}
```

## printf() Support

The library provides formatted output using:

```cpp
display.printf(...);
```

Examples:

```cpp
display.printf("%04d", 23);
```

Displays:

```text
0023
```

Floating point:

```cpp
display.printf("%.1f", 12.4);
```

On an ECBUY display this produces:

```text
12.4
```

with the decimal point attached to the preceding digit.

Hexadecimal:

```cpp
display.printf("%02X", 10);
```

Displays:

```text
0A
```

Text and numbers can be combined:

```cpp
display.printf("CH%02d", 3);
```

Displays:

```text
CH03
```

### AVR Floating-Point Support

On AVR platforms, including:

- ATmega328P
- ATmega2560
- ATmega32U4

the standard AVR `printf()` implementation normally omits floating-point support.

This library provides its own AVR-compatible `%f` handling, so code such as:

```cpp
display.printf("%.1f", 12.4);
```

works without requiring special linker options.

On RP2040, ESP32, and other supported non-AVR platforms, the normal system `vsnprintf()` implementation is used.

## Custom Character Maps

A complete custom character map contains 96 `uint16_t` entries.

The entries correspond to:

```text
Index 0   : space
Index 1   : !
Index 2   : "
...
Index 16  : 0
...
Index 25  : 9
...
Index 33  : A
...
Index 58  : Z
...
Index 65  : a
...
Index 90  : z
...
Index 94  : ~
Index 95  : unknown character
```

Example:

```cpp
const uint16_t myCharacterMap[96] =
{
    // 96 character definitions
};
```

Install the map using:

```cpp
display.setCharacterMap(myCharacterMap);
```

Installing a map automatically selects:

```cpp
ALPHA_DISPLAY_CUSTOM
```

Custom displays use SparkFun-compatible physical segment wiring.

### AVR PROGMEM Character Maps

AVR users can store the character map in flash instead of SRAM:

```cpp
const uint16_t PROGMEM myCharacterMap[96] =
{
    // 96 entries
};
```

Then install it using:

```cpp
display.setCharacterMap(
    myCharacterMap,
    ALPHA_MAP_PROGMEM
);
```

This saves approximately 192 bytes of SRAM.

### Clearing a Custom Map

```cpp
display.clearCharacterMap();
```

The display remains in:

```cpp
ALPHA_DISPLAY_CUSTOM
```

but character lookup falls back to the built-in SparkFun character map.

You can test whether a custom map is currently installed with:

```cpp
if (display.hasCharacterMap())
{
    // Custom map is active
}
```

## Individual Character Overrides

Individual characters can be replaced without creating a complete character map.

Example:

```cpp
display.defineChar(
    'A',
    SEG_A |
    SEG_B |
    SEG_C |
    SEG_E |
    SEG_F |
    SEG_G
);
```

Individual `defineChar()` definitions take priority over both built-in and custom character maps.

## Segment Constants

The library exposes logical segment constants:

```cpp
SEG_A
SEG_B
SEG_C
SEG_D
SEG_E
SEG_F
SEG_G
SEG_H
SEG_I
SEG_J
SEG_K
SEG_L
SEG_M
SEG_N
SEG_DP
```

Character maps use logical segment definitions rather than physical HT16K33 RAM positions.

The library translates logical segments into the correct physical mapping for the selected display hardware.

`SEG_DP` is used by display hardware that provides a decimal point as part of each digit, such as the ECBUY display.

## Decimal Points

### ECBUY

Each digit has an independently controllable decimal point.

```cpp
display.decimalOnDigit(1);
display.decimalOffDigit(1);
```

Digit numbering is zero-based:

```text
0 1 2 3
```

for the first display.

With multiple displays:

```text
Display 1: 0  1  2  3
Display 2: 4  5  6  7
Display 3: 8  9 10 11
Display 4: 12 13 14 15
```

### SparkFun / Custom

The original SparkFun decimal functions remain available:

```cpp
display.decimalOnSingle(1);
display.decimalOffSingle(1);
```

These operate using the original SparkFun board's dedicated punctuation wiring.

## Colon Support

The original SparkFun board provides dedicated colon hardware:

```cpp
display.colonOnSingle(1);
display.colonOffSingle(1);
```

The ECBUY display does not have a dedicated colon LED.

Instead, a colon is rendered as a normal character using the appropriate display segments:

```cpp
display.print("1:23");
```

On ECBUY hardware, the colon consumes one character position.

## Multiple Displays

Up to four HT16K33 displays can be configured:

```cpp
display.begin(
    0x70,
    0x71,
    0x72,
    0x73
);
```

Each display contributes four character positions for a maximum of sixteen digits.

## Brightness

Set all connected displays:

```cpp
display.setBrightness(15);
```

Valid values are:

```text
0 through 15
```

where:

```text
0  = minimum brightness
15 = maximum brightness
```

A single display can be adjusted using:

```cpp
display.setBrightnessSingle(1, 8);
```

Display numbers are one-based.

## Blink Rate

```cpp
display.setBlinkRate(2.0);
display.setBlinkRate(1.0);
display.setBlinkRate(0.5);
```

Any unsupported value results in no blinking.

## Display Enable / Disable

All displays:

```cpp
display.displayOn();
display.displayOff();
```

Single display:

```cpp
display.displayOnSingle(1);
display.displayOffSingle(1);
```

## Supported Microcontrollers

The library is intended to support Arduino-compatible platforms including:

- Arduino Nano / ATmega328P
- Arduino Mega 2560 / ATmega2560
- Pro Micro / ATmega32U4
- RP2040
- ESP32

Other Arduino-compatible platforms using the standard `Wire` and `Print` interfaces may also work.

## Repository Contents

- `/examples` — Example sketches demonstrating library functionality.
- `/src` — Library source files:
  - `HT16K33_Alphanumeric_Display.h`
  - `HT16K33_Alphanumeric_Display.cpp`
- `keywords.txt` — Arduino IDE keyword definitions.
- `library.properties` — Arduino library metadata.
- `LICENSE.md` — License and attribution information.

## Attribution

This library is derived from the **HT16K33 Alphanumeric  Display Arduino Library**.

Original repository:

https://github.com/sparkfun/SparkFun_Alphanumeric_Display_Arduino_Library

The original library was created by SparkFun Electronics and includes work by Priyanka Makin and Gaston Williams.

This project retains portions of the original SparkFun implementation while adding substantial modifications including:

- Multiple display hardware mappings
- ECBUY / VK16K33 display support
- Custom display mode
- User-defined character maps
- Per-digit decimal-point support
- Alternate colon handling
- `printf()`-style formatted output
- AVR floating-point formatting
- Additional platform support
- Expanded documentation

SparkFun Electronics does not maintain or endorse this derivative library.

## License

This library is released under the MIT License.

Portions of the source code are derived from the HT16K33 Alphanumeric  Display Arduino Library and retain the original SparkFun copyright and license notices.

See `LICENSE.md` for complete license and attribution information.

## Disclaimer

This software is provided "as is", without warranty of any kind.

Use of the names SparkFun, Qwiic, ECBUY, VK16K33, Arduino, ESP32, and RP2040 is for compatibility and identification purposes only.
