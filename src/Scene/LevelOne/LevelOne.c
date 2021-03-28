#include "LevelOne.h"
#include <stdlib.h>
#include <Engine/engine.h>


int LevelOne_draw(float deltaTime) {
    StateManager_top(&engine.sM)->gameObjects[0].Transform.Rotation.X += 1;
    StateManager_top(&engine.sM)->gameObjects[0].Transform.Rotation.Y += 1;
    StateManager_top(&engine.sM)->gameObjects[0].Transform.Rotation.Z += 1;
    CollisionBody_rotate(StateManager_top(&engine.sM)->physicsWorld->collisionBodies[0], 1, 1, 1);

    StateManager_top(&engine.sM)->gameObjects[3].Transform.Rotation.X += -1;
    StateManager_top(&engine.sM)->gameObjects[3].Transform.Rotation.Y += -1;
    StateManager_top(&engine.sM)->gameObjects[3].Transform.Rotation.Z += -1;
    CollisionBody_rotate(StateManager_top(&engine.sM)->physicsWorld->collisionBodies[3], -1, -1, -1);

    for (size_t index = 0; index < StateManager_top(&engine.sM)->NumOfGameObjects; ++index) {
        GameObject_draw(&StateManager_top(&engine.sM)->gameObjects[index]);
    }

    return 0;
}

int LevelOne_update(float deltaTime) {
    PhysicsWorld_update(StateManager_top(&engine.sM)->physicsWorld, deltaTime);
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects; ++i) {
        GameObject_update(&gameObjects[i]);
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
        case KEY_T:
            PhysicsWorld_debugToggle(StateManager_top(&engine.sM)->physicsWorld);
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

int LevelOne_mouseMovement(double x, double y) {
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
    state->physicsWorld = PhysicsEngine_newPhysicsWorld(&engine.physicsEngine);
    state->camera.Position.Y += 2.0f;
    state->camera.Pitch -= 15.0f;
    Camera_updateCameraVectors(&state->camera);

    // add wall
    GameObject_init(&state->gameObjects[0]);
    state->gameObjects[0].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[0].Transform.Position.X += 0.f;
    state->gameObjects[0].Transform.Position.Y += 0.f;
    state->gameObjects[0].Transform.Position.Z += 0.f;
    state->gameObjects[0].Transform.Rotation.X += 45.f;
    state->gameObjects[0].Transform.Rotation.Y += 45.f;
    state->gameObjects[0].Transform.Rotation.Z += 45.f;
    state->NumOfGameObjects = 1;
    // create CollisionBody for object
    CollisionBody* wallCollisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(wallCollisionBody);
    // create collider
    BoxCollider *wallCollider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(wallCollider);
    wallCollider->xOffset = 0.f;
    wallCollider->yOffset = 0.f;
    wallCollider->zOffset = -1.f;
    wallCollider->xLen = 10.f;
    wallCollider->yLen = 1.f;
    wallCollider->zLen = 1.f;
    CollisionBody_addBoxCollider(wallCollisionBody, wallCollider);
    CollisionBody_setPos(wallCollisionBody, 0.f, 0.f, 0.f);
    CollisionBody_setRot(wallCollisionBody, 45.f, 45.f, 45.f);
    PhysicsWorld_addCollisionBody(state->physicsWorld, wallCollisionBody);

    // add ball at rotation destination
    GameObject_init(&state->gameObjects[1]);
    state->gameObjects[1].ModelID = ModelManager_findModel(&engine.modelManager, "Ball.obj");
    state->gameObjects[1].Transform.Position.Z = -10.f;
    ++state->NumOfGameObjects;

    CollisionBody *ballCollisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(ballCollisionBody);

    SphereCollider *ballCollider = calloc(1, sizeof(SphereCollider));
    SphereCollider_init(ballCollider);
    ballCollider->radius = 0.5f;

    CollisionBody_addSphereCollider(ballCollisionBody, ballCollider);
    CollisionBody_setPos(ballCollisionBody, 0.f, 0.f, -10.f);
    PhysicsWorld_addCollisionBody(state->physicsWorld, ballCollisionBody);

    // add box at position pre-rotation
    GameObject_init(&state->gameObjects[2]);
    state->gameObjects[2].ModelID = ModelManager_findModel(&engine.modelManager, "Off/bluecube.off");
    state->gameObjects[2].Transform.Position.Z = 5.f;
    ++state->NumOfGameObjects;

    CollisionBody *boxCollisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(boxCollisionBody);

    BoxCollider *boxCollider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(boxCollider);

    boxCollider->xLen = 1.f;
    boxCollider->yLen = 1.f;
    boxCollider->zLen = 1.f;
    CollisionBody_addBoxCollider(boxCollisionBody, boxCollider);

    CollisionBody_setPos(boxCollisionBody, 0, 0, 5.f);
    PhysicsWorld_addCollisionBody(state->physicsWorld, boxCollisionBody);

    // add wall
    GameObject_init(&state->gameObjects[3]);
    state->gameObjects[3].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[3].Transform.Position.X += 10.f;
    state->gameObjects[3].Transform.Position.Y += 0.f;
    state->gameObjects[3].Transform.Position.Z += 0.f;
    state->gameObjects[3].Transform.Rotation.X += 400.f;
    state->gameObjects[3].Transform.Rotation.Y += 400.f;
    state->gameObjects[3].Transform.Rotation.Z += 400.f;
    ++state->NumOfGameObjects;
    // create CollisionBody for object
    CollisionBody* wallCollisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(wallCollisionBody2);
    // create collider
    BoxCollider* wallCollider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(wallCollider2);
    wallCollider2->xOffset = 0.f;
    wallCollider2->yOffset = 0.f;
    wallCollider2->zOffset = -1.f;
    wallCollider2->xLen = 10.f;
    wallCollider2->yLen = 1.f;
    wallCollider2->zLen = 1.f;
    CollisionBody_addBoxCollider(wallCollisionBody2, wallCollider2);
    CollisionBody_setPos(wallCollisionBody2, 10.f, 0.f, 0.f);
    CollisionBody_setRot(wallCollisionBody2, 400.f, 400.f, 400.f);
    PhysicsWorld_addCollisionBody(state->physicsWorld, wallCollisionBody2);

    // add wall
    GameObject_init(&state->gameObjects[4]);
    state->gameObjects[4].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[4].Transform.Position.X += -5.f;
    state->gameObjects[4].Transform.Position.Y += -5.f;
    state->gameObjects[4].Transform.Position.Z += -5.f;
    state->gameObjects[4].Transform.Rotation.X += 90.f;
    state->gameObjects[4].Transform.Rotation.Y += 90.f;
    state->gameObjects[4].Transform.Rotation.Z += 90.f;
    ++state->NumOfGameObjects;
    // create CollisionBody for object
    CollisionBody* wallCollisionBody3 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(wallCollisionBody3);
    // create collider
    BoxCollider* wallCollider3 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(wallCollider3);
    wallCollider3->xOffset = 0.f;
    wallCollider3->yOffset = 0.f;
    wallCollider3->zOffset = -1.f;
    wallCollider3->xLen = 10.f;
    wallCollider3->yLen = 1.f;
    wallCollider3->zLen = 1.f;
    wallCollider3->xRot = 90.f;
    wallCollider3->yRot = 0.f;
    wallCollider3->zRot = 0.f;
    CollisionBody_addBoxCollider(wallCollisionBody3, wallCollider3);
    CollisionBody_setPos(wallCollisionBody3, -5.f, -5.f, -5.f);
    CollisionBody_setRot(wallCollisionBody3, 0.f, 90.f, 90.f);
    PhysicsWorld_addCollisionBody(state->physicsWorld, wallCollisionBody3);
}
