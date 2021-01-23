#include "game.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Engine/InputManager.h"
#include "Engine/luaHelper.h"
#include "Helper/stringPath.h"

#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <assert.h>

int Game_draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int Game_update(float deltaTime) {
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    if(StateManager_top(&engine.sM)->NumOfGameObjects != 0) {
        for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects - 1; ++i) {
            float rotationSpeed = 10.0f;
            if (i % 2 == 0) {
                rotationSpeed *= -1.0f;
            }
            gameObjects[i].Transform.Rotation.X += rotationSpeed * deltaTime;
            gameObjects[i].Transform.Rotation.Y += rotationSpeed * deltaTime;
            gameObjects[i].Transform.Rotation.Z += rotationSpeed * deltaTime;
        }
    }
    return 0;
}

int Game_keyDown(InputType inputType) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    switch (inputType) {
        case KEY_UP_ARROW:
        case KEY_W:
            cam->MoveForward = true;
            break;
        case KEY_DOWN_ARROW:
        case KEY_S:
            cam->MoveBackward = true;
            break;
        case KEY_LEFT_ARROW:
        case KEY_A:
            cam->MoveLeft = true;
            break;
        case KEY_RIGHT_ARROW:
        case KEY_D:
            cam->MoveRight = true;
            break;
        default:
            break;
    }
    return 0;
}

int Game_keyUp(InputType inputType) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    switch (inputType) {
        case KEY_UP_ARROW:
        case KEY_W:
            cam->MoveForward = false;
            break;
        case KEY_DOWN_ARROW:
        case KEY_S:
            cam->MoveBackward = false;
            break;
        case KEY_LEFT_ARROW:
        case KEY_A:
            cam->MoveLeft = false;
            break;
        case KEY_RIGHT_ARROW:
        case KEY_D:
            cam->MoveRight = false;
            break;
        default:
            break;
    }
    return 0;
}

int Game_mouseMovement(float x, float y) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
        Camera_mouseLook(cam, x, y);
    }
    return 0;
}

void Game_init(State *state) {
    state->update = Game_update;
    state->draw = Game_draw;
    state->keyDown = Game_keyDown;
    state->keyUp = Game_keyUp;
    state->mouseMovement = Game_mouseMovement;
    char file[] = "game.lua";
    LuaHelper_loadScript(file);

    //Register functions for lua.
    lua_pushcfunction(engine.lua, Game_addGameObject);
    lua_setglobal(engine.lua, "GameObjectRegister");
    lua_pushcfunction(engine.lua, Game_setPosition);
    lua_setglobal(engine.lua, "GameObjectSetPosition");
    lua_pushcfunction(engine.lua, Game_setRotation);
    lua_setglobal(engine.lua, "GameObjectSetRotation");
    lua_pushcfunction(engine.lua, Game_setModel);
    lua_setglobal(engine.lua, "GameObjectSetModel");

    lua_getglobal(engine.lua, "Init");
    if (lua_pcall(engine.lua, 0, 1, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
}

int Game_addGameObject(lua_State *L) {
    //Get the ID ready for lua to manipulate a game object.
    State *state = StateManager_top(&engine.sM);
    size_t id = state->NumOfGameObjects;
    GameObject_init(&state->gameObjects[id]);
    ++state->NumOfGameObjects;
    lua_pushnumber(L, id);
    return 1;
}

int Game_setPosition(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->Transform.Position.X = lua_tonumber(L, 2);
    gameObject->Transform.Position.Y = lua_tonumber(L, 3);
    gameObject->Transform.Position.Z = lua_tonumber(L, 4);

    return 0;
}

int Game_setRotation(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    gameObject->Transform.Rotation.X = lua_tonumber(L, 2);
    gameObject->Transform.Rotation.Y = lua_tonumber(L, 3);
    gameObject->Transform.Rotation.Z = lua_tonumber(L, 4);

    return 0;
}

int Game_setModel(lua_State *L) {
    size_t id = lua_tonumber(L, 1);
    if (id > StateManager_top(&engine.sM)->NumOfGameObjects) {
        return 0;
    }
    GameObject *gameObject = &StateManager_top(&engine.sM)->gameObjects[id];
    size_t length = 0;
    const char* model = luaL_checklstring(L, 2,  &length);
    gameObject->ModelID = ModelManager_findModel(&engine.modelManager, model);

    return 0;
}
