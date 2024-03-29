#include "game.h"
#include <Engine/engine.h>
#include "Engine/luaHelper.h"
#include <assert.h>

double mouse[2];

int Game_draw(float deltaTime) {
    lua_getglobal(engine.lua, "Draw");
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int Game_update(float deltaTime) {
    State *state = StateManager_top(&engine.sM);
    lua_pushnumber(engine.lua, deltaTime);
    lua_setglobal(engine.lua, "deltaTime");
    lua_getglobal(engine.lua, "Update");
    lua_pushnumber(engine.lua, mouse[0]);
    lua_setglobal(engine.lua, "MouseDeltaX");
    lua_pushnumber(engine.lua, mouse[1]);
    lua_setglobal(engine.lua, "MouseDeltaY");
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    Camera_update(&state->camera, deltaTime);
    mouse[0] = 0.0;
    mouse[1] = 0.0;
    return 0;
}

int Game_keyDown(InputType inputType) {
    lua_getglobal(engine.lua, "InputKeyboardDown");
    lua_pushinteger(engine.lua, inputType);
    if (lua_pcall(engine.lua, 1, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    return 0;
}

int Game_keyUp(InputType inputType) {
    //Camera *cam = &StateManager_top(&engine.sM)->camera;
    lua_getglobal(engine.lua, "InputKeyboardUp");
    lua_pushinteger(engine.lua, (int)inputType);
    if (lua_pcall(engine.lua, 1, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    switch (inputType) {
        case KEY_F1:
            Engine_toggleCameraLock();
            break;
        case KEY_ESC:
            GuiManager_drawToggle(&engine.guiManager);
            break;
        case KEY_T:
            PhysicsWorld_debugToggle(StateManager_top(&engine.sM)->physicsWorld);
            break;
        default:
            break;
    }
    return 0;
}

int Game_mouseMovement(double x, double y) {
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
        mouse[0] = x;
        mouse[1] = y;
    }
    return 0;
}

int Game_mouseKey(int button, int buttonState) {
    lua_getglobal(engine.lua, "InputMouseButton");
    lua_pushinteger(engine.lua, button);
    lua_pushinteger(engine.lua, buttonState);
    if (lua_pcall(engine.lua, 2, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    return 0;
}

void Game_NextLevel(State *state) {
    for (size_t i = 0; i < state->NumOfGameObjects; ++i) {
        GameObject_free(&state->gameObjects[i]);
    }
    state->NumOfGameObjects = 0;
}

int Game_destroy() {
    lua_getglobal(engine.lua, "DeInit");
    if (lua_pcall(engine.lua, 0, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    PhysicsEngine_freePhysicsWorld(&engine.physicsEngine, StateManager_top(&engine.sM)->physicsWorld);
    State *state = StateManager_top(&engine.sM);
    for(size_t i = 0; i < state->NumOfGameObjects; ++i) {
        GameObject_free(&state->gameObjects[i]);
    }
    glPopAttrib();
    return 0;
}

void Game_init(State *state) {
    glPushAttrib(GL_LIGHTING_BIT);
    Engine_cameraLock(true);
    state->update = Game_update;
    state->draw = Game_draw;
    state->keyDown = Game_keyDown;
    state->keyUp = Game_keyUp;
    state->mouseMovement = Game_mouseMovement;
    state->mouseKeys = Game_mouseKey;
    state->destroy = Game_destroy;
    state->physicsWorld = PhysicsEngine_newPhysicsWorld(&engine.physicsEngine);
    PhysicsWorld_updateGravityNormal(state->physicsWorld, 0, -9.8f, 0);
    state->skyboxDraw = true;
    char file[] = "game.lua";
    mouse[0] = 0.0;
    mouse[1] = 0.0;
    LuaHelper_loadScript(file);
    LuaHelper_init();
}
