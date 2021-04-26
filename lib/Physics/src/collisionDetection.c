#include "include/BigBalls/collisionDetection.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

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

bool testBoxColliderCollision(BoxCollider *a, BoxCollider *b){
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

bool testSphereColliderCollision(SphereCollider *a, SphereCollider *b){
    assert(a != NULL && b != NULL);

    if(((a->xPostRot + a->radius >= b->xPostRot - b->radius && // a within b
         a->xPostRot - a->radius <= b->xPostRot + b->radius) &&
        (a->yPostRot + a->radius >= b->yPostRot - b->radius &&
         a->yPostRot - a->radius <= b->yPostRot + b->radius) &&
        a->zPostRot + a->radius >= b->zPostRot - b->radius &&
        a->zPostRot - a->radius <= b->zPostRot + b->radius) ||
       ((b->xPostRot + b->radius >= a->xPostRot - a->radius && // b within a
         b->xPostRot - b->radius <= a->xPostRot + a->radius) &&
        (b->yPostRot + b->radius >= a->yPostRot - a->radius &&
         b->yPostRot - b->radius <= a->yPostRot + a->radius) &&
        b->zPostRot + b->radius >= a->zPostRot - a->radius &&
        b->zPostRot - b->radius <= a->zPostRot + a->radius)){
        return true;
    }
    else{
        return false;
    }
}

bool testBoxSphereCollision(BoxCollider *a, SphereCollider *b){
    PVec3* norms = getAllBoxColliderNorms(*a);
    double sqRadius = pow(b->radius, 2);

    for(size_t i = 0; i < 6; ++i){ // for every face of box
        if(sqRadius - (norms[i].data[0] - b->xPostRot) >= 0 &&
           sqRadius - (norms[i].data[1] - b->yPostRot) >= 0 &&
           sqRadius - (norms[i].data[2] - b->zPostRot) >= 0){
            return true;
        }
    }
    return false;
}

bool testNarrowPhaseCollision(CollisionBody* a, CollisionBody* b){
    assert(a != NULL && b != NULL);

    // compare all box colliders with each other
    for(size_t i = 0; i < a->numOfBoxColliders; ++i){
        for(size_t j = 0; j < b->numOfBoxColliders; ++j){
            if(true){ // TODO: ensure no double collision detection
                testBoxColliderCollision(a->BoxColliders[i], b->BoxColliders[j]);
                return true;
            }
        }
    }

    // compare all sphere colliders with each other
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(true){ // TODO: ensure no double collision detection
                testSphereColliderCollision(a->SphereColliders[i], b->SphereColliders[j]);
                return true;
            }
        }
    }

    // compare boxes of a with spheres of b
    for(size_t i = 0; i < a->numOfBoxColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(true){// TODO: ensure no double collision detection
                testBoxSphereCollision(a->BoxColliders[i], b->SphereColliders[j]);
                return true;
            }
        }
    }

    // compare spheres of a with boxes of b
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfBoxColliders; ++j){
            if(true){// TODO: ensure no double collision detection
                testBoxSphereCollision(b->BoxColliders[j], a->SphereColliders[i]);
                return true;
            }
        }
    }

    return false;
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
                if(testNarrowPhaseCollision(physicsWorld->collisionBodies[i], physicsWorld->collisionBodies[j])){
                    if(cac->numOfCollisions == 0){
                        cac->collisionArray = calloc(1, sizeof(Collision));
                    }
                    else{
                        cac->collisionArray = realloc(cac->collisionArray, sizeof(Collision) * cac->numOfCollisions + 1);
                    }
                    *cac->collisionArray[cac->numOfCollisions].body1 = *physicsWorld->collisionBodies[i];
                    *cac->collisionArray[cac->numOfCollisions].body2 = *physicsWorld->collisionBodies[j];
                    // TODO: normal and penetration of collision
                    ++cac->numOfCollisions;
                }
            }
        }
    }
}
