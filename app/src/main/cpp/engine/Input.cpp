#include "Input.h"

bool Input::current_[COUNT] = {};
bool Input::previous_[COUNT] = {};

const Input::KeyMap
        Input::keyMap[] =
        {
                { 19,  Input::UP },
                { 20,  Input::DOWN },
                { 21,  Input::LEFT },
                { 22,  Input::RIGHT },

                { 66,  Input::ENTER },
                { 111, Input::ESC },

                { 61,  Input::TAB },
                { 62,  Input::SPACE },

                { 67,  Input::BACKSPACE },
                { 112, Input::DELETE_KEY },

                { 122, Input::HOME },
                { 123, Input::END },

                { 92,  Input::PAGE_UP },
                { 93,  Input::PAGE_DOWN },

                { 124, Input::INSERT },

                { 131, Input::F1 },
                { 132, Input::F2 },
                { 133, Input::F3 },
                { 134, Input::F4 },

                { 135, Input::F5 },
                { 136, Input::F6 },
                { 137, Input::F7 },
                { 138, Input::F8 },

                { 139, Input::F9 },
                { 140, Input::F10 },
                { 141, Input::F11 },
                { 142, Input::F12 },

                { 8,  Input::NUM1 },
                { 9,  Input::NUM2 },
                { 10, Input::NUM3 },
                { 11, Input::NUM4 },
                { 12, Input::NUM5 },
                { 13, Input::NUM6 }
        };

const int
        Input::keyMapCount =
        sizeof(Input::keyMap)
        /
        sizeof(Input::keyMap[0]);

void Input::setKey(
        Key key,
        bool down)
{
    if(down)
    {
        current_[key] =
                true;
    }
}

bool Input::isDown(
        Key key)
{
    return current_[key];
}

bool Input::isPressed(
        Key key)
{
    return current_[key]
           &&
           !previous_[key];
}

void Input::endFrame()
{
    for(int i = 0;
        i < COUNT;
        i++)
    {
        previous_[i] =
                current_[i];

        current_[i] =
                false;
    }
}