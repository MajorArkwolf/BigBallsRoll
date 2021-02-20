#include "engine.h"
#include "Engine/OpenGL.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
#include "Helper/stringPath.h"
#include "Engine/Audio/audioEngine.h"
#include "Engine/luaHelper.h"
#include "Scene/MainMenu/mainMenu.h"

const float FRAMERATE = 1 / 60.0f;                     // ~60 FPS.
const float FRAMERATE_MILLIS = 1 / 60.0f * 1000;       // Millisecond version of framerate.
const float PHYSICS_MILLIS = 200;

Engine engine;

/**
 * Callback function for glut when window size changes.
 * @param w the new width
 * @param h the new height
 */
void changeSize(int w, int h) {

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
 * @param value
 */
void Update(int value) {
    // Timer to start update function again based on frame rate.
    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);
    int oldTime = engine.timeSinceStart;
    engine.timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float) (engine.timeSinceStart - oldTime) / 1000.0f;
    StateManager_update(&engine.sM, deltaTime);
}

/**
 * Callback function for Draw
 */
void Draw(void) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    // Move cursor back to middle if camera lock is on
    if (engine.lockCamera) {
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Camera_lookAt(cam);
    glColor3f(255, 255, 255);

    StateManager_draw(&engine.sM, 0.0f);

    glutSwapBuffers();
}

/**
 * Process key press for normal keys, callback function for glut
 * @param key character of the key that was pressed.
 * @param xx Unknown
 * @param yy Unknown
 */
void processNormalKeys(unsigned char key, int xx, int yy) {
    InputType inputType = InputType_convertRegularKey((char) key);
    StateManager_keyDown(&engine.sM, inputType);
}

/**
 * Process key release for normal keys, callback function for glut
 * @param key character of the key that was pressed.
 * @param xx Unknown
 * @param yy Unknown
 */
void processNormalKeysUp(unsigned char key, int xx, int yy) {
    InputType inputType = InputType_convertRegularKey((char) key);
    if (inputType == KEY_ESC) {
        Engine_stop();
        exit(EXIT_SUCCESS);
    }
    StateManager_keyUp(&engine.sM, inputType);
}

/**
 * Process key press for special keys, callback function for glut
 * @param key int representation of the key that was pressed.
 * @param xx Unknown
 * @param yy Unknown
 */
void pressKey(int key, int xx, int yy) {
    InputType inputType = InputType_convertSpecialKey(key);
    StateManager_keyDown(&engine.sM, inputType);
    //glutSetWindow(mainWindow);
    //glutPostRedisplay();
}

/**
 * Process key release for special keys, callback function for glut
 * @param key int representation of the key that was pressed.
 * @param x Unknown
 * @param y Unknown
 */
void releaseKey(int key, int x, int y) {
    InputType inputType = InputType_convertSpecialKey(key);
    if (inputType == KEY_F1) {
        //Toggle the lock Camera.
        engine.lockCamera = !engine.lockCamera;
    }
    StateManager_keyUp(&engine.sM, inputType);
}

/**
 * Callback function for the mouse movement.
 * @param x Coordinates local to the window on the x axis
 * @param y Coordinates local to the window on the y axis
 */
void mouseMove(int x, int y) {
    float lastX = (float) x - glutGet(GLUT_WINDOW_WIDTH) / 2;
    float lastY = ((float) y - glutGet(GLUT_WINDOW_HEIGHT) / 2) * -1;
    StateManager_mouseMove(&engine.sM, lastX, lastY);
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


    //Initialise our Window and OpenGL context.
    glutInit(&argc, argv);
    //Set the window position to the centre of the screen.
    int x_offset = glutGet(GLUT_SCREEN_WIDTH) / 2 - engine.width / 2;
    int y_offset = glutGet(GLUT_SCREEN_HEIGHT) / 2 - engine.height / 2;

    glutInitWindowPosition(x_offset, y_offset);
    glutInitWindowSize(engine.width, engine.height);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE |
                        GLUT_RGBA);
    glutCreateWindow("Plachinko");
    if (!glutExtensionSupported("GL_EXT_abgr")) {
        printf("Couldn't find abgr extension.\n");
        exit(EXIT_FAILURE);
    }

    if (engine.fullScreen) {
        glutFullScreen();
    }

    // Render Que
    glutDisplayFunc(Draw);
    glutReshapeFunc(changeSize);
    glutIdleFunc(Draw);

    // register callbacks
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processNormalKeysUp);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    engine.textureManager.renderSetup = true;
    TextureManager_bindTexturesToRenderer(&engine.textureManager);

    glutTimerFunc(FRAMERATE_MILLIS, Update, 0);
    engine.timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
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
}
