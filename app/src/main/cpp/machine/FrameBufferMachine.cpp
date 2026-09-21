#include "FrameBufferMachine.h"

#include "Color.h"

FrameBufferMachine::FrameBufferMachine(
        int width,
        int height)
        :
        fb_(
                width,
                height),
        width_(width),
        height_(height)
{
}

void FrameBufferMachine::reset()
{
    if(!initialized_)
    {
        onInitUi();

        initialized_ =
                true;
    }

    fb_.clear(
            Color::BLACK);

    console_.clear();

    inputLayer_ =
            InputLayer::MENU;

    onReset();
}

void FrameBufferMachine::runFrame()
{
    static int counter = 0;

    counter++;

    if((counter % 60) == 0)
    {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "FRAME",
                "frame=%d",
                counter);
    }

    fb_.clear(
            Color::BLACK);

    handleInput();

    onFrame();

    console_.draw(
            fb_,
            0,
            16);

    ui_.draw(
            fb_);
}

void FrameBufferMachine::onFrame()
{
}

void FrameBufferMachine::onReset()
{
}

uint32_t* FrameBufferMachine::frameBuffer()
{
    return fb_.data();
}

int FrameBufferMachine::width() const
{
    return width_;
}

int FrameBufferMachine::height() const
{
    return height_;
}

void FrameBufferMachine::onInitUi()
{
}

void FrameBufferMachine::onMenuFrame()
{
}

void FrameBufferMachine::onConsoleFrame()
{
    if(Input::isPressed(Input::NUM1))
    {
        handleConsoleKey(
                '1');
    }

    if(Input::isPressed(Input::NUM2))
    {
        handleConsoleKey(
                '2');
    }

    if(Input::isPressed(Input::NUM3))
    {
        handleConsoleKey(
                '3');
    }

    while(keyboard_.hasData())
    {
        console_.putChar(
                keyboard_.pop());
    }
}

void FrameBufferMachine::handleConsoleKey(
        uint8_t ch)
{
    keyboard_.push(
            ch);
}

uint8_t FrameBufferMachine::readKeyboard()
{
    if(!keyboard_.hasData())
    {
        return 0;
    }

    return keyboard_.pop();
}

void FrameBufferMachine::writeConsole(
        uint8_t value)
{
    console_.putChar(
            static_cast<char>(
                    value));
}

void FrameBufferMachine::handleInput()
{
    switch(inputLayer_)
    {
        case InputLayer::MENU:

            if(Input::isPressed(
                    Input::ESC))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "ESC");

                ui_.clearSelection();

                inputLayer_ =
                        InputLayer::CONSOLE;

                return;
            }

            if(ui_.hasSelection())
            {
                if(ui_.processPopupShortcut())
                {
                    __android_log_print(
                            ANDROID_LOG_ERROR,
                            "INPUT",
                            "POPUP SHORTCUT");

                    return;
                }
            }
            else
            {
                if(ui_.processShortcut())
                {
                    __android_log_print(
                            ANDROID_LOG_ERROR,
                            "INPUT",
                            "MENU SHORTCUT");

                    return;
                }
            }

            if(Input::isPressed(Input::LEFT))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "LEFT");

                ui_.moveLeft();

                return;
            }

            if(Input::isPressed(Input::RIGHT))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "RIGHT");

                ui_.moveRight();

                return;
            }

            if(Input::isPressed(Input::UP))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "UP");

                ui_.moveUp();

                return;
            }

            if(Input::isPressed(Input::DOWN))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "DOWN");

                ui_.moveDown();

                return;
            }

            if(Input::isPressed(Input::ENTER))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "ENTER");

                ui_.execute();

                return;
            }

            onMenuFrame();

            break;

        case InputLayer::CONSOLE:

            if(Input::isPressed(
                    Input::ESC))
            {
                __android_log_print(
                        ANDROID_LOG_ERROR,
                        "INPUT",
                        "ESC CONSOLE");

                inputLayer_ =
                        InputLayer::MENU;

                return;
            }

            onConsoleFrame();

            break;
    }
}