#include "include/BigBalls/physicsMathsCommon.h"
#include <math.h>

CollisionArrayContainer collisionArrayContainer_init() {
    CollisionArrayContainer cac;
    cac.numOfCollisions = 0;
    cac.collisionArray = NULL;
    return cac;
}

void collisionArrayContainer_free(CollisionArrayContainer* cac) {
    cac->numOfCollisions = 0;
    free(cac->collisionArray);
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

BoxColliderVerts getBoxColliderVerts(BoxCollider* boxCollider){
    BoxColliderVerts res;
    Matrix41 vert1 = {boxCollider->xOffset,
                      boxCollider->yOffset,
                      boxCollider->zOffset,
                      0}; // point to be transformed
    Matrix41 vert2 = {boxCollider->xOffset + boxCollider->xLen,
                      boxCollider->yOffset,
                      boxCollider->zOffset,
                      0}; // point to be transformed
    Matrix41 vert3 = {boxCollider->xOffset,
                      boxCollider->yOffset + boxCollider->yLen,
                      boxCollider->zOffset,
                      0}; // point to be transformed
    Matrix41 vert4 = {boxCollider->xOffset,
                      boxCollider->yOffset,
                      boxCollider->zOffset + boxCollider->zLen,
                      0}; // point to be transformed
    Matrix41 vert5 = {boxCollider->xOffset + boxCollider->xLen,
                      boxCollider->yOffset + boxCollider->yLen,
                      boxCollider->zOffset,
                      0}; // point to be transformed
    Matrix41 vert6 = {boxCollider->xOffset + boxCollider->xLen,
                      boxCollider->yOffset,
                      boxCollider->zOffset + boxCollider->zLen,
                      0}; // point to be transformed
    Matrix41 vert7 = {boxCollider->xOffset,
                      boxCollider->yOffset + boxCollider->yLen,
                      boxCollider->zOffset + boxCollider->zLen,
                      0}; // point to be transformed
    Matrix41 vert8 = {boxCollider->xOffset + boxCollider->xLen,
                      boxCollider->yOffset + boxCollider->yLen,
                      boxCollider->zOffset + boxCollider->zLen,
                      0}; // point to be transformed
    res.verts[0] = vert1;
    res.verts[1] = vert2;
    res.verts[2] = vert3;
    res.verts[3] = vert4;
    res.verts[4] = vert5;
    res.verts[5] = vert6;
    res.verts[6] = vert7;
    res.verts[7] = vert8;
    return res;
}

float distance(Matrix41 a, Matrix41 b){
    return sqrtf(powf((b.elem[0] - a.elem[0]), 2) + powf((b.elem[1] - a.elem[1]), 2) + powf(b.elem[2] - a.elem[2], 2));
}
