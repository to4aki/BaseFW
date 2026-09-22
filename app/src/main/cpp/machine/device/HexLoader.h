#pragma once

#include <cstdint>
#include <sstream>
#include <string>

#include "machine/device/RomDevice.h"


class RomDevice;

class HexLoader {
public:

    static bool loadFromMemory(
            RomDevice &rom,
            const char *data,
            size_t size);
};