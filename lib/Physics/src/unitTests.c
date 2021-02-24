#include "include/BigBalls/unitTests.h"
#include "include/BigBalls/physicsEngine.h"
#include <stdbool.h>
#include <stdio.h>
#include "include/BigBalls/physicsWorld.h"

// test collision between idential objects
bool test1(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xOffset = 0.f;
    collider1->yOffset = 0.f;
    collider1->zOffset = 0.f;
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;

    CollisionBody_addBoxCollider(collisionBody1, collider1);
    CollisionBody_setPos(collisionBody1, 0.f, 0.f, 0.f);
    CollisionBody_setRot(collisionBody1, 0.f, 90.f, 0.f);

    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider1->xOffset = 0.f;
    collider1->yOffset = 0.f;
    collider1->zOffset = 0.f;
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;

    CollisionBody_addBoxCollider(collisionBody2, collider2);
    CollisionBody_setPos(collisionBody2, 0.f, 0.f, 0.f);
    CollisionBody_setRot(collisionBody2, 0.f, 90.f, 0.f);

    for(int i = 0; i < 11; ++i){
        CollisionBody_translate(collisionBody2, 1, 0, 0);
        if(testAABBCollision(collisionBody1, collisionBody2)){
            printf("%d\n", i);
        }
    }
    return testAABBCollision(collisionBody1, collisionBody2);
}

// test collision between rotated and non-rotated objects
bool test2(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xOffset = 0.f;
    collider1->yOffset = 0.f;
    collider1->zOffset = 0.f;
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;

    CollisionBody_addBoxCollider(collisionBody1, collider1);
    CollisionBody_setPos(collisionBody1, 0.f, 0.f, 0.f);
    CollisionBody_setRot(collisionBody1, 0.f, 0.f, 0.f);

    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider2->xOffset = 0.f;
    collider2->yOffset = 0.f;
    collider2->zOffset = 0.f;
    collider2->xLen = 10.f;
    collider2->yLen = 1.f;
    collider2->zLen = 1.f;

    CollisionBody_addBoxCollider(collisionBody2, collider2);
    CollisionBody_setPos(collisionBody2, 0.f, 0.f, 0.f);
    CollisionBody_setRot(collisionBody2, 90.f, 0.f, 0.f);

    for(int i = 0; i < 11; ++i){
        CollisionBody_translate(collisionBody2, 0, 0, 1);
        if(testAABBCollision(collisionBody1, collisionBody2)){
            printf("%d\n", i);
        }
    }
    return testAABBCollision(collisionBody1, collisionBody2);
}

void startTests(){
    printf("0 = pass, 1 = fail\n");
    printf("Test 1: %d\n", test1());
    printf("Test 2: %d\n", test2());
}

