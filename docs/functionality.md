# Functionality

The keyboard supports multiple keymaps and special key combinations to enhance its functionality. It includes default keymaps for regular typing and several symbol keymaps for special characters. The keyboard also supports key combinations for controlling the backlight, toggling locks (Alt, Ctrl, Caps, Symbol), and adjusting the volume for the mic and speaker.

## Keymaps

- **Default Keymap**: Contains the standard alphanumeric characters and some special keys.
- **Symbol Keymaps**: Provide access to various symbols and special characters. There are multiple symbol keymaps that can be cycled through using specific key combinations.

## Key Combinations

The keyboard supports a variety of key combinations to enhance its functionality. These combinations allow users to perform actions such as adjusting the backlight, toggling locks, and custom functions to be used for controlling the volume of the mic and speaker. Below is a table that outlines the key combinations and their corresponding functionalities:

| KEY/COMBINATION      | FUNCTIONALITY                                                                                               |
|----------------------|-------------------------------------------------------------------------------------------------------------|
| [a-z]                | Type lowercase letters                                                                                      |
| BACKSPACE            | Sends the backspace character                                                                               |
| ENTER                | Sends the enter character                                                                                   |
| SPACE                | Sends the space character                                                                                   |
| ALT + [a-z]          | Send the character being pressed along with a bool representing the `alt` key                               |
| ALT + BACKSPACE      | Increase the backlight brightness                                                                           |
| ALT + ENTER          | Decrease the backlight brightness                                                                           |
| ALT + SPACE          | Toggle the Alt lock, subsequent key presses will follow the same functionality as holding the `alt` key     |
| ALT + RSHIFT         | Toggle the backlight on or off                                                                              |
| ALT + MIC            | Mic function 1, recommended for toggling the microphone on or off                                           |
| ALT + $              | Speaker function 1, recommended for toggling the speaker on or off                                          |
| LSHIFT + [a-z]       | Type uppercase letters                                                                                      |
| LSHIFT + BACKSPACE   | Sends the delete character                                                                                  |
| LSHIFT + ENTER       | Sends the tab character                                                                                     |
| LSHIFT + SPACE       | Toggle the Caps Lock, subsequent key presses will follow the same functionality as holding the `lshift` key |
| LSHIFT + MIC         | Mic function 2, recommended for decreasing the microphone volume                                            |
| LSHIFT + $           | Speaker function 2, recommended for decreasing the speaker volume                                           |
| SYM + BACKSPACE      | Cycle forward through the symbol keymaps                                                                    |
| SYM + ENTER          | Cycle backward through the symbol keymaps                                                                   |
| SYM + SPACE          | Toggle the Symbol lock, subsequent key presses will send keys from the relevant symbol keymap               |
| RSHIFT + [a-z]       | Send the character being pressed along with a bool representing the `ctrl` key                              |
| RSHIFT + SPACE       | Toggle the Ctrl lock, subsequent key presses will follow the same functionality as holding the `rshift` key |
| RSHIFT + MIC         | Mic function 3, recommended for increasing the microphone volume                                            |
| RSHIFT + $           | Speaker function 3, recommended for increasing the speaker volume                                           |

## Available Characters

The following table shows the available characters for the keymaps. Symbol tables 4-8 are not currently implemented in the firmware. The characters are displayed in the following format:

- `q` (113, 0x71) 

Where `q` is the character, `113` is the decimal value, and `0x71` is the hexadecimal value. The characters shown in the table are based on the CP437 font used by `TFT_eSPI` and correspond to the key values for those positions within the font, if another font is used then the characters may be different but they will relate to the character in the same position within the font.

| DEFAULT               | CAPS                  | SYMBOL 1              | SYMBOL 2              | SYMBOL 3              |
|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
| `q` (113, 0x71)       | `Q` (81, 0x51)        | `#` (35, 0x23)        | `` ` `` (96, 0x60)    | `⌠` (218, 0xDA)       |
| `w` (119, 0x77)       | `W` (87, 0x57)        | `1` (49, 0x31)        | `%` (37, 0x25)        | `⌡` (217, 0xD9)       |
| `e` (101, 0x65)       | `E` (69, 0x45)        | `2` (50, 0x32)        | `&` (38, 0x26)        | `÷` (246, 0xF6)       |
| `r` (114, 0x72)       | `R` (82, 0x52)        | `3` (51, 0x33)        | `£` (163, 0xA3)       | `¥` (165, 0xA5)       |
| `t` (116, 0x74)       | `T` (84, 0x54)        | `(` (40, 0x28)        | `{` (123, 0x7B)       | `[` (91, 0x5B)        |
| `y` (121, 0x79)       | `Y` (89, 0x59)        | `)` (41, 0x29)        | `}` (125, 0x7D)       | `]` (93, 0x5D)        |
| `u` (117, 0x75)       | `U` (85, 0x55)        | `_` (95, 0x5F)        | `^` (94, 0x5E)        | `±` (177, 0xB1)       |
| `i` (105, 0x69)       | `I` (73, 0x49)        | `-` (45, 0x2D)        | `<` (60, 0x3C)        | `≤` (243, 0xF3)       |
| `o` (111, 0x6F)       | `O` (79, 0x4F)        | `+` (43, 0x2B)        | `>` (62, 0x3E)        | `≥` (242, 0xF2)       |
| `p` (112, 0x70)       | `P` (80, 0x50)        | `@` (64, 0x40)        | `=` (61, 0x3D)        | `≡` (240, 0xF0)       |
| `a` (97, 0x61)        | `A` (65, 0x41)        | `*` (42, 0x2A)        | `ª` (166, 0xA6)       | `≈` (247, 0xF7)       |
| `s` (115, 0x73)       | `S` (83, 0x53)        | `4` (52, 0x34)        | `º` (167, 0xA7)       | `°` (248, 0xF8)       |
| `d` (100, 0x64)       | `D` (68, 0x44)        | `5` (53, 0x35)        | `⌐` (169, 0xA9)       | `∙` (249, 0xF9)       |
| `f` (102, 0x66)       | `F` (70, 0x46)        | `6` (54, 0x36)        | `¬` (170, 0xAA)       | `·` (250, 0xFA)       |
| `g` (103, 0x67)       | `G` (71, 0x47)        | `/` (47, 0x2F)        | `\` (92, 0x5C)        | `√` (251, 0xFB)       |
| `h` (104, 0x68)       | `H` (72, 0x48)        | `:` (58, 0x3A)        | `½` (171, 0xAB)       | `\|` (92, 0x5C)       |
| `j` (106, 0x6A)       | `J` (74, 0x4A)        | `;` (59, 0x3B)        | `¼` (172, 0xAC)       | `ƒ` (159, 0x9F)       |
| `k` (107, 0x6B)       | `K` (75, 0x4B)        | `'` (39, 0x27)        | `«` (174, 0xAE)       |                       |
| `l` (108, 0x6C)       | `L` (76, 0x4C)        | `"` (34, 0x22)        | `»` (175, 0xAF)       |                       |
| `z` (122, 0x7A)       | `Z` (90, 0x5A)        | `7` (55, 0x37)        | `µ` (230, 0xE6)       |                       |
| `x` (120, 0x78)       | `X` (88, 0x58)        | `8` (56, 0x38)        | `∞` (236, 0xEC)       |                       |
| `c` (99, 0x63)        | `C` (67, 0x43)        | `9` (57, 0x39)        | `²` (253, 0xFD)       | `ⁿ` (252, 0xFC)       |
| `v` (118, 0x76)       | `V` (86, 0x56)        | `?` (63, 0x3F)        | `¿` (168, 0xA8)       |                       |
| `b` (98, 0x62)        | `B` (66, 0x42)        | `!` (33, 0x21)        | `¡` (173, 0xAD)       |                       |
| `n` (110, 0x6E)       | `N` (78, 0x4E)        | `,` (44, 0x2C)        | `∩` (239, 0xEF)       |                       |
| `m` (109, 0x6D)       | `M` (77, 0x4D)        | `.` (46, 0x2E)        | `~` (126, 0x7E)       |                       |
| `$` (36, 0x24)        |                       | `¢` (155, 0x9B)       | `₧` (158, 0x9E)       |                       |
| `MIC`                 |                       | `0` (48, 0x30)        | `NBSP` (255, 0xFF)    |                       |
| `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    |
| `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) |
| `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    |

| DEFAULT               | SYMBOL 4              | SYMBOL 5              | SYMBOL 6              | SYMBOL 7              | SYMBOL 8              |
|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
| `q` (113, 0x71)       | `â` (131, 0x83)       | `Ö` (153, 0x99)       | `│` (179, 0xB3)       | `╬` (206, 0xCE)       | `ENQ` (5, 0x05)       |
| `w` (119, 0x77)       | `ä` (132, 0x84)       | `ó` (162, 0xA2)       | `┤` (180, 0xB4)       | `╧` (207, 0xCF)       | `ACK` (6, 0x06)       |
| `e` (101, 0x65)       | `à` (133, 0x85)       | `ü` (129, 0x81)       | `╡` (181, 0xB5)       | `╨` (208, 0xD0)       | `BEL` (7, 0x07)       |
| `r` (114, 0x72)       | `å` (134, 0x86)       | `û` (150, 0x96)       | `╢` (182, 0xB6)       | `╤` (209, 0xD1)       | `BS` (8, 0x08)        |
| `t` (116, 0x74)       | `á` (160, 0xA0)       | `ù` (151, 0x97)       | `╖` (183, 0xB7)       | `╥` (210, 0xD2)       | `TAB` (9, 0x09)       |
| `y` (121, 0x79)       | `Ä` (142, 0x8E)       | `Ü` (154, 0x9A)       | `╕` (184, 0xB8)       | `╙` (211, 0xD3)       | `LF` (10, 0x0A)       |
| `u` (117, 0x75)       | `Å` (143, 0x8F)       | `ú` (163, 0xA3)       | `╣` (185, 0xB9)       | `╘` (212, 0xD4)       | `VT` (11, 0x0B)       |
| `i` (105, 0x69)       | `æ` (145, 0x91)       | `ÿ` (152, 0x98)       | `║` (186, 0xBA)       | `╒` (213, 0xD5)       | `FF` (12, 0x0C)       |
| `o` (111, 0x6F)       | `Æ` (146, 0x92)       | `α` (224, 0xE0)       | `╗` (187, 0xBB)       | `╓` (214, 0xD6)       | `CR` (13, 0x0D)       |
| `p` (112, 0x70)       | `ç` (135, 0x87)       | `Γ` (226, 0xE2)       | `╝` (188, 0xBC)       | `╫` (215, 0xD7)       | `SO` (14, 0x0E)       |
| `a` (97, 0x61)        | `Ç` (128, 0x80)       | `π` (227, 0xE3)       | `╜` (189, 0xBD)       | `╪` (216, 0xD8)       | `SI` (15, 0x0F)       |
| `s` (115, 0x73)       | `ß` (225, 0xE1)       | `Σ` (228, 0xE4)       | `╛` (190, 0xBE)       | `┘` (217, 0xD9)       | `DLE`(16, 0x10)       |
| `d` (100, 0x64)       | `é` (130, 0x82)       | `σ` (229, 0xE5)       | `┐` (191, 0xBF)       | `┌` (218, 0xDA)       | `DC1`(17, 0x11)       |
| `f` (102, 0x66)       | `ê` (136, 0x88)       | `τ` (231, 0xE7)       | `└` (192, 0xC0)       | `█` (219, 0xDB)       | `DC2`(18, 0x12)       |
| `g` (103, 0x67)       | `ë` (137, 0x89)       | `Φ` (232, 0xE8)       | `┴` (193, 0xC1)       | `▄` (220, 0xDC)       | `DC3`(19, 0x13)       |
| `h` (104, 0x68)       | `è` (138, 0x8A)       | `Θ` (233, 0xE9)       | `┬` (194, 0xC2)       | `▌` (221, 0xDD)       | `DC4`(20, 0x14)       |
| `j` (106, 0x6A)       | `É` (144, 0x90)       | `Ω` (234, 0xEA)       | `├` (195, 0xC3)       | `▐` (222, 0xDE)       | `NAK`(21, 0x15)       |
| `k` (107, 0x6B)       | `ï` (139, 0x8B)       | `δ` (235, 0xEB)       | `─` (196, 0xC4)       | `▀` (223, 0xDF)       | `SYN`(22, 0x16)       |
| `l` (108, 0x6C)       | `î` (140, 0x8C)       | `φ` (237, 0xED)       | `┼` (197, 0xC5)       | `■` (254, 0xFE)       | `ETB`(23, 0x17)       |
| `z` (122, 0x7A)       | `ì` (141, 0x8D)       | `ε` (238, 0xEE)       | `╞` (198, 0xC6)       | `░` (176, 0xB0)       | `CAN`(24, 0x18)       |
| `x` (120, 0x78)       | `í` (161, 0xA1)       |                       | `╟` (199, 0xC7)       | `▒` (177, 0xB1)       | `EM` (25, 0x19)       |
| `c` (99, 0x63)        | `ñ` (164, 0xA4)       |                       | `╚` (200, 0xC8)       | `▓` (178, 0xB2)       | `SUB`(26, 0x1A)       |
| `v` (118, 0x76)       | `Ñ` (165, 0xA5)       |                       | `╔` (201, 0xC9)       | `NUL` (0, 0x00)       | `ESC`(27, 0x1B)       |
| `b` (98, 0x62)        | `ô` (147, 0x93)       |                       | `╩` (202, 0xCA)       | `SOH` (1, 0x01)       | `FS`(28, 0x1C)        |
| `n` (110, 0x6E)       | `ö` (148, 0x94)       |                       | `╦` (203, 0xCB)       | `STX` (2, 0x02)       | `GS`(29, 0x1D)        |
| `m` (109, 0x6D)       | `ò` (149, 0x95)       |                       | `╠` (204, 0xCC)       | `ETX` (3, 0x03)       | `RS`(30, 0x1E)        |
| `$` (36, 0x24)        |                       |                       | `═` (205, 0xCD)       | `EOT` (4, 0x04)       | `US`(31, 0x1F)        |
| `MIC`                 |                       |                       |                       |                       |                       |
| `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    |
| `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) |
| `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    |