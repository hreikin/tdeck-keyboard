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
#define KEY_REPEAT_DELAY                    100   // 100 milliseconds key repeat delay, should this be larger ?
#define MIN_KEYMAP_INDEX                    0
#define MAX_KEYMAP_INDEX                    8     // TODO: change this when more keymaps are added
#define COL_COUNT                           7
#define ROW_COUNT                           5
#define KEY_INFO_SIZE                       6

enum KeyState {
    NOT_PRESSED,
    PRESSED,
    HELD,
    RELEASED
};

extern unsigned long keyRepeatStart;
extern uint8_t currentBrightness;
extern uint8_t rows[];
extern uint8_t cols[];
extern bool lastValue[ROW_COUNT][COL_COUNT];
extern char defaultKeymap[ROW_COUNT][COL_COUNT];
extern char symbolKeymap1[ROW_COUNT][COL_COUNT];
extern char symbolKeymap2[ROW_COUNT][COL_COUNT];
extern char symbolKeymap3[ROW_COUNT][COL_COUNT];
extern char symbolKeymap4[ROW_COUNT][COL_COUNT];
extern char symbolKeymap5[ROW_COUNT][COL_COUNT];
extern char symbolKeymap6[ROW_COUNT][COL_COUNT];
extern char symbolKeymap7[ROW_COUNT][COL_COUNT];
extern KeyState keyStates[ROW_COUNT][COL_COUNT];
extern uint8_t keymapIndex;
extern bool altLock;
extern bool ctrlLock;
extern bool capsLock;
extern bool symbolLock;
extern bool backlightState;
extern bool sendDataFlag;
extern uint8_t keyInfo[KEY_INFO_SIZE];     // keyValue, alt, ctrl, shift, mic, speaker
extern uint8_t sendData[KEY_INFO_SIZE];    // keyValue, alt, ctrl, shift, mic, speaker
extern uint8_t emptyData[KEY_INFO_SIZE];   // empty array to send when no key is pressed

/**
 * @brief Handles I2C requests.
 */
void onRequest();

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
 * @brief Checks if a key exists in the keymap.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @param keymap The keymap to check.
 * @return true if the key exists in the keymap, false otherwise.
 */
bool doesKeyExistInKeymap(int rowIndex, int colIndex, char keymap[ROW_COUNT][COL_COUNT]);

/**
 * @brief Prints the key information.
 * 
 * @param data The key data array.
 */
void printKeyInfo(uint8_t data[KEY_INFO_SIZE]);

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

#endif // KEYBOARD_HPP