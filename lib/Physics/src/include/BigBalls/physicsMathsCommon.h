#pragma once
#include "collisionBody.h"
#include "mathsCommon.h"

typedef struct Collision {
    CollisionBody *body1;
    CollisionBody *body2;
    float penetration;
    PVec3 normal;
} Collision;

Collision collision_init();