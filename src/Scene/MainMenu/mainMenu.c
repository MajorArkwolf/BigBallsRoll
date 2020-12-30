#include "mainMenu.h"
#include <stdlib.h>
#include <Engine/engine.h>
#include "Engine/InputManager.h"
#include "Helper/stringPath.h"
int draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int update(float deltaTime) {
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects; ++i) {
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

void MainMenu_init(State *state) {
    state->camera = Camera_construct();
    state->update = update;
    state->draw = draw;
    state->keyDown = keyDown;
    state->keyUp = keyUp;
    state->mouseMovement = mouseMovement;

    //Test Model Load
    GameObject_init(&state->gameObjects[0]);
    GameObject_init(&state->gameObjects[1]);
    state->gameObjects[0].Transform.Position.X += 15.f;
    state->gameObjects[0].Transform.Position.Z += 5.f;
    state->gameObjects[0].ModelID = ModelManager_findModel(&engine.modelManager, "Off/colourcube.off");
    state->gameObjects[1].ModelID = ModelManager_findModel(&engine.modelManager, "Off/colourcube.off");
    state->gameObjects[1].Transform.Position.X += 15.f;
    state->gameObjects[1].Transform.Position.Z -= 5.f;
    state->NumOfGameObjects = 2;

    //Test Texture Load
    TextureManager_init(&engine.tM);
    TextureManager_loadTextures(&engine.tM, "/home/chase/ICT289/");
    printf("%s",engine.tM.Textures[0].textureName);
}
