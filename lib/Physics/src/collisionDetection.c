#include "include/BigBalls/collisionDetection.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

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

    // the min and max points of each CollisionBody, which will be used to determine if the two AABB's of the CollisionBodies are intersecting (colliding)
    float x1min, x1max, y1min, y1max, z1min, z1max, x2min, x2max, y2min, y2max, z2min, z2max;

    // determine which coordinate is larger than the other, for each coordinate pair of each CollisionBody
    minMax(a->AABBx1, a->AABBx2, &x1min, &x1max);
    minMax(a->AABBy1, a->AABBy2, &y1min, &y1max);
    minMax(a->AABBz1, a->AABBz2, &z1min, &z1max);

    minMax(b->AABBx1, b->AABBx2, &x2min, &x2max);
    minMax(b->AABBy1, b->AABBy2, &y2min, &y2max);
    minMax(b->AABBz1, b->AABBz2, &z2min, &z2max);

    if((x1min <= x2max && x1max >= x2min) &&
        (y1min <= y2max && y1max >= y2min) &&
        (z1min <= z2max && z1max >= z2min)){

        // normal = vector BA
        PVec3 aCen = PVec3_init();
        aCen.data[0] = ((a->AABBx2 - a->AABBx1) / 2 ) + a->AABBx1;
        aCen.data[1] = ((a->AABBy2 - a->AABBy1) / 2 ) + a->AABBy1;
        aCen.data[2] = ((a->AABBz2 - a->AABBz1) / 2 ) + a->AABBz1;
        PVec3 bCen = PVec3_init();
        bCen.data[0] = ((b->AABBx2 - b->AABBx1) / 2 ) + b->AABBx1;
        bCen.data[1] = ((b->AABBy2 - b->AABBy1) / 2 ) + b->AABBy1;
        bCen.data[2] = ((b->AABBz2 - b->AABBz1) / 2 ) + b->AABBz1;
        PVec3 norm = subtractPVec3(&bCen, &aCen);

        *fn = PVec3NormaliseVec3(&norm);
        *pen = getMin(norm.data[0], getMin(norm.data[1], norm.data[2]));

        return true;
    }
    else{
        return false;
    }
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
    float distance_between = sqrtf(  (x - b->xPostRot) * (x - b->xPostRot) +
                             (y - b->yPostRot) * (y - b->yPostRot) +
                             (z - b->zPostRot) * (z - b->zPostRot));
    if (distance_between < b->radius) { // if a collision has occurred, gather collision details
        PVec3 aabbCentre = PVec3_init();
        aabbCentre.data[0] = ((a->AABBx2 - a->AABBx1) / 2 ) + a->AABBx1;
        aabbCentre.data[1] = ((a->AABBy2 - a->AABBy1) / 2 ) + a->AABBy1;
        aabbCentre.data[2] = ((a->AABBz2 - a->AABBz1) / 2 ) + a->AABBz1;
        PVec3 sphere;
        sphere.data[0] = b->xPostRot;
        sphere.data[1] = b->yPostRot;
        sphere.data[2] = b->zPostRot;
        PVec3 mag = subtractPVec3(&sphere, &aabbCentre);
        *fn = PVec3NormaliseVec3(&mag);
        *pen = b->radius - distance_between;
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
                        } else {
                            assert(false);
                        }
                    }
                    else{
                        cac->collisionArray = realloc(cac->collisionArray, sizeof(Collision) * (cac->numOfCollisions + 1));
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
