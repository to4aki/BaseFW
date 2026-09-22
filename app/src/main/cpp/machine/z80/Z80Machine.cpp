#include "machine/z80/Z80Machine.h"

#include "machine/device/HexLoader.h"

Z80Machine::Z80Machine()
        :
        FrameBufferMachine(
                256,
                216),
        ram_(32768),
        ioBus_(
                &keyboard_,
                &console_),
        cpu_(
                &memoryBus_,
                &ioBus_) {
    memoryBus_.setRom(&rom_);
    memoryBus_.setRam(&ram_);
}

bool Z80Machine::loadRom(
        const char *fileName) {

    if (assetManager() == nullptr) {
        return false;
    }

    AAsset *asset =
            AAssetManager_open(
                    assetManager(),
                    fileName,
                    AASSET_MODE_BUFFER);

    if (asset == nullptr) {
        return false;
    }

    const char *data =
            static_cast<const char *>(
                    AAsset_getBuffer(
                            asset));

    size_t size =
            AAsset_getLength(
                    asset);

    bool result =
            HexLoader::loadFromMemory(
                    rom_,
                    data,
                    size);

    AAsset_close(
            asset);

    if (result) {
        running_ = true;
    }

    return result;
}

void Z80Machine::onReset() {
    if (!romLoaded_) {
        romLoaded_ =
                loadRom(
                        "roms/rc2014_32k.hex");
    }

    if (romLoaded_) {
        cpu_.reset();
    }
}

#include <android/log.h>

void Z80Machine::onFrame() {
    if (!running_) {
        return;
    }

    if (irqPending_) {
        irqPending_ = false;

        cpu_.interrupt();
    }

    cpu_.runCycles(
            50000);
}

void Z80Machine::raiseInterrupt() {
    irqPending_ = true;
}

void Z80Machine::handleConsoleKey(
        uint8_t ch) {
    keyboard_.push(
            ch);

    raiseInterrupt();
}