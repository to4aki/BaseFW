#pragma once

#include "machine/bus/IMemoryBus.h"
#include "machine/bus/IIoBus.h"

struct Z80Context {
    IMemoryBus *memory;

    IIoBus *io;
};