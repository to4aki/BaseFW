#pragma once

#include <cstdint>
#include <queue>

enum class KeyboardLayout {
    US,
    JIS
};

class Keyboard {
public:

    static void putAndroidKey(
            int keyCode,
            int metaState);

    static bool hasData();

    static uint8_t read();

    static void clear();

    static void setLayout(
            KeyboardLayout layout);

private:
    static uint8_t convertKeyCode(
            int keyCode,
            int metaState);

    static uint8_t convertUsKeyCode(
            int keyCode,
            int metaState);

    static uint8_t convertJisKeyCode(
            int keyCode,
            int metaState);

    static KeyboardLayout
            layout_;

    static std::queue<uint8_t>
            queue_;
};
