#include "include/BigBalls/collisionDetection.h"
#include <assert.h>
#include <stdio.h>

bool testAABBCollision(CollisionBody *a, CollisionBody *b){
    assert(a != NULL && b != NULL);
    // the min and max points of each CollisionBody, which will be used to determine if the two AABB's of the CollisionBodies are intersecting (colliding)
    float x1min, x1max, y1min, y1max, z1min, z1max, x2min, x2max, y2min, y2max, z2min, z2max;

    // determine which coordinate is larger than the other, for each coordinate pair of each CollisionBody
    minMax(a->AABBx1, a->AABBx2, &x1min, &x1max);
    minMax(a->AABBy1, a->AABBy2, &y1min, &y1max);
    minMax(a->AABBz1, a->AABBz2, &z1min, &z1max);

    minMax(b->AABBx1, b->AABBx2, &x2min, &x2max);
    minMax(b->AABBy1, b->AABBy2, &y2min, &y2max);
    minMax(b->AABBz1, b->AABBz2, &z2min, &z2max);

    return (x1min <= x2max && x1max >= x2min) &&
           (y1min <= y2max && y1max >= y2min) &&
           (z1min <= z2max && z1max >= z2min);
}

void collisionsDetection(PhysicsWorld* physicsWorld, CollisionArrayContainer *cac){
    assert(physicsWorld != NULL);
    // TODO: ideally shouldn't check every body against each other - spacial partitioning method ideal
    // broad phase
    for(size_t i = 0; i < physicsWorld->numCollisionBodies; ++i){
        for(size_t j = i + 1; j < physicsWorld->numCollisionBodies; ++j){ // only checks collisions of different CollisionBodies, where j is always greater than i
            if(physicsWorld->collisionBodies[i]->isStatic == true && physicsWorld->collisionBodies[j]->isStatic == true) {
                continue;
            }
            // (avoids repeat inverse tests eg. checking 1-0 AND 0-1 would be redundant and inefficient)
            if(testAABBCollision(physicsWorld->collisionBodies[i], physicsWorld->collisionBodies[j])) {
                // broad phase collision detected
                //printf("Objects %d and %d are colliding!\n", (int)i ,(int)j);
                ++cac->numOfCollisions;
                // TODO: narrow phase
                // TODO: resolve collision
            }
        }
    }
}
