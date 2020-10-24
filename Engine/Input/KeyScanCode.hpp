// Code modified from the SDL library.
#ifndef AZGARD_KEY_SACNCODES
#define AZGARD_KEY_SACNCODES

namespace Azgard {
enum KeyScanCode {
    KEY_SCANCODE_UNKNOWN = 0,
    KEY_SCANCODE_A = 4,
    KEY_SCANCODE_B = 5,
    KEY_SCANCODE_C = 6,
    KEY_SCANCODE_D = 7,
    KEY_SCANCODE_E = 8,
    KEY_SCANCODE_F = 9,
    KEY_SCANCODE_G = 10,
    KEY_SCANCODE_H = 11,
    KEY_SCANCODE_I = 12,
    KEY_SCANCODE_J = 13,
    KEY_SCANCODE_K = 14,
    KEY_SCANCODE_L = 15,
    KEY_SCANCODE_M = 16,
    KEY_SCANCODE_N = 17,
    KEY_SCANCODE_O = 18,
    KEY_SCANCODE_P = 19,
    KEY_SCANCODE_Q = 20,
    KEY_SCANCODE_R = 21,
    KEY_SCANCODE_S = 22,
    KEY_SCANCODE_T = 23,
    KEY_SCANCODE_U = 24,
    KEY_SCANCODE_V = 25,
    KEY_SCANCODE_W = 26,
    KEY_SCANCODE_X = 27,
    KEY_SCANCODE_Y = 28,
    KEY_SCANCODE_Z = 29,
    KEY_SCANCODE_1 = 30,
    KEY_SCANCODE_2 = 31,
    KEY_SCANCODE_3 = 32,
    KEY_SCANCODE_4 = 33,
    KEY_SCANCODE_5 = 34,
    KEY_SCANCODE_6 = 35,
    KEY_SCANCODE_7 = 36,
    KEY_SCANCODE_8 = 37,
    KEY_SCANCODE_9 = 38,
    KEY_SCANCODE_0 = 39,
    KEY_SCANCODE_RETURN = 40,
    KEY_SCANCODE_ESCAPE = 41,
    KEY_SCANCODE_BACKSPACE = 42,
    KEY_SCANCODE_TAB = 43,
    KEY_SCANCODE_SPACE = 44,
    KEY_SCANCODE_MINUS = 45,
    KEY_SCANCODE_EQUALS = 46,
    KEY_SCANCODE_LEFTBRACKET = 47,
    KEY_SCANCODE_RIGHTBRACKET = 48,
    KEY_SCANCODE_BACKSLASH = 49,
    KEY_SCANCODE_NONUSHASH = 50,
    KEY_SCANCODE_SEMICOLON = 51,
    KEY_SCANCODE_APOSTROPHE = 52,
    KEY_SCANCODE_GRAVE = 53,
    KEY_SCANCODE_COMMA = 54,
    KEY_SCANCODE_PERIOD = 55,
    KEY_SCANCODE_SLASH = 56,
    KEY_SCANCODE_CAPSLOCK = 57,
    KEY_SCANCODE_F1 = 58,
    KEY_SCANCODE_F2 = 59,
    KEY_SCANCODE_F3 = 60,
    KEY_SCANCODE_F4 = 61,
    KEY_SCANCODE_F5 = 62,
    KEY_SCANCODE_F6 = 63,
    KEY_SCANCODE_F7 = 64,
    KEY_SCANCODE_F8 = 65,
    KEY_SCANCODE_F9 = 66,
    KEY_SCANCODE_F10 = 67,
    KEY_SCANCODE_F11 = 68,
    KEY_SCANCODE_F12 = 69,
    KEY_SCANCODE_PRINTSCREEN = 70,
    KEY_SCANCODE_SCROLLLOCK = 71,
    KEY_SCANCODE_PAUSE = 72,
    KEY_SCANCODE_INSERT = 73,
    KEY_SCANCODE_HOME = 74,
    KEY_SCANCODE_PAGEUP = 75,
    KEY_SCANCODE_DELETE = 76,
    KEY_SCANCODE_END = 77,
    KEY_SCANCODE_PAGEDOWN = 78,
    KEY_SCANCODE_RIGHT = 79,
    KEY_SCANCODE_LEFT = 80,
    KEY_SCANCODE_DOWN = 81,
    KEY_SCANCODE_UP = 82,
    KEY_SCANCODE_NUMLOCKCLEAR = 83,
    KEY_SCANCODE_KP_DIVIDE = 84,
    KEY_SCANCODE_KP_MULTIPLY = 85,
    KEY_SCANCODE_KP_MINUS = 86,
    KEY_SCANCODE_KP_PLUS = 87,
    KEY_SCANCODE_KP_ENTER = 88,
    KEY_SCANCODE_KP_1 = 89,
    KEY_SCANCODE_KP_2 = 90,
    KEY_SCANCODE_KP_3 = 91,
    KEY_SCANCODE_KP_4 = 92,
    KEY_SCANCODE_KP_5 = 93,
    KEY_SCANCODE_KP_6 = 94,
    KEY_SCANCODE_KP_7 = 95,
    KEY_SCANCODE_KP_8 = 96,
    KEY_SCANCODE_KP_9 = 97,
    KEY_SCANCODE_KP_0 = 98,
    KEY_SCANCODE_KP_PERIOD = 99,
    KEY_SCANCODE_NONUSBACKSLASH = 100,
    KEY_SCANCODE_APPLICATION = 101,
    KEY_SCANCODE_POWER = 102,
    KEY_SCANCODE_KP_EQUALS = 103,
    KEY_SCANCODE_F13 = 104,
    KEY_SCANCODE_F14 = 105,
    KEY_SCANCODE_F15 = 106,
    KEY_SCANCODE_F16 = 107,
    KEY_SCANCODE_F17 = 108,
    KEY_SCANCODE_F18 = 109,
    KEY_SCANCODE_F19 = 110,
    KEY_SCANCODE_F20 = 111,
    KEY_SCANCODE_F21 = 112,
    KEY_SCANCODE_F22 = 113,
    KEY_SCANCODE_F23 = 114,
    KEY_SCANCODE_F24 = 115,
    KEY_SCANCODE_EXECUTE = 116,
    KEY_SCANCODE_HELP = 117,
    KEY_SCANCODE_MENU = 118,
    KEY_SCANCODE_SELECT = 119,
    KEY_SCANCODE_STOP = 120,
    KEY_SCANCODE_AGAIN = 121,
    KEY_SCANCODE_UNDO = 122,
    KEY_SCANCODE_CUT = 123,
    KEY_SCANCODE_COPY = 124,
    KEY_SCANCODE_PASTE = 125,
    KEY_SCANCODE_FIND = 126,
    KEY_SCANCODE_MUTE = 127,
    KEY_SCANCODE_VOLUMEUP = 128,
    KEY_SCANCODE_VOLUMEDOWN = 129,
    KEY_SCANCODE_KP_COMMA = 133,
    KEY_SCANCODE_KP_EQUALSAS400 = 134,
    KEY_SCANCODE_INTERNATIONAL1 = 135,
    KEY_SCANCODE_INTERNATIONAL2 = 136,
    KEY_SCANCODE_INTERNATIONAL3 = 137,
    KEY_SCANCODE_INTERNATIONAL4 = 138,
    KEY_SCANCODE_INTERNATIONAL5 = 139,
    KEY_SCANCODE_INTERNATIONAL6 = 140,
    KEY_SCANCODE_INTERNATIONAL7 = 141,
    KEY_SCANCODE_INTERNATIONAL8 = 142,
    KEY_SCANCODE_INTERNATIONAL9 = 143,
    KEY_SCANCODE_LANG1 = 144,
    KEY_SCANCODE_LANG2 = 145,
    KEY_SCANCODE_LANG3 = 146,
    KEY_SCANCODE_LANG4 = 147,
    KEY_SCANCODE_LANG5 = 148,
    KEY_SCANCODE_LANG6 = 149,
    KEY_SCANCODE_LANG7 = 150,
    KEY_SCANCODE_LANG8 = 151,
    KEY_SCANCODE_LANG9 = 152,
    KEY_SCANCODE_ALTERASE = 153,
    KEY_SCANCODE_SYSREQ = 154,
    KEY_SCANCODE_CANCEL = 155,
    KEY_SCANCODE_CLEAR = 156,
    KEY_SCANCODE_PRIOR = 157,
    KEY_SCANCODE_RETURN2 = 158,
    KEY_SCANCODE_SEPARATOR = 159,
    KEY_SCANCODE_OUT = 160,
    KEY_SCANCODE_OPER = 161,
    KEY_SCANCODE_CLEARAGAIN = 162,
    KEY_SCANCODE_CRSEL = 163,
    KEY_SCANCODE_EXSEL = 164,
    KEY_SCANCODE_KP_00 = 176,
    KEY_SCANCODE_KP_000 = 177,
    KEY_SCANCODE_THOUSANDSSEPARATOR = 178,
    KEY_SCANCODE_DECIMALSEPARATOR = 179,
    KEY_SCANCODE_CURRENCYUNIT = 180,
    KEY_SCANCODE_CURRENCYSUBUNIT = 181,
    KEY_SCANCODE_KP_LEFTPAREN = 182,
    KEY_SCANCODE_KP_RIGHTPAREN = 183,
    KEY_SCANCODE_KP_LEFTBRACE = 184,
    KEY_SCANCODE_KP_RIGHTBRACE = 185,
    KEY_SCANCODE_KP_TAB = 186,
    KEY_SCANCODE_KP_BACKSPACE = 187,
    KEY_SCANCODE_KP_A = 188,
    KEY_SCANCODE_KP_B = 189,
    KEY_SCANCODE_KP_C = 190,
    KEY_SCANCODE_KP_D = 191,
    KEY_SCANCODE_KP_E = 192,
    KEY_SCANCODE_KP_F = 193,
    KEY_SCANCODE_KP_XOR = 194,
    KEY_SCANCODE_KP_POWER = 195,
    KEY_SCANCODE_KP_PERCENT = 196,
    KEY_SCANCODE_KP_LESS = 197,
    KEY_SCANCODE_KP_GREATER = 198,
    KEY_SCANCODE_KP_AMPERSAND = 199,
    KEY_SCANCODE_KP_DBLAMPERSAND = 200,
    KEY_SCANCODE_KP_VERTICALBAR = 201,
    KEY_SCANCODE_KP_DBLVERTICALBAR = 202,
    KEY_SCANCODE_KP_COLON = 203,
    KEY_SCANCODE_KP_HASH = 204,
    KEY_SCANCODE_KP_SPACE = 205,
    KEY_SCANCODE_KP_AT = 206,
    KEY_SCANCODE_KP_EXCLAM = 207,
    KEY_SCANCODE_KP_MEMSTORE = 208,
    KEY_SCANCODE_KP_MEMRECALL = 209,
    KEY_SCANCODE_KP_MEMCLEAR = 210,
    KEY_SCANCODE_KP_MEMADD = 211,
    KEY_SCANCODE_KP_MEMSUBTRACT = 212,
    KEY_SCANCODE_KP_MEMMULTIPLY = 213,
    KEY_SCANCODE_KP_MEMDIVIDE = 214,
    KEY_SCANCODE_KP_PLUSMINUS = 215,
    KEY_SCANCODE_KP_CLEAR = 216,
    KEY_SCANCODE_KP_CLEARENTRY = 217,
    KEY_SCANCODE_KP_BINARY = 218,
    KEY_SCANCODE_KP_OCTAL = 219,
    KEY_SCANCODE_KP_DECIMAL = 220,
    KEY_SCANCODE_KP_HEXADECIMAL = 221,
    KEY_SCANCODE_LCTRL = 224,
    KEY_SCANCODE_LSHIFT = 225,
    KEY_SCANCODE_LALT = 226,
    KEY_SCANCODE_LGUI = 227,
    KEY_SCANCODE_RCTRL = 228,
    KEY_SCANCODE_RSHIFT = 229,
    KEY_SCANCODE_RALT = 230,
    KEY_SCANCODE_RGUI = 231,
    KEY_SCANCODE_MODE = 257,
    KEY_SCANCODE_AUDIONEXT = 258,
    KEY_SCANCODE_AUDIOPREV = 259,
    KEY_SCANCODE_AUDIOSTOP = 260,
    KEY_SCANCODE_AUDIOPLAY = 261,
    KEY_SCANCODE_AUDIOMUTE = 262,
    KEY_SCANCODE_MEDIASELECT = 263,
    KEY_SCANCODE_WWW = 264,
    KEY_SCANCODE_MAIL = 265,
    KEY_SCANCODE_CALCULATOR = 266,
    KEY_SCANCODE_COMPUTER = 267,
    KEY_SCANCODE_AC_SEARCH = 268,
    KEY_SCANCODE_AC_HOME = 269,
    KEY_SCANCODE_AC_BACK = 270,
    KEY_SCANCODE_AC_FORWARD = 271,
    KEY_SCANCODE_AC_STOP = 272,
    KEY_SCANCODE_AC_REFRESH = 273,
    KEY_SCANCODE_AC_BOOKMARKS = 274,
    KEY_SCANCODE_BRIGHTNESSDOWN = 275,
    KEY_SCANCODE_BRIGHTNESSUP = 276,
    KEY_SCANCODE_DISPLAYSWITCH = 277,
    KEY_SCANCODE_KBDILLUMTOGGLE = 278,
    KEY_SCANCODE_KBDILLUMDOWN = 279,
    KEY_SCANCODE_KBDILLUMUP = 280,
    KEY_SCANCODE_EJECT = 281,
    KEY_SCANCODE_SLEEP = 282,
    KEY_SCANCODE_APP1 = 283,
    KEY_SCANCODE_APP2 = 284,
    KEY_NUM_SCANCODES = 512
};

}


#endif
