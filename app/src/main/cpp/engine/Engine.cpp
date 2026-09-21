#include "Engine.h"

Engine::Engine(
        IMachine* machine,
        Renderer* renderer)
        :
        machine_(machine),
        renderer_(renderer)
{
}

void Engine::tick()
{
    static int frameCounter = 0;

    frameCounter++;

    if((frameCounter % 60) == 0)
    {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "ENGINE",
                "before render %d",
                frameCounter);
    }

    machine_->runFrame();

    renderer_->render(
            machine_->frameBuffer(),
            machine_->width(),
            machine_->height());

    if((frameCounter % 60) == 0)
    {
        __android_log_print(
                ANDROID_LOG_ERROR,
                "ENGINE",
                "after render %d",
                frameCounter);
    }

    Input::endFrame();
}