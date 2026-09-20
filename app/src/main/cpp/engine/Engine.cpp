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
    static int cnt=0;

    if((cnt++ % 60)==0)
    {
        aout << "tick" << std::endl;
    }

    machine_->runFrame();

    renderer_->render(
            machine_->frameBuffer(),
            machine_->width(),
            machine_->height());
}