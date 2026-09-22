#pragma once

#include <cstdint>

#include "engine/KeyboardBuffer.h"

#include "gfx/TextConsole.h"

#include "machine/bus/IIoBus.h"
#include "machine/device/Ports.h"

class IoBus
        : public IIoBus {
public:

    IoBus(
            KeyboardBuffer *keyboard,
            TextConsole *console);

    uint8_t in(
            uint16_t port)
    override;

    void out(
            uint16_t port,
            uint8_t value)
    override;

private:

    KeyboardBuffer *keyboard_;

    TextConsole *console_;
};