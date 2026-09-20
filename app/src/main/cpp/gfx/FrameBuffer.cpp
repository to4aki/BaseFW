#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(
        int width,
        int height)
        :
        width_(width),
        height_(height),
        pixels_(width * height)
{
}

void FrameBuffer::clear(
        uint32_t color)
{
    std::fill(
            pixels_.begin(),
            pixels_.end(),
            color);
}

void FrameBuffer::setPixel(
        int x,
        int y,
        uint32_t color)
{
    if(x < 0 || x >= width_)
        return;

    if(y < 0 || y >= height_)
        return;

    pixels_[y * width_ + x]
            = color;
}

uint32_t* FrameBuffer::data()
{
    return pixels_.data();
}

int FrameBuffer::width() const
{
    return width_;
}

int FrameBuffer::height() const
{
    return height_;
}
