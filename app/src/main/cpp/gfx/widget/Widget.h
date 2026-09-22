#pragma once

#include "gfx/Color.h"
#include "gfx/Draw.h"
#include "gfx/FrameBuffer.h"

class Widget {
public:

    Widget(
            int x,
            int y,
            int w,
            int h);

    virtual ~Widget();

    virtual void draw(
            FrameBuffer &fb) = 0;

    void setParent(
            Widget *parent) {
        parent_ = parent;
    }

protected:

    int x_;
    int y_;

    int w_;
    int h_;

    Widget *parent_ = nullptr;

    int screenX() const {
        if (parent_ == nullptr) {
            return x_;
        }

        return parent_->screenX() + x_;
    }

    int screenY() const {
        if (parent_ == nullptr) {
            return y_;
        }

        return parent_->screenY() + y_;
    }
};