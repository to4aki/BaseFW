#pragma once

#include <string>
#include <cstring>

#include "gfx/Color.h"
#include "gfx/Draw.h"
#include "gfx/FrameBuffer.h"

class FrameBuffer;

class TextConsole {
public:

    static constexpr int COLS = 40;
    static constexpr int ROWS = 25;

    TextConsole();

    void clear();

    void locate(
            int x,
            int y);

    void putChar(
            char ch);

    void putString(
            const std::string &text);

    void draw(
            FrameBuffer &fb,
            int x,
            int y);

private:

    void scroll();

    char vram_[ROWS][COLS];

    int cursorX_ = 0;
    int cursorY_ = 0;
};