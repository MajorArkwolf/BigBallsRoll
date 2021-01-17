#pragma once

#include "colliderManager.h"

typedef struct CollisionBody{
    ColliderManager* colliderManager;
    int id;
} CollisionBody;

/**
 * Initialise collisionBody
 * @param collisionBody
 */
void CollisionBody_init(CollisionBody *collisionBody);

/**
 * Free collisionBody
 * @param collisionBody
 */
void CollisionBody_free(CollisionBody *collisionBody);