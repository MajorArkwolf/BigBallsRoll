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

PVec3 getSphereCentre(CollisionBody* c, SphereCollider* s){
    // apply all transforms to boxcollider
    Matrix44 T1 = createRotMat(c->xRot, c->yRot,c-> zRot);
    Matrix41 cPos = {c->xPos, c->yPos, c->zPos};
    Matrix41 newCPos = matrixMultiplication44_41(T1, cPos);

    PVec3 newSPos;
    newSPos.data[0] = newCPos.elem[0] + s->xOffset;
    newSPos.data[1] = newCPos.elem[1] + s->yOffset;
    newSPos.data[2] = newCPos.elem[2] + s->zOffset;

    return newSPos;
}

void determineCollisionDetails_BB(CollisionBody* ca, BoxCollider* ba, CollisionBody* cb, BoxCollider* bb, float* pen, PVec3* norm){
    BoxColliderVerts bcv1 = getBoxVerts(ca, ba);
    BoxColliderVerts bcv2 = getBoxVerts(cb, bb);

    // find closest two verts
    float cD = FLT_MAX;
    Matrix41 ca1, ca2, cb1;
    for(size_t i = 0; i < 8; ++i){
        for(size_t j = 0; j < 8; ++j){
            float d = distance(bcv1.verts[i], bcv2.verts[j]);
            if(d < cD){ // TODO: wont work if first is closest
                ca2 = ca1; // shuffle the last closest down
                ca1 = bcv1.verts[i];
                cb1 = bcv2.verts[j];
                cD = d;
            }
        }
    }

    // determine collision norm (difference of two closest vertices to other object)
    norm->data[0] = ca2.elem[0] - ca1.elem[0];
    norm->data[1] = ca2.elem[1] - ca1.elem[1];
    norm->data[2] = ca2.elem[2] - ca1.elem[2];

    // determine penetration
    float minV = FLT_MAX;
    checkMin(ca1.elem[0] - cb1.elem[0], &minV);
    checkMin(ca1.elem[1] - cb1.elem[1], &minV);
    checkMin(ca1.elem[2] - cb1.elem[2], &minV);
    *pen = minV;
}

void determineCollisionDetails_BS(CollisionBody* ca, BoxCollider* ba, CollisionBody* cb, SphereCollider* sb, float* pen, PVec3* norm){
    return;
}

void determineCollisionDetails_SS(CollisionBody* ca, SphereCollider* sa, CollisionBody* cb, SphereCollider* sb, float* pen, PVec3* norm){
    PVec3 cena = getSphereCentre(ca, sa);
    PVec3 cenb = getSphereCentre(cb, sb);

    Matrix41 mcena;
    mcena.elem[0] = cena.data[0];
    mcena.elem[1] = cena.data[1];
    mcena.elem[2] = cena.data[2];
    Matrix41 mcenb;
    mcenb.elem[0] = cenb.data[0];
    mcenb.elem[1] = cenb.data[1];
    mcenb.elem[2] = cenb.data[2];

    *pen = sa->radius + sb->radius - distance(mcena, mcenb);

    norm->data[0] = cenb.data[0] - cena.data[0];
    norm->data[1] = cenb.data[1] - cena.data[1];
    norm->data[2] = cenb.data[2] - cena.data[2];
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
    float dp = dotProductPVec3(&mag, &closest);
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
                determineCollisionDetails_BB(a, a->BoxColliders[i], b, b->BoxColliders[j], pen, fn);
                return true;
            }
        }
    }

    // compare all sphere colliders with each other
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(testSphereColliderCollision(a->SphereColliders[i], b->SphereColliders[j], fn, pen)){
                determineCollisionDetails_SS(a, a->SphereColliders[i], b, b->SphereColliders[j], pen, fn);
                return true;
            }
        }
    }

    // compare boxes of a with spheres of b
    for(size_t i = 0; i < a->numOfBoxColliders; ++i){
        for(size_t j = 0; j < b->numOfSphereColliders; ++j){
            if(testBoxSphereCollision(a->BoxColliders[i], b->SphereColliders[j], fn, pen)){
                determineCollisionDetails_BS(a, a->BoxColliders[i], b, b->SphereColliders[j], pen, fn);
                return true;
            }
        }
    }

    // compare spheres of a with boxes of b
    for(size_t i = 0; i < a->numOfSphereColliders; ++i){
        for(size_t j = 0; j < b->numOfBoxColliders; ++j){
            if(testBoxSphereCollision(b->BoxColliders[j], a->SphereColliders[i], fn, pen)){
                determineCollisionDetails_BS(b, b->BoxColliders[j], a, a->SphereColliders[i], pen, fn);
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
