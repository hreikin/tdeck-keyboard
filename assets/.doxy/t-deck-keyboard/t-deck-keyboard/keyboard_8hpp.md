

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
|  const int | [**colCount**](#variable-colcount)  <br> |
|  uint8\_t | [**cols**](#variable-cols)  <br> |
|  bool | [**ctrlLock**](#variable-ctrllock)  <br> |
|  uint8\_t | [**currentBrightness**](#variable-currentbrightness)  <br> |
|  char | [**defaultKeymap**](#variable-defaultkeymap)  <br> |
|  uint8\_t | [**emptyData**](#variable-emptydata)  <br> |
|  KeyState | [**keyStates**](#variable-keystates)  <br> |
|  uint8\_t | [**keymapIndex**](#variable-keymapindex)  <br> |
|  bool | [**lastValue**](#variable-lastvalue)  <br> |
|  const int | [**rowCount**](#variable-rowcount)  <br> |
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
|  bool | [**doesKeyExistInKeymap**](#function-doeskeyexistinkeymap) (int colIndex, int rowIndex, char keymap) <br>_Checks if a key exists in the keymap._  |
|  bool | [**keyHeld**](#function-keyheld) (int colIndex, int rowIndex) <br>_Checks if a key is being held._  |
|  bool | [**keyNotPressed**](#function-keynotpressed) (int colIndex, int rowIndex) <br>_Checks if a key is not pressed._  |
|  bool | [**keyPressed**](#function-keypressed) (int colIndex, int rowIndex) <br>_Checks if a key was pressed._  |
|  bool | [**keyReleased**](#function-keyreleased) (int colIndex, int rowIndex) <br>_Checks if a key was released._  |
|  void | [**onRequest**](#function-onrequest) () <br>_Handles I2C requests._  |
|  void | [**printKeyInfo**](#function-printkeyinfo) (uint8\_t data) <br>_Prints the key information._  |
|  void | [**readKeyMatrix**](#function-readkeymatrix) () <br>_Reads the key matrix and updates the key states._  |
|  void | [**sendKeyInfo**](#function-sendkeyinfo) () <br>_Sends the key information over I2C._  |
|  void | [**setKeyboardBrightness**](#function-setkeyboardbrightness) (uint8\_t command) <br>_Sets the keyboard backlight brightness._  |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DEBOUNCE\_DELAY**](keyboard_8hpp.md#define-debounce_delay)  `50`<br> |
| define  | [**FUNCTION\_DOWN**](keyboard_8hpp.md#define-function_down)  `0x03`<br> |
| define  | [**FUNCTION\_TOGGLE**](keyboard_8hpp.md#define-function_toggle)  `0x01`<br> |
| define  | [**FUNCTION\_UP**](keyboard_8hpp.md#define-function_up)  `0x02`<br> |
| define  | [**I2C\_DEV\_ADDR**](keyboard_8hpp.md#define-i2c_dev_addr)  `0x55`<br> |
| define  | [**KEYBOARD\_BACKLIGHT\_PIN**](keyboard_8hpp.md#define-keyboard_backlight_pin)  `9`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_CH**](keyboard_8hpp.md#define-keyboard_brightness_ch)  `0`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_DEFAULT**](keyboard_8hpp.md#define-keyboard_brightness_default)  `119`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_FREQ**](keyboard_8hpp.md#define-keyboard_brightness_freq)  `1000`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_MAX**](keyboard_8hpp.md#define-keyboard_brightness_max)  `255`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_MIN**](keyboard_8hpp.md#define-keyboard_brightness_min)  `0`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_RES**](keyboard_8hpp.md#define-keyboard_brightness_res)  `8`<br> |
| define  | [**KEYBOARD\_BRIGHTNESS\_STEP**](keyboard_8hpp.md#define-keyboard_brightness_step)  `17`<br> |
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



### variable colCount 

```C++
const int colCount;
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
char defaultKeymap[5][7];
```




<hr>



### variable emptyData 

```C++
uint8_t emptyData[6];
```




<hr>



### variable keyStates 

```C++
KeyState keyStates[5][7];
```




<hr>



### variable keymapIndex 

```C++
uint8_t keymapIndex;
```




<hr>



### variable lastValue 

```C++
bool lastValue[5][7];
```




<hr>



### variable rowCount 

```C++
const int rowCount;
```




<hr>



### variable rows 

```C++
uint8_t rows[];
```




<hr>



### variable sendData 

```C++
uint8_t sendData[6];
```




<hr>



### variable sendDataFlag 

```C++
bool sendDataFlag;
```




<hr>



### variable symbolKeymap1 

```C++
char symbolKeymap1[5][7];
```




<hr>



### variable symbolKeymap2 

```C++
char symbolKeymap2[5][7];
```




<hr>



### variable symbolKeymap3 

```C++
char symbolKeymap3[5][7];
```




<hr>



### variable symbolKeymap4 

```C++
char symbolKeymap4[5][7];
```




<hr>



### variable symbolKeymap5 

```C++
char symbolKeymap5[5][7];
```




<hr>



### variable symbolKeymap6 

```C++
char symbolKeymap6[5][7];
```




<hr>



### variable symbolKeymap7 

```C++
char symbolKeymap7[5][7];
```




<hr>



### variable symbolLock 

```C++
bool symbolLock;
```




<hr>
## Public Functions Documentation




### function doesKeyExistInKeymap 

_Checks if a key exists in the keymap._ 
```C++
bool doesKeyExistInKeymap (
    int colIndex,
    int rowIndex,
    char keymap
) 
```





**Parameters:**


* `colIndex` The column index of the key. 
* `rowIndex` The row index of the key. 
* `keymap` The keymap to check. 



**Returns:**

true if the key exists in the keymap, false otherwise. 





        

<hr>



### function keyHeld 

_Checks if a key is being held._ 
```C++
bool keyHeld (
    int colIndex,
    int rowIndex
) 
```





**Parameters:**


* `colIndex` The column index of the key. 
* `rowIndex` The row index of the key. 



**Returns:**

true if the key is being held, false otherwise. 





        

<hr>



### function keyNotPressed 

_Checks if a key is not pressed._ 
```C++
bool keyNotPressed (
    int colIndex,
    int rowIndex
) 
```





**Parameters:**


* `colIndex` The column index of the key. 
* `rowIndex` The row index of the key. 



**Returns:**

true if the key is not pressed, false otherwise. 





        

<hr>



### function keyPressed 

_Checks if a key was pressed._ 
```C++
bool keyPressed (
    int colIndex,
    int rowIndex
) 
```





**Parameters:**


* `colIndex` The column index of the key. 
* `rowIndex` The row index of the key. 



**Returns:**

true if the key was pressed, false otherwise. 





        

<hr>



### function keyReleased 

_Checks if a key was released._ 
```C++
bool keyReleased (
    int colIndex,
    int rowIndex
) 
```





**Parameters:**


* `colIndex` The column index of the key. 
* `rowIndex` The row index of the key. 



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
## Macro Definition Documentation





### define DEBOUNCE\_DELAY 

```C++
#define DEBOUNCE_DELAY `50`
```




<hr>



### define FUNCTION\_DOWN 

```C++
#define FUNCTION_DOWN `0x03`
```




<hr>



### define FUNCTION\_TOGGLE 

```C++
#define FUNCTION_TOGGLE `0x01`
```




<hr>



### define FUNCTION\_UP 

```C++
#define FUNCTION_UP `0x02`
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

