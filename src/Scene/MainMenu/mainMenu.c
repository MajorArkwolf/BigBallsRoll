#include "mainMenu.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Scene/Game/game.h"
#include "Engine/stateManager.h"

int MainMenu_draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int MainMenu_update(float deltaTime) {
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects; ++i) {
        GameObject_update(&gameObjects[i]);
    }
    return 0;
}

int MainMenu_keyDown(InputType inputType) {
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

int MainMenu_keyUp(InputType inputType) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    State *state;
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
        case KEY_SPACEBAR:
            state = malloc(sizeof (State));
            State_init(state);
            StateManager_push(&engine.sM, state);
            Game_init(state);
            return 0;
        default:
            break;
    }
    return 0;
}

int MainMenu_mouseMovement(float x, float y) {
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

    GameObject_init(&state->gameObjects[0]);
    GameObject_init(&state->gameObjects[1]);
    GameObject_init(&state->gameObjects[2]);
    GameObject_init(&state->gameObjects[3]);
    state->gameObjects[0].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[1].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Floor.obj");
    state->gameObjects[2].ModelID = ModelManager_findModel(&engine.modelManager, "Obj/Title.obj");
    state->gameObjects[3].ModelID = ModelManager_findModel(&engine.modelManager, "Ball.obj");
    state->gameObjects[0].Transform.Position.X += 20.f;
    state->gameObjects[0].Transform.Position.Z += 5.f;
    state->gameObjects[0].Transform.Position.Y -= 3.f;
    state->gameObjects[0].Transform.Rotation.Y += 90.f;
    state->gameObjects[1].Transform.Position.X += 20.f;
    state->gameObjects[1].Transform.Position.Y -= 4.f;
    state->gameObjects[1].Transform.Position.Z -= 5.f;
    state->gameObjects[1].Transform.Rotation.Y += 180.f;
    state->gameObjects[2].Transform.Position.X += 15.f;
    state->gameObjects[2].Transform.Position.Z += 0.25f;
    state->gameObjects[2].Transform.Rotation.X = 90.f;
    state->gameObjects[2].Transform.Rotation.Y -= 90.f;
    state->gameObjects[3].Transform.Position.X += 15.0f;
    state->gameObjects[3].Transform.Position.Y -= 2.5f;
    state->NumOfGameObjects = 4;

    state->camera.Position.Y += 2.0f;
    state->camera.Pitch -= 15.0f;
    Camera_updateCameraVectors(&state->camera);

    GameObject_registerSoundSource(&state->gameObjects[2]);
    AudioEngine_play(state->gameObjects[2].SoundID, &engine.audioManager.Sounds[0]);
}
