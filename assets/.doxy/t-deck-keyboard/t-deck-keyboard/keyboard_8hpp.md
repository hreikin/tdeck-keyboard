

# File keyboard.hpp



[**FileList**](files.md) **>** [**keyboard**](dir_fb0b1e2663c8abb876623317aa8e6792.md) **>** [**keyboard.hpp**](keyboard_8hpp.md)

[Go to the source code of this file](keyboard_8hpp_source.md)

_Header file for keyboard functions and keymaps._ [More...](#detailed-description)

* `#include <Arduino.h>`
* `#include <Wire.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**KeyState**](#enum-keystate)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**altLock**](#variable-altlock)  <br> |
|  bool | [**backlightState**](#variable-backlightstate)  <br> |
|  bool | [**capsLock**](#variable-capslock)  <br> |
|  uint8\_t | [**cols**](#variable-cols)  <br> |
|  bool | [**ctrlLock**](#variable-ctrllock)  <br> |
|  uint8\_t | [**currentBrightness**](#variable-currentbrightness)  <br> |
|  char | [**defaultKeymap**](#variable-defaultkeymap)  <br> |
|  uint8\_t | [**emptyData**](#variable-emptydata)  <br> |
|  uint8\_t | [**keyInfo**](#variable-keyinfo)  <br> |
|  unsigned long | [**keyRepeatStart**](#variable-keyrepeatstart)  <br> |
|  KeyState | [**keyStates**](#variable-keystates)  <br> |
|  uint8\_t | [**keymapIndex**](#variable-keymapindex)  <br> |
|  bool | [**lastValue**](#variable-lastvalue)  <br> |
|  uint8\_t | [**rows**](#variable-rows)  <br> |
|  uint8\_t | [**sendData**](#variable-senddata)  <br> |
|  bool | [**sendDataFlag**](#variable-senddataflag)  <br> |
|  char | [**symbolKeymap1**](#variable-symbolkeymap1)  <br> |
|  char | [**symbolKeymap2**](#variable-symbolkeymap2)  <br> |
|  char | [**symbolKeymap3**](#variable-symbolkeymap3)  <br> |
|  char | [**symbolKeymap4**](#variable-symbolkeymap4)  <br> |
|  char | [**symbolKeymap5**](#variable-symbolkeymap5)  <br> |
|  char | [**symbolKeymap6**](#variable-symbolkeymap6)  <br> |
|  char | [**symbolKeymap7**](#variable-symbolkeymap7)  <br> |
|  bool | [**symbolLock**](#variable-symbollock)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**autoResetKeymapIndex**](#function-autoresetkeymapindex) () <br>_Handles resetting the keymap index._  |
|  bool | [**doesKeyExistInKeymap**](#function-doeskeyexistinkeymap) (int rowIndex, int colIndex, char keymap) <br>_Checks if a key exists in the keymap._  |
|  void | [**handleCharacter**](#function-handlecharacter) (int rowIndex, int colIndex) <br>_Handles the character for a specific key._  |
|  bool | [**keyHeld**](#function-keyheld) (int rowIndex, int colIndex) <br>_Checks if a key is being held._  |
|  bool | [**keyNotPressed**](#function-keynotpressed) (int rowIndex, int colIndex) <br>_Checks if a key is not pressed._  |
|  bool | [**keyPressed**](#function-keypressed) (int rowIndex, int colIndex) <br>_Checks if a key was pressed._  |
|  bool | [**keyReleased**](#function-keyreleased) (int rowIndex, int colIndex) <br>_Checks if a key was released._  |
|  void | [**onRequest**](#function-onrequest) () <br>_Handles I2C requests._  |
|  void | [**printKeyInfo**](#function-printkeyinfo) (uint8\_t data) <br>_Prints the key information._  |
|  void | [**readKeyMatrix**](#function-readkeymatrix) () <br>_Reads the key matrix and updates the key states._  |
|  void | [**sendKeyInfo**](#function-sendkeyinfo) () <br>_Sends the key information over I2C._  |
|  void | [**setDefaultCharacter**](#function-setdefaultcharacter) (int rowIndex, int colIndex) <br>_Sets keyInfo to the correct character for a specific key, from the default keymap only._  |
|  void | [**setKeyboardBrightness**](#function-setkeyboardbrightness) (uint8\_t command) <br>_Sets the keyboard backlight brightness._  |
|  void | [**setSymbolCharacter**](#function-setsymbolcharacter) (int rowIndex, int colIndex) <br>_Sets keyInfo to the correct character for a specific key, from the symbol keymaps only._  |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**COL\_COUNT**](keyboard_8hpp.md#define-col_count)  `7`<br> |
| define  | [**DEBOUNCE\_DELAY**](keyboard_8hpp.md#define-debounce_delay)  `50`<br> |
| define  | [**FUNCTION\_DOWN**](keyboard_8hpp.md#define-function_down)  `0x02`<br> |
| define  | [**FUNCTION\_TOGGLE**](keyboard_8hpp.md#define-function_toggle)  `0x01`<br> |
| define  | [**FUNCTION\_UP**](keyboard_8hpp.md#define-function_up)  `0x03`<br> |
| define  | [**I2C\_DEV\_ADDR**](keyboard_8hpp.md#define-i2c_dev_addr)  `0x55`<br> |
| define  | [**KEYBOARD\_BACKLIGHT\_PIN**](keyboard_8hpp.md#define-keyboard_backlight_pin)  `9`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_CH**](keyboard_8hpp.md#define-keyboard_brightness_ch)  `0`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_DEFAULT**](keyboard_8hpp.md#define-keyboard_brightness_default)  `119`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_FREQ**](keyboard_8hpp.md#define-keyboard_brightness_freq)  `1000`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_MAX**](keyboard_8hpp.md#define-keyboard_brightness_max)  `255`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_MIN**](keyboard_8hpp.md#define-keyboard_brightness_min)  `0`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_RES**](keyboard_8hpp.md#define-keyboard_brightness_res)  `8`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_STEP**](keyboard_8hpp.md#define-keyboard_brightness_step)  `17`<br> |
| define  | [**KEY\_INFO\_SIZE**](keyboard_8hpp.md#define-key_info_size)  `7`<br> |
| define  | [**KEY\_REPEAT\_DELAY**](keyboard_8hpp.md#define-key_repeat_delay)  `200`<br> |
| define  | [**MAX\_KEYMAP\_INDEX**](keyboard_8hpp.md#define-max_keymap_index)  `8`<br> |
| define  | [**MIN\_KEYMAP\_INDEX**](keyboard_8hpp.md#define-min_keymap_index)  `0`<br> |
| define  | [**ROW\_COUNT**](keyboard_8hpp.md#define-row_count)  `5`<br> |
| define  | [**SCL**](keyboard_8hpp.md#define-scl)  `10`<br> |
| define  | [**SDA**](keyboard_8hpp.md#define-sda)  `2`<br> |

## Detailed Description




**Author:**

hreikin ([hreikin@gmail.com](mailto:hreikin@gmail.com)) @license MIT 




**Copyright:**

Copyright (c) 2025 hreikin ([hreikin@gmail.com](mailto:hreikin@gmail.com)) 




**Date:**

2025-03-07 





    
## Public Types Documentation




### enum KeyState 

```C++
enum KeyState {
    NOT_PRESSED,
    PRESSED,
    HELD,
    RELEASED
};
```




<hr>
## Public Attributes Documentation




### variable altLock 

```C++
bool altLock;
```




<hr>



### variable backlightState 

```C++
bool backlightState;
```




<hr>



### variable capsLock 

```C++
bool capsLock;
```




<hr>



### variable cols 

```C++
uint8_t cols[];
```




<hr>



### variable ctrlLock 

```C++
bool ctrlLock;
```




<hr>



### variable currentBrightness 

```C++
uint8_t currentBrightness;
```




<hr>



### variable defaultKeymap 

```C++
char defaultKeymap[ROW_COUNT][COL_COUNT];
```




<hr>



### variable emptyData 

```C++
uint8_t emptyData[KEY_INFO_SIZE];
```




<hr>



### variable keyInfo 

```C++
uint8_t keyInfo[KEY_INFO_SIZE];
```




<hr>



### variable keyRepeatStart 

```C++
unsigned long keyRepeatStart;
```




<hr>



### variable keyStates 

```C++
KeyState keyStates[ROW_COUNT][COL_COUNT];
```




<hr>



### variable keymapIndex 

```C++
uint8_t keymapIndex;
```




<hr>



### variable lastValue 

```C++
bool lastValue[ROW_COUNT][COL_COUNT];
```




<hr>



### variable rows 

```C++
uint8_t rows[];
```




<hr>



### variable sendData 

```C++
uint8_t sendData[KEY_INFO_SIZE];
```




<hr>



### variable sendDataFlag 

```C++
bool sendDataFlag;
```




<hr>



### variable symbolKeymap1 

```C++
char symbolKeymap1[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap2 

```C++
char symbolKeymap2[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap3 

```C++
char symbolKeymap3[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap4 

```C++
char symbolKeymap4[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap5 

```C++
char symbolKeymap5[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap6 

```C++
char symbolKeymap6[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolKeymap7 

```C++
char symbolKeymap7[ROW_COUNT][COL_COUNT];
```




<hr>



### variable symbolLock 

```C++
bool symbolLock;
```




<hr>
## Public Functions Documentation




### function autoResetKeymapIndex 

_Handles resetting the keymap index._ 
```C++
void autoResetKeymapIndex () 
```




<hr>



### function doesKeyExistInKeymap 

_Checks if a key exists in the keymap._ 
```C++
bool doesKeyExistInKeymap (
    int rowIndex,
    int colIndex,
    char keymap
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 
* `keymap` The keymap to check. 



**Returns:**

true if the key exists in the keymap, false otherwise. 





        

<hr>



### function handleCharacter 

_Handles the character for a specific key._ 
```C++
void handleCharacter (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 




        

<hr>



### function keyHeld 

_Checks if a key is being held._ 
```C++
bool keyHeld (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 



**Returns:**

true if the key is being held, false otherwise. 





        

<hr>



### function keyNotPressed 

_Checks if a key is not pressed._ 
```C++
bool keyNotPressed (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 



**Returns:**

true if the key is not pressed, false otherwise. 





        

<hr>



### function keyPressed 

_Checks if a key was pressed._ 
```C++
bool keyPressed (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 



**Returns:**

true if the key was pressed, false otherwise. 





        

<hr>



### function keyReleased 

_Checks if a key was released._ 
```C++
bool keyReleased (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 



**Returns:**

true if the key was released, false otherwise. 





        

<hr>



### function onRequest 

_Handles I2C requests._ 
```C++
void onRequest () 
```



Sends the key data over I2C when requested. 


        

<hr>



### function printKeyInfo 

_Prints the key information._ 
```C++
void printKeyInfo (
    uint8_t data
) 
```





**Parameters:**


* `data` The key data array. 




        

<hr>



### function readKeyMatrix 

_Reads the key matrix and updates the key states._ 
```C++
void readKeyMatrix () 
```




<hr>



### function sendKeyInfo 

_Sends the key information over I2C._ 
```C++
void sendKeyInfo () 
```




<hr>



### function setDefaultCharacter 

_Sets keyInfo to the correct character for a specific key, from the default keymap only._ 
```C++
void setDefaultCharacter (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key.

Sets keyInfo to the correct character for a specific key, from the default keymap only.




**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 




        

<hr>



### function setKeyboardBrightness 

_Sets the keyboard backlight brightness._ 
```C++
void setKeyboardBrightness (
    uint8_t command
) 
```





**Parameters:**


* `command` The command to set the brightness (toggle, up, down). 




        

<hr>



### function setSymbolCharacter 

_Sets keyInfo to the correct character for a specific key, from the symbol keymaps only._ 
```C++
void setSymbolCharacter (
    int rowIndex,
    int colIndex
) 
```





**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key.

Sets keyInfo to the correct character for a specific key, from the symbol keymaps only.




**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 




        

<hr>
## Macro Definition Documentation





### define COL\_COUNT 

```C++
#define COL_COUNT `7`
```




<hr>



### define DEBOUNCE\_DELAY 

```C++
#define DEBOUNCE_DELAY `50`
```




<hr>



### define FUNCTION\_DOWN 

```C++
#define FUNCTION_DOWN `0x02`
```




<hr>



### define FUNCTION\_TOGGLE 

```C++
#define FUNCTION_TOGGLE `0x01`
```




<hr>



### define FUNCTION\_UP 

```C++
#define FUNCTION_UP `0x03`
```




<hr>



### define I2C\_DEV\_ADDR 

```C++
#define I2C_DEV_ADDR `0x55`
```




<hr>



### define KEYBOARD\_BACKLIGHT\_PIN 

```C++
#define KEYBOARD_BACKLIGHT_PIN `9`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_CH 

```C++
#define KEYBOARD_BRIGHTNESS_CH `0`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_DEFAULT 

```C++
#define KEYBOARD_BRIGHTNESS_DEFAULT `119`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_FREQ 

```C++
#define KEYBOARD_BRIGHTNESS_FREQ `1000`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_MAX 

```C++
#define KEYBOARD_BRIGHTNESS_MAX `255`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_MIN 

```C++
#define KEYBOARD_BRIGHTNESS_MIN `0`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_RES 

```C++
#define KEYBOARD_BRIGHTNESS_RES `8`
```




<hr>



### define KEYBOARD\_BRIGHTNESS\_STEP 

```C++
#define KEYBOARD_BRIGHTNESS_STEP `17`
```




<hr>



### define KEY\_INFO\_SIZE 

```C++
#define KEY_INFO_SIZE `7`
```




<hr>



### define KEY\_REPEAT\_DELAY 

```C++
#define KEY_REPEAT_DELAY `200`
```




<hr>



### define MAX\_KEYMAP\_INDEX 

```C++
#define MAX_KEYMAP_INDEX `8`
```




<hr>



### define MIN\_KEYMAP\_INDEX 

```C++
#define MIN_KEYMAP_INDEX `0`
```




<hr>



### define ROW\_COUNT 

```C++
#define ROW_COUNT `5`
```




<hr>



### define SCL 

```C++
#define SCL `10`
```




<hr>



### define SDA 

```C++
#define SDA `2`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `keyboard/keyboard.hpp`

