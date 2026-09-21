#pragma once

#include <cstdint>

class Input
{
public:

    enum Key
    {
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

        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,

        COUNT
    };

    struct KeyMap
    {
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

private:

    static bool current_[COUNT];
    static bool previous_[COUNT];
};