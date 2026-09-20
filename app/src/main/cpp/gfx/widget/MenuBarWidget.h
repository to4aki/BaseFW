#pragma once

#include <string>
#include <vector>

#include "Widget.h"

class MenuBarWidget
        : public Widget
{
public:

    explicit MenuBarWidget(
            int width);

    void addItem(
            const std::string& text);

    void setSelected(
            int index);

    void draw(
            FrameBuffer& fb) override;

    void moveLeft();

    void moveRight();

    int selected() const;

    int selectedX() const;

private:

    std::vector<std::string>
            items_;

    int selected_ = 0;
};