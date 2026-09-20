#pragma once

#include <iostream>

#include "Renderer.h"
#include "AndroidOut.h"
#include "IMachine.h"

class Renderer;

class Engine
{
public:

    Engine(
            IMachine* machine,
            Renderer* renderer);

    void tick();

private:

    IMachine* machine_;
    Renderer* renderer_;
};