#include "include/BigBalls/collisionBodyManager.h"
#include <assert.h>

int newCollisionBodyID(CollisionBodyManager *collisionBodyManager){
    assert(collisionBodyManager != NULL);
    // increment internal ID count and return new ID
    return ++collisionBodyManager->idCount;
}

bool testAABBCollision(const float X1POS,
                       const float Y1POS,
                       const float Z1POS,
                       const float X1LEN,
                       const float Y1LEN,
                       const float Z1LEN,
                       const float X2POS,
                       const float Y2POS,
                       const float Z2POS,
                       const float X2LEN,
                       const float Y2LEN,
                       const float Z2LEN){
    const float D1X = X1POS - (X2POS + X2LEN);
    const float D1Y = Y1POS - (Y2POS + Y2LEN);
    const float D1Z = Z1POS - (Z2POS + Z2LEN);
    const float D2X = X2POS - (X1POS + X1LEN);
    const float D2Y = Y2POS - (Y1POS + Y1LEN);
    const float D2Z = Z2POS - (Z1POS + Z1LEN);

    // if smallest coord of a box is greater than largest x coord of other box, the boxes cannot be colliding
    return D1X > 0.0f || D1Y > 0.0f || D1Z > 0.0f || D2X > 0.0f || D2Y > 0.0f || D2Z > 0.0f ? false : true;
}

void detectCollisions(CollisionBodyManager * collisionBodyManager){
    // TODO: ideally shouldn't check every body against each other - spacial partitioning method ideal
    // broad phase
    for(size_t i = 0; collisionBodyManager->numCollisionBodies; ++i){
        for(size_t j = 0; collisionBodyManager->numCollisionBodies; j++){
            if(i != j){ // dont check for collision of the same object
                // TODO: stub
            }
        }
    }
    // narrow phase
}

CollisionBody* findCollisionBody(CollisionBodyManager *collisionBodyManager, const int ID){
    for(size_t i = 0; i < collisionBodyManager->numCollisionBodies; ++i){
        if(collisionBodyManager->collisionBodies[i]->id == ID){
            return collisionBodyManager->collisionBodies[i];
        }
    }
    return NULL;
}

void CollisionBodyManager_init(CollisionBodyManager *collisionBodyManager){
    assert(collisionBodyManager != NULL);
    collisionBodyManager->collisionBodies = NULL;
    collisionBodyManager->numCollisionBodies = 0;
    collisionBodyManager->idCount = 0;
}

void CollisionBodyManager_free(CollisionBodyManager *collisionBodyManager){
    assert(collisionBodyManager != NULL);
    for(size_t i = 1; i < collisionBodyManager->numCollisionBodies; ++i){
        CollisionBody_free(collisionBodyManager->collisionBodies[i]);
    }
    free(collisionBodyManager);
    collisionBodyManager = NULL;
}

void CollisionBodyManager_add(CollisionBodyManager *collisionBodyManager,
                              CollisionBody *collisionBody){
    assert(collisionBodyManager != NULL);
    // Allocate new, larger array
    if(collisionBodyManager->collisionBodies == NULL){
        collisionBodyManager->collisionBodies = calloc(1, sizeof(CollisionBody));
    }
    else{
        collisionBodyManager->collisionBodies = realloc(collisionBodyManager->collisionBodies, sizeof(CollisionBody) * collisionBodyManager->numCollisionBodies + 1);
    }
    // Copy BoxCollider object into array
    collisionBodyManager->collisionBodies[collisionBodyManager->numCollisionBodies] = collisionBody;
    // Assign ID to BoxCollider
    collisionBodyManager->collisionBodies[collisionBodyManager->numCollisionBodies]->id = newCollisionBodyID(collisionBodyManager);
    collisionBodyManager->numCollisionBodies++;
}

void CollisionBodyManager_rm(CollisionBodyManager *collisionBodyManager, const int ID){
    assert(collisionBodyManager != NULL);
    for(size_t i = 0; i < collisionBodyManager->numCollisionBodies; ++i){
        if(collisionBodyManager->collisionBodies[i]->id == ID){
            CollisionBody_free(collisionBodyManager->collisionBodies[i]);
            for(size_t j = i + 1; j < collisionBodyManager->numCollisionBodies; ++j){ // for each collisionbody after match index
                collisionBodyManager->collisionBodies[j - 1] = collisionBodyManager->collisionBodies[j];
            }
            collisionBodyManager->collisionBodies[collisionBodyManager->numCollisionBodies - 1] = NULL;
            --collisionBodyManager->numCollisionBodies;
            // reduce size of memory allocation (shouldn't be costly if realloc() realises whats going on)
            realloc(collisionBodyManager->collisionBodies, sizeof(CollisionBody) * collisionBodyManager->numCollisionBodies);
        }
    }
}
