#pragma once

#include <cstdint>

class FrameBuffer;

class IConsole {
public:

    virtual ~IConsole() = default;

    virtual void clear() = 0;

    virtual void putChar(
            char ch) = 0;

    virtual void draw(
            FrameBuffer &fb,
            int baseX,
            int baseY) = 0;
};