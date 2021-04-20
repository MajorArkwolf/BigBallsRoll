#pragma once
#include "Engine/Audio/audioEngine.h"
#include "Engine/Audio/audioManager.h"
#include "Engine/modelManager.h"
#include "Engine/stateManager.h"
#include "Engine/textureManager.h"
#include "BigBalls/physicsEngine.h"
#include <stdbool.h>
#include <lua.h>
#include "Engine/OpenGL.h"
#include "playerConfig.h"

typedef struct Engine {
    int timeSinceStart;
    ModelManager modelManager;
    StateManager sM;
    TextureManager textureManager;
    AudioEngine audioEngine;
    AudioPresets audioPresets;
    AudioManager audioManager;
    PlayerConfig playerConfig;
    PhysicsEngine physicsEngine;
    char *cwd;
    int width;
    int height;
    float fov;
    bool lockCamera;
    bool fullScreen;
    bool gui;
    int seed;
    lua_State *lua;
    GLFWwindow* window;
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
 * Toggles the camera from the locked state.
 */
void Engine_toggleCameraLock();

/**
 * Locks the camera if the value passed in is true.
 * @param lockCamera
 */
void Engine_cameraLock(bool lockCamera);

/**
 * Frees any memory the engine is using on the heap
 */
void Engine_stop();

/**
 * Load the config lua to set the default values.
 */
void Engine_loadConfig();
