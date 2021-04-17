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

CollisionArrayContainer collisionArrayContainer_init();

void collisionArrayContainer_free(CollisionArrayContainer* cac);

Collision collision_init();