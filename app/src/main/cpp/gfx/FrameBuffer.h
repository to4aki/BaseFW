#pragma once

#include <cstdint>
#include <vector>

class FrameBuffer
{
public:

    FrameBuffer(
            int width,
            int height);

    void clear(uint32_t color);

    void setPixel(
            int x,
            int y,
            uint32_t color);

    uint32_t* data();

    int width() const;
    int height() const;

private:

    int width_;
    int height_;

    std::vector<uint32_t> pixels_;
};
