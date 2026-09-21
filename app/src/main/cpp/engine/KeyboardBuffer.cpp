#include "KeyboardBuffer.h"

void KeyboardBuffer::push(
        uint8_t value)
{
    buffer_.push(
            value);
}

bool KeyboardBuffer::hasData() const
{
    return !buffer_.empty();
}

uint8_t KeyboardBuffer::pop()
{
    if(buffer_.empty())
    {
        return 0;
    }

    uint8_t value =
            buffer_.front();

    buffer_.pop();

    return value;
}

uint8_t KeyboardBuffer::peek() const
{
    if(buffer_.empty())
    {
        return 0;
    }

    return buffer_.front();
}