#include "MenuBarWidget.h"

#include "Draw.h"
#include "Color.h"

MenuBarWidget::MenuBarWidget(
        int width)
        :
        Widget(
                0,
                0,
                width,
                16)
{
}

void MenuBarWidget::addItem(
        const std::string& text)
{
    items_.push_back(
            text);
}

void MenuBarWidget::setSelected(
        int index)
{
    selected_ = index;
}

void MenuBarWidget::draw(
        FrameBuffer& fb)
{
    Draw::fillRect(
            fb,
            screenX(),
            screenY(),
            w_,
            h_,
            Color::BLUE);

    int x =
            screenX() + 4;

    for(size_t i = 0;
        i < items_.size();
        i++)
    {
        const std::string& text =
                items_[i];

        uint32_t fg =
                Color::WHITE;

        uint32_t bg =
                Color::BLUE;

        if(static_cast<int>(i)
           == selected_)
        {
            Draw::fillRect(
                    fb,
                    x - 2,
                    screenY() + 2,
                    static_cast<int>(
                            text.length()) * 8 + 4,
                    12,
                    Color::WHITE);

            fg =
                    Color::BLUE;

            bg =
                    Color::WHITE;
        }

        Draw::drawString(
                fb,
                x,
                screenY() + 4,
                text.c_str(),
                fg,
                bg);

        x +=
                static_cast<int>(
                        text.length())
                * 8
                + 8;
    }
}

void MenuBarWidget::moveLeft()
{
    if(selected_ > 0)
    {
        selected_--;
    }
}

void MenuBarWidget::moveRight()
{
    if(selected_ + 1
       < static_cast<int>(
               items_.size()))
    {
        selected_++;
    }
}

int MenuBarWidget::selected() const
{
    return selected_;
}

int MenuBarWidget::selectedX() const
{
    int x =
            screenX() + 4;

    for(int i = 0;
        i < selected_;
        i++)
    {
        x +=
                static_cast<int>(
                        items_[i].length())
                * 8
                + 8;
    }

    return x;
}
