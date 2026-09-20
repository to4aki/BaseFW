#include "FrameBufferMachine.h"

#include "Color.h"

FrameBufferMachine::FrameBufferMachine(
        int width,
        int height)
        :
        fb_(
                width,
                height),
        width_(width),
        height_(height)
{
}

void FrameBufferMachine::reset()
{
    fb_.clear(
            Color::BLACK);

    ui_.clear();

    onReset();
}

void FrameBufferMachine::runFrame()
{
    fb_.clear(
            Color::BLACK);

    onFrame();

    ui_.draw(
            fb_);
}

void FrameBufferMachine::onReset()
{
}

void FrameBufferMachine::onFrame()
{
}

uint32_t* FrameBufferMachine::frameBuffer()
{
    return fb_.data();
}

int FrameBufferMachine::width() const
{
    return width_;
}

int FrameBufferMachine::height() const
{
    return height_;
}