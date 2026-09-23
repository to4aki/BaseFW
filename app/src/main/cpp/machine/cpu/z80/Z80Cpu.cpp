#include <android/log.h>
#include "machine/cpu/z80/Z80Cpu.h"

static Z80EX_BYTE cpu_read(
        Z80EX_CONTEXT *cpu,
        Z80EX_WORD addr,
        int m1_state,
        void *user_data) {
    auto *context =
            static_cast<Z80Context *>(
                    user_data);

    return context->memory->read(
            addr);
}

static void cpu_write(
        Z80EX_CONTEXT *cpu,
        Z80EX_WORD addr,
        Z80EX_BYTE value,
        void *user_data) {
    auto *context =
            static_cast<Z80Context *>(
                    user_data);

    context->memory->write(
            addr,
            value);
}

static Z80EX_BYTE cpu_in(
        Z80EX_CONTEXT *cpu,
        Z80EX_WORD port,
        void *user_data) {
    auto *context =
            static_cast<Z80Context *>(
                    user_data);

    return context->io->in(
            port);
}

static void cpu_out(
        Z80EX_CONTEXT *cpu,
        Z80EX_WORD port,
        Z80EX_BYTE value,
        void *user_data) {
    auto *context =
            static_cast<Z80Context *>(
                    user_data);

    context->io->out(
            port,
            value);
}

static Z80EX_BYTE cpu_intread(
        Z80EX_CONTEXT *cpu,
        void *user_data) {
    return 0;
}

Z80Cpu::Z80Cpu(
        IMemoryBus *memory,
        IIoBus *io) {
    context_.memory = memory;
    context_.io = io;
    cpu_ =
            z80ex_create(
                    cpu_read,
                    &context_,

                    cpu_write,
                    &context_,

                    cpu_in,
                    &context_,

                    cpu_out,
                    &context_,

                    cpu_intread,
                    &context_);
}

Z80Cpu::~Z80Cpu() {
    if (cpu_) {
        z80ex_destroy(cpu_);
    }
}

void Z80Cpu::reset() {
    z80ex_reset(cpu_);
}

void Z80Cpu::runCycles(
        int cycles) {
    static bool first = true;

    if (first) {
        first = false;
    }

    int executed = 0;

    while (executed < cycles) {
        executed +=
                z80ex_step(
                        cpu_);
    }
}

void Z80Cpu::interrupt() {
    int cycles = z80ex_int(cpu_);
}