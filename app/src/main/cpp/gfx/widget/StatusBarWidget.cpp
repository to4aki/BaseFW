#include "StatusBarWidget.h"

StatusBarWidget::StatusBarWidget(
        int width,
        const std::string& text)
        :
        Widget(
                0,
                0,
                width,
                16),
        text_(text)
{
}

void StatusBarWidget::draw(
        FrameBuffer& fb)
{
    Draw::fillRect(
            fb,
            screenX(),
            screenY(),
            w_,
            h_,
            Color::BLUE);

    Draw::drawString(
            fb,
            screenX() + 4,
            screenY() + 4,
            text_.c_str(),
            Color::WHITE,
            Color::BLUE);
}