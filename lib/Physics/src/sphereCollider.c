#include "include/BigBalls/sphereCollider.h"

void SphereCollider_init(SphereCollider *sphereCollider){
    sphereCollider->id = -1;
    sphereCollider->xOffset = 0;
    sphereCollider->yOffset = 0;
    sphereCollider->zOffset = 0;
    sphereCollider->radius = 0;
}