#include <assert.h>
#include <stdbool.h>
#include "include/BigBalls/collisionBody.h"

void CollisionBody_init(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    collisionBody->numOfColliders = 0;
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->BoxColliders = NULL;
    collisionBody->SphereColliders = NULL;
    collisionBody->idCount = 0;
    collisionBody->id = -1;
    collisionBody->xPos = 0;
    collisionBody->yPos = 0;
    collisionBody->zPos = 0;
    collisionBody->xRot = 0;
    collisionBody->yRot = 0;
    collisionBody->zRot = 0;
    collisionBody->xVel = 0;
    collisionBody->yVel = 0;
    collisionBody->zVel = 0;
    collisionBody->AABBx1 = 0;
    collisionBody->AABBy1 = 0;
    collisionBody->AABBz1 = 0;
    collisionBody->AABBx2 = 0;
    collisionBody->AABBy2 = 0;
    collisionBody->AABBz2 = 0;
    collisionBody->mass = 0;
}

void CollisionBody_free(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    free(collisionBody->BoxColliders);
    free(collisionBody->SphereColliders);
    // Reset colliderManager values
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->numOfColliders = 0;
}

void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                  BoxCollider *boxCollider){
    assert(collisionBody != NULL);
    // Allocate new, larger array
    if(collisionBody->BoxColliders == NULL){
        collisionBody->BoxColliders = calloc(1, sizeof(BoxCollider));
    }
    else{
        collisionBody->BoxColliders = realloc(collisionBody->BoxColliders, sizeof(BoxCollider) * collisionBody->numOfBoxColliders + 1);
    }
    // Copy BoxCollider object into array
    collisionBody->BoxColliders[collisionBody->numOfBoxColliders] = boxCollider;
    ++collisionBody->numOfBoxColliders;
    ++collisionBody->numOfColliders;
    // recreate CollisionBody AABB
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_addSphereCollider(CollisionBody *collisionBody,
                                       SphereCollider *sphereCollider){
    assert(collisionBody != NULL);
    // Allocate new, larger array
    if(collisionBody->SphereColliders == NULL){
        collisionBody->SphereColliders = calloc(1, sizeof(SphereCollider));
    }
    else{
        collisionBody->SphereColliders = realloc(collisionBody->SphereColliders, sizeof(SphereCollider) * collisionBody->numOfSphereColliders + 1);
    }
    // Copy SphereCollider object into array
    collisionBody->SphereColliders[collisionBody->numOfSphereColliders] = sphereCollider;
    ++collisionBody->numOfSphereColliders;
    ++collisionBody->numOfColliders;
    // recreate CollisionBody AABB
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_translate(CollisionBody *collisionBody,
                             float xDist,
                             float yDist,
                             float zDist){
    assert(collisionBody != NULL && (xDist != 0 || yDist != 0 || zDist != 0));
    collisionBody->xPos += xDist; // update CollisionBody position
    collisionBody->yPos += yDist;
    collisionBody->zPos += zDist;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_rotate(CollisionBody *collisionBody,
                          float xRot,
                          float yRot,
                          float zRot){
    assert(collisionBody != NULL);
    collisionBody->xRot += xRot; // update CollisionBody rotation
    collisionBody->yRot += yRot;
    collisionBody->zRot += zRot;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_scale(CollisionBody *collisionBody,
                         float scaleFactor){
    assert(collisionBody != NULL && scaleFactor > 0); // decreased scale should be fractional, non-negative values
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->BoxColliders[i]->xLen *= scaleFactor;
        collisionBody->BoxColliders[i]->yLen *= scaleFactor;
        collisionBody->BoxColliders[i]->zLen *= scaleFactor;
    }
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        collisionBody->SphereColliders[i]->radius *= scaleFactor;// scale by the average of the three dimensions
    }
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_sleep(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    //TODO: implement
}

void CollisionBody_awake(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    // TODO: implement
}

void CollisionBody_stop(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    collisionBody->xVel = 0;
    collisionBody->yVel = 0;
    collisionBody->zVel = 0;
    collisionBody->forceX = 0;
    collisionBody->forceY = 0;
    collisionBody->forceZ = 0;
}

BoxColliderVerts getBoxColliderVerts(CollisionBody* collisionBody, BoxCollider* boxCollider){
    BoxColliderVerts res;
    Matrix41 vert1 = {collisionBody->xPos + boxCollider->xOffset,
                      collisionBody->yPos + boxCollider->yOffset,
                      collisionBody->zPos + boxCollider->zOffset,
                      1}; // point to be transformed
    Matrix41 vert2 = {collisionBody->xPos + boxCollider->xOffset + boxCollider->xLen,
                      collisionBody->yPos + boxCollider->yOffset,
                      collisionBody->zPos + boxCollider->zOffset,
                      1}; // point to be transformed
    Matrix41 vert3 = {collisionBody->xPos + boxCollider->xOffset,
                      collisionBody->yPos + boxCollider->yOffset + boxCollider->yLen,
                      collisionBody->zPos + boxCollider->zOffset,
                      1}; // point to be transformed
    Matrix41 vert4 = {collisionBody->xPos + boxCollider->xOffset,
                      collisionBody->yPos + boxCollider->yOffset,
                      collisionBody->zPos + boxCollider->zOffset + boxCollider->zLen,
                      1}; // point to be transformed
    Matrix41 vert5 = {collisionBody->xPos + boxCollider->xOffset + boxCollider->xLen,
                      collisionBody->yPos + boxCollider->yOffset + boxCollider->yLen,
                      collisionBody->zPos + boxCollider->zOffset,
                      1}; // point to be transformed
    Matrix41 vert6 = {collisionBody->xPos + boxCollider->xOffset + boxCollider->xLen,
                      collisionBody->yPos + boxCollider->yOffset,
                      collisionBody->zPos + boxCollider->zOffset + boxCollider->zLen,
                      1}; // point to be transformed
    Matrix41 vert7 = {collisionBody->xPos + boxCollider->xOffset,
                      collisionBody->yPos + boxCollider->yOffset + boxCollider->yLen,
                      collisionBody->zPos + boxCollider->zOffset + boxCollider->zLen,
                      1}; // point to be transformed
    Matrix41 vert8 = {collisionBody->xPos + boxCollider->xOffset + boxCollider->xLen,
                      collisionBody->yPos + boxCollider->yOffset + boxCollider->yLen,
                      collisionBody->zPos + boxCollider->zOffset + boxCollider->zLen,
                      1}; // point to be transformed
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

void CollisionBody_updateAABB(CollisionBody *collisionBody){
    assert(collisionBody != NULL && (collisionBody->numOfBoxColliders != 0 || collisionBody->numOfSphereColliders != 0)); // ensure that one collider exists before processing
    float greatestX, lowestX, greatestY, lowestY, greatestZ, lowestZ; // must be initialised to a point on a collider post-rotation
    bool varInit = false;

    // CollisionBody rotation matrix
    Matrix44 T1 = createRotMat(collisionBody->xRot,
                               collisionBody->yRot,
                               collisionBody->zRot);
    // get all BoxCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){ // for each collider
        // BoxCollider rotation matrix
        Matrix44 T2 = createRotMat(collisionBody->BoxColliders[i]->xRot,
                                   collisionBody->BoxColliders[i]->yRot,
                                   collisionBody->BoxColliders[i]->zRot);
        // Combined transformation matrix
        Matrix44 T3 = matrixMultiplication44_44(T2, T1);
        BoxColliderVerts verts = getBoxColliderVerts(collisionBody, collisionBody->BoxColliders[i]);
        for(size_t j = 0; j < 8; ++j){ // for each vertex of BoxCollider
            Matrix41 transformedVert = matrixMultiplication44_41(T3, verts.verts[j]);
            if(!varInit){ // init min/max values
                greatestX = lowestX = transformedVert.elem[0];
                greatestY = lowestY = transformedVert.elem[1];
                greatestZ = lowestZ = transformedVert.elem[2];
                varInit = true;
            }
            testPointMinMax(transformedVert.elem[0], 0, &lowestX, &greatestX);
            testPointMinMax(transformedVert.elem[1], 0, &lowestY, &greatestY);
            testPointMinMax(transformedVert.elem[2], 0, &lowestZ, &greatestZ);
        }
    }

    // get all SphereCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        // allocate position vector of SphereCollider
        Matrix41 pos = {collisionBody->xPos + collisionBody->SphereColliders[i]->xOffset,
                        collisionBody->yPos + collisionBody->SphereColliders[i]->yOffset,
                        collisionBody->zPos + collisionBody->SphereColliders[i]->zOffset};
        // apply CollisionBody rotation transformation matrix to position vector (a sphere cannot be rotated from the perspective of the physics engine)
        Matrix41 finalPos = matrixMultiplication44_41(T1, pos);
        // store resulting position in SphereCollider to be accessed later
        collisionBody->SphereColliders[i]->xFinalPos = finalPos.elem[0];
        collisionBody->SphereColliders[i]->yFinalPos = finalPos.elem[1];
        collisionBody->SphereColliders[i]->zFinalPos = finalPos.elem[2];

        if(!varInit){
            greatestX = lowestX = collisionBody->SphereColliders[i]->xFinalPos + collisionBody->SphereColliders[i]->radius;
            greatestY = lowestY = collisionBody->SphereColliders[i]->yFinalPos + collisionBody->SphereColliders[i]->radius;
            greatestZ = lowestZ = collisionBody->SphereColliders[i]->zFinalPos + collisionBody->SphereColliders[i]->radius;
            varInit = true;
        }
        // check for new min/max points
        testPointMinMax(collisionBody->SphereColliders[i]->xFinalPos, collisionBody->SphereColliders[i]->radius, &lowestX, &greatestX);
        // "len" extends in both directions from position
        testPointMinMax(collisionBody->SphereColliders[i]->xFinalPos, -1.f*collisionBody->SphereColliders[i]->radius, &lowestX, &greatestX);
        testPointMinMax(collisionBody->SphereColliders[i]->yFinalPos, collisionBody->SphereColliders[i]->radius, &lowestY, &greatestY);
        testPointMinMax(collisionBody->SphereColliders[i]->yFinalPos, -1.f*collisionBody->SphereColliders[i]->radius, &lowestY, &greatestY);
        testPointMinMax(collisionBody->SphereColliders[i]->zFinalPos, collisionBody->SphereColliders[i]->radius, &lowestZ, &greatestZ);
        testPointMinMax(collisionBody->SphereColliders[i]->zFinalPos, -1.f*collisionBody->SphereColliders[i]->radius, &lowestZ, &greatestZ);
    }

    // got dimensions for box, assign to CollisionBody
    collisionBody->AABBx1 = lowestX;
    collisionBody->AABBx2 = greatestX;
    collisionBody->AABBy1 = lowestY;
    collisionBody->AABBy2 = greatestY;
    collisionBody->AABBz1 = lowestZ;
    collisionBody->AABBz2 = greatestZ;
}

void PhysicsWorld_updateOOBB(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    // TODO: stub
}

void CollisionBody_setPos(CollisionBody *collisionBody,
                          float x,
                          float y,
                          float z){
    assert(collisionBody != NULL);
    collisionBody->xPos = x;
    collisionBody->yPos = y;
    collisionBody->zPos = z;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_setRot(CollisionBody *collisionBody,
                          float x,
                          float y,
                          float z){
    assert(collisionBody != NULL);
    collisionBody->xRot = x;
    collisionBody->yRot = y;
    collisionBody->zRot = z;
    CollisionBody_updateAABB(collisionBody);
}
