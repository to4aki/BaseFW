#pragma once

#include <cstdint>

class IIoBus {
public:

    virtual ~IIoBus() = default;

    virtual uint8_t in(
            uint16_t port) = 0;

    virtual void out(
            uint16_t port,
            uint8_t value) = 0;
};