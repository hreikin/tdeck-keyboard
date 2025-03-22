/**
 * @file      keyboard.cpp
 * @brief     Implementation of keyboard functions and keymaps.
 * @author    hreikin (hreikin@gmail.com)
 * @license   MIT
 * @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
 * @date      2025-03-07
 */
#include "keyboard.hpp"

unsigned long keyRepeatStart = 0;
bool backlightState = true;
bool sendFlag = false;
uint8_t modifierState = EMPTY;
uint8_t currentBrightness = KEYBOARD_BRIGHTNESS_DEFAULT; // Default brightness level
uint8_t rows[] = {1, 4, 5, 11, 13};
uint8_t cols[] = {0, 3, 19, 12, 18, 6, 7};
uint8_t keyInfo[KEY_INFO_SIZE] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};   // modifier masks, reserved byte, keycode 1, keycode 2, keycode 3, keycode 4, keycode 5, keycode 6
uint8_t emptyData[KEY_INFO_SIZE] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}; // empty array to send when no key is pressed, also used to reset the keyInfo array
bool lastValue[ROW_COUNT][COL_COUNT];
KeyState keyStates[ROW_COUNT][COL_COUNT];
// { q, w, [sym],           a, [alt], [space],    [mic] }
// { e, s,     d,           p,     x,       z, [lshift] }
// { r, g,     t,    [rshift],     v,       c,        f }
// { u, h,     y,     [enter],     b,       n,        j }
// { o, l,     i, [backspace],     $,       m,        k }
char defaultKeymap[ROW_COUNT][COL_COUNT] = {
    {KEY_Q, KEY_W, MODIFIER_SYM, KEY_A, MODIFIER_ALT, KEY_SPACE, KEY_MIC},
    {KEY_E, KEY_S, KEY_D, KEY_P, KEY_X, KEY_Z, MODIFIER_SHIFT},
    {KEY_R, KEY_G, KEY_T, MODIFIER_CTRL, KEY_V, KEY_C, KEY_F},
    {KEY_U, KEY_H, KEY_Y, KEY_ENTER, KEY_B, KEY_N, KEY_J},
    {KEY_O, KEY_L, KEY_I, KEY_BACKSPACE, KEY_DOLLAR_SIGN, KEY_M, KEY_K}};

void setKeyboardBrightness(int command)
{
    if (command == FUNCTION_TOGGLE)
    {
        if (backlightState)
        {
            currentBrightness = KEYBOARD_BRIGHTNESS_MIN;
        }
        else
        {
            currentBrightness = KEYBOARD_BRIGHTNESS_DEFAULT;
        }
    }
    else if (command == FUNCTION_UP)
    {
        if (currentBrightness < KEYBOARD_BRIGHTNESS_MAX)
        {
            if (currentBrightness >= KEYBOARD_BRIGHTNESS_MAX - KEYBOARD_BRIGHTNESS_STEP)
            {
                currentBrightness = KEYBOARD_BRIGHTNESS_MAX;
            }
            else
            {
                currentBrightness += KEYBOARD_BRIGHTNESS_STEP;
            }
        }
    }
    else if (command == FUNCTION_DOWN)
    {
        if (currentBrightness > KEYBOARD_BRIGHTNESS_MIN)
        {
            if (currentBrightness <= KEYBOARD_BRIGHTNESS_MIN + KEYBOARD_BRIGHTNESS_STEP)
            {
                currentBrightness = KEYBOARD_BRIGHTNESS_MIN;
            }
            else
            {
                currentBrightness -= KEYBOARD_BRIGHTNESS_STEP;
            }
        }
    }
    // If the toggle is on/off and the user increments/decrements the brightness then ensure
    // the backlight state is set correctly
    if (currentBrightness > KEYBOARD_BRIGHTNESS_MIN)
    {
        backlightState = true;
    }
    else
    {
        backlightState = false;
    }
    ledcWrite(KEYBOARD_BRIGHTNESS_CH, currentBrightness);
}

void printKeyInfo(uint8_t data[KEY_INFO_SIZE])
{
    // print all the keyInfo array values
    Serial.print("modifier masks: ");
    Serial.println(data[0]);
    Serial.print("reserved byte: ");
    Serial.println(data[1]);
    Serial.print("keycode 1: ");
    Serial.println(data[2]);
    Serial.print("keycode 2: ");
    Serial.println(data[3]);
    Serial.print("keycode 3: ");
    Serial.println(data[4]);
    Serial.print("keycode 4: ");
    Serial.println(data[5]);
    Serial.print("keycode 5: ");
    Serial.println(data[6]);
    Serial.print("keycode 6: ");
    Serial.println(data[7]);
    Serial.println("************************************");
}

bool keyReleased(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == RELEASED;
}

bool keyHeld(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == HELD;
}

bool keyPressed(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == PRESSED;
}

bool keyNotPressed(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == NOT_PRESSED;
}

void keyDownEvent(int rowIndex, int colIndex)
{
    if (rowIndex == CTRL_ROW && colIndex == CTRL_COL)
    {
        keyInfo[0] |= MODIFIER_CTRL;
    }
    else if (rowIndex == SHIFT_ROW && colIndex == SHIFT_COL)
    {
        keyInfo[0] |= MODIFIER_SHIFT;
    }
    else if (rowIndex == ALT_ROW && colIndex == ALT_COL)
    {
        keyInfo[0] |= MODIFIER_ALT;
    }
    else if (rowIndex == SYM_ROW && colIndex == SYM_COL)
    {
        keyInfo[0] |= MODIFIER_SYM;
    }
    else
    {
        // TODO: implement logic to maintain order of key presses ?
        // handle key overflow by filling all spaces with an error value (except modifier mask and reserved byte)
        if (keyInfo[KEY_INFO_SIZE - 1] != EMPTY)
        {
            for (int i = 2; i < KEY_INFO_SIZE; i++)
            {
                // set all keycodes to an error value
                keyInfo[i] = ERROR;
            }
        }
        else
        {
            // set the keycode in the keyInfo array
            for (int i = 2; i < KEY_INFO_SIZE; i++)
            {
                // if the keycode is already set then break the loop
                if (keyInfo[i] == defaultKeymap[rowIndex][colIndex])
                {
                    break;
                }
                // find the first empty space in the keyInfo array and set the keycode then break the loop
                else if (keyInfo[i] == EMPTY)
                {
                    keyInfo[i] = defaultKeymap[rowIndex][colIndex];
                    break;
                }
            }
        }
    }
}

void readKeyMatrix()
{
    // iterate the columns
    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        // col: set to output to low
        uint8_t curRow = rows[rowIndex];
        pinMode(curRow, OUTPUT);
        digitalWrite(curRow, LOW);

        // row: iterate through the rows
        for (int colIndex = 0; colIndex < COL_COUNT; colIndex++) {
            uint8_t curCol = cols[colIndex];
            pinMode(curCol, INPUT_PULLUP);
            delay(1); // arduino is not fast enough to switch input/output modes so wait 1 ms

            bool buttonPressed = (digitalRead(curCol) == LOW);

            // Debounce logic so keys don't trigger multiple times
            if (buttonPressed != lastValue[rowIndex][colIndex]) {
                delay(DEBOUNCE_DELAY); // Wait for debounce delay
                buttonPressed = (digitalRead(curCol) == LOW); // Read the button state again
            }

            if (buttonPressed) {
                if (keyNotPressed(rowIndex, colIndex) || keyReleased(rowIndex, colIndex)) {
                    keyStates[rowIndex][colIndex] = PRESSED;
                } else {
                    keyStates[rowIndex][colIndex] = HELD;
                }
            } else {
                if (keyPressed(rowIndex, colIndex) || keyHeld(rowIndex, colIndex)) {
                    keyStates[rowIndex][colIndex] = RELEASED;
                } else {
                    keyStates[rowIndex][colIndex] = NOT_PRESSED;
                }
            }

            lastValue[rowIndex][colIndex] = buttonPressed;
            pinMode(curCol, INPUT);
        }
        // disable the column
        pinMode(curRow, INPUT);
    }
}

/**
 * @brief Sends the key information over I2C.
 */
void sendKeyInfo()
{
    memcpy(keyInfo, emptyData, KEY_INFO_SIZE); // clear the keyInfo array
    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        for (int colIndex = 0; colIndex < COL_COUNT; colIndex++) {
            // any key released
            if (keyPressed(rowIndex, colIndex)) {
                keyRepeatStart = millis(); // Set the keyRepeatStart to the current time
                // enter
                if (keyPressed(3, 3)) {
                    // backlight down (alt + enter)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_DOWN);
                    }
                    // tab (lshift + enter)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = HORIZONTAL_TABULATION;
                    }
                    // cycle symbol backward (sym + enter)
                    else if (keyHeld(0, 2)) {
                        if (keymapIndex == MIN_KEYMAP_INDEX) {
                            keymapIndex = MAX_KEYMAP_INDEX;
                        }
                        else {
                            keymapIndex--;
                        }
                    }
                    // enter
                    else {
                        keyInfo[0] = CARRIAGE_RETURN;
                    }
                }
                // space
                else if (keyPressed(0, 5)) {
                    // alt lock (alt + space)
                    if (keyHeld(0, 4)) {
                        altLock = !altLock;
                    }
                    // ctrl lock (rshift + space)
                    else if (keyHeld(2, 3)) {
                        ctrlLock = !ctrlLock;
                    }
                    // caps lock (lshift + space)
                    else if (keyHeld(1, 6)) {
                        capsLock = !capsLock;
                    }
                    // symbol lock (sym + space)
                    else if (keyHeld(0, 2)) {
                        symbolLock = !symbolLock;
                        if (keymapIndex > MIN_KEYMAP_INDEX && symbolLock == false) {
                            keymapIndex = MIN_KEYMAP_INDEX;
                        }
                    }
                    // space
                    else {
                        keyInfo[0] = 0x20;
                    }
                }
                // backspace
                else if (keyPressed(4, 3)) {
                    // backlight up (alt + backspace)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_UP);
                    }
                    // del (lshift + backspace)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = 0x7F;
                    }
                    // cycle symbol forward (sym + backspace)
                    else if (keyHeld(0, 2)) {
                        keymapIndex++;
                        if (keymapIndex > MAX_KEYMAP_INDEX) {
                            keymapIndex = MIN_KEYMAP_INDEX;
                            symbolLock = false;  // reset symbol lock when all symbol keymaps have been cycled through
                        }
                    }
                    // backspace
                    else {
                        keyInfo[0] = BACKSPACE;
                    }
                }
                // mic/0
                else if (keyPressed(0, 6)) {
                    // mic toggle (alt + mic)
                    if (keyHeld(0, 4)) {
                        keyInfo[0] = FUNCTION_TOGGLE;
                        keyInfo[5] = true;
                    }
                    // mic volume down (lshift + mic)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = FUNCTION_DOWN;
                        keyInfo[5] = true;
                    }
                    // mic volume up (rshift + mic)
                    else if (keyHeld(2, 3)) {
                        keyInfo[0] = FUNCTION_UP;
                        keyInfo[5] = true;
                    }
                    // the below items are contained within the keymaps but appear here as well due to key combination usage
                    // 0
                    else if (keymapIndex == 1) {
                        keyInfo[0] = DIGIT_ZERO;
                    }
                    // nbsp
                    else if (keymapIndex == 2) {
                        keyInfo[0] = NO_BREAK_SPACE;
                    }
                }
                // $/speaker
                else if (keyPressed(4, 4)) {
                    // speaker toggle (alt + $)
                    if (keyHeld(0, 4)) {
                        keyInfo[0] = FUNCTION_TOGGLE;
                        keyInfo[6] = true;
                    }
                    // speaker volume down (lshift + $)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = FUNCTION_DOWN;
                        keyInfo[6] = true;
                    }
                    // speaker volume up (rshift + $)
                    else if (keyHeld(2, 3)) {
                        keyInfo[0] = FUNCTION_UP;
                        keyInfo[6] = true;
                    }
                    // the below items are contained within the keymaps but appear here as well due to key combination usage
                    // $
                    else if (keymapIndex == 0) {
                        keyInfo[0] = DOLLAR_SIGN;
                    }
                    // ¢
                    else if (keymapIndex == 1) {
                        keyInfo[0] = CENT_SIGN;
                    }
                    // ₧
                    else if (keymapIndex == 2) {
                        keyInfo[0] = PESETA_SIGN;
                    }
                    // ═
                    else if (keymapIndex == 6) {
                        keyInfo[0] = BOX_DRAWINGS_DOUBLE_HORIZONTAL;
                    }
                    // EOT
                    else if (keymapIndex == 7) {
                        keyInfo[0] = END_OF_TRANSMISSION;
                    }
                    // US
                    else if (keymapIndex == 8) {
                        keyInfo[0] = UNIT_SEPARATOR;
                    }
                }
                // rshift
                else if (keyPressed(2, 3)) {
                    // backlight toggle (alt + rshift)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_TOGGLE);
                    }
                }
                // a-z key, alt, ctrl, shift, alt lock, ctrl lock, caps lock, symbol (held)
                else {
                    handleCharacter(rowIndex, colIndex);
                }
            }
            // a-z key (held), alt, ctrl, shift, alt lock, ctrl lock, caps lock, symbol (held)
            else if (keyHeld(rowIndex, colIndex) && (millis() - keyRepeatStart > KEY_REPEAT_DELAY)) {
                handleCharacter(rowIndex, colIndex);
            }
        }
    }
    // if keyInfo array is not empty, print the data over serial
    if (keyInfo[0] != 0x00 || keyInfo[1] != 0x00 || keyInfo[2] != 0x00 || keyInfo[3] != 0x00 || keyInfo[4] != 0x00 || keyInfo[5] != 0x00 || keyInfo[6] != 0x00)
    {
        printKeyInfo(keyInfo);
        sendDataFlag = true;
    }
    // if the sendDataFlag is true then copy the keyInfo array to the sendData array which gets sent by the onRequest function
    if (sendDataFlag) {
        memcpy(sendData, keyInfo, KEY_INFO_SIZE);
    }
}