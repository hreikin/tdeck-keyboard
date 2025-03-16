

# File keyboard.cpp



[**FileList**](files.md) **>** [**keyboard**](dir_fb0b1e2663c8abb876623317aa8e6792.md) **>** [**keyboard.cpp**](keyboard_8cpp.md)

[Go to the source code of this file](keyboard_8cpp_source.md)

_Implementation of keyboard functions and keymaps._ [More...](#detailed-description)

* `#include "keyboard.hpp"`
* `#include "keys.hpp"`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**altLock**](#variable-altlock)   = `false`<br> |
|  bool | [**backlightState**](#variable-backlightstate)   = `true`<br> |
|  bool | [**capsLock**](#variable-capslock)   = `false`<br> |
|  uint8\_t | [**cols**](#variable-cols)   = `{0, 3, 19, 12, 18, 6, 7}`<br> |
|  bool | [**ctrlLock**](#variable-ctrllock)   = `false`<br> |
|  uint8\_t | [**currentBrightness**](#variable-currentbrightness)   = `119`<br> |
|  char | [**defaultKeymap**](#variable-defaultkeymap)   = `/* multi line expression */`<br> |
|  uint8\_t | [**emptyData**](#variable-emptydata)   = `{0x00, false, false, false, false, false, false}`<br> |
|  uint8\_t | [**keyInfo**](#variable-keyinfo)   = `{0x00, false, false, false, false, false, false}`<br> |
|  unsigned long | [**keyRepeatStart**](#variable-keyrepeatstart)   = `0`<br> |
|  KeyState | [**keyStates**](#variable-keystates)  <br> |
|  uint8\_t | [**keymapIndex**](#variable-keymapindex)   = `0`<br> |
|  bool | [**lastValue**](#variable-lastvalue)  <br> |
|  uint8\_t | [**rows**](#variable-rows)   = `{1, 4, 5, 11, 13}`<br> |
|  uint8\_t | [**sendData**](#variable-senddata)   = `{0x00, false, false, false, false, false, false}`<br> |
|  bool | [**sendDataFlag**](#variable-senddataflag)   = `false`<br> |
|  char | [**symbolKeymap1**](#variable-symbolkeymap1)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap2**](#variable-symbolkeymap2)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap3**](#variable-symbolkeymap3)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap4**](#variable-symbolkeymap4)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap5**](#variable-symbolkeymap5)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap6**](#variable-symbolkeymap6)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap7**](#variable-symbolkeymap7)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap8**](#variable-symbolkeymap8)   = `/* multi line expression */`<br> |
|  bool | [**symbolLock**](#variable-symbollock)   = `false`<br> |
















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
|  void | [**setDefaultCharacter**](#function-setdefaultcharacter) (int rowIndex, int colIndex) <br>_Sets the default character for a key._  |
|  void | [**setKeyboardBrightness**](#function-setkeyboardbrightness) (uint8\_t command) <br>_Sets the keyboard backlight brightness._  |
|  void | [**setSymbolCharacter**](#function-setsymbolcharacter) (int rowIndex, int colIndex) <br>_Sets the symbol character for a key._  |




























## Detailed Description




**Author:**

hreikin ([hreikin@gmail.com](mailto:hreikin@gmail.com)) @license MIT 




**Copyright:**

Copyright (c) 2025 hreikin ([hreikin@gmail.com](mailto:hreikin@gmail.com)) 




**Date:**

2025-03-07 





    
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



### variable symbolKeymap8 

```C++
char symbolKeymap8[ROW_COUNT][COL_COUNT];
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

_Sets the default character for a key._ 
```C++
void setDefaultCharacter (
    int rowIndex,
    int colIndex
) 
```



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

_Sets the symbol character for a key._ 
```C++
void setSymbolCharacter (
    int rowIndex,
    int colIndex
) 
```



Sets keyInfo to the correct character for a specific key, from the symbol keymaps only.




**Parameters:**


* `rowIndex` The row index of the key. 
* `colIndex` The column index of the key. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `keyboard/keyboard.cpp`

