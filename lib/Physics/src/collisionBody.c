#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "include/BigBalls/collisionBody.h"
#include "include/BigBalls/physicsMathsCommon.h"

void CollisionBody_init(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    collisionBody->numOfColliders = 0;
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->BoxColliders = NULL;
    collisionBody->boxCollidersAlloced = 0;
    collisionBody->SphereColliders = NULL;
    collisionBody->sphereCollidersAlloced = 0;
    collisionBody->id = -1;
    collisionBody->xPos = 0.0f;
    collisionBody->yPos = 0.0f;
    collisionBody->zPos = 0.0f;
    collisionBody->xRot = 0.0f;
    collisionBody->yRot = 0.0f;
    collisionBody->zRot = 0.0f;
    collisionBody->velocity.data[0] = 0.0f;
    collisionBody->velocity.data[1] = 0.0f;
    collisionBody->velocity.data[2] = 0.0f;
    collisionBody->force.data[0] = 1.0f;
    collisionBody->force.data[1] = 1.0f;
    collisionBody->force.data[2] = 1.0f;
    collisionBody->AABBx1 = 0.0f;
    collisionBody->AABBy1 = 0.0f;
    collisionBody->AABBz1 = 0.0f;
    collisionBody->AABBx2 = 0.0f;
    collisionBody->AABBy2 = 0.0f;
    collisionBody->AABBz2 = 0.0f;
    collisionBody->mass = 1;
    collisionBody->restitution = 1.0f;
    collisionBody->isStatic = false;
}

void CollisionBody_free(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    if (collisionBody->BoxColliders != NULL) {
        for (size_t i = 0; i < collisionBody->numOfBoxColliders; ++i) {
            free(collisionBody->BoxColliders[i]);
            collisionBody->BoxColliders[i] = NULL;
        }
        free(collisionBody->BoxColliders);
        collisionBody->BoxColliders = NULL;
    }

    if (collisionBody->SphereColliders != NULL) {
        for (size_t i = 0; i < collisionBody->numOfSphereColliders; ++i) {
            free(collisionBody->SphereColliders[i]);
            collisionBody->SphereColliders[i] = NULL;
        }
        free(collisionBody->SphereColliders);
        collisionBody->SphereColliders = NULL;
    }

    // Reset colliderManager values
    collisionBody->numOfBoxColliders = 0;
    collisionBody->numOfSphereColliders = 0;
    collisionBody->numOfColliders = 0;
}

void CollisionBody_addBoxCollider(CollisionBody *collisionBody,
                                  BoxCollider *boxCollider){
    assert(collisionBody != NULL);
    // Allocate new, larger array if needed
    if(collisionBody->BoxColliders == NULL){
        collisionBody->BoxColliders = calloc(1, sizeof(BoxCollider *));
        collisionBody->boxCollidersAlloced = 1;
    }
    else if (collisionBody->boxCollidersAlloced < collisionBody->numOfBoxColliders + 1){
        collisionBody->BoxColliders = realloc(collisionBody->BoxColliders, (sizeof(BoxCollider *)) * (collisionBody->boxCollidersAlloced * 2));
        collisionBody->boxCollidersAlloced *= 2;
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
    // Allocate new, larger array if needed
    if(collisionBody->SphereColliders == NULL){
        collisionBody->SphereColliders = calloc(1, sizeof(SphereCollider *));
        collisionBody->sphereCollidersAlloced = 1;
    }
    else if (collisionBody->sphereCollidersAlloced < collisionBody->numOfSphereColliders + 1){
        collisionBody->SphereColliders = realloc(collisionBody->SphereColliders, sizeof(SphereCollider *) * (collisionBody->sphereCollidersAlloced * 2));
        collisionBody->sphereCollidersAlloced *= 2;
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
    float newRotX = collisionBody->xRot + xRot; // update CollisionBody rotation
    float newRotY = collisionBody->yRot + yRot;
    float newRotZ = collisionBody->zRot + zRot;

    if(newRotX != 0){
        newRotX = fmodf(newRotX, 360.f);
    }
    if(newRotY != 0){
        newRotY = fmodf(newRotY, 360.f);
    }
    if(newRotZ != 0){
        newRotZ = fmodf(newRotZ, 360.f);
    }

    collisionBody->xRot = newRotX;
    collisionBody->yRot = newRotY;
    collisionBody->zRot = newRotZ;
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
    collisionBody->velocity.data[0] = 0;
    collisionBody->velocity.data[1] = 0;
    collisionBody->velocity.data[2] = 0;
    collisionBody->force.data[0] = 0;
    collisionBody->force.data[1] = 0;
    collisionBody->force.data[2] = 0;
}

void CollisionBody_updateAABB(CollisionBody *collisionBody){
    assert(collisionBody != NULL); // ensure that one collider exists before processing
    if (collisionBody->numOfBoxColliders != 0 || collisionBody->numOfSphereColliders != 0) {
        float greatestX, lowestX, greatestY, lowestY, greatestZ, lowestZ; // must be initialised to a point on a collider post-rotation
        bool varInit = false;

        // CollisionBody rotation matrix
        Matrix44 T1 = createRotMat(collisionBody->xRot,
                                   collisionBody->yRot,
                                   collisionBody->zRot);

        // get all BoxCollider min/max vertices
        for (size_t i = 0; i < collisionBody->numOfBoxColliders; ++i) { // for each collider
            BoxColliderVerts verts = getBoxColliderVerts(collisionBody->BoxColliders[i]);
            float bGreatestX, bLowestX, bGreatestY, bLowestY, bGreatestZ, bLowestZ; // must be initialised to a point on a collider post-rotation
            bool bVarInit = false;

            for (size_t j = 0; j < 8; ++j) { // for each vertex of BoxCollider
                Matrix41 transformedVert = matrixMultiplication44_41(T1, verts.verts[j]); // TODO: may be more efficient transforming a single point and determining extents from it, see previous commits

                // update box collider proposed AABB
                if(!bVarInit){
                    bGreatestX = bLowestX = transformedVert.elem[0] + collisionBody->xPos;
                    bGreatestY = bLowestY = transformedVert.elem[0] + collisionBody->yPos;
                    bGreatestZ = bLowestZ = transformedVert.elem[0] + collisionBody->zPos;
                    bVarInit = true;
                }
                testPointMinMax(transformedVert.elem[0] + collisionBody->xPos, 0, &bLowestX, &bGreatestX);
                testPointMinMax(transformedVert.elem[0] + collisionBody->yPos, 0, &bLowestY, &bGreatestY);
                testPointMinMax(transformedVert.elem[0] + collisionBody->zPos, 0, &bLowestZ, &bGreatestZ);

                // update collision body proposed AABB
                if (!varInit) { // init min/max values
                    greatestX = lowestX = transformedVert.elem[0] + collisionBody->xPos;
                    greatestY = lowestY = transformedVert.elem[1] + collisionBody->yPos;
                    greatestZ = lowestZ = transformedVert.elem[2] + collisionBody->zPos;
                    varInit = true;
                }
                testPointMinMax(transformedVert.elem[0] + collisionBody->xPos, 0, &lowestX, &greatestX);
                testPointMinMax(transformedVert.elem[1] + collisionBody->yPos, 0, &lowestY, &greatestY);
                testPointMinMax(transformedVert.elem[2] + collisionBody->zPos, 0, &lowestZ, &greatestZ);
            }
            // set box collider AABB
            BoxCollider_updateAABB(collisionBody->BoxColliders[i], bLowestX, bLowestY, bLowestZ, bGreatestX, bGreatestY, bGreatestZ);
        }

        // get all SphereCollider min/max vertices
        for (size_t i = 0; i < collisionBody->numOfSphereColliders; ++i) {
            // allocate position vector of SphereCollider
            Matrix41 pos = {collisionBody->xPos + collisionBody->SphereColliders[i]->xOffset,
                            collisionBody->yPos + collisionBody->SphereColliders[i]->yOffset,
                            collisionBody->zPos + collisionBody->SphereColliders[i]->zOffset};
            // apply CollisionBody rotation transformation matrix to position vector (a sphere cannot be rotated from the perspective of the physics engine)
            Matrix41 finalPos = matrixMultiplication44_41(T1, pos);

            SphereCollider_updatePostRotPos(collisionBody->SphereColliders[i], finalPos.elem[0], finalPos.elem[1], finalPos.elem[2]);

            if (!varInit) {
                greatestX = lowestX = finalPos.elem[0] + collisionBody->SphereColliders[i]->radius;
                greatestY = lowestY = finalPos.elem[1] + collisionBody->SphereColliders[i]->radius;
                greatestZ = lowestZ = finalPos.elem[2] + collisionBody->SphereColliders[i]->radius;
                varInit = true;
            }
            // check for new min/max points, "len" extends in both directions from position
            testPointMinMax(finalPos.elem[0], collisionBody->SphereColliders[i]->radius, &lowestX, &greatestX);
            testPointMinMax(finalPos.elem[0], -1.f * collisionBody->SphereColliders[i]->radius, &lowestX, &greatestX);
            testPointMinMax(finalPos.elem[1], collisionBody->SphereColliders[i]->radius, &lowestY, &greatestY);
            testPointMinMax(finalPos.elem[1], -1.f * collisionBody->SphereColliders[i]->radius, &lowestY, &greatestY);
            testPointMinMax(finalPos.elem[2], collisionBody->SphereColliders[i]->radius, &lowestZ, &greatestZ);
            testPointMinMax(finalPos.elem[2], -1.f * collisionBody->SphereColliders[i]->radius, &lowestZ, &greatestZ);
        }

        // got dimensions for box, assign to CollisionBody
        collisionBody->AABBx1 = lowestX;
        collisionBody->AABBx2 = greatestX;
        collisionBody->AABBy1 = lowestY;
        collisionBody->AABBy2 = greatestY;
        collisionBody->AABBz1 = lowestZ;
        collisionBody->AABBz2 = greatestZ;
    }
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
    if(x != 0){
        x = fmodf(x, 360.f);
    }
    if(y != 0){
        y = fmodf(y, 360.f);
    }
    if(z != 0){
        z = fmodf(z, 360.f);
    }
    collisionBody->xRot = x;
    collisionBody->yRot = y;
    collisionBody->zRot = z;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_registerBoxCollider(CollisionBody *cb, const float *offsetPosition, const float *length) {
    BoxCollider *boxCollider = malloc(1 * sizeof (BoxCollider));
    boxCollider->xOffset = offsetPosition[0];
    boxCollider->yOffset = offsetPosition[1];
    boxCollider->zOffset = offsetPosition[2];
    boxCollider->xLen = length[0];
    boxCollider->yLen = length[1];
    boxCollider->zLen = length[2];
    CollisionBody_addBoxCollider(cb, boxCollider);
}

void CollisionBody_registerSphereCollider(CollisionBody *cb, const float *offsetPosition, const float radius) {
    SphereCollider *sphereCollider = malloc(1 * sizeof (SphereCollider));
    sphereCollider->xOffset = offsetPosition[0];
    sphereCollider->yOffset = offsetPosition[1];
    sphereCollider->zOffset = offsetPosition[2];
    sphereCollider->radius = radius;
    CollisionBody_addSphereCollider(cb, sphereCollider);
}

void CollisionBody_setCollisionBodyStatic(CollisionBody *cb, bool isStatic) {
    cb->isStatic = isStatic;
}

void CollisionBody_addForce(CollisionBody *cb, float xForce, float yForce, float zForce) {
    cb->force.data[0] += xForce;
    cb->force.data[1] += yForce;
    cb->force.data[2] += zForce;
}

void CollisionBody_resetForce(CollisionBody *cb) {
    cb->force.data[0] = 0;
    cb->force.data[1] = 0;
    cb->force.data[2] = 0;
}

void CollisionBody_setMass(CollisionBody *cb, float mass) {
    cb->mass = mass;
}
