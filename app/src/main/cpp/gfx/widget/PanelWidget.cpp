#include "PanelWidget.h"

PanelWidget::PanelWidget(
        int x,
        int y,
        int w,
        int h)
        :
        Widget(
                x,
                y,
                w,
                h)
{
}

void PanelWidget::draw(
        FrameBuffer& fb)
{
    Draw::fillRect(
            fb,
            x_,
            y_,
            w_,
            h_,
            Color::GRAY);

    Draw::rect(
            fb,
            x_,
            y_,
            w_,
            h_,
            Color::WHITE);
}