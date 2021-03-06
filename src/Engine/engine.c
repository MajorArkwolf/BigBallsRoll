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
void Update(double deltaTime) {
    int mouseMode = glfwGetInputMode(engine.window, GLFW_CURSOR);
    if (engine.lockCamera && mouseMode == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (!engine.lockCamera && mouseMode != GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    StateManager_update(&engine.sM, (float)deltaTime);

/**
 * Callback function for Draw
 */
void Draw(void) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Camera_lookAt(cam);
    StateManager_draw(&engine.sM, 0.0f);
    glfwSwapBuffers(engine.window);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputType inputType = InputType_convertRegularKey(key);
    if (action == GLFW_PRESS) {
        StateManager_keyDown(&engine.sM, inputType);
    } else if (action == GLFW_RELEASE) {
        if (inputType == KEY_F1) {
            //Toggle the lock Camera.
            engine.lockCamera = !engine.lockCamera;
        }
        if (inputType == KEY_ESC) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
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
 * Callback function for when a mouse button is pressed
 * @param button int representation of the button
 * @param state Unknown
 * @param x Unknown
 * @param y Unknown
 */
void mouseButton(int button, int state, int x, int y) {
    //InputType inputType = InputType_convertMouseButton(button);
    // Check state to determine if down or up then send down the stack.
    //StateManager_keyUp(&engine.sM, inputType);
    //StateManager_keyDown(&engine.sM, inputType);
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

    //Get the current working directory
    engine.cwd = getCurrentWorkingDirectory(argv[0]);

    //Initialise our Services
    TextureManager_init(&engine.textureManager);
    TextureManager_preLoadTextures(&engine.textureManager, engine.cwd);
    ModelManager_init(&engine.modelManager);
    ModelManager_loadModels(&engine.modelManager, engine.cwd);
    PhysicsEngine_init(&engine.physicsEngine);
	
	//Initialise LUA state
    engine.lua = luaL_newstate();
    luaL_openlibs(engine.lua);
    luaopen_math(engine.lua);
    luaopen_string(engine.lua);
    Engine_loadConfig();

    AudioEngine_init(&engine.audioEngine);
    AudioManager_init(&engine.audioManager);
    AudioManager_loadSounds(&engine.audioManager, engine.cwd);

    //Initialise our Game State.
    StateManager_init(&engine.sM);
    State *state = malloc(sizeof(State));
    State_init(state);
    MainMenu_init(state);
    StateManager_push(&engine.sM, state);
    if (engine.sM.stack[engine.sM.top] == NULL) {
        printf("Game stack failed to start.");
        return EXIT_FAILURE;
    }

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
    glfwSwapInterval(1);
    glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(engine.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetKeyCallback(engine.window, key_callback);
    glfwSetCursorPosCallback(engine.window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(engine.window, framebuffer_size_callback);
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    engine.textureManager.renderSetup = true;
    TextureManager_bindTexturesToRenderer(&engine.textureManager);

    // Set the view port for the window.
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(engine.window, &width, &height);
    framebuffer_size_callback(engine.window, width, height);

    /// This is a semi fixed time step implementation used to help break up our render and physics.
    double currentTime = glfwGetTime();
    double accumulator = 0.0;
    double deltaTime = 0.01;
    double time = 0.0;
    while(!glfwWindowShouldClose(engine.window)) {
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime) {
            glfwPollEvents();
            Update(deltaTime);
            //Physics update goes here.
            time += deltaTime;
            accumulator -= deltaTime;
        }
        Draw();
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
        engine.seed = lua_tonumber(engine.lua, -1);
    }
}
