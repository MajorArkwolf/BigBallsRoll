#pragma once
#include "Engine/modelManager.h"
#include "Engine/stateManager.h"

typedef struct Engine {
    int timeSinceStart;
    ModelManager modelManager;
    StateManager sM;
    int width;
    int height;
    float fov;
} Engine;

extern Engine engine;

int Engine_run(int argc, char *argv[]);

void Engine_stop();