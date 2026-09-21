#pragma once

#include <cstdint>

#include "AndroidOut.h"

#include "IMachine.h"
#include "FrameBuffer.h"
#include "WidgetManager.h"
#include "TextConsole.h"
#include "KeyboardBuffer.h"

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

    enum class InputLayer
    {
        MENU,
        CONSOLE
    };

    virtual void onInitUi();

    virtual void onReset();

    virtual void onFrame();

    virtual void onMenuFrame();

    virtual void onConsoleFrame();

    virtual void handleConsoleKey(
            uint8_t ch);

    uint8_t readKeyboard();

    void writeConsole(
            uint8_t value);

    FrameBuffer fb_;

    WidgetManager ui_;

    TextConsole console_;

    KeyboardBuffer keyboard_;

    int width_;

    int height_;

    InputLayer inputLayer_ =
            InputLayer::MENU;

private:

    void handleInput();

    bool initialized_ =
            false;
};