#include "engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
#include "Helper/stringPath.h"
#include "Engine/luaHelper.h"
#include "Scene/MainMenu/mainMenu.h"
#include "Physics/physicsInterface.h"
#include "skybox.h"

Engine engine;

/// Used only in engine to keep state of the last position of the mouse, required for smooth mouse movement.
double lastMousePos[2];

/**
 * Callback function for glut when window size changes.
 * @param window the window context of the engine
 * @param w the new width
 * @param h the new height
 */
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) {
        h = 1;
    }

    float ratio = (float) w / (float) h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(engine.fov, ratio, 0.1f, 10000.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

/**
 * Callback function for glut update.
 * @param deltaTime Time since last frame
 */
void FixedUpdate(double deltaTime) {
    int mouseMode = glfwGetInputMode(engine.window, GLFW_CURSOR);
    if (engine.lockCamera && mouseMode == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (!engine.lockCamera && mouseMode != GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    StateManager_update(&engine.sM, (float) deltaTime);
}

void Update(double deltaTime) {
    State *state = StateManager_top(&engine.sM);
    for(size_t i = 0; i < state->NumOfGameObjects; ++i) {
        if (state->gameObjects[i].SoundID > 0) {
            AudioEngine_updateSource(state->gameObjects[i].SoundID, &state->gameObjects[i].Transform.Position,
                                     &state->gameObjects[i].Transform.Rotation);
        }
    }
}

/**
 * Callback function for Draw
 */
void Draw(void) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Skybox_draw();
    Camera_lookAt(cam);
    StateManager_draw(&engine.sM, 0.0f);
    PhysicsInterface_draw(StateManager_top(&engine.sM)->physicsWorld);
    GuiManager_draw(&engine.guiManager);

    glfwSwapBuffers(engine.window);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputType inputType = InputType_convertRegularKey(key);
    if (action == GLFW_PRESS) {
        StateManager_keyDown(&engine.sM, inputType);
    } else if (action == GLFW_RELEASE) {
        StateManager_keyUp(&engine.sM, inputType);
    }
}

/**
 * Callback function for the mouse movement.
 * @param window The active engine window
 * @param xPos Coordinates local to the window on the x axis
 * @param yPos Coordinates local to the window on the y axis
 */
static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos) {
    double xOffset = xPos - lastMousePos[0];
    double yOffset = yPos - lastMousePos[1];
    StateManager_mouseMove(&engine.sM, xOffset, yOffset * -1.0);
    lastMousePos[0] = xPos;
    lastMousePos[1] = yPos;
}

/**
 * Callback function for the mouse buttons.
 * @param window The active engine window
 * @param button mouse button pressed
 * @param action if pressed or released
 * @param mods unknown
 */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    InputType input = InputType_convertMouseButton(button);
    int buttonState = action == GLFW_PRESS;
    StateManager_mouseKeys(&engine.sM, input, buttonState);
    GuiManager_mouse_button_callback(window, button, action, mods);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int Engine_run(int argc, char *argv[]) {
    //Engine Defaults
    engine.width = 1600;
    engine.height = 1200;
    engine.fov = 60.0f;
    engine.lockCamera = false;
    engine.fullScreen = false;
    engine.running = true;

    //Get the current working directory
    engine.cwd = getCurrentWorkingDirectory(argv[0]);

    // Init here to avoid config values being overwritten.
    AudioEngine_AudioPresets_init(&engine.audioPresets);

    //Initialise our Services
    TextureManager_init(&engine.textureManager);
    TextureManager_preLoadTextures(&engine.textureManager, engine.cwd);
    Skybox_loadTexture();
    ModelManager_init(&engine.modelManager);
    ModelManager_loadModels(&engine.modelManager, engine.cwd);
    PlayerConfig_init(&engine.playerConfig);
    PhysicsInterface_init();

	//Initialise LUA state
    engine.lua = luaL_newstate();
    luaL_openlibs(engine.lua);
    luaopen_math(engine.lua);
    luaopen_string(engine.lua);
    Engine_loadConfig();

    AudioEngine_init(&engine.audioEngine);
    AudioManager_init(&engine.audioManager);
    AudioManager_loadSounds(&engine.audioManager, engine.cwd);
    AudioEngine_changeMasterVolume(&engine.audioPresets);

    glfwSetErrorCallback(error_callback);
    //Initialise our Window and OpenGL context.
    if (!glfwInit()){
        return EXIT_FAILURE;
    }
    if (engine.fullScreen) {
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    engine.window = glfwCreateWindow(engine.width, engine.height, "Big Balls Roll", NULL, NULL);
    if(engine.window == NULL) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(engine.window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(engine.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetKeyCallback(engine.window, key_callback);
    glfwSetCursorPosCallback(engine.window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(engine.window, framebuffer_size_callback);
    glfwSetInputMode(engine.window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    // GUI init after window creation
    GuiManager_init(&engine.guiManager);
    //Overwrite Nuklears function pointer so it doesnt steal our function call.
    glfwSetMouseButtonCallback(engine.window, mouse_button_callback);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_SMOOTH);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    engine.textureManager.renderSetup = true;
    TextureManager_bindTexturesToRenderer(&engine.textureManager);

    // Set the view port for the window.
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(engine.window, &width, &height);
    framebuffer_size_callback(engine.window, width, height);

    //Initialise our Game State.
    StateManager_init(&engine.sM);
    State *state = malloc(sizeof(State));
    State_init(state);
    StateManager_push(&engine.sM, state);
    MainMenu_init(state);
    if (engine.sM.stack[engine.sM.top] == NULL) {
        printf("Game stack failed to start.");
        return EXIT_FAILURE;
    }

    /// This is a semi fixed time step implementation used to help break up our render and physics.
    double currentTime = glfwGetTime();
    double accumulator = 0.0;
    double deltaTime = 0.01;
    while(!glfwWindowShouldClose(engine.window) && engine.running) {
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime) {
            glfwPollEvents();
            FixedUpdate(deltaTime);
            PhysicsInterface_update(deltaTime);
            accumulator -= deltaTime;
        }
        Update(frameTime);
        Draw();
        StateManager_safeStateRemoval(&engine.sM);
    }
    glfwDestroyWindow(engine.window);
    glfwTerminate();
    Engine_stop();
    return EXIT_SUCCESS;
}

void Engine_stop() {
    AudioEngine_stop_all(&engine.audioEngine);
    AudioManager_free(&engine.audioManager);
    AudioEngine_free(&engine.audioEngine);
    ModelManager_free(&engine.modelManager);
    TextureManager_free(&engine.textureManager);
    PhysicsInterface_free();
    GuiManager_free(&engine.guiManager);
    StateManager_free(&engine.sM);
    lua_close(engine.lua);
    free(engine.cwd);
}

void Engine_loadConfig() {
    char configFile[] = {"config.lua"};
    LuaHelper_loadScript(configFile);
    //Get width
    lua_getglobal(engine.lua, "width");
    if (lua_isnumber(engine.lua, 0) == 0) {
        engine.width = lua_tonumber(engine.lua, -1);
    }
    //Get Height
    lua_getglobal(engine.lua, "height");
    if (lua_isnumber(engine.lua, 0) == 0) {
        engine.height = lua_tonumber(engine.lua, -1);
    }
    //Get Fov
    lua_getglobal(engine.lua, "fov");
    if (lua_isnumber(engine.lua, 0) == 0) {
        engine.fov = lua_tonumber(engine.lua, -1);
    }

    //Get Fullscreen
    lua_getglobal(engine.lua, "fullscreen");
    if (lua_isboolean(engine.lua, 0) == 0) {
        engine.fullScreen = lua_toboolean(engine.lua, -1);
    }
    //Get Configured Seed.
    lua_getglobal(engine.lua, "seed");
    if (lua_isnumber(engine.lua, 0) == 0) {
        engine.playerConfig.seed = lua_tonumber(engine.lua, -1);
    }
    //Get master volume
    lua_getglobal(engine.lua, "master_volume");
    if (lua_isnumber(engine.lua, 0) == 0) {
        engine.audioPresets.MasterVolume = lua_tonumber(engine.lua, -1);
    }
}

void Engine_toggleCameraLock() {
    engine.lockCamera = !engine.lockCamera;
}

void Engine_cameraLock(bool lockCamera) {
    engine.lockCamera = lockCamera;
}

void UpdateWindow() {
    int xPos = 0;
    int yPos = 0;
    glfwGetWindowPos(engine.window, &xPos, &yPos);
    if (engine.playerConfig.windowedMode) {
        glfwSetWindowMonitor(engine.window,
                             NULL,
                             xPos,
                             yPos,
                             engine.playerConfig.width,
                             engine.playerConfig.height,
                             60);
    } else {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(engine.window,
                                glfwGetPrimaryMonitor(),
                                0,
                                0,
                                mode->width,
                                mode->height,
                                mode->refreshRate);
    }
}

void UpdateAudio() {
    AudioEngine_changeMasterVolume(&engine.audioPresets);
}

void Engine_updateConfig() {
    UpdateWindow();
    UpdateAudio();
    LuaHelper_PlayerConfig();
}
