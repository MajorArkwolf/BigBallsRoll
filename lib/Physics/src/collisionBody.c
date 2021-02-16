#include "include/BigBalls/collisionBody.h"
#include <assert.h>

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
    collisionBody->xPos += xDist; // update CollisionBody position
    collisionBody->yPos += yDist;
    collisionBody->zPos += zDist;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_rotate(CollisionBody *collisionBody,
                          float xRot,
                          float yRot,
                          float zRot){
    collisionBody->BoxColliders;
    collisionBody->SphereColliders;
    collisionBody->xRot += xRot; // update CollisionBody rotation
    collisionBody->yRot += yRot;
    collisionBody->zRot += zRot;
    CollisionBody_updateAABB(collisionBody);
}

void CollisionBody_scale(CollisionBody *collisionBody,
                         float scaleFactor){
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

void CollisionBody_sleep(CollisionBody *collisonBody){
    //TODO: implement
}

void CollisionBody_awake(CollisionBody *collisionBody){
    // TODO: implement
}

void CollisionBody_stop(CollisionBody *collisionBody){
    // TODO: check if stop should do more
    collisionBody->xVel = 0;
    collisionBody->yVel = 0;
    collisionBody->zVel = 0;
    collisionBody->force = 0;
    collisionBody->forceDirX = 0;
    collisionBody->forceDirY = 0;
    collisionBody->forceDirZ = 0;
}

void CollisionBody_updateAABB(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    assert(collisionBody != NULL && (collisionBody->numOfBoxColliders != 0 || collisionBody->numOfSphereColliders != 0)); // ensure that one collider exists before processing

    /*for(boxCollider in BoxColliders){
        // apply global rotation
        // apply local rotation
    }

    // apply global rotation
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        collisionBody->SphereColliders[i]->xAbs =
    }*/

    // declare local vars
    float greatestX, lowestX, greatestY, lowestY, greatestZ, lowestZ;
    // init min/max vertices
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

    // get all BoxCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfBoxColliders; ++i){
        if(collisionBody->BoxColliders[0]->xOffset + collisionBody->BoxColliders[0]->xLen > greatestX){ // x
            greatestX = collisionBody->BoxColliders[0]->xOffset + collisionBody->BoxColliders[0]->xLen;
        }
        if(collisionBody->BoxColliders[0]->zOffset + collisionBody->BoxColliders[0]->xLen < lowestX){
            lowestX = collisionBody->BoxColliders[0]->xOffset;
        }
        if(collisionBody->BoxColliders[0]->yOffset + collisionBody->BoxColliders[0]->yLen > greatestY){ // y
            greatestY = collisionBody->BoxColliders[0]->yOffset + collisionBody->BoxColliders[0]->yLen;
        }
        if(collisionBody->BoxColliders[0]->yOffset < lowestY){
            lowestY = collisionBody->BoxColliders[0]->yOffset;
        }
        if(collisionBody->BoxColliders[0]->zOffset + collisionBody->BoxColliders[0]->zLen > greatestZ){ // z
            greatestZ = collisionBody->BoxColliders[0]->zOffset + collisionBody->BoxColliders[0]->zLen;
        }
        if(collisionBody->BoxColliders[0]->zOffset < lowestZ){
            lowestZ = collisionBody->BoxColliders[0]->zOffset;
        }
    }
    // get all SphereCollider min/max vertices
    for(size_t i = 0; i < collisionBody->numOfSphereColliders; ++i){
        if(collisionBody->SphereColliders[0]->xOffset + collisionBody->SphereColliders[0]->radius > greatestX){ // x
            greatestX = collisionBody->SphereColliders[0]->xOffset + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->xOffset - collisionBody->SphereColliders[0]->radius < lowestX){
            lowestX = collisionBody->SphereColliders[0]->xOffset - collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yOffset + collisionBody->SphereColliders[0]->radius > greatestY){ // y
            greatestY = collisionBody->SphereColliders[0]->yOffset + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->yOffset - collisionBody->SphereColliders[0]->radius < lowestY){
            lowestY = collisionBody->SphereColliders[0]->yOffset - collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->zOffset + collisionBody->SphereColliders[0]->radius > greatestZ){ // z
            greatestZ = collisionBody->SphereColliders[0]->zOffset + collisionBody->SphereColliders[0]->radius;
        }
        if(collisionBody->SphereColliders[0]->zOffset - collisionBody->SphereColliders[0]->radius < lowestZ){
            lowestZ = collisionBody->SphereColliders[0]->zOffset - collisionBody->SphereColliders[0]->radius;
        }
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

void CollisionBody_updateOOBB(CollisionBody *collisionBody){
    // TODO: stub
}