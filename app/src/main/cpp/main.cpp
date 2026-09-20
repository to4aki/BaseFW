#include <memory>

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-activity/GameActivity.h>
#include <game-activity/GameActivityEvents.h>

#include "AndroidOut.h"

#include "Engine.h"
#include "Renderer.h"
#include "Input.h"

#include "machine/TestMachine.h"

extern "C"
{

#include <android/log.h>

void handle_cmd(
        android_app* app,
        int32_t cmd)
{
    switch(cmd)
    {
        case APP_CMD_KEY_EVENT:
        {
            android_input_buffer* inputBuffer =
                    android_app_swap_input_buffers(
                            app);

            if(inputBuffer)
            {
                for(uint64_t i = 0;
                    i < inputBuffer->keyEventsCount;
                    i++)
                {
                    const GameActivityKeyEvent& e =
                            inputBuffer->keyEvents[i];

                    if(e.action != 0)
                    {
                        continue;
                    }

                    switch(e.keyCode)
                    {
                        case 19:

                            Input::pressKey(
                                    Input::UP);

                            break;

                        case 20:

                            Input::pressKey(
                                    Input::DOWN);

                            break;

                        case 21:

                            Input::pressKey(
                                    Input::LEFT);

                            break;

                        case 22:

                            Input::pressKey(
                                    Input::RIGHT);

                            break;

                        case 66:

                            Input::pressKey(
                                    Input::ENTER);

                            break;

                        case 111:

                            Input::pressKey(
                                    Input::ESC);

                            break;
                    }
                }

                android_app_clear_key_events(
                        inputBuffer);

                android_app_clear_motion_events(
                        inputBuffer);
            }

            break;
        }

        default:

            break;
    }
}

void android_main(android_app* app)
{
    app->onAppCmd =
            handle_cmd;

    while(app->window == nullptr &&
          !app->destroyRequested)
    {
        int events;
        android_poll_source* source = nullptr;

        ALooper_pollOnce(
                -1,
                nullptr,
                &events,
                reinterpret_cast<void**>(
                        &source));

        if(source)
        {
            source->process(
                    app,
                    source);
        }
    }

    if(app->destroyRequested)
    {
        return;
    }

    auto renderer =
            std::make_unique<Renderer>(
                    app);

    auto machine =
            std::make_unique<TestMachine>();

    Engine engine(
            machine.get(),
            renderer.get());

    while(!app->destroyRequested)
    {
        int events;
        android_poll_source* source = nullptr;

        int result =
                ALooper_pollOnce(
                        0,
                        nullptr,
                        &events,
                        reinterpret_cast<void**>(
                                &source));

        if(result >= 0)
        {
            if(source)
            {
                source->process(
                        app,
                        source);
            }
        }

        engine.tick();
    }
}

}