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
    float xAbsPos; // Absolute position of BoxCollider (after local and CollisionBody rotation)
    float yAbsPos;
    float zAbsPos;
    float xAbsLen;
    float yAbsLen;
    float zAbsLen;
} BoxCollider;

/**
 * Initialises a BoxCollider
 * @param boxCollider an instantiated BoxCollider
 */
void BoxCollider_init(BoxCollider *boxCollider);
