#include "include/BigBalls/boxCollider.h"
#include <stdlib.h>
#include <assert.h>

void BoxCollider_init(BoxCollider *boxCollider){
    assert(boxCollider != NULL);
    boxCollider->xOffset = 0;
    boxCollider->yOffset = 0;
    boxCollider->zOffset = 0;
    boxCollider->xLen = 0;
    boxCollider->yLen = 0;
    boxCollider->zLen = 0;
}

void BoxCollider_updateAABB(BoxCollider *boxCollider,
                            float x1,
                            float y1,
                            float z1,
                            float x2,
                            float y2,
                            float z2){
    assert(boxCollider != NULL); // ensure that one collider exists before processing
    boxCollider->AABBx1 = x1;
    boxCollider->AABBy1 = y1;
    boxCollider->AABBz1 = z1;
    boxCollider->AABBx2 = x2;
    boxCollider->AABBy2 = y2;
    boxCollider->AABBz2 = z2;
}
