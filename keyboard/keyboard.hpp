/**
 * @file      keyboard.hpp
 * @brief     Header file for keyboard functions and keymaps.
 * @author    hreikin (hreikin@gmail.com)
 * @license   MIT
 * @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
 * @date      2025-03-07
 */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <Arduino.h>
#include <Wire.h>

// i2c address
#define I2C_DEV_ADDR 0x55
// pins
#define KEYBOARD_BACKLIGHT_PIN 9
#define SDA 2
#define SCL 10
// brightness settings
#define KEYBOARD_BRIGHTNESS_CH 0      // ledc channel
#define KEYBOARD_BRIGHTNESS_FREQ 1000 // ledc Frequency
#define KEYBOARD_BRIGHTNESS_RES 8     // ledc Resolution_bits
#define KEYBOARD_BRIGHTNESS_MAX 255
#define KEYBOARD_BRIGHTNESS_MIN 0
#define KEYBOARD_BRIGHTNESS_DEFAULT 128
#define KEYBOARD_BRIGHTNESS_STEP 32
// delays
#define DEBOUNCE_DELAY 50    // 50 milliseconds debounce delay
#define KEY_REPEAT_DELAY 200 // 200 milliseconds key repeat delay
// brightness commands
#define FUNCTION_TOGGLE 0x01
#define FUNCTION_UP 0x02
#define FUNCTION_DOWN 0x03
// pins array sizes
#define ROW_COUNT 5
#define COL_COUNT 7
// keyInfo array size
#define KEY_INFO_SIZE 8
// keyInfo values
#define EMPTY 0x00
#define ERROR 0x01
// rows and cols for the modifier keys
#define ALT_ROW 0
#define ALT_COL 4
#define CTRL_ROW 2
#define CTRL_COL 3
#define SHIFT_ROW 1
#define SHIFT_COL 6
#define SYM_ROW 0
#define SYM_COL 2
// HID modifier bitmasks
#define MODIFIER_ALT 0x04
#define MODIFIER_CTRL 0x01
#define MODIFIER_SHIFT 0x02
#define MODIFIER_SYM 0x08 // Use mask value for LEFT_GUI key
// HID keycodes
#define KEY_BACKSPACE 0x2a   // Keyboard DELETE (Backspace)
#define KEY_ENTER 0x28       // Keyboard Return (ENTER)
#define KEY_SPACE 0x2c       // Keyboard Spacebar
#define KEY_DOLLAR_SIGN 0x4e // Keyboard Page Down, used as dollar/speaker
#define KEY_MIC 0x4b         // Keyboard Page Up, used as mic/0
#define KEY_A 0x04           // Keyboard a and A
#define KEY_B 0x05           // Keyboard b and B
#define KEY_C 0x06           // Keyboard c and C
#define KEY_D 0x07           // Keyboard d and D
#define KEY_E 0x08           // Keyboard e and E
#define KEY_F 0x09           // Keyboard f and F
#define KEY_G 0x0a           // Keyboard g and G
#define KEY_H 0x0b           // Keyboard h and H
#define KEY_I 0x0c           // Keyboard i and I
#define KEY_J 0x0d           // Keyboard j and J
#define KEY_K 0x0e           // Keyboard k and K
#define KEY_L 0x0f           // Keyboard l and L
#define KEY_M 0x10           // Keyboard m and M
#define KEY_N 0x11           // Keyboard n and N
#define KEY_O 0x12           // Keyboard o and O
#define KEY_P 0x13           // Keyboard p and P
#define KEY_Q 0x14           // Keyboard q and Q
#define KEY_R 0x15           // Keyboard r and R
#define KEY_S 0x16           // Keyboard s and S
#define KEY_T 0x17           // Keyboard t and T
#define KEY_U 0x18           // Keyboard u and U
#define KEY_V 0x19           // Keyboard v and V
#define KEY_W 0x1a           // Keyboard w and W
#define KEY_X 0x1b           // Keyboard x and X
#define KEY_Y 0x1c           // Keyboard y and Y
#define KEY_Z 0x1d           // Keyboard z and Z

enum KeyState
{
    NOT_PRESSED,
    PRESSED,
    HELD,
    RELEASED
};

extern unsigned long keyRepeatStart;
extern bool backlightState;
extern bool sendFlag;
extern uint8_t modifierState;
extern uint8_t currentBrightness;
extern uint8_t rows[ROW_COUNT];
extern uint8_t cols[COL_COUNT];
extern uint8_t keyInfo[KEY_INFO_SIZE];   // modifier masks, reserved byte, keycode 1, keycode 2, keycode 3, keycode 4, keycode 5, keycode 6
extern uint8_t emptyData[KEY_INFO_SIZE]; // empty array to send when no key is pressed, also used to reset the keyInfo array
extern bool lastValue[ROW_COUNT][COL_COUNT];
extern char defaultKeymap[ROW_COUNT][COL_COUNT];

/**
 * @brief Sets the keyboard backlight brightness.
 *
 * @param command The command to set the brightness (toggle, up, down).
 */
void setKeyboardBrightness(int command);

/**
 * @brief Prints the key information.
 *
 * @param data The key data array.
 */
void printKeyInfo(uint8_t data[KEY_INFO_SIZE]);

/**
 * @brief Checks if a key was released.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key was released, false otherwise.
 */
bool keyReleased(int rowIndex, int colIndex);

/**
 * @brief Checks if a key is being held.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key is being held, false otherwise.
 */
bool keyHeld(int rowIndex, int colIndex);

/**
 * @brief Checks if a key was pressed.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key was pressed, false otherwise.
 */
bool keyPressed(int rowIndex, int colIndex);

/**
 * @brief Checks if a key is not pressed.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key is not pressed, false otherwise.
 */
bool keyNotPressed(int rowIndex, int colIndex);

/**
 * @brief Sets the modifiers and keycodes in the keyInfo array.
 *
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void keyDownEvent(int rowIndex, int colIndex);

/**
 * @brief Reads the key matrix, updates the key states and handles the key down events.
 */
void readKeyMatrix();

/**
 * @brief Sends the key information over I2C.
 */
void sendKeyInfo();

/**
 * @brief Sets the keyboard backlight brightness.
 * 
 * @param command The command to set the brightness (toggle, up, down).
 */
void setKeyboardBrightness(uint8_t command);

/**
 * @brief Handles resetting the keymap index.
 */
void autoResetKeymapIndex();

/**
 * @brief Sets keyInfo to the correct character for a specific key, from the default keymap only.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void setDefaultCharacter(int rowIndex, int colIndex);

/**
 * @brief Sets keyInfo to the correct character for a specific key, from the symbol keymaps only.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void setSymbolCharacter(int rowIndex, int colIndex);

/**
 * @brief Handles the character for a specific key.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void handleCharacter(int rowIndex, int colIndex);

#endif // KEYBOARD_HPP