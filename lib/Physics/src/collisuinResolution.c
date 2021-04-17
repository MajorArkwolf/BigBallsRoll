#include "include/BigBalls/collisionResolution.h"

void PositionalCorrection( Collision* collision )
{
    const float percent = 0.2f // usually 20% to 80%
    const float slop = 0.01f // usually 0.01 to 0.1
    Vec2 correction = max( penetration - k_slop, 0.0f ) / (A.inv_mass + B.inv_mass)) * percent * n
    A.position -= A.inv_mass * correction
    B.position += B.inv_mass * correction
}

void ResolveCollision( Collision* collision )
{
    // Calculate relative velocity
    PVec3 rv = subtractPVec3(&collision->body1->velocity, &collision->body1->velocity);

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = DotProductPVec3(&rv, &collision->normal);
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
    PVec3 impulse = j * normal
    A.velocity -= 1 / A.mass * impulse
    B.velocity += 1 / B.mass * impulse
}