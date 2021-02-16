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
    PhysicsWorld_update(StateManager_top(&engine.sM)->physicsEngine.physicsWorld[0], deltaTime);
    Camera_update(&StateManager_top(&engine.sM)->camera, (float) deltaTime);
    GameObject *gameObjects = StateManager_top(&engine.sM)->gameObjects;
    for (size_t i = 0; i < StateManager_top(&engine.sM)->NumOfGameObjects; ++i) {
        GameObject_update(&gameObjects[i]);
    }
    // TODO: physics debug renderer
    //(if debug){
        //...
        //for(AABB in AABBS)
            //glColor3f(0,1,0);
            //glBegin(GL_POLYGON);
            //for(vertex in AABB)
                //glVertex3f;
            //glEnd;
    //}
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
    PhysicsEngine *physicsEngine = calloc(1, sizeof(PhysicsEngine));
    PhysicsEngine_init(physicsEngine);
    state->physicsEngine = *physicsEngine;
    state->physicsEngine.physicsWorld[0] = PhysicsEngine_newPhysicsWorld(&state->physicsEngine);

    // add wall
    GameObject_init(&state->gameObjects[0]);
    state->gameObjects[0].ModelID = ModelManager_findModel(&engine.modelManager, "Terrain/Wall.obj");
    state->gameObjects[0].Transform.Position.X += 0.f;
    state->gameObjects[0].Transform.Position.Z += 0.f;
    state->gameObjects[0].Transform.Position.Y -= 0.f;
    //state->gameObjects[0].Transform.Rotation.Y += 90.f;
    state->NumOfGameObjects = 1;
    state->camera.Position.Y += 2.0f;
    state->camera.Pitch -= 15.0f;
    Camera_updateCameraVectors(&state->camera);

    // create CollisionBody for object
    CollisionBody* wallCollisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(wallCollisionBody);

    // create collider
    BoxCollider *wallCollider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(wallCollider);
    wallCollider->xOffset = 0.f; // TODO: check interaction between overall position and "offset"
    wallCollider->yOffset = 0.f;
    wallCollider->zOffset = 0.f;
    wallCollider->xLen = 10.f;
    wallCollider->yLen = 1.f;
    wallCollider->zLen = 1.f;

    CollisionBody_addBoxCollider(wallCollisionBody, wallCollider);
    CollisionBody_setPos(wallCollisionBody, 0.f, 0.f, 0.f);
    CollisionBody_setRot(wallCollisionBody, 0.f, 0.f, 0.f);
    PhysicsWorld_addCollisionBody(state->physicsEngine.physicsWorld[0], wallCollisionBody);

    // add ball
    GameObject_init(&state->gameObjects[1]);
    state->gameObjects[1].ModelID = ModelManager_findModel(&engine.modelManager, "Ball.obj");
    state->gameObjects[1].Transform.Position.X += 0.f;
    state->gameObjects[1].Transform.Position.Y -= 0.f;
    //state->gameObjects[1].Transform.Position.Z -= 3.f;
    ++state->NumOfGameObjects;

    CollisionBody *ballCollisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(ballCollisionBody);

    SphereCollider *ballCollider = calloc(1, sizeof(SphereCollider));
    SphereCollider_init(ballCollider);
    ballCollider->radius = 1.f;
    //ballCollider->xOffset = 0.f;
    //ballCollider->yOffset = -3.f;
    //ballCollider->zOffset = -3.f;

    CollisionBody_addSphereCollider(ballCollisionBody, ballCollider);
    CollisionBody_setPos(ballCollisionBody, 0.f, 0.f, 0.f);
    PhysicsWorld_addCollisionBody(state->physicsEngine.physicsWorld[0], ballCollisionBody);

    // add box
}
