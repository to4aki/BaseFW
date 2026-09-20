#include "LabelWidget.h"

LabelWidget::LabelWidget(
        int x,
        int y,
        const std::string& text)
        :
        Widget(
                x,
                y,
                0,
                0),
        text_(text)
{
}

void LabelWidget::setText(
        const std::string& text)
{
    text_ = text;
}

void LabelWidget::draw(
        FrameBuffer& fb)
{
    Draw::drawString(
            fb,
            screenX(),
            screenY(),
            text_.c_str(),
            Color::WHITE,
            Color::BLACK);
}