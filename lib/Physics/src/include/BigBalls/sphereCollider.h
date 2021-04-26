#pragma once
#include <stdbool.h>

typedef struct SphereCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float radius;
    float xPostRot;
    float yPostRot;
    float zPostRot;
} SphereCollider;

/**
 * Initialises a SphereCollider
 * @param sphereCollider an instantiated SphereCollider
 */
void SphereCollider_init(SphereCollider *sphereCollider);

void SphereCollider_updatePostRotPos(SphereCollider *sphereCollider,
                                     float x,
                                     float y,
                                     float z);
