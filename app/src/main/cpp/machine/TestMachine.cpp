#include "TestMachine.h"

TestMachine::TestMachine()
        :
        FrameBufferMachine(
                WIDTH,
                HEIGHT) {
    reset();
}

void TestMachine::onInitUi() {
    ui_.createMenuSystem(
            width());

    int run =
            ui_.addMenu(
                    "RUN",
                    Input::NUM1);

    ui_.addMenuItem(
            run,
            "STEP",
            Input::NUM1,
            [this]()
            {
                console_.putString(
                        "STEP\n");

                console_.putString(
                        ">");
            });

    ui_.addMenuItem(
            run,
            "RESET",
            Input::NUM2,
            [this]()
            {
                reset();

                console_.putString(
                        "RESET OK\n");

                console_.putString(
                        ">");
            });

    ui_.addMenuItem(
            run,
            "LOAD",
            Input::NUM3,
            [this]() {
            });

    ui_.addMenuItem(
            run,
            "SAVE",
            Input::NUM4,
            [this]() {
            });

    int reg =
            ui_.addMenu(
                    "REG",
                    Input::NUM2);

    ui_.addMenuItem(
            reg,
            "AF",
            Input::NUM1,
            [this]()
            {
                console_.putString(
                        "AF:1234\n");

                console_.putString(
                        ">");
            });

    ui_.addMenuItem(
            reg,
            "BC",
            Input::NUM2,
            [this]() {
            });

    ui_.addMenuItem(
            reg,
            "DE",
            Input::NUM3,
            [this]() {
            });

    ui_.addMenuItem(
            reg,
            "HL",
            Input::NUM4,
            [this]() {
            });

    int dasm =
            ui_.addMenu(
                    "DASM",
                    Input::NUM3);

    ui_.addMenuItem(
            dasm,
            "PAGEUP",
            Input::NUM1,
            [this]() {
            });

    ui_.addMenuItem(
            dasm,
            "PAGEDOWN",
            Input::NUM2,
            [this]() {
            });

    int memory =
            ui_.addMenu(
                    "MEMORY",
                    Input::NUM4);

    ui_.addMenuItem(
            memory,
            "DUMP",
            Input::NUM1,
            [this]() {
            });

    ui_.addMenuItem(
            memory,
            "GOTO",
            Input::NUM2,
            [this]() {
            });

    int tools =
            ui_.addMenu(
                    "TOOLS",
                    Input::NUM5);

    ui_.addMenuItem(
            tools,
            "OPTIONS",
            Input::NUM1,
            [this]() {
            });

    ui_.addMenuItem(
            tools,
            "KEYMAP",
            Input::NUM2,
            [this]() {
            });

    int help =
            ui_.addMenu(
                    "HELP",
                    Input::NUM6);

    ui_.addMenuItem(
            help,
            "ABOUT",
            Input::NUM1,
            [this]() {
            });

    ui_.addMenuItem(
            help,
            "LICENSE",
            Input::NUM2,
            [this]() {
            });

    ui_.addMenuItem(
            help,
            "SETTINGS",
            Input::NUM3,
            [this]() {
            });

    ui_.addMenuItem(
            help,
            "VERSION",
            Input::NUM4,
            [this]() {
            });
}

void TestMachine::onReset()
{
    ui_.clearSelection();

    console_.clear();

    console_.putString(
            "Z80 EMULATOR\n");

    console_.putString(
            "VERSION 0.1\n");

    console_.putString(
            "\n");

    console_.putString(
            "012345678901234567890123456789012345678901234567890\n");

    console_.putString(
            "READY.\n");

    console_.putString(
            ">");

}

void TestMachine::onFrame()
{
}

void TestMachine::onMenuFrame()
{
}
