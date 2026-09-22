#pragma once

#include <cstdint>
#include <queue>

class Input {
public:

    enum Key {
        UP,
        DOWN,
        LEFT,
        RIGHT,

        ENTER,
        ESC,

        TAB,
        SPACE,

        BACKSPACE,
        DELETE_KEY,

        HOME,
        END,

        PAGE_UP,
        PAGE_DOWN,

        INSERT,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        NUM0,
        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,
        NUM7,
        NUM8,
        NUM9,

        COUNT
    };

    struct KeyMap {
        int androidKey;
        Key key;
    };

    static const KeyMap keyMap[];
    static const int keyMapCount;

    static void setKey(
            Key key,
            bool down);

    static bool isDown(
            Key key);

    static bool isPressed(
            Key key);

    static void endFrame();

    static void pushChar(
            char ch);

    static bool getChar(
            char &ch);

private:

    static bool current_[COUNT];
    static bool previous_[COUNT];

    static std::queue<char>
            charQueue_;
};