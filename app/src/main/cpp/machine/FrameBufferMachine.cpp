#include "FrameBufferMachine.h"

FrameBufferMachine::FrameBufferMachine(
        int width,
        int height)
        :
        fb_(
                width,
                height),
        width_(width),
        height_(height) {
}

void FrameBufferMachine::reset() {

    if (!initialized_) {

        onInitUi();

        initialized_ =
                true;
    }

    fb_.clear(
            Color::BLACK);

    if (console_) {

        console_->clear();
    }

    ui_.clearSelection();

    inputLayer_ =
            InputLayer::CONSOLE;

    onReset();
}

void FrameBufferMachine::runFrame() {

    fb_.clear(
            Color::BLACK);

    handleInput();

    onFrame();

    if (console_) {

        console_->draw(
                fb_,
                0,
                16);
    }

    ui_.draw(
            fb_);
}

void FrameBufferMachine::onFrame() {
}

void FrameBufferMachine::onReset() {
}

uint32_t *FrameBufferMachine::frameBuffer() {
    return fb_.data();
}

int FrameBufferMachine::width() const {
    return width_;
}

int FrameBufferMachine::height() const {
    return height_;
}

void FrameBufferMachine::onInitUi() {
}

void FrameBufferMachine::onMenuFrame() {
}

void FrameBufferMachine::onConsoleFrame() {

    while (Keyboard::hasData()) {

        handleConsoleKey(
                Keyboard::read());
    }
}

void FrameBufferMachine::handleConsoleKey(
        uint8_t ch) {

    keyboard_.push(
            ch);
}

uint8_t FrameBufferMachine::readKeyboard() {

    if (!keyboard_.hasData()) {
        return 0;
    }

    return keyboard_.pop();
}

void FrameBufferMachine::writeConsole(
        uint8_t value) {

    if (console_) {

        console_->putChar(
                static_cast<char>(
                        value));
    }
}

void FrameBufferMachine::handleInput() {

    switch (inputLayer_) {

        case InputLayer::MENU:

            if (Input::isPressed(
                    Input::ESC)) {

                ui_.clearSelection();

                Keyboard::clear();

                inputLayer_ =
                        InputLayer::CONSOLE;

                return;
            }

            if (ui_.hasSelection()) {

                if (ui_.processPopupShortcut()) {
                    return;
                }
            } else {

                if (ui_.processShortcut()) {
                    return;
                }
            }

            if (Input::isPressed(
                    Input::LEFT)) {

                ui_.moveLeft();

                return;
            }

            if (Input::isPressed(
                    Input::RIGHT)) {

                ui_.moveRight();

                return;
            }

            if (Input::isPressed(
                    Input::UP)) {

                ui_.moveUp();

                return;
            }

            if (Input::isPressed(
                    Input::DOWN)) {

                ui_.moveDown();

                return;
            }

            if (Input::isPressed(
                    Input::ENTER)) {

                ui_.execute();

                return;
            }

            onMenuFrame();

            break;

        case InputLayer::CONSOLE:

            if (Input::isPressed(
                    Input::ESC)) {

                Keyboard::clear();

                inputLayer_ =
                        InputLayer::MENU;

                return;
            }

            onConsoleFrame();

            break;
    }
}

void FrameBufferMachine::setAssetManager(
        AAssetManager *assetManager) {

    assetManager_ =
            assetManager;
}

AAssetManager *FrameBufferMachine::assetManager() const {

    return assetManager_;
}

void FrameBufferMachine::setConsole(
        IConsole *console) {

    console_ = console;
}