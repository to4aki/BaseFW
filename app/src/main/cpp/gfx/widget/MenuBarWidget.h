#pragma once

#include <string>
#include <vector>
#include <functional>

#include "Widget.h"
#include "Input.h"
#include "PopupMenuWidget.h"

class MenuBarWidget
        : public Widget
{
public:

    struct Item
    {
        std::string text;

        Input::Key shortcut =
                Input::COUNT;

        std::vector<
                PopupMenuWidget::Item>
                popupItems;
    };

    explicit MenuBarWidget(
            int width);

    int addItem(
            const std::string& text,
            Input::Key shortcut =
            Input::COUNT);

    void addPopItem(
            int menuId,
            const std::string& text,
            Input::Key shortcut,
            std::function<void()> callback);

    void setPopup(
            PopupMenuWidget* popup);

    void setSelected(
            int index);

    void draw(
            FrameBuffer& fb) override;

    void moveLeft();

    void moveRight();

    int selected() const;

    int selectedX() const;

    bool processShortcut();

    void updatePopup();

private:

    std::vector<Item>
            items_;

    int selected_ = -1;

    PopupMenuWidget* popup_ =
            nullptr;

};