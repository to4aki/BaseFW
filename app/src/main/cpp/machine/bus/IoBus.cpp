#include <android/log.h>
#include "IoBus.h"

IoBus::IoBus(
        KeyboardBuffer *keyboard,
        TextConsole *console)
        :
        keyboard_(keyboard),
        console_(console) {
}

uint8_t IoBus::in(
        uint16_t port) {

    uint8_t p = port & 0xFF;

    switch (p) {

        case 0x80: {

            bool has = keyboard_->hasData();

            uint8_t status = 0x02;

            if (has) {
                status |= 0x01;
            }

            return status;
        }

        case 0x81: {

            if (!keyboard_->hasData()) {

                return 0;
            }

            uint8_t value = keyboard_->pop();

            return value;
        }

        default:

            return 0;
    }
}

void IoBus::out(
        uint16_t port,
        uint8_t value) {

    uint8_t p = port & 0xFF;

    switch (p) {

        case 0x81:

            console_->putChar(
                    static_cast<char>(
                            value));

            break;

        default:

            break;
    }
}