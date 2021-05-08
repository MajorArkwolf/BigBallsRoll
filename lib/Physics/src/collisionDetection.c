#include "include/BigBalls/collisionDetection.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

PVec3 getAABBCenter(BoxCollider* a){
    PVec3 res = PVec3_init();

    res.data[0] = ((a->AABBx2 - a->AABBx1) / 2 ) + a->AABBx1;
    res.data[1] = ((a->AABBy2 - a->AABBy1) / 2 ) + a->AABBy1;
    res.data[2] = ((a->AABBz2 - a->AABBz1) / 2 ) + a->AABBz1;

    return res;
}

float getVectorMagnitude(PVec3* incV){
    return sqrtf(powf(incV->data[0], 2) + powf(incV->data[1], 2) + powf(incV->data[2], 2));
}

BoxColliderVerts getBoxVerts(CollisionBody* c, BoxCollider* b){
    // apply all transforms to boxcollider
    Matrix44 T1 = createRotMat(c->xRot, c->yRot,c-> zRot);

    BoxColliderVerts bcv = getBoxColliderVerts(b);
    BoxColliderVerts tbcv;

    // get all verts of transformed boxcollider
    for(size_t i = 0; i < 8; ++i){
        matrixMultiplication44_41(T1, bcv.verts[i]);
        tbcv.verts[i] = matrixMultiplication44_41(T1, bcv.verts[i]);
    }

    return tbcv;
}

void determineCollisionNormalBoxToSphere(BoxCollider *a, SphereCollider *b, PVec3* fn, float* pen) {
    // Calculate the extents of our box
    PVec3 aabbExtents;
    aabbExtents.data[0] = a->xLen / 2 ;
    aabbExtents.data[1] = a->yLen / 2 ;
    aabbExtents.data[2] = a->zLen / 2 ;
    // Calculate the centre point of our cube
    PVec3 aabbCentre;
    aabbCentre.data[0] = aabbExtents.data[0] + a->AABBx1;
    aabbCentre.data[1] = aabbExtents.data[1] + a->AABBy1;
    aabbCentre.data[2] = aabbExtents.data[2] + a->AABBz1;
    // Convert our sphere into a PVec for simplicity later
    PVec3 sphere;
    sphere.data[0] = b->xPostRot;
    sphere.data[1] = b->yPostRot;
    sphere.data[2] = b->zPostRot;

    // Get our normal from ->AB
    PVec3 mag = subtractPVec3(&sphere, &aabbCentre);
    PVec3 closest = PVec3_init();
    closest.data[0] = clamp(mag.data[0], -aabbExtents.data[0], aabbExtents.data[0]);
    closest.data[1] = clamp(mag.data[1], -aabbExtents.data[1], aabbExtents.data[1]);
    closest.data[2] = clamp(mag.data[2], -aabbExtents.data[2], aabbExtents.data[2]);

    bool isInside = false;

    if (PVec3Compare(&mag, &closest, 0.001f)) {
        isInside = true;
        if (fabsf(mag.data[0]) > fabsf(mag.data[1]) &&
            fabsf(mag.data[0]) > fabsf(mag.data[2])) {
            if (closest.data[0] > 0) {
                closest.data[0] = aabbExtents.data[0];
            } else {
                closest.data[0] = -aabbExtents.data[0];
            }
        } else if (fabsf(mag.data[1]) > fabsf(mag.data[2])) {
            // Clamp to closest extent
            if (closest.data[1] > 0) {
                closest.data[1] = aabbExtents.data[1];
            } else {
                closest.data[1] = -aabbExtents.data[1];
            }
        } else {
            if (closest.data[2] > 0) {
                closest.data[2] = aabbExtents.data[2];
            } else {
                closest.data[2] = -aabbExtents.data[2];
            }
        }
    }
    PVec3 normal = subtractPVec3(&mag, &closest);
    float dp = sqrtf(powf(normal.data[0], 2) + powf(normal.data[1], 2) + powf(normal.data[2], 2));
    *fn = PVec3NormaliseVec3(&normal);
    if (isInside) {
        fn->data[0] *= -1;
        fn->data[1] *= -1;
        fn->data[2] *= -1;
    }
    *pen = b->radius - dp;
}

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

bool testBoxColliderCollision(BoxCollider *a, BoxCollider *b, PVec3* fn, float* pen){
    assert(a != NULL && b != NULL);

    // alg from https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331
    PVec3 cenA = getAABBCenter(a);
    PVec3 cenB = getAABBCenter(b);
    PVec3 n = subtractPVec3(&cenB, &cenA);

    // calculate half-extents along x for each object
    float a_extent = (a->AABBx2 - a->AABBx1) / 2;
    float b_extent = (b->AABBx2 - b->AABBx1) / 2;

    // calculate x overlap
    float x_overlap = a_extent + b_extent - fabsf(n.data[0]);

    // SAT test on X axis
    if(x_overlap > 0){
        // calculate half-extents along y for each object
        a_extent = (a->AABBy2 - a->AABBy1) / 2;
        b_extent = (b->AABBy2 - b->AABBy1) / 2;

        // calculate y overlap
        float y_overlap = a_extent + b_extent - fabsf(n.data[1]);

        if(y_overlap > 0){
            // calculate half-extents along z for each object
            a_extent = (a->AABBz2 - a->AABBz1) / 2;
            b_extent = (b->AABBz2 - b->AABBz1) / 2;

            // calculate z overlap
            float z_overlap = a_extent + b_extent - fabsf(n.data[2]);

            if(z_overlap > 0){
                // determine axis of most pen
                float min = getMin(x_overlap, getMin(y_overlap, z_overlap));
                if(min == x_overlap){
                    if(n.data[0] < 0){
                        fn->data[0] = -1;
                        fn->data[1] = 0;
                        fn->data[2] = 0;
                    }
                    else{
                        fn->data[0] = 1;
                        fn->data[1] = 0;
                        fn->data[2] = 0;
                    }
                    *pen = x_overlap;
                }
                else if (min == y_overlap){
                    if(n.data[1] < 0){
                        fn->data[0] = 0;
                        fn->data[1] = -1;
                        fn->data[2] = 0;
                    }
                    else{
                        fn->data[0] = 0;
                        fn->data[1] = 1;
                        fn->data[2] = 0;
                    }
                    *pen = y_overlap;
                }
                else{
                    if(n.data[2] < 0){
                        fn->data[0] = 0;
                        fn->data[1] = 0;
                        fn->data[2] = -1;
                    }
                    else{
                        fn->data[0] = 0;
                        fn->data[1] = 0;
                        fn->data[2] = 1;
                    }
                    *pen = z_overlap;
                }
                return true;
            }
        }
    }
    return false;
}

bool testSphereColliderCollision(SphereCollider *a, SphereCollider *b, PVec3* fn, float* pen){
    assert(a != NULL && b != NULL);

    // separated for clarity
    if(a->xPostRot + a->radius >= b->xPostRot - b->radius && // a within b
         a->xPostRot - a->radius <= b->xPostRot + b->radius) {
        if(a->yPostRot + a->radius >= b->yPostRot - b->radius &&
            a->yPostRot - a->radius <= b->yPostRot + b->radius){
            if(a->zPostRot + a->radius >= b->zPostRot - b->radius &&
               a->zPostRot - a->radius <= b->zPostRot + b->radius){

                Matrix41 cenA;
                cenA.elem[0] = a->xPostRot;
                cenA.elem[1] = a->yPostRot;
                cenA.elem[2] = a->zPostRot;
                Matrix41 cenB;
                cenB.elem[0] = a->xPostRot;
                cenB.elem[1] = a->yPostRot;
                cenB.elem[2] = a->zPostRot;

                *pen = a->radius + b->radius - distance(cenB, cenA);

                fn->data[0] = cenB.elem[0] - cenA.elem[0];
                fn->data[1] = cenB.elem[1] - cenA.elem[1];
                fn->data[2] = cenB.elem[2] - cenA.elem[2];

                return true;
            }
        }
    }
    return false;
}

bool testBoxSphereCollision(BoxCollider *a, SphereCollider *b, PVec3* fn, float* pen){
    float x = getMax(a->AABBx1, getMin(b->xPostRot, a->AABBx2));
    float y = getMax(a->AABBy1, getMin(b->yPostRot, a->AABBy2));
    float z = getMax(a->AABBz1, getMin(b->zPostRot, a->AABBz2));
    float distance_between = sqrtf(powf(x - b->xPostRot, 2) +
                             powf(y - b->yPostRot, 2) +
                             powf(z - b->zPostRot, 2));
    if (distance_between < b->radius) {
        determineCollisionNormalBoxToSphere(a, b, fn, pen);
        return true;
    } else {
        return false;
    }
}

bool testNarrowPhaseCollision(CollisionBody* a, CollisionBody* b, PVec3* fn, float* pen){
    assert(a != NULL && b != NULL);

    // compare all box colliders with each other
    for(size_t i = 0; i < a->numOfBoxColliders; ++i){
        for(size_t j = 0; j < b->numOfBoxColliders; ++j){
            if(testBoxColliderCollision(a->BoxColliders[i], b->BoxColliders[j], fn, pen)){
                return true;
            }
        }
    }

    // compare all sphere colliders with each other
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(testSphereColliderCollision(a->SphereColliders[i], b->SphereColliders[j], fn, pen)){
                return true;
            }
        }
    }

    // compare boxes of a with spheres of b
    for(size_t i = 0; i < a->numOfBoxColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(testBoxSphereCollision(a->BoxColliders[i], b->SphereColliders[j], fn, pen)){
                return true;
            }
        }
    }

    // compare spheres of a with boxes of b
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfBoxColliders; ++j){
            if(testBoxSphereCollision(b->BoxColliders[j], a->SphereColliders[i], fn, pen)){
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
                PVec3 fn = PVec3_init();
                float pen = 0.0f;
                if(testNarrowPhaseCollision(physicsWorld->collisionBodies[i], physicsWorld->collisionBodies[j], &fn, &pen)){
                    if(cac->collisionArray == NULL){
                        if (cac->numOfCollisions == 0) {
                            cac->collisionArray = calloc(1, sizeof(Collision));
                            cac->collisionsAlloced = 1;
                        } else {
                            assert(false);
                        }
                    }
                    else if(cac->collisionsAlloced < cac->numOfCollisions + 1){
                        cac->collisionArray = realloc(cac->collisionArray, sizeof(Collision) * (cac->collisionsAlloced * 2));
                        cac->collisionsAlloced *= 2;
                    }
                    cac->collisionArray[cac->numOfCollisions].body1 = physicsWorld->collisionBodies[i];
                    cac->collisionArray[cac->numOfCollisions].body2 = physicsWorld->collisionBodies[j];
                    cac->collisionArray[cac->numOfCollisions].normal = fn;
                    cac->collisionArray[cac->numOfCollisions].penetration = pen;
                    ++cac->numOfCollisions;
                }
            }
        }
    }
}
