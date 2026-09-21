#pragma once

#include <vector>
#include <string>
#include <functional>

#include "Widget.h"
#include "Color.h"
#include "Input.h"

class PopupMenuWidget
        : public Widget
{
public:

    struct Item
    {
        std::string text;

        Input::Key shortcut =
                Input::COUNT;

        std::function<void()> callback;
    };

    PopupMenuWidget(
            int x,
            int y);

    void addItem(
            const std::string& text,
            Input::Key shortcut,
            std::function<void()> callback);

    void setItems(
            const std::vector<Item>& items);

    void draw(
            FrameBuffer& fb) override;

    void setSelected(
            int index);

    void moveUp();

    void moveDown();

    void clear();

    void setPosition(
            int x,
            int y);

    bool processShortcut();

    int width() const
    {
        return w_;
    }

    int selected() const
    {
        return selected_;
    }

    void executeSelected();


private:

    std::vector<Item>
            items_;

    int selected_ = 0;
};