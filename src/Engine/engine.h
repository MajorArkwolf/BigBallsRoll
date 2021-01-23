#pragma once
#include "Engine/Audio/audioEngine.h"
#include "Engine/Audio/audioManager.h"
#include "Engine/modelManager.h"
#include "Engine/stateManager.h"
#include "Engine/textureManager.h"
#include <stdbool.h>
#include <lua.h>

typedef struct Engine {
    int timeSinceStart;
    ModelManager modelManager;
    StateManager sM;
    TextureManager textureManager;
    AudioEngine audioEngine;
    AudioManager audioManager;
    char *cwd;
    int width;
    int height;
    float fov;
    bool lockCamera;
    bool fullScreen;
    lua_State *lua;
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

void Engine_loadConfig();