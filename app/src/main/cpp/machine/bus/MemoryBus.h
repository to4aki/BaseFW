#pragma once

#include "machine/bus/IMemoryBus.h"

#include "machine/device/RomDevice.h"
#include "machine/device/RamDevice.h"

class MemoryBus
        : public IMemoryBus {
public:

    void setRom(
            RomDevice *rom);

    void setRam(
            RamDevice *ram);

    uint8_t read(
            uint16_t address) override;

    void write(
            uint16_t address,
            uint8_t value) override;

private:

    RomDevice *rom_ =
            nullptr;

    RamDevice *ram_ =
            nullptr;
};