#include "include/BigBalls/physicsWorld.h"
#include <assert.h>

int newCollisionBodyID(PhysicsWorld *physicsWorld){
    assert(physicsWorld != NULL);
    // increment internal ID count and return new ID
    return ++physicsWorld->idCount;
}

CollisionBody* findCollisionBody(PhysicsWorld *physicsWorld, const int ID){
    for(size_t i = 0; i < physicsWorld->numCollisionBodies; ++i){
        if(physicsWorld->collisionBodies[i]->id == ID){
            return physicsWorld->collisionBodies[i];
        }
    }
    return NULL;
}

void PhysicsWorld_init(PhysicsWorld *physicsWorld){
    assert(physicsWorld != NULL);
    physicsWorld->collisionBodies = NULL;
    physicsWorld->numCollisionBodies = 0;
    physicsWorld->idCount = 0;
}

void PhysicsWorld_free(PhysicsWorld *physicsWorld){
    assert(physicsWorld != NULL);
    for(size_t i = 1; i < physicsWorld->numCollisionBodies; ++i){
        CollisionBody_free(physicsWorld->collisionBodies[i]);
    }
    free(physicsWorld);
    physicsWorld = NULL;
}

void PhysicsWorld_add(PhysicsWorld *physicsWorld,
                              CollisionBody *collisionBody){
    assert(physicsWorld != NULL);
    // Allocate new, larger array
    if(physicsWorld->collisionBodies == NULL){
        physicsWorld->collisionBodies = calloc(1, sizeof(CollisionBody));
    }
    else{
        physicsWorld->collisionBodies = realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * physicsWorld->numCollisionBodies + 1);
    }
    // Copy BoxCollider object into array
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies] = collisionBody;
    // Assign ID to BoxCollider
    physicsWorld->collisionBodies[physicsWorld->numCollisionBodies]->id = newCollisionBodyID(physicsWorld);
    physicsWorld->numCollisionBodies++;
}

void PhysicsWorld_rm(PhysicsWorld *physicsWorld, const int ID){
    assert(physicsWorld != NULL);
    for(size_t i = 0; i < physicsWorld->numCollisionBodies; ++i){
        if(physicsWorld->collisionBodies[i]->id == ID){
            CollisionBody_free(physicsWorld->collisionBodies[i]);
            for(size_t j = i + 1; j < physicsWorld->numCollisionBodies; ++j){ // for each collisionbody after match index
                physicsWorld->collisionBodies[j - 1] = physicsWorld->collisionBodies[j];
            }
            physicsWorld->collisionBodies[physicsWorld->numCollisionBodies - 1] = NULL;
            --physicsWorld->numCollisionBodies;
            // reduce size of memory allocation (shouldn't be costly if realloc() realises whats going on)
            realloc(physicsWorld->collisionBodies, sizeof(CollisionBody) * physicsWorld->numCollisionBodies);
        }
    }
}
