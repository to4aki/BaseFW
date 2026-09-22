#pragma once

#include "machine/cpu/ICpu.h"
#include "machine/cpu/z80/Z80Context.h"
#include "machine/cpu/z80/z80ex/include/z80ex.h"

class Z80Cpu
        : public ICpu {
public:

    Z80Cpu(
            IMemoryBus *memory,
            IIoBus *io);

    ~Z80Cpu();

    void reset() override;

    void runCycles(int cycles) override;

    void interrupt();

private:

    Z80Context context_;

    Z80EX_CONTEXT *cpu_;
};