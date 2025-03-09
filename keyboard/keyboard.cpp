/**
 * @file      keyboard.cpp
 * @brief     Implementation of keyboard functions and keymaps.
 * @author    hreikin (hreikin@gmail.com)
 * @license   MIT
 * @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
 * @date      2025-03-07
 */
#include "keyboard.hpp"

uint8_t rows[] = {0, 3, 19, 12, 18, 6, 7};
const int rowCount = sizeof(rows) / sizeof(rows[0]);

uint8_t cols[] = {1, 4, 5, 11, 13};
const int colCount = sizeof(cols) / sizeof(cols[0]);

bool lastValue[5][7];
KeyState keyStates[5][7];
// TODO: Ensure the keymaps match the tables in keyboard.md
// TODO: defaultKeymap, symbolKeymap1, symbolKeymap2, symbolKeymap3, symbolKeymap4, symbolKeymap5, symbolKeymap6, symbolKeymap7
// Keys wrapped in square brackets may require special handling due to mic/speaker functionality and other key combinations.
char defaultKeymap[5][7] = {                      // index = 0
    {0x71, 0x77, NULL, 0x61, NULL, NULL, NULL},   // { q, w, [sym],           a, [alt], [space],    [mic] }
    {0x65, 0x73, 0x64, 0x70, 0x78, 0x7A, NULL},   // { e, s,     d,           p,     x,       z, [lshift] }
    {0x72, 0x67, 0x74, NULL, 0x76, 0x63, 0x66},   // { r, g,     t,    [rshift],     v,       c,        f }
    {0x75, 0x68, 0x79, NULL, 0x62, 0x6E, 0x6A},   // { u, h,     y,     [enter],     b,       n,        j }
    {0x6F, 0x6C, 0x69, NULL, 0x24, 0x6D, 0x6B}    // { o, l,     i, [backspace],     $,       m,        k }
};
// TODO: Add other symbol keymaps as needed
char symbolKeymap1[5][7] = {                      // index = 1
    {0x23, 0x31, NULL, 0x2A, NULL, NULL, 0x30},   // { #, 1, [sym],           *, [alt], [space],        0 }
    {0x32, 0x34, 0x35, 0x40, 0x38, 0x37, NULL},   // { 2, 4,     5,           @,     8,       7, [lshift] }
    {0x33, 0x2F, 0x28, NULL, 0x3F, 0x39, 0x36},   // { 3, /,     (,    [rshift],     ?,       9,        6 }
    {0x5F, 0x3A, 0x29, NULL, 0x21, 0x2C, 0x3B},   // { _, :,     ),     [enter],     !,       ,,        ; }
    {0x2B, 0x22, 0x2D, NULL, 0x9B, 0x2E, 0x27}    // { +, ",     -, [backspace],     ¢,       .,        ' }
};
char symbolKeymap2[5][7] = {                      // index = 2
    {0x60, 0x25, NULL, 0xA6, NULL, NULL, 0xFF},   // { `, %, [sym],           ª, [alt], [space],     NBSP }
    {0xDB, 0xA7, 0xA9, 0x3D, 0xEC, 0xE6, NULL},   // { &, º,     ⌐,           =,     ∞,       µ, [lshift] }
    {0x9C, 0x5C, 0x7B, NULL, 0xA8, 0xFD, 0xAA},   // { £, \,     {,    [rshift],     ¿,       ²,        ¬ }
    {0x5E, 0xAB, 0x7C, NULL, 0xAD, 0xEF, 0xAC},   // { ^, ½,     },     [enter],     ¡,       ∩,        ¼ }
    {0x3E, 0xAF, 0x3C, NULL, 0x9E, 0x7E, 0xAE}    // { >, »,     <, [backspace],     ₧,       ~,        « }
};
char symbolKeymap3[5][7] = {                      // index = 3
    {0xDA, 0xD9, NULL, 0xF7, NULL, NULL, NULL},   // { ⌠,    ⌡, [sym],           ≈,  [alt], [space],    [mic] }
    {0xF6, 0xF8, 0xF9, 0xF0, NULL, NULL, NULL},   // { ÷,    °,     ∙,           ≡,   NULL,    NULL, [lshift] }
    {0xA5, 0xFB, 0x5B, NULL, NULL, 0xFC, 0xFA},   // { ¥,    √,     [,    [rshift],   NULL,       ⁿ,        · }
    {0xB1, 0x5C, 0x5D, NULL, NULL, NULL, 0x9F},   // { ±,    \,     ],     [enter],   NULL,    NULL,        ƒ }
    {0xF2, NULL, 0xF3, NULL, NULL, NULL, NULL}    // { ≥, NULL,     ≤, [backspace], [NULL],    NULL,     NULL }
};
/*
Character List (CP437):
0x00: NUL, 0x01: SOH, 0x02: STX, 0x03: ETX, 0x04: EOT, 0x05: ENQ, 0x06: ACK, 0x07: BEL, 0x08: BS,  0x09: HT,  0x0A: LF,  0x0B: VT,  0x0C: FF,  0x0D: CR,  0x0E: SO,  0x0F: SI,
0x10: DLE, 0x11: DC1, 0x12: DC2, 0x13: DC3, 0x14: DC4, 0x15: NAK, 0x16: SYN, 0x17: ETB, 0x18: CAN, 0x19: EM,  0x1A: SUB, 0x1B: ESC, 0x1C: FS,  0x1D: GS,  0x1E: RS,  0x1F: US,
0x20: SP,  0x21: !,   0x22: ",   0x23: #,   0x24: $,   0x25: %,   0x26: &,   0x27: ',   0x28: (,   0x29: ),   0x2A: *,   0x2B: +,   0x2C: ,,   0x2D: -,   0x2E: .,   0x2F: /,
0x30: 0,   0x31: 1,   0x32: 2,   0x33: 3,   0x34: 4,   0x35: 5,   0x36: 6,   0x37: 7,   0x38: 8,   0x39: 9,   0x3A: :,   0x3B: ;,   0x3C: <,   0x3D: =,   0x3E: >,   0x3F: ?,
0x40: @,   0x41: A,   0x42: B,   0x43: C,   0x44: D,   0x45: E,   0x46: F,   0x47: G,   0x48: H,   0x49: I,   0x4A: J,   0x4B: K,   0x4C: L,   0x4D: M,   0x4E: N,   0x4F: O,
0x50: P,   0x51: Q,   0x52: R,   0x53: S,   0x54: T,   0x55: U,   0x56: V,   0x57: W,   0x58: X,   0x59: Y,   0x5A: Z,   0x5B: [,   0x5C: \,   0x5D: ],   0x5E: ^,   0x5F: _,
0x60: `,   0x61: a,   0x62: b,   0x63: c,   0x64: d,   0x65: e,   0x66: f,   0x67: g,   0x68: h,   0x69: i,   0x6A: j,   0x6B: k,   0x6C: l,   0x6D: m,   0x6E: n,   0x6F: o,
0x70: p,   0x71: q,   0x72: r,   0x73: s,   0x74: t,   0x75: u,   0x76: v,   0x77: w,   0x78: x,   0x79: y,   0x7A: z,   0x7B: {,   0x7C: |,   0x7D: },   0x7E: ~,   0x7F: DEL,
0x80: Ç,   0x81: ü,   0x82: é,   0x83: â,   0x84: ä,   0x85: à,   0x86: å,   0x87: ç,   0x88: ê,   0x89: ë,   0x8A: è,   0x8B: ï,   0x8C: î,   0x8D: ì,   0x8E: Ä,   0x8F: Å,
0x90: É,   0x91: æ,   0x92: Æ,   0x93: ô,   0x94: ö,   0x95: ò,   0x96: û,   0x97: ù,   0x98: ÿ,   0x99: Ö,   0x9A: Ü,   0x9B: ¢,   0x9C: £,   0x9D: ¥,   0x9E: ₧,   0x9F: ƒ,
0xA0: á,   0xA1: í,   0xA2: ó,   0xA3: ú,   0xA4: ñ,   0xA5: Ñ,   0xA6: ª,   0xA7: º,   0xA8: ¿,   0xA9: ⌐,   0xAA: ¬,   0xAB: ½,   0xAC: ¼,   0xAD: ¡,   0xAE: «,   0xAF: »,
0xB0: ░,   0xB1: ▒,   0xB2: ▓,   0xB3: │,   0xB4: ┤,   0xB5: ╡,   0xB6: ╢,   0xB7: ╖,   0xB8: ╕,   0xB9: ╣,   0xBA: ║,   0xBB: ╗,   0xBC: ╝,   0xBD: ╜,   0xBE: ╛,   0xBF: ┐,
0xC0: └,   0xC1: ┴,   0xC2: ┬,   0xC3: ├,   0xC4: ─,   0xC5: ┼,   0xC6: ╞,   0xC7: ╟,   0xC8: ╚,   0xC9: ╔,   0xCA: ╩,   0xCB: ╦,   0xCC: ╠,   0xCD: ═,   0xCE: ╬,   0xCF: ╧,
0xD0: ╨,   0xD1: ╤,   0xD2: ╥,   0xD3: ╙,   0xD4: ╘,   0xD5: ╒,   0xD6: ╓,   0xD7: ╫,   0xD8: ╪,   0xD9: ┘,   0xDA: ┌,   0xDB: █,   0xDC: ▄,   0xDD: ▌,   0xDE: ▐,   0xDF: ▀,
0xE0: α,   0xE1: ß,   0xE2: Γ,   0xE3: π,   0xE4: Σ,   0xE5: σ,   0xE6: µ,   0xE7: τ,   0xE8: Φ,   0xE9: Θ,   0xEA: Ω,   0xEB: δ,   0xEC: ∞,   0xED: φ,   0xEE: ε,   0xEF: ∩,
0xF0: ≡,   0xF1: ±,   0xF2: ≥,   0xF3: ≤,   0xF4: ⌠,   0xF5: ⌡,   0xF6: ÷,   0xF7: ≈,   0xF8: °,   0xF9: ∙,   0xFA: ·,   0xFB: √,   0xFC: ⁿ,   0xFD: ²,   0xFE: ■,   0xFF: NBSP
*/
bool altLock = false;
bool ctrlLock = false;
bool capsLock = false;
bool symbolLock = false;
bool backlightState = true;
bool sendDataFlag = false;
uint8_t keymapIndex = 0;                                            // defaultKeymap = 0, symbolKeymap1 = 1, symbol_keymap2 = 2, etc.
uint8_t sendData[6] = {0x00, false, false, false, false, false};    // key_value, alt, ctrl, shift, mic, speaker
uint8_t emptyData[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};        // empty array to send when no key is pressed
uint8_t currentBrightness = 119;                                    // Default brightness level

/**
 * @brief Handles I2C requests.
 * 
 * Sends the key data over I2C when requested.
 */
void onRequest()
{
    if (sendDataFlag) {
        Wire.write(sendData, sizeof(sendData));
        sendDataFlag = false;
        Serial.print("sendData : ");
        for (int i = 0; i < 5; i++) {
            Serial.print(sendData[i]);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        Wire.write(emptyData, sizeof(emptyData)); // Use the temporary array
    }
}

/**
 * @brief Sets the keyboard backlight brightness.
 * 
 * @param command The command to set the brightness (toggle, up, down).
 */
void setKeyboardBrightness(uint8_t command)
{
    if (command == FUNCTION_TOGGLE) {
        if (backlightState) {
            currentBrightness = 0;
        } else {
            currentBrightness = KEYBOARD_BRIGHTNESS_DEFAULT;
        }
    } else if (command == FUNCTION_UP) {
        if (currentBrightness < KEYBOARD_BRIGHTNESS_MAX) {
            if (currentBrightness >= KEYBOARD_BRIGHTNESS_MAX - KEYBOARD_BRIGHTNESS_STEP) {
                currentBrightness = KEYBOARD_BRIGHTNESS_MAX;
            } else {
                currentBrightness += KEYBOARD_BRIGHTNESS_STEP;
            }
        }
    } else if (command == FUNCTION_DOWN) {
        if (currentBrightness > KEYBOARD_BRIGHTNESS_MIN) {
            if (currentBrightness <= KEYBOARD_BRIGHTNESS_MIN + KEYBOARD_BRIGHTNESS_STEP) {
                currentBrightness = KEYBOARD_BRIGHTNESS_MIN;
            } else {
                currentBrightness -= KEYBOARD_BRIGHTNESS_STEP;
            }
        }
    }
    // If the toggle is on/off and the user increments/decrements the brightness then ensure 
    // the backlight state is set correctly
    if (currentBrightness > KEYBOARD_BRIGHTNESS_MIN) {
        backlightState = true;
    } else {
        backlightState = false;
    }
    ledcWrite(KEYBOARD_BRIGHTNESS_CH, currentBrightness);
}

/**
 * @brief Checks if a key was released.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key was released, false otherwise.
 */
bool keyReleased(int colIndex, int rowIndex)
{
    return keyStates[colIndex][rowIndex] == RELEASED;
}

/**
 * @brief Checks if a key is being held.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key is being held, false otherwise.
 */
bool keyHeld(int colIndex, int rowIndex)
{
    return keyStates[colIndex][rowIndex] == HELD;
}

/**
 * @brief Checks if a key was pressed.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key was pressed, false otherwise.
 */
bool keyPressed(int colIndex, int rowIndex)
{
    return keyStates[colIndex][rowIndex] == PRESSED;
}

/**
 * @brief Checks if a key is not pressed.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @return true if the key is not pressed, false otherwise.
 */
bool keyNotPressed(int colIndex, int rowIndex)
{
    return keyStates[colIndex][rowIndex] == NOT_PRESSED;
}

/**
 * @brief Checks if a key exists in the keymap.
 * 
 * @param colIndex The column index of the key.
 * @param rowIndex The row index of the key.
 * @param keymap The keymap to check.
 * @return true if the key exists in the keymap, false otherwise.
 */
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[5][7])
{
    return keymap[colIndex][rowIndex] != NULL;
}

/**
 * @brief Prints the key information.
 * 
 * @param data The key data array.
 */
void printKeyInfo(uint8_t data[6])
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
    Serial.print("mic: ");
    Serial.println(data[4]);
    Serial.print("speaker: ");
    Serial.println(data[5]);
    Serial.println("************************************");
}

/**
 * @brief Reads the key matrix and updates the key states.
 */
void readKeyMatrix()
{
    // iterate the columns
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        uint8_t curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);

        // row: iterate through the rows
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            uint8_t rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            delay(1); // arduino is not fast enough to switch input/output modes so wait 1 ms

            bool buttonPressed = (digitalRead(rowCol) == LOW);

            // Debounce logic so keys don't trigger multiple times
            if (buttonPressed != lastValue[colIndex][rowIndex]) {
                delay(DEBOUNCE_DELAY); // Wait for debounce delay
                buttonPressed = (digitalRead(rowCol) == LOW); // Read the button state again
            }

            if (buttonPressed) {
                if (keyStates[colIndex][rowIndex] == NOT_PRESSED || keyStates[colIndex][rowIndex] == RELEASED) {
                    keyStates[colIndex][rowIndex] = PRESSED;
                } else {
                    keyStates[colIndex][rowIndex] = HELD;
                }
            } else {
                if (keyStates[colIndex][rowIndex] == PRESSED || keyStates[colIndex][rowIndex] == HELD) {
                    keyStates[colIndex][rowIndex] = RELEASED;
                } else {
                    keyStates[colIndex][rowIndex] = NOT_PRESSED;
                }
            }

            lastValue[colIndex][rowIndex] = buttonPressed;
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}

/**
 * @brief Sends the key information over I2C.
 */
void sendKeyInfo()
{
    bool dataToSend = false;
    uint8_t keyInfo[6]= {0x00, false, false, false, false, false}; // key_value, alt, ctrl, shift, mic, speaker
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
        for (int colIndex = 0; colIndex < colCount; colIndex++) {
            // any key released
            if (keyReleased(colIndex, rowIndex)) {
                // enter
                if (keyReleased(3, 3)) {
                    // backlight down (alt + enter)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_DOWN);
                    }
                    // tab (lshift + enter)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = 0x09;
                        dataToSend = true;
                    }
                    // mic volume down (mic + enter)
                    else if (keyHeld(0, 6)) {
                        keyInfo[0] = FUNCTION_DOWN;
                        keyInfo[4] = true;
                        dataToSend = true;
                    }
                    // $/speaker volume down ($ + enter)
                    else if (keyHeld(4, 4)) {
                        keyInfo[0] = FUNCTION_DOWN;
                        keyInfo[5] = true;
                        dataToSend = true;
                    }
                    // cycle symbol backward (sym + enter)
                    else if (keyHeld(0, 2)) {
                        if (keymapIndex == 0) {
                            keymapIndex = 3;
                        }
                        else {
                            keymapIndex--;
                        }
                    }
                    // enter
                    else {
                        keyInfo[0] = 0x0D;
                        dataToSend = true;
                    }
                }
                // space
                else if (keyReleased(0, 5)) {
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
                        if (keymapIndex > 0 && symbolLock == false) {
                            keymapIndex = 0;
                        }
                    }
                    // space
                    else {
                        keyInfo[0] = 0x20;
                        dataToSend = true;
                    }
                }
                // backspace
                else if (keyReleased(4, 3)) {
                    // backlight up (alt + backspace)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_UP);
                    }
                    // del (lshift + backspace)
                    else if (keyHeld(1, 6)) {
                        keyInfo[0] = 0x7F;
                        dataToSend = true;
                    }
                    // mic volume up (mic + backspace)
                    else if (keyHeld(0, 6)) {
                        keyInfo[0] = FUNCTION_UP;
                        keyInfo[4] = true;
                        dataToSend = true;
                    }
                    // $/speaker volume up ($ + backspace)
                    else if (keyHeld(4, 4)) {
                        keyInfo[0] = FUNCTION_UP;
                        keyInfo[5] = true;
                        dataToSend = true;
                    }
                    // cycle symbol forward (sym + backspace)
                    else if (keyHeld(0, 2)) {
                        keymapIndex++;
                        if (keymapIndex > 3) {
                            keymapIndex = 0;
                        }
                    }
                    // backspace
                    else {
                        keyInfo[0] = 0x08;
                        dataToSend = true;
                    }
                }
                // rshift
                else if (keyReleased(2, 3)) {
                    // backlight toggle (alt + rshift)
                    if (keyHeld(0, 4)) {
                        setKeyboardBrightness(FUNCTION_TOGGLE);
                    }
                    // mic toggle (mic + rshift)
                    else if (keyHeld(0, 6)) {
                        keyInfo[0] = FUNCTION_TOGGLE;
                        keyInfo[4] = true;
                        dataToSend = true;
                    }
                    // $/speaker toggle ($ + rshift)
                    else if (keyHeld(4, 4)) {
                        keyInfo[0] = FUNCTION_TOGGLE;
                        keyInfo[5] = true;
                        dataToSend = true;
                    }
                }
                // a-z key, alt, ctrl, shift, alt lock, ctrl lock, caps lock
                else if ((keymapIndex == 0 || altLock || keyHeld(0, 4) || ctrlLock || keyHeld(2, 3) || capsLock || keyHeld(1, 6)) && doesKeyExistInKeymap(colIndex, rowIndex, defaultKeymap)) {
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
                        keyInfo[0] = defaultKeymap[colIndex][rowIndex] - 32;
                    }
                    else {
                        keyInfo[0] = defaultKeymap[colIndex][rowIndex];
                    }
                    dataToSend = true;
                }
                // symbol 1
                else if ((keymapIndex == 1 || keyHeld(0, 2)) && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap1)) {
                    keyInfo[0] = symbolKeymap1[colIndex][rowIndex];
                    dataToSend = true;
                    if (symbolLock == false) {
                        keymapIndex = 0;
                    }
                }
                // symbol 2
                else if (keymapIndex == 2 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap2)) {
                    keyInfo[0] = symbolKeymap2[colIndex][rowIndex];
                    dataToSend = true;
                    if (symbolLock == false) {
                        keymapIndex = 0;
                    }
                }
                // symbol 3
                else if (keymapIndex == 3 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap3)) {
                    keyInfo[0] = symbolKeymap3[colIndex][rowIndex];
                    dataToSend = true;
                    if (symbolLock == false) {
                        keymapIndex = 0;
                    }
                }
                // // symbol 4
                // else if (keymapIndex == 4 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap4)) {
                //     keyInfo[0] = symbolKeymap4[colIndex][rowIndex];
                //     dataToSend = true;
                //     if (symbolLock == false) {
                //         keymapIndex = 0;
                //     }
                // }
                // // symbol 5
                // else if (keymapIndex == 5 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap5)) {
                //     keyInfo[0] = symbolKeymap5[colIndex][rowIndex];
                //     dataToSend = true;
                //     if (symbolLock == false) {
                //         keymapIndex = 0;
                //     }
                // }
                // // symbol 6
                // else if (keymapIndex == 6 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap6)) {
                //     keyInfo[0] = symbolKeymap6[colIndex][rowIndex];
                //     dataToSend = true;
                //     if (symbolLock == false) {
                //         keymapIndex = 0;
                //     }
                // }
                // // symbol 7
                // else if (keymapIndex == 7 && doesKeyExistInKeymap(colIndex, rowIndex, symbolKeymap7)) {
                //     keyInfo[0] = symbolKeymap7[colIndex][rowIndex];
                //     dataToSend = true;
                //     if (symbolLock == false) {
                //         keymapIndex = 0;
                //     }
                // }
            }
        }
    }
    printKeyInfo(keyInfo);
    sendDataFlag = dataToSend;
    if (sendDataFlag) {
        memcpy(sendData, keyInfo, sizeof(keyInfo));
    }
}