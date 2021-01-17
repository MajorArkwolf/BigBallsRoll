#include "include/BigBalls/collisionBodyManager.h"
#include <assert.h>

int getID(CollisionBodyManager *collisionBodyManager){
    assert(collisionBodyManager != NULL);
    // increment and return new id
    return collisionBodyManager->idCount++;
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
    collisionBodyManager->collisionBodies[collisionBodyManager->numCollisionBodies]->id = getID(collisionBodyManager);
    collisionBodyManager->numCollisionBodies++;
}

void CollisionBodyManager_rm(CollisionBodyManager *collisionBodyManager,
                             int id){
    assert(collisionBodyManager != NULL);
}
