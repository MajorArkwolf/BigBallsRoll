#pragma once
#include "Engine/modelManager.h"
#include "Engine/stateManager.h"
#include "Engine/textureManager.h"
#include <stdbool.h>

typedef struct Engine {
    int timeSinceStart;
    ModelManager modelManager;
    StateManager sM;
    TextureManager tM;
    int width;
    int height;
    float fov;
    bool lockCamera;
} Engine;

extern Engine engine;

/**
 * Run the engine
 * @param argc passed from main
 * @param argv passed from main
 * @return 0 on success 1 on failure
 */
int Engine_run(int argc, char *argv[]);

/**
 * Frees any memory the engine is using on the heap
 */
void Engine_stop();
