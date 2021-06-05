#include "include/BigBalls/collisionResolution.h"
#include "include/BigBalls/mathsCommon.h"
#include "math.h"

void positionalCorrection( Collision* collision, float inv_massA, float inv_massB )
{
    const float percent = 0.2f; // usually 20% to 80%
    const float slop = 0.01f;// usually 0.01 to 0.1
    float fixFactor = getMax(collision->penetration - slop, 0.0f) / ((inv_massA + inv_massB) / percent);
    PVec3 correction = PVec3MultiplyScalar(&collision->normal, fixFactor);
    collision->body1->xPos -= inv_massA * correction.data[0];
    collision->body1->yPos -= inv_massA * correction.data[1];
    collision->body1->zPos -= inv_massA * correction.data[2];

    collision->body2->xPos += inv_massB * correction.data[0];
    collision->body2->yPos += inv_massB * correction.data[1];
    collision->body2->zPos += inv_massB * correction.data[2];
}

void resolveCollision( Collision* collision )
{
    if (collision->body1->mass + collision->body2->mass == 0.0f) {
        return;
    }
    float inv_massA = 0.0f;
    float inv_massB = 0.0f;
    if (collision->body1->mass > 0.0f) {
        inv_massA = (1 / collision->body1->mass);
    }
    if (collision->body2->mass > 0.0f) {
        inv_massB = (1 / collision->body2->mass);
    }
    // Calculate relative velocity
    PVec3 rv = subtractPVec3(&collision->body2->velocity, &collision->body1->velocity);

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = dotProductPVec3(&rv, &collision->normal);
    // Do not resolve if velocities are separating
    if(velAlongNormal > 0) {
        return;
    }

    // Calculate restitution
    float e = fminf( collision->body1->restitution, collision->body2->restitution);

    // Calculate impulse scalar
    float j = (-1.0f *(1.0f + e)) * velAlongNormal;
    float invMassSum = inv_massA + inv_massB;
    j /= invMassSum;

    // Apply impulse
    PVec3 impulse = PVec3MultiplyScalar(&collision->normal, j);
    PVec3 aDiff = PVec3MultiplyScalar(&impulse, inv_massA);
    collision->body1->velocity = subtractPVec3(&collision->body1->velocity , &aDiff);
    PVec3 bDiff = PVec3MultiplyScalar(&impulse, inv_massB);
    collision->body2->velocity = addPVec3(&collision->body2->velocity , &bDiff);
    positionalCorrection(collision, inv_massA, inv_massB);
}

void collisionResolution(Collision* collisionArray, size_t numOfCollisions) {
    if (collisionArray == NULL || numOfCollisions == 0) {
        return;
    }
    for (size_t i = 0; i < numOfCollisions; ++i) {
        resolveCollision(&collisionArray[i]);
    }
}
