#pragma once

class ICpu {
public:

    virtual ~ICpu() = default;

    virtual void reset() = 0;

    virtual void runCycles(
            int cycles) = 0;
};