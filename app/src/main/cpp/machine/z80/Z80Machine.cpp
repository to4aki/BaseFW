#include "machine/z80/Z80Machine.h"

Z80Machine::Z80Machine()
        :
        FrameBufferMachine(
                320,
                216),
        console_(),
        ram_(32768),
        ioBus_(
                &keyboard_,
                &console_),
        cpu_(
                &memoryBus_,
                &ioBus_) {

    setConsole(
            &console_);

    memoryBus_.setRom(
            &rom_);

    memoryBus_.setRam(
            &ram_);
}

bool Z80Machine::loadRom(
        const char *fileName) {

    if (assetManager() == nullptr) {
        return false;
    }

    AAsset *asset =
            AAssetManager_open(
                    assetManager(),
                    fileName,
                    AASSET_MODE_BUFFER);

    if (asset == nullptr) {
        return false;
    }

    const char *data =
            static_cast<const char *>(
                    AAsset_getBuffer(
                            asset));

    size_t size =
            AAsset_getLength(
                    asset);

    bool result =
            HexLoader::loadFromMemory(
                    rom_,
                    data,
                    size);

    AAsset_close(
            asset);

    if (result) {
        running_ = true;
    }

    return result;
}

void Z80Machine::onReset() {
    if (!romLoaded_) {
        romLoaded_ =
                loadRom(
                        "roms/rc2014_32k.hex");
//                        "roms/hexFiles/ROM.HEX");
    }

    if (romLoaded_) {
        cpu_.reset();
    }
}

void Z80Machine::onFrame() {
    if (!running_) {
        return;
    }

    if (irqPending_) {
        irqPending_ = false;

        cpu_.interrupt();
    }

    cpu_.runCycles(
            50000);
}

void Z80Machine::raiseInterrupt() {
    irqPending_ = true;
}

void Z80Machine::handleConsoleKey(
        uint8_t ch) {
    keyboard_.push(
            ch);

    raiseInterrupt();
}

void Z80Machine::onInitUi() {
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
            [this]() {
                console_.putString(
                        "STEP\n");

                console_.putString(
                        ">");
            });

    ui_.addMenuItem(
            run,
            "RESET",
            Input::NUM2,
            [this]() {
                reset();

                console_.putString(
                        "RESET OK\n");
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
            [this]() {
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
