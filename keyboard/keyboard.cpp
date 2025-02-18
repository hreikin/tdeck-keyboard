/**
 * @file      Keyboard_ESP32C3.ino
 * @author    Koby Hale
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-04-11
 * @Revision  : 
 * * 2024-12-16 : Fixed issue https://github.com/Xinyuan-LilyGO/T-Deck/issues/69
 * * 2024-12-24 : Fixed issue https://github.com/Xinyuan-LilyGO/T-Deck/issues/70
 * * 2024-12-25   Added keyboard backlight control
 */
// holds the methods (readKeyMatrix, sendKeyInfo), callbacks (onRequest, onReceive) and helpers (isPressed, isHeld) definitions
#include "keyboard.hpp"

uint8_t rows[] = {0, 3, 19, 12, 18, 6, 7};
const int rowCount = sizeof(rows) / sizeof(rows[0]);

uint8_t cols[] = {1, 4, 5, 11, 13};
const int colCount = sizeof(cols) / sizeof(cols[0]);

bool keys[5][7];
bool lastValue[5][7];
bool changedValue[5][7];
char default_keymap[5][7] = {       // index = 0
    {0x71, 0x77, NULL, 0x61, NULL, 0x20, NULL},   // { 'q', 'w', NULL, 'a', NULL, ' ', NULL }
    {0x65, 0x73, 0x64, 0x70, 0x78, 0x7A, NULL},   // { 'e', 's', 'd', 'p', 'x', 'z', NULL }
    {0x72, 0x67, 0x74, NULL, 0x76, 0x63, 0x66},   // { 'r', 'g', 't', NULL, 'v', 'c', 'f' }
    {0x75, 0x68, 0x79, NULL, 0x62, 0x6E, 0x6A},   // { 'u', 'h', 'y', NULL, 'b', 'n', 'j' }
    {0x6F, 0x6C, 0x69, NULL, 0x24, 0x6D, 0x6B}    // { 'o', 'l', 'i', NULL, '$', 'm', 'k' }
};
// TODO: Should space be NULL or tab ?
char caps_keymap[5][7] = {          // index = 1
    {0x51, 0x57, NULL, 0x41, NULL, 0x20, NULL},   // { 'Q', 'W', NULL, 'A', NULL, ' ', NULL }
    {0x45, 0x53, 0x44, 0x50, 0x58, 0x5A, NULL},   // { 'E', 'S', 'D', 'P', 'X', 'Z', NULL }
    {0x52, 0x47, 0x54, NULL, 0x56, 0x43, 0x46},   // { 'R', 'G', 'T', NULL, 'V', 'C', 'F' }
    {0x55, 0x48, 0x59, NULL, 0x42, 0x4E, 0x4A},   // { 'U', 'H', 'Y', NULL, 'B', 'N', 'J' }
    {0x4F, 0x4C, 0x49, NULL, 0x24, 0x4D, 0x4B}    // { 'O', 'L', 'I', NULL, '$', 'M', 'K' }
};
// TODO: Should space be NULL or work as `ctrl + space` ?
char ctrl_keymap[5][7] = {           // index = 2
    {0x11, 0x17, NULL, 0x01, NULL, 0x20, NULL},    // { 'q', 'w', NULL, 'a', NULL, ' ', NULL }
    {0x05, 0x13, 0x04, 0x10, 0x18, 0x1A, NULL},    // { 'e', 's', 'd', 'p', 'x', 'z', NULL }
    {0x12, 0x07, 0x14, NULL, 0x16, 0x03, 0x06},    // { 'r', 'g', 't', NULL, 'v', 'c', 'f' }
    {0x15, 0x08, 0x19, NULL, 0x02, 0x0E, 0x0A},    // { 'u', 'h', 'y', NULL, 'b', 'n', 'j' }
    {0x0F, 0x0C, 0x09, NULL, 0x24, 0x0D, 0x0B}     // { 'o', 'l', 'i', NULL, '$', 'm', 'k' }
};
// TODO: Add other symbol keymaps as needed
char symbol_keymap1[5][7] = {        // index = 3
    {0x23, 0x31, NULL, 0x2A, NULL, NULL, 0x30},    // { '#', '1', NULL, '*', NULL, NULL, '0' },
    {0x32, 0x34, 0x35, 0x40, 0x38, 0x37, NULL},    // { '2', '4', '5', '@', '8', '7', NULL },
    {0x33, 0x2F, 0x28, NULL, 0x3F, 0x39, 0x36},    // { '3', '/', '(', NULL, '?', '9', '6' },
    {0x5F, 0x3A, 0x29, NULL, 0x21, 0x2C, 0x3B},    // { '_', ':', ')', NULL, '!', ',', ';' },
    {0x2B, 0x22, 0x2D, NULL, NULL, 0x2E, 0x27}     // { '+', '"', '-', NULL, NULL, '.', '\'' }
};
uint8_t keymap_index = 0;
bool alt_key = false;
bool mic_key = false;
bool speaker_key = false;
uint8_t key_info[4] = {0x00, alt_key, mic_key, speaker_key};    // key_value, alt, mic, speaker
bool BL_state = false;
bool comdata_flag = false;
char comdata;

/*
* Dynamically modify backlight brightness at runtime
* Brightness Range: 0 ~ 255
*/
uint8_t kb_brightness_duty = KB_BRIGHTNESS_BOOT_DUTY;

/*
* Set the default backlight brightness level. If the user sets the backlight to 0
* via setKeyboardBrightness, the default brightness is used when pressing ALT+B,
* rather than the backlight brightness level set by the user. This ensures that
* pressing ALT+B can respond to the backlight being turned on and off normally.
* Brightness Range: 30 ~ 255
*/
uint8_t kb_brightness_setting_duty = KB_BRIGHTNESS_DEFAULT_DUTY;    //Alt+B default duty , is duty is zero , use setting duty


void onRequest()
{
    if (comdata_flag) {
        Wire.print(comdata);
        comdata_flag = false;
        Serial.print("comdata :");
        Serial.println(comdata);
    } else {
        Wire.print((char)0x00);
    }
}

void onReceive(int len)
{
    // Serial.printf("onReceive[%d]: ", len);
    while (Wire.available()) {
        int cmd = Wire.read();
        switch (cmd) {
        case LILYGO_KB_BRIGHTNESS_CMD: {
            int duty = Wire.read();
            if (duty >= 0) {
                kb_brightness_duty = duty;
                // Serial.printf("B:%d", duty);
                ledcWrite(KB_BRIGHTNESS_CH, duty);
                if (duty > 0) {
                    BL_state = true;
                } else if (duty == 0) {
                    BL_state = false;
                }
            }
        }
        case LILYGO_KB_ALT_B_BRIGHTNESS_CMD: {
            int duty = Wire.read();
            if (duty > 30) {
                kb_brightness_setting_duty = duty;
            }
        }
        break;
        default:
            break;
        }
    }
    // Serial.println();
}

bool keyPressed(int colIndex, int rowIndex)
{
    return changedValue[colIndex][rowIndex] && keys[colIndex][rowIndex] == true;
}

bool keyHeld(int colIndex, int rowIndex)
{
    return keys[colIndex][rowIndex] == true;
}

bool isPrintableKey(int colIndex, int rowIndex)
{
    return symbol_keymap1[colIndex][rowIndex] != NULL || default_keymap[colIndex][rowIndex] != NULL;
}

void readKeyMatrix()
{
    int delayTime = 0;
    // iterate the columns
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        uint8_t  curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);

        // row: interate through the rows
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            uint8_t  rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            delay(1); // arduino is not fast enought to switch input/output modes so wait 1 ms

            bool buttonPressed = (digitalRead(rowCol) == LOW);

            keys[colIndex][rowIndex] = buttonPressed;
            if ((lastValue[colIndex][rowIndex] != buttonPressed)) {
                changedValue[colIndex][rowIndex] = true;
            } else {
                changedValue[colIndex][rowIndex] = false;
            }

            lastValue[colIndex][rowIndex] = buttonPressed;
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}

void sendKeyInfo()
{
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
        for (int colIndex = 0; colIndex < colCount; colIndex++) {
            // we only want to print if the key is pressed and it is a printable character
            if (keyPressed(colIndex, rowIndex) && isPrintableKey(colIndex, rowIndex)) {
                char toPrint;

                if (keyHeld(0, 2)) {
                    toPrint = char(symbol_keymap1[colIndex][rowIndex]);
                } else {
                    toPrint = char(default_keymap[colIndex][rowIndex]);
                }

                // keys 1,6 and 2,3 are Shift keys, so we want to upper case
                if (keyHeld(1, 6) || keyHeld(2, 3)) {
                    toPrint = (char)((int)toPrint - 32);
                }

                Serial.print(toPrint);

                comdata = toPrint;
                comdata_flag = true;

            }
        }
    }
}