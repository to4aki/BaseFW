#pragma once

#include <memory>
#include <vector>

#include "gfx/widget/Widget.h"

#include "gfx/widget/GroupBoxWidget.h"
#include "gfx/widget/LabelWidget.h"
#include "gfx/widget/MenuBarWidget.h"
#include "gfx/widget/PanelWidget.h"
#include "gfx/widget/PopupMenuWidget.h"
#include "gfx/widget/StatusBarWidget.h"

class WidgetManager {
public:

    void add(
            std::unique_ptr<Widget> widget);

    void clear();

    void draw(
            FrameBuffer &fb);

    bool processShortcut();

    bool processPopupShortcut();

    void clearSelection();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void execute();

    int addMenu(
            const std::string &text,
            Input::Key shortcut);

    void addMenuItem(
            int menuId,
            const std::string &text,
            Input::Key shortcut,
            std::function<void()> callback);

    void createMenuSystem(
            int width);

    bool hasSelection() const;

private:

    std::vector<
            std::unique_ptr<Widget>>
            widgets_;

    MenuBarWidget *menu_ =
            nullptr;

    PopupMenuWidget *popup_ =
            nullptr;
};