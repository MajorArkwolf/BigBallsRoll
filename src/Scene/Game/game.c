#include "game.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Engine/InputManager.h"
#include "Helper/stringPath.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <assert.h>

int draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int update(float deltaTime) {
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects - 1; ++i) {
        float rotationSpeed = 10.0f;
        if (i % 2 == 0) {
            rotationSpeed *= -1.0f;
        }
        gameObjects[i].Transform.Rotation.X += rotationSpeed * deltaTime;
        gameObjects[i].Transform.Rotation.Y += rotationSpeed * deltaTime;
        gameObjects[i].Transform.Rotation.Z += rotationSpeed * deltaTime;
    }
    return 0;
}

int keyDown(InputType inputType) {
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

int keyUp(InputType inputType) {
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

int mouseMovement(float x, float y) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
        Camera_mouseLook(cam, x, y);
    }
    return 0;
}

void Game_init(State *state) {
    state->camera = Camera_construct();
    state->update = update;
    state->draw = draw;
    state->keyDown = keyDown;
    state->keyUp = keyUp;
    state->mouseMovement = mouseMovement;
    char file[] = "Script/game.lua";
    char* lua_location = malloc(sizeof (char) * (strlen(engine.cwd) + strlen(file) + 1));
    strcpy(lua_location, engine.cwd);
    strcat(lua_location, file);
    if(luaL_loadfile(engine.lua, lua_location) != LUA_OK) {
        assert(false);
    }

}
