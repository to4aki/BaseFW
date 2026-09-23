#pragma once

#include <string>
#include <cstring>

#include "gfx/Color.h"
#include "gfx/Draw.h"
#include "gfx/IConsole.h"
#include "gfx/FrameBuffer.h"

class FrameBuffer;

class TextConsole
        : public IConsole {
public:

    static constexpr int COLS = 40;
    static constexpr int ROWS = 25;

    TextConsole();

    void locate(
            int x,
            int y);

    void putString(
            const std::string &text);

    void clear() override;

    void putChar(
            char ch) override;

    void draw(
            FrameBuffer &fb,
            int baseX,
            int baseY) override;

private:

    void scroll();

    char vram_[ROWS][COLS];
    bool wrapped_[ROWS];

    int cursorX_ = 0;
    int cursorY_ = 0;

    bool escapeMode_ = false;

    std::string escapeBuffer_;

};