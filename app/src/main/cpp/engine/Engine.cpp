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
    machine_->runFrame();

    renderer_->render(
            machine_->frameBuffer(),
            machine_->width(),
            machine_->height());

    for(int i = 0;
        i < Input::COUNT;
        i++)
    {
        Input::setKey(
                static_cast<Input::Key>(i),
                false);
    }

    Input::endFrame();
}