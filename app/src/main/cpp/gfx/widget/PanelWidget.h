#pragma once

#include "Widget.h"
#include "Draw.h"
#include "Color.h"

class PanelWidget
        : public Widget
{
public:

    PanelWidget(
            int x,
            int y,
            int w,
            int h);

    void draw(
            FrameBuffer& fb) override;
};