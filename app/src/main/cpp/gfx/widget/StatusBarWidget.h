#pragma once

#include <string>

#include "Widget.h"
#include "Draw.h"
#include "Color.h"

class StatusBarWidget
        : public Widget
{
public:

    StatusBarWidget(
            int width,
            const std::string& text);

    void draw(
            FrameBuffer& fb) override;

private:

    std::string text_;
};