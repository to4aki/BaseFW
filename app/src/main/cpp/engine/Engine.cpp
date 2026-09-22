#include "Engine.h"

Engine::Engine(
        IMachine *machine,
        Renderer *renderer)
        :
        machine_(machine),
        renderer_(renderer) {
    machine_->reset();
}

void Engine::tick() {
    static int frameCounter = 0;

    frameCounter++;

    machine_->runFrame();

    renderer_->render(
            machine_->frameBuffer(),
            machine_->width(),
            machine_->height());

    Input::endFrame();
}