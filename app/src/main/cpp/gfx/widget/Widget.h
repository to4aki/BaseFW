#pragma once

#include "FrameBuffer.h"

class Widget
{
public:

    Widget(
            int x,
            int y,
            int w,
            int h);

    virtual ~Widget();

    virtual void draw(
            FrameBuffer& fb) = 0;

protected:

    int x_;
    int y_;

    int w_;
    int h_;
};