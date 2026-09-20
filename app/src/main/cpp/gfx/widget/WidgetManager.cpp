#include "WidgetManager.h"

void WidgetManager::add(
        std::unique_ptr<Widget> widget)
{
    widgets_.push_back(
            std::move(widget));
}

void WidgetManager::clear()
{
    widgets_.clear();
}

void WidgetManager::draw(
        FrameBuffer& fb)
{
    for(auto& widget : widgets_)
    {
        widget->draw(
                fb);
    }
}