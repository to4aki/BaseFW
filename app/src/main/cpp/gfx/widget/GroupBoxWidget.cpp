#include "GroupBoxWidget.h"

GroupBoxWidget::GroupBoxWidget(
        int x,
        int y,
        int w,
        int h,
        const std::string& title)
        :
        Widget(
                x,
                y,
                w,
                h),
        title_(title)
{
}

void GroupBoxWidget::draw(
        FrameBuffer& fb)
{
    Draw::rect(
            fb,
            screenX(),
            screenY(),
            w_,
            h_,
            Color::WHITE);

    Draw::fillRect(
            fb,
            screenX() + 8,
            screenY() - 4,
            static_cast<int>(title_.length()) * 8,
            8,
            Color::BLACK);

    Draw::drawString(
            fb,
            screenX() + 8,
            screenY() - 4,
            title_.c_str(),
            Color::WHITE,
            Color::BLACK);
}