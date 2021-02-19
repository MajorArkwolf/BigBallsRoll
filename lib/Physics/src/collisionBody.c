#include "include/BigBalls/collisionBody.h"
#include <assert.h>
#include <math.h>

// TODO: move to external math library
float** rotationTransformationMatrix(float x, float y, float z){
    float** res = calloc(3, sizeof(float *));
    res[0] = calloc(3, sizeof(float));
    res[1] = calloc(3, sizeof(float));
    res[2] = calloc(3, sizeof(float));
    res[0][0] = cosf(x)*cosf(z);
    res[0][1] = -1.f*cosf(x)*sinf(z) + sinf(x)*sinf(y)*cosf(z);
    res[0][2] = sinf(x)*sinf(z) + cosf(x)*sinf(y)*cosf(z);
    res[1][0] = cosf(y)*sinf(z);
    res[1][1] = cosf(x)*cosf(z) + sinf(x)*sinf(y)*sinf(z);
    res[1][2] = -1.f*sinf(x)*cosf(z) + cosf(x)*sinf(y)*sinf(z);
    res[2][0] = -1.f*sinf(y);
    res[2][1] = sinf(x)*cosf(y);
    res[2][2] = cosf(x)*cosf(y);
    return res;
}

// TODO: move to external math library
float** matrixMultiplication(float **a, float **b, int a_numRow, int a_numCol, int b_numRow, int b_numCol){
    assert(a != NULL && b != NULL && a_numRow > 0 && a_numCol > 0 && b_numRow > 0 && b_numCol > 0 && a_numCol == b_numRow);

    float **res = calloc(b_numRow, sizeof(float *));
    for(int i = 0; i < b_numRow; ++i){
        res[i] = calloc(a_numCol, sizeof(float));
    }
    for(int i = 0; i < a_numRow; ++i)
    {
        for(int j = 0; j < b_numCol; ++j)
        {
            float sum = 0;
            for(int k = 0; k < b_numRow; ++k){
                sum += a[i][k]*b[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}

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

    // run maths unit test
    // TODO: move tests to external math library
    float** a = calloc(2, sizeof(float*)); // some example I found on khan academy :D
    a[0] = calloc(2, sizeof(float));
    a[1] = calloc(2, sizeof(float));
    a[0][0] = 1.f;
    a[0][1] = 7.f;
    a[1][0] = 2.f;
    a[1][1] = 4.f;
    float** b = calloc(2, sizeof(float*));
    b[0] = calloc(2, sizeof(float));
    b[1] = calloc(2, sizeof(float));
    b[0][0] = 3.f;
    b[0][1] = 3.f;
    b[1][0] = 5.f;
    b[1][1] = 2.f;
    float** res = matrixMultiplication(a, b, 2, 2, 2, 2);
    assert(res[0][0] == 38 && res[0][1] == 17 && res[1][0] == 26 && res[1][1] == 14);
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
    assert(collisionBody != NULL && xDist > 0 && yDist > 0 && zDist > 0);
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
    collisionBody->force = 0;
    collisionBody->forceDirX = 0;
    collisionBody->forceDirY = 0;
    collisionBody->forceDirZ = 0;
}

void CollisionBody_updateAABB(CollisionBody *collisionBody){
    assert(collisionBody != NULL && (collisionBody->numOfBoxColliders != 0 || collisionBody->numOfSphereColliders != 0)); // ensure that one collider exists before processing
    // declare local vars
    float greatestX, lowestX, greatestY, lowestY, greatestZ, lowestZ;

    // init min/max values
    if(collisionBody->numOfBoxColliders != 0){
        greatestX = collisionBody->BoxColliders[0]->xOffset + collisionBody->BoxColliders[0]->xLen;
        lowestX = collisionBody->BoxColliders[0]->xOffset;
        greatestY = collisionBody->BoxColliders[0]->yOffset + collisionBody->BoxColliders[0]->yLen;;
        lowestY = collisionBody->BoxColliders[0]->yOffset;
        greatestZ = collisionBody->BoxColliders[0]->zOffset + collisionBody->BoxColliders[0]->zLen;;
        lowestZ = collisionBody->BoxColliders[0]->zOffset;
    }
    else if(collisionBody->numOfSphereColliders != 0){
        greatestX = collisionBody->SphereColliders[0]->xOffset + collisionBody->SphereColliders[0]->radius;
        lowestX = collisionBody->SphereColliders[0]->xOffset - collisionBody->SphereColliders[0]->radius;
        greatestY = collisionBody->SphereColliders[0]->yOffset + collisionBody->SphereColliders[0]->radius;
        lowestY = collisionBody->SphereColliders[0]->yOffset - collisionBody->SphereColliders[0]->radius;
        greatestZ = collisionBody->SphereColliders[0]->zOffset + collisionBody->SphereColliders[0]->radius;
        lowestZ = collisionBody->SphereColliders[0]->zOffset - collisionBody->SphereColliders[0]->radius;
    }

    // create CollisionBody rotation matrix
    float** T1 = rotationTransformationMatrix(collisionBody->xRot,
                                              collisionBody->yRot,
                                              collisionBody->zRot);
    // get all BoxCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        // create BoxCollider rotation matrix
        float** T2 = rotationTransformationMatrix(collisionBody->BoxColliders[i]->xRot,
                                     collisionBody->BoxColliders[i]->yRot,
                                     collisionBody->BoxColliders[i]->zRot);
        // create overall transformation matrix from CollisionBody and BoxCollider rotation matrices
        float **T3 = matrixMultiplication(T1, T2, 3, 3, 3, 3);
        // allocate position vector of BoxCollider
        float **pos = calloc(3, sizeof(float *));
        pos[0] = calloc(1, sizeof(float));
        pos[1] = calloc(1, sizeof(float));
        pos[2] = calloc(1, sizeof(float));
        pos[0][0] = collisionBody->xPos;
        pos[1][0] = collisionBody->yPos;
        pos[2][0] = collisionBody->zPos;
        // apply transformation matrix to position vector
        float **final = matrixMultiplication(T3, pos, 3, 3, 3, 1);
        // free position vector
        free(pos[0]);
        free(pos[1]);
        free(pos[2]);
        free(pos);
        // store resulting position in BoxCollider object so it can be accessed later
        collisionBody->BoxColliders[i]->xAbsPos = final[0][0];
        collisionBody->BoxColliders[i]->yAbsPos = final[1][0];
        collisionBody->BoxColliders[i]->zAbsPos = final[2][0];

        // check for new min/max points
        if(collisionBody->BoxColliders[0]->xAbsPos + collisionBody->BoxColliders[0]->xLen > greatestX){ // x
            greatestX = collisionBody->BoxColliders[0]->xAbsPos + collisionBody->BoxColliders[0]->xLen;
        }
        if(collisionBody->BoxColliders[0]->xAbsPos + collisionBody->BoxColliders[0]->xLen < lowestX){
            lowestX = collisionBody->BoxColliders[0]->xAbsPos;
        }
        if(collisionBody->BoxColliders[0]->yAbsPos + collisionBody->BoxColliders[0]->yLen > greatestY){ // y
            greatestY = collisionBody->BoxColliders[0]->yAbsPos + collisionBody->BoxColliders[0]->yLen;
        }
        if(collisionBody->BoxColliders[0]->yAbsPos < lowestY){
            lowestY = collisionBody->BoxColliders[0]->yAbsPos;
        }
        if(collisionBody->BoxColliders[0]->zAbsPos + collisionBody->BoxColliders[0]->zLen > greatestZ){ // z
            greatestZ = collisionBody->BoxColliders[0]->zAbsPos + collisionBody->BoxColliders[0]->zLen;
        }
        if(collisionBody->BoxColliders[0]->zAbsPos < lowestZ){
            lowestZ = collisionBody->BoxColliders[0]->zAbsPos;
        }
    }

    // get all SphereCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        // allocate position vector of SphereCollider
        float **pos = calloc(3, sizeof(float *));
        pos[0] = calloc(1, sizeof(float));
        pos[1] = calloc(1, sizeof(float));
        pos[2] = calloc(1, sizeof(float));
        pos[0][0] = collisionBody->xPos;
        pos[1][0] = collisionBody->yPos;
        pos[2][0] = collisionBody->zPos;
        // apply CollisionBody rotation transformation matrix to position vector (a sphere cannot be rotated from the perspective of the physics engine)
        float **final = matrixMultiplication(T1, pos, 3, 3, 3, 1);
        // free position vector
        free(pos[0]);
        free(pos[1]);
        free(pos[2]);
        free(pos);
        // store resulting position in SphereCollider to be accessed later
        collisionBody->SphereColliders[i]->xAbsPos = final[0][0];
        collisionBody->SphereColliders[i]->yAbsPos = final[1][0];
        collisionBody->SphereColliders[i]->zAbsPos = final[2][0];

        // check for new min/max points
        if(collisionBody->SphereColliders[0]->xAbsPos + collisionBody->SphereColliders[0]->radius > greatestX){ // x
            greatestX = collisionBody->SphereColliders[0]->xAbsPos + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->xAbsPos - collisionBody->SphereColliders[0]->radius < lowestX){
            lowestX = collisionBody->SphereColliders[0]->xAbsPos - collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yAbsPos + collisionBody->SphereColliders[0]->radius > greatestY){ // y
            greatestY = collisionBody->SphereColliders[0]->yAbsPos + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yAbsPos - collisionBody->SphereColliders[0]->radius < lowestY){
            lowestY = collisionBody->SphereColliders[0]->yAbsPos - collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yAbsPos + collisionBody->SphereColliders[0]->radius > greatestZ){ // z
            greatestZ = collisionBody->SphereColliders[0]->yAbsPos + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yAbsPos - collisionBody->SphereColliders[0]->radius < lowestZ){
            lowestZ = collisionBody->SphereColliders[0]->yAbsPos - collisionBody->SphereColliders[0]->radius;
        }
    }

    // free CollisionBody rotation transformation matrix
    free(T1[0]);
    free(T1[1]);
    free(T1[2]);
    free(T1);

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
