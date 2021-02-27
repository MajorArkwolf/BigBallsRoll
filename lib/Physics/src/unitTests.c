#include "include/BigBalls/unitTests.h"
#include "include/BigBalls/physicsEngine.h"
#include <stdbool.h>
#include <stdio.h>
#include "include/BigBalls/physicsWorld.h"
#include "include/BigBalls/collisionBody.h"
#include <math.h>
#include <assert.h>

bool fTolerance(float a, float b, float tolerance){
    assert(tolerance >= 0);
    if(fabsf(a-b) < tolerance){
        return true;
    }
    else{
        return false;
    }
}

// test collision between identical objects
bool testIdenticalCollision(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody1, collider1);

    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody2, collider2);

    for(int i = 0; i <= 9; ++i){
        CollisionBody_translate(collisionBody2, 1, 0, 0);
    }
    bool colliding = testAABBCollision(collisionBody1, collisionBody2);
    return (colliding);
}

// ensure that a near-miss is a near-miss
bool testNoncollision(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xLen = 1.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody1, collider1);

    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider1->xLen = 1.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody2, collider2);
    CollisionBody_translate(collisionBody2, 1.1f, 0.f, 0.f);

    return (!testAABBCollision(collisionBody1, collisionBody2));
}

// test positive x rot
bool testAABBRotationX(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;

    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 90.f, 0.f, 0.f);

    if(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
        fTolerance(collisionBody->AABBy1, -3.f, 0.0001f) &&
        fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
        fTolerance(collisionBody->AABBx2, 1.f, 0.0001f) &&
        fTolerance(collisionBody->AABBy2, 0.f, 0.0001f) &&
        fTolerance(collisionBody->AABBz2, 2.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}

// test positive y rot
bool testAABBRotationY(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;

    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 0.f, 90.f, 0.f);

    if(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz1, -1.f, 0.0001f) &&
       fTolerance(collisionBody->AABBx2, 3.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy2, 2.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz2, 0.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}

// test positive Z rot
bool testAABBRotationZ(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;

    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 0.f, 0.f, 90.f);

    if(fTolerance(collisionBody->AABBx1, -2.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBx2, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy2, 1.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz2, 3.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}

bool testRotationIdentityMatrix(){
    float res[3][3] = {{0}};
    rotationTransformationMatrix(0, 0, 0, res);
    // no rotation should result in identity matrix
    if(res[0][0] == 1 &&
        res[0][1] == 0 &&
        res[0][2] == 0 &&
        res[1][0] == 0 &&
        res[1][1] == 1 &&
        res[1][2] == 0 &&
        res[2][0] == 0 &&
        res[2][1] == 0 &&
        res[2][2] == 1){
            return true;
    }
    else{
        return false;
    }
}

bool testRotationX(){
    float res[3][3] = {{0}};
    rotationTransformationMatrix(90.f,0.f,0.f, res);
    if(res[0][0] == 1 &&
       res[0][1] == 0 &&
       res[0][2] == 0 &&
       res[1][0] == 0 &&
       res[1][1] == cosf(90*(float)M_PI/180.f) &&
       res[1][2] == -1.f*sinf(90*(float)M_PI/180.f) &&
       res[2][0] == 0 &&
       res[2][1] == sinf(90*(float)M_PI/180.f) &&
       res[2][2] == cosf(90*(float)M_PI/180.f)) {
        return true;
    }
    else{
        return false;
    }
}

bool testRotationY(){
    float res[3][3] = {{0}};
    rotationTransformationMatrix(0, 90, 0, res);
    if(res[0][0] == cosf(90*(float)M_PI/180.f) &&
       res[0][1] == 0 &&
       res[0][2] == sinf(90*(float)M_PI/180.f) &&
       res[1][0] == 0 &&
       res[1][1] == 1 &
       res[1][2] == 0 &&
       res[2][0] == -1.f*sinf(90*(float)M_PI/180.f) &&
       res[2][1] == 0 &&
       res[2][2] == cosf(90*(float)M_PI/180.f)) {
        return true;
    }
    else{
        return false;
    }
}

bool testRotationZ(){
    float res[3][3] = {{0}};
    rotationTransformationMatrix(0, 0, 90, res);
    if(res[0][0] == cosf(90*(float)M_PI/180.f) &&
       res[0][1] == -1.f*sinf(90*(float)M_PI/180.f)  &&
       res[0][2] == 0 &&
       res[1][0] == sinf(90*(float)M_PI/180.f) &&
       res[1][1] == cosf(90*(float)M_PI/180.f) &
       res[1][2] == 0 &&
       res[2][0] == 0 &&
       res[2][1] == 0 &&
       res[2][2] == 1) {
        return true;
    }
    else{
        return false;
    }
}

bool testFullRotation(){
    float res[3][3] = {{0}};
    rotationTransformationMatrix(360,360,360, res);
    if(fTolerance(res[0][0], 1.f, 0.0001f) &&
        fTolerance(res[0][1], 0.f, 0.0001f) &&
        fTolerance(res[0][2], 0.f, 0.0001f) &&
        fTolerance(res[1][0], 0.f, 0.0001f) &&
        fTolerance(res[1][1], 1.f, 0.0001f) &&
        fTolerance(res[1][2], 0.f, 0.0001f) &&
        fTolerance(res[2][0], 0.f, 0.0001f) &&
        fTolerance(res[2][1], 0.f, 0.0001f) &&
        fTolerance(res[2][2], 1.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}

void startTests(){
    printf("1 = pass, 0 = fail\n");
    printf("Test Identical Collision: %d\n", testIdenticalCollision());
    printf("Test noncollision: %d\n", testNoncollision());
    printf("Test AABB Rotation X: %d\n", testAABBRotationX());
    printf("Test AABB Rotation Y: %d\n", testAABBRotationY());
    printf("Test AABB Rotation Z: %d\n", testAABBRotationZ());
    printf("Test rotation identity matrix: %d\n", testRotationIdentityMatrix());
    printf("Test x rotation: %d\n", testRotationX());
    printf("Test y rotation: %d\n", testRotationY());
    printf("Test z rotation: %d\n", testRotationZ());
    printf("Test full rotation: %d\n", testFullRotation());
}

