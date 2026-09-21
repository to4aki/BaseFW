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

    menu_ =
            nullptr;

    popup_ =
            nullptr;
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

bool WidgetManager::processShortcut()
{
    if(menu_)
    {
        return menu_->processShortcut();
    }

    return false;
}

bool WidgetManager::processPopupShortcut()
{
    if(popup_)
    {
        return popup_->processShortcut();
    }

    return false;
}

void WidgetManager::clearSelection()
{
    if(menu_)
    {
        menu_->setSelected(
                -1);
    }
}

void WidgetManager::moveLeft()
{
    if(menu_)
    {
        menu_->moveLeft();
    }
}

void WidgetManager::moveRight()
{
    if(menu_)
    {
        menu_->moveRight();
    }
}

void WidgetManager::moveUp()
{
    if(popup_)
    {
        popup_->moveUp();
    }
}

void WidgetManager::moveDown()
{
    if(popup_)
    {
        popup_->moveDown();
    }
}

void WidgetManager::execute()
{
    if(popup_)
    {
        popup_->executeSelected();
    }
}

int WidgetManager::addMenu(
        const std::string& text,
        Input::Key shortcut)
{
    if(!menu_)
    {
        return -1;
    }

    return menu_->addItem(
            text,
            shortcut);
}

void WidgetManager::addMenuItem(
        int menuId,
        const std::string& text,
        Input::Key shortcut,
        std::function<void()> callback)
{
    if(!menu_)
    {
        return;
    }

    menu_->addPopItem(
            menuId,
            text,
            shortcut,
            callback);
}

void WidgetManager::createMenuSystem(
        int width)
{
    auto menu =
            std::make_unique<MenuBarWidget>(
                    width);

    menu_ =
            menu.get();

    add(
            std::move(menu));

    auto popup =
            std::make_unique<PopupMenuWidget>(
                    0,
                    16);

    popup_ =
            popup.get();

    add(
            std::move(popup));

    menu_->setPopup(
            popup_);
}

bool WidgetManager::hasSelection() const
{
    return
            menu_
            &&
            menu_->selected() >= 0;
}
