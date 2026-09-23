#include <android/log.h>

#include "TextConsole.h"

TextConsole::TextConsole() {
    clear();
}

void TextConsole::clear() {
    std::memset(
            vram_,
            ' ',
            sizeof(vram_));

    std::memset(
            wrapped_,
            0,
            sizeof(wrapped_));

    cursorX_ = 0;
    cursorY_ = 0;
}

void TextConsole::locate(
        int x,
        int y) {
    cursorX_ = x;
    cursorY_ = y;

    if (cursorX_ < 0) {
        cursorX_ = 0;
    }

    if (cursorX_ >= COLS) {
        cursorX_ = COLS - 1;
    }

    if (cursorY_ < 0) {
        cursorY_ = 0;
    }

    if (cursorY_ >= ROWS) {
        cursorY_ = ROWS - 1;
    }
}

void TextConsole::putChar(
        char ch) {
    if (ch == 0x1B) {
        escapeMode_ = true;
        escapeBuffer_.clear();
        return;
    }

    if (escapeMode_) {
        escapeBuffer_ += ch;

        if (ch == 'J') {
            if (escapeBuffer_ == "[2J") {
                clear();
            }

            escapeMode_ = false;
        } else if (ch == 'H') {
            if (escapeBuffer_ == "[H") {
                locate(
                        0,
                        0);
            }

            escapeMode_ = false;
        }

        return;
    }

    if (ch == '\b') {
        if (
                cursorX_ == 0 &&
                cursorY_ == 0) {
            return;
        }

        if (cursorX_ > 0) {
            cursorX_--;
        } else if (
                cursorY_ > 0 &&
                wrapped_[cursorY_ - 1]) {
            cursorY_--;
            cursorX_ = COLS - 1;
        } else {
            return;
        }

        vram_[cursorY_][cursorX_] =
                ' ';

        return;
    }

    if (ch == '\r') {
        cursorX_ = 0;
        return;
    }

    if (ch == '\n') {
        wrapped_[cursorY_] = false;

        cursorY_++;

        if (cursorY_ >= ROWS) {
            scroll();
        }

        return;
    }

    vram_[cursorY_][cursorX_] =
            ch;

    cursorX_++;

    if (cursorX_ >= COLS) {
        wrapped_[cursorY_] = true;

        cursorX_ = 0;
        cursorY_++;

        if (cursorY_ >= ROWS) {
            scroll();
        }
    }
}


void TextConsole::putString(
        const std::string &text) {
    for (char ch: text) {
        putChar(ch);
    }
}

void TextConsole::scroll() {
    for (int y = 1;
         y < ROWS;
         y++) {

        for (int x = 0;
             x < COLS;
             x++) {

            vram_[y - 1][x] =
                    vram_[y][x];
        }

        wrapped_[y - 1] =
                wrapped_[y];
    }

    for (int x = 0;
         x < COLS;
         x++) {

        vram_[ROWS - 1][x] =
                ' ';
    }

    wrapped_[ROWS - 1] =
            false;

    cursorY_ =
            ROWS - 1;
}

void TextConsole::draw(
        FrameBuffer &fb,
        int baseX,
        int baseY) {
    char str[2];

    str[0] = 0;
    str[1] = 0;

    for (int y = 0;
         y < ROWS;
         y++) {
        for (int x = 0;
             x < COLS;
             x++) {
            str[0] =
                    vram_[y][x];

            Draw::drawString(
                    fb,
                    baseX + x * 8,
                    baseY + y * 8,
                    str,
                    Color::WHITE,
                    Color::BLACK);
        }
    }
}