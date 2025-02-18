#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <Arduino.h>
#include <Wire.h>

#define I2C_DEV_ADDR                        0x55
#define keyboard_BL_PIN                     9
#define SDA                                 2
#define SCL                                 10
#define KB_BRIGHTNESS_CH                    0
#define KB_BRIGHTNESS_FREQ                  1000
#define KB_BRIGHTNESS_RES                   8     //Resolution_bits
#define KB_BRIGHTNESS_BOOT_DUTY             0
#define KB_BRIGHTNESS_DEFAULT_DUTY          127   //Alt+B default duty , is duty is zero , use setting duty

#define LILYGO_KB_BRIGHTNESS_CMD            0x01
#define LILYGO_KB_ALT_B_BRIGHTNESS_CMD      0x02

extern uint8_t rows[];
extern const int rowCount;

extern uint8_t cols[];
extern const int colCount;

extern bool keys[5][7];
extern bool lastValue[5][7];
extern bool changedValue[5][7];
extern char default_keymap[5][7];
extern char caps_keymap[5][7];
extern char ctrl_keymap[5][7];
extern char symbol_keymap1[5][7];
extern uint8_t keymap_index;
extern bool alt_key;
extern bool mic_key;
extern bool speaker_key;
extern uint8_t key_info[4];
extern bool BL_state;
extern bool comdata_flag;
extern char comdata;
extern uint8_t kb_brightness_duty;
extern uint8_t kb_brightness_setting_duty;

void onRequest();
void onReceive(int len);
bool keyPressed(int colIndex, int rowIndex);
bool keyHeld(int colIndex, int rowIndex);
bool isPrintableKey(int colIndex, int rowIndex);
void readKeyMatrix();
void sendKeyInfo();

#endif // KEYBOARD_HPP