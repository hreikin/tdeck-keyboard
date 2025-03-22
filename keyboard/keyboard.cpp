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

/**
 * @brief Checks if a key was released.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key was released, false otherwise.
 */
bool keyReleased(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == RELEASED;
}

/**
 * @brief Checks if a key is being held.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key is being held, false otherwise.
 */
bool keyHeld(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == HELD;
}

/**
 * @brief Checks if a key was pressed.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key was pressed, false otherwise.
 */
bool keyPressed(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == PRESSED;
}

/**
 * @brief Checks if a key is not pressed.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @return true if the key is not pressed, false otherwise.
 */
bool keyNotPressed(int rowIndex, int colIndex)
{
    return keyStates[rowIndex][colIndex] == NOT_PRESSED;
}

/**
 * @brief Checks if a key exists in the keymap.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 * @param keymap The keymap to check.
 * @return true if the key exists in the keymap, false otherwise.
 */
bool doesKeyExistInKeymap(int rowIndex, int colIndex, char keymap[ROW_COUNT][COL_COUNT])
{
    return keymap[rowIndex][colIndex] != NULL;
}

/**
 * @brief Prints the key information.
 * 
 * @param data The key data array.
 */
void printKeyInfo(uint8_t data[KEY_INFO_SIZE])
{
    // print all the keyInfo array values
    Serial.print("char: ");
    Serial.println(data[0]);
    Serial.print("alt: ");
    Serial.println(data[1]);
    Serial.print("ctrl: ");
    Serial.println(data[2]);
    Serial.print("shift: ");
    Serial.println(data[3]);
    Serial.print("sym: ");
    Serial.println(data[4]);
    Serial.print("mic: ");
    Serial.println(data[5]);
    Serial.print("speaker: ");
    Serial.println(data[6]);
    Serial.println("************************************");
}

/**
 * @brief Handles resetting the keymap index.
 */
void autoResetKeymapIndex()
{
    if (symbolLock == false) {
        keymapIndex = MIN_KEYMAP_INDEX;
    }
}

/**
 * @brief Sets the default character for a key.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void setDefaultCharacter(int rowIndex, int colIndex)
{
    // modifiers, alt, ctrl, shift
    if (altLock || keyHeld(0, 4)) {
        keyInfo[1] = true;
    }
    if (ctrlLock || keyHeld(2, 3)) {
        keyInfo[2] = true;
    }
    // shift is not applied when caps lock is on unlike the others, this is intended so the host can differentiate between the two
    if (keyHeld(1, 6)) {
        keyInfo[3] = true;
    }
    // key value
    if (capsLock || keyHeld(1, 6)) {
        keyInfo[0] = defaultKeymap[rowIndex][colIndex] - 32;
    }
    else {
        keyInfo[0] = defaultKeymap[rowIndex][colIndex];
    }
}

/**
 * @brief Sets the symbol character for a key.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void setSymbolCharacter(int rowIndex, int colIndex)
{
    // symbol 1
    if ((keymapIndex == 1 || keyHeld(0, 2)) && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap1)) {
        keyInfo[0] = symbolKeymap1[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 2
    else if (keymapIndex == 2 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap2)) {
        keyInfo[0] = symbolKeymap2[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 3
    else if (keymapIndex == 3 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap3)) {
        keyInfo[0] = symbolKeymap3[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 4
    else if (keymapIndex == 4 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap4)) {
        keyInfo[0] = symbolKeymap4[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 5
    else if (keymapIndex == 5 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap5)) {
        keyInfo[0] = symbolKeymap5[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 6
    else if (keymapIndex == 6 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap6)) {
        keyInfo[0] = symbolKeymap6[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 7
    else if (keymapIndex == 7 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap7)) {
        keyInfo[0] = symbolKeymap7[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // symbol 7 special handling for NUL character
    else if (keymapIndex == 7 && (keyHeld(2, 4) || keyPressed(2, 4))) {
        keyInfo[0] = symbolKeymap7[rowIndex][colIndex];
        autoResetKeymapIndex();
        keyInfo[4] = true;  // set the symbol flag if it is the NUL character (not NULL from an empty space)
    }
    // symbol 8
    else if (keymapIndex == 8 && doesKeyExistInKeymap(rowIndex, colIndex, symbolKeymap8)) {
        keyInfo[0] = symbolKeymap8[rowIndex][colIndex];
        autoResetKeymapIndex();
    }
    // set the symbol flag if the character isnt NULL (special handling above for NUL character)
    if (keyInfo[0] != NULL) {
        keyInfo[4] = true;
    }
}

/**
 * @brief Handles the character for a specific key.
 * 
 * @param rowIndex The row index of the key.
 * @param colIndex The column index of the key.
 */
void handleCharacter(int rowIndex, int colIndex) {
    // a-z key, alt, ctrl, shift, alt lock, ctrl lock, caps lock, symbol (held)
    if ((keymapIndex == MIN_KEYMAP_INDEX || altLock || keyHeld(0, 4) || ctrlLock || keyHeld(2, 3) || capsLock || keyHeld(1, 6) || keyHeld(0, 2)) && doesKeyExistInKeymap(rowIndex, colIndex, defaultKeymap)) {
        if (keyHeld(0, 2)) {
            setSymbolCharacter(rowIndex, colIndex);
        }
        else {
            setDefaultCharacter(rowIndex, colIndex);
        }
    }
    // symbol
    else if (keymapIndex > MIN_KEYMAP_INDEX) {
        setSymbolCharacter(rowIndex, colIndex);
    }
}

/**
 * @brief Reads the key matrix and updates the key states.
 */
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