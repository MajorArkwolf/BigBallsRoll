#include "include/BigBalls/physicsMathsCommon.h"

Collision collision_init() {
    Collision collision;
    collision.body1 = NULL;
    collision.body2 = NULL;
    collision.normal = PVec3_init();
    collision.penetration = 0.0f;
    return collision;
}