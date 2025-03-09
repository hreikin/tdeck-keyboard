

# File keyboard.cpp



[**FileList**](files.md) **>** [**keyboard**](dir_fb0b1e2663c8abb876623317aa8e6792.md) **>** [**keyboard.cpp**](keyboard_8cpp.md)

[Go to the source code of this file](keyboard_8cpp_source.md)

_Implementation of keyboard functions and keymaps._ [More...](#detailed-description)

* `#include "keyboard.hpp"`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**altLock**](#variable-altlock)   = `false`<br> |
|  bool | [**backlightState**](#variable-backlightstate)   = `true`<br> |
|  bool | [**capsLock**](#variable-capslock)   = `false`<br> |
|  const int | [**colCount**](#variable-colcount)   = `sizeof(cols) / sizeof(cols[0])`<br> |
|  uint8\_t | [**cols**](#variable-cols)   = `{1, 4, 5, 11, 13}`<br> |
|  bool | [**ctrlLock**](#variable-ctrllock)   = `false`<br> |
|  uint8\_t | [**currentBrightness**](#variable-currentbrightness)   = `119`<br> |
|  char | [**defaultKeymap**](#variable-defaultkeymap)   = `/* multi line expression */`<br> |
|  uint8\_t | [**emptyData**](#variable-emptydata)   = `{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}`<br> |
|  KeyState | [**keyStates**](#variable-keystates)  <br> |
|  uint8\_t | [**keymapIndex**](#variable-keymapindex)   = `0`<br> |
|  bool | [**lastValue**](#variable-lastvalue)  <br> |
|  const int | [**rowCount**](#variable-rowcount)   = `sizeof(rows) / sizeof(rows[0])`<br> |
|  uint8\_t | [**rows**](#variable-rows)   = `{0, 3, 19, 12, 18, 6, 7}`<br> |
|  uint8\_t | [**sendData**](#variable-senddata)   = `{0x00, false, false, false, false, false}`<br> |
|  bool | [**sendDataFlag**](#variable-senddataflag)   = `false`<br> |
|  char | [**symbolKeymap1**](#variable-symbolkeymap1)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap2**](#variable-symbolkeymap2)   = `/* multi line expression */`<br> |
|  char | [**symbolKeymap3**](#variable-symbolkeymap3)   = `/* multi line expression */`<br> |
|  bool | [**symbolLock**](#variable-symbollock)   = `false`<br> |
















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

------------------------------
The documentation for this class was generated from the following file `keyboard/keyboard.cpp`

