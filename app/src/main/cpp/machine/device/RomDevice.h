#pragma once

#include <cstdint>
#include <vector>

#include "machine/device/IMemoryRegion.h"

class RomDevice
        : public IMemoryRegion {
public:

    bool load(
            const uint8_t *data,
            size_t size);

    void program(
            uint16_t address,
            uint8_t value);

    uint8_t read(
            uint16_t address)
    override;

    void write(
            uint16_t address,
            uint8_t value)
    override;

private:

    std::vector<uint8_t>
            rom_;
};