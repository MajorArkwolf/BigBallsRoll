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
