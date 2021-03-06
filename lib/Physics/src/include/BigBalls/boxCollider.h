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
    float xFinalPos; // Absolute position of BoxCollider (after local and CollisionBody rotation)
    float yFinalPos;
    float zFinalPos;
    float xFinalLen;
    float yFinalLen;
    float zFinalLen;
} BoxCollider;

/**
 * Initialises a BoxCollider
 * @param boxCollider an instantiated BoxCollider
 */
void BoxCollider_init(BoxCollider *boxCollider);
