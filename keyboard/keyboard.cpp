#include "keyboard.hpp"

uint8_t rows[] = {0, 3, 19, 12, 18, 6, 7};
const int rowCount = sizeof(rows) / sizeof(rows[0]);

uint8_t cols[] = {1, 4, 5, 11, 13};
const int colCount = sizeof(cols) / sizeof(cols[0]);

bool keys[5][7];
bool lastValue[5][7];
bool changedValue[5][7];
char default_keymap[5][7] = {       // index = 0  // keys                                           // null
    {0x71, 0x77, NULL, 0x61, NULL, 0x20, NULL},   // { 'q', 'w', NULL, 'a', NULL, ' ', NULL }       // sym, alt, mic
    {0x65, 0x73, 0x64, 0x70, 0x78, 0x7A, NULL},   // { 'e', 's', 'd', 'p', 'x', 'z', NULL }         // lshift
    {0x72, 0x67, 0x74, NULL, 0x76, 0x63, 0x66},   // { 'r', 'g', 't', NULL, 'v', 'c', 'f' }         // rshift
    {0x75, 0x68, 0x79, NULL, 0x62, 0x6E, 0x6A},   // { 'u', 'h', 'y', NULL, 'b', 'n', 'j' }         // enter
    {0x6F, 0x6C, 0x69, NULL, 0x24, 0x6D, 0x6B}    // { 'o', 'l', 'i', NULL, '$', 'm', 'k' }         // backspace
};
char capsKeymap[5][7] = {                         // keys                                           // null
    {0x51, 0x57, NULL, 0x41, NULL, 0x09, NULL},   // { 'Q', 'W', NULL, 'A', NULL, '[tab]', NULL }   // sym, alt, mic
    {0x45, 0x53, 0x44, 0x50, 0x58, 0x5A, NULL},   // { 'E', 'S', 'D', 'P', 'X', 'Z', NULL }         // lshift
    {0x52, 0x47, 0x54, NULL, 0x56, 0x43, 0x46},   // { 'R', 'G', 'T', NULL, 'V', 'C', 'F' }         // rshift
    {0x55, 0x48, 0x59, NULL, 0x42, 0x4E, 0x4A},   // { 'U', 'H', 'Y', NULL, 'B', 'N', 'J' }         // enter
    {0x4F, 0x4C, 0x49, NULL, NULL, 0x4D, 0x4B}    // { 'O', 'L', 'I', NULL, NULL, 'M', 'K' }        // backspace, $ (speaker)
};
char ctrlKeymap[5][7] = {                          // keys                                          // null
    {0x11, 0x17, NULL, 0x01, NULL, NULL, NULL},    // { 'q', 'w', NULL, 'a', NULL, NULL, NULL }     // sym, alt, space, mic
    {0x05, 0x13, 0x04, 0x10, 0x18, 0x1A, NULL},    // { 'e', 's', 'd', 'p', 'x', 'z', NULL }        // lshift
    {0x12, 0x07, 0x14, NULL, 0x16, 0x03, 0x06},    // { 'r', 'g', 't', NULL, 'v', 'c', 'f' }        // rshift
    {0x15, 0x08, 0x19, NULL, 0x02, 0x0E, 0x0A},    // { 'u', 'h', 'y', NULL, 'b', 'n', 'j' }        // enter
    {0x0F, 0x0C, 0x09, NULL, NULL, 0x0D, 0x0B}     // { 'o', 'l', 'i', NULL, NULL, 'm', 'k' }       // backspace, $ (speaker)
};
// TODO: Add other symbol keymaps as needed
char symbolKeymap1[5][7] = {        // index = 1   // keys                                          //null
    {0x23, 0x31, NULL, 0x2A, NULL, NULL, 0x30},    // { '#', '1', NULL, '*', NULL, NULL, '0' },     // sym, alt, space
    {0x32, 0x34, 0x35, 0x40, 0x38, 0x37, NULL},    // { '2', '4', '5', '@', '8', '7', NULL },       // lshift
    {0x33, 0x2F, 0x28, NULL, 0x3F, 0x39, 0x36},    // { '3', '/', '(', NULL, '?', '9', '6' },       // rshift
    {0x5F, 0x3A, 0x29, NULL, 0x21, 0x2C, 0x3B},    // { '_', ':', ')', NULL, '!', ',', ';' },       // enter
    {0x2B, 0x22, 0x2D, NULL, NULL, 0x2E, 0x27}     // { '+', '"', '-', NULL, NULL, '.', '\'' }      // backspace, $ (speaker)
};
bool caps = false;
bool symbolLock = false;
bool backlightState = false;
bool sendFlag = false;
uint8_t keymapIndex = 0;                                     // default_keymap = 0, symbolKeymap1 = 1, symbol_keymap2 = 2, etc.
uint8_t sendData[5] = {0x00, false, false, false, false};    // key_value, alt, ctrl, mic, speaker

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

void onRequest()
{
    if (sendFlag) {
        Wire.write(sendData, sizeof(sendData));
        sendFlag = false;
        Serial.print("sendData : ");
        for (int i = 0; i < 5; i++) {
            Serial.print(sendData[i]);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        // TODO: Make this a global variable and use it here ?
        uint8_t emptyData[5] = {0x00, 0x00, 0x00, 0x00, 0x00}; // Create a temporary array
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
                kbBrightnessDuty = duty;
                // Serial.printf("B:%d", duty);
                ledcWrite(KB_BRIGHTNESS_CH, duty);
                if (duty > 0) {
                    backlightState = true;
                } else if (duty == 0) {
                    backlightState = false;
                }
            }
        }
        case LILYGO_KB_ALT_B_BRIGHTNESS_CMD: {
            int duty = Wire.read();
            if (duty > 30) {
                kbBrightnessSettingDuty = duty;
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

// // TODO: Does this need an argument adding (keymap or keymapIndex) so it knows which keymap to check or use ?
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[5][7])
{
    return keymap[colIndex][rowIndex] != NULL;
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
            // caps (toggle) = lshift+rshift
            if ((keyHeld(1, 6) && keyPressed(2, 3)) || (keyHeld(2, 3) && keyPressed(1, 6))) {
                capsToggle = !capsToggle;
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // alt + key = alt + [a-z]
            else if (keyHeld(0, 4) && keyPressed(colIndex, rowIndex) && doesKeyExistInKeymap(colIndex, rowIndex, ctrlKeymap)) {
                keyInfo[0] = ctrlKeymap[colIndex][rowIndex];
                keyInfo[1] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[1] = false;
            }
            // alt (toggle) = alt
            else if (keyPressed(0, 4)) {
                altToggle = !altToggle;
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // ctrl + key = lshift+alt + [a-z]
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyHeld(0, 4) && keyPressed(colIndex, rowIndex) && doesKeyExistInKeymap(colIndex, rowIndex, ctrlKeymap)) {
                keyInfo[0] = ctrlKeymap[colIndex][rowIndex];
                sendFlag = true;
                keyInfo[0] = 0x00;
            }
            // ctrl (toggle) = lshift+alt or rshift+alt
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyPressed(0, 4)) {
                ctrlToggle = !ctrlToggle;
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // del = lshift+backspace or rshift+backspace
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyPressed(4, 3)) {
                keyInfo[0] = 0x7F;
                sendFlag = true;
                keyInfo[0] = 0x00;
            }
            // tab = lshift+space or rshift+space
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyPressed(0, 5)) {
                keyInfo[0] = 0x09;
                sendFlag = true;
                keyInfo[0] = 0x00;
            }
            // mic (toggle) = ctrlToggle enabled + mic
            else if (ctrlToggle && keyPressed(0, 6)) {
                keyInfo[0] = 0x01;
                keyInfo[2] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[2] = false;
            }
            // mic = lshift+alt+mic or rshift+alt+mic
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyHeld(0, 4) && keyPressed(0, 6)) {
                keyInfo[0] = 0x01;
                keyInfo[2] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[2] = false;
            }
            // mic volume up = lshift+mic
            else if (keyHeld(1, 6) && keyPressed(0, 6)) {
                keyInfo[0] = 0x02;
                keyInfo[2] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[2] = false;
            }
            // mic volume down = rshift+mic
            else if (keyHeld(2, 3) && keyPressed(0, 6)) {
                keyInfo[0] = 0x03;
                keyInfo[2] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[2] = false;
            }
            // speaker (enable via toggle) = ctrlToggle enabled + speaker
            else if (ctrlToggle && keyPressed(4, 6)) {
                keyInfo[0] = 0x01;
                keyInfo[3] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[3] = false;
            }
            // speaker = lshift+alt+speaker or rshift+alt+speaker
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyHeld(0, 4) && keyPressed(4, 6)) {
                keyInfo[0] = 0x01;
                keyInfo[3] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[3] = false;
            }
            // speaker volume up = lshift+speaker
            else if (keyHeld(1, 6) && keyPressed(4, 6)) {
                keyInfo[0] = 0x02;
                keyInfo[3] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[3] = false;
            }
            // speaker volume down = rshift+speaker
            else if (keyHeld(2, 3) && keyPressed(4, 6)) {
                keyInfo[0] = 0x03;
                keyInfo[3] = true;
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[3] = false;
            }
            // symbol cycle forward = sym
            else if (keyPressed(0, 2)) {
                symbolToggle = true;
                if (keymapIndex > 1) {     // TODO: Change this value when more symbol_keymaps are added
                    keymapIndex = 1;
                } else {
                    keymapIndex++;
                }
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // symbol cycle backward = lshift+sym or rshift+sym
            else if ((keyHeld(1, 6) || keyHeld(2, 3)) && keyPressed(0, 2)) {
                symbolToggle = true;
                if (keymapIndex < 1) {
                    keymapIndex = 1;       // TODO: Change this value when more symbol_keymaps are added
                } else {
                    keymapIndex--;
                }
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // symbol lock = alt+sym
            else if (keyHeld(0, 4) && keyPressed(0, 2)) {
                symbolToggle = true;
                symbolLock = !symbolLock;
                sendFlag = false;   //Don't send char, the next key pressed should trigger the last if statement
            }
            // backspace = backspace
            else if (keyPressed(4, 3)) {
                keyInfo[0] = 0x08;
                sendFlag = true;
                keyInfo[0] = 0x00;
            }
            // enter = enter
            else if (keyPressed(3, 3)) {
                keyInfo[0] = 0x0D;
                sendFlag = true;
                keyInfo[0] = 0x00;
            }
            // normal key = [a-z]
            else if (keyPressed(colIndex, rowIndex)) {
                if (capsToggle || (keyHeld(1, 6) || keyHeld(2, 3)) && doesKeyExistInKeymap(colIndex, rowIndex, capsKeymap)) {
                    keyInfo[0] = capsKeymap[colIndex][rowIndex];
                } else if (altToggle && doesKeyExistInKeymap(colIndex, rowIndex, ctrlKeymap)) {
                    keyInfo[0] = ctrlKeymap[colIndex][rowIndex];
                } else if (ctrlToggle && doesKeyExistInKeymap(colIndex, rowIndex, ctrlKeymap)) {
                    keyInfo[0] = ctrlKeymap[colIndex][rowIndex];
                // TODO: This needs work to choose the correct symbol_keymap based on the keymapIndex
                } else if (symbolToggle && (keymapIndex == 1)) {
                    keyInfo[0] = symbolKeymap1[colIndex][rowIndex];
                } else if (doesKeyExistInKeymap(colIndex, rowIndex, default_keymap)) {
                    keyInfo[0] = default_keymap[colIndex][rowIndex];
                }
                if (symbolLock == false) {
                    symbolToggle = false;
                    keymapIndex = 0;
                }
                // TODO: Does this need moving out of the if else block ?
                // print all the keyInfo array values
                for (int i = 0; i < 4; i++) {
                    Serial.print(keyInfo[i]);
                    Serial.print(" ");
                }
                Serial.println();
                // // TODO: Add this line to each if else block that sets sendFlag to true so that keyInfo can be reset but the correct info is sent by sendData ?
                memcpy(sendData, keyInfo, sizeof(keyInfo));
                // // TODO: Rename this to sendFlag ?
                sendFlag = true;
                keyInfo[0] = 0x00;
                keyInfo[1] = false;
                keyInfo[2] = false;
                keyInfo[3] = false;
            }
        }
    }
}