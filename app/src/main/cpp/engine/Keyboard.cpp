#include "Keyboard.h"

std::queue<uint8_t>
        Keyboard::queue_;

KeyboardLayout
        Keyboard::layout_ =
        KeyboardLayout::JIS;

bool Keyboard::hasData() {
    return !queue_.empty();
}

uint8_t Keyboard::read() {
    if (queue_.empty()) {
        return 0;
    }

    uint8_t value =
            queue_.front();

    queue_.pop();

    return value;
}

void Keyboard::putAndroidKey(
        int keyCode,
        int metaState) {
    uint8_t value =
            convertKeyCode(
                    keyCode,
                    metaState);

    if (value != 0) {
        queue_.push(
                value);
    }
}


void Keyboard::setLayout(
        KeyboardLayout layout) {
    layout_ = layout;
}

uint8_t Keyboard::convertKeyCode(
        int keyCode,
        int metaState) {

    switch (layout_) {
        case KeyboardLayout::US:
            return convertUsKeyCode(
                    keyCode,
                    metaState);

        case KeyboardLayout::JIS:
            return convertJisKeyCode(
                    keyCode,
                    metaState);
    }

    return 0;
}


uint8_t Keyboard::convertUsKeyCode(
        int keyCode,
        int metaState) {
    bool shift =
            (metaState & 0x00000001)
            ||
            (metaState & 0x00000040);

    if (keyCode >= 29 &&
        keyCode <= 54) {
        uint8_t ch =
                static_cast<uint8_t>(
                        'a'
                        +
                        (keyCode - 29));

        if (shift) {
            ch =
                    static_cast<uint8_t>(
                            ch - 'a' + 'A');
        }

        return ch;
    }

    switch (keyCode) {
        case 7:
            return shift ? ')' : '0';

        case 8:
            return shift ? '!' : '1';

        case 9:
            return shift ? '@' : '2';

        case 10:
            return shift ? '#' : '3';

        case 11:
            return shift ? '$' : '4';

        case 12:
            return shift ? '%' : '5';

        case 13:
            return shift ? '^' : '6';

        case 14:
            return shift ? '&' : '7';

        case 15:
            return shift ? 42 : '8';

        case 16:
            return shift ? '(' : '9';

        case 62:
            return ' ';

        case 69:
            return shift ? '_' : '-';

        case 70:
            return shift ? '+' : '=';

        case 71:
            return shift ? '{' : '[';

        case 72:
            return shift ? '}' : ']';

        case 73:
            return shift ? '|' : '\\';

        case 74:
            return shift ? ':' : ';';

        case 75:
            return shift ? '"' : '\'';

        case 55:
            return shift ? '<' : ',';

        case 56:
            return shift ? '>' : '.';

        case 76:
            return shift ? '?' : '/';

        case 61:
            return '\t';

        case 66:
            return '\r';

        case 67:
            return '\b';

        default:
            return 0;
    }
}

uint8_t Keyboard::convertJisKeyCode(
        int keyCode,
        int metaState) {
    bool shift =
            (metaState & 0x00000001)
            ||
            (metaState & 0x00000040);

    if (keyCode >= 29 &&
        keyCode <= 54) {
        uint8_t ch =
                static_cast<uint8_t>(
                        'a'
                        + (keyCode - 29));

        if (shift) {
            ch =
                    static_cast<uint8_t>(
                            ch - 'a' + 'A');
        }

        return ch;
    }

    switch (keyCode) {
        case 7:
            return '0';

        case 8:
            return shift ? '!' : '1';

        case 9:
            return shift ? '"' : '2';

        case 10:
            return shift ? '#' : '3';

        case 11:
            return shift ? '$' : '4';

        case 12:
            return shift ? '%' : '5';

        case 13:
            return shift ? '&' : '6';

        case 14:
            return shift ? '\'' : '7';

        case 15:
            return shift ? '(' : '8';

        case 16:
            return shift ? ')' : '9';

        case 69:
            return shift ? '=' : '-';

        case 70:
            return shift ? '~' : '^';

        case 71:
            return shift ? '{' : '[';

        case 72:
            return shift ? '}' : ']';

        case 74:
            return shift ? '+' : ';';

        case 75:
            return shift ? '*' : ':';

        case 77:
            return shift ? '`' : '@';

        case 55:
            return shift ? '<' : ',';

        case 56:
            return shift ? '>' : '.';

        case 76:
            return shift ? '?' : '/';

        case 62:
            return ' ';

        case 61:
            return '\t';

        case 66:
            return '\r';

        case 67:
            return '\b';

        case 216:
            return shift ? '|' : '\\';

        case 217:
            return shift ? '_' : '\\';

        default:
            return 0;
    }
}

void Keyboard::clear() {

    while (!queue_.empty()) {
        queue_.pop();
    }
}