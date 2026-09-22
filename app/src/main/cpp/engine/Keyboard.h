#pragma once

#include <cstdint>
#include <queue>

class Keyboard {
public:

    static void putAndroidKey(
            int keyCode,
            int metaState);

    static bool hasData();

    static uint8_t read();

private:

    static uint8_t convertKeyCode(
            int keyCode,
            int metaState);

private:

    static std::queue<uint8_t>
            queue_;
};