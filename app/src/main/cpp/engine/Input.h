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

        COUNT
    };

    static void setKey(
            Key key,
            bool down);

    static bool isDown(
            Key key);

    static bool isPressed(
            Key key);

    static void endFrame();

    static void pressKey(
            Key key);

private:

    static bool current_[COUNT];
    static bool previous_[COUNT];
};