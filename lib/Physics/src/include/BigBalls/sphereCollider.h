#pragma once
#include <stdbool.h>

typedef struct SphereCollider{
    int id;
    float xOffset;
    float yOffset;
    float zOffset;
    float radius;
} SphereCollider;

/**
 * Initialises a SphereCollider
 * @param sphereCollider an instantiated SphereCollider
 * @return
 */
void SphereCollider_init(SphereCollider *sphereCollider);
