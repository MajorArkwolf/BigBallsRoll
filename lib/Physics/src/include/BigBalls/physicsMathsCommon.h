#pragma once
#include "collisionBody.h"
#include "mathsCommon.h"

typedef struct Collision {
    CollisionBody *body1;
    CollisionBody *body2;
    float penetration;
    PVec3 normal;
} Collision;

typedef struct CollisionArrayContainer {
    Collision *collisionArray;
    size_t numOfCollisions;
}CollisionArrayContainer;

/**
 * Creates a safe CollisionArrayContainer for use.
 * @return returns an empty container ready for use.
 */
CollisionArrayContainer collisionArrayContainer_init();

/**
 * Frees memory and sets number of collisions to zero
 * @param cac the container to free
 */
void collisionArrayContainer_free(CollisionArrayContainer* cac);

/**
 * Returns a ready to use container for Collision
 * @return collision object that contains the information needed for resolution
 */
Collision collision_init();