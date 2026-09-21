#pragma once

#include <cstdint>
#include <queue>

class KeyboardBuffer
{
public:

    void push(
            uint8_t value);

    bool hasData() const;

    uint8_t pop();

    uint8_t peek() const;

private:

    std::queue<uint8_t> buffer_;
};