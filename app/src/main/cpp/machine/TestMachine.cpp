#include "TestMachine.h"

TestMachine::TestMachine()
        :
        FrameBufferMachine(
                WIDTH,
                HEIGHT) {
    reset();
}

void TestMachine::onReset() {
    aout << "TestMachine::onReset" << std::endl;
    ui_.add(
            std::make_unique<StatusBarWidget>(
                    width(),
                    "FRAMEWORK TEST"));

    ui_.add(
            std::make_unique<PanelWidget>(
                    0,
                    16,
                    160,
                    80));

    ui_.add(
            std::make_unique<LabelWidget>(
                    4,
                    20,
                    "LABEL1"));

    ui_.add(
            std::make_unique<LabelWidget>(
                    4,
                    28,
                    "LABEL2"));
}

void TestMachine::onFrame() {
}