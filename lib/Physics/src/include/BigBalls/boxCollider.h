#pragma once
#include <stdbool.h>

typedef struct BoxCollider{
    int id;
    float xOffset;
    float yOffset;
    float zOffset;
    float xLen;
    float yLen;
    float zLen;
} BoxCollider;

/**
 * Initialises a BoxCollider
 * @param boxCollider an instantiated BoxCollider
 * @return
 */
void BoxCollider_init(BoxCollider *boxCollider);
