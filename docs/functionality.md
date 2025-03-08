# Functionality

The keyboard supports multiple keymaps and special key combinations to enhance its functionality. It includes default keymaps for regular typing and several symbol keymaps for special characters. The keyboard also supports key combinations for controlling the backlight, toggling locks (Alt, Ctrl, Caps, Symbol), and adjusting the volume for the mic and speaker.

## Keymaps

- **Default Keymap**: Contains the standard alphanumeric characters and some special keys.
- **Symbol Keymaps**: Provide access to various symbols and special characters. There are multiple symbol keymaps that can be cycled through using specific key combinations.

## Key Combinations

| KEY/COMBINATION      | FUNCTIONALITY             |
|----------------------|---------------------------|
| [a-z]                | [a-z]                     |
| ENTER                | Enter                     |
| SPACE                | Space                     |
| BACKSPACE            | Backspace                 |
| ALT + [a-z]          | Alt + [a-z]               |
| ALT + ENTER          | Decrease backlight        |
| ALT + SPACE          | Toggle alt lock           |
| ALT + BACKSPACE      | Increase backlight        |
| ALT + RSHIFT         | Toggle backlight          |
| LSHIFT (held)        | Shift + [a-z]             |
| LSHIFT + ENTER       | Tab                       |
| LSHIFT + SPACE       | Toggle caps lock          |
| LSHIFT + BACKSPACE   | Delete                    |
| MIC + ENTER          | Mic volume down           |
| MIC + BACKSPACE      | Mic volume up             |
| MIC + RSHIFT         | Toggle mic                |
| $ + ENTER            | Speaker volume down       |
| $ + BACKSPACE        | Speaker volume up         |
| $ + RSHIFT           | Toggle speaker            |
| SYM + [a-z]          | Symbol + [a-z] (Symbol 1) |
| SYM + ENTER          | Cycle symbol backward     |
| SYM + SPACE          | Toggle symbol lock        |
| SYM + BACKSPACE      | Cycle symbol forward      |
| RSHIFT (held)        | Ctrl + [a-z]              |
| RSHIFT + SPACE       | Toggle ctrl lock          |

## Available Characters

The following table shows the available characters for the keymaps, the characters shown are based on the CP437 font. Symbol tables 4-7 are not currently implemented in the firmware.

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

| DEFAULT               | SYMBOL 4              | SYMBOL 5              | SYMBOL 6              | SYMBOL 7              |
|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
| `q` (113, 0x71)       | `â` (131, 0x83)       | `Ö` (153, 0x99)       | `│` (179, 0xB3)       | `╬` (206, 0xCE)       |
| `w` (119, 0x77)       | `ä` (132, 0x84)       | `ó` (162, 0xA2)       | `┤` (180, 0xB4)       | `╧` (207, 0xCF)       |
| `e` (101, 0x65)       | `à` (133, 0x85)       | `ü` (129, 0x81)       | `╡` (181, 0xB5)       | `╨` (208, 0xD0)       |
| `r` (114, 0x72)       | `å` (134, 0x86)       | `û` (150, 0x96)       | `╢` (182, 0xB6)       | `╤` (209, 0xD1)       |
| `t` (116, 0x74)       | `á` (160, 0xA0)       | `ù` (151, 0x97)       | `╖` (183, 0xB7)       | `╥` (210, 0xD2)       |
| `y` (121, 0x79)       | `Ä` (142, 0x8E)       | `Ü` (154, 0x9A)       | `╕` (184, 0xB8)       | `╙` (211, 0xD3)       |
| `u` (117, 0x75)       | `Å` (143, 0x8F)       | `ú` (163, 0xA3)       | `╣` (185, 0xB9)       | `╘` (212, 0xD4)       |
| `i` (105, 0x69)       | `æ` (145, 0x91)       | `ÿ` (152, 0x98)       | `║` (186, 0xBA)       | `╒` (213, 0xD5)       |
| `o` (111, 0x6F)       | `Æ` (146, 0x92)       | `α` (224, 0xE0)       | `╗` (187, 0xBB)       | `╓` (214, 0xD6)       |
| `p` (112, 0x70)       | `ç` (135, 0x87)       | `Γ` (226, 0xE2)       | `╝` (188, 0xBC)       | `╫` (215, 0xD7)       |
| `a` (97, 0x61)        | `Ç` (128, 0x80)       | `π` (227, 0xE3)       | `╜` (189, 0xBD)       | `╪` (216, 0xD8)       |
| `s` (115, 0x73)       | `ß` (225, 0xE1)       | `Σ` (228, 0xE4)       | `╛` (190, 0xBE)       | `┘` (217, 0xD9)       |
| `d` (100, 0x64)       | `é` (130, 0x82)       | `σ` (229, 0xE5)       | `┐` (191, 0xBF)       | `┌` (218, 0xDA)       |
| `f` (102, 0x66)       | `ê` (136, 0x88)       | `τ` (231, 0xE7)       | `└` (192, 0xC0)       | `█` (219, 0xDB)       |
| `g` (103, 0x67)       | `ë` (137, 0x89)       | `Φ` (232, 0xE8)       | `┴` (193, 0xC1)       | `▄` (220, 0xDC)       |
| `h` (104, 0x68)       | `è` (138, 0x8A)       | `Θ` (233, 0xE9)       | `┬` (194, 0xC2)       | `▌` (221, 0xDD)       |
| `j` (106, 0x6A)       | `É` (144, 0x90)       | `Ω` (234, 0xEA)       | `├` (195, 0xC3)       | `▐` (222, 0xDE)       |
| `k` (107, 0x6B)       | `ï` (139, 0x8B)       | `δ` (235, 0xEB)       | `─` (196, 0xC4)       | `▀` (223, 0xDF)       |
| `l` (108, 0x6C)       | `î` (140, 0x8C)       | `φ` (237, 0xED)       | `┼` (197, 0xC5)       | `■` (254, 0xFE)       |
| `z` (122, 0x7A)       | `ì` (141, 0x8D)       | `ε` (238, 0xEE)       | `╞` (198, 0xC6)       | `░` (176, 0xB0)       |
| `x` (120, 0x78)       | `í` (161, 0xA1)       |                       | `╟` (199, 0xC7)       | `▒` (177, 0xB1)       |
| `c` (99, 0x63)        | `ñ` (164, 0xA4)       |                       | `╚` (200, 0xC8)       | `▓` (178, 0xB2)       |
| `v` (118, 0x76)       | `Ñ` (165, 0xA5)       |                       | `╔` (201, 0xC9)       |                       |
| `b` (98, 0x62)        | `ô` (147, 0x93)       |                       | `╩` (202, 0xCA)       |                       |
| `n` (110, 0x6E)       | `ö` (148, 0x94)       |                       | `╦` (203, 0xCB)       |                       |
| `m` (109, 0x6D)       | `ò` (149, 0x95)       |                       | `╠` (204, 0xCC)       |                       |
| `$` (36, 0x24)        |                       |                       | `═` (205, 0xCD)       |                       |
| `MIC`                 |                       |                       |                       |                       |
| `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    | `SPACE` (32, 0x20)    |
| `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) | `BACKSPACE` (8, 0x08) |
| `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    | `ENTER` (13, 0x0D)    |