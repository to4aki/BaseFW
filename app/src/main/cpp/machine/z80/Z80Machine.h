#pragma once

#include "machine/FrameBufferMachine.h"
#include "machine/device/RomDevice.h"
#include "machine/device/RamDevice.h"
#include "machine/device/HexLoader.h"
#include "machine/bus/MemoryBus.h"
#include "machine/bus/IoBus.h"
#include "machine/cpu/z80/Z80Cpu.h"

#include "gfx/TextConsole.h"

class Z80Machine
        : public FrameBufferMachine {
public:
    Z80Machine();

    void raiseInterrupt();

protected:
    void onInitUi() override;

    void onReset() override;

    void onFrame() override;

    void handleConsoleKey(
            uint8_t ch) override;

private:
    bool loadRom(
            const char *fileName);

private:
    bool romLoaded_ = false;
    bool running_ = false;
    bool irqPending_ = false;

    RomDevice rom_;
    RamDevice ram_;
    MemoryBus memoryBus_;
    IoBus ioBus_;
    Z80Cpu cpu_;
    TextConsole console_;
};
