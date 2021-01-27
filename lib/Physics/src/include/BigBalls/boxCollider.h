#pragma once
#include <stdbool.h>

typedef struct BoxCollider{
    float xOffset;
    float yOffset;
    float zOffset;
    float xLen;
    float yLen;
    float zLen;
    float xRot;
    float yRot;
    float zRot;
} BoxCollider;

/**
 * Initialises a BoxCollider
 * @param boxCollider an instantiated BoxCollider
 */
void BoxCollider_init(BoxCollider *boxCollider);
