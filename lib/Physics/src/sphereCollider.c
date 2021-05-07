#include "include/BigBalls/sphereCollider.h"
#include <stdlib.h>
#include <assert.h>

void SphereCollider_init(SphereCollider *sphereCollider){
    assert(sphereCollider != NULL);
    sphereCollider->xOffset = 0;
    sphereCollider->yOffset = 0;
    sphereCollider->zOffset = 0;
    sphereCollider->radius = 0;
}

void SphereCollider_updatePostRotPos(SphereCollider *sphereCollider,
                                     float x,
                                     float y,
                                     float z){
    sphereCollider->xPostRot = x;
    sphereCollider->yPostRot = y;
    sphereCollider->zPostRot = z;
}
