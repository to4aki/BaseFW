#include "machine/device/RamDevice.h"

RamDevice::RamDevice(
        size_t size)
        :
        ram_(
                size,
                0) {
}

uint8_t RamDevice::read(
        uint16_t address) {
    if (address >= ram_.size()) {
        return 0xFF;
    }

    return ram_[address];
}

void RamDevice::write(
        uint16_t address,
        uint8_t value) {
    if (address >= ram_.size()) {
        return;
    }

    ram_[address] =
            value;
}