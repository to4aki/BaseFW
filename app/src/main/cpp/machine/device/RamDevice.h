#pragma once

#include <cstdint>
#include <vector>

#include "machine/device/IMemoryRegion.h"

class RamDevice
        : public IMemoryRegion {
public:

    explicit RamDevice(
            size_t size);

    uint8_t read(
            uint16_t address)
    override;

    void write(
            uint16_t address,
            uint8_t value)
    override;

private:

    std::vector<uint8_t>
            ram_;
};