#pragma once

#include <memory>
#include <vector>

#include "Widget.h"
#include "FrameBuffer.h"
#include "StatusBarWidget.h"
#include "PanelWidget.h"
#include "LabelWidget.h"
#include "GroupBoxWidget.h"
#include "PopupMenuWidget.h"
#include "MenuBarWidget.h"

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
            const std::string& text,
            Input::Key shortcut);

    void addMenuItem(
            int menuId,
            const std::string& text,
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