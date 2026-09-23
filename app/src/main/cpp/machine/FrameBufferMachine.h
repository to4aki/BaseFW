#pragma once

#include <android/asset_manager.h>

#include <cstdint>

#include "AndroidOut.h"

#include "engine/Keyboard.h"
#include "engine/KeyboardBuffer.h"

#include "gfx/Color.h"
#include "gfx/FrameBuffer.h"
#include "gfx/IConsole.h"

#include "gfx/widget/WidgetManager.h"

#include "machine/IMachine.h"

class FrameBufferMachine
        : public IMachine {
public:

    FrameBufferMachine(
            int width,
            int height);

    virtual ~FrameBufferMachine() = default;

    void reset() override final;

    void runFrame() override final;

    uint32_t *frameBuffer() override;

    int width() const override;

    int height() const override;

    void setAssetManager(
            AAssetManager *assetManager);

protected:

    enum class InputLayer {
        MENU,
        CONSOLE
    };

    virtual void onInitUi();

    virtual void onReset();

    virtual void onFrame();

    virtual void onMenuFrame();

    virtual void onConsoleFrame();

    virtual void handleConsoleKey(uint8_t ch);

    uint8_t readKeyboard();

    void writeConsole(uint8_t value);

    AAssetManager *assetManager() const;

    FrameBuffer fb_;

    WidgetManager ui_;

    IConsole *console_ = nullptr;

    void setConsole(
            IConsole *console);

    KeyboardBuffer keyboard_;

    int width_;

    int height_;

    InputLayer inputLayer_ = InputLayer::MENU;

private:

    void handleInput();

    bool initialized_ = false;

    AAssetManager *assetManager_ = nullptr;
};