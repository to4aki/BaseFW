#pragma once

#include <cstdint>

class RomDevice;

class IImageLoader
{
public:

    virtual ~IImageLoader() = default;

    virtual bool load(
            RomDevice& rom) = 0;
};
`