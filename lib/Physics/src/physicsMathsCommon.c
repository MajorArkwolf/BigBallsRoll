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

PVec3* getAllBoxColliderNorms(BoxCollider box){
    PVec3* res = calloc(6, sizeof(Matrix41));
    PVec3 vecA, vecB;

    // face 1
    vecA.data[0] = box.AABBx1;
    vecA.data[1] = box.AABBy1;
    vecA.data[2] = box.AABBz1;
    vecB.data[0] = box.AABBx1;
    vecB.data[1] = box.AABBy2;
    vecB.data[2] = box.AABBz2;
    res[0] = crossProductPVec3(&vecA, &vecB);

    // face 2
    vecA.data[0] = box.AABBx1;
    vecA.data[1] = box.AABBy1;
    vecA.data[2] = box.AABBz1;
    vecB.data[0] = box.AABBx2;
    vecB.data[1] = box.AABBy1;
    vecB.data[2] = box.AABBz2;
    res[1] = crossProductPVec3(&vecA, &vecB);

    // face 3
    vecA.data[0] = box.AABBx1;
    vecA.data[1] = box.AABBy1;
    vecA.data[2] = box.AABBz1;
    vecB.data[0] = box.AABBx2;
    vecB.data[1] = box.AABBy2;
    vecB.data[2] = box.AABBz1;
    res[2] = crossProductPVec3(&vecA, &vecB);

    // face 4
    vecA.data[0] = box.AABBx2;
    vecA.data[1] = box.AABBy1;
    vecA.data[2] = box.AABBz1;
    vecB.data[0] = box.AABBx2;
    vecB.data[1] = box.AABBy2;
    vecB.data[2] = box.AABBz2;
    res[3] = crossProductPVec3(&vecA, &vecB);

    // face 5
    vecA.data[0] = box.AABBx1;
    vecA.data[1] = box.AABBy2;
    vecA.data[2] = box.AABBz1;
    vecB.data[0] = box.AABBx2;
    vecB.data[1] = box.AABBy2;
    vecB.data[2] = box.AABBz2;
    res[4] = crossProductPVec3(&vecA, &vecB);

    // face 6
    vecA.data[0] = box.AABBx1;
    vecA.data[1] = box.AABBy1;
    vecA.data[2] = box.AABBz2;
    vecB.data[0] = box.AABBx2;
    vecB.data[1] = box.AABBy2;
    vecB.data[2] = box.AABBz2;
    res[5] = crossProductPVec3(&vecA, &vecB);

    return res;
}
