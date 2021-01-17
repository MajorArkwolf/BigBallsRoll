#pragma once

#include "include/BigBalls/collisionBody.h"

typedef struct CollisionBodyManager{
    CollisionBody **collisionBodies;
    size_t numCollisionBodies;
    int idCount;
} CollisionBodyManager;

void CollisionBodyManager_init(CollisionBodyManager *collisionBodyManager);

void CollisionBodyManager_free(CollisionBodyManager *collisionBodyManager);

void CollisionBodyManager_add(CollisionBodyManager *collisionBodyManager,
                              CollisionBody *collisionBody);

void CollisionBodyManager_rm(CollisionBodyManager *collisionBodyManager,
                             int id);