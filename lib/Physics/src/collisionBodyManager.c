#include "include/BigBalls/collisionBodyManager.h"
#include <assert.h>

int newCollisionBodyID(CollisionBodyManager *collisionBodyManager){
    assert(collisionBodyManager != NULL);
    // increment internal ID count and return new ID
    return ++collisionBodyManager->idCount;
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
