#pragma once

#include <string>

#include "gfx/widget/Widget.h"

class LabelWidget
        : public Widget {
public:

    LabelWidget(
            int x,
            int y,
            const std::string &text);

    void setText(
            const std::string &text);

    void draw(
            FrameBuffer &fb) override;

private:

    std::string text_;
};