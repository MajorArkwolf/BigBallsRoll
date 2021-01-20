#include "LevelOne.h"
#include <stdlib.h>
#include <Engine/engine.h>

int LevelOne_draw(float deltaTime) {
    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }
    return 0;
}

int LevelOne_update(float deltaTime) {
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects; ++i) {
        GameObject_update(&gameObjects[i]);
//        float rotationSpeed = 10.0f;
//        if (i % 2 == 0) {
//            rotationSpeed *= -1.0f;
//        }
//        gameObjects[i].Transform.Rotation.X += rotationSpeed * deltaTime;
//        gameObjects[i].Transform.Rotation.Y += rotationSpeed * deltaTime;
//        gameObjects[i].Transform.Rotation.Z += rotationSpeed * deltaTime;
    }
    return 0;
}

int LevelOne_keyDown(InputType inputType) {
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

int LevelOne_keyUp(InputType inputType) {
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
        case KEY_SPACEBAR:
            break;
        default:
            break;
    }
    return 0;
}

int LevelOne_mouseMovement(float x, float y) {
    Camera *cam = &StateManager_top(&engine.sM)->camera;
    // If cursor is locked, let the camera move, else ignore movement
    if (engine.lockCamera) {
        Camera_mouseLook(cam, x, y);
    }
    return 0;
}

void LevelOne_init(State *state) {
    state->camera = Camera_construct();
    state->update = LevelOne_update;
    state->draw = LevelOne_draw;
    state->keyDown = LevelOne_keyDown;
    state->keyUp = LevelOne_keyUp;
    state->mouseMovement = LevelOne_mouseMovement;

    GameObject_init(&state->gameObjects[0]);
    state->gameObjects[0].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[0].Transform.Position.X += 20.f;
    state->gameObjects[0].Transform.Position.Z += 5.f;
    state->gameObjects[0].Transform.Position.Y -= 3.f;
    state->gameObjects[0].Transform.Rotation.Y += 90.f;
    state->NumOfGameObjects = 1;
    state->camera.Position.Y += 2.0f;
    state->camera.Pitch -= 15.0f;
    Camera_updateCameraVectors(&state->camera);
}
