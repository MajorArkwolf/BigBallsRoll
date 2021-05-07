#pragma once
#include <stdbool.h>

typedef struct BoxCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float xLen;
    float yLen;
    float zLen;
    float AABBx1;
    float AABBy1;
    float AABBz1;
    float AABBx2;
    float AABBy2;
    float AABBz2;
} BoxCollider;

/**
 * Initialises a BoxCollider
 * @param boxCollider an instantiated BoxCollider
 */
void BoxCollider_init(BoxCollider *boxCollider);

void BoxCollider_updateAABB(BoxCollider *boxCollider,
                            float x1,
                            float y1,
                            float z1,
                            float x2,
                            float y2,
                            float z2);
