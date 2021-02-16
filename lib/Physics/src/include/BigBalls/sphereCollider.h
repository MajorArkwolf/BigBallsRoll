#pragma once
#include <stdbool.h>

typedef struct SphereCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float xAbs; // absolute position of SphereCollider (after CollisionBody rotation)
    float yAbs;
    float zAbs;
    float radius;
} SphereCollider;

/**
 * Initialises a SphereCollider
 * @param sphereCollider an instantiated SphereCollider
 * @return
 */
void SphereCollider_init(SphereCollider *sphereCollider);
