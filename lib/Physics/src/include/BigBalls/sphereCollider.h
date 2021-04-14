#pragma once
#include <stdbool.h>

typedef struct SphereCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float radius;
} SphereCollider;

/**
 * Initialises a SphereCollider
 * @param sphereCollider an instantiated SphereCollider
 */
void SphereCollider_init(SphereCollider *sphereCollider);
