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

class WidgetManager
{
public:

    void add(
            std::unique_ptr<Widget> widget);

    void clear();

    void draw(
            FrameBuffer& fb);

private:

    std::vector<std::unique_ptr<Widget>>
            widgets_;
};