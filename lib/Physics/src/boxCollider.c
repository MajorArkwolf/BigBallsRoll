#include "include/BigBalls/boxCollider.h"

void BoxCollider_init(BoxCollider *boxCollider){
    boxCollider->id = -1;
    boxCollider->xOffset = 0;
    boxCollider->yOffset = 0;
    boxCollider->zOffset = 0;
    boxCollider->xLen = 0;
    boxCollider->yLen = 0;
    boxCollider->zLen = 0;
}
