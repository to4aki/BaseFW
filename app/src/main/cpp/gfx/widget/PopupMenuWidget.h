#pragma once

#include <vector>
#include <string>

#include "Widget.h"
#include "Color.h"
#include "Input.h"

class PopupMenuWidget
        : public Widget
{
public:

    PopupMenuWidget(
            int x,
            int y);

    void addItem(
            const std::string& text);

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

    int width() const
    {
        return w_;
    }

private:

    std::vector<std::string>
            items_;

    int selected_ = 0;

    int selected() const
    {
        return selected_;
    }
};