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

int MenuBarWidget::addItem(
        const std::string& text,
        Input::Key shortcut)
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

    items_.push_back(
            item);

    return static_cast<int>(
            items_.size() - 1);
}

void MenuBarWidget::addPopItem(
        int menuId,
        const std::string& text,
        Input::Key shortcut,
        std::function<void()> callback)
{
    if(menuId < 0)
    {
        return;
    }

    if(menuId >= static_cast<int>(
            items_.size()))
    {
        return;
    }

    PopupMenuWidget::Item item;

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

    items_[menuId]
            .popupItems
            .push_back(
                    item);
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
        const Item& item =
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
                            item.text.length()) * 8 + 4,
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
                item.text.c_str(),
                fg,
                bg);

        x +=
                static_cast<int>(
                        item.text.length())
                * 8
                + 8;
    }
}

void MenuBarWidget::moveLeft()
{
    if(selected_ > 0)
    {
        selected_--;

        updatePopup();
    }
}

void MenuBarWidget::moveRight()
{
    if(selected_ + 1
       < static_cast<int>(
               items_.size()))
    {
        selected_++;

        updatePopup();
    }
}

void MenuBarWidget::setSelected(
        int index)
{
    selected_ =
            index;

    updatePopup();
}

int MenuBarWidget::selectedX() const
{
    if(selected_ < 0)
    {
        return screenX();
    }

    int x =
            screenX() + 4;

    for(int i = 0;
        i < selected_;
        i++)
    {
        x +=
                static_cast<int>(
                        items_[i].text.length())
                * 8
                + 8;
    }

    return x;
}

bool MenuBarWidget::processShortcut()
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

            updatePopup();

            return true;
        }
    }

    return false;
}

void MenuBarWidget::setPopup(
        PopupMenuWidget* popup)
{
    popup_ = popup;
}

void MenuBarWidget::updatePopup()
{
    if(!popup_)
    {
        return;
    }

    if(selected_ < 0)
    {
        popup_->clear();

        return;
    }

    popup_->setItems(
            items_[selected_]
                    .popupItems);

    int x =
            selectedX();

    if(x + popup_->width() >= w_)
    {
        x =
                w_
                - popup_->width()
                - 1;
    }

    popup_->setPosition(
            x,
            16);
}

int MenuBarWidget::selected() const
{
    return selected_;
}
