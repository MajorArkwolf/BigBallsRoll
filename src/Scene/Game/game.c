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
    Camera_update(&StateManager_top(&engine.sM)->camera, deltaTime);
    mouse[0] = 0.0;
    mouse[1] = 0.0;
    return 0;
}

int Game_keyDown(InputType inputType) {
    lua_getglobal(engine.lua, "InputKeyboardDown");
    lua_pushinteger(engine.lua, inputType);
    if (lua_pcall(engine.lua, 1, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
//    Camera *cam = &StateManager_top(&engine.sM)->camera;
//    switch (inputType) {
//        case KEY_UP_ARROW:
//        case KEY_W:
//            cam->MoveForward = true;
//            break;
//        case KEY_DOWN_ARROW:
//        case KEY_S:
//            cam->MoveBackward = true;
//            break;
//        case KEY_LEFT_ARROW:
//        case KEY_A:
//            cam->MoveLeft = true;
//            break;
//        case KEY_RIGHT_ARROW:
//        case KEY_D:
//            cam->MoveRight = true;
//            break;
//        default:
//            break;
//    }
    return 0;
}

int Game_keyUp(InputType inputType) {
    //Camera *cam = &StateManager_top(&engine.sM)->camera;
    lua_getglobal(engine.lua, "InputKeyboardUp");
    lua_pushinteger(engine.lua, (int)inputType);
    if (lua_pcall(engine.lua, 1, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    switch (inputType) {
//        case KEY_UP_ARROW:
//        case KEY_W:
//            cam->MoveForward = false;
//            break;
//        case KEY_DOWN_ARROW:
//        case KEY_S:
//            cam->MoveBackward = false;
//            break;
//        case KEY_LEFT_ARROW:
//        case KEY_A:
//            cam->MoveLeft = false;
//            break;
//        case KEY_RIGHT_ARROW:
//        case KEY_D:
//            cam->MoveRight = false;
//            break;
        case KEY_F1:
            Engine_toggleCameraLock();
            break;
        case KEY_ESC:
            StateManager_pop(&engine.sM);
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

void Game_init(State *state) {
    Engine_cameraLock(true);
    state->update = Game_update;
    state->draw = Game_draw;
    state->keyDown = Game_keyDown;
    state->keyUp = Game_keyUp;
    state->mouseMovement = Game_mouseMovement;
    char file[] = "game.lua";
    mouse[0] = 0.0;
    mouse[1] = 0.0;
    LuaHelper_loadScript(file);
    LuaHelper_init();
}

void Game_NextLevel(State *state) {
    state->NumOfGameObjects = 0;
}
