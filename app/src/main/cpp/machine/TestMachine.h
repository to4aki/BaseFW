#pragma once

#include "AndroidOut.h"
#include "FrameBufferMachine.h"

class TestMachine
        : public FrameBufferMachine
{
public:

    static constexpr int WIDTH = 320;
    static constexpr int HEIGHT = 216;

    TestMachine();

protected:

    void onInitUi() override;

    void onReset() override;

    void onFrame() override;

    void onMenuFrame() override;
};