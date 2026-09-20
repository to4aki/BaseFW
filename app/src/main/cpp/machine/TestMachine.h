#pragma once

#include "AndroidOut.h"

#include "FrameBufferMachine.h"
#include "StatusBarWidget.h"
#include "PanelWidget.h"
#include "LabelWidget.h"

class TestMachine
        : public FrameBufferMachine
{
public:

    static constexpr int WIDTH = 320;
    static constexpr int HEIGHT = 200;

    TestMachine();

protected:

    void onReset() override;

    void onFrame() override;
};