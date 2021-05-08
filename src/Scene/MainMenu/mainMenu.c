#include "mainMenu.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Engine/luaHelper.h"
#include "Scene/Game/game.h"

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
                size_t id = state->NumOfGameObjects;
                GameObject_init(&state->gameObjects[id]);
                GameObject_registerSoundSource(&state->gameObjects[id]);
                AudioEngine_play(state->gameObjects[id].SoundID, sound);
                AudioEngine_setVolume(state->gameObjects[id].SoundID, 100.0f);
                ++state->NumOfGameObjects;
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
    return 0;
}

int MainMenu_keyDown(InputType inputType) {
    switch (inputType) {
        default:
            break;
    }
    return 0;
}

int MainMenu_keyUp(InputType inputType) {
    switch (inputType) {
        case KEY_ESC:
            GuiManager_drawToggle(&engine.guiManager);
            break;
        case KEY_T:
            PhysicsWorld_debugToggle(StateManager_top(&engine.sM)->physicsWorld);
        default:
            break;
    }
    ActivateKonami(inputType);
    return 0;
}

int MainMenu_mouseMovement(double x, double y) {
    //Camera *cam = &StateManager_top(&engine.sM)->camera;
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
       // Camera_mouseLook(cam, x, y);
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
    state->skyboxDraw = true;
    state->physicsWorld = PhysicsEngine_newPhysicsWorld(&engine.physicsEngine);
    PhysicsWorld_updateGravityNormal(state->physicsWorld, 0, -9.8f, 0);
    engine.lockCamera = false;
    char file[] = "mainMenu.lua";
    LuaHelper_loadScript(file);
    LuaHelper_init();
}
