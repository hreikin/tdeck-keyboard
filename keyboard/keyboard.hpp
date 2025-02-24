#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <Arduino.h>
#include <Wire.h>

#define I2C_DEV_ADDR                        0x55
#define keyboard_BL_PIN                     9
#define SDA                                 2
#define SCL                                 10
#define KB_BRIGHTNESS_CH                    0     // ledc channel
#define KB_BRIGHTNESS_FREQ                  1000  // ledc Frequency
#define KB_BRIGHTNESS_RES                   8     // ledc Resolution_bits
#define KB_BRIGHTNESS_BOOT_DUTY             0
#define KB_BRIGHTNESS_DEFAULT_DUTY          127   // Alt+B default duty , is duty is zero , use setting duty

#define LILYGO_KB_BRIGHTNESS_CMD            0x01
#define LILYGO_KB_ALT_B_BRIGHTNESS_CMD      0x02

#define DEBOUNCE_DELAY 50 // 50 milliseconds debounce delay

extern uint8_t rows[];
extern const int rowCount;

extern uint8_t cols[];
extern const int colCount;

extern bool keys[5][7];
extern bool lastValue[5][7];
extern bool changedValue[5][7];
extern char default_keymap[5][7];
extern char capsKeymap[5][7];
extern char ctrlKeymap[5][7];
extern char symbolKeymap1[5][7];
extern uint8_t keymapIndex;
extern bool caps;
extern bool symbolLock;
extern bool backlightState;
extern bool sendFlag;
// TODO: change to char ?
extern uint8_t sendData[5];    // keyValue, alt, ctrl, mic, speaker
extern uint8_t kbBrightnessDuty;
extern uint8_t kbBrightnessSettingDuty;

void onRequest();
void onReceive(int len);
bool keyPressed(int colIndex, int rowIndex);
bool keyHeld(int colIndex, int rowIndex);
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[5][7]);
void printKeyInfo(uint8_t data[5]);
void readKeyMatrix();
void sendKeyInfo();

#endif // KEYBOARD_HPP