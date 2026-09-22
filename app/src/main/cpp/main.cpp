#include <memory>

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-activity/GameActivity.h>
#include <game-activity/GameActivityEvents.h>

#include "AndroidOut.h"

#include "Engine.h"
#include "Renderer.h"
#include "Input.h"
#include "Keyboard.h"

#include "machine/z80/Z80Machine.h"

extern "C"
{

#include <android/log.h>

void handle_cmd(
        android_app *app,
        int32_t cmd) {
    switch (cmd) {
        case APP_CMD_KEY_EVENT: {
            android_input_buffer *inputBuffer =
                    android_app_swap_input_buffers(
                            app);

            if (inputBuffer) {
                for (uint64_t i = 0;
                     i < inputBuffer->keyEventsCount;
                     i++) {
                    const GameActivityKeyEvent &e =
                            inputBuffer->keyEvents[i];

                    bool down =
                            (e.action == 0);

                    for (int m = 0;
                         m < Input::keyMapCount;
                         m++) {
                        if (Input::keyMap[m].androidKey
                            ==
                            e.keyCode) {
                            Input::setKey(
                                    Input::keyMap[m].key,
                                    down);

                            break;
                        }
                    }

                    if (down) {
                        Keyboard::putAndroidKey(
                                e.keyCode,
                                e.metaState);
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

void android_main(
        android_app *app) {
    app->onAppCmd =
            handle_cmd;

    while (app->window == nullptr &&
           !app->destroyRequested) {
        int events;

        android_poll_source *source =
                nullptr;

        ALooper_pollOnce(
                -1,
                nullptr,
                &events,
                reinterpret_cast<void **>(
                        &source));

        if (source) {
            source->process(
                    app,
                    source);
        }
    }

    if (app->destroyRequested) {
        return;
    }

    auto renderer =
            std::make_unique<Renderer>(
                    app);

    auto machine =
            std::make_unique<Z80Machine>();

    machine->setAssetManager(
            app->activity->assetManager);

    Engine engine(
            machine.get(),
            renderer.get());

    while (!app->destroyRequested) {
        int events;

        android_poll_source *source =
                nullptr;

        while (true) {
            int result =
                    ALooper_pollOnce(
                            0,
                            nullptr,
                            &events,
                            reinterpret_cast<void **>(
                                    &source));

            if (result < 0) {
                break;
            }

            if (source) {
                source->process(
                        app,
                        source);
            }
        }

        engine.tick();
    }
}

}