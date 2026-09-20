#pragma once

#include "IMachine.h"
#include "FrameBuffer.h"
#include "WidgetManager.h"

class FrameBufferMachine
        : public IMachine
{
public:

    FrameBufferMachine(
            int width,
            int height);

    virtual ~FrameBufferMachine() = default;

    void reset() override final;

    void runFrame() override final;

    uint32_t* frameBuffer() override;

    int width() const override;

    int height() const override;

protected:

    virtual void onReset();

    virtual void onFrame();

protected:

    FrameBuffer fb_;

    WidgetManager ui_;

private:

    int width_;
    int height_;
};