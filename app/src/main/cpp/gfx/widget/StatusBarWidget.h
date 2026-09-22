#pragma once

#include <string>

#include "gfx/widget/Widget.h"

class StatusBarWidget
        : public Widget {
public:

    StatusBarWidget(
            int width,
            const std::string &text);

    void draw(
            FrameBuffer &fb) override;

private:

    std::string text_;
};