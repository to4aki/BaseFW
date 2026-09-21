#include "PopupMenuWidget.h"

#include "Draw.h"
#include "Color.h"

PopupMenuWidget::PopupMenuWidget(
        int x,
        int y)
        :
        Widget(
                x,
                y,
                0,
                0)
{
}

void PopupMenuWidget::addItem(
        const std::string& text,
        Input::Key shortcut,
        std::function<void()> callback)
{
    Item item;

    if(shortcut >= Input::NUM1 &&
       shortcut <= Input::NUM6)
    {
        item.text =
                std::to_string(
                        shortcut
                        - Input::NUM1
                        + 1)
                +
                ":"
                +
                text;
    }
    else
    {
        item.text =
                text;
    }

    item.shortcut =
            shortcut;

    item.callback =
            callback;

    items_.push_back(
            item);

    int itemWidth =
            static_cast<int>(
                    item.text.length())
            * 8
            + 16;

    if(itemWidth > w_)
    {
        w_ = itemWidth;
    }

    h_ =
            static_cast<int>(
                    items_.size())
            * 12
            + 4;
}

void PopupMenuWidget::setItems(
        const std::vector<Item>& items)
{
    clear();

    for(const auto& item : items)
    {
        items_.push_back(
                item);

        int itemWidth =
                static_cast<int>(
                        item.text.length())
                * 8
                + 16;

        if(itemWidth > w_)
        {
            w_ = itemWidth;
        }
    }

    h_ =
            static_cast<int>(
                    items_.size())
            * 12
            + 4;
}

void PopupMenuWidget::draw(
        FrameBuffer& fb)
{
    if(items_.empty())
    {
        return;
    }

    Draw::fillRect(
            fb,
            screenX(),
            screenY(),
            w_,
            h_,
            Color::BLUE);

    Draw::rect(
            fb,
            screenX(),
            screenY(),
            w_,
            h_,
            Color::WHITE);

    for(size_t i = 0;
        i < items_.size();
        i++)
    {
        uint32_t fg =
                Color::WHITE;

        uint32_t bg =
                Color::BLUE;

        if(static_cast<int>(i)
           == selected_)
        {
            Draw::fillRect(
                    fb,
                    screenX() + 3,
                    screenY() + 2
                    + static_cast<int>(i) * 12,
                    w_ - 6,
                    12,
                    Color::WHITE);

            fg =
                    Color::BLUE;

            bg =
                    Color::WHITE;
        }

        Draw::drawString(
                fb,
                screenX() + 4,
                screenY() + 4
                + static_cast<int>(i) * 12,
                items_[i].text.c_str(),
                fg,
                bg);
    }
}

void PopupMenuWidget::setSelected(
        int index)
{
    selected_ = index;
}

void PopupMenuWidget::moveUp()
{
    if(selected_ > 0)
    {
        selected_--;
    }
}

void PopupMenuWidget::moveDown()
{
    if(selected_ + 1
       < static_cast<int>(
               items_.size()))
    {
        selected_++;
    }
}

void PopupMenuWidget::clear()
{
    items_.clear();

    selected_ = 0;

    w_ = 0;

    h_ = 0;
}

void PopupMenuWidget::setPosition(
        int x,
        int y)
{
    x_ = x;
    y_ = y;
}

bool PopupMenuWidget::processShortcut()
{
    for(size_t i = 0;
        i < items_.size();
        i++)
    {
        if(items_[i].shortcut
           ==
           Input::COUNT)
        {
            continue;
        }

        if(Input::isPressed(
                items_[i].shortcut))
        {
            selected_ =
                    static_cast<int>(i);

            return true;
        }
    }

    return false;
}

void PopupMenuWidget::executeSelected()
{
    if(selected_ < 0)
    {
        return;
    }

    if(selected_
       >= static_cast<int>(
               items_.size()))
    {
        return;
    }

    if(items_[selected_].callback)
    {
        items_[selected_].callback();
    }
}