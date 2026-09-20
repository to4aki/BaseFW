#include "Input.h"

bool Input::current_[COUNT] = {};
bool Input::previous_[COUNT] = {};

void Input::setKey(
        Key key,
        bool down)
{
    current_[key] =
            down;
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
    }
}

void Input::pressKey(
        Key key)
{
    current_[key] = true;
}