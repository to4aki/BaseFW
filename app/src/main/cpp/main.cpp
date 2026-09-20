#include <memory>

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "AndroidOut.h"

#include "engine/Engine.h"
#include "engine/Renderer.h"

#include "machine/TestMachine.h"

extern "C"
{

void handle_cmd(android_app* app, int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_INIT_WINDOW:
            aout << "Window created" << std::endl;
            break;

        case APP_CMD_TERM_WINDOW:
            aout << "Window destroyed" << std::endl;
            break;

        default:
            break;
    }
}

void android_main(android_app* app)
{
    aout << "android_main" << std::endl;

    app->onAppCmd = handle_cmd;

    //
    // Window生成待ち
    //
    while (app->window == nullptr &&
           !app->destroyRequested)
    {
        int events;
        android_poll_source* source = nullptr;

        ALooper_pollOnce(
                -1,
                nullptr,
                &events,
                reinterpret_cast<void**>(&source));

        if (source)
        {
            source->process(app, source);
        }
    }

    if (app->destroyRequested)
    {
        return;
    }

    aout << "window ready" << std::endl;

    auto renderer =
            std::make_unique<Renderer>(app);

    auto machine =
            std::make_unique<TestMachine>();

    Engine engine(
            machine.get(),
            renderer.get());

    while (!app->destroyRequested)
    {
        int events;
        android_poll_source* source = nullptr;

        while (ALooper_pollOnce(
                0,
                nullptr,
                &events,
                reinterpret_cast<void**>(&source)) >= 0)
        {
            if (source)
            {
                source->process(app, source);
            }

            if (app->destroyRequested)
            {
                return;
            }
        }

        engine.tick();
    }
}

}