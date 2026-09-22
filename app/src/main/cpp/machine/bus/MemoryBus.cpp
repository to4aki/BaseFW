#include <android/log.h>
#include "machine/bus/MemoryBus.h"

void MemoryBus::setRom(
        RomDevice *rom) {
    rom_ = rom;
}

void MemoryBus::setRam(
        RamDevice *ram) {
    ram_ = ram;
}

uint8_t MemoryBus::read(
        uint16_t address) {
    uint8_t value;

    if (address < 0x8000) {
        value = rom_->read(address);
    } else {
        value = ram_->read(address - 0x8000);
    }

    return value;
}

void MemoryBus::write(
        uint16_t address,
        uint8_t value) {
    if (address < 0x8000) {
        return;
    }

    ram_->write(
            address - 0x8000,
            value);
}