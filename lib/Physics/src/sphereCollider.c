#include "include/BigBalls/sphereCollider.h"
#include <stdlib.h>
#include <assert.h>

void SphereCollider_init(SphereCollider *sphereCollider){
    assert(sphereCollider != NULL);
    sphereCollider->xOffset = 0.0f;
    sphereCollider->yOffset = 0.0f;
    sphereCollider->zOffset = 0.0f;
    sphereCollider->xPostRot = 0.0f;
    sphereCollider->yPostRot = 0.0f;
    sphereCollider->zPostRot = 0.0f;
    sphereCollider->radius = 0.0f;
}

void SphereCollider_updatePostRotPos(SphereCollider *sphereCollider,
                                     float x,
                                     float y,
                                     float z){
    sphereCollider->xPostRot = x;
    sphereCollider->yPostRot = y;
    sphereCollider->zPostRot = z;
}
