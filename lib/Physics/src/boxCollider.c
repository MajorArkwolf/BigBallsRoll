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
    boxCollider->xRot = 0;
    boxCollider->yRot = 0;
    boxCollider->zRot = 0;
}
