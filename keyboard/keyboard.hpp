/**
* @file      keyboard.hpp
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
#define FUNCTION_UP                         0x02
#define FUNCTION_DOWN                       0x03

#define DEBOUNCE_DELAY 50 // 50 milliseconds debounce delay

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

extern bool keys[5][7];
extern bool lastValue[5][7];
extern bool changedValue[5][7];
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
extern uint8_t sendData[5];    // keyValue, alt, ctrl, mic, speaker
extern KeyState keyStates[5][7];

void onRequest();
void onReceive(int len);
bool keyReleased(int colIndex, int rowIndex);
bool keyHeld(int colIndex, int rowIndex);
bool keyPressed(int colIndex, int rowIndex);
bool keyNotPressed(int colIndex, int rowIndex);
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[5][7]);
void printKeyInfo(uint8_t data[5]);
void readKeyMatrix();
void sendKeyInfo();

#endif // KEYBOARD_HPP