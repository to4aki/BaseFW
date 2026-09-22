#include "machine/device/RomDevice.h"

bool RomDevice::load(
        const uint8_t *data,
        size_t size) {
    rom_.assign(
            data,
            data + size);

    return true;
}

void RomDevice::program(
        uint16_t address,
        uint8_t value) {
    if (address >= rom_.size()) {
        rom_.resize(
                address + 1,
                0xFF);
    }

    rom_[address] =
            value;
}

uint8_t RomDevice::read(
        uint16_t address) {
    if (address >= rom_.size()) {
        return 0xFF;
    }

    return rom_[address];
}

void RomDevice::write(
        uint16_t address,
        uint8_t value) {
    /*
     * ROMなので無視
     */
}