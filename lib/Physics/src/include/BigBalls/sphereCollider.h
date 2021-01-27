#pragma once
#include <stdbool.h>

typedef struct SphereCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float radius;
    float xRot;
    float yRot;
    float zRot;
} SphereCollider;

/**
 * Initialises a SphereCollider
 * @param sphereCollider an instantiated SphereCollider
 * @return
 */
void SphereCollider_init(SphereCollider *sphereCollider);
