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
// // TODO: Should space be NULL or tab ? should $ be NULL ?
char capsKeymap[5][7] = {
    {0x51, 0x57, NULL, 0x41, NULL, 0x09, NULL},   // { 'Q', 'W', NULL, 'A', NULL, '[tab]', NULL }
    {0x45, 0x53, 0x44, 0x50, 0x58, 0x5A, NULL},   // { 'E', 'S', 'D', 'P', 'X', 'Z', NULL }
    {0x52, 0x47, 0x54, NULL, 0x56, 0x43, 0x46},   // { 'R', 'G', 'T', NULL, 'V', 'C', 'F' }
    {0x55, 0x48, 0x59, NULL, 0x42, 0x4E, 0x4A},   // { 'U', 'H', 'Y', NULL, 'B', 'N', 'J' }
    {0x4F, 0x4C, 0x49, NULL, NULL, 0x4D, 0x4B}    // { 'O', 'L', 'I', NULL, NULL, 'M', 'K' }
};
// // TODO: Should space be NULL or work as `ctrl + space` ? should $ be NULL ?
char ctrlKeymap[5][7] = {
    {0x11, 0x17, NULL, 0x01, NULL, NULL, NULL},    // { 'q', 'w', NULL, 'a', NULL, NULL, NULL }
    {0x05, 0x13, 0x04, 0x10, 0x18, 0x1A, NULL},    // { 'e', 's', 'd', 'p', 'x', 'z', NULL }
    {0x12, 0x07, 0x14, NULL, 0x16, 0x03, 0x06},    // { 'r', 'g', 't', NULL, 'v', 'c', 'f' }
    {0x15, 0x08, 0x19, NULL, 0x02, 0x0E, 0x0A},    // { 'u', 'h', 'y', NULL, 'b', 'n', 'j' }
    {0x0F, 0x0C, 0x09, NULL, NULL, 0x0D, 0x0B}     // { 'o', 'l', 'i', NULL, NULL, 'm', 'k' }
};
// TODO: Add other symbol keymaps as needed
char symbolKeymap1[5][7] = {       // index = 1
    {0x23, 0x31, NULL, 0x2A, NULL, NULL, 0x30},    // { '#', '1', NULL, '*', NULL, NULL, '0' },
    {0x32, 0x34, 0x35, 0x40, 0x38, 0x37, NULL},    // { '2', '4', '5', '@', '8', '7', NULL },
    {0x33, 0x2F, 0x28, NULL, 0x3F, 0x39, 0x36},    // { '3', '/', '(', NULL, '?', '9', '6' },
    {0x5F, 0x3A, 0x29, NULL, 0x21, 0x2C, 0x3B},    // { '_', ':', ')', NULL, '!', ',', ';' },
    {0x2B, 0x22, 0x2D, NULL, NULL, 0x2E, 0x27}     // { '+', '"', '-', NULL, NULL, '.', '\'' }
};
bool altToggle = false;
bool micToggle = false;
bool speakerToggle = false;
bool capsToggle = false;
bool ctrlToggle = false;
bool symbolToggle = false;
bool symbolLock = false;
bool backlightState = false;
bool sendFlag = false;
uint8_t keymapIndex = 0;   // default_keymap = 0, symbolKeymap1 = 1, symbol_keymap2 = 2, etc.
uint8_t keyInfo[4] = {0x00, false, false, false};    // key_value, alt, mic, speaker
uint8_t sendData[4] = {0x00, false, false, false};

/*
* Dynamically modify backlight brightness at runtime
* Brightness Range: 0 ~ 255
*/
uint8_t kbBrightnessDuty = KB_BRIGHTNESS_BOOT_DUTY;

/*
* Set the default backlight brightness level. If the user sets the backlight to 0
* via setKeyboardBrightness, the default brightness is used when pressing ALT+B,
* rather than the backlight brightness level set by the user. This ensures that
* pressing ALT+B can respond to the backlight being turned on and off normally.
* Brightness Range: 30 ~ 255
*/
uint8_t kbBrightnessSettingDuty = KB_BRIGHTNESS_DEFAULT_DUTY;    //Alt+B default duty , is duty is zero , use setting duty

// TODO: Refactor to use Wire.write() instead of Wire.print() and the key_info array
void onRequest()
{
    if (comdata_flag) {
        Wire.write(comdata, sizeof(comdata));
        comdata_flag = false;
        Serial.print("comdata : ");
        for (int i = 0; i < 4; i++) {
            Serial.print(comdata[i]);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        uint8_t emptyData[4] = {0x00, 0x00, 0x00, 0x00}; // Create a temporary array
        Wire.write(emptyData, sizeof(emptyData)); // Use the temporary array
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
    return symbol_keymap1[colIndex][rowIndex] != NULL || caps_keymap[colIndex][rowIndex] != NULL || default_keymap[colIndex][rowIndex] != NULL;
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
            // key 3,3 is the enter key
            if (keyPressed(3, 3)) {
                Serial.println("enter (enter)");
                key_info[0] = 0x0D;
                comdata_flag = true;
            }
            // key 4,3 is the backspace key
            if (keyPressed(4, 3)) {
                Serial.println("backspace (backspace)");
                key_info[0] = 0x08;
                comdata_flag = true;
            }
            // if both shifts are pressed, set keymap_index to 1, reset to 0 if pressed a second time
            if (keyPressed(1, 6) && keyPressed(2, 3)) {
                Serial.println("caps (lshift+rshift)");
                if (keymap_index == 1) {
                    keymap_index = 0;
                } else {
                    keymap_index = 1;
                }
            }
            // if `alt+c` set keymap_index to 2, reset to 0 if pressed a second time
            if (keyHeld(0, 4) && keyPressed(2, 5)) { //Alt+C
                Serial.println("ctrl (alt+c)");
                if (keymap_index == 2) {
                    keymap_index = 0;
                } else {
                    keymap_index = 2;
                }
            }
            // if `sym` is pressed, set keymap_index to 3, reset to 0 if pressed a second time
            // TODO: when extra symbol_keymaps are added in the future add a check of the 
            // TODO: keymap_index's value to see if you should increase by one or set to 3 or 
            // TODO: cycle back to 0
            if (keyHeld(0, 2)) {
                Serial.println("sym (sym)");
                if (keymap_index == 3) {
                    keymap_index = 0;
                } else {
                    keymap_index = 3;
                }
            }
            // if `alt+b` is pressed, toggle the backlight on and off
            if (keyHeld(0, 4) && keyPressed(3, 4)) { //Alt+B
                Serial.println("Alt+B");
                // If the software sets the duty cycle to 0, then the value set
                // by the ATL+B register is used to ensure that ALT+B can normally light up the backlight.
                if (BL_state) {
                    BL_state = false;
                    ledcWrite(KB_BRIGHTNESS_CH, 0); //turn off
                } else {
                    BL_state = true;
                    if (kb_brightness_duty == 0) {
                        Serial.println("User set bl duty is zero,use setting duty");
                        ledcWrite(KB_BRIGHTNESS_CH, kb_brightness_setting_duty);
                    } else {
                        Serial.println("Duty is not zero ,use user setting bl value");
                        ledcWrite(KB_BRIGHTNESS_CH, kb_brightness_duty);
                    }
                }
                comdata_flag = false;   //Don't send char
            }
            // we only want to print if the key is pressed and it is a printable character
            if (keyPressed(colIndex, rowIndex) && isPrintableKey(colIndex, rowIndex)) {
                // if keymap_index is 0, use default_keymap,
                if (keymap_index == 0) {
                    // keys 1,6 and 2,3 are Shift keys, so we want to upper case if either is held down while selecting the key
                    if (keyHeld(1, 6) || keyHeld(2, 3)) {
                        key_info[0] = caps_keymap[colIndex][rowIndex];
                    } else {
                        key_info[0] = default_keymap[colIndex][rowIndex];
                    }
                }
                // if keymap_index is 1, use caps_keymap
                else if (keymap_index == 1) {
                    key_info[0] = caps_keymap[colIndex][rowIndex];
                }
                // if keymap_index is 2, use ctrl_keymap
                else if (keymap_index == 2) {
                    key_info[0] = ctrl_keymap[colIndex][rowIndex];
                }
                // if keymap_index is 3, use symbol_keymap1
                else if (keymap_index == 3) {
                    key_info[0] = symbol_keymap1[colIndex][rowIndex];
                }
                // print all the key_info array values
                for (int i = 0; i < 4; i++) {
                    Serial.print(key_info[i]);
                    Serial.print(" ");
                }
                Serial.println();
                memcpy(comdata, key_info, sizeof(key_info));
                comdata_flag = true;
                // TODO: Should i reset the keymap_index to 0 after sending the key_info ?
            }
        }
    }
}