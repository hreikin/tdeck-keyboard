/**
 * @file      keyboard.cpp
 * @brief     Implementation of keyboard functions and keymaps.
 * @author    hreikin (hreikin@gmail.com)
 * @license   MIT
 * @copyright Copyright (c) 2025 hreikin (hreikin@gmail.com)
 * @date      2025-03-07
 */
#include "keyboard.hpp"
#include "keys.hpp"

// TODO: Switch these around, rows should be columns and columns should be rows
uint8_t rows[] = {0, 3, 19, 12, 18, 6, 7};
uint8_t cols[] = {1, 4, 5, 11, 13};

bool lastValue[COL_COUNT][ROW_COUNT];
KeyState keyStates[COL_COUNT][ROW_COUNT];
// TODO: Update special handling for $ key (new keymaps)
// Keys wrapped in square brackets require special handling
// default column in functionality.md
// { q, w, [sym],           a, [alt], [space],    [mic] }
// { e, s,     d,           p,     x,       z, [lshift] }
// { r, g,     t,    [rshift],     v,       c,        f }
// { u, h,     y,     [enter],     b,       n,        j }
// { o, l,     i, [backspace],   [$],       m,        k }
char defaultKeymap[COL_COUNT][ROW_COUNT] = {                                                                                  
    {LATIN_SMALL_LETTER_Q, LATIN_SMALL_LETTER_W, NULL, LATIN_SMALL_LETTER_A, NULL, NULL, NULL},                                          
    {LATIN_SMALL_LETTER_E, LATIN_SMALL_LETTER_S, LATIN_SMALL_LETTER_D, LATIN_SMALL_LETTER_P, LATIN_SMALL_LETTER_X, LATIN_SMALL_LETTER_Z, NULL},                     
    {LATIN_SMALL_LETTER_R, LATIN_SMALL_LETTER_G, LATIN_SMALL_LETTER_T, NULL, LATIN_SMALL_LETTER_V, LATIN_SMALL_LETTER_C, LATIN_SMALL_LETTER_F},                     
    {LATIN_SMALL_LETTER_U, LATIN_SMALL_LETTER_H, LATIN_SMALL_LETTER_Y, NULL, LATIN_SMALL_LETTER_B, LATIN_SMALL_LETTER_N, LATIN_SMALL_LETTER_J},                     
    {LATIN_SMALL_LETTER_O, LATIN_SMALL_LETTER_L, LATIN_SMALL_LETTER_I, NULL, DOLLAR_SIGN, LATIN_SMALL_LETTER_M, LATIN_SMALL_LETTER_K}                  
};
// symbol 1 column in functionality.md
// { #, 1, [sym],           *, [alt], [space],      [0] }
// { 2, 4,     5,           @,     8,       7, [lshift] }
// { 3, /,     (,    [rshift],     ?,       9,        6 }
// { _, :,     ),     [enter],     !,       ,,        ; }
// { +, ",     -, [backspace],   [¢],       .,        ' }
char symbolKeymap1[COL_COUNT][ROW_COUNT] = {                                                                                  
    {NUMBER_SIGN, DIGIT_ONE, NULL, ASTERISK, NULL, NULL, DIGIT_ZERO},                                          
    {DIGIT_TWO, DIGIT_FOUR, DIGIT_FIVE, COMMERCIAL_AT, DIGIT_EIGHT, DIGIT_SEVEN, NULL},                                             
    {DIGIT_THREE, SOLIDUS, LEFT_PARENTHESIS, NULL, QUESTION_MARK, DIGIT_NINE, DIGIT_SIX},                        
    {LOW_LINE, COLON, RIGHT_PARENTHESIS, NULL, EXCLAMATION_MARK, COMMA, SEMICOLON},   
    {PLUS_SIGN, QUOTATION_MARK, HYPHEN_MINUS, NULL, CENT_SIGN, FULL_STOP, APOSTROPHE} 
};
// symbol 2 column in functionality.md
// { `, %, [sym],           ª, [alt], [space],   [NBSP] }
// { &, º,     ⌐,           =,     ∞,       µ, [lshift] }
// { £, \,     {,    [rshift],     ¿,       ²,        ¬ }
// { ^, ½,     },     [enter],     ¡,       ∩,        ¼ }
// { >, »,     <, [backspace],   [₧],       ~,        « }
char symbolKeymap2[COL_COUNT][ROW_COUNT] = {
    {GRAVE_ACCENT, PERCENT_SIGN, NULL, FEMININE_ORDINAL_INDICATOR, NULL, NULL, NO_BREAK_SPACE},
    {AMPERSAND, MASCULINE_ORDINAL_INDICATOR, REVERSED_NOT_SIGN, EQUALS_SIGN, INFINITY, MICRO_SIGN, NULL},
    {POUND_SIGN, REVERSE_SOLIDUS, LEFT_CURLY_BRACKET, NULL, INVERTED_QUESTION_MARK, SUPERSCRIPT_TWO, NOT_SIGN},
    {CIRCUMFLEX_ACCENT, VULGAR_FRACTION_ONE_HALF, RIGHT_CURLY_BRACKET, NULL, INVERTED_EXCLAMATION_MARK, INTERSECTION, VULGAR_FRACTION_ONE_QUARTER},
    {GREATER_THAN_SIGN, RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK, LESS_THAN_SIGN, NULL, PESETA_SIGN, TILDE, LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK}
};
// symbol 3 column in functionality.md
// { ⌠,    ⌡, [sym],           ≈,  [alt], [space],   [NULL] }
// { ÷,    °,     ∙,           ≡,   NULL,    NULL, [lshift] }
// { ¥,    √,     [,    [rshift],   NULL,       ⁿ,        · }
// { ±,    \,     ],     [enter],   NULL,    NULL,        ƒ }
// { ≥, NULL,     ≤, [backspace], [NULL],    NULL,     NULL }
char symbolKeymap3[COL_COUNT][ROW_COUNT] = {
    {TOP_HALF_INTEGRAL, BOTTOM_HALF_INTEGRAL, NULL, ALMOST_EQUAL_TO, NULL, NULL, NULL},
    {DIVISION_SIGN, DEGREE_SIGN, BULLET_OPERATOR, IDENTICAL_TO, NULL, NULL, NULL},
    {YEN_SIGN, SQUARE_ROOT, LEFT_SQUARE_BRACKET, NULL, NULL, SUPERSCRIPT_LATIN_SMALL_LETTER_N, MIDDLE_DOT},
    {PLUS_MINUS_SIGN, REVERSE_SOLIDUS, RIGHT_SQUARE_BRACKET, NULL, NULL, NULL, LATIN_SMALL_LETTER_F_WITH_HOOK},
    {GREATER_THAN_OR_EQUAL_TO, NULL, LESS_THAN_OR_EQUAL_TO, NULL, NULL, NULL, NULL}
};
// symbol 4 column in functionality.md
// { â, ä, [sym],           Ç,  [alt], [space],   [NULL] }
// { à, ß,     é,           ç,      í,       ì, [lshift] }
// { å, ë,     á,    [rshift],      Ñ,       ñ,        ê }
// { Å, è,     Ä,     [enter],      ô,       ö,        É }
// { Æ, î,     æ, [backspace], [NULL],       ò,        ï }
char symbolKeymap4[COL_COUNT][ROW_COUNT] = {
    {LATIN_SMALL_LETTER_A_WITH_CIRCUMFLEX, LATIN_SMALL_LETTER_A_WITH_DIAERESIS, NULL, LATIN_CAPITAL_LETTER_C_WITH_CEDILLA, NULL, NULL, NULL},
    {LATIN_SMALL_LETTER_A_WITH_GRAVE, LATIN_SMALL_LETTER_SHARP_S, LATIN_SMALL_LETTER_E_WITH_ACUTE, LATIN_SMALL_LETTER_C_WITH_CEDILLA, LATIN_SMALL_LETTER_I_WITH_ACUTE, LATIN_SMALL_LETTER_I_WITH_GRAVE, NULL},
    {LATIN_SMALL_LETTER_A_WITH_RING_ABOVE, LATIN_SMALL_LETTER_E_WITH_DIAERESIS, LATIN_SMALL_LETTER_A_WITH_ACUTE, NULL, LATIN_CAPITAL_LETTER_N_WITH_TILDE, LATIN_SMALL_LETTER_N_WITH_TILDE, LATIN_SMALL_LETTER_E_WITH_CIRCUMFLEX},
    {LATIN_CAPITAL_LETTER_A_WITH_RING_ABOVE, LATIN_SMALL_LETTER_E_WITH_GRAVE, LATIN_CAPITAL_LETTER_A_WITH_DIAERESIS, NULL, LATIN_SMALL_LETTER_O_WITH_CIRCUMFLEX, LATIN_SMALL_LETTER_O_WITH_DIAERESIS, LATIN_CAPITAL_LETTER_E_WITH_ACUTE},
    {LATIN_CAPITAL_LIGATURE_AE, LATIN_SMALL_LETTER_I_WITH_CIRCUMFLEX, LATIN_SMALL_LIGATURE_AE, NULL, NULL, LATIN_SMALL_LETTER_O_WITH_GRAVE, LATIN_SMALL_LETTER_I_WITH_DIAERESIS}
};
// symbol 5 column in functionality.md
// { Ö, ó, [sym],           π,  [alt], [space],   [NULL] }
// { ü, Σ,     σ,           Γ,   NULL,       ε, [lshift] }
// { û, Φ,     ù,    [rshift],   NULL,    NULL,        τ }
// { ú, Θ,     Ü,     [enter],   NULL,    NULL,        Ω }
// { α, φ,     ÿ, [backspace], [NULL],    NULL,        δ }
char symbolKeymap5[COL_COUNT][ROW_COUNT] = {
    {LATIN_CAPITAL_LETTER_O_WITH_DIAERESIS, LATIN_SMALL_LETTER_O_WITH_ACUTE, NULL, GREEK_SMALL_LETTER_PI, NULL, NULL, NULL},
    {LATIN_SMALL_LETTER_U_WITH_DIAERESIS, GREEK_CAPITAL_LETTER_SIGMA, GREEK_SMALL_LETTER_SIGMA, GREEK_CAPITAL_LETTER_GAMMA, NULL, GREEK_SMALL_LETTER_EPSILON, NULL},
    {LATIN_SMALL_LETTER_U_WITH_CIRCUMFLEX, GREEK_CAPITAL_LETTER_PHI, LATIN_SMALL_LETTER_U_WITH_GRAVE, NULL, NULL, NULL, GREEK_SMALL_LETTER_TAU},
    {LATIN_SMALL_LETTER_U_WITH_ACUTE, GREEK_CAPITAL_LETTER_THETA, LATIN_CAPITAL_LETTER_U_WITH_DIAERESIS, NULL, NULL, NULL, GREEK_CAPITAL_LETTER_OMEGA},
    {GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_PHI, LATIN_SMALL_LETTER_Y_WITH_DIAERESIS, NULL, NULL, NULL, GREEK_SMALL_LETTER_DELTA}
};
// symbol 6 column in functionality.md
// { │, ┤, [sym],           ╜, [alt], [space],   [NULL] }
// { ╡, ╛,     ┐,           ╝,     ╟,       ╞, [lshift] }
// { ╢, ┴,     ╖,    [rshift],     ╔,       ╚,        └ }
// { ╣, ┬,     ╕,     [enter],     ╩,       ╦,        ├ }
// { ╗, ┼,     ║, [backspace],   [═],       ╠,        ─ }
char symbolKeymap6[COL_COUNT][ROW_COUNT] = {
    {BOX_DRAWINGS_LIGHT_VERTICAL, BOX_DRAWINGS_LIGHT_VERTICAL_AND_LEFT, NULL, BOX_DRAWINGS_UP_SINGLE_AND_HORIZONTAL_DOUBLE, NULL, NULL, NULL},
    {BOX_DRAWINGS_VERTICAL_SINGLE_AND_LEFT_DOUBLE, BOX_DRAWINGS_UP_SINGLE_AND_HORIZONTAL_DOUBLE, BOX_DRAWINGS_LIGHT_DOWN_AND_LEFT, BOX_DRAWINGS_DOUBLE_UP_AND_LEFT, BOX_DRAWINGS_VERTICAL_DOUBLE_AND_RIGHT_SINGLE, BOX_DRAWINGS_VERTICAL_SINGLE_AND_RIGHT_DOUBLE, NULL},
    {BOX_DRAWINGS_VERTICAL_DOUBLE_AND_LEFT_SINGLE, BOX_DRAWINGS_LIGHT_UP_AND_HORIZONTAL, BOX_DRAWINGS_DOWN_DOUBLE_AND_LEFT_SINGLE, NULL, BOX_DRAWINGS_DOUBLE_DOWN_AND_RIGHT, BOX_DRAWINGS_DOUBLE_UP_AND_RIGHT, BOX_DRAWINGS_LIGHT_UP_AND_RIGHT},
    {BOX_DRAWINGS_DOUBLE_VERTICAL_AND_LEFT, BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL, BOX_DRAWINGS_DOWN_SINGLE_AND_LEFT_DOUBLE, NULL, BOX_DRAWINGS_DOUBLE_UP_AND_HORIZONTAL, BOX_DRAWINGS_DOUBLE_DOWN_AND_HORIZONTAL, BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT},
    {BOX_DRAWINGS_DOUBLE_DOWN_AND_LEFT, BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL, BOX_DRAWINGS_DOUBLE_VERTICAL, NULL, BOX_DRAWINGS_DOUBLE_HORIZONTAL, BOX_DRAWINGS_DOUBLE_VERTICAL_AND_HORIZONTAL, BOX_DRAWINGS_LIGHT_HORIZONTAL}
};

// symbol 7 column in functionality.md
// { ╬, ╬, [sym],           ╪, [alt], [space],   [NULL] }
// { ╨, ┘,     ┌,           ╫,     ▒,       ░, [lshift] }
// { ╤, ▄,     ╥,    [rshift],   NUL,       ▓,        █ }
// { ╘, ▌,     ╙,     [enter],   SOH,     STX,        ▐ }
// { ╓, ■,     ╒, [backspace], [EOT],     ETX,        ▀ }
char symbolKeymap7[COL_COUNT][ROW_COUNT] = {
    {BOX_DRAWINGS_DOUBLE_VERTICAL_AND_HORIZONTAL, BOX_DRAWINGS_DOUBLE_VERTICAL_AND_HORIZONTAL, NULL, BOX_DRAWINGS_VERTICAL_SINGLE_AND_HORIZONTAL_DOUBLE, NULL, NULL, NULL},
    {BOX_DRAWINGS_UP_DOUBLE_AND_HORIZONTAL_SINGLE, BOX_DRAWINGS_LIGHT_UP_AND_LEFT, BOX_DRAWINGS_LIGHT_DOWN_AND_RIGHT, BOX_DRAWINGS_VERTICAL_DOUBLE_AND_HORIZONTAL_SINGLE, LIGHT_SHADE, MEDIUM_SHADE, NULL},
    {BOX_DRAWINGS_DOWN_SINGLE_AND_HORIZONTAL_DOUBLE, LOWER_HALF_BLOCK, BOX_DRAWINGS_DOWN_DOUBLE_AND_HORIZONTAL_SINGLE, NULL, NULL, DARK_SHADE, FULL_BLOCK},
    {BOX_DRAWINGS_UP_SINGLE_AND_RIGHT_DOUBLE, LEFT_HALF_BLOCK, BOX_DRAWINGS_UP_DOUBLE_AND_RIGHT_SINGLE, NULL, START_OF_HEADING, START_OF_TEXT, RIGHT_HALF_BLOCK},
    {BOX_DRAWINGS_DOWN_DOUBLE_AND_RIGHT_SINGLE, BLACK_SQUARE, BOX_DRAWINGS_DOWN_SINGLE_AND_RIGHT_DOUBLE, NULL, END_OF_TRANSMISSION, END_OF_TEXT, UPPER_HALF_BLOCK}
};

// symbol 8 column in functionality.md
// { ENQ, ACK, [sym],          SI, [alt], [space],   [NULL] }
// { BEL, DLE,   DC1,          SO,    EM,     CAN, [lshift] }
// {  BS, DC3,   TAB,    [rshift],   ESC,     SUB,      DC2 }
// {  VT, DC4,    LF,     [enter],    FS,      GS,      NAK }
// {  CR, ETB,    FF, [backspace],  [US],      RS,      SYN }
char symbolKeymap8[COL_COUNT][ROW_COUNT] = {
    {ENQUIRY, ACKNOWLEDGE, NULL, SHIFT_IN, NULL, NULL, NULL},
    {BELL, DATA_LINK_ESCAPE, DEVICE_CONTROL_ONE, SHIFT_OUT, END_OF_MEDIUM, CANCEL, NULL},
    {BACKSPACE, DEVICE_CONTROL_THREE, HORIZONTAL_TABULATION, NULL, ESCAPE, SUBSTITUTE, DEVICE_CONTROL_TWO},
    {VERTICAL_TABULATION, DEVICE_CONTROL_FOUR, LINE_FEED, NULL, FILE_SEPARATOR, GROUP_SEPARATOR, NEGATIVE_ACKNOWLEDGE},
    {CARRIAGE_RETURN, END_OF_TRANSMISSION_BLOCK, FORM_FEED, NULL, UNIT_SEPARATOR, RECORD_SEPARATOR, SYNCHRONOUS_IDLE}
};

bool altLock = false;
bool ctrlLock = false;
bool capsLock = false;
bool symbolLock = false;
bool backlightState = true;
bool sendDataFlag = false;
uint8_t keymapIndex = 0;                                                        // defaultKeymap = 0, symbolKeymap1 = 1, symbol_keymap2 = 2, etc.
uint8_t keyInfo[KEY_INFO_SIZE] = {0x00, false, false, false, false, false};     // key_value, alt, ctrl, shift, mic, speaker
uint8_t sendData[KEY_INFO_SIZE] = {0x00, false, false, false, false, false};    // key_value, alt, ctrl, shift, mic, speaker
uint8_t emptyData[KEY_INFO_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};        // empty array to send when no key is pressed
uint8_t currentBrightness = 119;                                                // Default brightness level
unsigned long keyRepeatStart = 0;

/**
 * @brief Handles I2C requests.
 * 
 * Sends the key data over I2C when requested.
 */
void onRequest()
{
    if (sendDataFlag) {
        Wire.write(sendData, KEY_INFO_SIZE);
        sendDataFlag = false;
        Serial.print("sendData : ");
        for (int i = 0; i < KEY_INFO_SIZE; i++) {
            Serial.print(sendData[i]);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        Wire.write(emptyData, KEY_INFO_SIZE); // Use the temporary array
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
            currentBrightness = KEYBOARD_BRIGHTNESS_MIN;
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
bool doesKeyExistInKeymap(int colIndex, int rowIndex, char keymap[COL_COUNT][ROW_COUNT])
{
    return keymap[colIndex][rowIndex] != NULL;
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
    Serial.print("mic: ");
    Serial.println(data[4]);
    Serial.print("speaker: ");
    Serial.println(data[5]);
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
                if (keyNotPressed(colIndex, rowIndex) || keyReleased(colIndex, rowIndex)) {
                    keyStates[colIndex][rowIndex] = PRESSED;
                } else {
                    keyStates[colIndex][rowIndex] = HELD;
                }
            } else {
                if (keyPressed(colIndex, rowIndex) || keyHeld(colIndex, rowIndex)) {
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