#pragma once

#include <cstdint>

class IMachine
{
public:
    virtual ~IMachine() = default;

    virtual void reset() = 0;

    virtual void runFrame() = 0;

    virtual uint32_t* frameBuffer() = 0;

    virtual int width() const = 0;

    virtual int height() const = 0;
};