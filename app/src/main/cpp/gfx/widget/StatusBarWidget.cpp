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
            x_,
            y_,
            w_,
            h_,
            Color::BLUE);

    Draw::drawString(
            fb,
            x_ + 4,
            y_ + 4,
            text_.c_str(),
            Color::WHITE,
            Color::BLUE);
}
