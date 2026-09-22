#pragma once

#include <string>

#include "gfx/widget/Widget.h"

class GroupBoxWidget
        : public Widget {
public:

    GroupBoxWidget(
            int x,
            int y,
            int w,
            int h,
            const std::string &title);

    void draw(
            FrameBuffer &fb) override;

private:

    std::string title_;
};