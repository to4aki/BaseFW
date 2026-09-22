#pragma once

#include "gfx/widget/Widget.h"

class PanelWidget
        : public Widget {
public:

    PanelWidget(
            int x,
            int y,
            int w,
            int h);

    void draw(
            FrameBuffer &fb) override;
};