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

#define I2C_DEV_ADDR                        0x55
#define KEYBOARD_BACKLIGHT_PIN              9
#define SDA                                 2
#define SCL                                 10
#define KEYBOARD_BRIGHTNESS_CH              0     // ledc channel
#define KEYBOARD_BRIGHTNESS_FREQ            1000  // ledc Frequency
#define KEYBOARD_BRIGHTNESS_RES             8     // ledc Resolution_bits
#define KEYBOARD_BRIGHTNESS_MAX             255
#define KEYBOARD_BRIGHTNESS_MIN             0
#define KEYBOARD_BRIGHTNESS_DEFAULT         119
#define KEYBOARD_BRIGHTNESS_STEP            17
#define FUNCTION_TOGGLE                     0x01
#define FUNCTION_DOWN                       0x02
#define FUNCTION_UP                         0x03
#define DEBOUNCE_DELAY                      50    // 50 milliseconds debounce delay

enum KeyState {
    NOT_PRESSED,
    PRESSED,
    HELD,
    RELEASED
};

extern uint8_t currentBrightness;
extern uint8_t rows[];
extern const int rowCount;

extern uint8_t cols[];
extern const int colCount;

extern bool lastValue[5][7];
extern char defaultKeymap[5][7];
extern char symbolKeymap1[5][7];
extern char symbolKeymap2[5][7];
extern char symbolKeymap3[5][7];
extern char symbolKeymap4[5][7];
extern char symbolKeymap5[5][7];
extern char symbolKeymap6[5][7];
extern char symbolKeymap7[5][7];
extern uint8_t keymapIndex;
extern bool altLock;
extern bool ctrlLock;
extern bool capsLock;
extern bool symbolLock;
extern bool backlightState;
extern bool sendDataFlag;
extern uint8_t sendData[6];    // keyValue, alt, ctrl, shift, mic, speaker
extern uint8_t emptyData[6];   // empty array to send when no key is pressed
extern KeyState keyStates[5][7];

/**
 * @brief Handles I2C requests.
 */
void onRequest();

/**
 * @brief Checks if a key was released.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key was released, false otherwise.
 */
bool keyReleased(int colIndex, int rowIndex);

/**
 * @brief Checks if a key is being held.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key is being held, false otherwise.
 */
bool keyHeld(int colIndex, int rowIndex);

/**
 * @brief Checks if a key was pressed.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key was pressed, false otherwise.
 */
bool keyPressed(int colIndex, int rowIndex);

/**
 * @brief Checks if a key is not pressed.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key is not pressed, false otherwise.
 */
bool keyNotPressed(int colIndex, int rowIndex);

/**
 * @brief Checks if a key exists in the keymap.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @param keymap The keymap to check.
 * @return true if the key exists in the keymap, false otherwise.
 */
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[5][7]);

/**
 * @brief Prints the key information.
 * 
 * @param data The key data array.
 */
void printKeyInfo(uint8_t data[6]);

/**
 * @brief Reads the key matrix and updates the key states.
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

#endif // KEYBOARD_HPP