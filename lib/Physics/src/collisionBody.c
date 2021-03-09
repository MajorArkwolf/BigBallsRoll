#include "include/BigBalls/collisionBody.h"
#include "include/BigBalls/mathsCommon.h"
#include <assert.h>
#include <stdbool.h>

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

void CollisionBody_updateAABB(CollisionBody *collisionBody){
    assert(collisionBody != NULL && (collisionBody->numOfBoxColliders != 0 || collisionBody->numOfSphereColliders != 0)); // ensure that one collider exists before processing
    // declare local vars
    float greatestX, lowestX, greatestY, lowestY, greatestZ, lowestZ;
    bool varInit = false;

    // create CollisionBody rotation matrix
    float T1[3][3] = {{0}};
    rotationTransformationMatrix(collisionBody->xRot,
                                 collisionBody->yRot,
                                 collisionBody->zRot,
                                 T1);
    // get all BoxCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        // create BoxCollider rotation matrix
        float T2[3][3] = {{0}};
        rotationTransformationMatrix(collisionBody->BoxColliders[i]->xRot,
                                     collisionBody->BoxColliders[i]->yRot,
                                     collisionBody->BoxColliders[i]->zRot,
                                     T2);
        // create overall transformation matrix from CollisionBody and BoxCollider rotation matrices
        float T3[3][3] = {{0}};
        matrixMultiplication(3, 3, 3, 3, T1, T2, T3);
        // allocate position vector of BoxCollider
        float pos[3][1] = {{collisionBody->xPos}, {collisionBody->yPos}, {collisionBody->zPos}};
        // apply transformation matrix to position vector
        float final[3][1] = {{0}};
        matrixMultiplication(3, 3, 3, 1, T3, pos, final);
        // store resulting position in BoxCollider object so it can be accessed later
        collisionBody->BoxColliders[i]->xFinalPos = final[0][0];
        collisionBody->BoxColliders[i]->yFinalPos = final[1][0];
        collisionBody->BoxColliders[i]->zFinalPos = final[2][0];
        // do trig to find out new extents
        // allocate second position vector of collider
        float len[3][1] = {{collisionBody->BoxColliders[i]->xFinalPos + collisionBody->BoxColliders[i]->xLen}, {collisionBody->BoxColliders[i]->yFinalPos +collisionBody->BoxColliders[i]->yLen}, {collisionBody->BoxColliders[i]->zFinalPos +collisionBody->BoxColliders[i]->zLen}};
        // apply transformation matrix to position vector
        float finalLen[3][1] = {{0}};
        matrixMultiplication(3, 3, 3, 1, T3, len, finalLen);
        // convert back from point to an extension of position
        collisionBody->BoxColliders[i]->xFinalLen = finalLen[0][0] - collisionBody->BoxColliders[i]->xFinalPos;
        collisionBody->BoxColliders[i]->yFinalLen = finalLen[1][0] - collisionBody->BoxColliders[i]->yFinalPos;
        collisionBody->BoxColliders[i]->zFinalLen = finalLen[2][0] - collisionBody->BoxColliders[i]->zFinalPos;

        // check for new min/max points
        if(!varInit){
            if(collisionBody->BoxColliders[0]->xFinalLen > 0){
                greatestX = collisionBody->BoxColliders[0]->xFinalPos + collisionBody->BoxColliders[0]->xFinalLen;
                lowestX = collisionBody->BoxColliders[0]->xFinalPos;
            }
            else{
                greatestX = collisionBody->BoxColliders[0]->xFinalPos;
                lowestX = collisionBody->BoxColliders[0]->xFinalPos + collisionBody->BoxColliders[0]->xFinalLen;
            }
            if(collisionBody->BoxColliders[0]->yFinalLen > 0){
                greatestY = collisionBody->BoxColliders[0]->yFinalPos + collisionBody->BoxColliders[0]->yFinalLen;
                lowestY = collisionBody->BoxColliders[0]->yFinalPos;
            }
            else{
                greatestY = collisionBody->BoxColliders[0]->yFinalPos;
                lowestY = collisionBody->BoxColliders[0]->yFinalPos + collisionBody->BoxColliders[0]->yFinalLen;
            }
            if(collisionBody->BoxColliders[0]->zFinalLen > 0){
                greatestZ = collisionBody->BoxColliders[0]->zFinalPos + collisionBody->BoxColliders[0]->zFinalLen;
                lowestZ = collisionBody->BoxColliders[0]->zFinalPos;
            }
            else{
                greatestZ = collisionBody->BoxColliders[0]->zFinalPos;
                lowestZ = collisionBody->BoxColliders[0]->zFinalPos + collisionBody->BoxColliders[0]->zFinalLen;
            }
            varInit = true;
        }
        testPointMinMax(collisionBody->BoxColliders[i]->xFinalPos, collisionBody->BoxColliders[i]->xFinalLen, &lowestX, &greatestX);
        testPointMinMax(collisionBody->BoxColliders[i]->yFinalPos, collisionBody->BoxColliders[i]->yFinalLen, &lowestY, &greatestY);
        testPointMinMax(collisionBody->BoxColliders[i]->zFinalPos, collisionBody->BoxColliders[i]->zFinalLen, &lowestZ, &greatestZ);
    }

    // get all SphereCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        // allocate position vector of SphereCollider
        float pos[3][1] = {{collisionBody->xPos}, {collisionBody->yPos}, {collisionBody->zPos}};
        // apply CollisionBody rotation transformation matrix to position vector (a sphere cannot be rotated from the perspective of the physics engine)
        float final[3][1] = {{0}, {0}, {0}};
        matrixMultiplication(3, 3, 3, 1, T1, pos, final);
        // store resulting position in SphereCollider to be accessed later
        collisionBody->SphereColliders[i]->xFinalPos = final[0][0];
        collisionBody->SphereColliders[i]->yFinalPos = final[1][0];
        collisionBody->SphereColliders[i]->zFinalPos = final[2][0];

        if(!varInit){
            greatestX = collisionBody->SphereColliders[i]->xFinalPos + collisionBody->SphereColliders[i]->radius;
            lowestX = collisionBody->SphereColliders[i]->xFinalPos - collisionBody->SphereColliders[i]->radius;
            greatestY = collisionBody->SphereColliders[i]->yFinalPos + collisionBody->SphereColliders[i]->radius;
            lowestY = collisionBody->SphereColliders[i]->yFinalPos - collisionBody->SphereColliders[i]->radius;
            greatestZ = collisionBody->SphereColliders[i]->zFinalPos + collisionBody->SphereColliders[i]->radius;
            lowestZ = collisionBody->SphereColliders[i]->zFinalPos - collisionBody->SphereColliders[i]->radius;

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
