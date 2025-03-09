# T-Deck Keyboard

The T-Deck Keyboard project is an improved firmware for the T-Deck's keyboard. It provides firmware for the keyboard along with a minimal test program for the T-deck that reads key inputs from the keyboard and prints them over a serial connection. The keyboards firmware includes functionality for handling key presses, managing keyboard backlight brightness, and sending key and modifier information over I2C.

## Getting Started

To get started with the T-Deck Keyboard project, visit the [Usage](usage.md) page for a quick installation and usage guide. For an in-depth overview of the firmware’s capabilities, consult the [Functionality](functionality.md) page, reference pages are also available at the [Documentation](https://hreikin.co.uk/tdeck-keyboard) site.

## Features

- **Extended Key Functionality**: Supports special key combinations for enhanced functionality.
- **Keymaps**: Supports multiple keymaps including default and symbol keymaps.
- **Modifier Keys**: Handles modifier keys such as Alt, Ctrl, Shift, and special function keys for mic and speaker control.
- **Backlight Control**: Allows for adjusting the keyboard backlight brightness with commands to toggle, increase, or decrease brightness.
- **I2C Communication**: Sends key and modifier information over I2C when requested.

## Files

- **tdeck/tdeck.ino**: Basic test program that initializes the T-Deck, checks the keyboard, and reads key values.
- **keyboard/keyboard.hpp**: Header file defining keyboard functions, keymaps, and constants.
- **keyboard/keyboard.cpp**: Implementation of keyboard functions, keymaps, and I2C request handling.
- **keyboard/keyboard.ino**: Program to read the key matrix and send key information over I2C. This is the firmware for the keyboard.

## Contributing

Contributions are both encouraged and greatly appreciated, more information can be found on the [Contributing](CONTRIBUTING.md) page.

## License

This project is licensed under the MIT License. See the LICENSE file for details.