#include "include/BigBalls/physicsMathsCommon.h"

CollisionArrayContainer collisionArrayContainer_init() {
    CollisionArrayContainer cac;
    cac.numOfCollisions = 0;
    cac.collisionArray = NULL;
    return cac;
}

void collisionArrayContainer_free(CollisionArrayContainer* cac) {
    cac->numOfCollisions = 0;
    cac->collisionArray = NULL;
}

Collision collision_init() {
    Collision collision;
    collision.body1 = NULL;
    collision.body2 = NULL;
    collision.normal = PVec3_init();
    collision.penetration = 0.0f;
    return collision;
}
