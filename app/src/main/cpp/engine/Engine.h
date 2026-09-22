#pragma once

#include <iostream>

#include "AndroidOut.h"

#include "engine/Input.h"
#include "engine/Renderer.h"
#include "machine/IMachine.h"

class Renderer;

class Engine {
public:

    Engine(
            IMachine *machine,
            Renderer *renderer);

    void tick();

private:

    IMachine *machine_;
    Renderer *renderer_;
};