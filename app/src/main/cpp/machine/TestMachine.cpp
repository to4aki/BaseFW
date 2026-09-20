#include "TestMachine.h"

TestMachine::TestMachine()
        :
        FrameBufferMachine(
                WIDTH,
                HEIGHT) {
    reset();
}

void TestMachine::onReset() {
    auto menu =
            std::make_unique<MenuBarWidget>(
                    width());

    menu->addItem(
            "RUN");

    menu->addItem(
            "REG");

    menu->addItem(
            "DASM");

    menu->addItem(
            "MEMORY");

    menu->addItem(
            "TOOLS");

    menu->addItem(
            "HELP");

    menu->setSelected(
            0);

    menu_ =
            menu.get();

    ui_.add(
            std::move(menu));


    auto popup =
            std::make_unique<PopupMenuWidget>(
                    0,
                    16);

    popup->addItem(
            "STEP");

    popup->addItem(
            "RESET");

    popup->addItem(
            "LOAD");

    popup->addItem(
            "SAVE");

    popup_ =
            popup.get();

    ui_.add(
            std::move(popup));

    rebuildPopup();
}

void TestMachine::onFrame()
{
    if(Input::isPressed(
            Input::LEFT))
    {
        menu_->moveLeft();

        rebuildPopup();
    }

    if(Input::isPressed(
            Input::RIGHT))
    {
        menu_->moveRight();

        rebuildPopup();
    }

    if(Input::isPressed(
            Input::UP))
    {
        popup_->moveUp();
    }

    if(Input::isPressed(
            Input::DOWN))
    {
        popup_->moveDown();
    }
}

void TestMachine::rebuildPopup()
{
    popup_->clear();

    switch(menu_->selected())
    {
        case 0:
        {
            popup_->addItem(
                    "STEP");

            popup_->addItem(
                    "RESET");

            break;
        }

        case 1:
        {
            popup_->addItem(
                    "AF");

            popup_->addItem(
                    "BC");

            popup_->addItem(
                    "DE");

            popup_->addItem(
                    "HL");

            break;
        }

        case 2:
        {
            popup_->addItem(
                    "PAGEUP");

            popup_->addItem(
                    "PAGEDOWN");

            break;
        }

        case 5:
        {
            popup_->addItem(
                    "ABOUT");

            popup_->addItem(
                    "LICENSE");

            popup_->addItem(
                    "SETTINGS");

            popup_->addItem(
                    "VERSION");

            break;
        }
    }

    int x =
            menu_->selectedX();

    if(x + popup_->width()
       > width())
    {
        x =
                width()
                - popup_->width();
    }

    popup_->setPosition(
            x,
            16);
}