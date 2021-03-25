#include <stdbool.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "include/BigBalls/unitTests.h"
#include "include/BigBalls/physicsWorld.h"
#include "include/BigBalls/collisionBody.h"
#include "include/BigBalls/mathsCommon.h"

bool testIdentity44(){
    Matrix44 sus = identity44();
    Matrix44 target = {.elem[0] = {1, 0, 0, 0},
                       .elem[1] = {0, 1, 0, 0},
                       .elem[2] = {0, 0, 1, 0},
                       .elem[3] = {0, 0, 0, 1}};
    return compareMatrix44(sus, target);
}

bool testMatrixMultiplication44_44(){
    Matrix44 a = {.elem[0] = {5, 2, 6, 1},
                  .elem[1] = {0, 6, 2, 0},
                  .elem[2] = {3, 8, 1, 4},
                  .elem[3] = {1, 8 ,5, 6}};
    Matrix44 b = {.elem[0] = {7, 5, 8, 0},
                  .elem[1] = {1, 8, 2, 6},
                  .elem[2] = {9, 4, 3, 8},
                  .elem[3] = {5, 3, 7, 9}};
    Matrix44 sus = matrixMultiplication44_44(a, b);
    Matrix44 target = {.elem[0] = {96, 68, 69, 69},
                       .elem[1] = {24, 56, 18, 52},
                       .elem[2] = {58, 95, 71, 92},
                       .elem[3] = {90, 107, 81, 142}};
    return compareMatrix44(sus, target);
}

bool testMatrixMultiplication44_41(){
    Matrix44 a = {.elem[0] = {5, 45, -3, 4},
                  .elem[1] = {3, -2, 11, 9},
                  .elem[2] = {2, 31, 6, 22},
                  .elem[3] = {6, -5 ,-9, 7}};
    Matrix41 b = {2, -3, 4, 5};
    Matrix41 sus = matrixMultiplication44_41(a, b);
    Matrix41 target = {-117, 101, 45, 26};
    return compareMatrix41(sus, target);
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

// test positive y rot
bool testAABBStackedRotation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xRot = 180.f;

    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 180.f, 0.f, 0.f);

    if(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBx2, 1.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy2, 2.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz2, 3.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}

/**
bool testRotationIdentityMatrix(){
    Matrix44 res = rotationTransformationMatrix(0, 0, 0);
    // no rotation should result in identity matrix
    if(res.elem[0][0] == 1 &&
        res.elem[0][1] == 0 &&
        res.elem[0][2] == 0 &&
        res.elem[1][0] == 0 &&
        res.elem[1][1] == 1 &&
        res.elem[1][2] == 0 &&
        res.elem[2][0] == 0 &&
        res.elem[2][1] == 0 &&
        res.elem[2][2] == 1){
            return true;
    }
    else{
        return false;
    }
}*/

/**
bool testRotationX(){
    Matrix44 res = rotationTransformationMatrix(90.f,0.f,0.f);
    if(res.elem[0][0] == 1 &&
       res.elem[0][1] == 0 &&
       res.elem[0][2] == 0 &&
       res.elem[1][0] == 0 &&
       res.elem[1][1] == cosf(90*(float)M_PI/180.f) &&
       res.elem[1][2] == -1.f*sinf(90*(float)M_PI/180.f) &&
       res.elem[2][0] == 0 &&
       res.elem[2][1] == sinf(90*(float)M_PI/180.f) &&
       res.elem[2][2] == cosf(90*(float)M_PI/180.f)) {
        return true;
    }
    else{
        return false;
    }
}

bool testRotationY(){
    Matrix44 res = rotationTransformationMatrix(0, 90, 0);
    if(res.elem[0][0] == cosf(90*(float)M_PI/180.f) &&
       res.elem[0][1] == 0 &&
       res.elem[0][2] == sinf(90*(float)M_PI/180.f) &&
       res.elem[1][0] == 0 &&
       res.elem[1][1] == 1 &
       res.elem[1][2] == 0 &&
       res.elem[2][0] == -1.f*sinf(90*(float)M_PI/180.f) &&
       res.elem[2][1] == 0 &&
       res.elem[2][2] == cosf(90*(float)M_PI/180.f)) {
        return true;
    }
    else{
        return false;
    }
}

bool testRotationZ(){
    Matrix44 res = rotationTransformationMatrix(0, 0, 90);
    if(res.elem[0][0] == cosf(90*(float)M_PI/180.f) &&
       res.elem[0][1] == -1.f*sinf(90*(float)M_PI/180.f)  &&
       res.elem[0][2] == 0 &&
       res.elem[1][0] == sinf(90*(float)M_PI/180.f) &&
       res.elem[1][1] == cosf(90*(float)M_PI/180.f) &
       res.elem[1][2] == 0 &&
       res.elem[2][0] == 0 &&
       res.elem[2][1] == 0 &&
       res.elem[2][2] == 1) {
        return true;
    }
    else{
        return false;
    }
}

bool testFullRotation(){
    Matrix44 res = rotationTransformationMatrix(360,360,360);
    if(fTolerance(res.elem[0][0], 1.f, 0.0001f) &&
        fTolerance(res.elem[0][1], 0.f, 0.0001f) &&
        fTolerance(res.elem[0][2], 0.f, 0.0001f) &&
        fTolerance(res.elem[1][0], 0.f, 0.0001f) &&
        fTolerance(res.elem[1][1], 1.f, 0.0001f) &&
        fTolerance(res.elem[1][2], 0.f, 0.0001f) &&
        fTolerance(res.elem[2][0], 0.f, 0.0001f) &&
        fTolerance(res.elem[2][1], 0.f, 0.0001f) &&
        fTolerance(res.elem[2][2], 1.f, 0.0001f)){
        return true;
    }
    else{
        return false;
    }
}*/

bool coolTest(){
    Matrix41 myCoord = {.elem[0] = 1,
                        .elem[1] = 1,
                        .elem[2] = 1,
                        .elem[3] = 1};

    Matrix44 res = createRotMat(45, 45, 45); // 45, 45, 45 rotation
    Matrix41 final = matrixMultiplication44_41(res, myCoord);
    if(fTolerance(final.elem[0], 45*M_PI/180.f, 0.001f) &&
       fTolerance(final.elem[1], 45*M_PI/180.f, 0.001f) &&
       fTolerance(final.elem[2], 45*M_PI/180.f,0.001f)){
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
    printf("Test AABB Stacked Rotation: %d\n", testAABBStackedRotation());
    //printf("Test rotation identity matrix: %d\n", testRotationIdentityMatrix());
    //printf("Test x rotation: %d\n", testRotationX());
    //printf("Test y rotation: %d\n", testRotationY());
    //printf("Test z rotation: %d\n", testRotationZ());
    //printf("Test full rotation: %d\n", testFullRotation());
    printf("Test 4x4 * 4x4 matrix multiplication: %d\n", testMatrixMultiplication44_44());
    printf("Test 4x4 * 4x1 matrix multiplication: %d\n", testMatrixMultiplication44_41());
    printf("Test 4 by 4 identity matrix: %d\n", testIdentity44());
    printf("cool test: %d\n", coolTest());
}
