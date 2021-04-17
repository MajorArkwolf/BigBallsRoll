#include "include/BigBalls/collisionResolution.h"
#include "include/BigBalls/mathsCommon.h"

void positionalCorrection( Collision* collision )
{
//    const float percent = 0.2f // usually 20% to 80%
//    const float slop = 0.01f // usually 0.01 to 0.1
//    Vec2 correction = max( penetration - k_slop, 0.0f ) / (A.inv_mass + B.inv_mass)) * percent * n
//    A.position -= A.inv_mass * correction
//    B.position += B.inv_mass * correction
}

void resolveCollision( Collision* collision )
{
    // Calculate relative velocity
    PVec3 rv = subtractPVec3(&collision->body1->velocity, &collision->body1->velocity);

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = dotProductPVec3(&rv, &collision->normal);
    // Do not resolve if velocities are separating
    if(velAlongNormal > 0) {
        return;
    }

    // Calculate restitution
    float e = min( collision->body1->restitution, collision->body2->restitution);

    // Calculate impulse scalar
    float j = (-1.0f *(1.0f + e)) * velAlongNormal;
    j /= 1 / collision->body1->mass + 1 / collision->body2->mass;

    // Apply impulse
    PVec3 impulse = PVec3MultiplyScalar(&collision->normal, j);

    //TODO: Static objects will most likely need to be accounted for here.
    PVec3 aDiff = PVec3MultiplyScalar(&impulse, (1 / collision->body1->mass));
    collision->body1->velocity = subtractPVec3(&collision->body1->velocity , &aDiff);
    PVec3 bDiff = PVec3MultiplyScalar(&impulse, (1 / collision->body2->mass));
    collision->body2->velocity = addPVec3(&collision->body2->velocity , &bDiff);
}

void collisionResolution(Collision* collisionArray, size_t numOfCollisions) {
    if (collisionArray == NULL || numOfCollisions == 0) {
        return;
    }
    for (size_t i = 0; i < numOfCollisions; ++i) {
        resolveCollision(&collisionArray[i]);
    }
}