#ifndef ARDUINO_CONF_TOOL_GEN_KEYMAP_H
#define ARDUINO_CONF_TOOL_GEN_KEYMAP_H

void fillKeymap(std::map<const std::string, unsigned char> &keymap) {
    /*keymap.insert(std::make_pair("KEY_MOD_LCTRL",  0x01));
    keymap.insert(std::make_pair("KEY_MOD_LSHIFT", 0x02));
    keymap.insert(std::make_pair("KEY_MOD_LALT",   0x04));
    keymap.insert(std::make_pair("KEY_MOD_LMETA",  0x08));
    keymap.insert(std::make_pair("KEY_MOD_RCTRL",  0x10));
    keymap.insert(std::make_pair("KEY_MOD_RSHIFT", 0x20));
    keymap.insert(std::make_pair("KEY_MOD_RALT",   0x40));
    keymap.insert(std::make_pair("KEY_MOD_RMETA",  0x80));*/
    keymap.insert(std::make_pair("KEY_NONE", 0x00));// No key pressed
    keymap.insert(std::make_pair("KEY_ERR_OVF", 0x01));//  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
    keymap.insert(std::make_pair("KEY_A", 0x04));// Keyboard a and A
    keymap.insert(std::make_pair("KEY_B", 0x05));// Keyboard b and B
    keymap.insert(std::make_pair("KEY_C", 0x06));// Keyboard c and C
    keymap.insert(std::make_pair("KEY_D", 0x07));// Keyboard d and D
    keymap.insert(std::make_pair("KEY_E", 0x08));// Keyboard e and E
    keymap.insert(std::make_pair("KEY_F", 0x09));// Keyboard f and F
    keymap.insert(std::make_pair("KEY_G", 0x0a));// Keyboard g and G
    keymap.insert(std::make_pair("KEY_H", 0x0b));// Keyboard h and H
    keymap.insert(std::make_pair("KEY_I", 0x0c));// Keyboard i and I
    keymap.insert(std::make_pair("KEY_J", 0x0d));// Keyboard j and J
    keymap.insert(std::make_pair("KEY_K", 0x0e));// Keyboard k and K
    keymap.insert(std::make_pair("KEY_L", 0x0f));// Keyboard l and L
    keymap.insert(std::make_pair("KEY_M", 0x10));// Keyboard m and M
    keymap.insert(std::make_pair("KEY_N", 0x11));// Keyboard n and N
    keymap.insert(std::make_pair("KEY_O", 0x12));// Keyboard o and O
    keymap.insert(std::make_pair("KEY_P", 0x13));// Keyboard p and P
    keymap.insert(std::make_pair("KEY_Q", 0x14));// Keyboard q and Q
    keymap.insert(std::make_pair("KEY_R", 0x15));// Keyboard r and R
    keymap.insert(std::make_pair("KEY_S", 0x16));// Keyboard s and S
    keymap.insert(std::make_pair("KEY_T", 0x17));// Keyboard t and T
    keymap.insert(std::make_pair("KEY_U", 0x18));// Keyboard u and U
    keymap.insert(std::make_pair("KEY_V", 0x19));// Keyboard v and V
    keymap.insert(std::make_pair("KEY_W", 0x1a));// Keyboard w and W
    keymap.insert(std::make_pair("KEY_X", 0x1b));// Keyboard x and X
    keymap.insert(std::make_pair("KEY_Y", 0x1c));// Keyboard y and Y
    keymap.insert(std::make_pair("KEY_Z", 0x1d));// Keyboard z and Z
    keymap.insert(std::make_pair("KEY_1", 0x1e));// Keyboard 1 and !
    keymap.insert(std::make_pair("KEY_2", 0x1f));// Keyboard 2 and @
    keymap.insert(std::make_pair("KEY_3", 0x20));// Keyboard 3 and #
    keymap.insert(std::make_pair("KEY_4", 0x21));// Keyboard 4 and $
    keymap.insert(std::make_pair("KEY_5", 0x22));// Keyboard 5 and %
    keymap.insert(std::make_pair("KEY_6", 0x23));// Keyboard 6 and ^
    keymap.insert(std::make_pair("KEY_7", 0x24));// Keyboard 7 and &
    keymap.insert(std::make_pair("KEY_8", 0x25));// Keyboard 8 and *
    keymap.insert(std::make_pair("KEY_9", 0x26));// Keyboard 9 and (
    keymap.insert(std::make_pair("KEY_0", 0x27));// Keyboard 0 and )
    keymap.insert(std::make_pair("KEY_ENTER", 0x28));// Keyboard Return (ENTER)
    keymap.insert(std::make_pair("KEY_ESC", 0x29));// Keyboard ESCAPE
    keymap.insert(std::make_pair("KEY_BACKSPACE", 0x2a));// Keyboard DELETE (Backspace)
    keymap.insert(std::make_pair("KEY_TAB", 0x2b));// Keyboard Tab
    keymap.insert(std::make_pair("KEY_SPACE", 0x2c));// Keyboard Spacebar
    keymap.insert(std::make_pair("KEY_MINUS", 0x2d));// Keyboard - and _
    keymap.insert(std::make_pair("KEY_EQUAL", 0x2e));// Keyboard = and +
    keymap.insert(std::make_pair("KEY_LEFTBRACE", 0x2f));// Keyboard [ and {
    keymap.insert(std::make_pair("KEY_RIGHTBRACE", 0x30));// Keyboard ] and }
    keymap.insert(std::make_pair("KEY_BACKSLASH", 0x31));// Keyboard \ and |
    keymap.insert(std::make_pair("KEY_HASHTILDE", 0x32));// Keyboard Non-US # and ~
    keymap.insert(std::make_pair("KEY_SEMICOLON", 0x33));// Keyboard ; and :
    keymap.insert(std::make_pair("KEY_APOSTROPHE", 0x34));// Keyboard ' and "
    keymap.insert(std::make_pair("KEY_GRAVE", 0x35));// Keyboard ` and ~
    keymap.insert(std::make_pair("KEY_COMMA", 0x36));// Keyboard , and <
    keymap.insert(std::make_pair("KEY_DOT", 0x37));// Keyboard . and >
    keymap.insert(std::make_pair("KEY_SLASH", 0x38));// Keyboard / and ?
    keymap.insert(std::make_pair("KEY_CAPSLOCK", 0x39));// Keyboard Caps Lock
    keymap.insert(std::make_pair("KEY_F1", 0x3a));// Keyboard F1
    keymap.insert(std::make_pair("KEY_F2", 0x3b));// Keyboard F2
    keymap.insert(std::make_pair("KEY_F3", 0x3c));// Keyboard F3
    keymap.insert(std::make_pair("KEY_F4", 0x3d));// Keyboard F4
    keymap.insert(std::make_pair("KEY_F5", 0x3e));// Keyboard F5
    keymap.insert(std::make_pair("KEY_F6", 0x3f));// Keyboard F6
    keymap.insert(std::make_pair("KEY_F7", 0x40));// Keyboard F7
    keymap.insert(std::make_pair("KEY_F8", 0x41));// Keyboard F8
    keymap.insert(std::make_pair("KEY_F9", 0x42));// Keyboard F9
    keymap.insert(std::make_pair("KEY_F10", 0x43));// Keyboard F10
    keymap.insert(std::make_pair("KEY_F11", 0x44));// Keyboard F11
    keymap.insert(std::make_pair("KEY_F12", 0x45));// Keyboard F12
    keymap.insert(std::make_pair("KEY_SYSRQ", 0x46));// Keyboard Print Screen
    keymap.insert(std::make_pair("KEY_SCROLLLOCK", 0x47));// Keyboard Scroll Lock
    keymap.insert(std::make_pair("KEY_PAUSE", 0x48));// Keyboard Pause
    keymap.insert(std::make_pair("KEY_INSERT", 0x49));// Keyboard Insert
    keymap.insert(std::make_pair("KEY_HOME", 0x4a));// Keyboard Home
    keymap.insert(std::make_pair("KEY_PAGEUP", 0x4b));// Keyboard Page Up
    keymap.insert(std::make_pair("KEY_DELETE", 0x4c));// Keyboard Delete Forward
    keymap.insert(std::make_pair("KEY_END", 0x4d));// Keyboard End
    keymap.insert(std::make_pair("KEY_PAGEDOWN", 0x4e));// Keyboard Page Down
    keymap.insert(std::make_pair("KEY_RIGHT", 0x4f));// Keyboard Right Arrow
    keymap.insert(std::make_pair("KEY_LEFT", 0x50));// Keyboard Left Arrow
    keymap.insert(std::make_pair("KEY_DOWN", 0x51));// Keyboard Down Arrow
    keymap.insert(std::make_pair("KEY_UP", 0x52));// Keyboard Up Arrow
    keymap.insert(std::make_pair("KEY_NUMLOCK", 0x53));// Keyboard Num Lock and Clear
    keymap.insert(std::make_pair("KEY_KPSLASH", 0x54));// Keypad /
    keymap.insert(std::make_pair("KEY_KPASTERISK", 0x55));// Keypad *
    keymap.insert(std::make_pair("KEY_KPMINUS", 0x56));// Keypad -
    keymap.insert(std::make_pair("KEY_KPPLUS", 0x57));// Keypad +
    keymap.insert(std::make_pair("KEY_KPENTER", 0x58));// Keypad ENTER
    keymap.insert(std::make_pair("KEY_KP1", 0x59));// Keypad 1 and End
    keymap.insert(std::make_pair("KEY_KP2", 0x5a));// Keypad 2 and Down Arrow
    keymap.insert(std::make_pair("KEY_KP3", 0x5b));// Keypad 3 and PageDn
    keymap.insert(std::make_pair("KEY_KP4", 0x5c));// Keypad 4 and Left Arrow
    keymap.insert(std::make_pair("KEY_KP5", 0x5d));// Keypad 5
    keymap.insert(std::make_pair("KEY_KP6", 0x5e));// Keypad 6 and Right Arrow
    keymap.insert(std::make_pair("KEY_KP7", 0x5f));// Keypad 7 and Home
    keymap.insert(std::make_pair("KEY_KP8", 0x60));// Keypad 8 and Up Arrow
    keymap.insert(std::make_pair("KEY_KP9", 0x61));// Keypad 9 and Page Up
    keymap.insert(std::make_pair("KEY_KP0", 0x62));// Keypad 0 and Insert
    keymap.insert(std::make_pair("KEY_KPDOT", 0x63));// Keypad . and Delete
    keymap.insert(std::make_pair("KEY_102ND", 0x64));// Keyboard Non-US \ and |
    keymap.insert(std::make_pair("KEY_COMPOSE", 0x65));// Keyboard Application
    keymap.insert(std::make_pair("KEY_POWER", 0x66));// Keyboard Power
    keymap.insert(std::make_pair("KEY_KPEQUAL", 0x67));// Keypad =
    keymap.insert(std::make_pair("KEY_F13", 0x68));// Keyboard F13
    keymap.insert(std::make_pair("KEY_F14", 0x69));// Keyboard F14
    keymap.insert(std::make_pair("KEY_F15", 0x6a));// Keyboard F15
    keymap.insert(std::make_pair("KEY_F16", 0x6b));// Keyboard F16
    keymap.insert(std::make_pair("KEY_F17", 0x6c));// Keyboard F17
    keymap.insert(std::make_pair("KEY_F18", 0x6d));// Keyboard F18
    keymap.insert(std::make_pair("KEY_F19", 0x6e));// Keyboard F19
    keymap.insert(std::make_pair("KEY_F20", 0x6f));// Keyboard F20
    keymap.insert(std::make_pair("KEY_F21", 0x70));// Keyboard F21
    keymap.insert(std::make_pair("KEY_F22", 0x71));// Keyboard F22
    keymap.insert(std::make_pair("KEY_F23", 0x72));// Keyboard F23
    keymap.insert(std::make_pair("KEY_F24", 0x73));// Keyboard F24
    keymap.insert(std::make_pair("KEY_OPEN", 0x74));// Keyboard Execute
    keymap.insert(std::make_pair("KEY_HELP", 0x75));// Keyboard Help
    keymap.insert(std::make_pair("KEY_PROPS", 0x76));// Keyboard Menu
    keymap.insert(std::make_pair("KEY_FRONT", 0x77));// Keyboard Select
    keymap.insert(std::make_pair("KEY_STOP", 0x78));// Keyboard Stop
    keymap.insert(std::make_pair("KEY_AGAIN", 0x79));// Keyboard Again
    keymap.insert(std::make_pair("KEY_UNDO", 0x7a));// Keyboard Undo
    keymap.insert(std::make_pair("KEY_CUT", 0x7b));// Keyboard Cut
    keymap.insert(std::make_pair("KEY_COPY", 0x7c));// Keyboard Copy
    keymap.insert(std::make_pair("KEY_PASTE", 0x7d));// Keyboard Paste
    keymap.insert(std::make_pair("KEY_FIND", 0x7e));// Keyboard Find
    keymap.insert(std::make_pair("KEY_MUTE", 0x7f));// Keyboard Mute
    keymap.insert(std::make_pair("KEY_VOLUMEUP", 0x80));// Keyboard Volume Up
    keymap.insert(std::make_pair("KEY_VOLUMEDOWN", 0x81));// Keyboard Volume Down
    keymap.insert(std::make_pair("KEY_KPCOMMA", 0x85));// Keypad Comma
    keymap.insert(std::make_pair("KEY_RO", 0x87));// Keyboard International1
    keymap.insert(std::make_pair("KEY_KATAKANAHIRAGANA", 0x88));// Keyboard International2
    keymap.insert(std::make_pair("KEY_YEN", 0x89));// Keyboard International3
    keymap.insert(std::make_pair("KEY_HENKAN", 0x8a));// Keyboard International4
    keymap.insert(std::make_pair("KEY_MUHENKAN", 0x8b));// Keyboard International5
    keymap.insert(std::make_pair("KEY_KPJPCOMMA", 0x8c));// Keyboard International6
    keymap.insert(std::make_pair("KEY_HANGEUL", 0x90));// Keyboard LANG1
    keymap.insert(std::make_pair("KEY_HANJA", 0x91));// Keyboard LANG2
    keymap.insert(std::make_pair("KEY_KATAKANA", 0x92));// Keyboard LANG3
    keymap.insert(std::make_pair("KEY_HIRAGANA", 0x93));// Keyboard LANG4
    keymap.insert(std::make_pair("KEY_ZENKAKUHANKAKU", 0x94));// Keyboard LANG5
    keymap.insert(std::make_pair("KEY_KPLEFTPAREN", 0xb6));// Keypad (
    keymap.insert(std::make_pair("KEY_KPRIGHTPAREN", 0xb7));// Keypad )
    keymap.insert(std::make_pair("KEY_LEFTCTRL", 0xe0));// Keyboard Left Control
    keymap.insert(std::make_pair("KEY_LEFTSHIFT", 0xe1));// Keyboard Left Shift
    keymap.insert(std::make_pair("KEY_LEFTALT", 0xe2));// Keyboard Left Alt
    keymap.insert(std::make_pair("KEY_LEFTMETA", 0xe3));// Keyboard Left GUI
    keymap.insert(std::make_pair("KEY_RIGHTCTRL", 0xe4));// Keyboard Right Control
    keymap.insert(std::make_pair("KEY_RIGHTSHIFT", 0xe5));// Keyboard Right Shift
    keymap.insert(std::make_pair("KEY_RIGHTALT", 0xe6));// Keyboard Right Alt
    keymap.insert(std::make_pair("KEY_RIGHTMETA", 0xe7));// Keyboard Right GUI
    keymap.insert(std::make_pair("KEY_MEDIA_PLAYPAUSE", 0xe8));
    keymap.insert(std::make_pair("KEY_MEDIA_STOPCD", 0xe9));
    keymap.insert(std::make_pair("KEY_MEDIA_PREVIOUSSONG", 0xea));
    keymap.insert(std::make_pair("KEY_MEDIA_NEXTSONG", 0xeb));
    keymap.insert(std::make_pair("KEY_MEDIA_EJECTCD", 0xec));
    keymap.insert(std::make_pair("KEY_MEDIA_VOLUMEUP", 0xed));
    keymap.insert(std::make_pair("KEY_MEDIA_VOLUMEDOWN", 0xee));
    keymap.insert(std::make_pair("KEY_MEDIA_MUTE", 0xef));
    keymap.insert(std::make_pair("KEY_MEDIA_WWW", 0xf0));
    keymap.insert(std::make_pair("KEY_MEDIA_BACK", 0xf1));
    keymap.insert(std::make_pair("KEY_MEDIA_FORWARD", 0xf2));
    keymap.insert(std::make_pair("KEY_MEDIA_STOP", 0xf3));
    keymap.insert(std::make_pair("KEY_MEDIA_FIND", 0xf4));
    keymap.insert(std::make_pair("KEY_MEDIA_SCROLLUP", 0xf5));
    keymap.insert(std::make_pair("KEY_MEDIA_SCROLLDOWN", 0xf6));
    keymap.insert(std::make_pair("KEY_MEDIA_EDIT", 0xf7));
    keymap.insert(std::make_pair("KEY_MEDIA_SLEEP", 0xf8));
    keymap.insert(std::make_pair("KEY_MEDIA_COFFEE", 0xf9));
    keymap.insert(std::make_pair("KEY_MEDIA_REFRESH", 0xfa));
    keymap.insert(std::make_pair("KEY_MEDIA_CALC", 0xfb));
}

#endif //ARDUINO_CONF_TOOL_GEN_KEYMAP_H
