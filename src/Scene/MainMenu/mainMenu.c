#include "mainMenu.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Engine/luaHelper.h"
#include "Scene/Game/game.h"
#include "Engine/stateManager.h"

bool paused = false;

InputType konamiCode[] = {KEY_UP_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW,
                        KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW,
                        KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_A, KEY_B};
size_t konamiCodeTracker = 0;
bool konamiCodeEntered = false;

void PauseMenu(bool desiredState) {
    if (desiredState != paused) {
        if (paused) {
            lua_getglobal(engine.lua, "MainMenuUnpause");
            if (lua_pcall(engine.lua, 0, 0, 0) == LUA_OK) {
                lua_pop(engine.lua, lua_gettop(engine.lua));
            }
            paused = false;
        } else {
            lua_getglobal(engine.lua, "MainMenuPause");
            if (lua_pcall(engine.lua, 0, 0, 0) == LUA_OK) {
                lua_pop(engine.lua, lua_gettop(engine.lua));
            }
            State_deregisterLights(StateManager_top(&engine.sM));
            paused = true;
        }
    }
}

void ActivateKonami(InputType inputType) {
    if (konamiCodeEntered == false && inputType == konamiCode[konamiCodeTracker]) {
        ++konamiCodeTracker;
    } else {
        konamiCodeTracker = 0;
    }
    if (konamiCodeTracker == 10) {
        konamiCodeTracker = 0;
        konamiCodeEntered = true;
        size_t konami = TextureManager_findTextureID(&engine.textureManager, "Konami.png");
        size_t modelID = ModelManager_findModel(&engine.modelManager, "Ball.obj");
        Model *model = ModelManager_getModel(&engine.modelManager, modelID);
        model->Mesh->Materials->DiffuseTexture = TextureManager_getTextureUsingID(&engine.textureManager, konami);
        ALuint unlock = 0;
        if (AudioManager_findSound(&engine.audioManager, "unlock.ogg", &unlock)) {
            Sound *sound = AudioManager_getSound(&engine.audioManager, unlock);
            if (sound != NULL) {
                State *state = StateManager_top(&engine.sM);
                GameObject_registerSoundSource(&state->gameObjects[0]);
                AudioEngine_play(state->gameObjects[0].SoundID, sound);
            }
        }
    }
}

int MainMenu_draw(float deltaTime) {
    PauseMenu(false);
    lua_getglobal(engine.lua, "MainMenuDraw");
    if (lua_pcall(engine.lua, 0, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int MainMenu_update(float deltaTime) {
    PauseMenu(false);
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    lua_pushnumber(engine.lua, deltaTime);
    lua_setglobal(engine.lua, "deltaTime");
    lua_getglobal(engine.lua, "MainMenuUpdate");
    if (lua_pcall(engine.lua, 0, 0, 0) == LUA_OK) {
        lua_pop(engine.lua, lua_gettop(engine.lua));
    }
    Camera_update(&StateManager_top(&engine.sM)->camera, deltaTime);
    engine.lockCamera = false;
    return 0;
}

int MainMenu_keyDown(InputType inputType) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    switch (inputType) {
        default:
            break;
    }
    return 0;
}

int MainMenu_keyUp(InputType inputType) {
    State *state;
    switch (inputType) {
        case KEY_ESC:
            glfwSetWindowShouldClose(engine.window, GLFW_TRUE);
            break;
        case KEY_SPACEBAR:
            PauseMenu(true);
            state = malloc(sizeof (State));
            State_init(state);
            StateManager_push(&engine.sM, state);
            Game_init(state);
            return 0;
        default:
            break;
    }
    ActivateKonami(inputType);
    return 0;
}

int MainMenu_mouseMovement(double x, double y) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
        Camera_mouseLook(cam, x, y);
    }
    return 0;
}

void MainMenu_init(State *state) {
    state->camera = Camera_construct();
    state->update = MainMenu_update;
    state->draw = MainMenu_draw;
    state->keyDown = MainMenu_keyDown;
    state->keyUp = MainMenu_keyUp;
    state->mouseMovement = MainMenu_mouseMovement;
    char file[] = "mainMenu.lua";
    LuaHelper_loadScript(file);
    LuaHelper_init();
//    GameObject_registerSoundSource(&state->gameObjects[2]);
//    AudioEngine_play(state->gameObjects[2].SoundID, &engine.audioManager.Sounds[0]);
}
