# TODO

- [ ] create keymaps for different layouts:
    - [x] default
    - [x] caps
    - [x] ctrl
    - [ ] symbol_1 - symbol_n
- [x] create keymap_index variable (int) to track which keymap to use
- [x] create modifiers (bools) for alt, mic, speaker (may need to create bools for different tables or order the if statements in sendKeyInfo() ?)
- [x] create key_info array with key_value and modifiers and implement in sendKeyInfo()
- [x] callbacks for onRequest() and onReceive()
- [x] helpers for isKeyPressed(), isKeyHeld()
- [x] readKeyMatrix() to read the key matrix and update the key values
- [x] sendKeyInfo() to get the key from the appropriate table using the helpers, send all modifiers and the key value in KeyInfo format
    - [x] default keymap is (0)
    - [x] use both shift keys for caps lock (1), single key for normal shift, if normal shift take from the caps table as well
    - [x] use alt + c for ctrl (2)
    - [ ] symbol cycles through the others (3 to n)
- [ ] Basic usage documentation